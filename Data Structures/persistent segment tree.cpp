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

const int N = 5e5+10LL;

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

    ll psum(int cur, int s, int e, int l, int r){
        if(r<s||l>e) return 0;
        if(l<=s&&e<=r) return t[cur].val;
        ll m = (s+e)>>1;
        return psum(lc,s,m,l,r)+psum(rc,m+1,e,l,r);
    }

    ll sum(int pre, int cur, int s, int e, int l, int r){
        return psum(cur,s,e,l,r)-psum(pre,s,e,l,r);
    }

    int kth(int pre, int cur, int s, int e, int k){
        if(s==e) return s;
        int cnt = t[lc].val-t[t[pre].l].val;
        ll m = (s+e)>>1;
        if(cnt>=k) return kth(t[pre].l,lc,s,m,k);
        else return kth(t[pre].r,rc,m+1,e,k-cnt);
    }

    ll query(int pre, int cur, int s, int e, ll x){
        if(s==e) return s;
        int lcnt = t[lc].val-t[t[pre].l].val;
        int rcnt = t[rc].val-t[t[pre].r].val;
        ll m = (s+e)>>1, bit = (e-s+1)/2;
        if((x&bit)&&lcnt==0) return query(t[pre].r,rc,m+1,e,x);
        if(!(x&bit)&&rcnt!=0) return query(t[pre].r,rc,m+1,e,x);
        return query(t[pre].l,lc,s,m,x);
    }
};

PST t;
ll a[N], root[N], b[N];
ll n = 524287;

int main(){
    fastio;
    ll q,cur=0; cin >> q;
    root[0] = t.build(0,n);
    while(q--){
        ll tp; cin >> tp;
        if(tp==1){
            ll x; cin >> x;
            root[cur+1] = t.upd(root[cur],0,n,x,1);
            ++cur;
        }
        else if(tp==2){
            ll l,r,x; cin >> l >> r >> x;
            cout << t.query(root[l-1],root[r],0,n,x) << "\n";
        }
        else if(tp==3){
            ll k; cin >> k;
            cur -= k;
        }
        else if(tp==4){
            ll l,r,x; cin >> l >> r >> x;
            cout << t.sum(root[l-1],root[r],0,n,1,x) << "\n";
        }
        else{
            ll l,r,k; cin >> l >> r >> k;
            cout << t.kth(root[l-1],root[r],0,n,k) << "\n";
        }
    }
}
// boj 13538
