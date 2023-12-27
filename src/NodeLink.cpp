#include "header/NodeLink.h"

#include "header/Node.h"

#ifdef DEBUG
#include <iostream>
#endif

NodeLink::NodeLink(Node *node) : _node(node), _hits(0)
{
#ifdef MAP
    std::cout << "MAP: Creating a new node link going to node: " << node->GetId() << std::endl;
#endif

    node->_hits.insert(this);
}

const Node *NodeLink::GetNode() const
{
    return _node;
}

void NodeLink::Hit()
{
    _hits++;

#ifdef DEBUG
    std::cout << "DEBUG: Hit for node link going to node: " << _node->GetId() << std::endl;
#endif
}

unsigned int NodeLink::GetHits() const
{
    return _hits;
}

NodeLink::~NodeLink()
{
#ifdef MAP
    std::cout << "MAP: Deleting a node link going to node: " << _node->GetId() << std::endl;
#endif
}
