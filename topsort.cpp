#include <iostream>
#include "topsort.h"
using namespace::std;
void topsort::add_node(const string& nn, const vector<string>& deps)
{
	for (auto& i: deps)
		nodes[i].second = 0;
	auto& ds = nodes[nn];
	ds.second = 0;
	for (auto& i: deps)
	{
		auto srch = nodes.find(i);
		//cout << "" << srch->first << "\\";
		ds.first.push_back(&(srch->first));
	}
}
void topsort::print()
{
	for (auto& i: nodes)
	{
		cout << i.first << "(" << i.second.second << ") :";
		for (auto& j: i.second.first)
		{
			cout << *j << ", ";
		}
		cout << endl;
	}
}
bool topsort::visit(vector<string>& rez, const string* nn)
{
	auto& node = nodes[*nn];
	if (node.second == 1) return false;//loop!
	if (node.second == 0) //not visited
	{
		node.second = 1;
		bool noloop = true;
		for (auto& i: node.first)
		{
			noloop = noloop && visit(rez, i);
		}
		node.second = 2;
		rez.push_back(*nn);
		return noloop;
	}
	//if (node.second == 2) return true;
	return true;
}
vector<string> topsort::sort()
{
	vector<string> rez;
	bool noloop = true;
	for (auto& i: nodes)
	{
		noloop = noloop && visit(rez, &(i.first));
	}
	if (noloop)
	{
		return rez;
	}
	else
	{
		cout << "loop detected" << endl;
		return vector<string>();
	}
}
istream& operator>> (istream& is, topsort& ts)
{
	while(is.good())
	{
		string nn;
		vector<string> deps;
		//forsatm is 
		//<узел_A> = <узел_A1>, <узел_A2>, ... <узел_AN>
		char c;
		while (true)
		{
			if (!is.get(c) || c == '=')
			{
				if (!nn.empty())
				{
					nn.pop_back();//delete last space;
					break;
				}
			}
			nn += c;
		}
		is.get(c);// " "
		string tmp;
		while (true)
		{
			//if (!is.get(c)) break;
			if (!is.get(c) || c == '\n')
			{
				deps.push_back(tmp);
				break;
			}
			if (c == ',')
			{
				is.get(c);//read space
				deps.push_back(tmp);
				tmp = "";
				continue;
			}
			tmp += c;
		}
		if (!nn.empty())
			ts.add_node(nn, deps);
	}
	return is;
}
