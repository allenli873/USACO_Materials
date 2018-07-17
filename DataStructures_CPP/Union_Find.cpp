//make sure to initialize par (par[i]=i)
int par[MAX_N];
int ran[MAX_N];

int find(int curr) {
    return par[curr] == curr ? curr : (par[curr] = find(par[curr]));
}

void unite(int n1, int n2) {
    int f1 = find(n1);
    int f2 = find(n2);
    if(ran[f1] > ran[f2]) {
        par[f2] = f1;
        ran[f1]++;
    } else {
        par[f1] = f2;
        ran[f2]++;
    }
}
