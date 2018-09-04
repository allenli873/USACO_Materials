template<class T>
struct SegTree {
    vector<T> seg;
    int SZ;

    T f(T a, T b) {
        return a + b;
    }
    SegTree(int sz) {
        SZ = sz;
        seg.resize(SZ*2);
    }
    SegTree(int sz, int arr[]) {
        SZ = sz;
        seg.resize(SZ*2);
        for(int i = 0; i < SZ; i++) seg[SZ+i] = arr[i];
        for(int i = SZ - 1; i > 0; --i) seg[i] = f(seg[i<<1], seg[i<<1|1]);
    }
    T query(int l, int r) {
        r++;
        T res = 0;
        for(l += SZ, r += SZ; l < r; l >>= 1,r >>= 1) {
            if(l&1) res = f(res, seg[l++]);
            if(r&1) res = f(res, seg[--r]);
        }
        return res;
    }
    void update(int idx, T val) {
        for(seg[idx += SZ] = val; idx > 1; idx >>= 1) seg[idx>>1] = f(seg[idx], seg[idx^1]);
    }
};
