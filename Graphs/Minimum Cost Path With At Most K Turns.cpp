Approach 1:
// Use DFS ->Traverse every path and find the shortest path with atmost k turns
// //T.C:0(4^mn)

Appraoch 2: Multi Dimensional Dijkastra
// Dijkastra Algo ->Shortest algo used to find the minimum distance from source nodes to all the other nodes in a wieghted graph

// # Why Use Multidimensional (4D) Dijkstra?
// ## Problem Context
// Grid mein shortest cost path chahiye, lekin ek constraint ke saath: **at most `k` turns** allowed hain.
// Agar turn constraint na hoti, to simple hota: vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
// Sirf `(row, col)` track karo, minimum cost dhundo. Done.Lekin yaha turn constraint hai — isliye ye approach fail karti hai.

// ---

// ## Step 1: Why 2D Dijkastra fail

// grid = [[0,   0,   0, 1000],
//         [100, 100, 0, 0]]
// k = 1

// **True optimal path**: `(0,0)→(1,0)→(1,1)→(1,2)→(1,3)` (down, right, right, right)
// - Cost = 0+100+100+0+0 = **200**
// - Turns = sirf 1 (down→right pe)
// - **Valid** hai (k=1)

// ### Buggy 2D Code Kya Karta Hai:

// 1. Pehle ye path explore hota hai: `(0,0)→(0,1)→(1,1)` [right, phir down-turn]
//    → cost = 0+0+100 = **100**, pohochta hai (1,1) pe **"down" direction se**, turnCnt=1
//    → `dist[1][1] = 100` set ho jata hai

// 2. Ye state **dead-end** hai — (1,1) se (1,2) jaane ke liye "right" chahiye (direction change: down→right), turnCnt already 1 hai → 2 ho jayega → **invalid** (k=1). Path aage badh hi nahi sakta.

// 3. Ab sahi path try hota hai: `(0,0)→(1,0)→(1,1)` [down, phir right-turn]
//    → cost = 0+100+100 = **200**, pohochta hai (1,1) pe **"right" direction se**, turnCnt=1
//    → Yaha se aage "right" continue karna **bilkul valid** hai (same direction, koi naya turn nahi)

// 4. Lekin code ye check karta hai:
//    if (newcost < dist[new_i][new_j])   // 200 < 100? NO!
//    Cost 200 hai, `dist[1][1]` pehle se 100 hai → **ye valid, zaroori path discard ho jata hai!**

// 5. Result: sirf dead-end wala path bacha, jo eventually expensive route (via (0,3)) se (1,3) tak pohochta hai cost **1000** mein.
// Code ka output: 1000. Sahi answer: 200. ❌ GALAT!

// ---

// ## Step 3: Root Cause
// `dist[1][1] = 100` **ek hi number** store kar raha hai us cell ke liye — chahe wo kisi bhi direction/turns se aaya ho.
// Lekin haqeeqat mein (1,1) pe **do alag states** exist karte hain:
// | State | Cost | Future Potential |
// | `(1,1, dir=down, turns=1)` | 100 | ❌ Dead end — agla move "right" turn+1 karega → invalid |
// | `(1,1, dir=right, turns=1)` | 200 | ✅ Useful — "right" continue kar sakta hai, koi naya turn nahi lagega |

// **Dono ka future potential completely alag hai.** Sirf cost dekh ke ek ko discard karna galat hai — **cheaper hona "better" hone ki guarantee nahi deta**, agar wo aage jaake dead-end hai.

// ---

// ## Step 4: Fix — State Ko Expand Karo

// State sirf `(row, col)` nahi, balki:
// state = (row, col, direction, turns_used)

// Isko aise socho — jaise grid ki **multiple "layers"** ban gayi hain:
// - Har cell ke liye 4 (directions) × (k+1) (turn-counts) alag "versions" ho sakte hain
// - Har version ka apna independent "best cost" hoga

// Ab `(1,1, down, 1)` aur `(1,1, right, 1)` **do alag entries** hain is 4D array mein — dono independently apna best cost maintain karte hain, koi ek doosre ko wrongly overwrite/discard nahi karta.

// | **Dijkstra** | Exactly isi situation ke liye bana hai: non-negative weights + koi fixed order nahi + shortest cost chahiye. 
// Priority queue hamesha sabse sasta unprocessed state nikalta hai — guarantee: jab ek state pop ho, uska cost final minimum hota hai.

Time Complexity:
// Sabse Pehle Ye Samjho: Kitne "States" Hain?
// Har state hai: (row, col, direction, turns_used)
// row ke possible values: m
// col ke possible values: n
// direction ke possible values: 5 (4 real directions + 1 "start" sentinel)
// turns_used ke possible values: k+1 (0 se k tak)

// Har state ko heap se ek baar process karte hain.Jab ek state process hota hai, hum 4 directions try karte hain (edges)
// //To:
Total edges explored ≈ (Total states) × 4
                     ≈ O(m · n · k) × 4
                     = O(m · n · k)

// Ab Heap Ka Cost Add Karo
// Har baar jab hum heap mein push ya pop karte hain, wo O(log(heap size)) leta hai. Heap size worst case mein total states ke barabar ho sakta hai.
Total Time = O(m · n · k) states/edges × O(log(m · n · k)) heap operation
           = O(m · n · k · log(m · n · k))


//Space Complexity
//Size of 4D matrix:
= O(m · n · k)

class Solution {
public:
    // Type aliases taaki nested vectors likhna aasan ho jaye
    using v = vector<int>;
    using vv = vector<v>;
    using vvv = vector<vv>;

    // 4 possible moves: right, left, down, up
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int minCost(vector<vector<int>>& grid, int k) {

        int m = grid.size();
        int n = grid[0].size();

        // ---------------------------------------------------------
        // dir index meaning: 0=right, 1=left, 2=down, 3=up, 4=START
        // (4 = sentinel, matlab "abhi tak koi move nahi hua",  taaki pehla move kabhi bhi "turn" na gine)
        // ---------------------------------------------------------
        vector<vvv> dist(m, vvv(n, vv(5, v(k + 1, INT_MAX))));

        // ---------------------------------------------------------
        // PRIORITY QUEUE (min-heap) — Dijkstra ka core.
        // Heap entry = (cost, row, col, prevDir, turnCnt)
        // NOTE: 'cost' state ka part NAHI hai — wo sirf SORTING KEY  hai, taaki heap hamesha "abhi tak ka sabse sasta state"
        // hi pop kare. Actual identity sirf (row,col,dir,turns) hai.
        // ---------------------------------------------------------
          using State = tuple<int, int, int, int, int>;
        priority_queue<State, vector<State>, greater<State>> q;

        // Starting state: (0,0), prevDir=4 (no direction yet), turns=0
        q.push({grid[0][0], 0, 0, 4, 0});
        dist[0][0][4][0] = grid[0][0];

        while (!q.empty()) {
            auto [cost, i, j, prevDir, turnCnt] = q.top();
            q.pop();

            // -------------------------------------------------------
            // STALE ENTRY CHECK:
            // Ho sakta hai isi state ke liye heap mein ek CHEAPER
            // entry pehle hi process ho chuki ho (kyunki hum state
            // ko multiple baar, alag costs ke saath, push kar sakte
            // hain.)
            // Agar current entry ka cost, dist[] mein stored best
            // cost se zyada hai, iska matlab ye outdated hai — skip.
            // -------------------------------------------------------
            if (cost > dist[i][j][prevDir][turnCnt])
                continue;

            // -------------------------------------------------------
            // DESTINATION CHECK:
            // Dijkstra guarantee karta hai (kyunki saare edge weights
            // >= 0 hain) ki jab destination PEHLI BAAR heap se pop
            // hota hai, uska cost hi GLOBAL MINIMUM hota hai.
            // Kyunki heap hamesha sabse chota cost pehle deta hai,
            // koi bhi abhi tak unexplored path is se sasta ho hi
            // nahi sakta. Isliye turant return kar sakte hain.
            // -------------------------------------------------------
            if (i == m - 1 && j == n - 1)
                return cost;

            // Chaaron directions try karo
            for (int d = 0; d < 4; d++) {
                int new_i = i + dir[d][0];
                int new_j = j + dir[d][1];

                // Boundary check
                if (min(new_i, new_j) < 0 || new_i >= m || new_j >= n)
                    continue;

                // -----------------------------------------------
                // TURN COUNT UPDATE:
                // Agar ye pehla move hai (prevDir==4) YA naya
                // direction purane jaisa hi hai -> turn nahi lagta.
                // Warna turnCnt ek badh jayega.
                // -----------------------------------------------
                int newCnt =
                    (prevDir == 4 || d == prevDir) ? turnCnt : turnCnt + 1;

                // Agar turns limit se zyada ho gaye, ye path invalid
                // hai — is state ko explore hi mat karo
                if (newCnt > k) {
                    continue;
                }

                int newCost = cost + grid[new_i][new_j];

                // -----------------------------------------------
                // RELAXATION STEP (Dijkstra ka standard step):
                // Agar naya cost, is exact state ke liye ab tak ke
                // best cost se kam hai, to update karo aur is naye
                // (behtar) version ko heap mein push karo.
                // -----------------------------------------------
                if (newCost < dist[new_i][new_j][d][newCnt]) {
                    dist[new_i][new_j][d][newCnt] = newCost;
                    q.push({newCost, new_i, new_j, d, newCnt});
                }
            }
        }

        // Heap khaali ho gaya aur destination kabhi pop nahi hua
        // -> matlab koi valid path exist hi nahi karta within k turns
        return -1;
    }
};
