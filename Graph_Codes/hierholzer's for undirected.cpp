        //EULER CYCLE

        ll n,m;
        cin>>n>>m;

        set<ll> g[n+1];
        rep(i,0,m)
        {
            ll u,v;
            cin>>u>>v;

            g[u].insert(v);
            g[v].insert(u);
        }

        auto euler_circuit=[&](){
            rep(i,1,n+1)
            {
                if(sz(g[i])%2)
                {
                    cout<<"IMPOSSIBLE\n";
                    return;
                }
            }

            vll ans;

            stack<int>st;
            st.push(1);

            while(!st.empty())
            {
                ll u=st.top();
                if(g[u].size())
                {
                    ll v=*g[u].begin();
                    g[u].erase(v);
                    g[v].erase(u);
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

            for(auto u:ans)
            {
                cout<<u<<" ";
            }
            cout<<endl;
            return;
        };

        euler_circuit();