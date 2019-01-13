template<int SZ> struct mstree {
	ordered_set<int> val[SZ+1];

	void update(int x, int y, int t = 1) {
		for (int X = x; X <= SZ; X += X&-X) {
			if (t == 1) val[X].insert(y);
			else val[X].erase(y);
		}
	}

	int query(int x, int y) {
		int t = 0;
		while(x > 0) {
			t += val[x].order_of_key(y+1);
			x -= x&-x;
		}
		return t;
	}

	int query(int lx, int rx, int ly, int ry) {
		return query(rx,ry)-query(lx-1,ry)-query(rx,ly-1)+query(lx-1,ly-1);
	}
};
