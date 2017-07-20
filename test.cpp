#include <gtest/gtest.h>
#include <sstream>
#include "topsort.h"
#include <iostream>
using namespace std;
topsort construct_from_graph(const vector< pair< string, vector<string> > >& input)
{
	stringstream ss;
	topsort ts;
	//write graph to stringstream
	for (auto& i: input)
	{
		ss << i.first << " = ";
		string tmp;
		for (auto& j: i.second)
		{
			tmp += j + ", ";
		}
		tmp.pop_back();
		tmp.pop_back();
		ss << tmp << endl;
	}
	/*char c;
	while (ss.get(c))
	{
		cout << c;
	}*/
	ss >> ts;
	return ts;
}
bool verify(const vector< pair< string, vector<string> > >& input, topsort& ts)
{//                           node name     deps
	//get the sorted nodes
	auto l = ts.sort();
	for (unsigned int i = 0; i < l.size(); i++)//for each node is sorted list
	{
		// copy dependences list 
		vector<string> deps;
		for (auto& j: input)
		{
			if (j.first == l[i])
				deps = j.second;
		}
		for (auto& j: deps)//for each dependence
		{
			//check whether its met or not
			bool found = false;
			//searching in upper part of sorted list
			for (unsigned int k = 0; k < i; k++)
			{
				if (j == l[k])
				{
					found = true;
					break;
				}
			}
			//not met => bad list
			if (!found)
			{
				return false;
			}
		}
	}
	//ok
	return true;//btw true is returned for empty list
}
TEST(topsort_test, test_00)// a1 -> a2 -> a3 -> a4 -> a5
{
	topsort ts;
	string nna1 = "a1";
	vector<string> deps_a1 {"a2"};
	string nna2 = "a2";
	vector<string> deps_a2 {"a3"};
	string nna3 = "a3";
	vector<string> deps_a3 {"a4"};
	string nna4 = "a4";
	vector<string> deps_a4 {"a5"};
	ts.add_node(nna1, deps_a1);
	ts.add_node(nna2, deps_a2);
	ts.add_node(nna3, deps_a3);
	ts.add_node(nna4, deps_a4);
	//ts.print();
	auto l = ts.sort();
	/*for (auto& i: l)
	{
		cout << i << endl;
	}*/
	EXPECT_TRUE(l[0] == "a5");
	EXPECT_TRUE(l[1] == "a4");
	EXPECT_TRUE(l[2] == "a3");
	EXPECT_TRUE(l[3] == "a2");
	EXPECT_TRUE(l[4] == "a1");
}
TEST(topsort_test, test_01)//using overloaded >> operator
{
	topsort ts;
	stringstream ss;
	ss << "a = a1, a2, a3\n";
	ss << "A = a, b, c";
	ss >> ts;
	auto l = ts.sort();
	/*for (auto& i: l)
	{
		cout << "|" << i << "|" << endl;
	}*/
	EXPECT_TRUE(l[0] == "a1");
	EXPECT_TRUE(l[1] == "a2");
	EXPECT_TRUE(l[2] == "a3");
	EXPECT_TRUE(l[3] == "a");
	EXPECT_TRUE(l[4] == "b");
	EXPECT_TRUE(l[5] == "c");
	EXPECT_TRUE(l[6] == "A");
}
TEST(topsort_test, test_02)//same, nut advanced example
{
	topsort ts;
	stringstream ss;
	ss << "Hydra Pond = Lizard Den, Serpent Fly Hive, Basilisk Pit, Wyvern Nest\n";
	ss << "Wyvern Nest = Lizard Den\n";
	ss << "Gorgon Lair = Lizard Den, Serpent Fly Hive\n";
	ss << "Basilisk Pit = Serpent Fly Hive\n";
	ss << "Serpent Fly Hive = Gnoll Hut\n";
	ss << "Lizard Den = Gnoll Hut\n";
	ss >> ts;
	auto l = ts.sort();
	/*for (auto& i: l)
	{
		cout << i << endl;
	}*/
	EXPECT_TRUE(l[0] == "Gnoll Hut");
	EXPECT_TRUE(l[1] == "Serpent Fly Hive");
	EXPECT_TRUE(l[2] == "Basilisk Pit");
	EXPECT_TRUE(l[3] == "Lizard Den");
	EXPECT_TRUE(l[4] == "Gorgon Lair");
	EXPECT_TRUE(l[5] == "Wyvern Nest");
	EXPECT_TRUE(l[6] == "Hydra Pond");
}
TEST(topsort_test, test_03)//using the verify function
{
	vector< pair< string, vector<string> > > graph;
	graph.push_back(pair<string, vector<string>>("Hydra Pond", vector<string> {"Lizard Den", "Serpent Fly Hive", "Basilisk Pit", "Wyvern Nest"}));
	graph.push_back(pair<string, vector<string>>("Wyvern Nest", vector<string> {"Lizard Den"}));
	graph.push_back(pair<string, vector<string>>("Gorgon Lair", vector<string> {"Lizard Den", "Serpent Fly Hive"}));
	graph.push_back(pair<string, vector<string>>("Basilisk Pit", vector<string> {"Serpent Fly Hive"}));
	graph.push_back(pair<string, vector<string>>("Serpent Fly Hive", vector<string> {"Gnoll Hut"}));
	graph.push_back(pair<string, vector<string>>("Lizard Den", vector<string> {"Gnoll Hut"}));
	topsort ts = construct_from_graph(graph);
	EXPECT_TRUE(verify(graph,ts));
}
TEST(topsort_test, test_04)//more verify function
{
	vector< pair<string, vector<string>>> graph;
	graph.push_back(pair<string, vector<string>> ("A", vector<string>{"B"}));
	graph.push_back(pair<string, vector<string>> ("B", vector<string>{"C"}));
	graph.push_back(pair<string, vector<string>> ("C", vector<string>{"D"}));
	graph.push_back(pair<string, vector<string>> ("D", vector<string>{"E"}));
	topsort ts = construct_from_graph(graph);
	EXPECT_TRUE(verify(graph,ts));
}
TEST(topsort_test, test_05)
{
	vector<pair<string, vector<string>>> graph;
	graph.push_back(pair<string, vector<string>> ("поехать в магазин", vector<string>{"сесть в машину", "тронуться", "ехать", "остановиться у магазина"}));
	graph.push_back(pair<string, vector<string>> ("сесть в машину", vector<string>{"открыть водительскую дверь", "сесть на сиденье", "закрыть дверь", "пристегнуть ремень"}));
	graph.push_back(pair<string, vector<string>> ("тронуться", vector<string>{"сесть на сиденье", "завести мотор", "нажать на тормоз", "отпустить ручник", "включить поворотник", "отпустить тормоз", "нажать на газ"}));
	graph.push_back(pair<string, vector<string>> ("остановиться у магазина", vector<string>{"ехать", "увидеть магазин", "нажать на тормоз", "остановить автомобиль", "затянуть ручник"}));
	topsort ts = construct_from_graph(graph);
	topsort ts2 = ts;
	EXPECT_TRUE(verify(graph, ts));
	auto l = ts2.sort();
	for (auto& i: l)
	{
		cout << i << endl;
	}
}
int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
