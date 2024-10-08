#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define FAST() ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define INF 2100000000
using namespace std;

int N,K,ans=INF;
vector<pii> edge[200010];
map<int,int> um;
int visited[200010]={0};
int tsize[200010];

int get_tsize(int x,int pre){
    tsize[x]=1;
    for(pii next:edge[x]){
        if(pre==next.first||visited[next.first]) continue;
        tsize[x]+=get_tsize(next.first,x);
    }
    return tsize[x];
}

int get_centroid(int x,int pre,int half){
    for(pii next:edge[x]){
        if(pre==next.first||visited[next.first]) continue;
        if(half<tsize[next.first]) return get_centroid(next.first,x,half);
    }
    return x;
}

void cal(int x,int pre,int dist,int depth){
    if(dist>K) return;
    if(um.find(K-dist)!=um.end()) ans=min(ans,um[K-dist]+depth);
    for(pii next:edge[x]){
        if(next.first==pre||visited[next.first]) continue;
        cal(next.first,x,dist+next.second,depth+1);
    }
}

void update(int x,int pre,int dist,int depth){
    if(dist>K) return;
    if(um.find(dist)!=um.end()) um[dist]=min(um[dist],depth);
    else um[dist]=depth;
    for(pii next:edge[x]){
        if(next.first==pre|| visited[next.first]) continue;
        update(next.first,x,dist+next.second,depth+1);
    }
}

void solve(int cur){
    int sz=get_tsize(cur,-1);
    int cent=get_centroid(cur,-1,sz/2);
    visited[cent]=1;
    um.clear();
    um[0]=0;
    for(pii next:edge[cent]){
        if(visited[next.first]) continue;
        cal(next.first,cent,next.second,1);
        update(next.first,cent,next.second,1);
    }
    for(pii next:edge[cent]){
        if(visited[next.first]) continue;
        solve(next.first);
    }
}

int main()
{
    FAST(); 
    int a,b,c;
    cin>>N>>K;
    for(int i=1;i<N;++i){
        cin>>a>>b>>c;
        edge[a].push_back({b,c});
        edge[b].push_back({a,c});
    }
    solve(0);
    cout<<(ans==INF?-1:ans);
    return 0;
}

