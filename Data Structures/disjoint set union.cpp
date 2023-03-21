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

const ll N = 200010;

struct DSU{
    ll par[N];
    DSU(){
        for(int i=0;i<N;i++){
            par[i] = i;
        }
    }

    ll find(ll x){
        if(x==par[x]) return par[x];
        return par[x] = find(par[x]);
    }

    ll onion(ll a, ll b){
        a = find(a); b = find(b);
        if(a==b) return 0;
        if(a<b) swap(a,b);
        par[b] = a;
        return 1;
    }
};

int main(){
    fastio;
}
