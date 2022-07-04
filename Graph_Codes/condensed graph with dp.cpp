        //Coin collector cses

        ll n,m;
        cin>>n>>m;

        vll coins(n+1);

        rep(i,1,n+1)
        {
            cin>>coins[i];
        }
        vll g[n+1],rg[n+1];

        rep(i,0,m)
        {
            ll u,v;
            cin>>u>>v;

            g[u].pb(v);
            rg[v].pb(u);
        }

        vector<bool>vis(n+1,false);
        vll order;
        vll component[n+1];

        function<void(ll)> dfs1=[&](ll node)
        {
            vis[node]=true;

            for(auto it:g[node])
            {
                if(!vis[it])
                {
                    dfs1(it);
                }
            }
            order.pb(node);
        };

        function<void(ll,ll)> dfs2=[&](ll node,ll idx)
        {
            vis[node]=true;
            component[idx].pb(node);

            for(auto it:rg[node])
            {
                if(!vis[it])
                {
                    dfs2(it,idx);
                }
            }
        };

        rep(i,1,n+1)
        {
            if(!vis[i])
                dfs1(i);
        }

        vis.assign(n+1,false);
        reverse(all(order));
        
        vll root(n+1,0);
        vll condensed_graph[n+1];
        vll root_nodes;

        ll num=1;
        for(auto u:order)
        {
            if(!vis[u])
            {
                dfs2(u,num);

                for(auto it:component[num])
                {
                    root[it]=u;
                    if(it!=u)
                    coins[u]+=coins[it];
                }

                root_nodes.pb(u);
                num++;
            }
        }

        rep(i,1,n+1)
        {
            for(auto u:g[i])
            {
                if(root[i]!=root[u])
                {
                    condensed_graph[root[i]].pb(root[u]);
                }
            }
        }

        vll dp(n+1,-1);

        function<ll(ll)> fn=[&](ll node){

            if(dp[node]!=-1)
            {
                return dp[node];
            }

            ll ans=0;

            for(auto it:condensed_graph[node])
            {
                ans=max(ans,fn(it));
            }

            ans+=coins[node];
            return dp[node]=ans;
        };

        ll ans=0;

        for(auto it:root_nodes)
        {   
            if(dp[it]==-1)
            {   
                ans=max(ans,fn(it));
            }
        }

        cout<<ans;