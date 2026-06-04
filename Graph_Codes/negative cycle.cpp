//https://cses.fi/problemset/task/1197/

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
        
        g[u].push_back(make_pair(v,w));
    }
    
    vector<ll>dis(n+1,INF), oldDis(n+1,INF);
    
    vector<ll>parent(n+1,-1);
        
    // dis[1] = 0;          We want to find any cycle 
    
    for(ll iteration = 0; iteration<n-1; iteration++){
        oldDis = dis;
        for(ll node = 1; node<=n; node++){
            for(pair<ll,ll> edge: g[node]){
                
                // We want to find any cycle 
                // if(dis[node] == INF){
                //     continue;
                // }
                
                if (dis[node] + edge.second < dis[edge.first]) {
                    dis[edge.first] = dis[node] + edge.second;
                    parent[edge.first] = node;
                }
            }
        }
    }
    
    ll x = -1;
    for(ll node = 1; node<=n; node++){
            for(pair<ll,ll> edge: g[node]){
                
                // We want to find any cycle 
                // if(dis[node] == INF){
                //     continue;
                // }
                
                
                if (dis[node] + edge.second < dis[edge.first]) {
                    dis[edge.first] = dis[node] + edge.second;
                    parent[edge.first] = node;
                    x = edge.first;
                }
            }
    }
    
    if(x == -1){
        cout<<"NO"<<endl;
        return 0;
    }
    
    cout<<"YES"<<endl;
    
    /*
        Move the x inside the negative cycle in case it is outside
    */
    for(ll i=0;i<n;i++){
        x = parent[x];
    }
    
    vector<ll>cycle;
    
    ll cur = x;
    cycle.push_back(cur);
    
    cur = parent[cur];
    
    while(cur !=x){
        cycle.push_back(cur);
        cur = parent[cur];
    }
    
    cycle.push_back(cur);
    
    reverse(cycle.begin(),cycle.end());
    
    for(int node: cycle){
        cout<<node<<" ";
    }
    
}