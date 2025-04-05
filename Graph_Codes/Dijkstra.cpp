    vll dijkstra(ll src)
    {
        vll d(n+1,inf),par(n+1);
        set<pii>s;

        d[src]=0;
        s.insert({d[src],src});

        while(!s.empty())
        {
            auto it=s.begin();
            ll u=it->se;
            s.erase(it);

            for(pii e:adj[u])
            {
                ll nb=e.fi,w=e.se;

                if(d[u]+w<d[nb])
                {
                    s.erase({d[nb],nb});
                    d[nb]=d[u]+w;
                    par[nb]=u;
                    s.insert({d[nb],nb});
                }
            }
        }

        return d;
    }