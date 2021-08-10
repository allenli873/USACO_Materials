// https://dmoj.ca/problem/tle17c7p5
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow. cap[i][j] != cap[j][i] is allowed; double edges are not.
 *  If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported.
 *  To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: Approximately O(E^2)
 */
#include <bits/extc++.h> /// include-line, keep-include

const double INF = numeric_limits<ll>::max() / 4;
const double INF_D = numeric_limits<double>::max() / 4;
typedef vector<ll> VL;

struct MCMF {
	int N;
	vector<vi> ed, red;
	vector<VL> cap, flow;
    vector<vector<double>> cost;
	vi seen;
    vector<double> dist, pi;
	vector<pair<int, int>> par;

	MCMF(int N) :
		N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(N, vector<double>(N)),
		seen(N), dist(N), pi(N), par(N) {}

	void ae(int from, int to, ll cap, double cost) {
		this->cap[from][to] = cap;
		this->cost[from][to] = cost;
		ed[from].push_back(to);
		red[to].push_back(from);
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF_D);
		dist[s] = 0; double di;

		__gnu_pbds::priority_queue<pair<double, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({0, s});

		auto relax = [&](int i, ll cap, double cost, int dir) {
			double val = di - pi[i] + cost;
			if (cap && val < dist[i]) {
				dist[i] = val;
				par[i] = {s, dir};
				if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
				else q.modify(its[i], {-dist[i], i});
			}
		};

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (int i : ed[s]) if (!seen[i])
				relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
			for (int i : red[s]) if (!seen[i])
				relax(i, flow[i][s], -cost[i][s], 0);
		}
		rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF_D);
	}

	pair<ll, double> maxflow(int s, int t) {
		ll totflow = 0;
        double totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
			totflow += fl;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				if (r) flow[p][x] += fl;
				else flow[x][p] -= fl;
		}
        int ct = 0;
        int on = (N - 2) / 2;
        rep(i,0,N) rep(j,0,N) {
            if (i >= 1 && i <= on && j >= on + 1 && j <= 2 * on && flow[i][j] > 0) {
                cout << i << ' ' << j - on << '\n';
                ct++;
            }
            totcost += cost[i][j] * flow[i][j];  
        }
        if (ct != (N - 2) / 2) totflow = 6969;
		return {totflow, totcost};
	}
};

double dist(pair<double, double> &a, pair<double, double> &b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}
int main() {
    int n; cin >> n;
    MCMF graph(n * 2 + 2);
    int sink = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        graph.ae(0, i, 1, 0);
    }
    for (int i = n + 1; i <= 2 * n; i++) {
        graph.ae(i, sink, 1, 0);
    }
    vector<pair<double, double>> pts(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> pts[i].first >> pts[i].second;
    }
    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2 * n; j++) {
            graph.ae(i + 1, j + 1, 1, dist(pts[i], pts[j]));
        }
    }
    graph.maxflow(0, sink);
}
