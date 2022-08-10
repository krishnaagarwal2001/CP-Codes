    class dsu
    {
        ll n;
        vector<ll> par;
        vector<ll> s;
        public:
        dsu(ll nval)
        {
            n = nval;
            par.resize(n + 1);
            s.resize(n + 1);
     
            for (int i = 1; i <= n; ++i)
                par[i] = i, s[i] = 1;
        }
     
        //O(1) ammortized
        ll root(ll x)
        {
            if (x == par[x])
                return x;
            return par[x] = root(par[x]);
        }
     
        //O(1) ammortized
        bool find(ll a,ll b)
        {
            return root(a) == root(b);
        }
     
        //O(1) ammortized
        void un(ll a, ll b)
        {
            int ra = root(a);
            int rb = root(b);
     
            if (ra == rb)
                return;
     
            if (s[ra] > s[rb])
                swap(ra, rb);
     
            par[ra] = rb;
            s[rb] += s[ra];
        }
    };

    int main()
    {
        vector<vll> edge(m);    //{cost,u,v}

        dsu d(n);
        ll cost=0;
        set<vll>s;
        for(auto it:edge)
        {
            if(sz(s)==n-1)
            {
                break;
            }

            ll u=it[1],v=it[2];

            if(!d.find(u,v))
            {
                s.insert(it);
                d.un(u,v);
                cost+=it[0];
            }
        }
    }