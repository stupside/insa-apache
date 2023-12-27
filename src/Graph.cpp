#include "header/Graph.h"

#include "header/Node.h"

#include "header/GraphIStream.h"
#include "header/GraphOStream.h"

#include <iostream>

const std::map<std::string, Node *> &Graph::GetNodes() const
{
    return _nodes;
}

const std::set<Node *, Graph::NodeComparator> Graph::GetNodesByHits() const
{
    std::set<Node *, NodeComparator> nodes;

    for (const auto &entry : GetNodes())
    {
        nodes.insert(entry.second);
    }

    return nodes;
}

const GraphFilter &Graph::GetFilter() const
{
    return *_filter;
}

void Graph::RegisterLink(const std::string &source, const std::string &destination)
{
#ifdef DEBUG
    std::cout << "DEBUG: Registering link from " << source << " to " << destination << std::endl;
#endif

    Node *nodeSource = nullptr;
    const auto &findNodeSource = _nodes.find(source);

    if (findNodeSource == _nodes.end())
    {
        _nodes[source] = nodeSource = new Node(source);

#ifdef DEBUG
        std::cout << "DEBUG: Registering a new node for source" << std::endl;
#endif
    }
    else
    {
        nodeSource = findNodeSource->second;

#ifdef DEBUG
        std::cout << "DEBUG: Reusing node for source" << std::endl;
#endif
    }

    Node *nodeDestination = nullptr;
    const auto &findNodeDestination = _nodes.find(destination);

    if (findNodeDestination == _nodes.end())
    {
        _nodes[destination] = nodeDestination = new Node(destination);

#ifdef DEBUG
        std::cout << "DEBUG: Registering a new node for destination" << std::endl;
#endif
    }
    else
    {
        nodeDestination = findNodeDestination->second;

#ifdef DEBUG
        std::cout << "DEBUG: Reusing node for destination" << std::endl;
#endif
    }

    nodeSource->AddLinkTo(nodeDestination);
}

Graph::Graph(const GraphFilter *filter)
{

#ifdef MAP
    std::cout << "MAP: Creating a new graph" << std::endl;
#endif

    _nodes = std::map<std::string, Node *>();

    _filter = filter;
}

Graph::~Graph()
{
    for (auto &entry : GetNodes())
    {
        Node *node = entry.second;

#ifdef MAP
        std::cout << "MAP: Deleting node " << node->GetId() << std::endl;
#endif

        delete node;
    }

    _nodes.clear();
}

std::ostream &operator<<(std::ostream &os, const Graph &graph)
{
    GraphOStream gostream(&graph);

    os << gostream;

    return os;
}

std::ifstream &operator>>(std::ifstream &is, Graph &graph)
{
    GraphIStream gistream(&graph);

    while (is >> gistream)
    {
    }

    return is;
}

std::ofstream &operator<<(std::ofstream &os, const Graph &graph)
{
    GraphOStream gostream(&graph);

    os << gostream;

    return os;
}

bool Graph::NodeComparator::operator()(const Node *left, const Node *right) const
{
    return left->GetHits() >= right->GetHits();
}
