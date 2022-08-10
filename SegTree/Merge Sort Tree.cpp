//KQEURY
#include<bits/stdc++.h>
using namespace std;

const int N=3e4+10;
vector<int>ST[4*N];
int A[N],n;

#define lc (x << 1)
#define rc (x << 1)|1
#define all(a) a.begin(),a.end()

void build(int l=1,int r=n,int x=1)
{
    if(l==r)
    {
        ST[x].push_back(A[l]);
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,lc);
    build(mid+1,r,rc);
    merge(all(ST[lc]),all(ST[rc]),back_inserter(ST[x]));
}

int query(int L,int R,int K,int l=1,int r=n,int x=1){
    if(L>r or R<l)
    {
        return 0;
    }

    if(l>=L and r<=R)
    {
        int ans=distance(upper_bound(all(ST[x]),K),ST[x].end());
        return ans;
    }

    int mid=(l+r)>>1;
    return query(L,R,K,l,mid,lc)+query(L,R,K,mid+1,r,rc);
}

int main()
{   
    
    scanf("%d",&n);

    for(int i=1;i<=n;++i)
    {
        scanf("%d",A+i);
    }
    build();

    int q;
    scanf("%d",&q);

    while(q--)
    {
        int l,r,k;
        scanf("%d %d %d",&l,&r,&k);
        cout<<query(l,r,k)<<endl;
    }
}