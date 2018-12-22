// C++ program to search if a target node is reachable from
// a source with given max depth.
#include<bits/stdc++.h>
using namespace std;

// Graph class represents a directed graph using adjacency
// list representation.
class Graph
{
	int V; // No. of vertices

	// Pointer to an array containing
	// adjacency lists
	list<int> *adj;

	// A function used by IDDFS
	bool DLS(int v, int target, int limit);

	void printPath();


	stack<int> pathStack ;


public:
	Graph(int V); // Constructor

	void addEdge(int v, int w);

	// IDDFS traversal of the vertices reachable from v
	bool IDDFS(int v, int target, int max_depth);

};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

// A function to perform a Depth-Limited search
// from given source 'src'
bool Graph::DLS(int src, int target, int limit)
{
    pathStack.push(src);

    if (src == target){
        printPath() ;
		return true;
	}

    // If reached the maximum depth, stop recursing.
    if (limit <= 0)
        return false;

    // Recur for all the vertices adjacent to source vertex
    for (auto i = adj[src].begin(); i != adj[src].end(); ++i){
       if (DLS(*i, target, limit-1) == true){
          return true;
       }
       pathStack.pop() ;
    }

     return false;
}

// IDDFS to search if target is reachable from v.
// It uses recursive DFSUtil().
bool Graph::IDDFS(int src, int target, int max_depth)
{
	// Repeatedly depth-limit search till the
	// maximum depth.
	for (int i = 0; i <= max_depth; i++)
       {
           while ( ! pathStack.empty() )
                 pathStack.pop();
           if (DLS(src, target, i) == true)
            return true;
       }

	return false;
}

void Graph::printPath(){
    vector<int> pathVector ;
    while(!pathStack.empty()){
        pathVector.push_back(pathStack.top()) ;
        pathStack.pop() ;
    }
    cout<<"Path from node is: " ;
    for(int i=pathVector.size()-1; i>=0 ; i--){
        cout<<pathVector[i]<<" " ;
    }
    cout<<endl ;
}





int main()
{
    // Let us create a Directed graph with 7 nodes
    Graph g(10);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(5, 6);
    g.addEdge(5, 7);
    g.addEdge(5, 8);
    g.addEdge(8, 9);

    int target , maxDepth, src;
    cout<<"Enter the source : "<<endl;
    cin>>src;
    cout<<"Enter the goal  : "<<endl;
    cin>>target;
    cout<<"Enter the maximum depth : "<<endl;
    cin>>maxDepth;
    if (g.IDDFS(src, target, maxDepth) == true)
        cout << "Target is reachable from source "
                "within max depth";
    else
        cout << "Target is NOT reachable from source "
                "within max depth";
    return 0;
}
