#include "header/GraphIStream.h"

#include "header/Node.h"
#include "header/Graph.h"
#include "header/NodeLink.h"

#include <sstream>
#include <iostream>

static const std::string IGNORED[] = {";", "?", "#", "&"};

static void ParseLog(const std::string &line, std::string &outDate, std::string &outDestination, std::string &outSource)
{
    std::istringstream log(line);

    std::string ignore;

    log >> ignore >> ignore >> ignore >> outDate >> ignore >> ignore >> outDestination >> ignore >> ignore >> ignore >> outSource;

#ifdef DEBUG
    std::cout << "DEBUG: ParseLog: " << outDate << " " << outDestination << " " << outSource << std::endl;
#endif
}

static void ParseDate(const std::string &date, unsigned int &outHour)
{
    std::istringstream iss(date);

    std::string day, hour;

    std::getline(iss, day, ':');
    std::getline(iss, hour, ':');

    outHour = std::stoi(hour);

#ifdef DEBUG
    std::cout << "DEBUG: ParseDate: " << outHour << std::endl;
#endif
}

static void ParseUrl(std::string &source, std::string &outDomain, std::string &outPath)
{
    if (source.size() > 0 && source[0] == '"')
    {
        source = source.substr(1, source.size() - 2);
    }

    if (source.size() > 0 && source[source.size() - 1] == '"')
    {
        source = source.substr(0, source.size() - 1);
    }

    if (source == "-")
    {
        outPath = source;
        outDomain = source;
    }
    else
    {
        std::size_t begin = source.find("://");

        begin = (begin == std::string::npos) ? 0 : begin + 3;

        std::size_t end = source.find('/', begin);

        if (begin == std::string::npos || end == std::string::npos)
        {
        }
        else
        {
            outDomain = source.substr(begin, end - begin);
        }

        if (end == std::string::npos)
        {
        }
        else
        {
            outPath = source.substr(end);
        }

        for (const std::string &ignore : IGNORED)
        {
            std::size_t position = outPath.find(ignore);

            if (position != std::string::npos)
            {
                outPath = outPath.substr(0, position);
            }
        }
    }

#ifdef DEBUG
    std::cout << "DEBUG: ParseUrl: " << source << " " << outDomain << " " << outPath << std::endl;
#endif
}

GraphIStream::GraphIStream(Graph *graph)
{
#ifdef MAP
    std::cout << "MAP: Creating a new graph input stream" << std::endl;
#endif
    _graph = graph;
}

GraphIStream::~GraphIStream()
{
#ifdef MAP
    std::cout << "MAP: Deleting a graph input stream" << std::endl;
#endif
}

std::ifstream &operator>>(std::ifstream &is, const GraphIStream &stream)
{
    std::string line;

    std::getline(is, line);

    if (line.empty())
    {
#ifdef DEBUG
        std::cout << "DEBUG: Empty line, ignoring" << std::endl;
#endif
        return is;
    }

    std::string date, destination, source;

    ParseLog(line, date, destination, source);

    unsigned int hour;

    ParseDate(date, hour);

    if (stream._graph->GetFilter().ShouldIgnoreHour(hour))
    {
        return is;
    }

    std::string sourceDomain, sourcePath;
    ParseUrl(source, sourceDomain, sourcePath);

    std::string destinationDomain, destinationPath;
    ParseUrl(destination, destinationDomain, destinationPath);

    if (destinationDomain.empty())
    {
        destinationDomain = sourceDomain;
#ifdef DEBUG
        std::cout << "DEBUG: Empty destination domain, using source domain" << std::endl;
#endif
    }

    if (stream._graph->GetFilter().ShouldIgnoreDomain(sourceDomain) || stream._graph->GetFilter().ShouldIgnoreDomain(destinationDomain))
    {
        return is;
    }

    if (stream._graph->GetFilter().ShouldIgnoreExtension(destinationPath))
    {
        return is;
    }

    stream._graph->RegisterLink(sourcePath, destinationPath);

    return is;
}
