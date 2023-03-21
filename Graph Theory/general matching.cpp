#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
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
#define MAX 200010
#define SIZE 100010

vector<ll> g[510];
ll n,m,t=-1,match[510],lab[510],par[510],orig[510],aux[510];
queue<ll> q;

ll lca(ll x, ll y){
	for(t++;;swap(x,y)){
		if(x==-1) continue;
		if(aux[x]==t) return x;
		aux[x] = t;
		if(match[x]==-1) x = -1;
		else x = orig[par[match[x]]];
	}
}

void blossom(ll v, ll w, ll a){
	while(orig[v]!=a){
		par[v] = w; w = match[v];
		if(lab[w]==1) lab[w] = 0, q.push(w);
		orig[v] = orig[w] = a;
		v = par[w];
	}
}

void augment(ll v){
	while(v!=-1){
		int pv = par[v], nv = match[pv];
		match[v] = pv;
		match[pv] = v; v = nv;
	}
}

int bfs(ll root){
	memset(lab,-1LL,sizeof(lab));
	for(int i=0;i<=n;i++) orig[i] = i;
	q = queue<ll>();
	lab[root] = 0; q.push(root);
	while(!q.empty()){
		ll v = q.front(); q.pop();
		for(auto x:g[v]){
			if(lab[x]==-1){
				lab[x] = 1; par[x] = v;
				if(match[x]==-1){
					augment(x);
					return 1;
				}
				lab[match[x]] = 0;
				q.push(match[x]);
			}
			else if(lab[x]==0&&orig[x]!=orig[v]){
				ll a = lca(orig[x],orig[v]);
				blossom(x,v,a);
				blossom(v,x,a);
			}
		}
	}
	return 0;
}

int main(){
    fastio;
	memset(match,-1LL,sizeof(match));
	memset(aux,-1LL,sizeof(match));
	cin >> n >> m;
	for(int i=0;i<m;i++){
		ll x,y; cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	ll ans = 0;
	vector<ll> v;
	for(int i=1;i<=n;i++) v.push_back(i);
	for(auto x:v){
		if(match[x]==-1){
			for(auto y:g[x]){
				if(match[y]==-1){
					match[x] = y; match[y] = x;
					ans++;
					break;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(match[i]==-1&&bfs(i)) ans++;
	}
	cout << ans;
}
