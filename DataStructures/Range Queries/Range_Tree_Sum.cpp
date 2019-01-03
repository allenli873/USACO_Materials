class Node {
public:
	int SZ = 1 << 20;
	int val;
	Node* c[2];

	Node() {
		val = 0;
		c[0] = c[1] = nullptr;
	}

	Node* getC(int x) {
		if(!c[x])
			c[x] = new Node();
		return c[x];
	}
	int getMid(int l, int r) {
		return ((l+r) < 0) ? (l+r-1)/2:(l+r)/2;
	}
	void update(int idx, int v, int l, int r) {
		if(l == r) {
			val += v;
			return;
		}
		int mid = getMid(l, r);
		if(idx <= mid)
			getC(0) -> update(idx, v, l, mid);
		else
			getC(1) -> update(idx, v, mid + 1, r);
		val = (c[0] ? c[0] -> val : 0) + (c[1] ? c[1] -> val : 0);
	}
	int query(int a, int b, int l, int r) {
		if(l >= a && r <= b)
			return val;
		if(l > b || r < a)
			return 0;
		int mid = getMid(l, r);
		int res = (c[0] ? c[0] -> query(a, b, l, mid) : 0);
		res += (c[1] ? c[1] -> query(a, b, mid+1, r) : 0);
		res %= MOD;
		return res;
	}
};
