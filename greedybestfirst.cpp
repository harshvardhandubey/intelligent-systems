// C++ program to find minimum number of denominations
#include &lt;bits/stdc++.h&gt;
using namespace std;
 
// All denominations of Indian Currency
int deno[] = {1, 2, 5, 10, 20, 50, 100, 500, 1000};
int n = sizeof(deno)/sizeof(deno[0]);
 
// Driver program
void findMin(int V)
{
    // Initialize result
    vector&lt;int&gt; ans;
 
    // Traverse through all denomination
    for (int i=n-1; i&gt;=0; i--)
    {
        // Find denominations
        while (V &gt;= deno[i])
        {

           V -= deno[i];
           ans.push_back(deno[i]);
        }
    }
 
    // Print result
    for (int i = 0; i &lt; ans.size(); i++)
           cout &lt;&lt; ans[i] &lt;&lt; &quot;  &quot;;
}
 
// Driver program
int main()
{
   int n = 93;
   cout &lt;&lt; &quot;Following is minimal number of change for &quot; &lt;&lt; n &lt;&lt; &quot; is &quot;;
   findMin(n);
   return 0;
}