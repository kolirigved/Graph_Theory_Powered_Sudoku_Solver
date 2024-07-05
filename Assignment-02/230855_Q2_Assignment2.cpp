#include <bits/stdc++.h>
using namespace std;
#define max(a, b) (a < b ? b : a)
#define min(a, b) ((a > b) ? b : a)
#define ll long long
#define mod 1000000007


typedef pair<ll, int> pii;

vector<ll> dijkstra(int n, int source, vector<pair<int, ll> > adj[]) {
    set<pii> st; 

    vector<ll> distance(n, LLONG_MAX); 
    distance[source] = 0; 
    st.insert({0, source});

    while (!st.empty()) {
        auto it = *(st.begin());
        int node = it.second;
        ll dist = it.first;
        st.erase(it);

        for (auto it : adj[node]) {
            int neighbor = it.first;
            ll weight= it.second;

            if (distance[node] + weight < distance[neighbor]) {
                st.erase({distance[neighbor], neighbor});
                distance[neighbor] = distance[node] + weight;
                st.insert({distance[neighbor], neighbor});
            }
        }
    }

    return distance;
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int n,m;
    cin>>n>>m;
    vector<pair <int, ll> > adj[n];

    for (int i = 0; i < m; i++){
        int u,v;
        ll w;
        cin>>u>>v>>w;
        adj[u-1].push_back({v-1,w});
    }

    vector<ll> distance = dijkstra(n, 0, adj);

    for(int i = 0; i < n; i++){
        cout << distance[i] << " ";
    }
    
    return 0;
}
