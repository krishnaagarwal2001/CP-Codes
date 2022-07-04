bool dfs_for_topo(ll i,vll &ans,vll &vis)
{
    vis[i]=1;
    
    for(auto it:adj[i])
    {
        if(!vis[i])
        {
            bool e=dfs_for_topo(it,ans,vis);
            
            if(!e) return false;
        }
        else if(vis[i]==1)
            return false;
    }
    
    vis[i]=2;
    ans.pb(i);
    return true;
}
vll topo_by_dfs()
{
    vll vis(n+1,0),ans;
    bool possible=true;
    
    rep(i,1,n+1)
    {
        if(!vis[i])
            possible&=dfs_for_topo(i,ans,vis);
    }
    
    reverse(all(ans));
    
    return possible?ans:vll {};
    
}