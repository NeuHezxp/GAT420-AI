#include "Node.h"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;
using char_node_t = node<char>;

vector<char_node_t*> getDFS(char_node_t* root, char target);
vector<char_node_t*> getBFS(char_node_t* root, char target);

int main()
{
	//      A
	//    B   C
	//  D   E   F
	// create nodes with char data
	char_node_t* nodeA = new char_node_t{ 'A' };
	char_node_t* nodeB = new char_node_t{ 'B' };
	char_node_t* nodeC = new char_node_t{ 'C' };
	char_node_t* nodeD = new char_node_t{ 'D' };
	char_node_t* nodeE = new char_node_t{ 'E' };
	char_node_t* nodeF = new char_node_t{ 'F' };
	// create tree from nodes (children)
	// create the other connections as shown in the tree at the top (A->C, B->D, ...)
	nodeA->children.push_back(nodeB); // A->B
	nodeA->children.push_back(nodeC); // A->C

	nodeB->children.push_back(nodeD); // B->D
	nodeB->children.push_back(nodeE); // B->E

	nodeC->children.push_back(nodeF); // C->F

	// get search path to 'F' from node 'A'
	auto path = getBFS(nodeA, 'F');
	//auto path = getBFS(nodeA, 'F'); // For Breadth First Search

	// Display path result
	cout << "path: ";
	for (auto it = path.begin(); it != path.end(); ++it) {
		cout << "->" << (*it)->data;
	}
	cout << endl;
}

vector<char_node_t*> getDFS(char_node_t* root, char target)
{
	// check for valid root node
	if (root == nullptr) return vector<char_node_t*>();

	// create nodes stack and push root onto stack
	stack<char_node_t*> node_stack; /*<create stack of char_node_t*>*/
	root->visited = true;//<set root visited to true>
	node_stack.push(root);	//<push root onto node_stack>

	while (!node_stack.empty()) //<node_stack is not empty>
	{
		// get current node from the top of stack
		char_node_t* current = node_stack.top(); //<get node on top of stack>
		// check if the current node data is target value
		if (current->data == target)
		{
			cout << "found: " << current->data << endl;
			break;
		}
		else
		{
			cout << "visited: " << current->data << endl;
		}

		// if target not found then go down tree (child of current node)
		// push unvisited child node onto stack
		bool popNode = true; // pop node if there are no unvisited children
		for (char_node_t* child : current->children) //<get child in children>
		{
			// if child node is unvisited th en mark visited and push onto stack
			if (!child->visited)
			{
				child->visited = true;
				node_stack.push(child);
				popNode = false;
				break;
			}
		}
		// if no unvisited children of the current node then pop the stack to go back up the tree
		if (popNode)
		{
			node_stack.pop();//<pop node off of node_stack>
		}
	}

	// convert stack nodes to vector of nodes (path)
	// stack nodes are in reverse order with the target at the top
	// add stack nodes to front of path vector
	vector<char_node_t*> path;
	while (!node_stack.empty())
	{
		// add top node and then pop node off of stack
		path.insert(path.begin(), node_stack.top());//path.insert(<begin() of path>, <top of node_stack>);
		node_stack.pop();
	}

	return path;
}

vector<char_node_t*> getBFS(char_node_t* root, char target)
{
	// check for valid root node
	if (root == nullptr) return vector<char_node_t*>();

	// create nodes queue and queue root onto stack
	queue<char_node_t*> node_queue;//<create queue of char_node_t*> node_queue;
	root->visited = true;
	node_queue.push(root);

	while (!node_queue.empty())
	{
		// get current node from the front of the queue
		char_node_t* current = node_queue.front();
		// check if the current node data is target value
		if (current->data == target)
		{
			cout << "found: " << current->data << endl;
			break;
		}
		else
		{
			cout << "visit: " << current->data << endl;
		}

		// if target not found then push all the children of the current node into the queue
		for (char_node_t* child : current->children)
		{
			if (!child->visited)
			{
				child->visited = true;
				child->parent = current;
				node_queue.push(child);
			}
		}

		// pop the front of the queue
		if (!node_queue.empty())
		{
			node_queue.pop();
		}
	}

	// convert nodes to vector of nodes (path)
// nodes are in reverse order with the parent used to move through the nodes
	  // add nodes to front of path vector
	vector<char_node_t*> path;
	char_node_t* node = (node_queue.empty() ? nullptr : node_queue.front());  //<get front of node_queue, if node_queue is empty then set node to nullptr>
	while (node)
	{
		// add node and then set node to node parent
		path.insert(path.begin(), node); //path.insert(<begin() of path>, node);
		node = node->parent;  //node = <node parent>;		 
	}

	return path;
}