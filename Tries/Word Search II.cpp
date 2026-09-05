// Approach 1:
// Har word ke liye alag se DFS chalao poore board pe.
// N words hain, board size m×n hai.
// TC = O(N × m × n × 4^L) (L = avg word length, DFS branching factor 4 hoti hai)
// Bahut redundant kaam hota hai kyunki common prefixes baar baar traverse hote hain.


// Approach2: (Trie + Single DFS)
// Saare N words ko ek Trie mein daal do. Isse common prefixes share ho jaate hain.
// Ab board ke har cell se sirf ek baar DFS chalao (poore words list ke liye ek saath), Trie ko follow karte hue.
// Jaise hi DFS mein endOfWord = true milta hai, matlab wahan tak ek complete word ban chuka hai — usko result mein daal do.
// Trick: Ek baar word mil jaye to endOfWord = false kar do taaki duplicate na aaye result mein.
// Visited track karne ke liye board cell ko temporarily '.' (ya koi invalid marker) se mark karo, DFS ke baad wapas original character restore kar do (backtracking).


//T.C:
// Trie banane ka cost: O(N × L) — N words, har word ki avg length L.
// DFS traversal: Har cell se hum DFS start karte hain, aur worst case mein 4 directions explore karte hain. 
// Trie ki wajah se DFS depth zyada se zyada longest word ki length (L_max) tak hi jaati hai (kyunki agar Trie mein path nahi hai to hum prune kar dete hain).
// Overall worst case: O(m × n × 4^(L_max))
// (yahan N ka factor Trie ki wajah se hat gaya, kyunki common prefixes share ho jaate hain aur redundant DFS calls nahi hoti )

//S.C:
// Trie storage: O(N × L) — worst case har character ke liye naya node (agar koi common prefix na ho).
// Recursion stack (DFS): O(L_max) — longest word ki length jitni depth tak DFS jaayega.
// Result storage: O(N × L) — matched words store karne ke liye.


class Solution {
public:
    // ---------- Trie Node Definition ----------
    struct trieNode {
        bool endOfWord = false;      // true agar yahan tak koi complete word khatam hota hai
        string word = "";            // agar endOfWord true hai, to wo poora word yahan store hoga
        trieNode* character[26] = {}; // 26 english lowercase letters ke liye child pointers
    };

    // ---------- Insert a word into Trie ----------
    // Har character ke liye Trie mein node banate jao (agar already exist nahi karta)
    void insertWord(trieNode* root, string word) {
        int n = word.size();
        for (int i = 0; i < n; i++) {
            char ch = word[i];
            if (root->character[ch - 'a'] == NULL) {
                root->character[ch - 'a'] = new trieNode();
            }
            root = root->character[ch - 'a'];
        }
        // Last node pe word complete hone ka marker laga do
        root->endOfWord = true;
        root->word = word; // pura word store kar liya taaki baad mein direct nikal sakein
    }

    // 4 directions: left, right, down, up
    int dir[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
    vector<string> res; // final answer store karne ke liye

    // ---------- DFS + Trie traversal ----------
    // root = current trie node jahan tak hum match kar chuke hain
    void findStr(vector<vector<char>>& board, int i, int j, trieNode* root) {

        // Boundary check + already visited cell check ('.' means visited)
        if (min(i, j) < 0 || i >= board.size() || j >= board[0].size() ||
            board[i][j] == '.') {
            return;
        }

        char ch = board[i][j];

        // Agar current character ka Trie mein path hi nahi hai,
        // matlab is direction mein koi word match nahi hoga -> prune kar do
        if (root->character[ch - 'a'] == NULL) {
            return;
        }

        // Trie mein aage badho
        trieNode* newRoot = root->character[ch - 'a'];

        // Agar yahan tak ek complete word ban gaya hai
        if (newRoot->endOfWord == true) {
            newRoot->endOfWord = false;   // duplicate se bachne ke liye flag off kar do
            res.push_back(newRoot->word); // result mein daal do
        }

        // Current cell ko visited mark karo (backtracking ke liye temporary change)
        board[i][j] = '.';

        // 4 directions mein DFS calls
        for (auto& d : dir) {
            int new_i = i + d[0];
            int new_j = j + d[1];
            findStr(board, new_i, new_j, newRoot);
        }

        // Backtrack: cell ko original character wapas de do
        // (kyunki yehi cell doosre starting point/path se bhi use ho sakta hai)
        board[i][j] = ch;
    }

    vector<string> findWords(vector<vector<char>>& board,
                              vector<string>& words) {

        // Root node of Trie
        trieNode* root = new trieNode();

        // Saare words ka ek Trie structure bana do
        for (int i = 0; i < words.size(); i++) {
            insertWord(root, words[i]);
        }

        // Board ke har cell se DFS start karo (agar us character se koi word start hota hai Trie mein)
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                char ch = board[i][j];
                if (root->character[ch - 'a'] != NULL) {
                    findStr(board, i, j, root);
                }
            }
        }

        return res;
    }
};
