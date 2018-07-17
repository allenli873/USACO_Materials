package DataStructures;

public class UnionFind {
    int[] parent, rank;
    public UnionFind(int n) {
        parent = new int[n + 1];
        rank = new int[n + 1];
        for(int i = 1; i <= n; i++) {
        	parent[i] = i;
        }
    }
    int find(int curr) {
        return parent[curr] == curr ? curr : (parent[curr] = find(parent[curr]));
    }

    void union(int n1, int n2) {
        int f1 = find(n1);
        int f2 = find(n2);
        if(rank[f1] > rank[f2]) {
            parent[f2] = f1;
            rank[f1]++;
        } else {
            parent[f1] = f2;
            rank[f2]++;
        }
    }
}
