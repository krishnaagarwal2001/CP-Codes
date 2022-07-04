//No. of elements <=x in range (with updates)

void build(vvl& sr,vll& a)
    {
        ll n=sz(a),b=sz(sr);
        
        rep(i,0,n)
        {
            sr[i/b].pb(a[i]);
        }
        
        rep(i,0,b)
        {
            sort(all(sr[i]));
        }
    }
    
    void update(vvl& sr,vll& a,ll pos,ll val)
    {   
        ll b=sz(sr);
        
        ll block=pos/b;
        
        rep(i,0,sz(sr[block]))
        {
            if(sr[block][i]==a[pos])
            {
                a[pos]=val;
                sr[block][i]=val;
                
                ll j=i-1;
                ll idx=i;
                while(j>=0)
                {
                    if(sr[block][j]>sr[block][idx])
                    {
                        swap(sr[block][j],sr[block][idx]);
                        j--;
                        idx--;
                    }
                    else
                    {
                        break;
                    }
                }
                
                 j=i+1;
                idx=i;
                
                while(j<sz(sr[block]))
                {
                    if(sr[block][j]<sr[block][idx])
                    {
                        swap(sr[block][j],sr[block][idx]);
                        j++;
                        idx++;
                    }
                    else
                    {
                        break;
                    }
                }
                
                
                break;
            }
        }
        
    }
    
    ll query(vvl& sr,vll& a,ll l,ll r,ll x)
    {
        ll ans=0;
        ll b=sz(sr);
        
        ll l_block=l/b,r_block=r/b;
        ll l_end=l_block*b+b-1,r_st=r_block*b;
        
        for(int i=l;i<=min(r,l_end);++i)
        {
            if(a[i]<=x)
            {
                ans++;
            }
        }
        
        if(l_block==r_block)
        return ans;
        
        for(int i=r;i>=max(l,r_st);i--)
        {
            if(a[i]<=x)
            {
                ans++;
            }
        }
        
        rep(i,l_block+1,r_block)
        {
            auto it=upper_bound(all(sr[i]),x);
            if(it==sr[i].end())
            {
                ans+=sz(sr[i]);
            }
            else
            {
                ans+=(it-sr[i].begin());
            }
        }
        
        return ans;
    }