#include <iostream>
//#include "PCB.h"
#include "ReadyQueue.h"

// TODO: Add your implementation of ReadyQueue functions here
void ReadyQueue::add(PCB* pcbPtr)
{
	pcbPtr->added++;//increment the times added by one
	pcbPtr->state = PState::READY;//change state to ready
	PCB temp = *pcbPtr;
	ReadyQue.InsertVertex(temp);
}
PCB ReadyQueue::removeHighest()
{
	elem_t e;
	elem_t t = ReadyQue.findNext();//find PCB with max priority
	t.removed++;//increment the times removed by one
	t.state = PState::RUNNING;//state is changed from ready to running
	e = t;
	ReadyQue.DeleteVertex(e);
	return e;
}
int ReadyQueue::size()
{
	return ReadyQue.total;//return size of ready
}
void ReadyQueue::display()
{
	ReadyQue.Display();
}
