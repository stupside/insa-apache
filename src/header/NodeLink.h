#ifndef NODELINK_H
#define NODELINK_H

class Node;

/**
 * An object that represents a node link. A node link is a connection between two nodes.
 */
class NodeLink
{
private:
    /**
     * The node that is connected to this link.
     */
    const Node *_node;

    /**
     * How many times this link has been hit.
     */
    unsigned int _hits;

public:
    /**
     * Creates a new node link for the given node.
     * @param node The node that is connected to this link.
     */
    explicit NodeLink(Node *node);

    /**
     * Creates a new node link for the given node.
     * @param other The node link to copy.
     */
    const Node *GetNode() const;

    /**
     * Adds a log to the node link.
     */
    void Hit();

    /**
     * Get the number of visites for this node link.
     * @return The number of visites for this node link.
     */
    unsigned int GetHits() const;

    /**
     * Creates a new node link for the given node.
     * @param other The node link to copy.
     */
    NodeLink(const NodeLink &other) = delete;

    /**
     * Copies a node link.
     * @param other The node link to copy.
     * @return The copied node link.
     */
    NodeLink &operator=(const NodeLink &other) = delete;

    /**
     * Destroys the node link.
     */
    ~NodeLink();
};

#endif // NODELINK_H