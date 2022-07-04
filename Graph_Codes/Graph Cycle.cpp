

vector<ll>vis(n+1,0);
        vll p(n+1,-1);

        function<void(int)> dfs=[&](ll st){
            vis[st]=1;
            // s.push(st);
            for(auto it:g[st])
            {
                if(!vis[it])
                {   
                    p[it]=st;
                    dfs(it);
                }
                else if(vis[it]==1)
                {   
                    vll cycle;
                    ll cur=st;
                    cycle.pb(cur);
                    while(p[cur]!=it)
                    {
                        cycle.pb(p[cur]);
                        cur=p[cur];
                    }
                    cycle.pb(it);
                    cycle.pb(st);
                    reverse(all(cycle));
                    cout<<sz(cycle)<<endl;
                    for(auto y:cycle)
                        cout<<y<<" ";
     
                    exit(0);
                }
            }
            vis[st]=2;
            
        };


bool detect_cycle(ll n)
{
	vis.assign(n + 1, 0);

	bool cycle_found = 0;

	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			cycle_found |= dfs(i, -1);

	return cycle_found;
}

vi par;
ll cyc_end, cyc_st;

bool dfs1(ll i)
{
	vis[i] = 1;
	for (auto nb : adj[i])
	{
		if (nb == par[i])
			continue;

		if (!vis[nb])
		{
			par[nb] = i;
			bool cf = dfs1(nb);

			if (cf)
				return true;
		}

		else
		{
			cyc_end = i;
			cyc_st = nb;
			return true;
		}
	}

	return false;
}

vector<ll> get_cycle(ll n)
{
	par.assign(n + 1, -1);
	vis.assign(n + 1, false);

	for (int i = 1; i <= n; ++i){
	if (vis[i] == 0)
	{
		if (dfs1(i)){
		//return the cycle
		vector<ll> v;

		while (cyc_end != cyc_st)
		v.pb(cyc_end), cyc_end = par[cyc_end];

		v.pb(cyc_st);

		return v;
		}
	}
	}

	return {};
}