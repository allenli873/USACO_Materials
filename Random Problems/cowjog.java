import java.io.OutputStream;
import java.io.FilenameFilter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.File;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 *
 * @author Allen Li
 */
public class cowjog {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            final String regex = "cowjog.in";
            File directory = new File(".");
            File[] candidates = directory.listFiles(new FilenameFilter() {
                public boolean accept(File dir, String name) {
                    return name.matches(regex);
                }
            });
            File toRun = null;
            for (File candidate : candidates) {
                if (toRun == null || candidate.lastModified() > toRun.lastModified())
                    toRun = candidate;
            }
            inputStream = new FileInputStream(toRun);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("cowjog.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        CowJog solver = new CowJog();
        solver.solve(1, in, out);
        out.close();
    }

    static class CowJog {
        public void solve(int testNumber, InputReader in, PrintWriter out) {
            int n = in.nextInt();
            long t = in.nextLong();
            long[] res = new long[n];
            for (int i = 0; i < n; i++) {
                res[i] = in.nextLong() + in.nextLong() * t;
            }
            out.println(lis(res, res.length));
        }

        int upper_bound(long arr[], int l, int r, long key) {
            while (l < r) {
                int m = (l + r) / 2;
                if (arr[m] >= key)
                    l = m + 1;
                else
                    r = m;
            }
            return l;
        }

        int lis(long arr[], int size) {
            long[] tail = new long[size];
            int len = 1;
            tail[0] = arr[0];
            for (int i = 1; i < size; i++) {
                if (arr[i] > tail[0])
                    tail[0] = arr[i];
                else if (arr[i] <= tail[len - 1])
                    tail[len++] = arr[i];
                else
                    tail[upper_bound(tail, 0, len - 1, arr[i])] = arr[i];
            }
            return len;
        }

    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }

    }
}

