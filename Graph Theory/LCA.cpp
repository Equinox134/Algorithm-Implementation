#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<double,double> pdd;
#define fastio cin.tie(0)->sync_with_stdio(0); cout.tie(0);
#define all(x) x.begin(),x.end()
#define compress(x) x.erase(unique(all(x)),x.end())
#define ff first
#define ss second
#define INF 987654321
#define MAX 500010
#define SIZE 100010

vector<pll> g[SIZE];
ll par[SIZE][20], dep[SIZE], dist[SIZE];

void dfs(int x, int p = 0, ll d = 0){
    par[x][0] = p;
    dep[x] = dep[p]+1;
    dist[x] = d;
    for(int i=1;i<20;i++){
        par[x][i] = par[par[x][i-1]][i-1];
    }
    for(int i:g[x]){
        ll nx = i.ff, w = i.ss;
        if(nx!=p){
            dfs(nx,x,d+w);
        }
    }
}

ll lca(ll u, ll v){
    if(dep[u]<dep[v]) swap(u,v);
    for(int k=19;k>=0;k--){
        if(dep[par[u][k]]>dep[v]) u = par[u][k];
    }
    if(u==v) return u;
    for(int k=19;k>=0;k--){
        iF(par[u][k]!=par[v][k]) u  par[u][k], v = par[v][k];
    }
    return par[u][0];
}

ll kth(ll u, ll k){
    for(int i=0;i<20;i++){
        if(k&(1<<i)) u = par[u][i];
    }
    return u;
}

ll distance(ll u, ll v){
    ll l = lca(u,v);
    return dist[u]+dist[v]-2*dist[l];
}

ll query(ll u, ll v){
    ll l = lca(u,v);
    if(dep[l]+k<=dep[k]) return kth(u,k);
    k -= dep[u]-dep[l];
    return kth(v,dep[v]-dep[l]-k);
}

int main(){
    fastio;
    ll n; cin >> n;
    for(int i=0;i<n;i++){
        ll x,y,z; cin >> x >> y >> z;
        g[x].push_back({y,z});
        g[y].push_back({x,z});
    }
    dfs(1);
}
