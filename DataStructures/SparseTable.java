package DataStructures;

import java.util.ArrayList;
import java.util.List;

class SparseTable {
    int[][] par;
    int[] depth;
    List<List<Integer>> adjList = new ArrayList<List<Integer>>();
    int root;
    int n;
    public SparseTable(int n) {
        this.n = n;
        root = -1;
        par = new int[n + 1][18];
        for(int i = 0; i <= n; i++) {
            adjList.add(new ArrayList<Integer>());
        }
        depth = new int[n + 1];
    }

    void addVal(int val, int parent) {
        par[val][0] = parent;
        adjList.get(parent).add(val);
    }

    void calculate() { //call this method after filling out parents
        for(int i = 1; i <= n; i++) {
            if(par[i][0] == 0) {//then it is the root
                root = i;
                break;
            }
        }
        dfs(root, root);
        for(int j = 1; j < 18; j++) {
            for(int i = 1; i <= n; i++) {
                par[i][j] = par[par[i][j - 1]][j - 1];
            }
        }
    }

    void dfs(int d, int val) {
        depth[val] = d;
        if(adjList.get(val).isEmpty())
            return;
        for(int i: adjList.get(val))
            dfs(d + 1, i);
    }

    void lca(int a, int c) {
        while(par[a][0] != par[c][0]) {
            if(depth[a] > depth[c]) {
                int liftNeed = depth[a] - depth[c];
                String str = Integer.toBinaryString(liftNeed);
                for(int j = 0; j < str.length(); j++)
                    if(str.charAt(j) == '1')
                        a = par[a][str.length() - j - 1];
            } else if(depth[c] > depth[a]) {
                int liftNeed = depth[c] - depth[a];
                String str = Integer.toBinaryString(liftNeed);
                for(int j = 0; j < str.length(); j++)
                    if(str.charAt(j) == '1')
                        c = par[c][str.length() - j - 1];
            } else { //lift them both
                while(par[a][0] != par[c][0])
                    for(int j = 1; j < 18; j++)
                        if(par[a][j] == par[c][j]) { //take the one before it
                            a = par[a][j - 1];
                            c = par[c][j - 1];
                            break;
                        }
            }
        }
    }
}
