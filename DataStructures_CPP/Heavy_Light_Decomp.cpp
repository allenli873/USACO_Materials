//
// Created by Allen Li on 6/28/18.
// HLD on classic problem: In a tree, support two queries: 1. change the value of an edge, and 2. Given two nodes, find the maximum value of an edge on the path between them
//

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<double, double> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
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

const int MOD = 1000000007;
const int INF = 1061109567;
const int MAXN = 100005;

class SegTree {
public:
    int len;
    vi seg, arr;

    SegTree(int l) {
        len = l;
        seg.resize(l * 4);
    }

    SegTree(vi a) {
        len = a.size();
        seg.resize(len * 4);
        arr = a;
        build(1, 0, len - 1);
    }

    int query(int a, int b) {
        return query(a, b, 1, 0, len - 1);
    }

    void update(int idx, int diff) {
        update(1, 0, len - 1, idx, diff);
    }

private:
    int f(int a, int b) { //change for different problems
        return max(a, b);
    }

    void build(int node, int l, int r) {
        if (l > r)
            return;
        if (l == r) {
            seg[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        seg[node] = f(seg[node * 2], seg[node * 2 + 1]);
    }

    int query(int a, int b, int node, int l, int r) {
        if (l > b || r < a) {
            return -1;
        }
        if (l >= a && r <= b) {
            return seg[node];
        }
        int mid = (l + r) / 2;
        int n1 = query(a, b, node * 2, l, mid);
        int n2 = query(a, b, node * 2 + 1, mid + 1, r);
        if (n1 == -1)
            return n2;
        if (n2 == -1)
            return n1;
        return f(n1, n2);
    }

    void update(int node, int l, int r, int idx, int diff) {
        if (idx < l || idx > r)
            return;
        if (l == r) {
            seg[node] += diff;
            return;
        }
        int mid = (l + r) / 2;
        update(node * 2, l, mid, idx, diff);
        update(node * 2 + 1, mid + 1, r, idx, diff);
        seg[node] = f(seg[node * 2], seg[node * 2 + 1]);
    }
};

int heavy[MAXN], sz[MAXN], chainHead[MAXN], stIndex[MAXN], cost[MAXN];
vpi adj[MAXN];
vi depth;
int par[MAXN][18];
int cIdx = 0;
SegTree *st;

void dfs(int curr, int past, int currD) {
    depth[curr] = currD;
    par[curr][0] = past;
    sz[curr] = 1;
    for (auto node: adj[curr]) {
        if (node.f != past) {
            cost[node.f] = node.s;
            dfs(node.f, curr, currD + 1);
            sz[curr] += sz[node.f];
        }
    }
    for (auto node: adj[curr]) {
        if (node.f != past)
            if (sz[node.f] > sz[curr] / 2) {
                heavy[curr] = node.f;
                break;
            }
    }
}

void computeSparse() {
    dfs(0, 0, 0);
    FOR(j, 1, 18)
        FOR(i, 1, MAXN)
            par[i][j] = par[par[i][j - 1]][j - 1];
}

void computeHLD() {
    memset(heavy, -1, sizeof heavy);
    computeSparse();
    vi temp;
    F0R(i, MAXN) {
        if (i == 0 || heavy[par[i][0]] != i) {
            for (int j = i; j != -1; j = heavy[j]) {
                temp.pb(cost[j]);
                stIndex[j] = cIdx++;
                chainHead[j] = i;
            }
        }
    }
    st = new SegTree(temp);
}

int queryUp(int node, int lca) {
    int ans = 0;
    while (node != lca) {
        if (heavy[par[node][0]] != node) {
            ans = max(ans, cost[node]);
            node = par[node][0];
        } else {
            int next = -1;
            if (chainHead[lca] == chainHead[node])
                next = lca;
            else
                next = chainHead[node];
            int pos1 = min(stIndex[node], stIndex[next]);
            int pos2 = max(stIndex[node], stIndex[next]);
            pos1++;
            ans = max(ans, st->query(pos1, pos2));
            node = next;
        }
    }
    return ans;
}

int getLCA(int n1, int n2) {
    while (par[n1][0] != par[n2][0]) {
        int lift = abs(depth[n1] - depth[n2]);
        if (depth[n1] > depth[n2]) {
            F0R(j, 18)
                if (lift & (1 << j))
                    n1 = par[n1][j];
        } else if (depth[n2] > depth[n1]) {
            F0R(j, 18)
                if (lift & (1 << j))
                    n2 = par[n2][j];
        } else {
            while (par[n1][0] != par[n2][0]) {
                FOR(j, 1, 18)
                    if (par[n1][j] == par[n2][j]) {
                        n1 = par[n1][j - 1];
                        n2 = par[n2][j - 1];
                        break;
                    }
            }
        }
    }
    return n1 == n2 ? n1 : par[n1][0];
}

int query(int a, int b) {
    int lca = getLCA(a, b);
    return max(queryUp(a, lca), queryUp(b, lca));
}

void updateUtil(int node, int val) { //node is the node of higher depth for the updated edge
    int p = par[node][0];
    if (heavy[p] != node)
        cost[node] = val;
    else
        st->update(stIndex[node], val - (st -> query(stIndex[node], stIndex[node])));
}

void update(int n1, int n2, int val) {
    updateUtil(depth[n1] > depth[n2] ? n1 : n2, val);
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
 * Values:
 *      0-1: 5
 *      0-2: 3
 *      1-3: 7
 *      1-4: 9
 *      4-5: 2
 */
void makeInitTree() {
    adj[0].pb({1, 5});
    adj[0].pb({2, 3});
    adj[1].pb({3, 7});
    adj[1].pb({4, 9});
    adj[4].pb({5, 2});
    //undirected so edge both ways
    adj[1].pb({0, 5});
    adj[2].pb({0, 3});
    adj[3].pb({1, 7});
    adj[4].pb({1, 9});
    adj[5].pb({4, 2});
}

int main() {
    FAST_IO;
    //initial testing tree
    int n = 6;
    makeInitTree();
    depth.resize(n);
    computeHLD();
    cout << "The maximum edge from " << 0 << " to " << 1 << " is " << query(0, 1) << '\n';
    cout << "The maximum edge from " << 3 << " to " << 5 << " is " << query(3, 5) << '\n';
    cout << "The maximum edge from " << 3 << " to " << 2 << " is " << query(3, 2) << '\n';
    cout << "Changing the edge between " << 0 << " and " << 1 << " to " << 4 << '\n';
    update(0, 1, 4);
    cout << "The maximum edge from " << 0 << " to " << 1 << " is " << query(0, 1) << '\n';
    cout << "The maximum edge from " << 3 << " to " << 5 << " is " << query(3, 5) << '\n';
    cout << "The maximum edge from " << 3 << " to " << 2 << " is " << query(3, 2) << '\n';
}
