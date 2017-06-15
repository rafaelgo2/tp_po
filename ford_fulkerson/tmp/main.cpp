#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Edge{
    int flow; //Quanto de flow ainda pode passar
    int capacity; //Capacidade da aresa
    int from; //Origem da aresta
    int to; //Destino da aresta
    bool original; //Tipo da aresta (verdadeira ou falsa)
    Edge(){}
    Edge(int capacity):
        capacity(capacity), flow(capacity), original(true){}
    Edge(int capacity, int from, int to):
            flow(capacity), capacity(capacity), from(from), to(to), original(true){}
    Edge operator~(){
        Edge e(0, to, from);
        e.capacity = capacity;
        e.original = false;
        return e;
    }
};

typedef vector<int> Vertex;

int dfs(int v, int d, int acc, vector<Vertex> &graph, vector<Edge> &e, vector<int> &ant, vector<bool> &path){
    if (v == d) {
        path[d] = true;
        return acc;
    }
    int aug;
    for (int i = 0; i < graph[v].size(); i++){
        Edge edge = e[graph[v][i]];
        if (edge.flow > 0 && ant[edge.to] == -1) {
            ant[edge.to] = v;
            aug = dfs(edge.to, d, min(acc, edge.flow), graph, e, ant, path);
            if (aug > 0){
                if (e[graph[v][i]].original){
                    path[graph[v][i]] = true;
                    e[graph[v][i]].flow -= aug;
                    e[graph[v][i] + e.size()/2].flow += aug;
                }
                else{
                    e[graph[v][i] - e.size()/2].flow += aug;
                    e[graph[v][i]].flow -= aug;
                }
                return aug;
            }
        }
    }
    return 0;
}

int main() {
    ifstream in("in.txt");
    ostream &out = cout;
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
    vector<Vertex> graph(n);
    for (int i = 0; i < m; i++){
        graph[e[i].from].push_back(i);
        e.push_back(~e[i]);
        graph[e[i].to].push_back(i+m);
    }
    vector<int> ant(n);
    vector<bool> path(m);
    int ans = 0;
    while (true){
        fill(ant.begin()+1, ant.end(), -1);
        fill(path.begin(), path.end(), false);
        int aug = dfs(0, n-1, INT32_MAX, graph, e, ant, path);
        if (!aug)
            break;
        ans += aug;
        out << "flow: " << endl;
        for (int i = 0; i < m; i++)
            out << e[i].capacity - e[i].flow << " ";
        out << endl;
        out << "path: " << endl;
        for (int i = 0; i < m; i++)
            out << (int)path[i] << " ";
        out << endl;
        out << "copy: " << endl;
        for (int i = 0; i < m; i++)
            out << e[i].capacity << " ";
        out << endl;
        out << ans << endl;
        out << endl;
    }
    out << ans << endl;
    return 0;
}
