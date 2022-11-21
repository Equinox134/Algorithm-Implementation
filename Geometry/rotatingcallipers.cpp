//use essential.cpp and convexhull.cpp
//returns maximum distance between points
ll mdist(ll d){
	vector<point> p;
	p.resize(n);
	for(int i=0;i<n;i++){
		point pt = st[i].p;
		ll vx = st[i].vx, vy = st[i].vy;
		p[i] = point(pt.x+vx*d,pt.y+vy*d);
	}
	vector<point> ch = convexhull(p);
	
	ll ret = 0,c=1;
	ll size = ch.size();
	for(ll a=0;a<size;a++){
		ll b = (a+1)%size;
		while(1){
			ll d = (c+1)%size;
			
			point zero;
			point ab = ch[b] - ch[a];
			point cd = ch[d] - ch[c];
			
			if(ccw(zero,ab,cd)>0) c = d;
			else break;
		}
		ret = max(ret,dist(ch[a],ch[c]));
	}
	
	return ret;
}
