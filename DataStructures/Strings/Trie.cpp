struct TrieNode {
    TrieNode *ch[26];
    TrieNode() {
        for (int i = 0; i < 26; i++) {
            ch[i] = nullptr;
        }
    }
    bool isEnd;
};

void insert(TrieNode *u, string &str, int depth) {
    if (depth == str.size()) {
        u->isEnd = true;
        return;
    }
    int cur = str[depth] - 'a';
    if (!u->ch[cur]) {
        u->ch[cur] = new TrieNode;
    }
    insert(u->ch[cur], str, depth + 1);
}
