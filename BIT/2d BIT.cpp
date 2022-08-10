struct BIT{
        ll n,m;
        vvl tree;

        BIT(ll n,ll m)
        {
            this->n=n;
            this->m=m;
            tree.assign(n+1,vll(m+1,0));
        }

        ll sum(ll x,ll y)
        {   
            ll res=0;
            while(x)
            {
                ll y1=y;
                while(y1)
                {
                    res+=tree[x][y1];
                    y1-=(y1 & (-y1));
                }

                x-=(x & (-x));
            }
            return res;
        }

        ll sum(ll x1,ll y1,ll x2,ll y2)
        {
            return (sum(x1-1,y1-1)+sum(x2,y2)-sum(x2,y1-1)-sum(x1-1,y2));
        }

        void update(ll x,ll y,ll val)
        {
            while(x<=n)
            {
                ll y1=y;
                while(y1<=m)
                {
                    tree[x][y1]+=val;
                    y1+=(y1 & (-y1));
                }

                x+=(x&(-x));
            }
        }
    };