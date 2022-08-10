    // https://atcoder.jp/contests/agc002/tasks/agc002_d
    
    struct DSU
    {
        ll n;
        vector<ll> par;
        vector<ll> s;
        DSU(ll nval)
        {
            n = nval;
            par.resize(n + 1);
            s.resize(n + 1);

            for (int i = 1; i <= n; ++i)
                par[i] = i, s[i] = 1;
        }

        ll root(ll x)
        {
            if (x == par[x])
                return x;
            return par[x] = root(par[x]);
        }

        bool find(ll a,ll b)
        {
            return root(a) == root(b);
        }

        void unite(ll a, ll b)
        {
            int ra = root(a);
            int rb = root(b);

            if (ra == rb)
                return;

            if (s[ra] > s[rb])
                swap(ra, rb);
 
            par[ra] = rb;
            s[rb] += s[ra];
            s[ra]=0;
        }
    };

    struct Edge{
        ll a,b;
    };

    struct Query{
        ll x,y,z,idx;
        ll low,high;
    };

    bool check(Query &query,DSU &dsu)               //check function to check if mid satisfies that query or not
    {
        ll x=query.x,y=query.y,z=query.z;

        ll cnt=0;

        if(dsu.find(x,y))
        {
            cnt=dsu.s[dsu.root(x)];
        }
        else
        {
            cnt=dsu.s[dsu.root(x)]+dsu.s[dsu.root(y)];
        }
        return (cnt>=z);
    }

    // O(logM *(N+M+Q))

    void solve(ll n,ll m,ll q,Edge edges[],Query queries[])
    {
        rep(i,1,q+1)                    //initializing low and high of every query
        {
            queries[i].low=1;
            queries[i].high=m;
        }

        while(1)                            //iteration = O(logM)
        {
            vector<Query> queryListToCheck[m+5];       //Queries to be checked
            bool isNoChange=true;                      //denote if we got the ans of all the queries

            rep(i,1,q+1)                              //pushing queries which are not satisfied
            {
                if(queries[i].low!=queries[i].high)
                {
                    ll mid=(queries[i].low+queries[i].high)/2;
                    queryListToCheck[mid].push_back(queries[i]);
                    isNoChange=false;
                }
            }

            if(isNoChange)
                break;

            DSU dsu(n);                           //O(N)   //some ds which help to fasten the process (depends on the use case)

            rep(mid,1,m+1)                        //O(M)      // looping through all m
            {
                dsu.unite(edges[mid].a,edges[mid].b);

                for(auto query:queryListToCheck[mid])    //O(N)total   //checking for particular query
                {   
                    if(!check(query,dsu))
                    {
                        queries[query.idx].low=mid+1;
                    }
                    else
                    {
                        queries[query.idx].high=mid;
                    }
                }
            }

        }

        rep(i,1,q+1)
        {
            cout<<queries[i].low<<endl;
        }
    }
    void solve()  
    {   
        ll n,m,q;
        cin>>n>>m;

        Edge edges[m+5];

        rep(i,1,m+1)
        {
            cin>>edges[i].a>>edges[i].b;
        }

        cin>>q;

        Query queries[q+5];

        rep(i,1,q+1)
        {
            cin>>queries[i].x>>queries[i].y>>queries[i].z;
            queries[i].idx=i;
        }

        solve(n,m,q,edges,queries);
        cout<<"\n";
    }
    