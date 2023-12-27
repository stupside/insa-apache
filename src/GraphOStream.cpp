#include "header/GraphOStream.h"

#include "header/Node.h"
#include "header/Graph.h"
#include "header/NodeLink.h"

#define SHOW_TOP_NODES 10

GraphOStream::GraphOStream(const Graph *graph)
{
#ifdef MAP
    std::cout << "MAP: Creating a new graph ostream" << std::endl;
#endif
    _graph = graph;
}

GraphOStream::~GraphOStream()
{
#ifdef MAP
    std::cout << "MAP: Deleting a graph ostream" << std::endl;
#endif
}

std::ostream &operator<<(std::ostream &os, const GraphOStream &stream)
{
    unsigned int shown = 0;

    os << "Top " << SHOW_TOP_NODES << " out of " << stream._graph->GetNodes().size() << " visited nodes:" << std::endl;

    for (const auto *node : stream._graph->GetNodesByHits())
    {
        if (shown++ == SHOW_TOP_NODES)
        {
            break;
        }

        os << ' ' << shown << " - " << *node;
    }

    return os;
}

std::ofstream &operator<<(std::ofstream &os, const GraphOStream &stream)
{
    os << "digraph {" << std::endl;

    for (const auto &entry : stream._graph->GetNodes())
    {
        const Node *node = entry.second;

        os << "node" << node->GetId() << " [label=\"" << entry.first << "\"];" << std::endl;

        for (const auto &link : node->GetLinks())
        {
            os << "node" << node->GetId() << " -> node" << link.second->GetNode()->GetId() << " [label=\"" << link.second->GetHits() << "\"];" << std::endl;
        }
    }

    os << "}" << std::endl;

    return os;
}
