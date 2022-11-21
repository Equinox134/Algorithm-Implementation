//use essential.cpp
vector<point> convexhull(vector<point>& v){
	sort(v.begin(),v.end());
	for(ll i=1;i<v.size();i++){
		v[i].p = v[i].x - v[0].x;
		v[i].q = v[i].y - v[0].y;
	}
	sort(v.begin()+1,v.end());
	
	stack<ll> s;
	s.push(0); s.push(1);
	ll next = 2;
	
	while(next<v.size()){
		while(s.size()>=2){
			ll first,second;
			second = s.top(); s.pop();
			first = s.top();
			if(ccw(v[first],v[second],v[next])>0){
				s.push(second);
				break;
			}
		}
		s.push(next++);
	}
	
	vector<point> tmp;
	while(!s.empty()){
		tmp.push_back(v[s.top()]);
		s.pop();
	}
	reverse(tmp.begin(),tmp.end());
	return tmp;
}
