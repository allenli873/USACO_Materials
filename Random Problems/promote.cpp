#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

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
const int MAXN = 100005;

struct Node {
    ordered_set<int>* nums;
    int val, ans;
    vector<Node*> children;
};
Node nodes[MAXN];
void dfs(Node* curr) {
    Node* largest = nullptr;
    for(auto node: curr -> children) {
        dfs(node);
        if(!largest || node -> nums -> size() > largest -> nums -> size())
            largest = node;
    }
    if(!largest)
        curr -> nums = new ordered_set<int>;
    else
        curr -> nums = largest -> nums;
    //merge sets
    for(auto node: curr -> children)
        if(node != largest)
            for(auto element: *(node -> nums))
                curr -> nums -> insert(element);
    curr -> ans = curr -> nums -> size() - (curr -> nums -> order_of_key(curr -> val));
    curr -> nums -> insert(curr -> val);
}
int main() {
    FAST_IO;
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
    int n; cin >> n;
    F0R(i, n)
        cin >> nodes[i].val;
    FOR(i, 1, n) {
        int par; cin >> par;
        par--;
        nodes[par].children.pb(&nodes[i]);
    }
    dfs(&nodes[0]);
    F0R(i, n)
        cout << nodes[i].ans << '\n';
}
