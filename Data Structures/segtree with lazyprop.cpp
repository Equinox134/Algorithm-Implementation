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

const int N = 5e5+10;

struct Seg{
    #define lc (n<<1)
    #define rc ((n<<1)|1)
    ll t[4*N], lazy[4*N];
    
    Seg(){
        memset(t,0,sizeof(t));
        memset(lazy,0,sizeof(lazy));
    }
    
    inline void ulazy(int n, int s, int e){
        if(lazy[n]==0) return;
        t[n] += lazy[n]*(e-s+1);
        if(s!=e){
            lazy[lc] += lazy[n];
            lazy[rc] += lazy[n];
        }
        lazy[n] = 0;
    }
    
    void upd(int n, int s, int e, int l, int r, int val){
        ulazy(n,s,e);
        if(r<s||e<l) return;
        if(l<=s&&e<=r){
            lazy[n] += val;
            ulazy(n,s,e);
            return;
        }
        int mid = (s+e)>>1;
        upd(lc,s,mid,l,r,val);
        upd(rc,mid+1,e,l,r,val);
        t[n] = t[lc]+t[rc];
    }
    
    ll query(int n, int s, int e, int l, int r){
        ulazy(n,s,e);
        if(r<s||e<l) return 0;
        if(l<=s&&e<=r) return t[n];
        int mid = (s+e)>>1;
        return query(lc,s,mid,l,r)+query(rc,mid+1,e,l,r);
    }
};

int main(){
    fastio;
}
