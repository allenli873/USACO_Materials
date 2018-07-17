class Node_Inner {
public:
    int val;
    Node_Inner *c[2];

    Node_Inner() {
        val = 0;
        c[0] = c[1] = nullptr;
    }

    Node_Inner *getC(int x) {
        if (!c[x])
            c[x] = new Node_Inner();
        return c[x];
    }

    bool overlaps(int a, int b, int c, int d) {
        return b >= c && a <= d;
    }

    int getMid(int l, int r) {
        return ((l + r) < 0) ? (l + r - 1) / 2 : (l + r) / 2;
    }

    void update(int idx, int v, int l, int r) {
        if (l == r) {
            val = v;
            return;
        }
        int mid = getMid(l, r);
        if (idx <= mid)
            getC(0)->update(idx, v, l, mid);
        else
            getC(1)->update(idx, v, mid + 1, r);
        val = max(c[0] ? c[0]->val : 0, c[1] ? c[1]->val : 0);
    }

    int query(int a, int b, int l, int r) {
        if (l >= a && r <= b)
            return val;
        if (l > b || r < a)
            return -INF;
        int mid = getMid(l, r);
        int res = (c[0] ? c[0]->query(a, b, l, mid) : (overlaps(a, b, l, mid) ? 0 : -INF));
        res = max(res, c[1] ? c[1]->query(a, b, mid + 1, r) : (overlaps(a, b, mid + 1, r) ? 0 : -INF));
        return res;
    }
};

class Node_Outer {
public:
    Node_Inner *node;
    Node_Outer *c[2];

    Node_Outer() {
        node = new Node_Inner();
        c[0] = c[1] = nullptr;
    }

    Node_Outer *getC(int x) {
        if (!c[x])
            c[x] = new Node_Outer();
        return c[x];
    }

    bool overlaps(int a, int b, int c, int d) {
        return b >= c && a <= d;
    }

    int getMid(int l, int r) {
        return ((l + r) < 0) ? (l + r - 1) / 2 : (l + r) / 2;
    }

    void update(int x, int y, int v, int lx, int rx, int ly, int ry) {
        if (lx == rx) {
            node->update(y, v, ly, ry);
            return;
        }
        int mid = getMid(lx, rx);
        if (x <= mid)
            getC(0)->update(x, y, v, lx, mid, ly, ry);
        else
            getC(1)->update(x, y, v, mid + 1, rx, ly, ry);
        int res = c[0] ? c[0]->node->query(y, y, ly, ry) : 0;
        res = max(res, c[1] ? c[1]->node->query(y, y, ly, ry) : 0);
        node->update(y, res, ly, ry);
    }

    int query(int qlx, int qrx, int qly, int qry, int lx, int rx, int ly, int ry) {
        if (lx >= qlx && rx <= qrx)
            return node->query(qly, qry, ly, ry);
        if (lx > qrx || rx < qlx)
            return -INF;
        int mid = getMid(lx, rx);
        int res = c[0] ? c[0]->query(qlx, qrx, qly, qry, lx, mid, ly, ry) : (overlaps(qlx, qrx, lx, mid) ? 0 : -INF);
        res = max(res,
                  c[1] ? c[1]->query(qlx, qrx, qly, qry, mid + 1, rx, ly, ry) : (overlaps(qlx, qrx, mid + 1, rx) ? 0
                                                                                                                 : -INF));
        return res;
    }
};
