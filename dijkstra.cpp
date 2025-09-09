#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int start, vector<vector<pair<int, int>>>& graf)
{
    int n=graf.size();
    vector<int> answer(n, 10000000);
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>> q;
    answer[start]=0;
    q.push({0,start});

    while (!q.empty())
    {
        pair<int, int> nod = q.top();
        q.pop();
        int node = nod.second;

        if (visited[node])
            continue;

        visited[node] = true;

        for (pair<int, int> nextt : graf[node])
        {
            int next = nextt.second;
            int weight = nextt.first;

            if (answer[next] > answer[node] + weight)
            {
                answer[next] = answer[node] + weight;
                q.push({answer[next], next});
            }
        }
    }

    return answer;
}

int main()
{
    int n=0, m=0;
    cin>>n>>m;
    vector<vector<pair<int, int>>> graf(n);
    for (int i=0; i<m; i++)
    {
        int u=0, v=0, weight=0;
        cin>>u>>v>>weight;
        graf[u].push_back({weight,v});
        graf[v].push_back({weight,u});
    }
    vector<int> rez=dijkstra(0, graf);
    for (int i=0; i<n; i++)
    {
        cout<<i<<": "<<rez[i]<<endl;
    }
    return 0;
}