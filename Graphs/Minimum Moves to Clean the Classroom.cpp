//Appraoch:Bitmask

//
//  Grid cells:
//    'S' → Starting position
//    'L' → Litter (must collect all)
//    'R' → Reset  (energy → MAX instantly, reusable)
//    'X' → Obstacle (cannot pass)
//    '.' → Empty space
//
//  Rules:
//    • Every move costs 1 energy
//    • energy == 0 → cannot move (unless standing on R)
//    • Step on R   → energy fully restored
//    • Step on L   → that litter is collected
//
//  Goal : collect ALL litter → return minimum moves
//         impossible         → return -1

//============================================================
//  WHAT IS A BITMASK?
//============================================================
//  We have multiple litters. We need to track WHICH ones
//  are collected. Instead of a vector<bool>, we use a single
//  integer where each BIT = one litter's status.
//
//    bit = 0  →  litter NOT collected yet
//    bit = 1  →  litter IS collected

//  Example with 3 litters (L0, L1, L2):
//
//    mask = 000  →  nothing collected       (start)
//    mask = 001  →  only L0 collected       (1 << 0)
//    mask = 010  →  only L1 collected       (1 << 1)
//    mask = 100  →  only L2 collected       (1 << 2)
//    mask = 011  →  L0 + L1 collected       (001 | 010)   
//    mask = 111  →  ALL collected ✓         (001 | 010 | 100)   ← this is fullMask

//  How to collect litter Li:
   newMask |= (1 << id[i][j])  //get the previous one's using OR and  Mark the current one also
     
//    Example: collecting L1
//      1 << 1     =  010
//      000 | 010  =  010   ← Get the previous L0 and add it using OR -> L1 is now marked collected

//  How to assign IDs to each litter (1<<id)?
//For this we will assign every 'L' cell a unique id (0,1,2…)
// Code:
  int m = classroom.size(), n = classroom[0].size();
   vector<vector<int>> id(m, vector<int>(n, -1));
    int sr = -1, sc = -1, cnt = 0;

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++) {
                if(classroom[i][j] == 'S') { sr=i; sc=j; }
                if(classroom[i][j] == 'L') id[i][j] = cnt++; //store id for all the litters
            }
        }


//How do we know we cleaned all Litter using Bitmask?
// If we reach fullmask(L0|L1|L2.....) ,  we know we cleaned all litters
//To calculate fullmask, [ fullmask = (1 << cnt) - 1 ]
//example if there are 3 litters the fullmask will be (1<<3)-1 => 8-1 = 7 or '111'

        int fullMask = (1 << cnt) - 1;




//============================================================
//  WHY BFS? (not DFS or Dijkstra)
//============================================================

// Every move from one cell to another costs exactly:  1 move
// That makes this a perfect BFS problem. BFS explores states in increasing number of moves:
// 0 moves
//    |
// 1 move
//    |
// 2 moves
//    |
// ...
// So the first state where all litter is collected gives the minimum number of moves.

// BFS Kyun? (Dijkstra kyun nahi?)
// Har move ka cost exactly 1 hai.
// BFS automatically shortest path deta hai jab sab edges equal cost ke hoon.
// Pehli baar jab mask == fullMask mile — wahi minimum moves hai!
//  DFS      → goes deep, cannot guarantee shortest path
//  Dijkstra → for unequal weights; overkill here, BFS suffices


//============================================================
//  WHY NORMAL BFS (row, col) FAILS
//============================================================
 // Imagine two paths both reaching cell (2,3):
//    Path A: S → L0 → (2,3)   collected: L0   energy: 3
//    Path B: S → L1 → (2,3)   collected: L1   energy: 3
//
//  Normal BFS: "(2,3) already visited → skip Path B"  ✗
//  But Path A never got L1! Skipping B means L1 is never collected.
//
//  Fix: add mask to the state → (row, col, mask)
//
//    (2, 3, mask=001)  ←  L0 collected   → explore
//    (2, 3, mask=010)  ←  L1 collected   → also explore (DIFFERENT state!)
//
//  Same cell, different masks = completely different states.
//============================================================
//  KEY OPTIMIZATION — best[r][c][mask]
//============================================================
//
//  Even with mask in state, we could reach the same
//  (row, col, mask) multiple times with different energies.
//
//  best[r][c][mask] = MAX energy with which we have EVER reached (r, c) with this exact mask.
//
//  PRUNING RULE:
//    If we reach (nx, ny, newMask) with energy newEn,  but best[nx][ny][newMask] >= newEn already → SKIP IT.
//
//    Why? 
//   A previous path already reached here with >= energy  AND same collected litter. It can do everything this path
//    can do, and more. This new path is useless.
//
//  IMPORTANT EDGE CASE — more moves but more energy:
//
//    State A: (r,c,mask) in 2 moves, energy = 2
//    State B: (r,c,mask) in 3 moves, energy = 4
//
//    Neither is strictly better!
//    A has fewer moves. B can travel farther without dying.
//
//    BFS processes A first (fewer moves in queue). B is also kept because its energy (4) > best so far (2).
//    best[r][c][mask] updates to 4 → B is NOT pruned.  Both paths are explored. ✓
//

CODE:
// best[r][c][mask] = max energy at this state 
vector<vector<vector<int>>> best(m, vector<vector<int>>(n, vector<int>(masks, -1)));

if(best[nr][nc][newMask] >= newEn) continue;  // Already better path h humare pass(minimum) to continue , Else
best[nr][nc][newMask] = newEn;                // Update karo
q.push({nr, nc, newMask, newEn, dist+1});     // Explore this new beast path

//============================================================
//How do we check we dont visit the same path again?
//============================================================
if (best[nr][nc][newMask] >= newEn)
    continue;

// It means "for future states, don't explore a new path if it reaches the same position + mask with less/equal energy."


//============================================================
CODE:
 APPROACH: BFS + Bitmask 
//============================================================
class Solution {
public:
  

/*
    ═══════════════════════════════════════════════════════
     COMPLEXITY ANALYSIS
    ═══════════════════════════════════════════════════════

     Variables:
       m = rows (≤20), n = cols (≤20), L = litter count (≤10)
       2^L = total bitmask combinations (≤1024)

     TIME COMPLEXITY: O(m × n × 2^L)
     ──────────────────────────────────
     Total unique states = m × n × 2^L
       (har cell ke liye, har possible mask combination)

     Har state ek baar queue mein aata hai (best[] pruning ki wajah se)
     Har state ke liye 4 neighbors check karte hain → 4 × O(1)

     Max states: 20 × 20 × 1024 = 409,600  ← bilkul manageable!

     SPACE COMPLEXITY: O(m × n × 2^L)
     ───────────────────────────────────
     best[m][n][2^L] array       → O(m × n × 2^L)
     BFS queue (worst case)      → O(m × n × 2^L)
     id[m][n] array              → O(m × n)

     Total dominant term         → O(m × n × 2^L)
     Max space: ~409,600 integers ← perfectly fine
    ═══════════════════════════════════════════════════════
    */



CODE:
    int dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

    int minMoves(vector<string>& classroom, int energy) {

        int m = classroom.size();
        int n = classroom[0].size();

        // ── Step 1: Grid scan ──────────────────────────────────────────
        // Starting position dhundo + har litter ko unique ID do (0-indexed)
        // ID baad mein bitmask banane ke kaam aayega

        int srci = -1, srcj = -1;
        int cnt  = 0;  // total litter count

        vector<vector<int>> id(m, vector<int>(n, -1));  // litter ID map

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    srci = i;
                    srcj = j;
                }
                if (classroom[i][j] == 'L') {
                    id[i][j] = cnt++;  // L0 → id=0, L1 → id=1, ...
                }
            }
        }

        // ── Step 2: fullMask banao ────────────────────────────────────
        // Jab mask == fullMask → saari litter collect ho gayi
        // Example: 3 litters → fullMask = (1<<3)-1 = 111 = 7

        int fullMask = (1 << cnt) - 1;

        // ── Step 3: best[r][c][mask] array ───────────────────────────
        // best[i][j][mask] = max energy jis se hum (i,j) pe
        //                    is mask state mein pahunche hain
        // -1 matlab abhi tak is state mein nahi pahunche

        vector<vector<vector<int>>> best(
            m, vector<vector<int>>(n, vector<int>(fullMask + 1, -1))
        );

        // ── Step 4: BFS setup ─────────────────────────────────────────
        struct State {
            int x, y;    // current position
            int mask;    // litters collected so far (bitmask)
            int en;      // energy remaining
            int dist;    // moves taken so far
        };

        queue<State> q;

        // Start: position=S, mask=0 (kuch collect nahi), full energy, 0 moves
        q.push({srci, srcj, 0, energy, 0});
        best[srci][srcj][0] = energy;

        // ── Step 5: BFS loop ──────────────────────────────────────────
        while (!q.empty()) {

            auto [x, y, mask, en, dist] = q.front();
            q.pop();

            // ✓ Saari litter collect ho gayi → yahi answer hai
            // BFS guarantee karta hai ki yeh minimum moves hai
            if (mask == fullMask) return dist;

            // ✗ Energy khatam → aage nahi ja sakte, state skip
            if (en == 0) continue;

            // Charon directions try karo
            for (auto& d : dirs) {

                int nx = x + d[0];
                int ny = y + d[1];

                // Grid ke bahar gaya → skip
                if (min(nx, ny) < 0 || nx >= m || ny >= n) continue;

                // Obstacle → skip
                if (classroom[nx][ny] == 'X') continue;

                // Har move mein 1 energy lagti hai
                int newEn   = en - 1;
                int newMask = mask;  // pehle se collected litter copy karo

                // Litter mili → us bit ko ON karo (collect!)
                // Example: L1 mili → newMask |= (1<<1) → bit1 = 1
                if (classroom[nx][ny] == 'L') {
                    newMask |= (1 << id[nx][ny]);
                }

                // Reset cell → energy poori bhar do
                if (classroom[nx][ny] == 'R') {
                    newEn = energy;
                }

                // KEY PRUNING:
                // Agar is (nx, ny, newMask) state mein pehle se
                // equal ya zyada energy se pahunche hain → yeh state
                // useless hai, skip karo
                if (best[nx][ny][newMask] >= newEn) continue;

                // Naya best update karo aur state queue mein daalo
                best[nx][ny][newMask] = newEn;
                q.push({nx, ny, newMask, newEn, dist + 1});
            }
        }

        // Saari litter collect karna impossible tha
        return -1;
    }

    
};

