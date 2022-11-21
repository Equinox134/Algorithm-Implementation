struct point{
	ll x,y,p,q;
	point(): point(0,0,1,0){}
	point(ll x1, ll y1): point(x1,y1,1,0){}
	point(ll x1, ll y1, ll p1, ll q1): x(x1),y(y1),p(p1),q(q1){}
	bool operator<(const point& O) const {
		if(1LL*q*O.p!=1LL*p*O.q) return 1LL*q*O.p<1LL*p*O.q;
		if(x!=O.x) return x<O.x;
		return y<O.y;
	}
	bool operator>(const point& O) const {
		if(x==O.x) return y>O.y;
		return x>O.x;
	}
	bool operator<=(const point& O) const {
		if(x==O.x) return y<=O.y;
		return x<=O.x;
	}
	point operator-(const point&O) const {
		return point(x-O.x,y-O.y);
	}
};

ll ccw(point& a, point& b, point& c){
	ll x1=a.x, x2=b.x, x3=c.x;
	ll y1=a.y, y2=b.y, y3=c.y;
	ll tmp = 1LL*x1*y2+1LL*x2*y3+1LL*x3*y1;
	tmp = tmp-1LL*y1*x2-1LL*y2*x3-1LL*y3*x1;
	if(tmp>0) return 1;
	else if(tmp==0) return 0;
	else return -1;
}
