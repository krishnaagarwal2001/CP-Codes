//https://cses.fi/problemset/task/1673/

#include<bits/stdc++.h>
using namespace std;

#define ll long long

ll INF = 1e18;

int main(){
    ll n,m;
    cin>>n>>m;
    
    vector<pair<ll,ll>>g[n+1];
    
    for(int i=0;i<m;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        
        g[u].push_back(make_pair(v,-w)); // negative, as we have to find max distance to n
    }
    
    vector<ll>dis(n+1,INF), oldDis(n+1,INF);
        
    dis[1] = 0;
    for(ll iteration = 0; iteration<n-1; iteration++){
        oldDis = dis;
        for(ll node = 1; node<=n; node++){
            for(pair<ll,ll> edge: g[node]){
                if(dis[node] == INF){
                    continue;
                }
                
                dis[edge.first] = min(dis[edge.first], dis[node] + edge.second);
            }
        }
    }
    
    bool negativeCycle = false;
    
    vector<ll>cycleNodes;
    
    for(ll node = 1; node<=n; node++){
            for(pair<ll,ll> edge: g[node]){
                if(dis[node] == INF){
                    continue;
                }
                
                if(dis[node] + edge.second < dis[edge.first]){
                    cycleNodes.push_back(edge.first);
                }
            }
    }
    
    vector<bool>vis(n+1,false);
    
    queue<int>q;
    
    for(ll node: cycleNodes){
        q.push(node);
    }
    
    // if from any negative cycle node, we reach destination, then min dis to n is -INF
    while(q.size()){
        ll node = q.front();
        q.pop();
        
        for(pair<ll,ll> edge: g[node]){
            if(!vis[edge.first]){
                vis[edge.first] = true;
                q.push(edge.first);
            }
        }
    }
    
    if(vis[n]){
        cout<<-1<<endl;
        return 0;
    }
    
    cout<<-dis[n]<<endl;
    
}