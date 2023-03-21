// use essential
vector<point> convexhull(vector<point> &p){
	ll n = p.size(),k=0;
	if(n<3) return p;
	if(n==3){
		if(ccw(p[0],p[1],p[2])<0) reverse(all(p));
		return p;
	}
	vector<point> H(2*n);
	sort(all(p));
	for(int i=0;i<n;i++){
		while(k>=2&&ccw(H[k-2],H[k-1],p[i])<=0) k--;
		H[k++] = p[i];
	}
	for(int i=n-1,t=k+1;i>0;i--){
		while(k>=t&&ccw(H[k-2],H[k-1],p[i-1])<=0) k--;
		H[k++] = p[i-1];
	}
	H.resize(k-1);
	return H;
}
