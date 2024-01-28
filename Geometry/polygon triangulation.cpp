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
#define INF 1e17
#define MAX 500010
#define SIZE 100010
#define MOD 1000000007

const double PI = atan2(0,-1);
const double EPS = 1e-10;

struct Point{
    double x,y;
    ll i;
    Point(){}
    Point(double x, double y): Point(x,y,0){}
    Point(double x, double y, ll i): x(x), y(y), i(i){}

    bool operator < (const Point&p) const {
        return y<p.y;
    }

    Point operator - (const Point&p) const {
        return Point(x-p.x,y-p.y);
    }

    bool half() const {
        return (y+EPS<0||(abs(y)<EPS&&x+EPS<0));
    }
};

ll sign(ll x){
    return (x>0)-(x<0);
}

ll ccw(Point a, Point b, Point c){
    double tmp = (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
    return sign(tmp);
}

double cury;

struct Edge{
    Point s,e;
    ll i;
    Edge(){}
    Edge(Point s, Point e): Edge(s,e,0){}
    Edge(Point s, Point e, ll i): s(s), e(e), i(i){}

    bool operator < (const Edge&p) const {
        double sy1 = 0, sy2 = 0;
        sy1 = (s.x*abs(cury-e.y)+e.x*abs(cury-s.y))/
        (abs(cury-e.y)+abs(cury-s.y));
        sy2 = (p.s.x*abs(cury-p.e.y)+p.e.x*abs(cury-p.s.y))/
        (abs(cury-p.e.y)+abs(cury-p.s.y));
        return sy1<sy2;
    }
};

vector<ll> pslg[200010];
ll type[200010],ch[200010];
Point help[200010];

struct Triangulate{
    vector<Point> pol;
    vector<vector<Point>> mono;

    Triangulate(vector<Point> p){
        pol = p;
    }

    void findfaces(){
        ll n = pol.size();
        vector<vector<int> > used(n);
        for(int i=0;i<n;i++){
            used[i].resize(pslg[i].size());
            used[i].assign(pslg[i].size(),0);
            auto cmp = [&](ll l, ll r){
                Point pl = pol[l]-pol[i];
                Point pr = pol[r]-pol[i];
                if(pl.half()!=pr.half()) return pl.half()<pr.half();
                return (pl.x*pr.y-pl.y*pr.x)>0;
            };
            sort(all(pslg[i]),cmp);
        }

        for(int i=0;i<n;i++){
            for(int id=0;id<(ll)pslg[i].size();id++){
                if(used[i][id]) continue;
                vector<Point> face;
                ll v = i, e = id;
                while(!used[v][e]){
                    used[v][e] = 1;
                    face.push_back(pol[v]);
                    ll u = pslg[v][e];
                    ll e1 = lower_bound(all(pslg[u]),v,[&](ll l, ll r){
                        Point pl = pol[l]-pol[u];
                        Point pr = pol[r]-pol[u];
                        if(pl.half()!=pr.half()) return pl.half()<pr.half();
                        return (pl.x*pr.y-pl.y*pr.x)>0;
                    }) - pslg[u].begin() + 1;
                    if(e1==(ll)pslg[u].size()) e1 = 0;
                    v = u;
                    e = e1;
                }
                if((ll)face.size()!=n) mono.emplace_back(face);
            }
        }
    }

    void addedge(vector<Point>& orig){
        ll n = orig.size();
        set<Edge> st;
        for(auto i:orig){
            cury = i.y;
            Point ni = pol[(i.i+1)%n];
            Point pi = pol[(i.i-1+n)%n];

            if(type[i.i]==0){
                // reg
                if(pi.y>i.y&&i.y>ni.y){
                    if(type[help[pi.i].i]==4){
                        pslg[i.i].push_back(help[pi.i].i);
                        pslg[help[pi.i].i].push_back(i.i);
                    }
                    st.erase(Edge(pi,i,pi.i));
                    st.insert(Edge(i,ni,i.i));
                    help[i.i] = i;
                }
                else{
                    auto it = st.lower_bound(Edge(i,i));
                    Edge e = *it;
                    if(type[help[e.i].i]==4){
                        pslg[i.i].push_back(help[e.i].i);
                        pslg[help[e.i].i].push_back(i.i);
                    }
                    help[e.i] = i;
                }
            }
            else if(type[i.i]==1){
                // start
                st.insert(Edge(i,ni,i.i));
                help[i.i] = i;
            }
            else if(type[i.i]==2){
                // split
                auto it = st.lower_bound(Edge(i,i));
                Edge e = *it;
                pslg[i.i].push_back(help[e.i].i);
                pslg[help[e.i].i].push_back(i.i);
                help[e.i] = i;
                help[i.i] = i;
                st.insert(Edge(i,ni,i.i));
            }
            else if(type[i.i]==3){
                // end
                if(type[help[pi.i].i]==4){
                    pslg[i.i].push_back(help[pi.i].i);
                    pslg[help[pi.i].i].push_back(i.i);
                }
                st.erase(Edge(pi,i,pi.i));
            }
            else if(type[i.i]==4){
                // merge
                if(type[help[pi.i].i]==4){
                    pslg[i.i].push_back(help[pi.i].i);
                    pslg[help[pi.i].i].push_back(i.i);
                }
                st.erase(Edge(pi,i,pi.i));
                auto it = st.lower_bound(Edge(i,i));
                Edge e = *it;
                if(type[help[e.i].i]==4){
                    pslg[i.i].push_back(help[e.i].i);
                    pslg[help[e.i].i].push_back(i.i);
                }
                help[e.i] = i;
            }
        }
    }

    void monotonize(){
        vector<Point> orig = pol;

        ll n = pol.size();
        for(int i=0;i<n;i++){
            pslg[i].clear();
        }
        for(int i=0;i<n;i++){
            Point cur = pol[i];
            Point prv = pol[(i-1+n)%n], nxt = pol[(i+1)%n];
            pslg[cur.i].push_back(prv.i);
            pslg[cur.i].push_back(nxt.i);

            Point nv = nxt-cur, pv = prv-cur;
            double dot = nv.x*pv.x+nv.y*pv.y;
            double det = nv.x*pv.y-nv.y*pv.x;
            double ang = atan2(det,dot);

            if((nxt.y<cur.y&&cur.y<prv.y)||(prv.y<cur.y&&cur.y<nxt.y)) type[cur.i] = 0; //reg
            else if(cur.y>nxt.y&&cur.y>prv.y){
                if(ang<0) type[cur.i] = 1; // start
                else type[cur.i] = 2; // split
            }
            else if(cur.y<nxt.y&&cur.y<prv.y){
                if(ang<0) type[cur.i] = 3; // end
                else type[cur.i] = 4; // merge
            }
        }

        sort(orig.rbegin(),orig.rend());

        addedge(orig);

        findfaces();
        if(mono.empty()) mono.push_back(pol);
    }

    void monotri(vector<Point>& u){
        ll id = 0, n = (ll)u.size();
        double mx = -1e300;
        for(int i=0;i<n;i++){
            if(u[i].y>mx){
                mx = u[i].y;
                id = i;
            }
        }
        ch[u[id].i] = 0;
        ll f = 0;
        for(int i=0,t=(id+1)%n;i<n-1;i++,t=(t+1)%n){
            if(u[t].y<u[(t+1)%n].y&&u[t].y<u[(t-1+n)%n].y){
                ch[u[t].i] = 0; 
                f = 1;
                continue;
            }
            if(!f) ch[u[t].i] = 1;
            else ch[u[t].i] = -1;
        }

        sort(u.rbegin(),u.rend());
        stack<Point> st;
        st.push(u[0]); st.push(u[1]);
        for(int i=2;i<n-1;i++){
            Point v = st.top();
            if(ch[u[i].i]!=ch[v.i]&&ch[u[i].i]!=0){
                while(st.size()>1){
                    pslg[st.top().i].push_back(u[i].i);
                    pslg[u[i].i].push_back(st.top().i);
                    st.pop();
                }
                st.pop();
                st.push(u[i-1]); st.push(u[i]);
            }
            else{
                st.pop();
                while(!st.empty()&&ch[u[i].i]*ccw(u[i],v,st.top())>0){
                    pslg[st.top().i].push_back(u[i].i);
                    pslg[u[i].i].push_back(st.top().i);
                    v = st.top();
                    st.pop();
                }
                st.push(v); st.push(u[i]);
            }
        }
        st.pop();
        while(st.size()>1){
            pslg[st.top().i].push_back(u[n-1].i);
            pslg[u[n-1].i].push_back(st.top().i);
            st.pop();
        }
        st.pop();
    }

    void triangulate(){
        monotonize();
        for(auto i:mono){
            monotri(i);
        }
    }
};

int main(){
    fastio;
    ll n; cin >> n;
    vector<Point> inp;
    for(int i=0;i<n;i++){
        double x,y; cin >> x >> y;
        inp.push_back(Point(x,y,i));
    }
    Triangulate tri = Triangulate(inp);
    tri.triangulate();

    for(int i=0;i<n;i++){
        for(auto j:pslg[i]){
            if(j==(i+1)%n||j==(i-1+n)%n) continue;
            cout << j+1 << " ";
        }
        cout << "\n";
    }
}
