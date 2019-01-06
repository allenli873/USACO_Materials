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

#define mp make_pair
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

int deg[MAXN], constrained[MAXN], good[MAXN];
vi adj[MAXN], constrains[MAXN];
bool vis[MAXN], constraining[MAXN];

void dfs(int curr, int par) {
	if(constraining[curr]) return;
	good[curr] = 1;
	for(auto node: adj[curr]) {
		if(node == par)
			continue;
		dfs(node, curr);
	}
}

int main() {
	FAST_IO;
	freopen("gathering.in", "r", stdin);
	freopen("gathering.out", "w", stdout);
	int n, m; cin >> n >> m;
	F0R(i, n-1) {
		int a, b; cin >> a >> b, a--, b--;
		adj[a].pb(b);
		adj[b].pb(a);
		deg[a]++; deg[b]++;
	}
	F0R(i, m) {
		int a, b; cin >> a >> b, a--, b--;
		constrains[a].pb(b);
		constrained[b]++;
		constraining[a] = true;
	}
	int root = -1;
	queue<int> q;
	F0R(i, n) {
		if(!constrained[i] && deg[i] == 1)
			q.push(i);
	}
	while(!q.empty()) {
		int curr = q.front(); q.pop();
		if(vis[curr]) continue;
		vis[curr] = true;
		if(deg[curr] == 0) {
			root = curr;
			break;
		}
		for(auto node: adj[curr]) {
			deg[node]--;
			if(deg[node] == 1 && !constrained[node])
				q.push(node);
		}
		for(auto node: constrains[curr]) {
			constrained[node]--;
			if(deg[node] == 1 && !constrained[node])
				q.push(node);
		}
	}
	if(root == -1) {
		F0R(i, n) cout << 0 << '\n';
		return 0;
	}
	dfs(root, -1);
	F0R(i, n) cout << good[i] << '\n';
}

//Remember to change MAXN if relevant!!!
