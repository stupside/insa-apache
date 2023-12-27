#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <fstream>

#include "GraphFilter.h"

class Node;

/**
 * An object that represents a graph. It contains a dictionary of nodes.
 */
class Graph
{

private:
    /**
     * The nodes of the graph.
     */
    std::map<std::string, Node *> _nodes;

    /**
     * The filter used to filter nodes during the graph creation from a log file.
     */
    const GraphFilter *_filter;

public:
    /**
     * Default constructor.
     *
     * @param filter The filter used to filter nodes during the graph creation from a log file.
     */
    explicit Graph(const GraphFilter *filter = nullptr);

    /**
     * Add a node to the graph.
     *
     * @param source The source of the node.
     * @param destination The destination of the node.
     * @param log The log of the node.
     */
    void RegisterLink(const std::string &source, const std::string &destination);

    /**
     * Get the nodes of the graph.
     *
     * @return The nodes of the graph.
     */
    const std::map<std::string, Node *> &GetNodes() const;

    struct NodeComparator
    {
        bool operator()(const Node *left, const Node *right) const;
    };

    const std::set<Node *, NodeComparator> GetNodesByHits() const;

    /**
     * Get the filter used to filter nodes during the graph creation from a log file.
     *
     * @return The filter used to filter nodes during the graph creation from a log file.
     */
    const GraphFilter &GetFilter() const;

    /**
     * Copy constructor.
     *
     * @param graph The graph to copy.
     */
    Graph(const Graph &) = delete;

    /**
     * Copy assignment operator.
     *
     * @param graph The graph to copy.
     * @return A reference to this object.
     */
    Graph &operator=(const Graph &) = delete;

    /**
     * Display the graph in the output stream by ordering the nodes by their number of visits.
     *
     * @param os The output stream.
     * @param graph The graph to display.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);

    /**
     * Load a graph from a file.
     *
     * @param is The input stream.
     * @param graph The graph to load.
     * @return The input stream.
     */
    friend std::ifstream &operator>>(std::ifstream &is, Graph &graph);

    /**
     * Save a graph to a file.
     *
     * @param os The output stream.
     * @param graph The graph to save.
     * @return The output stream.
     */
    friend std::ofstream &operator<<(std::ofstream &os, const Graph &graph);

    /**
     * Destructor.
     */
    ~Graph();
};

#endif