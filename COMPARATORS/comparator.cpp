/*Comparators in C++

A comparator is a function or object used to define a custom sorting or ordering rule for elements in data structures like
vector, set, map, priority_queue, etc.

🔹 Why Comparators are Used

To control the sorting order of elements (ascending, descending, or custom).

To compare objects or pairs based on specific keys.

Commonly used with:

sort()

set, map (custom ordering)
// They can be implemented in differnet ways
*/

void printVec(vector<pair<int, int>> &v)
{
    for (auto i : v)
    {
        cout << i.first << "," << i.second << ":  ";
    }
}

// 1.Function Pointers:A normal function is used as a comparator and passed to sorting functions.

bool myComparator1(int a, int b)
{
    // return a<b;//ASC
    return a > b; // DESC
}

bool myComparator2(pair<int,int>a,pair<int,int>b){
    return a.second<b.second;//based on second key->ASC
}

int main()
{
    // Eg1:
     vector<int> v1 = {2, 5, 4, 19, 8};
     sort(v1.begin(), v1.end(), myComparator1);  // Sort using custom comparator
    //   for (auto i : v)
    //  {   cout << i << " ";  }

    // Eg2:2D pair
    vector<pair<int, int>> v2 = {{2, 5}, {1, 3}, {8, 5}, {4, 2}};
    // sort(v2.begin(), v2.end()); //->by default based on first value in pair
    // printVec(v2);

    sort(v2.begin(),v2.end(),myComparator2);//// Sort based on 2nd element (ASC)
    printVec(v2);
}
/* ---------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------*/

## 2.Function Objects(Functors)
//A functor is a class or struct that overloads the () operator so it behaves like a function.
// It’s more powerful because it can store state (unlike plain functions).


class myComparator1
{
    public:
    bool operator()(int a, int b)
    {
        // return a < b;//ASC
        return a>b;//DESC  
    }
};

int main()
{
    vector<int> v1 = {2, 5, 4, 19, 8};

    // Pass an instance of the functor to sort
    sort(v1.begin(), v1.end(), myComparator1());
    for(auto i:v1){
        cout<<i<<" ";
    }
}


/* ---------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------------*/

// 2.Lambda Expressions
// A lambda expression is an anonymous (inline) function.
// Best for quick, one-line comparators — no need to define a separate function.

 auto mylambda=[](int a,int b){
    return a<b;
 };

int main()
{
    vector<int> v1 = {2, 5, 4, 19, 8};

    sort(v1.begin(), v1.end(), mylambda);
    for(auto i:v1){
        cout<<i<<" ";
    }
}

// Notes about `lambda`

// [] → capture clause (captures variables from surrounding scope if needed).

// auto must be used for lambdas because the type is compiler-generated.
