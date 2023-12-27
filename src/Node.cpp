#include "header/Node.h"

#include "header/NodeLink.h"

#include <iostream>

Node::Node(const std::string &path)
{
    static unsigned int id = 0;

    _id = ++id;

#ifdef MAP
    std::cout << "MAP: Creating a new node: " << _id << std::endl;
#endif

    _path = std::move(path);

    _hits = std::set<const NodeLink *>();
    _links = std::map<std::string, NodeLink *>();
}

void Node::AddLinkTo(Node *destination)
{
#ifdef DEBUG
    std::cout << "DEBUG: Adding link from node " << _id << " to node " << destination->_id << std::endl;
#endif

    NodeLink *link = nullptr;
    const auto &findLink = _links.find(destination->_path);

    if (findLink == _links.end())
    {
        _links[destination->_path] = link = new NodeLink(destination);

#ifdef DEBUG
        std::cout << "DEBUG: Registering a new node link" << std::endl;
#endif
    }
    else
    {
        link = findLink->second;

#ifdef DEBUG
        std::cout << "DEBUG: Reusing node link" << std::endl;
#endif
    }

    link->Hit();
}

unsigned int Node::GetId() const
{
    return _id;
}

unsigned int Node::GetHits() const
{
    unsigned int hits = 0;

    for (const auto *link : _hits)
    {
        hits += link->GetHits();
    }

    return hits;
}

const std::map<std::string, NodeLink *> &Node::GetLinks() const
{
    return _links;
}

Node::~Node()
{
#ifdef MAP
    std::cout << "MAP: Deleting node " << _id << std::endl;
#endif

    _hits.clear();

    for (auto &link : _links)
    {
        delete link.second;
    }

    _links.clear();
}

int operator>=(const Node &lhs, const Node &rhs)
{
    return lhs.GetHits() >= rhs.GetHits();
}

int operator==(const Node &lhs, const Node &rhs)
{
    return lhs._path == rhs._path;
}

std::ostream &operator<<(std::ostream &os, const Node &node)
{
    os << node._path << " (" << node.GetHits() << " hits)" << std::endl;

    return os;
}
