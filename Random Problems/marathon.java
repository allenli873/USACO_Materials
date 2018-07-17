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
public class marathon {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("marathon.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("marathon.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        FastReader in = new FastReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        MarathonGold solver = new MarathonGold();
        solver.solve(1, in, out);
        out.close();
    }

    static class MarathonGold {
        final int INF = Integer.MAX_VALUE / 4;
        int[][] seg;
        Point[] points;
        int n;

        private int querySum(int l, int r) {
            return querySum(1, 0, n - 2, l, r);
        }

        private int querySum(int node, int l, int r, int a, int b) {
            if (l > b || r < a)
                return 0;
            if (l >= a && r <= b)
                return seg[node][0];
            int mid = (l + r) / 2;
            return querySum(node * 2, l, mid, a, b) + querySum(node * 2 + 1, mid + 1, r, a, b);
        }

        private void buildSum(int node, int l, int r) {
            if (l > r)
                return;
            if (l == r) {
                seg[node][0] = points[l].dist(points[l + 1]);
                return;
            }
            int mid = (l + r) / 2;
            buildSum(node * 2, l, mid);
            buildSum(node * 2 + 1, mid + 1, r);
            seg[node][0] = seg[node * 2][0] + seg[node * 2 + 1][0];
        }

        private void buildMax(int node, int l, int r) {
            if (l > r)
                return;
            if (l == r) {
                seg[node][1] = points[l].dist(points[l + 1]) + points[l + 1].dist(points[l + 2]) - points[l].dist(points[l + 2]);
                return;
            }
            int mid = (l + r) / 2;
            buildMax(node * 2, l, mid);
            buildMax(node * 2 + 1, mid + 1, r);
            seg[node][1] = Math.max(seg[node * 2][1], seg[node * 2 + 1][1]);
        }

        private int queryMax(int l, int r) {
            return queryMax(1, 0, n - 3, l, r);
        }

        private int queryMax(int node, int l, int r, int a, int b) {
            if (l > b || r < a)
                return -INF;
            if (l >= a && r <= b)
                return seg[node][1];
            int mid = (l + r) / 2;
            return Math.max(queryMax(node * 2, l, mid, a, b), queryMax(node * 2 + 1, mid + 1, r, a, b));
        }

        private void updateSum(int node, int newVal) {
            updateSum(1, 0, n - 2, node, newVal);
        }

        private void updateSum(int node, int l, int r, int val, int newVal) {
            if (val < l || val > r)
                return;
            if (l == r) {
                seg[node][0] = newVal;
                return;
            }
            int mid = (l + r) / 2;
            updateSum(node * 2, l, mid, val, newVal);
            updateSum(node * 2 + 1, mid + 1, r, val, newVal);
            seg[node][0] = seg[node * 2][0] + seg[node * 2 + 1][0];
        }

        private void updateMax(int node, int newVal) {
            updateMax(1, 0, n - 3, node, newVal);
        }

        private void updateMax(int node, int l, int r, int val, int newVal) {
            if (val < l || val > r)
                return;
            if (l == r) {
                seg[node][1] = newVal;
                return;
            }
            int mid = (l + r) / 2;
            updateMax(node * 2, l, mid, val, newVal);
            updateMax(node * 2 + 1, mid + 1, r, val, newVal);
            seg[node][1] = Math.max(seg[node * 2][1], seg[node * 2 + 1][1]);
        }

        public void solve(int testNumber, FastReader in, PrintWriter out) {
            n = in.nextInt();
            int q = in.nextInt();
            points = new Point[n];
            for (int i = 0; i < n; i++) {
                points[i] = new Point(in.nextInt(), in.nextInt());
            }
            seg = new int[n * 4][2];
            buildSum(1, 0, n - 2);
            buildMax(1, 0, n - 3);
            for (int i = 0; i < q; i++) {
                char c = in.next().charAt(0);
                if (c == 'Q') {
                    int l = in.nextInt() - 1;
                    int r = in.nextInt() - 2;
                    out.println(querySum(l, r) - queryMax(l, r - 1));
                } else {
                    int index = in.nextInt() - 1;
                    points[index] = new Point(in.nextInt(), in.nextInt());
                    if (index > 0)
                        updateSum(index - 1, points[index - 1].dist(points[index]));
                    if (index < n - 1)
                        updateSum(index, points[index].dist(points[index + 1]));
                    if (index > 1)
                        updateMax(index - 2, points[index - 2].dist(points[index - 1]) + points[index - 1].dist(points[index]) - points[index - 2].dist(points[index]));
                    if (index > 0 && index < n - 1)
                        updateMax(index - 1, points[index - 1].dist(points[index]) + points[index].dist(points[index + 1]) - points[index - 1].dist(points[index + 1]));
                    if (index < n - 2)
                        updateMax(index, points[index].dist(points[index + 1]) + points[index + 1].dist(points[index + 2]) - points[index].dist(points[index + 2]));
                }
            }
        }

        class Point {
            int x;
            int y;

            public Point(int x, int y) {
                this.x = x;
                this.y = y;
            }

            int dist(Point p2) {
                return Math.abs(p2.x - x) + Math.abs(p2.y - y);
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

        public String nextString() {
            int c = read();
            while (isSpaceChar(c)) {
                c = read();
            }
            StringBuilder res = new StringBuilder();
            do {
                if (Character.isValidCodePoint(c)) {
                    res.appendCodePoint(c);
                }
                c = read();
            } while (!isSpaceChar(c));
            return res.toString();
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

        public String next() {
            return nextString();
        }

        public interface SpaceCharFilter {
            public boolean isSpaceChar(int ch);

        }

    }
}

