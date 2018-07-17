package DataStructures;

class BIT {
    int[] fen;
    int n;
    public BIT(int n) {
        this.n = n;
        fen = new int[n * 2];
    }
    void update(int num, int v) {
        for(int i = num + n; i < fen.length; i += Integer.lowestOneBit(i)) {
            fen[i]+=v;
        }
    }
    int query(int num) {
        int ret = 0;
        for(int i = num + n; i > 0; i -= Integer.lowestOneBit(i)) {
            ret += fen[i];
        }
        return ret;
    }
}
