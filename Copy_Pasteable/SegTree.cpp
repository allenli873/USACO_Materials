template<class T>
class SegTree {
public:
    int SZ;
    vector<T> seg;

    SegTree(int sz) {
        SZ = sz;
        seg.resize(SZ * 4, 0);
    }

    SegTree(int sz, T arr[]) {
        SZ = sz;
        seg.resize(SZ * 4);
        build(1, 0, SZ - 1, arr);
    }

    T query(int a, int b) {
        return query(a, b, 1, 0, SZ - 1);
    }

    void update(int idx, T newVal) {
        update(1, 0, SZ - 1, idx, newVal);
    }

private:
    T f(T a, T b) { //change for different problems
        return a + b;
    }

    void build(int node, int l, int r, T arr[]) {
        if (l > r)
            return;
        if (l == r) {
            seg[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid, arr);
        build(node * 2 + 1, mid + 1, r, arr);
        seg[node] = f(seg[node * 2], seg[node * 2 + 1]);
    }

    T query(int a, int b, int node, int l, int r) {
        if (l > b || r < a) {
            return NINF;
        }
        if (l >= a && r <= b) {
            return seg[node];
        }
        int mid = (l + r) / 2;
        T n1 = query(a, b, node * 2, l, mid);
        T n2 = query(a, b, node * 2 + 1, mid + 1, r);
        if (n1 == NINF)
            return n2;
        if (n2 == NINF)
            return n1;
        return f(n1, n2);
    }

    void update(int node, int l, int r, int idx, T newVal) {
        if (idx < l || idx > r)
            return;
        if(l == r) {
            seg[node] += newVal;
            return;
        }
        int mid = (l + r) / 2;
        update(node * 2, l, mid, idx, newVal);
        update(node * 2 + 1, mid + 1, r, idx, newVal);
        seg[node] = f(seg[node*2], seg[node*2+1]);
    }
};
