package bfs;
import java.util.InputMismatchException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
public class BFS {
private Queue&lt;Integer&gt; queue;
public BFS()
{
queue = new LinkedList&lt;Integer&gt;();
}
public void bfs(int adjacency_matrix[][], int source)
{
int number_of_nodes = adjacency_matrix[source].length - 1;
int[] visited = new int[number_of_nodes + 1];
int i, element;
visited[source] = 1;
queue.add(source);
while (!queue.isEmpty())
{

element = queue.remove();
i = element;
System.out.print(i + &quot;\t&quot;);
while (i &lt;= number_of_nodes)
{
if (adjacency_matrix[element][i] == 1 &amp;&amp; visited[i] == 0)
{
queue.add(i);
visited[i] = 1;
}
i++;
}
}
}
public static void main(String... arg)
{
int number_no_nodes, source;
Scanner scanner = null;
try
{
System.out.println(&quot;Enter the number of nodes in the graph&quot;);
scanner = new Scanner(System.in);
number_no_nodes = scanner.nextInt();
int adjacency_matrix[][] = new int[number_no_nodes + 1][number_no_nodes + 1];
System.out.println(&quot;Enter the adjacency matrix&quot;);
for (int i = 1; i &lt;= number_no_nodes; i++)
for (int j = 1; j &lt;= number_no_nodes; j++)
adjacency_matrix[i][j] = scanner.nextInt();
System.out.println(&quot;Enter the source for the graph&quot;);
source = scanner.nextInt();
System.out.println(&quot;The BFS traversal of the graph is &quot;);
BFS bfs = new BFS();
bfs.bfs(adjacency_matrix, source);
} catch (InputMismatchException inputMismatch)
{
System.out.println(&quot;Wrong Input Format&quot;);
}
scanner.close();

}
}