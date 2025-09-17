#include <bits/stdc++.h>
using namespace std;

vector<int> bellman_ford(int start, int n, vector<vector<int>> edges) 
{
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    for (int i = 0; i < n; i++) 
    {
        for (auto e : edges) 
        {
            int u = e[0], v = e[1], w = e[2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) 
            {
                if (i == n - 1) 
                {
                    return {-1};
                }
                dist[v] = dist[u] + w;
            }
        }
    }
    return dist;
}

vector<vector<int>> make_graph(int n) 
{
    vector<vector<int>> edges;
    for (int i = 0; i < n - 1; i++) 
    {
        int w = (rand() % 21) - 10;
        if (w == 0) 
        {
            w = 1;
        }
        edges.push_back({i, i + 1, w});
    }
    for (int i = 0; i < 7; i++) 
    {
        int u = rand() % n;
        int v = rand() % n;
        if (u == v) 
        {
            continue;
        }
        int w = (rand() % 21) - 10;
        if (w == 0) 
        {
            w = -5;
        }
        edges.push_back({u, v, w});
    }
    return edges;
}

int main() 
{
    int n = 50;
    srand(time(0));
    ofstream file("output.txt");
    for (int t = 0; t < 10; t++) 
    {
        vector<vector<int>> graph = make_graph(n);
        vector<int> dist = bellman_ford(0, n, graph);
        if (file.is_open()) 
        {
            for (auto e : graph) 
            {
                file << e[0] << " " << e[1] << " " << e[2] << "\n";
            }
            file << "\n";
            if (dist.size() == 1) 
            {
                file << -1;
            }
            else 
            {
                for (int d : dist) 
                {
                    file << d << " ";
                }
            }
            file << "\n\n\n";
        }
    }
    file.close();
    return 0;
}
