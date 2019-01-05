//structs
template<class Type> struct vec {
	Type x, y;
	vec(Type _x, Type _y) : x(_x), y(_y) {}
	Type dot(vec o) const {
		return x * o.x + y * o.y;
	}
	Type cross(vec o) const {
		return x * o.y - y * o.x;
	}
};
struct point {
	int x, y;
	point() { x = y = 0; }
	point(int _x, int _y) : x(_x), y(_y) {}
	bool operator < (point o) const {
		if(x != o.x)
			return x < o.x;
		return y < o.y;
	}
	vec<int> toVec(point o) const {
		return vec<int>(o.x - x, o.y - y);
	}
	double dist(point o) const {
		return hypot(x - o.x, y - o.y);
	}
};
struct point_d {
	double x, y;
	point_d() { x = y = 0.0; }
	point_d(double _x, double _y) : x(_x), y(_y) {}
	bool operator < (point o) const {
		if(abs(x-o.x) > EPS)
			return x < o.x;
		return y < o.y;
	}
	vec<double> toVec(point o) const {
		return vec<double>(o.x - x, o.y - y);
	}
	double dist(point o) const {
		return hypot(x - o.x, y - o.y);
	}
};
//useful methods
bool ccw(point a, point b, point c) {
	return (a.toVec(b)).cross(a.toVec(c)) >= 0; //watch out for collinear case (>= or >)
}
bool collinear(point a, point b, point c) {
	return abs((a.toVec(b)).cross(a.toVec(c))) < EPS;
}
vector<point> convexHull(vector<point>& points) {
	int N = points.size();
	sort(all(points));
	vector<point> res;
	//upper hull
	F0R(i, N) {
		while(res.size() >= 2 && ccw(res[res.size() - 2], res[res.size() - 1], points[i]))
			res.erase(res.end() - 1);
		res.pb(points[i]);
	}
	//lower hull
	int half = res.size();
	F0Rd(i, N-2) {
		while(res.size() > half && ccw(res[res.size() - 2], res[res.size() - 1], points[i]))
			res.erase(res.end() - 1);
		res.pb(points[i]);
	}
	res.erase(res.end() - 1);
	return res;
}
