        vector<ll>g[n+1];
        vector<vll>capacity(n+1,vll(n+1,0)),in_capacity(n+1,vll(n+1,0));    //residual capacity
        rep(i,0,m)
        {
            ll u,v,w;
            cin>>u>>v>>w;

            g[u].pb(v);
            g[v].pb(u);                  // back edge with 0 capacity
            capacity[u][v]+=w;          // For multiple edges sum of all the capacities
            in_capacity[u][v]+=w;
        }

        ll s=1,t=n;
        vector<ll>par(n+1,-1);

        auto bfs=[&](ll s,ll t){
            par[s]=-2;
            queue<pii>q;
            q.push({s,inf});

            while(!q.empty())
            {
                auto [cur,flow]=q.front();
                q.pop();
                for(auto next:g[cur])
                {   
                    if(par[next]==-1 and capacity[cur][next])
                    {
                        par[next]=cur;
                        ll new_flow=min(flow,capacity[cur][next]);

                        if(next==t)
                            return new_flow;

                        q.push({next,new_flow});
                    }
                }
            }
            return 0ll;
        };

        ll flow=0;
        ll new_flow;

        while(new_flow=bfs(s,t))
        {   
            flow+=new_flow;
            ll cur=t;
            while(cur!=s)
            {
                ll pre=par[cur];
                capacity[pre][cur]-=new_flow;
                capacity[cur][pre]+=new_flow;
                cur=pre;
            }
            fill(all(par),-1);
        }

        cout<<flow;

        /* To find MIN CUT*/

        fill(all(par),-1);
        bfs(s,t);

        rep(i,1,n+1)
        {
            rep(j,1,n+1)
            {
                if(par[i]!=-1 and par[j]==-1 and in_capacity[i][j])
                {
                    cout<<i<<" "<<j<<endl;
                }
            }
        }