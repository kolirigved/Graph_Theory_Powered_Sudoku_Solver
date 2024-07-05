#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mod 1000000007

vector<int> dijkstra(int n, int m, int source, const vector<pair<pair<int, int>, int>>& v) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> distance(n, INT_MAX);
    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int node = pq.top().second;
        int dist = pq.top().first;
        pq.pop();

        for (int i = 0; i < m; i++) {
            int resultant = (node & (~v[i].first.first)) | v[i].first.second;
            if (dist + v[i].second < distance[resultant]) {
                distance[resultant] = dist + v[i].second;
                pq.push({distance[resultant], resultant});
            }
        }
    }

    return distance;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    ll test;
    cin >> test;
    while (test--) {
        int n, m;
        cin >> n >> m;

        bitset<10> inp;
        cin >> inp; // symptoms
        int sym = (int)inp.to_ulong();
        int N = 1 << n;

        vector<pair<pair<int, int>, int>> v(m);
        for (int i = 0; i < m; i++) {
            cin >> v[i].second; // days
            cin >> inp; // medicine
            v[i].first.first = (int)inp.to_ulong();
            cin >> inp; // side effect
            v[i].first.second = (int)inp.to_ulong();
        }

        vector<int> dist = dijkstra(N, m, sym, v);

        if (dist[0] == INT_MAX) dist[0] = -1;
        cout << dist[0] << endl;
    }

    return 0;
}
