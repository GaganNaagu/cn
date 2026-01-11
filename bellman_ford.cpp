#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge
{
    int s, d, w;
};

void bellmanFord(int v, int e, vector<Edge> &edges, int source)
{
    vector<int> distance(v, INT_MAX);
    distance[source] = 0;

    for (int i = 1; i <= v - 1; i++)
    {
        for (int j = 0; j < e; j++)
        {
            int u = edges[j].s;
            int vtx = edges[j].d;
            int w = edges[j].w;

            if (distance[u] != INT_MAX && distance[u] + w < distance[vtx])
            {
                distance[vtx] = distance[u] + w;
            }
        }
    }

    for (int j = 0; j < e; j++)
    {
        int u = edges[j].s;
        int vtx = edges[j].d;
        int w = edges[j].w;

        if (distance[u] != INT_MAX && distance[u] + w < distance[vtx])
        {
            cout << "Graph has a negative weight cycle!" << endl;
            return;
        }
    }

    cout << "\nVertex\tDistance from Source (" << source << ")\n";
    for (int i = 0; i < v; i++)
    {
        if (distance[i] == INT_MAX)
            cout << i << "\tINF\n";
        else
            cout << i << "\t" << distance[i] << "\n";
    }
}

int main()
{
    int v, e, source;

    cout << "Enter no of vertices: ";
    cin >> v;

    cout << "Enter no of edges: ";
    cin >> e;

    vector<Edge> edges(e);

    cout << "Enter edges in the format (source destination weight):\n";
    for (int i = 0; i < e; i++)
    {
        cin >> edges[i].s >> edges[i].d >> edges[i].w;
    }

    cout << "Enter source vertex: ";
    cin >> source;

    bellmanFord(v, e, edges, source);

    return 0;
}