#include <bits/stdc++.h>
using namespace std;

void floyd_warshall(int n, vector<vector<int>>& mat, int inf)
{
    for(int k=0; k<n; k++)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(mat[i][k] < inf && mat[k][j] < inf)
                {
                    mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
                }
            }
        }

        cout << "\n";
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                cout << mat[i][j] << ' ';
            }
            cout << '\n';
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    const int INF = 1e9;
    vector<vector<int>> mat(n, vector<int>(n, INF));
    for(int i=0; i<n; i++) mat[i][i] = 0;

    for(int i=0; i<m; i++)
    {
        int a, b, weight;
        cin >> a >> b >> weight;
        mat[a][b] = weight;
    }

    floyd_warshall(n, mat, INF);

    vector<vector<int>> d = mat;
    cout << "Vtor pat za da vidime dali ima negativen ciklus:\n";

    floyd_warshall(n, mat, INF);

    if(mat != d)
    {
        cout << "Ima negativen ciklus\n";
    }

    return 0;
}
