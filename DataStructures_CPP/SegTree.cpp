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
        return a + b;
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
        if(l == r) {
            seg[node] += diff;
            return;
        }
        int mid = (l + r) / 2;
        update(node * 2, l, mid, idx, diff);
        update(node * 2 + 1, mid + 1, r, idx, diff);
        seg[node] = f(seg[node*2], seg[node*2+1]);
    }
};
