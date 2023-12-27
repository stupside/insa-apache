#ifndef CLI_H
#define CLI_H

class Graph;
class GraphFilter;

#include <string>

#include <iostream>

/**
 * Command line interface.
 */
class Cli
{
private:
    static bool LoadGraph(Graph &graph, const std::string &path);
    static bool SaveGraph(const Graph &graph, const std::string &path);

    Cli();

public:
    /**
     * Argument to display help.
     */
    static const std::string CLI_HELP;

    /**
     * Argument to specify output file and generate graph.
     */
    static const std::string CLI_OUTPUT;

    /**
     * Argument to specify a filter by hour.
     */
    static const std::string CLI_FILTER_HOUR;

    /**
     * Argument to specify a filter by domain.
     */
    static const std::string CLI_FILTER_DOMAIN;

    /**
     * Argument to specify a filter by extension.
     */
    static const std::string CLI_FILTER_EXTENSION;

    static unsigned int ProcessArguments(int argc, const char **args);

    /**
     * Help message.
     */
    friend std::ostream &operator<<(std::ostream &os, const Cli &cli);
};

#endif // CLI_H