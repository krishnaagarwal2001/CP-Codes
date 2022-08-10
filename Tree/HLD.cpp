#include <bits/stdc++.h>
using namespace std;
 
const int N = 2e5+5;
const int D = 19;
const int S = (1<<D);
 
int n, q, v[N];
vector<int> adj[N];
 
int sz[N], p[N][D], dep[N];
int st[S], id[N], tp[N];

// v--> value of node
// sz--> sz of subtree
// p --> LCAs
// dep --> depth
//  st---> segment tree
// id--> element id for segtree
// tp--> top of chain
int readInt () {
        bool minus = false;
        int result = 0;
        char ch;
        ch = getchar();
        while (true) {
            if (ch == '-') break;
            if (ch >= '0' && ch <= '9') break;
            ch = getchar();
        }
        if (ch == '-') minus = true; else result = ch-'0';
        while (true) {
            ch = getchar();
            if (ch < '0' || ch > '9') break;
            result = result*10 + (ch - '0');
        }
        if (minus)
            return -result;
        else
            return result;
    }

void update(int idx, int val, int i=1, int l=1, int r=n) {
    if(l == r) { st[i] = val; return; }
    int m = (l+r)/2;
    if(idx <= m) update(idx, val, i*2, l, m);
    else update(idx,  val, i*2+1, m+1, r);
    st[i] = max(st[i*2], st[i*2+1]);
}
int query(int lo, int hi, int i=1, int l=1, int r=n) {
    if(lo > r || hi < l) return 0;
    if(lo <= l && r <= hi) return st[i];
    int m = (l+r)/2;
    return max(query(lo, hi, i*2, l, m),
            query(lo, hi, i*2+1, m+1, r));
}
 
int dfs_sz(int cur, int par) {
    sz[cur] = 1;
    for(int chi : adj[cur]) {
        if(chi == par) continue;
        dep[chi] = dep[cur] + 1;
        p[chi][0] = cur;
        sz[cur] += dfs_sz(chi, cur);
    }
    return sz[cur];
}
void init_lca() {
    for(int d=1; d<18; d++)
    for(int i=1; i<=n; i++)
        p[i][d] = p[p[i][d-1]][d-1];
}
int ct = 1;
void dfs_hld(int cur, int par, int top) {
    id[cur] = ct++;
    tp[cur] = top;
    update(id[cur], v[cur]);
    int h_chi = -1, h_sz = -1;
    for(int chi : adj[cur]) {
        if(chi == par) continue;
        if(sz[chi] > h_sz) {
            h_sz = sz[chi];
            h_chi = chi;
        }
    }
    if(h_chi == -1) return;
    dfs_hld(h_chi, cur, top);
    for(int chi : adj[cur]) {
        if(chi == par || chi == h_chi) continue;
        dfs_hld(chi, cur, chi);
    }
}
int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for(int d=D-1; d>=0; d--) {
        if(dep[a] - (1<<d) >= dep[b]) {
            a = p[a][d];
        }
    }
    for(int d=D-1; d>=0; d--) {
        if(p[a][d] != p[b][d]) {
            a = p[a][d];
            b = p[b][d];
        }
    }
    if(a != b) {
        a = p[a][0];
        b = p[b][0];
    }
    return a;
}
int path(int chi, int par) {
    int ret = 0;
    while(chi != par) {
        if(tp[chi] == chi) {                //Travelling Light Chain
            ret = max(ret, v[chi]);
            chi = p[chi][0];
        } else if(dep[tp[chi]] > dep[par]) {              //Travelling heavy chain
            ret = max(ret, query(id[tp[chi]], id[chi]));
            chi = p[tp[chi]][0];
        } else {                                           //In same chain
            ret = max(ret, query(id[par]+1, id[chi]));
            break;
        }
    }
    return ret;
}
int main() {
 
    n=readInt();
    q=readInt();
    for(int i=1; i<=n; i++) v[i]=readInt();
    for(int i=2; i<=n; i++) {
        int a, b;
        a=readInt();
        b=readInt();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs_sz(1, 1);
    init_lca();
    memset(st, 0, sizeof st);
    dfs_hld(1, 1, 1);
    while(q--) {
        int t;
        t=readInt();

        if(t == 1) {
            int s, x;
            s=readInt();
            x=readInt();
            v[s] = x;
            update(id[s], v[s]);
        } else {
            int a, b;
            a=readInt();
            b=readInt();
            int c = lca(a, b);
            int res = max(max(path(a,c), path(b,c)), v[c]);
            cout<<res<<" ";
        }
    }
}