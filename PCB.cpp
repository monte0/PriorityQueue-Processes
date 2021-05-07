#include "PCB.h"
#include <cstdlib>
// TODO: Add your implementation here
//default constructor
PCB::PCB()
{
	id = 0;
	priority = 0;
	state = PState::NEW;
	added = 0;
	removed = 0;
}
//constructor
PCB::PCB(int num, int pri, PState::ProcState st)
{
	id = num;
	priority = pri;
	state = st;
	added = 0;
	removed = 0;
}
//compares two PCB elements
//returns true if the ID and priority are the same
bool PCB::isEqual(PCB p)
{
	if (this->id == p.id && this->priority == p.priority)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//fills the Table with an given ID and a random Priority between 1 and 50
void PCBTable::fillTable()
{
	for (int i = 0; i < 30; i++)//assign id and random priority
	{
		int tmp = rand() % 50 + 1;	//random number between 1 and 50
		this->table[i].id = i;
		this->table[i].priority = tmp;
	}
}
//Displays the table's element's ID, Priority and State
void PCBTable::displayAll()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		std::cout << "ID: " << this->table[i].id << "\tPriority: " << this->table[i].priority;
		if (this->table[i].state == PState::READY)
		{
			std::cout << "\tREADY" << std::endl;
		}
		else if (this->table[i].state == PState::RUNNING)
		{
			std::cout << "\tRUNNING" << std::endl;
		}
		else
		{
			std::cout << "\tOTHER" << std::endl;
		}
	}
}
//Displays the Table's element's ID and times added and times removed
void PCBTable::DisplayAddedRemoved()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		std::cout << "PCB ID " << this->table[i].id << " added ";
		std::cout << this->table[i].added << " times, removed " << this->table[i].removed << " times" << std::endl;
	}
}
//organizes the PCBTable in ascending order based on the elements' ID
void PCBTable::fixOrder()
{
	PCB one;//temporary PCB, used for swapping
	int z;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE - 1; j++)
		{
			if (this->table[j].id > this->table[j + 1].id)
			{
				one = this->table[j];				//c = a
				this->table[j] = this->table[j + 1];//a = b
				this->table[j + 1] = one;			//b = c
			}
		}
	}
}
//swap old PCB with new PCB in table
//makes sure the PCBTable is divided in two parts NonReady and Ready halfs
//with the value middle being in the middle
void PCBTable::swapPCB(PCB a, int& middle)
{
	PCB small;//used to swap
	middle++;
	int next = middle;
	for (int i = next; i < MAX_SIZE; i++)
	{
		if (this->table[i].isEqual(a) == true)
		{

			this->table[i] = a;//update PCBTABLE
			small = this->table[next];//c = a
			this->table[next] = this->table[i];//a = b
			this->table[i] = small;//b = c
			break;
		}
	}
}
