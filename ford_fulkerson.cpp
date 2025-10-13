#include <bits/stdc++.h>
using namespace std;

int bfs(int n, int s, int t, vector<vector<int>> &adj, vector<vector<int>> &cap, vector<int> &par) {
    fill(par.begin(), par.end(), -1);
    par[s] = -2;
    queue<pair<int,int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        auto [u, flow] = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (par[v] == -1 && cap[u][v] > 0) {
                par[v] = u;
                int new_flow = min(flow, cap[u][v]);
                if (v == t) return new_flow;
                q.push({v, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int n, int s, int t, vector<vector<int>> &adj, vector<vector<int>> &cap) {
    vector<int> par(n);
    int total = 0, flow;

    while ((flow = bfs(n, s, t, adj, cap, par))) {
        total += flow;
        int v = t;
        while (v != s) {
            int u = par[v];
            cap[u][v] -= flow;
            cap[v][u] += flow;
            v = u;
        }
    }
    return total;
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<int>> adj(n), cap(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] = c;
    }

    cout << maxflow(n, s, t, adj, cap);
    return 0;
}
