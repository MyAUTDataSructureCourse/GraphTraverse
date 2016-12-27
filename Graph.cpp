//
// Created by ahmad on 12/27/16.
//

#include <algorithm>
#include <stack>
#include <queue>
#include "Graph.h"

GraphEdgeConnection::GraphEdgeConnection(char v1, char v2)
{
    vertex1.key = v1;
    vertex2.key = v2;
}

bool GraphEdgeConnection::containVertex(char v)
{
    return (v == vertex1.key) || (v == vertex2.key);
}

GraphVertex::GraphVertex()
{
    isVisited = false;
}

bool Graph::containVertex(char v)
{
    for (int i = 0; i < vertexes.size(); ++i) {
        if(vertexes[i].key == v)
            return true;
    }

    return false;
}

bool Graph::isVisited(char v)
{
    for (int i = 0; i < vertexes.size(); ++i) {
        if(vertexes[i].key == v)
            return vertexes[i].isVisited;
    }

    exit(-1);
}
std::vector<char> Graph::getAllNotVisitedVertexesConnectedTo(char v)
{
    std::vector<char> result;
    for (int i = 0; i < edgeTable.size(); ++i) {
        if(edgeTable[i].containVertex(v))
        {
            char c = (edgeTable[i].vertex1.key == v)? edgeTable[i].vertex2.key : edgeTable[i].vertex1.key;
            if(!isVisited(c))
                result.push_back(c);
        }
    }

    std::sort(result.begin(), result.end());

    return result;
}

void Graph::addEdge(char v1, char v2)
{
    if( !containVertex(v1))
    {
        GraphVertex g1;
        g1.key = v1;
        vertexes.push_back(g1);
    }

    if( !containVertex(v2))
    {
        GraphVertex g2;
        g2.key = v2;
        vertexes.push_back(g2);
    }

    edgeTable.push_back(GraphEdgeConnection(v1, v2));
}

void Graph::visitVertex(char v)
{
    for (int i = 0; i < vertexes.size(); ++i) {
        if(vertexes[i].key == v)
        {
            vertexes[i].isVisited = true;
            return;
        }
    }
}

std::vector<char> Graph::dfs(char startVertex)
{
    std::vector<char> result;

    char currentVertex = startVertex;
    std::stack<char> stck;
    stck.push(currentVertex);
    result.push_back(currentVertex);
    visitVertex(currentVertex);

    while (! stck.empty())
    {
        currentVertex = stck.top();

        std::vector<char> nearestVertexes = getAllNotVisitedVertexesConnectedTo(currentVertex);
        if(nearestVertexes.size() == 0)
        {
            stck.pop();
        }
        else
        {
            currentVertex = nearestVertexes[0];
            stck.push(currentVertex);
            result.push_back(currentVertex);
            visitVertex(currentVertex);
        }
    }

    resetVisited();

    return result;
}

std::vector<char> Graph::bfs(char startVertex)
{
    std::vector<char> result;

    char currentVertex = startVertex;
    std::queue<char> q;

    q.push(currentVertex);
    visitVertex(currentVertex);
    result.push_back(currentVertex);


    while (! q.empty())
    {

        currentVertex = q.front();
        q.pop();
        std::vector<char> nearestVertexes = getAllNotVisitedVertexesConnectedTo(currentVertex);
        for (int i = 0; i < nearestVertexes.size(); ++i) {
            result.push_back(nearestVertexes[i]);
            visitVertex(nearestVertexes[i]);
            q.push(nearestVertexes[i]);
        }
    }

    resetVisited();

    return result;
}

void Graph::resetVisited()
{
    for (int i = 0; i < vertexes.size(); ++i) {
        vertexes[i].isVisited = false;
    }
}