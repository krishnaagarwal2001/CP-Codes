        ll n,m,k;
        cin>>n>>m>>k;

        vll g[n+1];
        rep(i,0,k)
        {
            ll u,v;
            cin>>u>>v;
            // v+=n;

            g[u].pb(v);
        }

        vll match_n(n+1,0),match_m(m+1,0),dis(n+1,0); 
        auto bfs=[&](){
            
            queue<ll>q;

            rep(i,1,n+1)
            {
                if(match_n[i]==0)
                {
                    dis[i]=0;
                    q.push(i);
                }
                else
                {
                    dis[i]=inf;
                }
            }

            dis[0]=inf;

            while(!q.empty())
            {
                ll u=q.front();
                q.pop();

                if(dis[u]<dis[0])
                {
                    for(auto it:g[u])
                    {
                        if(dis[match_m[it]]==inf)
                        {
                            dis[match_m[it]]=dis[u]+1;
                            q.push(match_m[it]);
                        }
                    }
                }
            }

            return (dis[0]!=inf);
        };

        function<bool(ll)> dfs=[&](ll node){

            if(node)
            {
                for(auto it:g[node])
                {
                    if(dis[match_m[it]]==dis[node]+1)
                    {
                        if(dfs(match_m[it]))
                        {
                            match_m[it]=node;
                            match_n[node]=it;
                            return true;
                        }
                    }
                }

                dis[node]=inf;
                return false;
            }

            return true;
        };

        ll ans=0;

        while(bfs())
        {
            rep(i,1,n+1)
            {
                if(match_n[i]==0 and dfs(i))
                    ans++;
            }
        }

        cout<<ans<<endl;

        rep(i,1,n+1)
        {
            if(match_n[i])
            {
                cout<<i<<" "<<match_n[i]<<endl;
            }
        }