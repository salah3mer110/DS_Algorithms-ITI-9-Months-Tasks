// Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template<class VertexType>
class Graph
{
    int numVertices;               ///Current Number of Vertices
    VertexType vertices[50];  ///Max Number of Vertices is 50
    int edges[50][50];              ///Adjacency Matrix
    bool marks[50];

public:
    explicit Graph() { numVertices = 0; }

    void MakeEmpty() {
        numVertices = 0;
        
        for (auto& m : marks)
            m = false;

        for (auto& edge : edges) {
            for (auto& e : edge) {
                e = 0;
            }
        }
    }
    bool IsEmpty() {
        return numVertices == 0;
    }
    bool IsFull() {
        return numVertices == 50;
    }

    void AddVertex(const VertexType& vertex) {
        if (IsFull()) {
            cout << "Graph is full! Cannot add vertex." << endl;
            return;
        }

        if (GetIndex(vertex) != -1) {
            cout << "Vertex already exists" << endl;
            return;
        }

        vertices[numVertices++] = vertex;
    }
    void AddEdge(VertexType fromVertex, VertexType toVertex, int Weight) {
        int fromIndex = GetIndex(fromVertex);
        int toIndex = GetIndex(toVertex);
        if (fromIndex == -1 || toIndex == -1) {
            cout << "On of the Vertices not found" << endl;
            return;
        }

        edges[fromIndex][toIndex] = Weight;
    
    }
    int GetPathWeight(VertexType fromVertex, VertexType toVertex) {
        int fromIndex = GetIndex(fromVertex);
        int toIndex = GetIndex(toVertex);
        if (fromIndex == -1 || toIndex == -1) {
            cout << "One of the Vertices not found" << endl;
            return 0;
        }
        return edges[fromIndex][toIndex];
    }
    int GetIndex(const VertexType& vertex) {
        for (int i = 0; i < numVertices; i++)
        {
            if (vertices[i] == vertex)
                return i;
        }
        return -1;
    }
    void GetAdjVertices(VertexType vertex, queue<VertexType>& VertexQ) {
        int fromIndex = GetIndex(vertex);
        if (fromIndex == -1) {
            cout << "the Vertice not found" << endl;
            return;
        }
        for (int i = 0; i < numVertices; i++)
        {
            if (edges[fromIndex][i] != 0)
                VertexQ.push(vertices[i]);
        }
    }

    void ClearMarks() {
        for (auto& m : marks) 
            m = false;
    }
    void MarkVertex(VertexType vertex){
        int index = GetIndex(vertex);
        if (index != -1)
            marks[index] = true;
    }
    bool IsMarked(VertexType vertex) {
        int index = GetIndex(vertex);
        if (index == -1)
            return false;
        return marks[index];
    }

    ///Standard Algorithms ( only one from 1 , 2 ) and Implement 3
    ////1.
    void DepthFirstSearch(const VertexType& startVertex, const VertexType& endVertex)  /// Stack , Queue
    {
        queue<VertexType> q;
        stack<VertexType> st;
        bool found = false;

        ClearMarks();

        st.push(startVertex);
        while (!st.empty() && !found) {
        
            VertexType b = st.top();
            st.pop();

            if (b == endVertex) {
                cout << b << " Found" << endl;
                found = true;
                return;
            }
            else {
                if (!IsMarked(b)) {
                    MarkVertex(b);
                    cout << b << " -> ";
                    GetAdjVertices(b, q);
                    while (!q.empty()) {
                        VertexType a = q.front();
                        q.pop();
                        if (!IsMarked(a)) {
                            st.push(a);
                        }
                    }
                }
            }
        }
        if (!found) {
            cout << "Path not found!" << endl;
        }
    }
    ///2.
    void BreadthFirstSearch(const VertexType& startVertex, const VertexType& endVertex) /// 2 Queue
    {
        queue<VertexType> q;
        queue<VertexType> adjQueue;
        bool found = false;

        ClearMarks();

        q.push(startVertex);
        MarkVertex(startVertex);
        while (!q.empty() && !found) {
            VertexType v = q.front();
            q.pop();
            if (v == endVertex) {
                cout << v << " Found" << endl;
                found = true;
                return;
            }
            else {
                    cout << v << " -> ";
                    GetAdjVertices(v, adjQueue);
                    while (!adjQueue.empty()) {
                        VertexType adj = adjQueue.front();
                        adjQueue.pop();
                        if (!IsMarked(adj)) {
                            MarkVertex(adj);
                            q.push(adj);
                        }
                    }
                
            }
        }
        if (!found) {
            cout << "Path not found!" << endl;
        }
    }

    ///3. Print All Shortest Path /// Dijkstra
    void Dijkstra(const VertexType& startVertex) {
        
        int distance[50];
        int INF = 9999999;
        
        for (int i = 0; i < numVertices; i++)
            distance[i] = INF;

        int startIndex = GetIndex(startVertex);
        
        if (startIndex == -1) {
            cout << "Start vertex not found!" << endl;
            return;
        }

        distance[startIndex] = 0;


        for (int count = 0; count < numVertices; count++) {
            int minVertex = -1;
            for (int i = 0; i < numVertices; i++) {
                if (!marks[i] && (minVertex == -1 || distance[i] < distance[minVertex]))
                    minVertex = i;
            }
            if (distance[minVertex] == INF) break;
            marks[minVertex] = true;

            for (int neighbor = 0; neighbor < numVertices; neighbor++) {
                if (edges[minVertex][neighbor] > 0 && distance[minVertex] + edges[minVertex][neighbor] < distance[neighbor]) {
                    distance[neighbor] = distance[minVertex] + edges[minVertex][neighbor];
                }
            }
        }

        cout << "Shortest distances from " << startVertex << ":\n";
        for (int i = 0; i < numVertices; i++) {
            cout << startVertex << " -> " << vertices[i] << " = ";
            if (distance[i] == INF)
                cout << "INF\n";
            else
                cout << distance[i] << "\n";
        }
    }
};



int main()
{
    Graph<string> g;
    g.AddVertex("A");
    g.AddVertex("B");
    g.AddVertex("C");
    g.AddVertex("D");
    g.AddVertex("E");
    g.AddEdge("A", "B", 2);
    g.AddEdge("A", "C", 3);
    g.AddEdge("B", "D", 4);
    g.AddEdge("C", "D", 1);
    g.AddEdge("D", "E", 5);

    g.ClearMarks();
    cout << "DFS from A to E: ";
    g.DepthFirstSearch("A", "E");

    g.ClearMarks();
    cout << "BFS from A to E: ";
    g.BreadthFirstSearch("A", "E");

    g.ClearMarks();
    g.Dijkstra("B");
}
