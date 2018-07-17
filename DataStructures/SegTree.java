class SegTree {
    int[] seg, arr, lazy;
    public SegTree(int[] arr) {
        this.arr = arr;
        seg = new int[arr.length * 4];
        lazy = new int[arr.length * 4];
    }

    private int getSum(int l, int r, int a, int b, int node) {
        if (lazy[node] != 0) {
            seg[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (l > r || l > b || r < a)
            return 0;
        if (l >= a && r <= b)
            return seg[node];

        int mid = (l + r) / 2;
        return getSum(l, mid, a, b, 2 * node) + getSum(mid + 1, r, a, b, 2 * node + 1);
    }

    int getSum(int l, int r) {
        return getSum(0, arr.length - 1, l, r, 1);
    }

    private void updateRange(int node, int l, int r, int a, int b, int diff) {
        if (lazy[node] != 0) {
            seg[node] += (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }

        if (l > r || l > b || r < a)
            return;

        if (l >= a && r <= b) {
            seg[node] += (r - l + 1) * diff;
            if (l != r) {
                lazy[node * 2] += diff;
                lazy[node * 2 + 1] += diff;
            }
            return;
        }
        int mid = (l + r) / 2;
        updateRange(node * 2, l, mid, a, b, diff);
        updateRange(node * 2 + 1, mid + 1, r, a, b, diff);
        seg[node] = seg[node * 2] + seg[node * 2 + 1];
    }

    void updateRange(int a, int b, int diff)  {
        updateRange(1, 0, arr.length - 1, a, b, diff);
    }

    private void build(int l, int r, int node) {
        if (l > r)
            return;
        if (l == r) {
            seg[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, node * 2);
        build(mid + 1, r, node * 2 + 1);

        seg[node] = seg[node * 2] + seg[node * 2 + 1];
    }
    void build() {
        build(0, arr.length - 1, 1);
    }
}
