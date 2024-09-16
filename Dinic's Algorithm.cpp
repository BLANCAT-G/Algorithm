#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <unordered_map>
#include <cmath>
#define FAST() ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define ll long long
#define pii pair<int,int>
#define pll pair<long long,long long>
#define INF 2100000000
#define LNF 9000000000000000000
using namespace std;

struct Edge{
    int to,rev;
    ll cap,flow=0;
    Edge(int to,ll cap,int rev):to(to),cap(cap),rev(rev){}
};

int N,K,D;
queue<int> q;
vector<vector<Edge>> adj;
vector<int> level,ptr;

void addEdge(int a,int b,ll cap){
    adj[a].push_back(Edge(b, cap, adj[b].size())); 
    adj[b].push_back(Edge(a, 0, adj[a].size() - 1));
}

bool bfs(int s,int t){
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(auto &e:adj[v]){
            if(e.cap-e.flow<1)
                continue;
            if(level[e.to]!=-1)
                continue;
            level[e.to]=level[v]+1;
            q.push(e.to);
        }
    }
    return level[t]!=-1;
}

ll dfs(int v,int t,ll flow=LNF){
    if(v==t)
        return flow;
    for(int &i=ptr[v];i<adj[v].size();++i){
        Edge &e=adj[v][i];
        if(level[e.to]!=level[v]+1)
            continue;
        if(e.cap-e.flow<1)
            continue;
        ll pushed=dfs(e.to,t,min(flow,e.cap-e.flow));
        if(pushed>0){
            e.flow+=pushed;
            adj[e.to][e.rev].flow-=pushed;
            return pushed;
        }
    }
    return 0;
}

ll maxFlow(int s,int t){
    ll flow=0;
    while(1){
        fill(level.begin(),level.end(),-1);
        level[s] = 0; 
        q.push(s); 
        if (!bfs(s, t)) 
            break; 
        fill(ptr.begin(), ptr.end(), 0); 
        while (ll pushed = dfs(s, t)) 
            flow += pushed;
    }
    return flow;
}
