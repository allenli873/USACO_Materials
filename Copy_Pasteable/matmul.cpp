struct mi {
    ll v; explicit operator ll() const { return v; }
    mi() { v = 0; }
    mi(ll _v) {
        v = (-MOD <= _v && _v <= MOD) ? _v : _v % MOD;
        if(v < 0) v += MOD;
    }
    friend bool operator==(const mi& a, const mi& b) { return a.v == b.v; }
    friend bool operator!=(const mi& a, const mi& b) { return !(a == b); }
    friend bool operator<(const mi& a, const mi& b) { return a.v < b.v; }
    friend bool operator<=(const mi& a, const mi& b) { return a < b || a == b; }
    friend bool operator>(const mi& a, const mi& b) { return a.v > b.v; }
    friend bool operator>=(const mi& a, const mi& b) {return a > b || a == b; }
    mi operator-() const { return mi(-v); }
    mi& operator+=(const mi& m) {
        if((v += m.v) >= MOD) v -= MOD;
        return *this;
    }
    mi& operator-=(const mi& m) {
        if((v -= m.v) < 0) v += MOD;
        return *this;
    }
    mi& operator*=(const mi& m) {
        v = v * m.v % MOD;
        return *this;
    }
    mi& operator/=(const mi& m) {
        return (*this) *= inv(m);
    }
    mi& operator++() { return *this += 1; }
    mi& operator--() { return *this -= 1; }
    friend mi operator+(mi a, const mi& b) { return a += b; }
    friend mi operator-(mi a, const mi& b) { return a -= b; }
    friend mi operator*(mi a, const mi& b) { return a *= b; }
    friend mi operator/(mi a, const mi& b) { return a /= b; }
    friend mi pow(mi b, ll p) {
        assert(p >= 0);
        mi ret = 1;
        for(; p; p /= 2, b *= b) if(p & 1) ret *= b;
        return ret;
    }
    friend mi inv(const mi& a) {
        assert(a.v != 0);
        return pow(a, MOD - 2);
    }
    // printing
    friend ostream& operator<<(ostream& os, const mi& m) {
        os << m.v; return os;
    }
    friend istream& operator>>(istream& is, mi& m) {
        ll x; is >> x;
        m.v = x;
        return is;
    }
};

vector<vector<mi>> matmul(vector<vector<mi>>& mat1, vector<vector<mi>>& mat2) {
    int n1 = sz(mat1), m1 = sz(mat1[0]), n2 = sz(mat2), m2 = sz(mat2[0]);
    assert(m1 == n2);
    vector<vector<mi>> res(n1, vector<mi>(m2, 0));
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            for (int a = 0; a < m1; a++) {
                res[i][j] += mat1[i][a] * mat2[a][j];
            }
        }
    }
    return res;
}

void expo(vector<vector<mi>>& mat, ll exp) {
    assert(sz(mat) == sz(mat[0]));
    int n = sz(mat);
    vector<vector<mi>> a(mat);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = 0;
    for (int i = 0; i < n; i++) mat[i][i] = 1;
    while (exp) {
        if (exp & 1)
            mat = matmul(mat, a);
        a = matmul(a, a);
        exp >>= 1;
    }
}
