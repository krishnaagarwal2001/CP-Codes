vll g[N];
vector<bool>vis(N,false);
vector<ll>tin,low(N,-1);
ll timer=0;

// tin[v] = Time at which node v is first visited during DFS.
//          (Discovery time / DFS entry time)

// low[v] = The earliest (minimum) discovery time reachable from the
//          subtree rooted at v using:
//          1. Zero or more tree edges, followed by
//          2. At most one back edge.

void dfs(ll v,ll p=-1)
{
	vis[v]=true;
	tin[v]=low[v]=timer++;
	ll children=0;
	for(auto to:g[v])
	{
		if(to==p)continue;

		if(vis[to])
		{
			low[v]=min(low[v],tin[to]);
		}
		else
		{
			dfs(to,v);
			low[v]=min(low[v],low[to]);

			if(low[to]>=tin[v] and p!=-1)
			{
				//(v)...Cutoff point/articulation point
			}

			++children;
		}
	}

	if(p==-1 and children>1)
	{
		//(v)...Cutoff point/articulation point
	}
}

void find_articulation_point()
{
	ll timer=0;

	rep(i,1,n+1)
	{
		if(!vis[i])
			dfs(i);
	}
}
