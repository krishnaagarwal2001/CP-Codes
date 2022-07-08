        //Giant Pizza CSES

        ll n,m;
        cin>>n>>m;

        vll g[2*m+1],rg[2*m+1];

        rep(i,0,n)
        {
            char c,d;
            ll u,v;
            cin>>c>>u>>d>>v;

            if(c=='+' and d=='+')
            {
                g[u+m].pb(v);               
                g[v+m].pb(u);
                rg[v].pb(u+m);
                rg[u].pb(v+m);

            }
            else if(c=='+' and d=='-')
            {
                g[u+m].pb(v+m);
                g[v].pb(u);
                rg[v+m].pb(u+m);
                rg[u].pb(v);
            }
            else if(c=='-' and d=='+')
            {
                g[u].pb(v);
                g[v+m].pb(u+m);
                rg[v].pb(u);
                rg[u+m].pb(v+m);
            }
            else
            {
                g[u].pb(v+m);
                g[v].pb(u+m);
                rg[v+m].pb(u);
                rg[u+m].pb(v);
            }

        }

        vector<bool>vis(2*m+1,false);
        vll order;
        vll component[2*m+1];

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

        rep(i,1,2*m+1)
        {
            if(!vis[i]){
                dfs1(i);
            }
        }

        vis.assign(2*m+1,false);
        reverse(all(order));
        
        vll root(2*m+1,0);

        ll num=1;
        for(auto u:order)
        {
            if(!vis[u])
            {
                dfs2(u,num);
                for(auto it:component[num])
                {
                    root[it]=num;
                }
                num++;
            }
            
        }

        vll ans(m+1);
        rep(i,1,m+1)    
        {   
            if(root[i]==root[i+m])
            {
                cout<<"IMPOSSIBLE\n";
                return;
            }

            ans[i]=(root[i]>root[i+m]);
        }

        rep(i,1,m+1)
        {
            if(ans[i])
            {
                cout<<"+ ";
            }
            else
            {
                cout<<"- ";
            }
        }