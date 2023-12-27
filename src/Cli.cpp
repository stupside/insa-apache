
#include "header/Cli.h"

#include "header/Graph.h"
#include "header/GraphFilter.h"

const std::string Cli::CLI_HELP = "-h";

const std::string Cli::CLI_OUTPUT = "-g";

const std::string Cli::CLI_FILTER_HOUR = "-t";
const std::string Cli::CLI_FILTER_DOMAIN = "-d";
const std::string Cli::CLI_FILTER_EXTENSION = "-e";

Cli::Cli()
{
#ifdef MAP
    std::cout << "Cli constructor called" << std::endl;
#endif
}

unsigned int Cli::ProcessArguments(int argc, const char **args)
{
    static const Cli cli;

    GraphFilter filter;

    std::string input, output;

    for (int index = 1; index < argc; ++index)
    {
        const std::string arg = args[index];

        if (arg == Cli::CLI_HELP)
        {
            std::cout << cli;

            return 0;
        }
        else
        {
            if (arg == Cli::CLI_FILTER_DOMAIN)
            {
                const std::string domain = args[++index];

                filter.FilterByDomain(domain);
            }
            else if (arg == Cli::CLI_FILTER_EXTENSION)
            {
                filter.FilterByExtension("gif")
                    .FilterByExtension("ico")
                    .FilterByExtension("png")
                    .FilterByExtension("jpg")
                    .FilterByExtension("css")
                    .FilterByExtension("js");
            }
            else if (arg == Cli::CLI_FILTER_HOUR)
            {
                const std::string hour = args[++index];

                if (hour.find_first_not_of("0123456789") != std::string::npos)
                {
                    std::cerr << "Error: " << Cli::CLI_FILTER_HOUR << " Argument must be an integer" << std::endl;

                    return EINVAL;
                }

                unsigned int hourInt = std::stoi(hour);

                if (hourInt < 0 || hourInt > 23)
                {
                    std::cerr << "Error: " << Cli::CLI_FILTER_HOUR << " Argument must be between 0 and 23" << std::endl;

                    return EINVAL;
                }

                filter.FilterByHour(hourInt);
            }
            else if (arg == Cli::CLI_OUTPUT)
            {
                output = args[++index];
            }
            else
            {
                input = args[index];
            }
        }
    }

    if (input.empty())
    {
        std::cerr << "Error: No log file specified" << std::endl;

        return EINVAL;
    }
    else
    {
        Graph graph(&filter);

        std::cout << graph.GetFilter();

        if (LoadGraph(graph, input))
        {
            if (output.empty() == false && SaveGraph(graph, output) == false)
            {
                std::cerr << "Error: " << Cli::CLI_OUTPUT << " Dot file could not be saved" << std::endl;

                return ENOENT;
            }

            std::cout << graph;
        }
        else
        {
            std::cerr << "Error: " << Cli::CLI_OUTPUT << " Log file could not be loaded" << std::endl;

            return ENOENT;
        }
    }

    // No error

    return 0;
}

bool Cli::LoadGraph(Graph &graph, const std::string &path)
{
    std::ifstream log(path);

    if (log.is_open())
    {
        log >> graph;

        log.close();

        return true;
    }

    return false;
}

bool Cli::SaveGraph(const Graph &graph, const std::string &path)
{
    std::ofstream dot(path);

    if (dot.is_open())
    {
        dot << graph;

        std::cout << "Dot file saved to " << path << std::endl;

        dot.close();

        return true;
    }

    return false;
}

std::ostream &operator<<(std::ostream &os, const Cli &cli)
{
    os << "Usage: ./analog [OPTIONS] file.log" << std::endl;

    os << std::endl;

    os << "Options:" << std::endl;

    os << "\t" << Cli::CLI_HELP << "\t\tShow this help message and exit" << std::endl;
    os << "\t" << Cli::CLI_OUTPUT << " FILE\t\tSpecify output file" << std::endl;

    os << "\t" << Cli::CLI_FILTER_HOUR << " HOUR\t\tFilter by hour (e.g., ./analog " << Cli::CLI_FILTER_HOUR << " 12)" << std::endl;
    os << "\t" << Cli::CLI_FILTER_DOMAIN << " DOMAIN\tFilter by domain (e.g., ./analog " << Cli::CLI_FILTER_DOMAIN << " insa-lyon.fr)" << std::endl;
    os << "\t" << Cli::CLI_FILTER_EXTENSION << " EXTENSION\tFilter by extension (e.g., ./analog " << Cli::CLI_FILTER_EXTENSION << ")" << std::endl;

    // Error codes
    os << std::endl;

    os << "Error codes (https://en.cppreference.com/w/cpp/error/error_code):" << std::endl;

    os << "\t" << EINVAL << "\t\tInvalid argument" << std::endl;
    os << "\t" << ENOENT << "\t\tNo such file or directory" << std::endl;

    // Exemples
    os << std::endl;

    os << "Examples:" << std::endl;

    os << "\t./analog ./samples/medium.log" << std::endl;
    os << "\t./analog ./samples/medium.log " << Cli::CLI_FILTER_HOUR << " 12" << std::endl;
    os << "\t./analog ./samples/medium.log " << Cli::CLI_FILTER_DOMAIN << " insa-lyon.fr" << std::endl;
    os << "\t./analog ./samples/medium.log " << Cli::CLI_FILTER_EXTENSION << std::endl;
    os << "\t./analog ./samples/medium.log " << Cli::CLI_FILTER_EXTENSION << " " << Cli::CLI_FILTER_DOMAIN << " insa-lyon.fr" << std::endl;
    os << "\t./analog ./samples/medium.log " << Cli::CLI_FILTER_EXTENSION << " " << Cli::CLI_FILTER_DOMAIN << " insa-lyon.fr " << Cli::CLI_FILTER_HOUR << " 12" << std::endl;

    return os;
}