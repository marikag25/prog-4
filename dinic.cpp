#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, flow, rev;
};

void addEdge(vector<vector<Edge>> &adj, int u, int v, int cap) {
    int revA = adj[v].size();
    int revB = adj[u].size();
    adj[u].push_back({v, cap, 0, revA});
    adj[v].push_back({u, 0, 0, revB});
}

bool BFS(const vector<vector<Edge>> &adj, int s, int t, vector<int> &level) {
    for (int i = 0; i < level.size(); i++){
        level[i] = -1;
    }
    level[s] = 0;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &e : adj[u]) {
            if (level[e.to] < 0 && e.flow < e.cap) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }

    return level[t] >= 0;
}

int DFS(vector<vector<Edge>> &adj, vector<int> &level, vector<int> &start, int u, int t, int flow) {
    if (u == t)
        return flow;

    while (start[u] < adj[u].size()) {
        int i = start[u];  
        Edge &e = adj[u][i];

        if (level[e.to] == level[u] + 1 && e.flow < e.cap) {
            int curr_flow = min(flow, e.cap - e.flow);
            int temp_flow = DFS(adj, level, start, e.to, t, curr_flow);

            if (temp_flow > 0) {
                e.flow += temp_flow;
                adj[e.to][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }

        start[u]++; 
    }

    return 0;
}

int DinicMaxFlow(vector<vector<Edge>> &adj, int s, int t) {
    int total = 0;
    vector<int> level(adj.size());
    vector<int> start(adj.size());

    while (BFS(adj, s, t, level)) {
        for (int i = 0; i < start.size(); i++)
            start[i] = 0;

        while (int pushed = DFS(adj, level, start, s, t, INT_MAX))
            total += pushed;
    }

    return total;
}

int main() {
    int n = 6;
    vector<vector<Edge>> adj(n);

    addEdge(adj, 0, 1, 16);
    addEdge(adj, 0, 2, 13);
    addEdge(adj, 1, 2, 10);
    addEdge(adj, 1, 3, 12);
    addEdge(adj, 2, 1, 4);
    addEdge(adj, 2, 4, 14);
    addEdge(adj, 3, 2, 9);
    addEdge(adj, 3, 5, 20);
    addEdge(adj, 4, 3, 7);
    addEdge(adj, 4, 5, 4);

    cout << "Maximum flow: " << DinicMaxFlow(adj, 0, 5) << endl;
    return 0;
}
