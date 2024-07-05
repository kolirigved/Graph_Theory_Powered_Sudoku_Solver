#include <bits/stdc++.h>
using namespace std;
#define max(a, b) (a < b ? b : a)
#define min(a, b) ((a > b) ? b : a)
#define ll long long


vector <int> dijkstra(int n, int source, vector<pair<int, int>> adj[]) {
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> distance(n, INT_MAX);
    distance[source] = 0;
    pq.push({0, source});
    while(!pq.empty()){
        int node = pq.top().second;
        int dist = pq.top().first;
        pq.pop();
        for(auto it: adj[node]){
            if(dist + it.second < distance[it.first]){
                distance[it.first] = dist + it.second;
                pq.push({distance[it.first], it.first});
            }
        }
    }
    return distance;
}


int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int n = 6;
    vector<pair<int, int>> adj[n];

    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});
    
    adj[0].push_back({4, 1});
    adj[4].push_back({0, 1});
    
    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});
    
    adj[2].push_back({3, 6});
    adj[3].push_back({2, 6});
    
    adj[4].push_back({5, 2});
    adj[5].push_back({4, 2});

    adj[5].push_back({3, 1});
    adj[3].push_back({5, 1});

    vector<int> distance = dijkstra(n, 0, adj);

    for(int i = 0; i < n; i++){
        cout << distance[i] << " ";
    }
    
    return 0;
}
