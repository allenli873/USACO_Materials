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

const int MAXN = 2e5+5;

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

mstree<ll, MAXN> st;
int main() {
	FAST_IO;
	freopen("friendcross.in", "r", stdin);
	freopen("friendcross.out", "w", stdout);
	int n, k; cin >> n >> k;
	int left[n], right[n];
	int pos[n], mapper[n];
	F0R(i, n) {
		cin >> left[i], left[i]--;
		mapper[left[i]] = i;
	}
	F0R(i, n) {
		cin >> right[i], right[i]--;
		pos[mapper[right[i]]] = i;
	}
	ll res = 0;
	F0R(i, n) st.updPre(pos[i]+1, left[i]);
	st.build();
	F0R(i, n) {
		res += st.query(pos[i]+1, n, 0, left[i] - k - 1) + st.query(pos[i]+1, n, left[i] + k + 1, n);
		st.upd(pos[i]+1, left[i]);
	}
	cout << res << '\n';
}

//Remember to change MAXN if relevant!!!
