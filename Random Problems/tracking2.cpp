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

const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const int NINF = -0x3f3f3f40;
const ll INF_L = 0x3f3f3f3f3f3f3f3f;
const ll NINF_L = -0x3f3f3f3f3f3f3f40;

const int MAXN = 1e5+5;

ll n, k, dp[MAXN];
ll exp(int b, int e) {
	if(e == 0) return 1;
	if(e == 1) return b;
	if(e&1) return b*exp(b,e-1)%MOD;
	ll t=exp(b, e/2);
	return t*t%MOD;
}
ll solve(ll v, ll len) {
	ll x = 1e9-v;
	memset(dp, 0, sizeof dp);
	dp[0] = 0;
	dp[1] = 1;
	FOR(i, 2, k+1) {
		dp[i] = dp[i-1] * (x+1);
		dp[i] %= MOD;
	}
	if(len < k) return dp[len+1];
	FOR(i, 1, k+1) {
		dp[i] *= exp(x, len-i+1);
		dp[i] += dp[i-1];
		dp[i] %= MOD;
	}
	FOR(i, k+1, len+2) {
		dp[i] = (dp[i-1]-dp[i-k-1]+MOD)%MOD * exp(exp(x, len-i+2), MOD - 2);
		dp[i] %= MOD;
		dp[i] *= exp(x, len-i+1);
		dp[i] %= MOD;
		dp[i] += dp[i-1];
		dp[i] %= MOD;
	}
	return (dp[len+1]-dp[len]+MOD)%MOD;
}

int main() {
	FAST_IO;
	freopen("tracking2.in", "r", stdin);
	freopen("tracking2.out", "w", stdout);
	cin >> n >> k;
	int arr[n-k+2], train[n];
	memset(train, -1, sizeof train);
	vi tv; int tvI;
	F0R(i, n-k+1) cin >> arr[i];
	F0R(i, n-k) {
		if(arr[i] < arr[i+1]) {
			train[i] = arr[i];
			tv.pb(arr[i]);
		}
		if(arr[i] > arr[i+1]) {
			train[i + k] = arr[i];
			tv.pb(arr[i]);
		}
	}
	int cL = 0;
	ll ans = 1;
	F0R(i, n) {
		if(train[i] != -1) {
			ans *= solve(tv[tvI++], cL);
			ans %= MOD;
			cL = 0;
			continue;
		}
		cL++;
	}
	if(cL) {
		ans *= solve(arr[n-k], cL);
		ans %= MOD;
	}
	cout << ans << '\n';
}

//Remember to change MAXN if relevant!!!
