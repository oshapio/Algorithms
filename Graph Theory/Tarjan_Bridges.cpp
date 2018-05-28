#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
struct grafas{
    vector<int>kaimynas;
} virsune[100005];

vector<pii> tiltas;
bool visited[100005];
int pradinisLaikas[100005],
    minLaikas[100005];

void dfs(int v, int tevas, int laikas){
    visited[v] = true;
    pradinisLaikas[v] = laikas;
    minLaikas[v]      = laikas;
    for(int i = 0; i < virsune[v].kaimynas.size(); i++){
        int kaimynoVirsune = virsune[v].kaimynas[i];
        if(!visited[kaimynoVirsune]){
            dfs(kaimynoVirsune,v,laikas+1);
            // Ziurim ar si briauna yra tiltas
            minLaikas[v] = min(minLaikas[kaimynoVirsune],minLaikas[v]);
            if(minLaikas[kaimynoVirsune] > pradinisLaikas[v]){
                tiltas.push_back(make_pair(kaimynoVirsune,v));
            }
        }else if(kaimynoVirsune != tevas){
            minLaikas[v] = min(pradinisLaikas[kaimynoVirsune],minLaikas[v]);
        }
    }
}
int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a,b;
        cin >>a>>b;
        a++;
        b++;
        virsune[a].kaimynas.push_back(b);
        virsune[b].kaimynas.push_back(a);
    }

    // nulinimas
    for(int i = 0; i < 100005;i++){
        visited[i] = false;
        pradinisLaikas[i] = 999999999;
        minLaikas[i] = 999999999;
    }
    // nuo pirmos virsunes spaninam medi
    // gali buti kad grafas nera jungus, todel dfsa per visas virsunes
    for(int i = 0; i < n; i++){
        if(!visited[i])
            dfs(1,-1,0);
    }

    for(int i = 0; i < tiltas.size(); i++){
        cout << tiltas[i].first << " " << tiltas[i].second<<endl;
    }
    return 0;
}