#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "PCB.h"
#include <queue>
using std::queue;

// tree element type is PCB for now
typedef PCB elem_t;   // elem_t is hidden from the client

// definition of what a Vertex is - also hidden from the client
// Note: a vertex is a node of the tree
struct Vertex
{
	Vertex* Up;  // points to the parent node 
	Vertex* Left;
	elem_t  Elem;	//this is a PCB Elem
	Vertex* Right;
	queue<elem_t> count;	//handles duplicates
};

class BST
{
public:
	int total;	//keeps track of total entries
	BST();  // intializes Root
	~BST();  // destructor calls dtraverse to destroy the dynamic tree

	// PURPOSE: these will show the vertices in IN order 
	// TO CALL: No parameter  but provide a pointer to 
	// the root vertex in calling INorderTraversal
	void Display();
	void INorderTraversal(Vertex*); // recursive

	// PURPOSE: these will search in PRE order 
	// TO CALL: provide the element to search for; provide a pointer to 
	// the root vertex in calling PREorderSearch
	bool Search(elem_t);
	bool PREorderSearch(Vertex*, elem_t); // recursive

	 // PURPOSE: This adds a new vertex into the BST 
	 // TO CALL: provide the element to be added to the tree
	void InsertVertex(elem_t);

	// PURPOSE: This deletes a vertex with the given element 
	//     - calls remove and  findMax (see below)
	// TO CALL: provide the element to be removed from the tree
	void DeleteVertex(elem_t);

	//elem_t findFirst();
	// the following can be inherited but not available to the client 

	elem_t findNext();  // finds the MAX element in the
protected:
	Vertex* Root; //  Root which is a pointer to the root vertex

	// utility functions follow - these are not for the clients to use
	// These were created to implement the public methods

	void dtraverse(Vertex*);
	// traverse and delete all vertices in post order

	void remove(Vertex*, Vertex*);
	// removes the vertex knowing its parent

	elem_t findMax(Vertex*);  // finds the MAX element in the
							  // left sub-tree of the vertex and also deletes it
};
#endif