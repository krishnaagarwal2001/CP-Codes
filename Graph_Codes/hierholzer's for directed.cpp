        //EULER PATH

        ll n,m;
        cin>>n>>m;

        set<ll> g[n+1];
        vll indegree(n+1,0),outdegree(n+1,0);
        rep(i,0,m)
        {
            ll u,v;
            cin>>u>>v;

            g[u].insert(v);
            outdegree[u]++;
            indegree[v]++;
            // g[v].insert(u);
        }

        auto euler_path=[&](ll start,ll end){

            bool f=true;
            rep(i,1,n+1)
            {
                if(i==start)
                {
                    if(outdegree[i]!=indegree[i]+1)
                    {
                        f=false;
                    }
                }
                else if(i==end)
                {
                    if(outdegree[i]!=indegree[i]-1)
                    {
                        f=false;
                    }
                }
                else
                {
                    if(outdegree[i]!=indegree[i])
                    {
                        f=false;
                    }
                }
            }

            if(!f)
            {
                cout<<"IMPOSSIBLE\n";
                return;
            }

            vll ans;

            stack<int>st;
            st.push(start);

            while(!st.empty())
            {
                ll u=st.top();
                if(g[u].size())
                {
                    ll v=*g[u].begin();
                    g[u].erase(v);
                    st.push(v);
                }
                else
                {
                    ans.pb(u);
                    st.pop();
                }
            }

            if(sz(ans)!=m+1)
            {
                cout<<"IMPOSSIBLE\n";
                return;
            }
            reverse(all(ans));
            for(auto u:ans)
            {
                cout<<u<<" ";
            }
            cout<<endl;
            return;
        };

        euler_path(1,n);