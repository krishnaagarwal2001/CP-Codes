 void bellman_ford()
        {   
            ll x;
            vll relaxant(n+1,-1);
            vll dist(n+1,0);
            
            for(ll i = 1; i <= n; ++i)
            {
                x = -1;
                for(auto e: edge)
                {
         
                    ll u = e[0];
                    ll v = e[1];
                    ll d = e[2];
                    if(dist[u]+d < dist[v])
                    {
                        dist[v] = d+dist[u];
                        relaxant[v] = u;
                        x = v;
                    }
                }
            } 
           // deb(1)
            if(x == -1)
                cout << "NO" << endl;
         
            else
            {
                for(ll i = 1; i <= n; ++i)
                {
                    x = relaxant[x];
                }
         
                vector<ll> cycle;
         
                for(ll v = x; ; v = relaxant[v])
                {
                    cycle.push_back(v);
                    if(v == x and (cycle.size() > 1))
                        break;
                }
         
                reverse(cycle.begin(), cycle.end());
         
                cout << "YES" << endl;
                for(auto v: cycle)
                {
                    cout << v << " ";
                }
         
                cout << endl;
            }
         
         
        }