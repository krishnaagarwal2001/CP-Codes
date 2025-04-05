vll bfs(vll source){
queue<ll>q;
vll dist(n+1,-1);

for(auto it:source){
q.push(it);
dist[it]=0;
}

while(!q.empty()){
ll i=q.front();
q.pop();

for(auto nb:adj[i]){

if(dist[nb]!=-1)continue;

q.push(nb);
dist[nb]=dist[i]+1;
}
}

return dis;
}