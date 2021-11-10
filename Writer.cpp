//Created By: Andrew Brown 20/10/28
#include <iostream>
#include "SharedObject.h"
#include "thread.h"
#include <string> 

struct MyShared{
	int sdelay;
	int sthreadID;
	int sreportID;
	bool sRunning;
};

class WriterThread : public Thread{
public:
		int 	delay;
		int 	threadID;
		int 	reportID = 1;
		bool	flag;
		
		WriterThread(int in, int threadid):Thread(8*1000){
			this->delay = in;
			this->threadID = threadid;
		}

		virtual long ThreadMain(void) override{
			
			Shared<MyShared> sharedMemory ("sharedMemory");
			while(true)// Here the memory values of the thread must be updated
			{
				sharedMemory->sthreadID = threadID; //sets thread ID
				sharedMemory->sreportID = reportID; //sets number of reports
				reportID ++; //increments the number of reports 
				sharedMemory->sdelay = delay;//sets delay
				sleep(delay); //sleeps the thread for the amount of delay set by the user
				if(flag){
					break;
				}
			}
		}
};



int main(void)
{
	std::string  userInput;
	std::string userDelay;
	int numThreads=1; //Used for creating writerThread objects where numThreads will be used to give threads ID #s

	std::cout << "I am a Writer" << std::endl;
	
	WriterThread * thread; //declare thread 

	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory
	//Set the running value to true so the reader can poll the shared memory
	shared ->sRunning = true;

	
	while(true){
		//Prompt user and get input. 
		std::cout << "Would you like to create a writer thread? Enter Y or N: "<< std::endl;
		getline(std::cin,userInput);
		if(userInput == "Y"){
			std::cout << "Please enter a delay time for this thread: "<< std::endl;
			getline(std::cin,userDelay);
			int delay = atoi(userDelay.c_str()); //Convert the string to and int

			//Create a new writerThread object 
			thread = new WriterThread(delay,numThreads);//instantiate thread 
			numThreads++; //Increase the number of threads 
		}
		else if (userInput == "N"){
			//If the user enters N then the while statement will break and threads will be handled 
			if(numThreads -1 !=0){ //Avoids core dump in the case N is entered first and no threads were created
				shared->sRunning = false;
				break;
			}
			else{
				break;
			}
		}
		else
		{
			//To handle inproper inputs. 
			std::cout << "Invalid input entered." << std::endl;
		}
	}//end while 
	if(numThreads-1 != 0){ //Avoids core dump in the case N is entered first and no threads were created
		thread ->flag = true;
		delete thread; 
	}
	

	return 0;	
}//end main 