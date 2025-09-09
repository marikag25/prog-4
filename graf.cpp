#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n=0, m=0;
    cin>>n>>m;
    char k='\0';
    cin>>k;
    
    vector<vector<int>> lista (n, vector<int>());
    int mat[n][n];
    
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            mat[i][j]=0;
        }
    }
    
    for (int i=0; i<m; i++)
    {
        int prv=0, vtor=0;
        cin>>prv>>vtor;
        
        if (k=='o')
        {
            lista[prv].push_back(vtor);   
            mat[prv][vtor]=1;
        }
        
        else if (k=='n')
        {
            lista[prv].push_back(vtor);
            lista[vtor].push_back(prv);   
            mat[prv][vtor]=1;
            mat[vtor][prv]=1;   
        }
        
    }
    
    
    for (int i=0; i<n; i++)
    {
        cout<<i<<": ";
        for (int j=0; j<lista[i].size(); j++)
        {
            cout<<lista[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
    
    return 0;
}