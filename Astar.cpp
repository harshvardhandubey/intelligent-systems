#include&lt;bits/stdc++.h&gt;
using namespace std;

#define ROW 9
#define COL 10
// Creating a shortcut for int, int pair type
typedef pair&lt;int, int&gt; Pair;
// Creating a shortcut for pair&lt;int, pair&lt;int, int&gt;&gt; type
typedef pair&lt;double, pair&lt;int, int&gt;&gt; pPair;
// A structure to hold the necessary parameters
struct cell
{
// Row and Column index of its parent
// Note that 0 &lt;= i &lt;= ROW-1 &amp; 0 &lt;= j &lt;= COL-1
int parent_i, parent_j;
// f = g + h
double f, g, h;
};
// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(int row, int col)
{
// Returns true if row number and column number
// is in range
return (row &gt;= 0) &amp;&amp; (row &lt; ROW) &amp;&amp;
(col &gt;= 0) &amp;&amp; (col &lt; COL);

}
// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(int grid[][COL], int row, int col)
{
// Returns true if the cell is not blocked else false
if (grid[row][col] == 1)

return (true);
else
return (false);

}
// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(int row, int col, Pair dest)
{
if (row == dest.first &amp;&amp; col == dest.second)
return (true);
else
return (false);

}
// A Utility Function to calculate the &#39;h&#39; heuristics.
double calculateHValue(int row, int col, Pair dest)
{
// Return using the distance formula
return ((double)sqrt ((row-dest.first)*(row-dest.first)

+ (col-dest.second)*(col-dest.second)));

}
// A Utility Function to trace the path from the source
// to destination
void tracePath(cell cellDetails[][COL], Pair dest)
{
printf (&quot;\nThe Path is &quot;);
int row = dest.first;
int col = dest.second;

stack&lt;Pair&gt; Path;
while (!(cellDetails[row][col].parent_i == row

&amp;&amp; cellDetails[row][col].parent_j == col ))

{
Path.push (make_pair (row, col));
int temp_row = cellDetails[row][col].parent_i;
int temp_col = cellDetails[row][col].parent_j;
row = temp_row;
col = temp_col;
}
Path.push (make_pair (row, col));
while (!Path.empty())
{
pair&lt;int,int&gt; p = Path.top();
Path.pop();
printf(&quot;-&gt; (%d,%d) &quot;,p.first,p.second);
}
return;
}
// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
// If the source is out of range
if (isValid (src.first, src.second) == false)
{
printf (&quot;Source is invalid\n&quot;);
return;
}
// If the destination is out of range
if (isValid (dest.first, dest.second) == false)

{
printf (&quot;Destination is invalid\n&quot;);
return;
}
// Either the source or the destination is blocked
if (isUnBlocked(grid, src.first, src.second) == false ||

isUnBlocked(grid, dest.first, dest.second) == false)

{
printf (&quot;Source or the destination is blocked\n&quot;);
return;
}
// If the destination cell is the same as source cell
if (isDestination(src.first, src.second, dest) == true)
{
printf (&quot;We are already at the destination\n&quot;);
return;
}
// Create a closed list and initialise it to false which means
// that no cell has been included yet
// This closed list is implemented as a boolean 2D array
bool closedList[ROW][COL];
memset(closedList, false, sizeof (closedList));
// Declare a 2D array of structure to hold the details
//of that cell
cell cellDetails[ROW][COL];
int i, j;
for (i=0; i&lt;ROW; i++)
{
for (j=0; j&lt;COL; j++)
{

cellDetails[i][j].f = FLT_MAX;
cellDetails[i][j].g = FLT_MAX;
cellDetails[i][j].h = FLT_MAX;
cellDetails[i][j].parent_i = -1;
cellDetails[i][j].parent_j = -1;
}
}
// Initialising the parameters of the starting node
i = src.first, j = src.second;
cellDetails[i][j].f = 0.0;
cellDetails[i][j].g = 0.0;
cellDetails[i][j].h = 0.0;
cellDetails[i][j].parent_i = i;
cellDetails[i][j].parent_j = j;
/*
Create an open list having information as-
&lt;f, &lt;i, j&gt;&gt;
where f = g + h,
and i, j are the row and column index of that cell
Note that 0 &lt;= i &lt;= ROW-1 &amp; 0 &lt;= j &lt;= COL-1
This open list is implenented as a set of pair of pair.*/
set&lt;pPair&gt; openList;
// Put the starting cell on the open list and set its
// &#39;f&#39; as 0
openList.insert(make_pair (0.0, make_pair (i, j)));
// We set this boolean value as false as initially
// the destination is not reached.
bool foundDest = false;
while (!openList.empty())
{

pPair p = *openList.begin();
// Remove this vertex from the open list
openList.erase(openList.begin());
// Add this vertex to the open list
i = p.second.first;
j = p.second.second;
closedList[i][j] = true;
/*
Generating all the 8 successor of this cell
N.W N N.E
\ | /
\ | /
W----Cell----E
/ | \
/ | \
S.W S S.E
Cell--&gt;Popped Cell (i, j)
N --&gt; North (i-1, j)
S --&gt; South (i+1, j)
E --&gt; East (i, j+1)
W --&gt; West (i, j-1)
N.E--&gt; North-East (i-1, j+1)
N.W--&gt; North-West (i-1, j-1)
S.E--&gt; South-East (i+1, j+1)
S.W--&gt; South-West (i+1, j-1)*/
// To store the &#39;g&#39;, &#39;h&#39; and &#39;f&#39; of the 8 successors
double gNew, hNew, fNew;
//----------- 1st Successor (North) ------------
// Only process this cell if this is a valid one
if (isValid(i-1, j) == true)

{
// If the destination cell is the same as the
// current successor
if (isDestination(i-1, j, dest) == true)
{
// Set the Parent of the destination cell
cellDetails[i-1][j].parent_i = i;
cellDetails[i-1][j].parent_j = j;
printf (&quot;The destination cell is found\n&quot;);
tracePath (cellDetails, dest);
foundDest = true;
return;
}
// If the successor is already on the closed
// list or if it is blocked, then ignore it.
// Else do the following
else if (closedList[i-1][j] == false &amp;&amp;

isUnBlocked(grid, i-1, j) == true)

{
gNew = cellDetails[i][j].g + 1.0;
hNew = calculateHValue (i-1, j, dest);
fNew = gNew + hNew;
// If it isn’t on the open list, add it to
// the open list. Make the current square
// the parent of this square. Record the
// f, g, and h costs of the square cell
// OR
// If it is on the open list already, check
// to see if this path to that square is better,
// using &#39;f&#39; cost as the measure.

if (cellDetails[i-1][j].f == FLT_MAX ||
cellDetails[i-1][j].f &gt; fNew)

{
openList.insert( make_pair(fNew,
make_pair(i-1, j)));
// Update the details of this cell
cellDetails[i-1][j].f = fNew;
cellDetails[i-1][j].g = gNew;
cellDetails[i-1][j].h = hNew;
cellDetails[i-1][j].parent_i = i;
cellDetails[i-1][j].parent_j = j;
}
}
}
//----------- 2nd Successor (South) ------------
// Only process this cell if this is a valid one
if (isValid(i+1, j) == true)
{
// If the destination cell is the same as the
// current successor
if (isDestination(i+1, j, dest) == true)
{
// Set the Parent of the destination cell
cellDetails[i+1][j].parent_i = i;
cellDetails[i+1][j].parent_j = j;
printf(&quot;The destination cell is found\n&quot;);
tracePath(cellDetails, dest);
foundDest = true;
return;
}

// If the successor is already on the closed
// list or if it is blocked, then ignore it.
// Else do the following
else if (closedList[i+1][j] == false &amp;&amp;

isUnBlocked(grid, i+1, j) == true)

{
gNew = cellDetails[i][j].g + 1.0;
hNew = calculateHValue(i+1, j, dest);
fNew = gNew + hNew;

// If it isn’t on the open list, add it to
// the open list. Make the current square
// the parent of this square. Record the
// f, g, and h costs of the square cell
// OR
// If it is on the open list already, check
// to see if this path to that square is better,
// using &#39;f&#39; cost as the measure.
if (cellDetails[i+1][j].f == FLT_MAX ||
cellDetails[i+1][j].f &gt; fNew)

{
openList.insert( make_pair (fNew, make_pair (i+1, j)));
// Update the details of this cell
cellDetails[i+1][j].f = fNew;
cellDetails[i+1][j].g = gNew;
cellDetails[i+1][j].h = hNew;
cellDetails[i+1][j].parent_i = i;
cellDetails[i+1][j].parent_j = j;
}
}

}
//----------- 3rd Successor (East) ------------
// Only process this cell if this is a valid one
if (isValid (i, j+1) == true)
{
// If the destination cell is the same as the
// current successor
if (isDestination(i, j+1, dest) == true)
{
// Set the Parent of the destination cell
cellDetails[i][j+1].parent_i = i;
cellDetails[i][j+1].parent_j = j;
printf(&quot;The destination cell is found\n&quot;);
tracePath(cellDetails, dest);
foundDest = true;
return;
}
// If the successor is already on the closed
// list or if it is blocked, then ignore it.
// Else do the following
else if (closedList[i][j+1] == false &amp;&amp;

isUnBlocked (grid, i, j+1) == true)

{
gNew = cellDetails[i][j].g + 1.0;
hNew = calculateHValue (i, j+1, dest);
fNew = gNew + hNew;
// If it isn’t on the open list, add it to
// the open list. Make the current square
// the parent of this square. Record the
// f, g, and h costs of the square cell

// OR
// If it is on the open list already, check
// to see if this path to that square is better,
// using &#39;f&#39; cost as the measure.
if (cellDetails[i][j+1].f == FLT_MAX ||
cellDetails[i][j+1].f &gt; fNew)

{
openList.insert( make_pair(fNew,

make_pair (i, j+1)));

// Update the details of this cell
cellDetails[i][j+1].f = fNew;
cellDetails[i][j+1].g = gNew;
cellDetails[i][j+1].h = hNew;
cellDetails[i][j+1].parent_i = i;
cellDetails[i][j+1].parent_j = j;
}
}
}
//----------- 4th Successor (West) ------------
// Only process this cell if this is a valid one
if (isValid(i, j-1) == true)
{
// If the destination cell is the same as the
// current successor
if (isDestination(i, j-1, dest) == true)
{
// Set the Parent of the destination cell
cellDetails[i][j-1].parent_i = i;
cellDetails[i][j-1].parent_j = j;
printf(&quot;The destination cell is found\n&quot;);

tracePath(cellDetails, dest);
foundDest = true;
return;
}
// If the successor is already on the closed
// list or if it is blocked, then ignore it.
// Else do the following
else if (closedList[i][j-1] == false &amp;&amp;

isUnBlocked(grid, i, j-1) == true)

{
gNew = cellDetails[i][j].g + 1.0;
hNew = calculateHValue(i, j-1, dest);
fNew = gNew + hNew;
// If it isn’t on the open list, add it to
// the open list. Make the current square
// the parent of this square. Record the
// f, g, and h costs of the square cell
// OR
// If it is on the open list already, check
// to see if this path to that square is better,
// using &#39;f&#39; cost as the measure.
if (cellDetails[i][j-1].f == FLT_MAX ||
cellDetails[i][j-1].f &gt; fNew)

{
openList.insert( make_pair (fNew,

make_pair (i, j-1)));

// Update the details of this cell
cellDetails[i][j-1].f = fNew;
cellDetails[i][j-1].g = gNew;

cellDetails[i][j-1].h = hNew;
cellDetails[i][j-1].parent_i = i;
cellDetails[i][j-1].parent_j = j;
}
}
}
//----------- 5th Successor (North-East) ------------
// Only process this cell if this is a valid one
if (isValid(i-1, j+1) == true)
{
// If the destination cell is the same as the
// current successor
if (isDestination(i-1, j+1, dest) == true)
{
// Set the Parent of the destination cell
cellDetails[i-1][j+1].parent_i = i;
cellDetails[i-1][j+1].parent_j = j;
printf (&quot;The destination cell is found\n&quot;);
tracePath (cellDetails, dest);
foundDest = true;
return;
}
// If the successor is already on the closed
// list or if it is blocked, then ignore it.
// Else do the following
else if (closedList[i-1][j+1] == false &amp;&amp;

isUnBlocked(grid, i-1, j+1) == true)

{
gNew = cellDetails[i][j].g + 1.414;
hNew = calculateHValue(i-1, j+1, dest);

fNew = gNew + hNew;
// If it isn’t on the open list, add it to
// the open list. Make the current square
// the parent of this square. Record the
// f, g, and h costs of the square cell
// OR
// If it is on the open list already, check
// to see if this path to that square is better,
// using &#39;f&#39; cost as the measure.
if (cellDetails[i-1][j+1].f == FLT_MAX ||
cellDetails[i-1][j+1].f &gt; fNew)

{
openList.insert( make_pair (fNew,

make_pair(i-1, j+1)));

// Update the details of this cell
cellDetails[i-1][j+1].f = fNew;
cellDetails[i-1][j+1].g = gNew;
cellDetails[i-1][j+1].h = hNew;
cellDetails[i-1][j+1].parent_i = i;
cellDetails[i-1][j+1].parent_j = j;
}
}
}

//----------- 6th Successor (North-West) ------------

// Only process this cell if this is a valid one
if (isValid (i-1, j-1) == true)
{
// If the destination cell is the same as the

// current successor
if (isDestination (i-1, j-1, dest) == true)
{
// Set the Parent of the destination cell
cellDetails[i-1][j-1].parent_i = i;
cellDetails[i-1][j-1].parent_j = j;
printf (&quot;The destination cell is found\n&quot;);
tracePath (cellDetails, dest);
foundDest = true;
return;
}
// If the successor is already on the closed
// list or if it is blocked, then ignore it.
// Else do the following
else if (closedList[i-1][j-1] == false &amp;&amp;

isUnBlocked(grid, i-1, j-1) == true)

{
gNew = cellDetails[i][j].g + 1.414;
hNew = calculateHValue(i-1, j-1, dest);
fNew = gNew + hNew;

// If it isn’t on the open list, add it to
// the open list. Make the current square
// the parent of this square. Record the
// f, g, and h costs of the square cell
// OR
// If it is on the open list already, check
// to see if this path to that square is better,
// using &#39;f&#39; cost as the measure.
if (cellDetails[i-1][j-1].f == FLT_MAX ||

cellDetails[i-1][j-1].f &gt; fNew)

{
openList.insert( make_pair (fNew, make_pair (i-1, j-1)));
// Update the details of this cell
cellDetails[i-1][j-1].f = fNew;
cellDetails[i-1][j-1].g = gNew;
cellDetails[i-1][j-1].h = hNew;
cellDetails[i-1][j-1].parent_i = i;
cellDetails[i-1][j-1].parent_j = j;
}
}
}

//----------- 7th Successor (South-East) ------------
// Only process this cell if this is a valid one
if (isValid(i+1, j+1) == true)
{
// If the destination cell is the same as the
// current successor
if (isDestination(i+1, j+1, dest) == true)
{
// Set the Parent of the destination cell
cellDetails[i+1][j+1].parent_i = i;
cellDetails[i+1][j+1].parent_j = j;
printf (&quot;The destination cell is found\n&quot;);
tracePath (cellDetails, dest);
foundDest = true;
return;
}
// If the successor is already on the closed

// list or if it is blocked, then ignore it.
// Else do the following
else if (closedList[i+1][j+1] == false &amp;&amp;

isUnBlocked(grid, i+1, j+1) == true)

{
gNew = cellDetails[i][j].g + 1.414;
hNew = calculateHValue(i+1, j+1, dest);
fNew = gNew + hNew;
// If it isn’t on the open list, add it to
// the open list. Make the current square
// the parent of this square. Record the
// f, g, and h costs of the square cell
// OR
// If it is on the open list already, check
// to see if this path to that square is better,
// using &#39;f&#39; cost as the measure.
if (cellDetails[i+1][j+1].f == FLT_MAX ||
cellDetails[i+1][j+1].f &gt; fNew)

{
openList.insert(make_pair(fNew,
make_pair (i+1, j+1)));
// Update the details of this cell
cellDetails[i+1][j+1].f = fNew;
cellDetails[i+1][j+1].g = gNew;
cellDetails[i+1][j+1].h = hNew;
cellDetails[i+1][j+1].parent_i = i;
cellDetails[i+1][j+1].parent_j = j;
}
}
}

//----------- 8th Successor (South-West) ------------
// Only process this cell if this is a valid one
if (isValid (i+1, j-1) == true)
{
// If the destination cell is the same as the
// current successor
if (isDestination(i+1, j-1, dest) == true)
{
// Set the Parent of the destination cell
cellDetails[i+1][j-1].parent_i = i;
cellDetails[i+1][j-1].parent_j = j;
printf(&quot;The destination cell is found\n&quot;);
tracePath(cellDetails, dest);
foundDest = true;
return;
}
// If the successor is already on the closed
// list or if it is blocked, then ignore it.
// Else do the following
else if (closedList[i+1][j-1] == false &amp;&amp;

isUnBlocked(grid, i+1, j-1) == true)

{
gNew = cellDetails[i][j].g + 1.414;
hNew = calculateHValue(i+1, j-1, dest);
fNew = gNew + hNew;
// If it isn’t on the open list, add it to
// the open list. Make the current square
// the parent of this square. Record the
// f, g, and h costs of the square cell
// OR

// If it is on the open list already, check
// to see if this path to that square is better,
// using &#39;f&#39; cost as the measure.
if (cellDetails[i+1][j-1].f == FLT_MAX ||
cellDetails[i+1][j-1].f &gt; fNew)

{
openList.insert(make_pair(fNew,
make_pair(i+1, j-1)));
// Update the details of this cell
cellDetails[i+1][j-1].f = fNew;
cellDetails[i+1][j-1].g = gNew;
cellDetails[i+1][j-1].h = hNew;
cellDetails[i+1][j-1].parent_i = i;
cellDetails[i+1][j-1].parent_j = j;
}
}
}
}
// When the destination cell is not found and the open
// list is empty, then we conclude that we failed to
// reach the destiantion cell. This may happen when the
// there is no way to destination cell (due to blockages)
if (foundDest == false)
printf(&quot;Failed to find the Destination Cell\n&quot;);
return;
}
// Driver program to test above function
int main()
{
/* Description of the Grid-

1--&gt; The cell is not blocked
0--&gt; The cell is blocked */
int grid[ROW][COL] =
{
{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
};

// Source is the left-most bottom-most corner
Pair src = make_pair(8, 0);
// Destination is the left-most top-most corner
Pair dest = make_pair(0, 0);
aStarSearch(grid, src, dest);
return(0);
}