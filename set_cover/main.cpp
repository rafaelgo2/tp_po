#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

//MyShuffler
struct Shuffler{
	pair<int, int> *cmpv;
	int n;
	void shuffle(){
		for (int i = 0; i < n; i++){
			cmpv[i].first = rand();
			cmpv[i].second = i;
		}
		sort(cmpv, cmpv+n);
	}
	Shuffler(int n_, int seed){
		srand(seed);
		n = n_;
		cmpv = new pair<int, int>[n];
		shuffle();
	}
	~Shuffler(){
		delete [] cmpv;
	}
	struct iterator{
		int i;
		pair<int, int> *cmpv;
		iterator(int i, pair<int, int> *cmpv):
			i(i), cmpv(cmpv){
			}
		int operator*(){
			return cmpv[i].second;
		}
		bool operator!=(iterator r){
			return cmpv != r.cmpv || i != r.i;
		}
		void operator++(int){
			i += 1;
		}
	};
	iterator begin(){
		return iterator(0, cmpv);
	}
	iterator end(){
		return iterator(n, cmpv);
	}
};

//------

//CONFIG
ifstream in("in.txt");
//ifstream &in = cin;
ostream &out = cout;

typedef vector<int> vi;

struct Element{
	vi subset;
	bool selected;
	int weight;
	Element():
		selected(false),
		weight(0)
		{
	}
	void insert(int i){
		subset.push_back(i);
	}
	int& operator[](int i){
		return subset[i];
	}
	int size(){
		return subset.size();
	}
};

struct Subset{
	vi element;
	bool selected;
	int capacity;
	Subset():
		selected(false),
		capacity(0){
	}
	void insert(int i){
		element.push_back(i);
	}
	int& operator[](int i){
		return element[i];
	}
	int size(){
		return element.size();
	}
};

int main() {
	int n, m;
	in >> n >> m;

	vector<Element> element(n);
	vector<Subset> subset(m);
	for (int i = 0; i < m; i++)
		in >> subset[i].capacity;
	
	int aux;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++){
			in >> aux;
			if (aux){
				element[i].insert(j);
				subset[j].insert(i);
			}
		}

	Shuffler s(n, time(NULL));
	int ans = 0;
	for (Shuffler::iterator it = s.begin(); it != s.end(); it++){
		if (element[*it].selected)
			continue;
		unsigned smaller_subset = element[*it][0];
		for (unsigned i = 1; i < element[*it].size(); i++)
			if (subset[element[*it][i]].capacity < subset[smaller_subset].capacity)
				smaller_subset = element[*it][i];
		subset[smaller_subset].selected = true;
		element[*it].weight += subset[smaller_subset].capacity;
		ans += subset[smaller_subset].capacity;
		for (unsigned i = 0; i < subset[smaller_subset].size(); i++)
			element[subset[smaller_subset][i]].selected = true;
		for (unsigned i = 0; i < element[*it].size(); i++)
			subset[element[*it][i]].capacity -= subset[smaller_subset].capacity;
			
		for (unsigned i = 0; i < m; i++)
			out << (int)subset[i].selected << " ";
		out << endl;
		for (unsigned i = 0; i < n; i++)
			out << element[i].weight << " ";
		out << endl;
		out << endl;
	}
	out << ans << endl;
	return 0;
}
