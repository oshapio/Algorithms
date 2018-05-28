#include <bits/stdc++.h>

#define time das
using namespace std;
const int MAX = 1e5;
vector<int> adj[MAX];
vector<vector<int> > comps;
int n, m, time[MAX], mintime[MAX];
int T = 0;
stack<int> stck;
void dfsTarjan(int v){
    time[v] = T++;
    stck.push(v);
    mintime[v] = time[v];
    for(auto i : adj[v]){
        if(time[i] == -1) dfsTarjan(i);
        mintime[v] = min(mintime[v], mintime[i]);
    }
    vector<int> comp;
    if(mintime[v] == time[v]){
        while(true){
            int curr = stck.top(); stck.pop();
            comp.push_back(curr);
            mintime[curr] = MAX;
            if(curr == v) break;
        }
        comps.push_back(comp);
    }
}
int main(){
    memset(time,    -1, sizeof(time));
    memset(mintime, MAX, sizeof(mintime));
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
    }
    for(int i = 1; i <= n; i++){
        if(time[i] == -1) dfsTarjan(i);
    }
    cout << endl;
    cout << comps.size() << endl;
    for(int i = 0; i < comps.size(); i++){
        cout << "{ ";
        for(int j = 0; j < comps[i].size(); j++){
            cout << comps[i][j] << ", ";
        }
        cout << "}" << endl;
    }
    return 0;
}
