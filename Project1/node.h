#pragma once
#pragma once
#include<iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>

#ifndef NODE
#define NODE

struct Node {
	int x, y, f, g, id;
	int degree; //degree
	Node* left; //Left brother
	Node* right; //Right brother
	Node* heap_parent; //parent node
	Node* child; // first child node
	Node* parent;
	bool mark; // Whether the first child was deleted
	char status;
	
	// 0 for in closeList, 1 for in openList, -1 not in both
	Node(int _x, int _y, char _status) :x(_x), y(_y), status(_status), f(0), g(0), degree(0), left(NULL), right(NULL), heap_parent(NULL), parent(NULL),mark(true){
		id = 182 * x + y;
	}
};

std::vector<std::string> readFile() {
	std::ifstream fin("ca_cave.map");
	std::string s;
	std::vector<std::string> g;
	for (int i = 0; i < 4; i++) {
		getline(fin, s);
		//str[i] = s;
	}

	/*std::istringstream buf(str[1]);
	std::istream_iterator<std::string> beg(buf), end;
	std::vector<std::string> tokens(beg, end);
	for (auto& s : tokens)
		std::cout << '"' << s << '"' << '\n';*/

	while (getline(fin, s))
	{
		g.push_back(s);
	}
	//std::cout << g.size() << "   " << g[0].length() << std::endl;

	return g;
}

class Graph {
	//int width, height;
	Node* graph[277][183];
	int width = 183;
	int height = 277;

public:
	Graph() {
		std::vector<std::string> status = readFile();
		//width = status[0].length();
		//height = status.size();

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				graph[i][j] = new Node(i, j, status[i][j]);
			}
		}
	}

	int getID(int x, int y)
	{
		return x * (width - 1) + y;
	}

	Node* getById(int id) {
		return graph[id / (width - 1)][id % (width - 1)];
	}

	Node* get(int x, int y) {
		return graph[x][y];
	}
};

#endif