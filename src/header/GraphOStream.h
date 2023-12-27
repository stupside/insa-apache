#ifndef GRAPHOSTREAM_H
#define GRAPHOSTREAM_H

#include <string>
#include <fstream>

class Graph;

/**
 * An object that represents a graph output stream. This class is used to write a graph to a file.
 */
class GraphOStream
{
private:
    /**
     * A pointer to the graph that should be written to the output stream in the dot format.
     */
    const Graph *_graph;

public:
    /**
     * Creates a new graph output stream.
     * @param graph A pointer to the graph that should be written to the output stream in the dot format.
     */
    explicit GraphOStream(const Graph *graph);

    /**
     * Creates a new graph output stream.
     * @param other The graph output stream to copy.
     */
    GraphOStream(const GraphOStream &other) = delete;

    /**
     * Copies a graph output stream.
     * @param other The graph output stream to copy.
     * @return The copied graph output stream.
     */
    GraphOStream &operator=(const GraphOStream &other) = delete;

    /**
     * Destroys the graph output stream.
     */
    ~GraphOStream();

    friend std::ostream &operator<<(std::ostream &os, const GraphOStream &stream);

    /**
     * Writes a graph to the output stream in the dot format.
     * @param os The output stream.
     * @param stream The graph output stream.
     * @return The output stream.
     * @see https://en.wikipedia.org/wiki/DOT_(graph_description_language)
     */
    friend std::ofstream &operator<<(std::ofstream &os, const GraphOStream &stream);
};

#endif // GRAPHOSTREAM_H
