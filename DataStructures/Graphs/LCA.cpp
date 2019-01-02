//
// Created by Allen Li on 6/14/18.
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
#define F0R(i, a) for(int (i)=0;(i)<(a);(i)++)
#define FOR(i, a, b) for(int (i)=(a);(i)<(b);(i)++)
#define F0Rd(i, a) for(int (i)=a;(i)>=0;(i)--)
#define FORd(i, a, b) for(int (i)=a;(i)>=(b);(i)--)
#define all(x) (x).begin(), (x).end()

#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int INF = 1061109567;
const int MAXN = 100005;
vector<vi> adj;
vi depth;

int par[MAXN][18];

void dfs(int curr, int past, int currD) {
    depth[curr] = currD;
    par[curr][0] = past;
    for(auto node: adj[curr])
        if(node != past)
            dfs(node, curr, currD+1);
}
void computeSparse() {
    dfs(0, 0, 0);
    FOR(j, 1, 18) {
        FOR(i, 1, MAXN) {
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }

}
int lca(int n1, int n2) {
    if(depth[n1] < depth[n2])
        swap(n1, n2);
    if(depth[n1] > depth[n2]) {
        int lift = depth[n1]-depth[n2];
        F0R(j, 18)
            if (lift & (1 << j))
                n1 = par[n1][j];
    }
    if(n1 == n2)
        return n1;
    while (par[n1][0] != par[n2][0]) {
        FOR(j, 1, 18)
            if (par[n1][j] == par[n2][j]) {
                n1 = par[n1][j - 1];
                n2 = par[n2][j - 1];
                break;
            }
    }
    return par[n1][0];
}
/*
 * Tree:
 *              0
 *             / \
 *            1   2
 *           / \
 *          3   4
 *               \
 *                5
 */
int main() {
    FAST_IO;
    int n = 6;
    adj.resize(n);
    depth.resize(n);
    adj[0].pb(1);
    adj[0].pb(2);
    adj[1].pb(3);
    adj[1].pb(4);
    adj[4].pb(5);
    computeSparse();
    cout << "LCA of 1 and 2 is " << lca(1, 2) << endl;
    cout << "LCA of 0 and 1 is " << lca(0, 1) << endl;
    cout << "LCA of 3 and 4 is " << lca(3, 4) << endl;
    cout << "LCA of 3 and 5 is " << lca(3, 5) << endl;
    cout << "LCA of 4 and 5 is " << lca(4, 5) << endl;
}
