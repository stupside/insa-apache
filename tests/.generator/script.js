const { execSync } = require('child_process');

const fs = require('fs');
const path = require('path');

// Hardcoded commands with specific values for the -d option
const commands = [
  // Basic analyses
  `../../.build/analog ../../samples/small.log -g dot`,
  `../../.build/analog ../../samples/medium.log -g dot`,
  `../../.build/analog ../../samples/big.log -g dot`,

  // Filter by hour
  `../../.build/analog ../../samples/small.log -t 15 -g dot`,

  // Filter by domain
  `../../.build/analog ../../samples/small.log -d www.google.fr -g dot`,
  `../../.build/analog ../../samples/medium.log -d intranet-if.insa-lyon.fr -g dot`,
  `../../.build/analog ../../samples/big.log -d if.insa-lyon.fr -g dot`,
  `../../.build/analog ../../samples/small.log -d -g dot`, // Invalid domain value

  // Filter by extension
  `../../.build/analog ../../samples/small.log -e -g dot`,
  `../../.build/analog ../../samples/medium.log -e -g dot`,
  `../../.build/analog ../../samples/big.log -e -g dot`,

  // Combined filters
  `../../.build/analog ../../samples/small.log -e -d www.google.fr -g dot`,
  `../../.build/analog ../../samples/medium.log -e -d intranet-if.insa-lyon.fr -t 10 -g dot`,
  `../../.build/analog ../../samples/big.log -e -d if.insa-lyon.fr -t 16 -g dot`,
  `../../.build/analog ../../samples/small.log -t 12 -d -g dot`, // Invalid domain value
  `../../.build/analog ../../samples/medium.log -t 8 -e -g dot`,
  `../../.build/analog ../../samples/big.log -t 14 -e -d www.google.fr -g dot`,
  
  // Edge cases
  `../../.build/analog ../../samples/small.log -t -1 -g dot`, // Negative hour (Error expected)
  `../../.build/analog ../../samples/big.log -t 24 -e -g dot`, // Hour greater than 23 (Error expected)
  `../../.build/analog ../../samples/small.log -d "" -g dot`, // Empty domain (No error expected)
  `../../.build/analog ../../samples/nonexistent.log -g dot`, // Nonexistent log file (Error expected)
];

// Hardcoded descriptions for each command
const hardcodedDescriptions = [
  // Basic analyses
  'Perform basic analysis of the small.log journal file. (No error expected)',
  'Perform basic analysis of the medium.log journal file. (No error expected)',
  'Perform basic analysis of the big.log journal file. (No error expected)',

  // Filter by hour
  'Filter by hour (15) and generate an output file dot. (No error expected)',

  // Filter by domain
  'Filter by domain (www.google.fr) and generate an output file dot. (No error expected)',
  'Filter by domain (intranet-if.insa-lyon.fr) and generate an output file dot. (No error expected)',
  'Filter by domain (if.insa-lyon.fr) and generate an output file dot. (No error expected)',
  'Filter by domain (INVALID) and generate an output file dot. (Error expected)',

  // Filter by extension
  'Filter by extension and generate an output file dot. (No error expected)',
  'Filter by extension and generate an output file dot. (No error expected)',
  'Filter by extension and generate an output file dot. (No error expected)',

  // Combined filters
  'Filter by extension and domain (www.google.fr) and generate an output file dot. (No error expected)',
  'Filter by extension, domain (intranet-if.insa-lyon.fr), and hour (10) and generate an output file dot. (No error expected)',
  'Filter by extension, domain (if.insa-lyon.fr), and hour (16) and generate an output file dot. (No error expected)',
  'Filter by hour (12) and domain (INVALID) and generate an output file dot. (Error expected)',
  'Filter by hour (8), extension, and generate an output file dot. (No error expected)',
  'Filter by hour (14), extension, and domain (www.google.fr) and generate an output file dot. (No error expected)',

  // Edge cases
  'Filter by negative hour (-1) and generate an output file dot. (Error expected)',
  'Filter by hour (24), extension, and generate an output file dot. (Error expected)',
  'Filter by empty domain and generate an output file dot. (No error expected)',
  'Analyze a nonexistent.log journal file (which does not exist) and generate an output file dot. (Error expected)',
];

// Create a folder for each command
for (let i = 0; i < commands.length; i++) {
  const folderName = `Test${i + 1}`;
  fs.mkdirSync(folderName);

  const stdErrStream = fs.createWriteStream(path.join(folderName, 'stderr.out'));
  const descriptionStream = fs.createWriteStream(path.join(folderName, 'description'));
  const runStream = fs.createWriteStream(path.join(folderName, 'run'));

  try {
    const command = commands[i];

    // Execute the command and capture error output (stderr)
    execSync(command, { stdio: ['ignore', 'pipe', 'pipe'] });

    // If no error occurred, create the std.out file
    const stdOutStream = fs.createWriteStream(path.join(folderName, 'std.out'));
    const stdout = execSync(command, { encoding: 'utf-8', stdio: ['pipe', 'pipe', 'pipe'] });
    stdOutStream.write(stdout);
    stdOutStream.end();

    descriptionStream.write(`Command: ${command}\n`);
    descriptionStream.write(`Description: ${hardcodedDescriptions[i]}\n\n`);
    runStream.write(`${command}\n`);

    // Rename and move the .dot file to .outfile
    const dotFilePathSource = path.join(__dirname, `dot`);
    const dotFilePathDestination = path.join(__dirname, folderName, `dot.outfile`);
    fs.renameSync(dotFilePathSource, dotFilePathDestination);
  } catch (error) {
    console.error(`Error executing command: ${commands[i]}`);
    console.error(error.stderr.toString());
    stdErrStream.write(error.stderr.toString());
    descriptionStream.write(`Command: ${commands[i]}\n`);
    descriptionStream.write(`Description: ${hardcodedDescriptions[i]} (Error expected)\n\n`);
    runStream.write(`${commands[i]}\n`);
  }

  stdErrStream.end();
  descriptionStream.end();
  runStream.end();

  console.log(`Execution of command ${i + 1} completed. Check ${folderName}/stderr.out, ${folderName}/description, ${folderName}/run, and ${folderName}/dot.outfile files for output.`);
}
