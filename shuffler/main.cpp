#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;

struct Shuffler{
	pair<int, int> *cmpv;
	int init;
	int n;
	Shuffler(int n):
		n(n),
		cmpv(new pair<int, int>[n]),
		init(n){
	}
	~Shuffler(){
		delete [] cmpv;
	}
	void shuffle(){
		for (int i = 0; i < n; i++){
			cmpv[i].first = rand();
			cmpv[i].second = i;
		}
		sort(cmpv, cmpv+n);
		init = 0;
	}
	bool hasNext(){
		return init != n;
	}
	int getNext(){
		return cmpv[init++].second;
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
			return i != r.i;
		}
		void operator+=(int inc){
			i += inc;
		}
	};
	iterator begin(){
		return iterator(0, cmpv);
	}
	iterator end(){
		return iterator(n, cmpv);
	}
};

int main(){ _
	srand(time(NULL));
	int n;
	cin >> n;
	string *v = new string[n];
	for (int i = 0; i < n; i++)
		cin >> v[i];
	Shuffler s(n);
	s.shuffle();
	for (Shuffler::iterator i = s.begin(); i != s.end(); i+= 1)
		cout << v[*i] << " ";
	cout << endl;
	return 0;
}
