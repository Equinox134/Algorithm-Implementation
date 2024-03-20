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
#define MAX 200010
#define SIZE 100010
 
# pragma GCC optimize ("O3")
//# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")
 
const double PI = atan2(0,-1);
const double PI2 = PI/2;
const double PI3 = PI*3/2;
 
struct Circle{
	ll x,y,r;
	ll idx,aidx;
	Circle(){}
	Circle(ll x, ll y, ll r, ll idx, ll aidx): x(x), y(y), r(r), idx(idx), aidx(aidx) {}
	bool operator < (const Circle&C) const {
		if(y+r!=C.y+C.r) return y+r>C.y+C.r;
		if(y!=C.y) return y>C.y;
		if(x!=C.x) return x<C.x;
		return r>C.r;
	}
	bool operator == (const Circle&C) const {
		return x==C.x&&y==C.y&&r==C.r;
	}
	bool operator != (const Circle&C) const {
		return x!=C.x||y!=C.y||r!=C.r;
	}
};
 
struct SupLine{
	Circle c;
	double th;
};
 
typedef vector<Circle> VC;
 
int ccw(pdd a, pdd b, pdd c){
	double k = (b.ff-a.ff)*(c.ss-a.ss)-(c.ff-a.ff)*(b.ss-a.ss);
	if(abs(k)<=1e-10) k = 0;
	return (k>0)-(k<0);
}
 
double norm(double a){
	if(abs(a)<1e-10) a = 0;
	while(a<0) a+=2*PI;
	while(a+1e-10>=2*PI) a-=2*PI;
	if(abs(a)<1e-10) a = 0;
	return a;
}
 
int same(double a, double b){
	return (abs(a-b)<=1e-10);
}
 
double r2d(double a){
	return a*180/PI;
}
 
double alpha(SupLine l1, SupLine l2){
	double th = l2.th - l1.th;
	th = norm(th);
	return th;
}
 
bool dom(SupLine p, SupLine q){
	if(!(abs(p.th-q.th)<=1e-10)) return false;
	Circle c1 = p.c, c2 = q.c;
	double th1 = p.th, th2 = q.th;
	double sn1 = sin(th1), cs1 = cos(th1);
	double x1 = c1.x+c1.r*sn1, y1 = c1.y+c1.r*cs1;
	double x2 = c2.x+c2.r*sn1, y2 = c2.y+c2.r*cs1;
	double nx = x1+cs1, ny = y1-sn1;
	int k = ccw({nx,ny},{x1,y1},{x2,y2});
	return k>=0;
}
 
void add(vector<ll> &v, ll c, ll &sz){
	if(sz==0){
		v.emplace_back(c);
		sz++;
		return;
	}
	if(v[sz-1]==c) return;
	v.emplace_back(c);
	sz++;
}
 
Circle C = Circle();
 
SupLine L(Circle a, Circle b){
	if(a==b) return {C,1000};
	double d = hypot(a.x-b.x,a.y-b.y);
	if(d<=abs(a.r-b.r)) return {C,-1000};
	double th1 = acos((a.r-b.r)/d);
	double th2 = -atan2(b.y-a.y,b.x-a.x);
	double th = th2;
	th += PI2-th1;
	th = norm(th);
	return {a,th};
}
 
SupLine Ls;
bool f = false;
ll cnt;
ll sx,sy,cx,cy,szs;
VC inp;
 
void Advance(vector<ll> &S, vector<ll> &X, vector<ll> &Y, Circle x, Circle y){
	SupLine l1 = L(x,y), l2 = L(y,x);
	SupLine ls1 = L(x,inp[X[(cx+1)%sx]]), ls2 = L(y,inp[Y[(cy+1)%sy]]);
	double a1,a2,a3,a4;
	a1 = alpha(Ls,l1); a2 = alpha(Ls,ls1);
	a3 = alpha(Ls,ls2); a4 = alpha(Ls,l2);
	if(ls1.th>500) a2 = 1000; if(ls1.th<-500) a2 = 2000;
	if(ls2.th>500) a3 = 1000; if(ls2.th<-500) a3 = 2000;
	
//	cout << x.aidx << " " << y.aidx << "\n";
//	cout << r2d(a1) << " " << r2d(a2) << " " << r2d(a3) << " " << r2d(a4) << "\n";
	
	if(l1.th>=0){
		if(a1<a2&&a1<a3){
			add(S,y.idx,szs);
			if(szs>=4&&S[0]==S[szs-2]&&S[1]==S[szs-1]) f = true;
			else if(a4<a2&&a4<a3&&abs(a4)>1e-10){
				add(S,x.idx,szs);
				if(szs>=4&&S[0]==S[szs-2]&&S[1]==S[szs-1]) f = true;
			}
		}
	}
	
	if(a2<a3){
		if(ls1.th>500) Ls = {x,Ls.th};
		else Ls = ls1;
		cx = (cx+1)%sx;
	}
	else{
		if(ls2.th>500) Ls = {y,Ls.th};
		else Ls = ls2;
		cy = (cy+1)%sy;
	}
}
 
vector<ll> Merge(ll s, ll e){
	vector<ll> S,P,Q;
	if(s==e){
		S.push_back(s);
		return S;
	}
	ll m = (s+e)>>1;
	P = Merge(s,m); Q = Merge(m+1,e);
	//cout << s << " " << e << "\n";
	Ls = {Circle(),0};
	SupLine Lp = {inp[P[0]],0}, Lq = {inp[Q[0]],0};
	ll sz = 0; 
	ll sp = P.size(), sq = Q.size();
	ll curp = 0, curq = 0, iter = 0;
	
//	for(auto i:P)cout << inp[i].aidx << " "; cout << "\n";
//	for(auto i:Q)cout << inp[i].aidx << " "; cout << "\n";
	
	while(1){
		++iter;
		f = false;
		Circle p = inp[P[curp]], q = inp[Q[curq]];
		if(dom(Lp,Lq)){
			add(S,p.idx,sz);
			if(sz>=4&&S[0]==S[sz-2]&&S[1]==S[sz-1]) break;
			sx = sp; sy = sq; cx = curp; cy = curq; szs = sz;
			Advance(S,P,Q,p,q);
			curp = cx; curq = cy; sz = szs;
		}
		else{
			add(S,q.idx,sz);
			if(sz>=4&&S[0]==S[sz-2]&&S[1]==S[sz-1]) break;
			sx = sq; sy = sp; cx = curq; cy = curp; szs = sz;
			Advance(S,Q,P,q,p);
			curq = cx; curp = cy; sz = szs;
		}
		
		p = inp[P[curp]]; q = inp[Q[curq]];
		Lp = {p,Ls.th}; Lq = {q,Ls.th};
		if(iter>=2*(sp+sq)) break;
		if(f||sz>=4&&S[0]==S[sz-2]&&S[1]==S[sz-1]) break;
		//for(auto i:S) cout << inp[i].aidx << " "; cout << "\n";
	}
	if(sz>=4&&S[0]==S[sz-2]&&S[1]==S[sz-1]){
		S.pop_back(); S.pop_back();
		sz -= 2;
	}
//	int flag = 0;
//	for(auto i:S){
//		cout << inp[i].aidx << " ";
//		if(inp[i].aidx==45946) flag = 1;
//	}
//	cout << "\n\n";
	//if(cnt>210000) cout << cnt,exit(0);
	return S;
}
 
vector<double> va;
 
void solve(){
	inp.clear();
	ll n; cin >> n;
	VC chS;
	for(int i=0;i<n;i++){
		ll x,y,r; cin >> x >> y >> r;
		inp.push_back(Circle(x,y,r,0,i));
	}
 
	sort(all(inp));
	compress(inp);
	for(int i=0;i<inp.size();i++) inp[i].idx = i;
	vector<ll> res = Merge(0,inp.size()-1);
	if(res.size()>1) res.push_back(res[0]);
	for(auto i:res) chS.push_back(inp[i]);
	reverse(all(chS));
	//for(auto i:chS) cout << i.aidx << " "; cout << "\n";
	chS.pop_back();
	ll sz = chS.size();
	double ang = 0, ans = 0;
	for(int i=0;i<sz;i++){
		int j = (i+1)%sz;
		Circle a = chS[i], b = chS[j];
		double d = hypot(a.x-b.x,a.y-b.y);
		double t1 = acos((a.r-b.r)/d);
		double t2 = atan2(b.y-a.y,b.x-a.x);
		double na = t2-PI2-t1;
		//cout << norm(2*PI) << "\n";
		na = norm(na);
		if(na<ang&&na==0) na = 2*PI;
		ans += a.r*(na-ang);
		ans += sqrt(d*d-(a.r-b.r)*(a.r-b.r));
		ang = na;
	}
	ans += chS[0].r*(2*PI-ang);
	va.push_back(ans);
}
 
int main(){
	fastio;
	ll t=1; //cin >> t;
	while(t--) solve();
	cout.precision(10);
	for(auto i:va) cout << fixed << i << "\n";
}
//https://www.acmicpc.net/problem/27957
