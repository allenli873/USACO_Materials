import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.InputMismatchException;
import java.io.IOException;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author Allen Li
 */
public class guard {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("guard.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("guard.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        FastReader in = new FastReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        GuardMark solver = new GuardMark();
        solver.solve(1, in, out);
        out.close();
    }

    static class GuardMark {
        final int N_INF = Integer.MIN_VALUE / 4;

        public void solve(int testNumber, FastReader in, PrintWriter out) {
            int n = in.nextInt();
            int h = in.nextInt();
            Cow[] cows = new Cow[n];
            for (int i = 0; i < n; i++) {
                cows[i] = new Cow(in.nextInt(), in.nextInt(), in.nextInt());
            }

            int[] dp = new int[1 << n]; //dp(i)=safety with mask i
            Arrays.fill(dp, N_INF);
            for (int i = 0; i < n; i++) {
                dp[1 << i] = cows[i].s;
            }
            for (int i = 1; i < 1 << n; i++) {
                if (dp[i] != N_INF) {
                    for (int j = 0; j < n; j++) {
                        if ((i & 1 << j) >= 1)
                            continue;
                        int factor = Math.min(dp[i] - cows[j].w, cows[j].s);
                        if (dp[i | 1 << j] < factor)
                            dp[i | 1 << j] = factor;
                    }
                }
            }
            int max = N_INF;
            for (int i = 1; i < 1 << n; i++) {
                if (dp[i] == N_INF)
                    continue;
                long height = 0;
                for (int j = 0; j < n; j++) {
                    if ((i & 1 << j) >= 1)
                        height += cows[j].h;
                }
                if (height >= h)
                    max = Math.max(max, dp[i]);
            }
            if (max >= 0)
                out.println(max);
            else
                out.println("Mark is too tall");
        }

        class Cow {
            int h;
            int w;
            int s;

            public Cow(int h, int w, int s) {
                this.h = h;
                this.w = w;
                this.s = s;
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

        public interface SpaceCharFilter {
            public boolean isSpaceChar(int ch);

        }

    }
}

