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

const int MAXN = 55;

class Node {
public:
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
	bool overlaps(int a, int b, int c, int d) {
		return b >= c && a <= d;
	}
	int getMid(int l, int r) {
		return ((l+r) < 0) ? (l+r-1)/2:(l+r)/2;
	}
	void update(int idx, int v, int l = 0, int r = 1e9+5) {
		if(l == r) {
			val = v;
			return;
		}
		int mid = getMid(l, r);
		if(idx <= mid)
			getC(0) -> update(idx, v, l, mid);
		else
			getC(1) -> update(idx, v, mid + 1, r);
		val = min(c[0] ? c[0] -> val : INF, c[1] ? c[1] -> val : INF);
	}
	int query(int a, int b, int l = 0, int r = 1e9+5) {
		if(l >= a && r <= b)
			return val;
		if(l > b || r < a)
			return INF;
		int mid = getMid(l, r);
		int res = (c[0] ? c[0] -> query(a, b, l, mid) : INF);
		res = min(res, c[1] ? c[1] -> query(a, b, mid+1, r) : INF);
		return res;
	}
};

struct sling {
	int x, y, z, ans;
};

Node seg[8];
int main() {
	FAST_IO;
	int n, m; cin >> n >> m;
	sling sl[n];
	F0R(i, n) cin >> sl[i].x >> sl[i].y >> sl[i].z;
	sling q[n];
	F0R(i, m) {
		cin >> q[i].x >> q[i].y;
		q[i].z = -1;
	}
	vector<sling*> ss[2]; // handle diff directions separate
	F0R(i, n) {
		if(sl[i].x < sl[i].y)
			ss[0].pb(&sl[i]);
		else {
			swap(sl[i].x, sl[i].y);
			ss[1].pb(&sl[i]);
		}
	}
	F0R(i, m) {
		if(q[i].x < q[i].y)
			ss[0].pb(&q[i]);
		else {
			swap(q[i].x, q[i].y);
			ss[1].pb(&q[i]);
		}
	}
	F0R(i, 2) {
		F0R(j, 4) {
			for(auto cSl: ss[i]) {
				if(cSl->z == -1) {
					cSl->ans = min(cSl->y - cSl->x, seg[])
				} else {

				}
			}
		}
	}
}

//Remember to change MAXN if relevant!!!
