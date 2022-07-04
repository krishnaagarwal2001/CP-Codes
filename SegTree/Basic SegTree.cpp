
void build(vll &arr,vll &segtree,ll s,ll e,ll x)
{
    if(s==e)
    {
        segtree[x]=arr[s];
        return;
    }

    ll mid=(s+e)/2;
    build(arr,segtree,s,mid,2*x);
    build(arr,segtree,mid+1,e,2*x+1);

    segtree[x]=max(segtree[2*x],segtree[2*x+1]);       //function change according to question
}  

void update(vll &arr,vll &segtree,ll s,ll e,ll x,ll pos,ll val)
{
    if(s==e)
    {
        segtree[x]=val;
        arr[pos]=val;
        return;
    }

    ll mid=(s+e)/2;
    if(pos>mid)
    {
        update(arr,segtree,mid+1,e,2*x+1,pos,val);
    }
    else
    {
        update(arr,segtree,s,mid,2*x,pos,val);
    }
    
    segtree[x]=max(segtree[2*x],segtree[2*x+1]);    //function change according to question
} 

ll query(vll &arr,vll &segtree,ll s,ll e,ll x,ll left,ll right)
{
    if(s>right or e<left)
    {
        return (ll)0;                                 //function change according to question
    }

    if(s>=left and e<=right)
    {
        return segtree[x];
    }

    ll mid=(s+e)/2;

    ll a1=query(arr,segtree,s,mid,2*x,left,right);
    ll a2=query(arr,segtree,mid+1,e,2*x+1,left,right);

    return max(a1,a2);
}

// vll segtree(4*n,0);
// build(a,segtree,0,n-1,1);
// query(a,segtree,0,n-1,1,l,r);
// update(a,segtree,0,n-1,1,pos,val);

void main()
{
    ll n;
    cin>>n;

    vll a(n);
    rep(i,0,n)
    cin>>a[i];

    vll segtree(4*n,0);

    build(a,segtree,0,n-1,1);

    ll q;
    cin>>q;
    while(q--)
    {
        ll type;
        cin>>type;

        if(type==1)
        {
            ll l,r;
            cin>>l>>r;
            cout<<query(a,segtree,0,n-1,1,l,r);
        }
        else
        {
            ll pos,val;
            cin>>pos>>val;
            update(a,segtree,0,n-1,1,pos,val);
        }
    }

}