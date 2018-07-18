#if ($HEADER_COMMENTS)
//
// Created by $USER_NAME on ${DATE}.
#if ($ORGANIZATION_NAME && $ORGANIZATION_NAME != "")
// Copyright (c) $YEAR ${ORGANIZATION_NAME}#if (!$ORGANIZATION_NAME.endsWith(".")).#end All rights reserved.
#end
//

\#include <bits/stdc++.h>
\#include <ext/pb_ds/tree_policy.hpp>
\#include <ext/pb_ds/assoc_container.hpp>

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

\#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(20)
\#define watch(x) cout << (#x) << " is " << (x) << endl
\#define long ll
\#define finish(x) return cout << (x) << '\n', 0
\#define F0R(i, a) for(int (i)=0;(i)<(a);(i)++)
\#define FOR(i, a, b) for(int (i)=(a);(i)<(b);(i)++)
\#define F0Rd(i, a) for(int (i)=a;(i)>=0;(i)--)
\#define FORd(i, a, b) for(int (i)=a;(i)>=(b);(i)--)
\#define all(x) (x).begin(), (x).end()

\#define mp make_pair
\#define pb push_back
\#define f first
\#define s second
\#define lb lower_bound
\#define ub upper_bound

const int MOD = 1000000007;
const int INF = 1061109567;

int main() {
    FAST_IO;
    
}

#end