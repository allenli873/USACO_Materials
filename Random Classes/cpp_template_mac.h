#if ($HEADER_COMMENTS)
//
// Created by $USER_NAME on ${DATE}.
#if ($ORGANIZATION_NAME && $ORGANIZATION_NAME != "")
// Copyright (c) $YEAR ${ORGANIZATION_NAME}#if (!$ORGANIZATION_NAME.endsWith(".")).#end All rights reserved.
#end
//

\#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<double,double> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

template<class T> inline void MAX(T& a, T b) { if(a < b) a = b; }
template<class T> inline void MIN(T& a, T b) { if(a > b) a = b; }
template<class T> inline void MODA(T& a, T b) { a %= b; if(a < 0) a += b; }

\#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); cout.precision(20)
\#define watch(x) cout << (#x) << " is " << (x) << endl
\#define long ll
\#define finish(x) return cout << (x) << '\n', 0
\#define F0R(i, a) for(int (i)=0;(i)<(a);++(i))
\#define FOR(i, a, b) for(int (i)=(a);(i)<(b);++(i))
\#define F0Rd(i, a) for(int (i)=a;(i)>=0;--(i))
\#define FORd(i, a, b) for(int (i)=a;(i)>=(b);--(i))
\#define all(x) (x).begin(), (x).end()
\#define sz(x) ((int)(x).size())

\#define mp make_pair
\#define pb push_back
\#define pf push_front
\#define f first
\#define s second
\#define lb lower_bound
\#define ub upper_bound

const int MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const int NINF = -0x3f3f3f40;

int main() {
    FAST_IO;
    
}

#end
