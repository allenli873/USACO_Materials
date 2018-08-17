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
const int MAXN = 55;

int block;

struct Query {
	int l, r;
	inline pi toPair() const {
		return {l / block, ((l / block) & 1) ? -r : r};
	}
};
bool cmp(Query q1, Query q2) {
	return q1.toPair() < q2.toPair();
}
int main() {
	FAST_IO;
	freopen("circlecross.in", "r", stdin);
	freopen("circlecross.out", "w", stdout);
	int n; cin >> n;
	block = (int)(sqrt(n*2));
	int arr[n*2];
	F0R(i, n*2) {
		cin >> arr[i];
		arr[i]--;
	}
	Query queries[n];
	F0R(i, n)
		queries[i].l = -1;

	F0R(i, n*2) {
		if(queries[arr[i]].l == -1)
			queries[arr[i]].l = i;
		else
			queries[arr[i]].r = i;
	}
	sort(queries, queries + n, cmp);
	int cnt[n];
	memset(cnt, 0, sizeof cnt);
	int currL = queries[0].l, currR = queries[0].l-1;
	int curr = 0, ans = 0;

	F0R(i, n) {
		int L = queries[i].l, R = queries[i].r;
		while(currL < L) {
			cnt[arr[currL]]--;
			if(!(cnt[arr[currL]]&1))
				curr--;
			else
				curr++;
			currL++;
		}
		while(currL > L) {
			currL--;
			cnt[arr[currL]]++;
			if(!(cnt[arr[currL]]&1))
				curr--;
			else
				curr++;
		}
		while(currR > R) {
			cnt[arr[currR]]--;
			if(!(cnt[arr[currR]]&1))
				curr--;
			else
				curr++;
			currR--;
		}
		while(currR < R) {
			currR++;
			cnt[arr[currR]]--;
			if(!(cnt[arr[currR]]&1))
				curr--;
			else
				curr++;
		}
		ans += curr;
	}
	cout << (ans/2) << '\n';
}

