import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class censor {
    public static void main(String[] args) {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream("censor.in");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        OutputStream outputStream;
        try {
            outputStream = new FileOutputStream("censor.out");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Censoring solver = new Censoring();
        solver.solve(1, in, out);
        out.close();
    }

    static class Censoring {
        final int PRIME = 31;
        final int MOD = (int) 1E9 + 7;

        public void solve(int testNumber, InputReader in, PrintWriter out) {
            StringBuilder sb = new StringBuilder(in.next());
            int n = in.nextInt();
            long[] cens = new long[n]; //stores the hashes of each string
            int[] len = new int[n];
            for (int i = 0; i < n; i++) {
                String s = in.next();
                cens[i] = hash(s);
                len[i] = s.length();
            }
            long[] power = new long[n];
            for (int i = 0; i < n; i++) {
                power[i] = exponentiate(PRIME, len[i]);
            }

            long[] rHash = new long[n];
            for (int i = 0; i < sb.length(); i++) {
                for (int j = 0; j < n; j++) {
                    rHash[j] *= PRIME;
                    rHash[j] += sb.charAt(i) - 'a';
                    rHash[j] %= MOD;
                    if (i >= len[j]) {
                        //take out the first char
                        rHash[j] -= power[j] * (sb.charAt(i - len[j]) - 'a') % MOD;
                        while (rHash[j] < 0)
                            rHash[j] += MOD;
                        if (rHash[j] == cens[j]) {
                            sb.delete(i - len[j] + 1, i + 1);
                            i = -1;
                            Arrays.fill(rHash, 0);
                            break;
                        }
                    }
                }

            }
            out.println(sb);
        }

        long exponentiate(int prime, int i) {
            if(i == 0)
                return 1;
            if(i % 2 == 1)
                return prime * exponentiate(num, i - 1) % MOD;
            long n = exponentiate(prime, i / 2);
            return n * n % MOD;
        }

        long hash(String str) {
            long res = 0;
            for (int i = 0; i < str.length(); i++) {
                res = res * PRIME % MOD + (str.charAt(i) - 'a');
            }
            return res;
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

    }
}

