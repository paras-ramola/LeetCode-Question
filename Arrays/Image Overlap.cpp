Problem
// Tumhare paas do binary matrices hain — `img1` aur `img2` (dono n×n). Tumhe `img1` ko **left-right ya up-down slide (translate)** 
// karna hai (rotate nahi karna) taaki jab overlap ho,  dono me jitne zyada se zyada cells `1` match ho jaayein.
// **Key baat**: Hum matrix ko *rotate* nahi kar sakte, sirf *shift* (translate) kar sakte hain — left/right/up/down.

"Offset" ka matlab kya hai?
// Jab tum ek matrix ko doosre ke upar slide karte ho, to ye socho ki har cell apni jagah se kitna hata hai.
// - `rowOff` = kitni rows neeche/upar shift hui
// - `colOff` = kitni columns left/right shift hui

How we use Offset in Code?
 // Hum `img1` (A) ko physically move nahi karte (kyunki wo mehenga operation hai — naya matrix banana padega).
// Iske bajaye hum **indices ka offset calculate karte hain** — matlab, agar A ka cell `(i, j)` hai, to shift hone ke baad ye kaunse B ke cell ke corresponding aayega?
// B_i = i + rowOff
// B_j = j + colOff


What will be the range of offset?
-n+1 to n
//isse ye endure hota h ki min ek row ya col overlapp hori h

  
// Agar `rowOff = 1, colOff = 0`, matlab A ko 1 row neeche shift kiya — to A ka cell (0,0) ab B ke cell (1,0) ke saamne aa jaayega. Isiliye humne B_i = i + rowOff likha.
// 
  
## Step-by-step approach

// 1. **Har possible offset try karo**: `rowOff` aur `colOff` dono `-(n-1)` se `(n-1)` tak ja sakte hain (isse zyada shift karoge to matrices overlap hi nahi karengi).
// 2. **Har offset ke liye**: A ke har cell `(i,j)` ko check karo — uska corresponding B cell nikaalo `(i+rowOff, j+colOff)`.
// 3. **Bounds check karo**: agar ye corresponding index matrix ke bahar chala gaya, to skip karo (kyunki wahan koi overlap nahi hai).
// 4. **Agar dono cells `1` hain**, count badhao.
// 5. **Sabhi offsets me se max count wala answer return karo**.
  
 Time Complexity
// - Offsets: `O(n)` row × `O(n)` col = `O(n²)` offsets
// - Har offset ke liye counting: `O(n²)`
// - Total: **O(n⁴)** 
CODE:
  
class Solution {
public:
    int n;

    // Given a specific (rowOff, colOff) shift, count kitne positions par
    // A aur B dono me 1 overlap ho rahe hain
    int countOverlap(vector<vector<int>>& A, vector<vector<int>>& B,
                     int rowOff, int colOff) {

        int cnt = 0;

        // A ke har cell (i, j) ko fix maano (A ko move nahi kar rahe)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                // Agar A ko (rowOff, colOff) se shift kiya jaaye,
                // to A ka (i,j) cell, B ke kis cell ke upar aakar baithega?
                // Isiliye hum B ke corresponding index nikaal rahe hain,
                // bina B ko physically shift kiye.
                int B_i = i + rowOff;
                int B_j = j + colOff;

                // Agar ye corresponding index B ki grid se bahar chala gaya,
                // to yahan koi overlap possible nahi -> skip
                if (B_i < 0 || B_i >= n || B_j < 0 || B_j >= n) {
                    continue;
                }

                // Dono jagah 1 mila -> overlap count badhao
                if (A[i][j] == 1 && B[B_i][B_j] == 1) {
                    cnt++;
                }
            }
        }
        return cnt;
    }

    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        n = img1.size();
        int maxOverlapCnt = 0;

        // Row shift -(n-1) se (n-1) tak try karo
        // (isse zyada shift karne par dono matrices ka koi common region hi nahi bachega)
        for (int rowOff = -n + 1; rowOff < n; rowOff++) {

            // Column shift bhi -(n-1) se (n-1) tak try karo
            for (int colOff = -n + 1; colOff < n; colOff++) {

                // Is particular shift ke liye overlap count nikaalo
                int overlapCnt = countOverlap(img1, img2, rowOff, colOff);

                // Ab tak ka best overlap update karo
                maxOverlapCnt = max(maxOverlapCnt, overlapCnt);
            }
        }
        return maxOverlapCnt;
    }
};



# Optimized Approach - "Coordinates match karo, poori grid nahi"

## Pehle problem samjho brute force wale me
// Upar wale approach me hum **har possible shift** ke liye **puri n×n grid scan** kar rahe the — chahe wahan 1's ho ya na ho. 
// Ye waste hai! Agar matrix mostly 0's se bhari hai (sparse hai), to hum bekar me 0's ko bhi check kar rahe hain.


Idea
// Socho tumhare paas do sheets hain, dono par sirf kuch **specific dots (1's)** bane hain — baaki sab khaali hai. Ab tumhe pucha jaaye "dono sheets ko slide karke max dots kaise overlap karoge?"
// Ek smart insaan kya karega? Wo **khaali jagah ko ignore** karega aur sirf **dots ke positions** yaad rakhega. Fir har dot pair (ek A ka, ek B ka) ke beech "kitna shift chahiye unhe overlap karne ke liye" calculate karega.
// **Key insight**: Agar A ka ek dot `(x1, y1)` par hai aur B ka ek dot `(x2, y2)` par hai, to inhe overlap karne ke liye jo shift chahiye wo hai:

rowOff = x2 - x1
colOff = y2 - y1


// Agar tum A ko exactly isi `(rowOff, colOff)` se shift karo, to ye dono dots overlap ho jaayenge!

## Approach

// Ab tumhe sirf ye karna hai:
// 1. A ke saare 1's ke coordinates nikaalo (list bana lo)
// 2. B ke saare 1's ke coordinates nikaalo (list bana lo)
// 3. **Har A ka dot** aur **har B ka dot** ka pair banao, unke beech ka `(rowOff, colOff)` nikaalo
// 4. Ek **hashmap** me count karo — konsa `(rowOff, colOff)` sabse zyada baar aaya
// 5. Jo offset sabse zyada baar aaya, wahi tumhara max overlap hai!

// **Kyun ye kaam karta hai?** Kyunki agar ek particular `(rowOff, colOff)` shift 5 baar aaya (matlab 5 different dot-pairs isi shift se match ho rahe hain),
//  to iska matlab hai ki **usi ek shift** par 5 overlaps ek saath ho rahe hain!

 example

img1 (A):        img2 (B):
1 0               0 1
0 1               1 0

// **Step 1**: A ke 1's ke coordinates: `(0,0)` aur `(1,1)`
// **Step 2**: B ke 1's ke coordinates: `(0,1)` aur `(1,0)`

// **Step 3**: Har A-dot aur B-dot ka pair banao:

// | A dot | B dot | rowOff = Bx-Ax | colOff = By-Ay |
// |-------|-------|----------------|-----------------|
// | (0,0) | (0,1) | 0-0=0 | 1-0=1 |
// | (0,0) | (1,0) | 1-0=1 | 0-0=0 |
// | (1,1) | (0,1) | 0-1=-1 | 1-1=0 |
// | (1,1) | (1,0) | 1-1=0 | 0-1=-1 |

// **Step 4**: Hashmap me count karo:
// ```
// (0,1)  -> 1
// (1,0)  -> 1
// (-1,0) -> 1
// (0,-1) -> 1
// ```

// Sabhi offsets sirf 1 baar aaye. Matlab **max overlap = 1**.

// Ye match karta hai humare pehle wale manual calculation se (jab humne `colOff=1` try kiya tha to overlap 1 mila tha)!

Time Complexity
O(n²) + O(k²)    k = number of 1's 
≈ O(n²)
 
  Code :

class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();

        vector<pair<int,int>> onesA, onesB;

        // Step 1: A ke saare 1's ke coordinates nikaalo
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (img1[i][j] == 1)
                    onesA.push_back({i, j});

        // Step 2: B ke saare 1's ke coordinates nikaalo
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (img2[i][j] == 1)
                    onesB.push_back({i, j});

        // Step 3: Har (A-dot, B-dot) pair ke liye offset nikaalo
        // aur hashmap me count badhao
        unordered_map<int, int> offsetCount; // key = encoded (rowOff, colOff)
        int maxOverlap = 0;

        for (auto& a : onesA) {
            for (auto& b : onesB) {
                int rowOff = b.first - a.first;
                int colOff = b.second - a.second;

                // rowOff aur colOff ko ek single key me encode karo
                // (taaki hashmap me easily store ho sake)
                int key = (rowOff + n) * (2*n) + (colOff + n);

                offsetCount[key]++;
                maxOverlap = max(maxOverlap, offsetCount[key]);
            }
        }

        return maxOverlap;
    }
};

## Encoding wala part samjho

int key = (rowOff + n) * (2*n) + (colOff + n);

 // ek trick hai do numbers (rowOff, colOff) ko **ek single unique integer** me convert karne ki, taaki unordered_map fast rahe.

// `rowOff` aur `colOff` dono negative bhi ho sakte hain (jaise `-n+1` se `n-1` tak), lekin hashmap ka key normally positive number hona chahiye
// (ya phir tum `pair<int,int>` ko bhi directly key bana sakte ho `map<pair<int,int>, int>` use karke, thoda slow hoga but simpler hai).




