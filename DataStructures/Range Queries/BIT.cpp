template<class Type, int SZ>
class BIT {
public:
    Type fen[SZ * 2];
    int n;

    Type query(int idx) {
        Type ret = 0;
        for(int i = idx + 5; i > 0; i -= i & -i)
            ret += fen[i];
        return ret;
    }

    void update(int idx, Type val) {
        for(int i = idx + 5; i < n * 2; i += i & -i)
            fen[i] += val;
    }
};
