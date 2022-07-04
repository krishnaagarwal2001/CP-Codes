// Original Tree

vector<ll>g[N];
ll sub[N],nn,U[N],V[N],W[N],deleted[N];

// Centroid Tree
ll par[N],level[N],dist[20][N];
//dist[LOGN][N]: dist[lvl][x]: distance between (Centroid at level lvl) and (x) in original tree
ll adj(ll x,ll e) { return U[e]^V[e]^x;}	//adjacent vertex of x on edge e

void dfs_sz(ll u,ll p)
{
	sub[u]=1;
	nn++;

	for(auto e:g[u])
	{
		ll w=adj(u,e);
		if(w!=p and !deleted[e])
		{
			dfs_sz(w,u);
			sub[u]+=sub[w];
		}
	}
}

ll find_centroid(ll u,ll p)
{
	for(auto e:g[u])
	{
		if(deleted[e]) continue;

		ll w=adj(u,e);
		if(w!=p and sub[w]>nn/2)
			return find_centroid(w,u);
	}

	return u;
}

void add_edge_in_centroid_tree(ll p,ll c)
{
	par[c]=p;
	level[c]=level[p]+1;
}

void dfs(ll u,ll p,ll lvl)
{
	for(auto e:g[u])
	{
		ll w=adj(u,e);
		if(w==p or deleted[e]) continue;

		dist[lvl][w]=dist[lvl][u]+W[e];
		dfs(w,u,lvl);
	}
}

void decompose(ll root,ll p=-1)
{
	nn=0;

	//Compute subtree sizes and no of node nn in this tree
	dfs_sz(root,root);

	//find centroid of tree and make it the new root
	ll centroid=find_centroid(root,root);
	if(p==-1) p=centroid;
	add_edge_in_centroid_tree(p,centroid);

	//process the O(N) paths from centroid to all leaves in this component
	dfs(centroid,centroid,level[centroid]);

	//delete the adjacent edges of the centroid
	//recursively decompose the subtrees
	for(auto e:g[centroid])
	{
		if(deleted[e])
			continue;

		deleted[e]=1;
		ll w=adj(centroid,e);
		decompose(w,centroid);
	}

}

ll lca_level(ll x,ll y)
{	
	//O(logN)
	while(x!=y)
	{
		if(level[x]>level[y]) swap(x,y);
		y=par[y];
	}

	return x;
}

//MAIN FUNCTION

ll compute_distance(ll x,ll y)
{
	ll lca_lvl=level[lca_level(x,y)];

	return dist[lca_lvl][x]+dist[lca_lvl][y];
}

int main()
{
	ll n;
	cin>>n;

	rep(i,1,n)
	{
		cin>>U[i]>>V[i]>>W[i];
		g[U[i]].pb(i);
		g[V[i]].pb(i);
	}

	decompose(1);

	ll q;
	cin>>q;

	while(q--)
	{
		ll x,y;
		cin>>x>>y;

		cout<<compute_distance(x,y);
	}
}

