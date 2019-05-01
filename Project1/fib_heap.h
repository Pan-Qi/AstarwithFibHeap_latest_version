#pragma once
#include"node.h"
#ifndef FIB_HEAP
#define FIB_HEAP

//struct FibNode {
//	int key; //node
//	int degree; //degree
//	Node* node;
//	FibNode* left; //Left brother
//	FibNode* right; //Right brother
//	FibNode* parent; //parent node
//	FibNode* child; // first child node
//	bool mark; // Whether the first child was deleted
//	FibNode(int _key, Node* _node) :key(_key), node(_node), degree(0), left(NULL), right(NULL), parent(NULL), child(NULL) {	}
//};

class Fib_heap {
	int keyNum;
	int maxDegree;
	Node* min;
	Node** cons;// double address

	void add(Node *node)
	{
		node->left = min->left;
		min->left->right = node;
		node->right = min;
		min->left = node;
	} 

	void remove(Node* node) {
		if (node) {
		node->left->right = node->right;
		node->right->left = node->left;
	}
}

	Node* remove_min()
	{
		Node* minNode = min;

		if (min == min->right)
			min = NULL;
		else
		{
			remove(min);
			min = min->right;
		}
		minNode->left = minNode->right = minNode;

		return minNode;
	}

	void cat(Node *a, Node *b)
	{
		Node *tmp;

		tmp = a->right;
		a->right = b->right;
		b->right->left = a;
		b->right = tmp;
		tmp->left = b;
	}


	Fib_heap* fib_heap_union(Fib_heap* h1, Fib_heap* h2)
	{
		Fib_heap *tmp;

		if (h1 == NULL)
			return h2;
		if (h2 == NULL)
			return h1;

		if (h2->maxDegree > h1->maxDegree)// make sure h1 have the max degree
		{
			tmp = h1;
			h1 = h2;
			h2 = tmp;
		}

		if ((h1->min) == NULL)                // no min node in h1
		{
			h1->min = h2->min;
			h1->keyNum = h2->keyNum;
			free(h2->cons);
			free(h2);
		}
		else if ((h2->min) == NULL)           // h1 have min node, h2 don't
		{
			free(h2->cons);
			free(h2);
		}                                   // both have min node
		else
		{
			// put h2 root into h1
			cat(h1->min, h2->min);
			if (h1->min->f > h2->min->f)
				h1->min = h2->min;
			h1->keyNum += h2->keyNum;
			free(h2->cons);
			free(h2);
		}

		return h1;
	}

	void fib_node_add(Node* node, Node* root)
	{
		node->left = root->left;
		root->left->right = node;
		node->right = root;
		root->left = node;
	}

	void fib_heap_link(Node* node, Node* root)
	{
		remove(node);
		if (root->child == NULL)
			root->child = node;
		else
			fib_node_add(node, root->child);

		node->heap_parent = root;
		root->degree++;
		node->mark = 0;
	}

	//create space for consolidate
	void cons_make()
	{
		int old = maxDegree;

		
		maxDegree = log2(keyNum) + 1; //result up bound integer

		// allocate space agian if not enough
		if (old >= maxDegree)
			return;

		cons = (Node **)realloc(cons,sizeof(Fib_heap *) * (maxDegree + 1));
	}

	//union same degree trees
	void fib_heap_consolidate()
	{
		int i, d, D;
		Node *x, *y, *tmp;

		cons_make();

		D = maxDegree + 1;

		for (i = 0; i < D; i++)
			cons[i] = NULL;

		// union same degree tree root node
		while (min != NULL)
		{
			x = remove_min();    
			d = x->degree;                    
			while (cons[d] != NULL)
			{
				y = cons[d];            
				if (x->f > y->f)        
				{
					tmp = x;
					x = y;
					y = tmp;

				}
				fib_heap_link(y, x);    
				cons[d] = NULL;
				d++;
			}
			cons[d] = x;
		}
		min = NULL;

		for (i = 0; i < D; i++)
		{
			if (cons[i] != NULL)
			{
				if (min == NULL)
					min = cons[i];
				else
				{
					fib_node_add(cons[i],min);
					if ((cons[i])->f < min->f)
						min = cons[i];
				}
			}
		}
	}

	void fib_heap_cut(Node* node, Node* parent)
	{
		remove(node);
		renew_degree(parent, node->degree);
		if (node == node->right)
			parent->child = NULL;
		else
			parent->child = node->right;

		node->heap_parent = NULL;
		node->left = node->right = node;
		node->mark = 0;
		fib_node_add(node, min);
	}

	void renew_degree(Node *parent, int degree)
	{
		parent->degree -= degree;
		if (parent->heap_parent != NULL)
			renew_degree(parent->heap_parent, degree);
	}

	void fib_heap_cascading_cut(Node *node)
	{
		Node *parent = node->heap_parent;
		if (parent != NULL)
			return;

		if (node->mark == 0)
			node->mark = 1;
		else
		{
			fib_heap_cut(node, parent);
			fib_heap_cascading_cut(parent);
		}
	}


public:
	Fib_heap() {
		keyNum = 0;
		maxDegree = 0;
		min = NULL;
		cons = NULL;
	}

	void push(Node* node)
	{
		if (keyNum == 0) {
			min = node;
			min->left = min->right = min;
		}
		else
		{
			add(node);
			if (node->f < min->f)
				min = node;
		}
		keyNum++;
	}

	Node* pop()
	{
		if (keyNum == 0)
			return NULL;

		Node* child;
		//FibNode* minNode = min;
		while (min->child != NULL)
		{
			child = min->child;
			remove(child);
			if (child->right == child)
				min->child = NULL;
			else
				min->child = child->right;

			add(child);
			child->heap_parent = NULL;
		}

		Node* node = min;

		remove(node);
		if (node->right == node)
			min = NULL;
		else
		{
			min = node->right;
			fib_heap_consolidate();
		}
		keyNum--;

		return node;
	}

	void fib_heap_decrease(Node* node, int f)
	{
		Node* parent;

		if (min == NULL ||node == NULL)
			return;

		node->f = f;
		parent = node->heap_parent;
		if (parent != NULL && node->f < parent->f)
		{
			fib_heap_cut(node, parent);
			fib_heap_cascading_cut(parent);
		}

		if (node->f < min->f)
			min = node;
	}

	bool empty() {
		if (keyNum == 0)
			return true;
		return false;
	}
};
#endif