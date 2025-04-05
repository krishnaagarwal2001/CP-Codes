ll bellman_ford(ll src)
    {
        vll d(n+1,-inf);
 
        d[src]=0;
        vll old=d;
        rep(i,0,n-1)
        {   
            old=d;
            for(auto it:g)
            {   
                ll u=it[0],v=it[1],w=it[2];
                if(d[u]==inf)
                    continue;
                d[v]=min(d[v],d[u]+w);
            }
        }
 
        rep(i,0,n-1)
        {   
            old=d;
            for(auto it:g)
            {   
                ll u=it[0],v=it[1],w=it[2];
                if(d[u]==inf)
                    continue;
                if(d[u]+w<d[v])
                {
                    d[v]=-inf;          //negative cycle present
                }
                
            }
        }
        
        //deb(old[n])
        if(d[n]!=-inf)
            return d[n];
        else
            return -1;
    }