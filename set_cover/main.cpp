#include <iostream>
#include <vector>

using namespace std;

int main() {
    istream &in = cin;
    ostream &out = cout;
    int e_sz, s_sz;
    in >> e_sz //Elementos
       >> s_sz;//Conjuntos
    vector<int> w(s_sz);
    for (int i = 0; i < e_sz; i++)
        in >> w[i];
    int aux;
    vector< vector<bool> > m(e_sz, vector<bool>(s_sz));
    for (int i = 0; i < e_sz; i++)
        for (int j = 0; j < s_sz; j++) {
            cin >> aux;
            m[i][j] = aux == 1;
        }
    vector<bool> ans(s_sz, false);
    return 0;
}