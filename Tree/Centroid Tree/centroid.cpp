ll n,q;
        cin>>n>>q;

        vll g[n+1];

        rep(i,0,n-1)
        {
            ll u,v;
            cin>>u>>v;
            g[u].pb(v);
            g[v].pb(u);
        }

        vll level(n+1,0);
        vll subtree_size(n+1,0);
        vll removed(n+1,0);
        vll centroid_par(n+1,0);
        vvl dist(19,vll(n+1));

        function<void(ll,ll)> get_subtree_size=[&](ll node,ll p)
        {
            subtree_size[node]=1;
            for(auto it:g[node])
            {
                if(it!=p and !removed[it])
                {
                    get_subtree_size(it,node);
                    subtree_size[node]+=subtree_size[it];
                }
            }
        };

        function<ll(ll,ll,ll)> get_centroid=[&](ll node,ll ms,ll p)
        {
            for(auto it:g[node])
            {
                if(it!=p and !removed[it])
                {
                    if(subtree_size[it]>ms/2)
                        return get_centroid(it,ms,node);
                }
            }
            return node;
        };

        function<void(ll,ll,ll,ll)> get_dist=[&](ll node,ll p,ll d,ll level)
        {
            dist[level][node]=d;

            for(auto it:g[node])
            {   
                if(it!=p and !removed[it])
                    get_dist(it,node,d+1,level);
            }
        };

        function<void(ll,ll)> centroid_decomposition=[&](ll node,ll p)
        {   
            get_subtree_size(node,node);
            ll c=get_centroid(node,subtree_size[node],node);
            centroid_par[c]=p;
            level[c]=level[p]+1;
            // log(c,level[c])
            get_dist(c,c,0,level[c]);
            
            removed[c]=1;
            for(auto it:g[c])
            {
                if(!removed[it])
                    centroid_decomposition(it,c);
            }
        };

        centroid_decomposition(1,0);

        function<ll(ll,ll)> get_lca=[&](ll u,ll v)
        {   
            // log(u,v)
            while(u!=v)
            {
                if(level[u]>level[v])
                    swap(u,v);
                v=centroid_par[v];
                // log(u,v)
            }
            // log(u)
            return u;
        };

        function<ll(ll,ll)> ans=[&](ll u,ll v)
        {
            ll lca_level=level[get_lca(u,v)];
            // log(u,v,get_lca(u,v),lca_level)
            return dist[lca_level][u]+dist[lca_level][v];
        };

        while(q--)
        {
            ll u,v;
            cin>>u>>v;

            cout<<ans(u,v)<<endl;
        }