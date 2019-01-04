struct point {
	int x, y;
	point() { x = y = 0; }
	point(int _x, int _y) : x(_x), y(_y) {}
	bool operator < (point o) const {
		if(x != o.x)
			return x < o.x;
		return y < o.y;
	}
};
struct point_d {
	double x, y;
	point_d() { x = y = 0.0; }
	point_d(double _x, double _y) : x(_x), y(_y) {}
	bool operator < (point o) const {
		if(abs(x - o.x) > EPS)
			return x < o.x;
		return y < o.y;
	}
};
