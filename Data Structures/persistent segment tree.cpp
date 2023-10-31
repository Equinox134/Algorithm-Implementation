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

const int N = 1e5+10LL;

struct PST{
    #define lc t[cur].l
    #define rc t[cur].r
    struct node{
        ll l = 0, r = 0, val = 0;
    } t[20*N];
    int T = 0;

    int build(int s, int e){
        int cur = ++T;
        if(s==e) return cur;
        ll m = (s+e)>>1;
        lc = build(s,m);
        rc = build(m+1,e);
        t[cur].val = t[lc].val+t[rc].val;
        return cur;
    }

    int upd(int pre, int s, int e, int i, ll v){
        int cur = ++T;
        t[cur] = t[pre];
        if(s==e){
            t[cur].val += v;
            return cur;
        }
        ll m = (s+e)>>1;
        if(i<=m){
            rc = t[pre].r;
            lc = upd(t[pre].l,s,m,i,v);
        }
        else{
            lc = t[pre].l;
            rc = upd(t[pre].r,m+1,e,i,v);
        }
        t[cur].val = t[lc].val+t[rc].val;
        return cur;
    }

    int query(int pre, int cur, int s, int e, int k){
        if(s==e) return s;
        int cnt = t[lc].val-t[t[pre].l].val;
        ll m = (s+e)>>1;
        if(cnt>=k) return query(t[pre].l,lc,s,m,k);
        else return query(t[pre].r,rc,m+1,e,k-cnt);
    }
};

PST t;
ll a[N], root[N], b[N];

int main(){
    fastio;
    map<ll,ll> mp;
    ll n,q; cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        mp[a[i]] = 0;
    }
    ll c = 0;
    for(auto i:mp){
        mp[i.ff] = ++c;
        b[c] = i.ff;
    }
    root[0] = t.build(1,n);
    for(int i=1;i<=n;i++){
        root[i] = t.upd(root[i-1],1,n,mp[a[i]],1);
    }
    while(q--){
        ll l,r,k;
        cin >> l >> r >> k;
        cout << b[t.query(root[l-1],root[r],1,n,k)] << "\n";
    }
}
