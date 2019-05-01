#include<iostream>
#include "a_star.h"
#include<math.h> 
#include "fib_heap.h"
#include <cstdlib>
#include <time.h>
#include"node.h"
int main() {

/*
	int i = 0;
	int width = 183;
	int height = 277;
	Graph g = Graph();
	Node* start[100];
	Node* goal[100];
	while (i < 100) {
		int w = rand() % (width);
		int h = rand() % (height);
		if (g.get(h, w)->status == '.') {
			start[i] = g.get(h, w);
			i++;
		}
	}
	i = 0;
	while (i < 100) {
		int w = rand() % (width);
		int h = rand() % (height);
		if (g.get(h, w)->status == '.') {
			goal[i] = g.get(h, w);
			i++;
		}
	}
	clock_t  clockBegin, clockEnd;
	clockBegin = clock();

	for (int i = 0; i < 100; i++) {
		findPath(start[i]->x,start[i]->y, goal[i]->x,goal[i]->y);
	}

	clockEnd = clock();
	std::cout << "running time" << clockEnd - clockBegin << std::endl;
	system("pause");*/

	Fib_heap fh = Fib_heap();
	Node* node = new Node(2,3,'O');
	node->f = 10;
	fh.push(node);
	node = new Node(5, 5, 'O'); 
	node->f = 20;
	fh.push(node);
	node = new Node(3, 3, 'O');
	node->f = 30;
	fh.push(node);
	node = new Node(7, 7, 'O');
	node->f = 40;
	fh.push(node);
	Node* a;
	a = fh.pop();
	std::cout << a->id << std::endl;
	a = fh.pop();
	std::cout << a->id << std::endl;
	a = fh.pop();
	std::cout << a->id << std::endl;
	a = fh.pop();
	std::cout << a->id << std::endl;
	return 0;
}