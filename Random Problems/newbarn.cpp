#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<double, double> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

template<class T, class U>
inline void MAX(T &a, U b) { if (a < b) a = b; }

template<class T, class U>
inline void MIN(T &a, U b) { if (a > b) a = b; }

template<class T, class U>
inline void MODA(T &a, U b) {
	a %= b;
	if (a < 0) a += b;
}

#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(20)
#define dbg(x) cout << (#x) << " is " << (x) << '\n'
#define dbg2(x, y) cout << (#x) << " is " << (x) << " and " << (#y) << " is " << y << '\n'
#define dbgarr(x, sz) for(int asdf = 0; asdf < (sz); asdf++) cout << x[asdf] << ' '; cout << '\n'
#define dbgarr2(x, rose, colin) for(int asdf2 = 0; asdf2 < rose; asdf2++) { dbgarr(x[asdf2], colin); }
#define dbgitem(x) for(auto asdf = x.begin(); asdf != x.end(); asdf++) cout << *asdf << ' '; cout << '\n'
#define finish(x) return cout << (x) << '\n', 0
#define F0R(i, a) for(int (i)=0;(i)<(a);++(i))
#define FOR(i, a, b) for(int (i)=(a);(i)<(b);++(i))
#define F0Rd(i, a) for(int (i)=a;(i)>=0;--(i))
#define FORd(i, a, b) for(int (i)=a;(i)>=(b);--(i))
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

template <typename T> ostream& operator<<(ostream& os, const vector<T> &p){os << "["; F0R(i, p.size()) os << p[i] << (i == p.size() - 1 ? "" : ",") ; os << "]"; return os;}
template <typename T> ostream& operator<<(ostream& os, const set<T> &p){os << "{ "; for (T x: p) os << x << " "; os << "}"; return os;}
template <typename T> ostream& operator<<(ostream& os, const multiset<T> &p){os << "{ "; for (T x: p) os << x << " "; os << "}"; return os;}
template <typename T, typename U> ostream& operator<<(ostream& os, const pair<T, U> &p){os << '{' << p.first << ',' << p.second << '}'; return os;}

#define pb push_back
#define pf push_front
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const double EPS = 1e-9;
const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const int NINF = -0x3f3f3f40;
const ll INF_L = 0x3f3f3f3f3f3f3f3f;
const ll NINF_L = -0x3f3f3f3f3f3f3f40;

const int MAXN = 1e5+5;

struct tree {
	pi h1 = {0, -2}, h2 = {0, -2};

};

struct tnode {
	int d, tid, u_par;
	tnode(int _d, int _tid, int _u_par) {
		d = _d;
		tid = _tid;
		u_par = _u_par;
	}
};

struct node {
	vi ch;
	bool used = false; //used as a centroid
	int sz = 1;
	vector<tnode> tn; //the trees that the node is in
};

node nodes[MAXN];
tree trees[MAXN];

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

void dfs_depth(int cur, int par, int tid, int d, int u_par) {
	if(d == 1) u_par = cur;
	nodes[cur].tn.pb(tnode(d, tid, u_par));
	for(int no: nodes[cur].ch) {
		if(no == par || nodes[no].used) continue;
		dfs_depth(no, cur, tid, d+1, u_par);
	}
}

void make_tree(int top, int par) {
	dfs_size(top, par);
	int c = find_cent(top, par, nodes[top].sz);
	nodes[c].used = true;
	dfs_depth(c, -1, c, 0, -1);
	for(int node: nodes[c].ch)
		if(!nodes[node].used)
			make_tree(node, c);
}

int main() {
	FAST_IO;
	freopen("newbarn.in", "r", stdin);
	freopen("newbarn.out", "w", stdout);
	int q; cin >> q;
	vector<pair<char, int>> queries;
	vi roots;
	int n = 0;
	F0R(i, q) {
		char a; int b; cin >> a >> b, b--;
		queries.pb({a, b});
		if(a == 'B') {
			if(b == -2)
				roots.pb(n++);
			else {
				nodes[n].ch.pb(b);
				nodes[b].ch.pb(n);
				n++;
			}
		}
	}
	for(auto no: roots)
		make_tree(no, -1);
	int curr = 0;
	for(auto query: queries) {
		int ans = 0;
		int v = curr;
		if(query.f == 'B') {
			for(auto no: nodes[v].tn) {
				tree& cTree = trees[no.tid];
				pi cpair = {no.d, no.u_par};
				if(cpair.f > cTree.h2.f) {
					if(cpair.s == cTree.h1.s)
						MAX(cTree.h1.f, cpair.f);
					else {
						cTree.h2 = cpair;
						if (cTree.h2.f > cTree.h1.f)
							swap(cTree.h1, cTree.h2);
					}
				}
			}
			curr++;
		} else {
			for(auto no: nodes[query.s].tn) {
				tree& cTree = trees[no.tid];
				if(no.tid >= curr) continue;
				if(no.u_par == cTree.h1.s)
					MAX(ans, no.d+cTree.h2.f);
				else
					MAX(ans, no.d+cTree.h1.f);
			}
			cout << ans << '\n';
		}
	}
}

//Remember to change MAXN if relevant!!!
