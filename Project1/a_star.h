#pragma once
#pragma once
#include "fib_heap.h"
#include "node.h"


#ifndef A_STAR
#define A_STAR

int hValue(Node* start, Node* goal) {
	int h = abs(start->x - goal->x) + abs(start->y - goal->y);
	return h;
}

bool findPath(int x ,int y, int m,int n) {
	Graph g = Graph();
	Node* start = g.get(x, y);
	Node* goal = g.get(m, n);
	int closeNum = 0;//number of node already checked
	int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };//four directions
	start->f = hValue(start, goal);
	start->status = 'O';
	Fib_heap pq = Fib_heap();
	pq.push(start);
	while (!pq.empty()) {
		Node* node = pq.pop();
		if (node->id == goal->id) {
			std::cout << "The number of node checked: " << closeNum << std::endl;
			std::cout << "<" << goal->x << "," << goal->y << ">";
			while (node->parent) {
				node = node->parent;
				std::cout << "<" << node->x << "," << node->y << ">";
			}
			return true;
		}
		else {
			for (int i = 0; i < 4; i++) {
				int x = dir[i][0] + node->x;
				int y = dir[i][1] + node->y;
				Node* nextNode = g.get(x, y);
				if (nextNode->status == '.' || nextNode->status == 'O'){
					if (nextNode->status == 'O') {
						int f = node->g + 1 + hValue(nextNode, goal);
						if (f < nextNode->f) {
							nextNode->parent = node;
							nextNode->g = node->g + 1;
							nextNode->f = f;
							pq.fib_heap_decrease(nextNode,nextNode->f);
						}
					}
					else {
						nextNode->g = node->g + 1;
						nextNode->f = nextNode->g + hValue(nextNode, goal);
						nextNode->parent = node;
						nextNode->status = 'O';
						pq.push(nextNode);
					}
				}
			}
		}
		node->status = 'C';
		closeNum++;
	}
	return false;
}


//bool path(Node* start, Node* goal,Graph g) {
//	
//	if (start && goal && start->status == 0 or goal->status == 0)
//		return false;
//	else {
//		return findPath(start, goal, g);
//	}
//}

#endif // !A_STAR