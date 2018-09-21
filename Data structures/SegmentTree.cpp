#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5;
int data[MAXN];
struct segmentTree{
    private: int tree[MAXN * 4];
    private: int saizas = 0;
    public: segmentTree(int _saizas){saizas=_saizas;}
    int build(int l, int r, int x){
        if(l == r){
            tree[x] = data[l];
            return tree[x];
        }
        int mid = (l + r) / 2;
        return tree[x] = build(l, mid, x*2) + build(mid+1, r, x*2+1);
    }
    int query(int queryL, int queryR, int x, int currL, int currR){
        if(queryL > currR || queryR < currL) return 0;
        if(queryL <= currL && queryR >= currR) return tree[x];
        int mid = (currL + currR) / 2;
        return query(queryL, queryR, x * 2, currL, mid) + query(queryL, queryR, x * 2 + 1, mid + 1, currR);
    }
    int query(int queryL, int queryR, int x, int currL, int currR){
        if(queryL > currR || queryR < currL) return 0;
        if(queryL <= currL && queryR >= currR) return tree[x];
        int mid = (currL + currR) / 2;
        return query(queryL, queryR, x * 2, currL, mid) + query(queryL, queryR, x * 2 + 1, mid + 1, currR);
    }
    public: void buildTree(){
        build(0, saizas, 1);
    }
};

int main(){
    for(int i = 1; i < MAXN; i++){
        data[i] = i;
    }
    segmentTree st = segmentTree(MAXN);
    st.buildTree();

    return 0;
}
