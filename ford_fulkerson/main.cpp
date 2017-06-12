#include <iostream>
#include <vector>

using namespace std;

struct Edge{
    int c;
    int from;
    int to;
    bool original;
    Edge(){}
    Edge(int c, int from, int to):
            c(c), from(from), to(to), original(true){}
    Edge operator~(){
        Edge e(0, to, from);
        e.original = false;
        return e;
    }
    void operator-=(int c_){
        if (original) //TODO TESTAR
            c -= c_;
        else
            c -= c_;
    }
};

typedef vector<Edge&> Vertex;

int dfs(int v, int d, int acc, vector<Vertex> &graph, vector<int> &ant, vector<bool> &path){
    if (v == d) {
        path[d] = true;
        return acc;
    }
    int aug;
    for (int i = 0; i < graph[v].size(); i++){
        Edge &e = graph[v][i];
        if (ant[e.to] == -1) {
            ant[e.to] = v;
            aug = dfs(e.to, d, min(acc, e.c), graph, ant, path);
            if (aug > 0){
                path[v] = true;
                e -= aug;
                return aug;
            }
        }
    }
    return 0;
}
ostream operator<<(ostream &out, vector<bool> &v){
    for (int i = 0; i < v.size(); i++)
        out << (int)v[i] << " ";
    return out;
}

ostream operator<<(ostream &out, vector<int> &v){
    for (int i = 0; i < v.size(); i++)
        out << v[i] << " ";
    return out;
}

int main() {
    istream &in = cin;
    ostream &out = cout;
    int n, m;
    in >> n
       >> m;
    vector<Edge> e(m);
    vector<Edge> e_back(m);
    for (int i = 0; i < m; i++)
        in >> e[i].c;
    int aux;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++){
            in >> aux;
            switch (aux){
                case 1:{
                    e[j].from = i;
                }break;
                case -1:{
                    e[j].to = i;
                }break;
            }
        }
    vector<Vertex> graph(n);
    for (int i = 0; i < m; i++){
        graph[e[i].from].push_back(e[i]);
        e_back[i] = ~e[i];
        graph[e[i].to].push_back(e_back[i]);
    }
    vector<int> ant(n);
    vector<bool> path(n);
    int ans = 0;
    while (true){
        fill(ant.begin()+1, ant.end(), -1);
        fill(path.begin(), path.end(), false);
        int aug = dfs(0, n-1, INTMAX_MAX, graph, ant, path);
        if (!aug)
            break;
        ans += aug;
        out << path << endl;
    }
    return 0;
}