import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.InputMismatchException;
import java.io.IOException;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author Allen Li
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("haybales.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("haybales.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        FastReader in = new FastReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Haybales solver = new Haybales();
        solver.solve(1, in, out);
        out.close();
    }

    static class Haybales {
        final long INF = Long.MAX_VALUE / 4;
        Node[] seg;
        long[] lazy;
        int[] vals;

        void down(int node, int l, int r) {
            if (lazy[node] == 0)
                return;
            seg[node].sum += (r - l + 1) * lazy[node];
            seg[node].min += lazy[node];
            if (l != r) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }

        void update(int node, int l, int r, int a, int b, int diff) {
            down(node, l, r);
            if (l > b || r < a)
                return;
            if (l >= a && r <= b) {
                lazy[node] += diff;
                down(node, l, r);
                return;
            }
            int mid = (l + r) / 2;
            update(node * 2, l, mid, a, b, diff);
            update(node * 2 + 1, mid + 1, r, a, b, diff);
            seg[node].sum = seg[node * 2].sum + seg[node * 2 + 1].sum;
            seg[node].min = Math.min(seg[node * 2].min, seg[node * 2 + 1].min);
        }

        void build(int node, int l, int r) {
            if (l > r)
                return;
            if (l == r) {
                seg[node].min = seg[node].sum = vals[l];
                return;
            }
            int mid = (l + r) / 2;
            build(node * 2, l, mid);
            build(node * 2 + 1, mid + 1, r);
            seg[node].min = Math.min(seg[node * 2].min, seg[node * 2 + 1].min);
            seg[node].sum = seg[node * 2].sum + seg[node * 2 + 1].sum;
        }

        long queryMin(int node, int l, int r, int a, int b) {
            down(node, l, r);
            if (l > b || r < a)
                return INF;
            if (l >= a && r <= b)
                return seg[node].min;
            int mid = (l + r) / 2;
            return Math.min(queryMin(node * 2, l, mid, a, b), queryMin(node * 2 + 1, mid + 1, r, a, b));
        }

        long querySum(int node, int l, int r, int a, int b) {
            down(node, l, r);
            if (l > b || r < a)
                return 0;
            if (l >= a && r <= b)
                return seg[node].sum;
            int mid = (l + r) / 2;
            return querySum(node * 2, l, mid, a, b) + querySum(node * 2 + 1, mid + 1, r, a, b);
        }

        public void solve(int testNumber, FastReader in, PrintWriter out) {
            int n = in.nextInt();
            int q = in.nextInt();
            vals = new int[n];
            for (int i = 0; i < n; i++) {
                vals[i] = in.nextInt();
            }
            seg = new Node[n * 4];
            for (int i = 0; i < seg.length; i++) {
                seg[i] = new Node(0, 0);
            }
            lazy = new long[n * 4];
            build(1, 0, vals.length - 1);
            for (int i = 0; i < q; i++) {
                char c = in.nextCharacter();
                if (c == 'M') {
                    int n1 = in.nextInt() - 1;
                    int n2 = in.nextInt() - 1;
                    out.println(queryMin(1, 0, vals.length - 1, n1, n2));
                } else if (c == 'S') {
                    int n1 = in.nextInt() - 1;
                    int n2 = in.nextInt() - 1;
                    out.println(querySum(1, 0, vals.length - 1, n1, n2));
                } else {
                    int n1 = in.nextInt() - 1;
                    int n2 = in.nextInt() - 1;
                    int diff = in.nextInt();
                    update(1, 0, vals.length - 1, n1, n2, diff);
                }
            }
        }

        class Node {
            long sum;
            long min;

            public Node(long sum, long min) {
                this.sum = sum;
                this.min = min;
            }

        }

    }

    static class FastReader {
        private InputStream stream;
        private byte[] buf = new byte[1024];
        private int curChar;
        private int numChars;
        private FastReader.SpaceCharFilter filter;

        public FastReader(InputStream stream) {
            this.stream = stream;
        }

        public int read() {
            if (numChars == -1) {
                throw new InputMismatchException();
            }
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (numChars <= 0) {
                    return -1;
                }
            }
            return buf[curChar++];
        }

        public int nextInt() {
            int c = read();
            while (isSpaceChar(c)) {
                c = read();
            }
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            int res = 0;
            do {
                if (c < '0' || c > '9') {
                    throw new InputMismatchException();
                }
                res *= 10;
                res += c - '0';
                c = read();
            } while (!isSpaceChar(c));
            return res * sgn;
        }

        public boolean isSpaceChar(int c) {
            if (filter != null) {
                return filter.isSpaceChar(c);
            }
            return isWhitespace(c);
        }

        public static boolean isWhitespace(int c) {
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }

        public char nextCharacter() {
            int c = read();
            while (isSpaceChar(c)) {
                c = read();
            }
            return (char) c;
        }

        public interface SpaceCharFilter {
            public boolean isSpaceChar(int ch);

        }

    }
}
