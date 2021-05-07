#ifndef PCB_H
#define PCB_H
#include <iostream>

// enum class of process state
// A process (PCB) in ready queue should be in READY state
struct PState
{
	enum  ProcState { NEW, READY, RUNNING, WAITING, TERMINATED };
};

const int MAX_SIZE = 30;//total size of PCBTABLE
/*
Process control block(PCB) is a data structure representing a process in the system.
A process should have at least an ID and a state(i.e.NEW, READY, RUNNING, WAITING or TERMINATED).
It may also have other attributes, such as scheduling information (e.g. priority)
*/
class PCB {
public:
	// The unique process ID
	unsigned int id;
	// The priority of a process valued between 1-50. Larger number represents higher priority
	unsigned int priority;
	// The current state of the process.
	// A process in the ReadyQueue should be in READY state
	PState::ProcState state;
	//number of times added
	int added;
	//number of times removed
	int removed;

	// TODO: Add constructor and other necessary functions for the PCB class
	PCB();//default constructor
	PCB(int num, int pri, PState::ProcState st);//constructor

	//compares two PCB based on ID and Priority
	bool isEqual(PCB p);
};

/*
An array(list) of all PCB elements in the system.
*/
class PCBTable {
	// TODO: Add your implementation of the PCBTable
public:
	PCB table[MAX_SIZE];
	//assigns the table with a ID and a random priority
	void fillTable();
	//Displays all the element's ID, Priority, and State
	void displayAll();
	//Displays the element's ID, and times added and removed
	void DisplayAddedRemoved();
	//organizes the Table by the ID in ascending order
	void fixOrder();
	//switches an old PCB with updated values
	void swapPCB(PCB a, int& middle);
};
#endif