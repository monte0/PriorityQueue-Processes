#include <iostream>
#include <cstdlib>
//#include <sys/time.h>
#include <ctime>
#include <time.h>
#include <chrono>
#include "ReadyQueue.h"


using namespace std::chrono;
int main(int argc, char* argv[])
{
	//Print basic information about the program
	std::cout << "CS 433 Programming assignment 1" << std::endl;
	std::cout << "Author: Miguel Cea" << std::endl;
	std::cout << "Date: 02/13/2020" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description : Program to implement a priority ready queue of processes" << std::endl;
	std::cout << "=================================" << std::endl;

	// TODO: Add your code for Test 1
	std::cout << "Performing Test 1" << std::endl;

	PCBTable* P1 = new PCBTable;
	ReadyQueue q1;				//will hold ready state processes
	PCB tmp;					//used for swapping
	PCB temp;							//temporary PCB, used for swapping
	srand(time(NULL));					//inserts random processes

	//fill table with ID and priority being the same
	for (int i = 0; i < 30; i++)
	{
		P1->table[i].id = i;
		P1->table[i].priority = i;
	}

	//1. add processes 15, 6, 23, 29, and 8 to q1. Display the content of q1.
	q1.add(&P1->table[15]);
	q1.add(&P1->table[6]);
	q1.add(&P1->table[23]);
	q1.add(&P1->table[29]);
	q1.add(&P1->table[8]);
	std::cout << "After adding 5 processes: " << std::endl;
	q1.display();

	//2. and 3. remove the process with the highest priority from q1 and display q1.
	for (int i = 0; i < 2; i++)//remove two times
	{
		tmp = q1.removeHighest();
		std::cout << "After removing a process: " << std::endl;
		q1.display();
	}

	//4. add processes 3, 17, 22, 12, and 19 to q1. Display the content of q1.
	q1.add(&P1->table[3]);
	q1.add(&P1->table[17]);
	q1.add(&P1->table[22]);
	q1.add(&P1->table[12]);
	q1.add(&P1->table[19]);
	std::cout << "After adding 5 processes: " << std::endl;
	q1.display();

	int tot = q1.size();
	//5. One by one remove the the process with the highest priorityfrom the queue q1
	//and display the queue after eaech removal.
	for (int i = 0; i < tot; i++)
	{
		q1.removeHighest();
		std::cout << "After removing a process: " << std::endl;
		q1.display();
	}

	//TODO: Add your code for Test 2
	std::cout << "Performing Test 2" << std::endl;
	PCBTable* P2 = new PCBTable;
	P2->fillTable();				//fill table with random priority
	std::cout << "ORIGINAL TABLE" << std::endl;
	P2->displayAll();
	//this variable, last, will be really inportant in choosing a random PCB
	//that isnt already in the ReadyQue. I set it equal to the last index
	//of the table and use it with modulus. Everytime I add an element to the ReadyQue
	//last will get smaller since the number of NonReady PCBs will get smaller.
	//this makes sure I dont choose an element at the end of the PCBTable 
	int last = MAX_SIZE - 1;


	//here I here I choose a random PCB element to add to the READYQUE
	//and I swap it with the last PCB element of the Table
	//then I decrement last to make sure I dont chose the elements already
	//in the ReadyQue
	for (int i = 0; i < 15; i++)
	{//select 15 random processes and add them to q1
		int tmp = rand() % last;	//random process between 0 and 29
		q1.add(&P2->table[tmp]);
		temp = P2->table[tmp];				//c = a
		P2->table[tmp] = P2->table[last];	//a = b
		P2->table[last] = temp;				//b = c
		last--;								//only use indexes with PCB elements in NonReady State
	}

	std::cout << "After adding 15 random processes:" << std::endl;
	P2->displayAll();
	int remove = 0;		//keep track of times removing from ReadyQue 
	int add = 0;		//keep track of times adding to ReadyQue

	auto start = std::chrono::steady_clock::now();//start clock
	for (int i = 0; i < 1000000; i++)//1,000,000 loops
	{
		int tmp = rand() % 2;//a random number either 0 or 1
		if (tmp % 2 == 0)//if its even then remove a process, EVEN
		{
			remove++;
			if (q1.size() == 0)
			{
				//q1 is empty so do nothing
			}
			else//there is still some in the queue
			{
				temp = q1.removeHighest();
				P2->swapPCB(temp, last);
			}
		}
		else//else its odd and we add a process, ODD
		{
			add++;
			if (q1.size() == 30)
			{
				//all processes in the PCBTable are in q1, so do nothing
			}
			else//add a process that isnt already in queue from the table to queue
			{
				if (last == 0)//there is only one NonReady state element in the PCBTable
				{
					q1.add(&P2->table[0]);
					P2->table[last] = P2->table[0];
					last--;
				}
				else
				{
					int tmp = rand() % last;	//random process between 0 and 29
					q1.add(&P2->table[tmp]);	//add to readyque 
					temp = P2->table[tmp];		//c = a
					P2->table[tmp] = P2->table[last];	//a = b
					P2->table[last] = temp;				//b = c
					last--;
				}
			}
		}
	}

	auto end = std::chrono::steady_clock::now();//stop clock
	double timePassed = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());//get time passed in nanoseconds

	std::cout << "FINAL CONTENTS OF PCBTABLE AFTER 1000000 LOOPS" << std::endl;
	P2->displayAll();

	std::cout << "FINAL CONTENTS OF READYQUE AFTER 1000000 LOOPS" << std::endl;
	q1.display();

	P2->fixOrder();
	P2->DisplayAddedRemoved();
	std::cout << "ADDED= " << add << "\tREMOVED= " << remove << std::endl;
	std::cout << "The 1,000,000 loops took a total of " << timePassed / 1e9 << " seconds" << std::endl;
}
