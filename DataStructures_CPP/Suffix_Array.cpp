struct suffix {
    int idx;
    pi rank;
    bool operator<(const suffix& o) const {
        return rank < o.rank;
    }
};

int* buildSuffixArray(string text) {
    int n = text.size();
    suffix suff[n];
    F0R(i, n) {
        suff[i].idx = i;
        suff[i].rank.f = text[i] - 'a';
        suff[i].rank.s = ((i + 1) < n) ? (text[i + 1] - 'a') : -1;
    }
    sort(suff, suff + n);
    int ind[n];
    for(int k = 4; k <= 2 * n; k *= 2) {
        int rank = 0;
        int prev = suff[0].rank.f;
        suff[0].rank.f = rank;
        ind[suff[0].idx] = 0;
        FOR(i, 1, n) {
            if(suff[i].rank.f == prev && suff[i].rank.s == suff[i-1].rank.s) { //if the two are equal
                suff[i].rank.f = rank;
            } else {
                prev = suff[i].rank.f;
                suff[i].rank.f = ++rank;
            }
            ind[suff[i].idx] = i;
        }
        F0R(i, n) {
            int next = suff[i].idx + k/2;
            suff[i].rank.s = (next < n) ? suff[ind[next]].rank.f : -1;
        }
        sort(suff, suff + n);
    }
    int* ret = new int[n];
    F0R(i, n)
        ret[i] = suff[i].idx;
    return ret;
}

int* buildLCPArray(string text, int* suffixArr) {
    int n = text.size();
    int* ret = new int[n];
    F0R(i, n)
        ret[i]=0;
    int inv[n];
    F0R(i, n)
        inv[suffixArr[i]] = i;
    int prev = 0;
    F0R(i, n) {
        if(inv[i] == n - 1) {
            prev = 0;
            continue;
        }
        int j = suffixArr[inv[i] + 1];
        while(i + prev < n && j + prev < n && text[i + prev] == text[j + prev])
            prev++;
        ret[inv[i]] = prev;
        if(prev)
            prev--;
    }
    return ret;
}
