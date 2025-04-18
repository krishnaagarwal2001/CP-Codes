//also known as Kahn's Algo

vll topo_by_bfs()		//If is lexicographically smallest--use priority queue
{
    queue<ll>q;
    vll indeg(n+1,0);
    vll ans;
    rep(i,1,n+1)
    {
        for(auto j:adj[i])
            indeg[j]++;
    }
    
    rep(i,1,n+1)
    {
        if(!indeg[i])
            q.push(i);
    }
    
    while(!q.empty())
    {
        ll i=q.front();
        q.pop();
        ans.pb(i);
        for(auto j:adj[i])
        {
            indeg[j]--;
            
            if(!indeg[j])
                q.push(j);
        }
    }
    
    return sz(ans)<n?vll {}:ans;
}