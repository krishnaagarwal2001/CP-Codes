
//RANGE GCD CODECHEF

void build(vll& sr,vll& lazy,vll& a)
    {
        ll n=sz(a),b=sz(sr);
        ll cur=-1;
        rep(i,0,n)
        {   
            ll bl=i/b;
            lazy[bl]=1;
            if(cur<bl)
            {   
                sr[bl]=a[i];
                cur=bl;
            }
            else
            {
                sr[bl]=__gcd(sr[bl],a[i]);
            }
        }
    }
    
    void update(vll& sr,vll& lazy,vll& a,ll l,ll r,ll m)
    {   
        ll b=sz(sr);
        
        ll l_block=l/b,r_block=r/b;
        ll l_end=l_block*b+b-1,r_st=r_block*b;
        
        for(int i=l;i<=min(r,l_end);++i)
        {   
            a[i]*=m;
        }
        
        sr[l_block]=a[l_block*b];
        for(int i=l_block*b;i<=l_end;++i)               //update sr[l_block]
        {
            sr[l_block]=__gcd(sr[l_block],a[i]);        
        }
        
        if(l_block==r_block)
        return;
        
        for(int i=r;i>=max(l,r_st);i--)
        {
            a[i]*=m;
        }
        
        
        sr[r_block]=a[r_block*b];
        for(int i=r_st;i<=r_st+b-1;i++)                 //update sr[r_block]
        {
            sr[r_block]=__gcd(sr[r_block],a[i]);
        }

        rep(i,l_block+1,r_block)
        {
            lazy[i]*=m;
        }
        
    }
    
    ll query(vll& sr,vll& lazy,vll& a,ll l,ll r)
    {   
        ll b=sz(sr);
        ll ans=a[l]*lazy[l/b];
      
        ll l_block=l/b,r_block=r/b;
        ll l_end=l_block*b+b-1,r_st=r_block*b;
        
        for(int i=l;i<=min(r,l_end);++i)
        {   
            ans=__gcd(ans,a[i]*lazy[i/b]);
        }
        
        if(l_block==r_block)
        return ans;
        
        for(int i=r;i>=max(l,r_st);i--)
        {
            ans=__gcd(ans,a[i]*lazy[i/b]);
        }
        
        rep(i,l_block+1,r_block)
        {
            ans=__gcd(ans,sr[i]*lazy[i]);
        }
        
        return ans;
    }