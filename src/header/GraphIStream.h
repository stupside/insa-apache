#ifndef GRAPHISTREAM_H
#define GRAPHISTREAM_H

#include <fstream>

class Graph;

/**
 * An object that represents a graph input stream. This class is used to read a graph from a file.
 */
class GraphIStream
{
private:
    /**
     * A pointer to the graph that should be filled from the input stream.
     */
    Graph *_graph;

public:
    /**
     * Creates a new graph input stream.
     * @param graph A pointer to the graph that should be filled from the input stream.
     */
    explicit GraphIStream(Graph *graph);

    /**
     * Creates a new graph input stream.
     * @param other The graph input stream to copy.
     */
    GraphIStream(const GraphIStream &other) = delete;

    /**
     * Copies a graph input stream.
     * @param other The graph input stream to copy.
     * @return The copied graph input stream.
     */
    GraphIStream &operator=(const GraphIStream &other) = delete;

    /**
     * Destroys the graph input stream.
     */
    ~GraphIStream();

    /**
     * Reads a graph from the input stream. The graph should be in the dot format.
     * @param is The input stream.
     * @param stream The graph input stream.
     * @return The input stream.
     * @see https://en.wikipedia.org/wiki/DOT_(graph_description_language)
     */
    friend std::ifstream &operator>>(std::ifstream &is, const GraphIStream &stream);
};

#endif // GRAPHISTREAM_H