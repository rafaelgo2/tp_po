#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#define INF ( ((unsigned) -1) >> 1 )

//CONFIG
ifstream in("in.txt");
//ifstream &in = cin;
ostream &out = cout;

struct Edge{
    int flow; //Quanto de flow ainda pode passar
    int capacity; //Capacidade da aresa
    int from; //Origem da aresta
    int to; //Destino da aresta
    bool original; //Tipo da aresta (original ou residual)
    Edge(){}
    Edge(int capacity):
        capacity(capacity), flow(capacity), original(true){}
    Edge(int capacity, int from, int to):
            flow(capacity), capacity(capacity), from(from), to(to), original(true){}
    Edge operator~(){ //Transforma uma aresta original em residual
        Edge e(0, to, from);
        e.capacity = capacity;
        e.original = false;
        return e;
    }
    bool isResidual(){
	return flow > 0;
    }
};

typedef vector<int> Vertex;

struct Graph {
    vector<Vertex> v;
    vector<Edge> e;
    int n, m;
    Graph(int n, int m):
            n(n), m(m){
        v.resize(n);
        e.reserve(2*m);
    }
    void add_edge(Edge edge){
        v[edge.from].push_back(e.size());
        e.push_back(edge);
        v[edge.to].push_back(e.size());
        e.push_back(~edge);
    }
    int aug_path(int curr, int dest, vector<bool> &visited, vector<bool> &path, int acc){
        if (curr == dest){
            path[dest] = true;
            return acc;
        }
        for (unsigned i = 0; i < v[curr].size(); i++){
            Edge edge = e[v[curr][i]];
            if (edge.flow > 0 && !visited[edge.to]){
                visited[edge.to] = true;
                int aug = aug_path(edge.to, dest, visited, path, min(acc, edge.flow));
                if (aug > 0){
                    int inc = edge.original ? 1 : -1;
                    if (edge.original)
                        path[v[curr][i]] = true;
                    e[v[curr][i]+inc].flow += aug;
                    e[v[curr][i]].flow -= aug;
                    return aug;
                }
            }
        }
        return 0;
    }
    void dfs_min_cut(int curr, int dest, vector<bool> &visited){
	if (curr == dest)
		return;
	for (unsigned i = 0; i < v[curr].size(); i++){
		Edge edge = e[v[curr][i]];
		if (edge.isResidual() && !visited[edge.to]){
			visited[edge.to] = true;
			dfs_min_cut(edge.to, dest, visited);
		}
	}
    }
    //Assume que max_flow(begin, end) ja foi chamado
    void min_cut(int begin, int end){
        vector<bool> visited(n);
        fill(visited.begin(), visited.end(), false);
	visited[begin] = true;
	dfs_min_cut(begin, end, visited);
	cout << "Min_cut: ";
	for (unsigned i = 0; i < m; i++){
	    Edge edge = e[2*i];
	    out << (int) (visited[edge.from] && !visited[edge.to]) << " ";
	}	
        out << endl;
    }
    void max_flow(int begin, int end){
        vector<bool> visited(n);
        vector<bool> path(m);
        int flow = 0;
        while (true){
            fill(visited.begin(), visited.end(), false);
            visited[begin] = true;
            fill(path.begin(), path.end(), false);
            int aug = aug_path(begin, end, visited, path, INF);
            if (aug == 0)
                break;
            flow += aug;
            for (unsigned i = 0; i < m; i++)
                out << e[2*i].capacity - e[2*i].flow << " ";
            out << endl;
            for (unsigned i = 0; i < m; i++)
                out << (int)path[i] << " ";
            out << endl;
            for (unsigned i = 0; i < m; i++)
                out << e[2*i].capacity << " ";
            out << endl << endl;
        }
	cout << "Max_flow: " << flow << endl;
    }
};

int main(){
    int n, m, capacity;
    in >> n
       >> m;
    vector<Edge> e(m);
    for (int i = 0; i < m; i++){
        in >> capacity;
        e[i] = Edge(capacity);
    }
    int aux;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            in >> aux;
            switch (aux){
                case 1:{
                    e[j].to = i;
                }break;
                case -1:{
                    e[j].from = i;
                }break;
            }
        }
    Graph g(n, m);
    for (unsigned i = 0; i < e.size(); i++)
        g.add_edge(e[i]);
    g.max_flow(0, n-1);
    g.min_cut(0, n-1);
    return 0;
}
