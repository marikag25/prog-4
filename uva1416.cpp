#include <bits/stdc++.h>
using namespace std;


int bfs(int n, int s, int t, vector<vector<int>> &graph, vector<vector<int>> &capacity, vector<int> &parent)
{
    parent.clear();
    for(int i=0;i<n;i++)
    {
        parent.push_back(-1);
    }

    parent[s] = -2;

    queue<pair<int,int>> q;
    q.push({s,INT_MAX});

    while(!q.empty())
    {
        auto h = q.front();
        q.pop();

        int node = h.first;
        int flow = h.second;

        for(auto next:graph[node])
        {
            if(parent[next]==-1 and capacity[node][next])
            {
                parent[next] = node;
                int newf = min(flow, capacity[node][next]);

                if(next == t)
                return newf;

                q.push({next,newf});
            }
        }


    }

    return 0;
}


int ford_fulkerson(int n, int s, int t, vector<vector<int>> & graph, vector<vector<int>> &capacity)
{
    int flow=0;
    int newf=0;
    vector<int> parent;
    while(newf = bfs(n,s,t,graph,capacity,parent))
    {
        int now = t;
        flow += newf;
        while(now!=s)
        {
           
            int before = parent[now];
            capacity[before][now] -= newf;
            capacity[now][before] += newf;
            now = before;
        }
    }

    return flow;
}



int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<int>> graph(n), capacity(n, vector<int>(n, 0));
    vector<array<int, 3>> edges;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back(b);
        graph[b].push_back(a);
        capacity[a][b] = w;
        edges.push_back({a, b, w});
    }

    int min_flow = INT_MAX;
    pair<int, int> removed_edge;

    for (auto [a, b, w] : edges) {
        auto temp_cap = capacity;
        temp_cap[a][b] = 0;

        int flow = ford_fulkerson(n, s, t, graph, temp_cap);
        if (flow < min_flow) {
            min_flow = flow;
            removed_edge = {a, b};
        }
    }

    cout << min_flow << "\n" << removed_edge.first << ' ' << removed_edge.second;
    return 0;
}
