struct node {
	vi ch;
	bool used = false; //used as a centroid
	int sz = 1;
};

node nodes[MAXN];

void dfs_size(int cur, int par) {
	nodes[cur].sz = 1;
	for(int node: nodes[cur].ch) {
		if(node == par || nodes[node].used) continue;
		dfs_size(node, cur);
		nodes[cur].sz += nodes[node].sz;
	}
}

int find_cent(int cur, int par, int sz) {
	for(int node: nodes[cur].ch) {
		if(node == par || nodes[node].used) continue;
		if(nodes[node].sz * 2 >= sz)
			return find_cent(node, cur, sz);
	}
	return cur;
}

void make_tree(int top, int par) {
	dfs_size(top, par);
	int c = find_cent(top, par, nodes[top].sz);
	nodes[c].used = true;
	for(int node: nodes[c].ch)
		if(!nodes[node].used)
			make_tree(node, c);
}
