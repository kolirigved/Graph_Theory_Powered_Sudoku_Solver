#include <bits/stdc++.h>
using namespace std;

void ConstructAdjacency(vector <int> adj[]) {
    adj[0]={1,2};
    adj[1]={0,3,4};
    adj[2]={0,5,6,10};
    adj[3]={1,7,8};
    adj[4]={1,9};
    adj[5]={2,10};
    adj[6]={2,11,12};
    adj[7]={3};
    adj[8]={3};
    adj[9]={4,13,14};
    adj[10]={2,5};
    adj[11]={6};
    adj[12]={6};
    adj[13]={9};
    adj[14]={9};
    return;
}

void dfs(int node, vector <int> adj[], vector <bool> &visited) {
    visited[node] = true;
    cout << node << " ";
    for(auto it: adj[node])
        if(!visited[it])
            dfs(it, adj, visited);
    return;
}

int main() {
    int n = 15; // number of vertices
    vector <int> adj[n];
    ConstructAdjacency(adj);
    vector <bool> visited(n, false);

    // Roll Number 230855
    dfs(5, adj, visited);

    return 0;
}
