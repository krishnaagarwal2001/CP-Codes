    ll par[N],level[N];
    vll g[N];
    ll lca[20][N];

    ll n,q;

    void dfs_lca(ll x,ll p)
    {
        lca[0][x]=p;

        for(auto y:g[x])
        {
            if(y!=p)
            {   
                level[y]=level[x]+1;
                dfs(y,x);
            }
        }
    }

    ll kth_ancestor(ll x,ll k)
    {
        for(ll i=0;k>0 and x>0;i++,k/=2)
        {
            if(k&1)
            {
                x=lca[i][x];
            }
        }

        return x;
    }

    ll LCA(ll x,ll y)
    {
        if(level[x]>level[y])
            swap(x,y);

        y=kth_ancestor(y,level[y]-level[x]);

        if(x==y) return x;

        for(ll i=19;i>=0;i--)
        {
            if(lca[i][x]!=lca[i][y])
            {
                x=lca[i][x];
                y=lca[i][y];
            }
        }

        return lca[0][x];
    }

    void precompute_lca()
    {   
        level[1]=0;
        dfs_lca(1,0);
        rep(i,1,20)
        {
            rep(x,1,n+1)
            {
                lca[i][x]=lca[i-1][lca[i-1][x]];
            }
        }
    }
    // rep(i,1,20)
    // {
    //     rep(x,1,n+1)
    //     {
    //         lca[i][x]=lca[i-1][lca[i-1][x]];
    //     }
    // }
    void solve()
    {
        cin>>n>>q;
        par[1]=0;
        rep(i,2,n+1)
        {
            cin>>par[i];

            g[par[i]].pb(i);
            g[i].pb(par[i]);
        }

        precompute_lca();
        

        while(q--)
        {   

            ll a,b;
            cin>>a>>b;

            cout<<LCA(a,b)<<endl;
        }

        cout<<"\n";
    }