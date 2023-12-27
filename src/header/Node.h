#ifndef NODE_H
#define NODE_H

#include <map>
#include <set>
#include <string>

class NodeLink;

/**
 * An object that represents a node. A node is a path in the graph.
 */
class Node
{
private:
    /**
     * The node id. This value is unique for each node and only used convert graph to dot format.
     */
    unsigned int _id;

    /**
     * The node path. This value is unique for each node and used to compare nodes.
     */
    std::string _path;

    /**
     * The number of visites for this node.
     */
    std::set<const NodeLink *> _hits;

    /**
     * The links that are connected to this node. The key is the destination node path.
     */
    std::map<std::string, NodeLink *> _links;

public:
    friend class NodeLink;

    /**
     * Creates a new node.
     * @param path The node path.
     */
    explicit Node(const std::string &);

    /**
     * Adds a log to the node.
     */
    void AddLinkTo(Node *destination);

    /**
     * Get the id of the node. This value is unique for each node and only used convert graph to dot format.
     * @return The id of the node.
     */
    unsigned int GetId() const;

    /**
     * Get the number of visites for this node.
     * @return The number of visites for this node.
     */
    unsigned int GetHits() const;

    /**
     * Get the links that are connected to this node. The key is the destination node path.
     * @return The links that are connected to this node.
     */
    const std::map<std::string, NodeLink *> &GetLinks() const;

    /**
     * Copies a node.
     * @param other The node to copy.
     * @return The copied node.
     */
    Node &operator=(const Node &) = delete;

    /**
     * Destroys the node.
     */
    ~Node();

    /**
     * Compares two nodes. A node is greater than or equal to another node if it has been more visited than or equal to the other node.
     * @param lhs The left hand side node.
     * @param rhs The right hand side node.
     * @return True if the left hand side node is greater than or equal to the right hand side node, false otherwise.
     */
    friend int operator>=(const Node &lhs, const Node &rhs);

    /**
     * Compares two nodes. Two nodes are equal if they have the same path.
     * @param lhs The left hand side node.
     * @param rhs The right hand side node.
     * @return True if the left hand side node is equal to the right hand side node, false otherwise.
     */
    friend int operator==(const Node &lhs, const Node &rhs);

    /**
     * Writes a node to the output stream but not in the dot format. Only used to print a node to the console.
     * @param os The output stream.
     * @param node The node.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Node &node);
};

#endif // NODE_H