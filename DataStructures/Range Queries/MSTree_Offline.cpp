template<class T> struct BIT {
	vector<T> bit, vals;

	void build() {
		vals.pb(0);
		sort(all(vals));
		vals.erase(unique(all(vals)),vals.end());
		bit.resize(sz(vals));
	}

	int getIdx(T k) {
		return ub(all(vals),k)-vals.begin()-1;
	}

	void upd(int k, T val) {
		k = getIdx(k);
		for ( ;k < sz(vals); k += (k&-k)) bit[k] += val;
	}

	T query(int k) {
		k = getIdx(k);
		T temp = 0;
		for (;k;k -= (k&-k)) temp += bit[k];
		return temp;
	}
};

template<class T, int SZ> struct mstree {
	BIT<T> val[SZ+10];

	void updPre(int x, int y) {
		x += 9, y += 9;
		for (int X = x; X <= SZ; X += X&-X) val[X].vals.pb(y);
	}

	void build() {
		F0R(i,SZ+10) val[i].build();
	}

	void upd(int x, int y, int t = 1) {
		x += 9, y += 9;
		for (int X = x; X <= SZ+10; X += X&-X) val[X].upd(y, t);
	}

	int query(int x, int y) {
		x += 9, y += 9;
		int t = 0;
		for (;x > 0; x -= x&-x) t += val[x].query(y);
		return t;
	}

	int query(int lox, int hix, int loy, int hiy) {
		if(lox > hix || loy > hiy) return 0;
		return query(hix,hiy)-query(lox-1,hiy)
			   -query(hix,loy-1)+query(lox-1,loy-1);
	}
};
