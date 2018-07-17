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

int dx[]{-1, 0, 1, 0};
int dy[]{0, -1, 0, 1};
int main() {
    FAST_IO;
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);
    int r, c; cin >> r >> c;
    char mat[r][c];
    F0R(i, r) {
        string str; cin >> str;
        F0R(j, c)
            mat[i][j] = str[j];
    }
    vpi xs;
    F0R(i, r)
        F0R(j, c)
            if(mat[i][j] == 'X')
                xs.pb(mp(i, j));

    bool vis[r][c];
    memset(vis, false, sizeof vis);
    vpi islands;
    int fillMat[r][c];
    memset(fillMat, -1, sizeof fillMat);
    int curr = 0;
    for(pi point: xs) {
        queue<pi> q; //true if thinks on island
        q.push(point);
        bool isl = false;
        while (!q.empty()) {
            pi co = q.front();
            q.pop();
            if (vis[co.f][co.s])
                continue;
            isl = true;
            vis[co.f][co.s] = true;
            fillMat[co.f][co.s] = curr;
            for(int i = 0; i < 4; i++) {
                pi nxt = mp(co.f + dx[i], co.s + dy[i]);
                if(nxt.f >= 0 && nxt.f < r && nxt.s >= 0 && nxt.s < c)
                    if(mat[nxt.f][nxt.s] == 'X')
                        q.push(nxt);
            }
        }
        if(isl) {
            islands.pb(point);
            curr++;
        }
    }
//    F0R(i, r) {
//        F0R(j, c)
//            cout << fillMat[i][j];
//        cout << '\n';
//    }
    int n = islands.size();
    int dist[n][n];
    memset(dist, 63, sizeof dist);
    curr = 0;
    for(pi point: islands) {
        queue<pair<pi, int>> q;
        int tDist[r][c];
        memset(tDist, 63, sizeof tDist);
        q.push(mp(point, 0));
        while(!q.empty()) {
            auto node = q.front();
            q.pop();
            pi co = node.f;
            if(node.s >= tDist[co.f][co.s])
                continue;
            tDist[co.f][co.s] = node.s;
            if(fillMat[co.f][co.s] != -1)
                dist[curr][fillMat[co.f][co.s]] = min(dist[curr][fillMat[co.f][co.s]], node.s);
            for(int i = 0; i < 4; i++) {
                auto nxt = mp(mp(co.f + dx[i], co.s + dy[i]), node.s);
                if(nxt.f.f >= 0 && nxt.f.f < r && nxt.f.s >= 0 && nxt.f.s < c) {
                    if (mat[nxt.f.f][nxt.f.s] == 'X')
                        q.push(nxt);
                    if(mat[nxt.f.f][nxt.f.s] == 'S') {
                        nxt.s++;
                        q.push(nxt);
                    }
                }
            }
        }
        curr++;
    }
//    F0R(i, n) {
//        F0R(j, n)
//            cout << dist[i][j] << " ";
//        cout << '\n';
//    }
    int dp[1 << n][n];
    memset(dp, 63, sizeof dp);
    F0R(i, n)
        dp[1 << i][i] = 0;
    F0R(i, 1 << n) {
        F0R(j, n) {
            if(dp[i][j] == INF)
                continue;
            F0R(k, n) {
                if((1 << k) & i)
                    continue;
                dp[i|(1<<k)][k] = min(dp[i|(1<<k)][k], dp[i][j] + dist[j][k]);
            }
        }
    }
    int ans = INF;
    F0R(i, n)
        ans = min(ans, dp[(1 << n) - 1][i]);
    cout << ans << '\n';
}

