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
            inputStream = new FileInputStream("fortmoo.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("fortmoo.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        FastReader in = new FastReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Fortmoo2 solver = new Fortmoo2();
        solver.solve(1, in, out);
        out.close();
    }

    static class Fortmoo2 {
        int[][] dp;

        public void solve(int testNumber, FastReader in, PrintWriter out) {
            int n = in.nextInt();
            int m = in.nextInt();
            dp = new int[n + 1][m + 1];
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    dp[i][j] = dp[i - 1][j] + (in.nextCharacter() == 'X' ? 1 : 0);
                }
            }
            int res = 0;
            for (int a = 0; a < n; a++) {
                for (int b = a; b < n; b++) {
                    //previous rectange start
                    int prev = -1;
                    for (int i = 0; i < m; i++) {
                        boolean valid = sum(a, b, i) == 0;
                        if (valid) {
                            res = Math.max(res, b - a + 1);
                            if (prev != -1) {
                                res = Math.max(res, (i - prev + 1) * (b - a + 1));
                            }
                            if (prev == -1) {
                                prev = i;
                            }
                        }
                        //if top/bottom are taken
                        if (sum(a, a, i) > 0 || sum(b, b, i) > 0)
                            prev = -1;
                        if (valid && prev == -1)
                            prev = i;
                    }
                }
            }
            out.println(res);
        }

        int sum(int a, int b, int c) {
            ++a;
            ++b;
            ++c;
            return dp[b][c] - dp[a - 1][c];
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

