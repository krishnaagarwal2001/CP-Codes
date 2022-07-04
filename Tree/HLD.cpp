
vll S(N),par(N),head(N),special(N),st(N),et(N),val(N);
ll timer=0;

ll anc(ll x,ll y)
{
	return arr[x]<=arr[y] and dep[x]>=dep[y];		//check for error
}

void dfs_sz(ll x,ll p)
{
	S[x]=1;
	head[x]=x;
	par[x]=p;

	for(auto y:g[x])
	{
		if(y!=p)
		{
			dfs_sz(y,x);
			s[x]+=s[y];

			if(sz[y]>sz[sc[x]]) sc[x]=y;
		}
	}
}

void dfs_hld(ll x,ll p)
{
	st[x]=++timer;
	ST::A[T]=val[x];

	if(sc[x])
	{
		head[sc[x]]=head[x];
		dfs_hld(sc[x],x);
	}

	for(auto y:g[x])
	{
		if(y!=p and y!=sc[x])
			dfs_hld(y,x);
	}

	en[x]=timer;
}

ll lca(ll x,ll y)
{
	if(anc(x,y)) return x;
	if(anc(y,x)) return y;

	while(!anc(par[head[x]],y)) x=par[head[x]];
	while(!anc(par[head[y]],x)) y=par[head[y]];

	x=par[head[x]];
	y=par[head[y]];

	return anc(x,y)?y:x;
}

ll query_up(ll x,ll p)
{
	ll ans=0;

	while(head[x]!=head[p])
	{
		ans=min(ans,ST::query(st[head[x]]),st[x]);
		x=par[head[x]];
	}

	ans=min(ans,ST::query(st[p],st[x]));
	return ans;

}