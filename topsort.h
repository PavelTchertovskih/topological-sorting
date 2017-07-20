#ifndef TOPSORT_H
#define TOPSORT_H
#include <list>
#include <map>
#include <string>
#include <vector>
#include <istream>
using std::list;
using std::map;
using std::string;
using std::vector;
using std::pair;
using std::istream;
class topsort
{
	map<string, pair<list<const string*>,int>> nodes;
	// node name      deps list         color
	bool visit(vector<string>&, const string*);
public:
	void add_node(const string&, const vector<string>&);
	void print();
	vector<string> sort();
};
istream& operator>> (istream& is, topsort& ts);
#endif
