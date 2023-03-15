#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int best_size = 1;
    for (int i = 0; i < n; i++) {
        vector<bool> used(n, false);
        used[i] = true;
        for (int j : adj[i]) {
            used[j] = true;
        }
        int size = 1;
        for (int j = i+1; j < n; j++) {
            if (!used[j]) {
                bool is_clique = true;
                for (int k : adj[j]) {
                    if (!used[k]) {
                        is_clique = false;
                        break;
                    }
                }
                if (is_clique) {
                    size++;
                    used[j] = true;
                }
            }
        }
        best_size = max(best_size, size);
    }
    cout << best_size << endl;
    return 0;
}
