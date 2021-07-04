package dfs;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Stack;
public class DFS {
private Stack&lt;Integer&gt; stack;
public DFS()
{
stack = new Stack&lt;Integer&gt;();
}
public void dfs(int adjacency_matrix[][], int source)
{
int number_of_nodes = adjacency_matrix[source].length - 1;
int visited[] = new int[number_of_nodes + 1];
int element = source;
int i = source;
System.out.print(element + &quot;\t&quot;);
visited[source] = 1;
stack.push(source);
while (!stack.isEmpty())
{
element = stack.peek();
i = element;
while (i &lt;= number_of_nodes)
{
if (adjacency_matrix[element][i] == 1 &amp;&amp; visited[i] == 0)

{
stack.push(i);
visited[i] = 1;
element = i;
i = 1;
System.out.print(element + &quot;\t&quot;);
continue;
}
i++;
}
stack.pop();
}
}
public static void main(String...arg)
{
int number_of_nodes, source;
Scanner scanner = null;
try
{
System.out.println(&quot;Enter the number of nodes in the graph&quot;);
scanner = new Scanner(System.in);
number_of_nodes = scanner.nextInt();
int adjacency_matrix[][] = new int[number_of_nodes + 1][number_of_nodes + 1];
System.out.println(&quot;Enter the adjacency matrix&quot;);
for (int i = 1; i &lt;= number_of_nodes; i++)
for (int j = 1; j &lt;= number_of_nodes; j++)
adjacency_matrix[i][j] = scanner.nextInt();
System.out.println(&quot;Enter the source for the graph&quot;);
source = scanner.nextInt();
System.out.println(&quot;The DFS Traversal for the graph is given by &quot;);
DFS dfs = new DFS();
dfs.dfs(adjacency_matrix, source);
}catch(InputMismatchException inputMismatch)
{
System.out.println(&quot;Wrong Input format&quot;);
}
scanner.close();
}
}