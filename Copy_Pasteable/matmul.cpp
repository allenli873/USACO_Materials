struct Mat {
    Mat(int N, int M) {
        m.resize(N);
        for (vector<T> &v : m)
            v.resize(M);
    }
    Mat(vector<vector<T>> &vec) : m(vec) {}
    Mat(Mat<T> &mat) : m(mat.m) {}

    vector<T> &operator[](int idx) { return m[idx]; }
    const vector<T> &operator[](int idx) const { return m[idx]; }
    int rows() const { return m.size(); }
    int cols() const { return m[0].size(); }

    static void exp(Mat &mat, ll po) {
        assert(mat.rows() == mat.cols());
        int n = mat.rows();
        Mat<T> a(mat);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) mat[i][j] = 1;
                else mat[i][j] = 0;
            }
        }
        while (po) {
            if (po & 1)
                mat = mult(mat, a);
            a = mult(a, a);
            po >>= 1;
        }
    }

    static Mat mult(const Mat &mat1, const Mat &mat2) {
        int n1 = mat1.rows(), m1 = mat1.cols();
        int n2 = mat2.rows(), m2 = mat2.cols();
        assert(m1 == n2);
        Mat res(n1, m2);
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < m2; j++) {
                for (int a = 0; a < m1; a++) {
                    res[i][j] += mat1[i][a] * mat2[a][j];
                }
            }
        }
        return res;
    }

    //printing
    friend ostream &operator<<(ostream &os, const Mat &m) {
        for (int i = 0; i < m.rows(); i++) {
            os << "[";
            for (int j = 0; j < m.cols(); j++) {
                os << m[i][j];
                if (j != m.cols() - 1) os << ',';
            }
            os << "]";
            if (i != m.rows() - 1) os << '\n';
        }
        return os;
    }
    
    vector<vector<T>> m;
};
