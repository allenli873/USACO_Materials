vi computeZ(string seq) {
    int n = seq.size();
    vi z(n);
    int l, r, k;
    l = r = 0;
    for (int i = 1; i < n; ++i) {
        if(i > r) {
            l = r = i;
            while(r < n && seq[r - l] == seq[r])
                r++;
            z[i] = r - l;
            r--;
        } else {
            k = i - l;
            if(z[k] < r - i + 1)
                z[i] = z[k];
            else {
                l = i;
                while(r < n && seq[r - l] == seq[r])
                    r++;
                z[i] = r - l;
                r--;
            }
        }
    }
    return z;
}
