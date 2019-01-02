const int MAXN = 5005;
int V = MAXN, t;
vector<int> adj[MAXN];
vector<vector<int>> components;
void SCCUtil(int curr, int disc[], int low[], stack<int>* st, bool inStack[]) {
    disc[curr] = low[curr] = ++t;
    st -> push(curr);
    inStack[curr] = true;
    for(auto node: adj[curr]) {
        if(!disc[node]) {
            SCCUtil(node, disc, low, st, inStack);
            MIN(low[curr], low[node]);
        } else if(inStack[node])
            MIN(low[curr], disc[node]);
    }
    int tmp;
    if(low[curr] == disc[curr]) { //head
        vector<int> vec;
        while(st -> top() != curr) {
            tmp = st -> top(), st -> pop();
            vec.pb(tmp);
            inStack[tmp] = false;
        }
        tmp = st -> top(), st -> pop();
        vec.pb(tmp);
        inStack[tmp] = false;
        components.pb(vec);
    }
}
void SCC() {
    t = 0;
    int disc[V], low[V];
    bool inStack[V];
    stack<int>* st = new stack<int>();
    memset(disc, 0, sizeof disc);
    memset(low, 0, sizeof low);
    memset(inStack, false, sizeof inStack);
    F0R(i, V)
        if(!disc[i]) {
            SCCUtil(i, disc, low, st, inStack);
        }
}
