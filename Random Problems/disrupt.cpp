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

const int MAXN = 5e4+5;

struct Node {
	set<pair<int, int>>* nums;
	vector<pair<int, int>> cNums;
	int idx;
	vector<Node*> c;
};
Node nodes[MAXN];
int ans[MAXN];
map<pair<int, int>, int> mp;
void dfs(Node* curr, Node* par) {
	Node* largest = nullptr;
	for(auto node: curr->c) {
		if(node == par) continue;
		dfs(node, curr);
		if(!largest || node->nums->size() > largest->nums->size())
			largest = node;
	}
	if(par == nullptr)
		return;
	if(!largest)
		curr->nums = new set<pair<int,int>>;
	else
		curr->nums = largest->nums;
	for(auto node: curr -> c) {
		if(node == par) continue;
		if (node != largest)
			for (auto element: *(node->nums)) {
				if (curr->nums->count(element))
					curr->nums->erase(element);
				else
					curr->nums->insert(element);
			}
	}
	for(auto element: curr->cNums) {
		if(curr->nums->count(element))
			curr->nums->erase(element);
		else
			curr->nums->insert(element);
	}
	int a = curr->idx, b = par->idx;
	if(a > b) swap(a, b);
	if(curr->nums->empty())
		ans[mp[{a, b}]] = -1;
	else
		ans[mp[{a, b}]] = (*(curr->nums->begin())).f;
}
int main() {
	FAST_IO;
	freopen("disrupt.in", "r", stdin);
	freopen("disrupt.out", "w", stdout);
	int n, m; cin >> n >> m;
	F0R(i, n)
		nodes[i].idx = i;
	F0R(i, n-1) {
		int a, b; cin >> a >> b, a--, b--;
		if(a > b) swap(a, b);
		mp[{a, b}] = i;
		nodes[a].c.pb(&nodes[b]);
		nodes[b].c.pb(&nodes[a]);
	}
	F0R(i, m) {
		int a, b, c; cin >> a >> b >> c, a--, b--;
		nodes[a].cNums.pb({c, i});
		nodes[b].cNums.pb({c, i});
	}
	dfs(&nodes[0], nullptr);
	F0R(i, n-1) cout << ans[i] << '\n';
}

//Remember to change MAXN if relevant!!!
