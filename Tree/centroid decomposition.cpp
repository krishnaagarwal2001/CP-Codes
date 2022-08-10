#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;
const int LOGN=20;

vector<int>g[N];
int sub[N],nn,U[N],V[N],W[N],deleted[N];
int par[N],level[N],dist[LOGN][N];

int adj(int x,int e){
    return U[e]^V[e]^x;
}

void dfs_sz(int u,int p)
{
    sub[u]=1;
    nn++;
    for(auto e:g[u])
    {
        int w=adj(u,e);
        if(w!=p and !deleted[e])
        {
            dfs_sz(w,u);
            sub[u]+=sub[w];
        }
    }
}

int find_centroid(int u,int p)
{
    for(auto e:g[u])
    {
        if(deleted[e]) continue;
        int w=adj(u,e);
        if(w!=p and sub[w]>nn/2)
        {
            return find_centroid(w,u);
        }
    }
    return u;
}

void add_edge_in_centroid_tree(int parent,int child){
    par[child]=parent;
    level[child]=level[parent]+1;
}

void dfs(int u,int p,int lvl)
{
    for(auto e:g[u])
    {
        int w=adj(u,e);
        if(w==p or deleted[e]) continue;
        dist[lvl][w]=dist[lvl][u]+W[e];
        dfs(w,u,lvl);
    }
}

void decompose(int root,int p=-1)
{
    nn=0;
    dfs_sz(root,root);
    int centroid=find_centroid(root,root);

    if(p==-1) p=centroid;

    add_edge_in_centroid_tree(p,centroid);
    dfs(centroid,centroid,level[centroid]);

    for(auto e:g[centroid])
    {
        if(deleted[e])continue;
        deleted[e]=1;
        int w=adj(centroid,e);
        decompose(w,centroid);
    }
}

int lca(int x,int y)
{
    while(x!=y)
    {
        if(level[x]>level[y])
            swap(x,y);
        y=par[y];
    }
    return x;
}

int compute_distance(int x,int y)
{
    int lca_level=level[lca(x,y)];
    return dist[lca_level][x]+dist[lca_level][y];
}
int main()
{
    int n;
    scanf("%d",&n);
    int m;
    scanf("%d",&m);
    for(int i=1;i<n;++i)
    {
        scanf("%d %d",U+i,V+i);
        W[i]=1;
        // U[i]++;                          //to make it 1 based indexing
        // V[i]++;
        g[U[i]].push_back(i);
        g[V[i]].push_back(i);
    }

    decompose(1);

    while(m--)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        printf("%d\n",compute_distance(x,y));
    }
}