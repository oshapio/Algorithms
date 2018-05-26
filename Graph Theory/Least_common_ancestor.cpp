#include <iostream>
#include <utility>
#include <cmath>
#include <vector>
#include <cstdio>

using namespace std;
typedef pair<int,int> pii;
int n,k;
struct tree{
   vector<int>adj;
} tr     [100004];
int prc  [100046];
int lca  [100045][18];
int depth[100005];
int T    [100004]; // parent of i-th node

void genLca(){
    for(int e = 0; 1 << e < n; e++){
        for(int i = 0; i <= n; i++){
            lca[i][e]=-1;
        }
    }
    T[1]=1;
    for(int i = 1; i <= n; i++){
        lca[i][0] = T[i];
    }
    //lca[1][0]=0;
    // dp(i,e) = dp(dp(i,e-1),e-1)
    for(int e = 1; 1 << e < n; e++){
        for(int i = 1; i <= n; i++){
            if(lca[i][e-1]!=-1)
                lca[i][e] = lca[lca[i][e-1]][e-1];
        }
    }
}

int findLca(int a, int b){
    if(depth[a] < depth[b])swap(a,b);

    int logVal = log2(depth[a]);

    for(int i = logVal; i >= 0; i--){
        if(depth[a] - (1 << i) >= depth[b]){
            a = lca[a][i];
        }
    }
    if(a == b) return a;
    int backLog = log2(depth[a]);
    for(;backLog >=0; backLog--){
        if(lca[a][backLog] != -1 && lca[a][backLog] != lca[b][backLog]){
            a = lca[a][backLog];
            b = lca[b][backLog];
        }
    }
    return T[a];
}

int dfs(int par, int v, int dpth){ // finds the depth and childs of veretx v
    depth[v] = dpth;
    T[v] = par;
    for(int i = 0; i < tr[v].adj.size(); i++){
        if(tr[v].adj[i] != par){
           // T[tr[v].adj[i]]=par;
            dfs(v, tr[v].adj[i],dpth+1);
        }
    }

}

void sumDfs(int par,int v){
    for(int i = 0; i < tr[v].adj.size(); i++){
        if(par != tr[v].adj[i]){
            sumDfs(v,tr[v].adj[i]);
            prc[v]+=prc[tr[v].adj[i]];
        }
    }
}
int main(){
    freopen("maxflow.in","r",stdin);
    freopen("maxflow.out","w",stdout);
    for(int i =0; i < 100005; i++) prc[i]=0;
    cin >> n >> k;
    for(int i =0 ;i  <n-1; i++){
        //T[i+1]=-1;
        int from,to;
        cin >> from >> to;
        tr[from].adj.push_back(to);
        tr[to].adj.push_back(from);
    }
    dfs(-1,1,0);
    //T[1]=0;
    genLca();

    for(int i = 0; i < k; i++){
        int from,to;
        cin >> from >> to;
        prc[from]++;
        prc[to]++;
        int theirLca = findLca(from,to);
        prc[theirLca]--;
        //if(theirLca != 1)
            prc[T[theirLca]]--;
    }

    sumDfs(-1,1);
    int maxSum = -1;
    for(int i = 0; i <= n; i++){
        maxSum= max(maxSum,prc[i]);
    }
    cout << maxSum;

    return 0;
}
