

vector<pii> g[N],tree[N];    

ll par[N],lca[20][N],arrival[N],departure[N],level[N],timer,dist[N];

void dfs(ll x,ll p)
{
    lca[0][x]=p;
    arrival[x]= ++timer;

    for(auto y:g[x])
    {
        if(y.fi!=p)
        {   
            level[y.fi]=level[x]+1;
            dist[y.fi]=dist[x]+y.se;
            dfs(y.fi,x);
        }
    }
    departure[x]=++timer;
}

ll anc(ll p,ll x)
{
	return arrival[x]>=arrival[p] and departure[x]<=departure[p];		//check for error
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
	timer=0;
	level[1]=0;
	dist[1]=0;
    dfs(1,0);
    rep(i,1,20)
    {
        rep(x,1,n+1)
        {
            lca[i][x]=lca[i-1][lca[i-1][x]];
        }
    }
}

struct comp{
	bool operator()(ll a,ll b)
	const{
		return arrival[a]<arrival[b];			//sort based on arrival time
	}
};
	
ll aux_tree(vector<ll> &Q)              //return root node of auxiliary tree
{   
    sort(all(Q),comp());                //Q[0] is the root
    ll SIZE=sz(Q);
    rep(i,0,SIZE-1)
    {   
        Q.pb(LCA(Q[i],Q[i+1]));
    }

    sort(all(Q),comp());
    Q.erase(unique(all(Q)),Q.end());

    rep(i,0,sz(Q))
    log(Q[i])

    stack<ll>s;

    s.push(Q[0]);

    rep(i,1,sz(Q))
    {
        while(!anc(s.top(),Q[i])) s.pop();

        ll w=level[s.top()]+level[Q[i]]-2*level[LCA(s.top(),Q[i])];
        tree[s.top()].pb({Q[i],w});
        tree[Q[i]].pb({s.top(),w});

        s.push(Q[i]);
    }

    //CHANGE HERE


    //
                                        
    rep(i,0,sz(Q))
    {
        tree[Q[i]].clear();
    }

     return Q[0];
}


//https://www.hackerrank.com/contests/worldcupsemifinals/challenges/wccity