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

const ll N = 100010;

struct segtree{
    ll tree[4*N], lazy[4*N];

    void ulazy(ll n, ll s, ll e){
        if(lazy[n]==0) return;
        tree[n] += lazy[n]*(e-s+1);
        if(s!=e){
            lazy[2*n] += lazy[n];
            lazy[2*n+1] += lazy[n];
        }
        lazy[n] = 0;
    }

    void update(ll n, ll s, ll e, ll l, ll r, ll v){
        ulazy(n,s,e);
        if(r<s||l>e) return;
        if(l<=s&&e<=r){
            lazy[n] += v;
            ulazy(n,s,e);
            return;
        }
        ll m = (s+e)>>1;
        update(2*n,s,m,l,r,v);
        update(2*n+1,m+1,e,l,r,v);
        tree[n] = tree[2*n]+tree[2*n+1];
    }

    ll query(ll n, ll s, ll e, ll l, ll r){
        ulazy(n,s,e);
        if(r<s||l>e) return 0;
        if(l<=s&&e<=r) return tree[n];
        ll m = (s+e)>>1;
        return query(2*n,s,m,l,r)+query(2*n+1,m+1,e,l,r);
    }
} seg;

ll n,q,pv;
ll sz[N], dep[N], par[N], top[N], in[N];
ll chk[N];
vector<ll> g[N], inp[N];

void dfs(ll v = 1){
    chk[v] = 1;
    for(auto i:inp[v]){
        if(chk[i]) continue;
        chk[i] = 1;
        g[v].push_back(i);
        dfs(i);
    }
}

void dfs1(ll v = 1){
    sz[v] = 1;
    for(auto &i:g[v]){
        par[i] = v;
        dep[i] = dep[v]+1;
        dfs1(i);
        sz[v] += sz[i];
        if(sz[i]>sz[g[v][0]]) swap(i,g[v][0]);
    }
}

void dfs2(ll v = 1){
    in[v] = ++pv;
    for(auto i:g[v]){
        top[i] = i==g[v][0]?top[v]:i;
        dfs2(i);
    }
}

void update(ll a, ll b, ll c){
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]]) swap(a,b);
        int st = top[a];
        seg.update(1,1,n,in[st],in[a],c);
        a = par[st];
    }
    if(dep[a]>dep[b]) swap(a,b);
    seg.update(1,1,n,in[a],in[b],c);
}

ll query(ll a, ll b){
    ll ret = 0;
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]]) swap(a,b);
        int st = top[a];
        ret += seg.query(1,1,n,in[st],in[a]);
        a = par[st];
    }
    if(dep[a]>dep[b]) swap(a,b);
    ret += query(1,1,n,in[a],in[b]);
    return ret;
}

int main(){
    fastio;
    cin >> n >> q;
    for(int i=1;i<n;i++){
        ll x,y; cin >> x >> y;
        inp[x].push_back(y);
        inp[y].push_back(x);
    }
    dfs(); dfs1(); dfs2();
    while(q--){
        char t; ll x,y;
        cin >> t >> x >> y;
        if(t=='P') update(x,y,1);
        else cout << query(x,y) << "\n";
    }
}
