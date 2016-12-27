//
// Created by ahmad on 12/27/16.
//

#ifndef GRAPHTRAVERSE_GRAPH_H
#define GRAPHTRAVERSE_GRAPH_H

#include <vector>

struct GraphVertex
{
    bool isVisited;
    char key;

    GraphVertex();
};

struct GraphEdgeConnection
{
private:
public:

    GraphVertex vertex1;
    GraphVertex vertex2;

    GraphEdgeConnection(char v1, char v2);

    bool containVertex(char v);
};



class Graph {
private:
    std::vector<GraphEdgeConnection> edgeTable;
    std::vector<GraphVertex> vertexes;

    std::vector<char> getAllNotVisitedVertexesConnectedTo(char v);
    bool containVertex(char v);
    bool isVisited(char v);

    void visitVertex(char v);
    void resetVisited();
public:
    void addEdge(char v1, char v2);

    std::vector<char> dfs(char startVertex);
    std::vector<char> bfs(char startVertex);
};


#endif //GRAPHTRAVERSE_GRAPH_H
