template<int SZ> struct DSU {
	int par[SZ], ranks[SZ];

	DSU() {
		iota(par, par + SZ, 0);
	}
	
	int find(int curr) {
		return par[curr] == curr ? curr : (par[curr] = find(par[curr]));
	}

	void unite(int n1, int n2) {
		int f1 = find(n1);
		int f2 = find(n2);
		if(ranks[f1] > ranks[f2]) {
			par[f2] = f1;
			ranks[f1]++;
		} else {
			par[f1] = f2;
			ranks[f2]++;
		}
	}
};
