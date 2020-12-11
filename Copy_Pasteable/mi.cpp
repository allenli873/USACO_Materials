struct mi {
    ll v; explicit operator ll() const { return v; }
    mi() { v = 0; }
    mi(ll _v) {
        v = (-MOD <= _v && _v <= MOD) ? _v : _v % MOD;
        if(v < 0) v += MOD;
    }
    friend bool operator==(const mi& a, const mi& b) { return a.v == b.v; }
    friend bool operator!=(const mi& a, const mi& b) { return !(a.v == b.v); }
    friend bool operator<(const mi& a, const mi& b) { return a.v < b.v; }
    friend bool operator<=(const mi& a, const mi& b) { return a.v < b.v || a.v == b.v; }
    friend bool operator>(const mi& a, const mi& b) { return a.v > b.v; }
    friend bool operator>=(const mi& a, const mi& b) {return a.v > b.v || a.v == b.v; }
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
    mi pow(mi b, ll p) {
        assert(p >= 0);
        mi ret = 1; 
        for(; p; p /= 2, b *= b) if(p & 1) ret *= b;
        return ret;
    }
    mi inv(const mi& a) {
        assert(a.v != 0);
        return pow(a, MOD - 2);
    }
    // printing
    friend ostream& operator<<(ostream& os, const mi& m) {
        os << m.v; return os;
    }
    friend istream& operator>>(istream& is, mi& m) {
        ll x; is >> x;
        m.v = ((x % MOD) + MOD) % MOD;
        return is;
    }
};
