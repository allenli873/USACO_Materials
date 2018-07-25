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

template<class T>
inline void MAX(T &a, T b) { if (a < b) a = b; }

template<class T>
inline void MIN(T &a, T b) { if (a > b) a = b; }

template<class T>
inline void MODA(T &a, T b) {
    a %= b;
    if (a < 0) a += b;
}

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

const int MOD = 2012;
const int INF = 0x3f3f3f3f;
const int NINF = -0x3f3f3f40;

int main() {
    FAST_IO;
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);
    string str; cin >> str;
    int n = sz(str);
    int dp[n+1][n+1];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    int curr = 0;
    F0R(i, n) {
        if(str[i] == '(') {
            F0R(j, n) {
                if (j != n) {
                    dp[i + 1][j + 1] += dp[i][j];
                    MODA(dp[i + 1][j + 1], MOD);
                }
                dp[i + 1][j] += dp[i][j];
                MODA(dp[i + 1][j], MOD);
            }
            ++curr;
        } else {
            F0R(j, n+1) {
                if(j) {
                    dp[i + 1][j - 1] += dp[i][j];
                    MODA(dp[i + 1][j - 1], MOD);
                }
                int k = curr - j;
                if(k > 0) {
                    dp[i + 1][j] += dp[i][j];
                    MODA(dp[i + 1][j], MOD);
                }
            }
            --curr;
        }
    }
    cout << dp[n][0] << '\n';

    //The n^3 solution below
    /*
    int dp[n+1][n+1][n+1];
    memset(dp, 0, sizeof dp);
    dp[0][0][0] = 1;
    F0R(i, n) {
        if(str[i] == '(') {
            F0R(j, n)
                F0R(k, n) {
                    if(j != n) {
                        dp[i + 1][j + 1][k] += dp[i][j][k];
                        MODA(dp[i + 1][j + 1][k], MOD);
                    }
                    if(k != n) {
                        dp[i + 1][j][k + 1] += dp[i][j][k];
                        MODA(dp[i + 1][j][k + 1], MOD);
                    }
                }
        } else {
            F0R(j, n+1) {
                F0R(k, n+1) {
                    if(j) {
                        dp[i + 1][j - 1][k] += dp[i][j][k];
                        MODA(dp[i + 1][j - 1][k], MOD);
                    }
                    if(k) {
                        dp[i + 1][j][k - 1] += dp[i][j][k];
                        MODA(dp[i + 1][j][k - 1], MOD);
                    }
                }
            }
        }
    }
    cout << dp[n][0][0] << '\n';
    */
}

