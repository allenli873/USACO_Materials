//
// Created by Allen Li on 7/16/18.
//

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

#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(20)
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
const int INF = 1061109567;
const int MAXN = 3000005;

int arr[MAXN];
int main() {
    FAST_IO;
    freopen("empty.in", "r", stdin);
    freopen("empty.out", "w", stdout);
    int n, k; cin >> n >> k;
    F0R(i, k) {
        ll x, y, a, b; cin >> x >> y >> a >> b;
        FOR(j, 1, y + 1) {
            arr[(a * j + b) % n] += x;
        }
    }
    ll curr = 0;
    F0R(i, 2 * n) {
        if(arr[i % n] > 1) {
            curr += arr[i % n] - 1;
            arr[i % n] = 1;
        } else if(!arr[i % n] && curr) {
            arr[i % n] = 1;
            --curr;
        }
    }
    F0R(i, n) {
        if(!arr[i])
            finish(i);
    }
}

