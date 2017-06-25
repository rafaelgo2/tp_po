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
    void addEdge(Edge edge){
        v[edge.from].push_back(e.size());
        e.push_back(edge);
        v[edge.to].push_back(e.size());
        e.push_back(~edge);
    }
    int dfs(int curr, int dest, vector<int> &ant, vector<bool> &path, int acc){
        if (curr == dest){
            path[dest] = true;
            return acc;
        }
        for (unsigned i = 0; i < v[curr].size(); i++){
            Edge edge = e[v[curr][i]];
            if (edge.flow > 0 && ant[edge.to] == -1){
                ant[edge.to] = curr;
                int aug = dfs(edge.to, dest, ant, path, min(acc, edge.flow));
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
    int max_flow(int begin, int end){
        vector<int> ant(n);
        vector<bool> path(m);
        int flow = 0;
        while (true){
            fill(ant.begin(), ant.end(), -1);
            ant[begin] = begin;
            fill(path.begin(), path.end(), false);
            int aug = dfs(begin, end, ant, path, INF);
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
        return flow;
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
        g.addEdge(e[i]);
    int flow = g.max_flow(0, n-1);
    cout << "Max flow = " << flow << endl;
    return 0;
}
