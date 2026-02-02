#include <bits/stdc++.h>
using namespace std;

void DijkstraPrimes(int n) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    cout << 2 << " ";
    q.push({4, 2});

    for (int i = 3; i <= n; i++) {
        if (i < q.top().first) {
            cout << i << " ";
            q.push({i * i, i});
        } else {

            while (i == q.top().first) {
                pair<int, int> top = q.top();
                q.pop();
                q.push({top.first + top.second, top.second});
            }
        }
    }
    cout << endl;
}

int main() {
    DijkstraPrimes(50);
    return 0;
}