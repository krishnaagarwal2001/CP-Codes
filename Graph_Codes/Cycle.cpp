#include<bits/stdc++.h>
using namespace std;

vector<int>parent;
vector<int>color;

bool isCycle = 0;
vector<int> anyCycle;

void dfs(int node, int par){
    parent[node] = par;
    color[node] = 2;

    for(int v : g[node]){
        if(v == par){           // we can comment it out in directed graph
            continue;
        }

        if(color[v] == 1){
            // node -- v is a forward edge
            dfs(v,node);

        }else if(color[v] == 2){
            //node -- v is a back edge
            // we found a cycle
            
            if(!isCycle){
                int curNode = node;

                while(curNode != v){
                    anyCycle.push_back(curNode);
                    curNode = parent[curNode];
                }

                anyCycle.push_back(curNode);
            }
        }else if(color[v] == 3){            // we can comment it out in undirected graph
            //node -- v is a crosss edge
        }
    }
}

int main(){
    color.assign(n+1,1);
    parent.resize(n+1);
}