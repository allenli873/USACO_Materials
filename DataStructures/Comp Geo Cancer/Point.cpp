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
