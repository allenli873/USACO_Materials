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
#define sq(x) (x)*(x)
#define watch(x) cout << (#x) << " is " << (x) << endl
#define long ll
#define finish(x) return cout << (x) << '\n', 0
#define F0R(i, a) for(int (i)=0;(i)<(a);++(i))
#define FOR(i, a, b) for(int (i)=(a);(i)<(b);++(i))
#define F0Rd(i, a) for(int (i)=a;(i)>=0;--(i))
#define FORd(i, a, b) for(int (i)=a;(i)>=(b);--(i))
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

#define mp make_pair
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
const int MAXN = 1e6+5;

/*
 * Problem:
 * Given an array, define the value of a query as the sum of all
 * (K_s)^2 * s, where K_s is the number of occurrences of s. Find the
 * value of all queries.
 */

int block;

inline ll hilbert(int x, int y, int pow, int rotate) {
	if (!pow) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	ll subSquareSize = ll(1) << (2*pow - 2);
	ll ans = seg * subSquareSize;
	ll add = hilbert(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct Query {
	int l, r, idx;
	ll ord;
	inline void getOrd() {
		ord = hilbert(l, r, 21, 0);
	}
};

int curr[MAXN];

bool cmp(Query& q1, Query& q2) {
	return q1.ord < q2.ord;
}
int main() {
	FAST_IO;
	int n, t; cin >> n >> t;
	block = (int)(sqrt(n));
	int arr[n];
	F0R(i, n) cin >> arr[i];
	Query queries[t];
	F0R(i, t) {
		cin >> queries[i].l >> queries[i].r;
		queries[i].l--; queries[i].r--;
		queries[i].idx = i;
		queries[i].getOrd();
	}
	sort(queries, queries + t, cmp);

	ll ans[t];

	int currL = queries[0].l, currR = queries[0].l-1;
	ll currAns = 0;
	F0R(i, t) {
		int L = queries[i].l, R = queries[i].r;
		while(currL < L) {
			ll tmp = curr[arr[currL]]--;
			currAns -= (tmp*tmp-(tmp-1)*(tmp-1)) * arr[currL];
			currL++;
		}
		while(currL > L) {
			currL--;
			ll tmp = ++curr[arr[currL]];
			currAns += (tmp*tmp-(tmp-1)*(tmp-1)) * arr[currL];
		}
		while(currR > R) {
			ll tmp = curr[arr[currR]]--;
			currAns -= (tmp*tmp-(tmp-1)*(tmp-1)) * arr[currR];
			currR--;
		}
		while(currR < R) {
			currR++;
			ll tmp = ++curr[arr[currR]];
			currAns += (tmp*tmp-(tmp-1)*(tmp-1)) * arr[currR];
		}
		ans[queries[i].idx] = currAns;
	}
	F0R(i, t) cout << ans[i] << '\n';
}

