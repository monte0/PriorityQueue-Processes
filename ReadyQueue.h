#ifndef READYQUEUE_H
#define READYQUEUE_H
#include "PCB.h"
#include "BinaryTree.h"

/**
 * ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue here such that the process with the highest priority
 * can be selected next.
 */
class ReadyQueue {
public:
	// TODO: Implement the required functions. Add necessary member fields and functions
	// You may use different parameter signatures from the example below
	BST ReadyQue;

	// add a PCB representing a process into the ready queue.
	void add(PCB* pcbPtr);

	// remove and return the PCB with the highest priority from the queue
	PCB removeHighest();

	// Returns the number of elements in the queue.
	int size();

	// Prints the queue contents to standard output.
	void display();
};
#endif