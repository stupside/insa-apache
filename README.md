# insa-apache

**insa-apache** is a tool crafted for analyzing Apache logs and generating DOT graphs, offering valuable insights into web server activities.

## Table of Contents

- [Overview](#insa-apache)
- [Makefile](#makefile)
  - [Builds](#builds)
  - [Build Commands](#build-commands)
  - [Run Commands](#run-commands)
- [Help](#help)
  - [Examples](#examples)
  - [Error Codes](#error-codes)

---

## Makefile

### Builds

The project builds are organized in the `.build` directory, containing the following binaries:

- `.build/analog`
- `.build/analog_debug`

### Build Commands

Building the project is streamlined with the provided makefile. Use the following commands:

- `make build`: Build the release version.
- `make debug`: Build the debug version.

### Run Commands

Run the project manually or by utilizing the provided makefile commands:

- `make val`: Execute the binary with valgrind for memory analysis.
- `make dev`: Run the binary with the DEBUG flag for detailed execution tracing.

---

## Help

Arguments can be chained, and their order is not important.

```sh
-h              Show this help message and exit
-g FILE         Specify the output file
-t HOUR         Filter by hour (e.g., ./analog -t 12)
-d DOMAIN       Filter by domain (e.g., ./analog -d insa-lyon.fr)
-e EXTENSION    Filter by extension (e.g., ./analog -e)
```

### Examples

```sh
# Basic analysis
./analog ./samples/medium.log

# Filter by hour
./analog ./samples/medium.log -t 12

# Filter by domain
./analog ./samples/medium.log -d insa-lyon.fr

# Filter by extension
./analog ./samples/medium.log -e

# Combined filters
./analog ./samples/medium.log -e -d insa-lyon.fr
./analog ./samples/medium.log -e -d insa-lyon.fr -t 12
```

### Error Codes

When running the binary from your code, it's crucial to receive feedback and handle execution errors properly. Here are some error codes:

- `22`: Invalid argument
- `2`: No such file or directory
