#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
using namespace std;
const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];
bool parallelVisited[MAX];

void dfs(int node)
{
    stack<int> s;
    s.push(node);
    while (!s.empty())
    {
        int curr_node = s.top();
        if (!visited[curr_node])
        {
            visited[curr_node] = true;
            s.pop();
            cout<<curr_node<<" ";
            for (int i = 0; i < graph[curr_node].size(); i++)
            {
                int adj_node = graph[curr_node][i];
                if (!visited[adj_node])
                {
                    s.push(adj_node);
                }
            }
        }
    }
}

void parallelDfs(int node)
{
    stack<int> s;
    s.push(node);
    while (!s.empty())
    {
        int curr_node = s.top();
        if (!visited[curr_node])
        {
            visited[curr_node] = true;
            s.pop();
            cout<<curr_node<<" ";
	
		#pragma omp parallel for
            for (int i = 0; i < graph[curr_node].size(); i++)
            {
                int adj_node = graph[curr_node][i];
                if (!visited[adj_node])
                {
                    s.push(adj_node);
                }
            }
        }
    }
}

int main()
{
    int n, m, start_node;
    std::cout << "Enter no. of Node,no. of Edges and Starting Node of graph:\n";
    cin >> n >> m >> start_node;
    // n: node,m:edges
    std::cout << "Enter pair of node and edges:\n";
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        // u and v: Pair of edges
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    double startTime = omp_get_wtime();
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }
    dfs(start_node);
    cout<<endl;
    double endTime = omp_get_wtime();

    double startTimeParallel = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }
    parallelDfs(start_node);
    cout<<endl;
    double endTimeParallel = omp_get_wtime();

    std::cout<<"Sequential Time : "<< endTime - startTime<<endl;
    std::cout<<"Parallel Time : "<< endTimeParallel - startTimeParallel<<endl;
    return 0;
}