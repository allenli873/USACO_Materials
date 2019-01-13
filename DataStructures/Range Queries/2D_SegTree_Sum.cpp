//segtree constants
const int LB = -5, UB = 1e5+5;
class Node_Inner {
public:
	int val;
	Node_Inner* c[2];

	Node_Inner() {
		val = 0;
		c[0] = c[1] = nullptr;
	}

	Node_Inner* getC(int x) {
		if(!c[x])
			c[x] = new Node_Inner();
		return c[x];
	}
	int getMid(int l, int r) {
		return ((l+r) < 0) ? (l+r-1)/2:(l+r)/2;
	}
	void update(int idx, int v, int l = LB, int r = UB) {
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
	int query(int a, int b, int l = LB, int r = UB) {
		if(l >= a && r <= b)
			return val;
		if(l > b || r < a)
			return 0;
		int mid = getMid(l, r);
		int res = (c[0] ? c[0] -> query(a, b, l, mid) : 0);
		res += (c[1] ? c[1] -> query(a, b, mid+1, r) : 0);
		return res;
	}
	void inUpdate(int idx, Node_Inner* c0, Node_Inner* c1, int l = LB, int r = UB) {
		if(l != r) {
			int mid = getMid(l, r);
			if(idx <= mid)
				getC(0) -> inUpdate(idx, c0 ? c0 -> c[0] : nullptr, c1 ? c1 -> c[0] : nullptr, l, mid);
			else
				getC(1) -> inUpdate(idx, c0 ? c0 -> c[1] : nullptr, c1 ? c1 -> c[1] : nullptr, mid+1, r);
		}
		val = (c0 ? c0 -> val : 0) + (c1 ? c1 -> val : 0);
	}
};

class Node_Outer {
public:
	Node_Inner *node;
	Node_Outer *c[2];

	Node_Outer() {
		node = new Node_Inner();
		c[0] = c[1] = nullptr;
	}

	Node_Outer *getC(int x) {
		if (!c[x])
			c[x] = new Node_Outer();
		return c[x];
	}

	int getMid(int l, int r) {
		return ((l + r) < 0) ? (l + r - 1) / 2 : (l + r) / 2;
	}

	void update(int x, int y, int v, int lx = LB, int rx = UB, int ly = LB, int ry = UB) {
		if (lx == rx && lx == x) {
			node->update(y, v, ly, ry);
			return;
		}
		int mid = getMid(lx, rx);
		if (x <= mid)
			getC(0)->update(x, y, v, lx, mid, ly, ry);
		else
			getC(1)->update(x, y, v, mid + 1, rx, ly, ry);
		node->inUpdate(y, c[0] ? c[0] -> node : nullptr, c[1] ? c[1] -> node : nullptr);
	}

	int query(int qlx, int qrx, int qly, int qry, int lx = LB, int rx = UB, int ly = LB, int ry = UB) {
		if (lx >= qlx && rx <= qrx)
			return node->query(qly, qry, ly, ry);
		if (lx > qrx || rx < qlx)
			return 0;
		int mid = getMid(lx, rx);
		int res = c[0] ? c[0]->query(qlx, qrx, qly, qry, lx, mid, ly, ry) : 0;
		res += c[1] ? c[1]->query(qlx, qrx, qly, qry, mid + 1, rx, ly, ry) : 0;
		return res;
	}
};
