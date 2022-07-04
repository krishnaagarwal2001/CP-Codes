        ll n,m;
        cin>>n>>m;

        vll g[n+1],rg[n+1];     //rg-->transpose graph

        rep(i,0,m)
        {
            ll u,v;
            cin>>u>>v;

            g[u].pb(v);
            rg[v].pb(u);
        }

        vector<bool>vis(n+1,false);
        vll order;
        vll component[n+1];                     // To store CC

        function<void(ll)> dfs1=[&](ll node)        //For sorting according to out time
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

        function<void(ll,ll)> dfs2=[&](ll node,ll idx)      //To find components
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
        
        ll num=1;
        for(auto u:order)
        {
            if(!vis[u])
            {
                dfs2(u,num);            //new dfs --> new component
                num++;
            }
        }
