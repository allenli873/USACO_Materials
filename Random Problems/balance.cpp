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

const int MAXN = 55;

//structs
template<class Type> struct vec {
	Type x, y;
	vec(Type _x, Type _y) : x(_x), y(_y) {}
	Type dot(vec o) const {
		return x * o.x + y * o.y;
	}
	Type cross(vec o) const {
		return x * o.y - y * o.x;
	}
};
struct point {
	ll x, y;
	point() { x = y = 0; }
	point(ll _x, ll _y) : x(_x), y(_y) {}
	bool operator < (point o) const {
		if(x != o.x)
			return x < o.x;
		return y < o.y;
	}
	vec<ll> toVec(point o) const {
		return vec<ll>(o.x - x, o.y - y);
	}
	double dist(point o) const {
		return hypot(x - o.x, y - o.y);
	}
};
struct point_d {
	double x, y;
	point_d() { x = y = 0.0; }
	point_d(double _x, double _y) : x(_x), y(_y) {}
	bool operator < (point o) const {
		if(abs(x-o.x) > EPS)
			return x < o.x;
		return y < o.y;
	}
	vec<double> toVec(point o) const {
		return vec<double>(o.x - x, o.y - y);
	}
	double dist(point o) const {
		return hypot(x - o.x, y - o.y);
	}
};
//useful methods
bool ccw(point a, point b, point c) {
	return (a.toVec(b)).cross(a.toVec(c)) >= 0; //watch out for collinear case (>= or >)
}
bool collinear(point a, point b, point c) {
	return abs((a.toVec(b)).cross(a.toVec(c))) < EPS;
}
vector<point> convexHull(vector<point>& points) {
	int N = points.size();
	sort(all(points));
	vector<point> res;
	//upper hull
	F0R(i, N) {
		while(res.size() >= 2 && ccw(res[res.size() - 2], res[res.size() - 1], points[i]))
			res.erase(res.end() - 1);
		res.pb(points[i]);
	}
	//lower hull
//	int half = res.size();
//	F0Rd(i, N-2) {
//		while(res.size() > half && ccw(res[res.size() - 2], res[res.size() - 1], points[i]))
//			res.erase(res.end() - 1);
//		res.pb(points[i]);
//	}
//	res.erase(res.end() - 1);
	return res;
}
int main() {
	FAST_IO;
	freopen("balance.in", "r", stdin);
	freopen("balance.out", "w", stdout);
	ll n; cin >> n;
	vector<point> points;
	points.pb(point(0, 0));
	FOR(i, 1, n+1) {
		int a; cin >> a;
		points.pb(point(i, a));
	}
	points.pb(point(n+1, 0));
	vector<point> hull = convexHull(points);
	point currLine[2];
	currLine[0] = hull[0];
	currLine[1] = hull[1];
	int idx = 2;
	F0R(i, n+2) {
		ld ans = 0;
		if(currLine[1].x == i) {
			if(i == n + 1)
				return 0;
			currLine[0] = currLine[1];
			currLine[1] = hull[idx++];
		}
		if(currLine[0].x == i) {
			ans = 1e5*currLine[0].y;
		} else {
			vec<ll> dir = currLine[0].toVec(currLine[1]);
			ans = 1e5 * (1.0 * dir.y * (i - currLine[0].x) + currLine[0].y * dir.x);
			ans /= dir.x;
		}
		if(i) cout << (ll)ans << '\n';
	}
}

//Remember to change MAXN if relevant!!!
