#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
#include <queue>

using namespace std;
const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void parallelBfs(int node)
{
    	queue<int> s;
	s.push(node);

	while(!s.empty()){
	
		int curr_node = s.front();
		s.pop();
		visited[curr_node] = true;

		cout<<curr_node<<" ";

		#pragma omp parallel for
		for(int i = 0; i < graph[curr_node].size(); i++){

			#pragma omp critical
			{
				int adj_node = graph[curr_node][i];
		
				if(!visited[adj_node]){
					s.push(adj_node);
					visited[adj_node] = true;
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
    parallelBfs(start_node);
    cout<<endl;
    double endTime = omp_get_wtime();


    std::cout<<"Time Required is : "<< endTime - startTime<<endl;
    return 0;
}