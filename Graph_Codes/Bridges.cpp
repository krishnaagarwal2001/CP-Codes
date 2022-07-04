vll g[N];
vector<bool>vis(N,false);
vector<ll>tin(N,-1),low(N,-1);
ll timer=0;

void dfs(ll v,ll p=-1)
{
	vis[v]=true;
	tin[v]=low[v]=timer++;

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

			if(low[to]>tin[v])
			{
				//(v-->to)...Bridge
			}
		}
	}
}

void find_bridges()
{
	ll timer=0;

	rep(i,1,n+1)
	{
		if(!vis[i])
			dfs(i);
	}
}