#include <iostream>
#include "SharedObject.h"
#include "thread.h"
#include <string> 
#include "Semaphore.h"

using namespace std;

struct MyShared{
	int sharedThreadID;
	int sharedReportID;
	int sharedDelay;
	bool sharedRunning;
};


class WriterThread : public Thread{
public:
		int delay;
		int threadID;
		int reportID = 1;
		bool flag;
		
		WriterThread(int delay, int threadID):Thread(8*1000){
			this->delay = delay;
			this->threadID = threadID;
		}

		virtual long ThreadMain(void) override{

			Shared<MyShared> sharedMemory ("sharedMemory");
			//create semaphores for the writer and reader
			Semaphore writerSem("writerSemaphore");
			Semaphore readerSem("readerSemaphore");
			
			// below the memory values of the thread must be updated
			while(true){
				writerSem.Wait(); //lock resource so no others can write to the shared memory at the same time
				//update the thread information while it is locked
				sharedMemory->sharedThreadID = threadID; //sets thread ID
				sharedMemory->sharedReportID = reportID; //sets number of reports
				sharedMemory->sharedDelay = delay;//sets delay
				reportID ++; //increments the number of reports 
				
				writerSem.Signal(); //once the information is set, the resource can be unlocked for other read write operations to occur as needed
				readerSem.Signal(); //signal the reader semaphore so that reads can occur from the shared resource 
				
				sleep(delay); //sleep the thread for the amount of delay set by the user
				if(flag){
					break;
				}
			}
			// return 1;
		}
};

int main(void)
{
	 //Creates sem with initial value of one and owner status as true
	Semaphore writerSem("writerSemaphore", 1, true);
	//Creates sem with initial value of zero and owner status as false	
	Semaphore readerSem("readerSemaphore", 0, false); 
	
	string userInput;
	string threadDelay;
	int numThreads=1; //Used for creating writerThread objects where numThreads will be used to give threads ID #s

	cout << "I am a Writer" << endl;
	
	WriterThread * thread; //declare thread 
	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory
	
	while(true){
		cout << "Would you like to create a writer thread? Enter yes or no: "<< endl;
		cin >> userInput;
		cin.ignore();
		if(userInput == "yes"){
			cout << "Please enter a delay time for this thread: "<< endl;
			cin >> threadDelay;
			cin.ignore();
			int delay = atoi(threadDelay.c_str()); //Convert the string to and int
			//Create a new writerThread object 
			thread = new WriterThread(delay,numThreads);//instantiate thread 
			shared ->sharedRunning = true;//Set the running value to true so the reader can poll the shared memory
			numThreads++; //Increase the number of threads 
		}
		else if (userInput == "no"){
			//if no is the first input -> sharedRunning should be false
			if(numThreads -1 !=0){ 
				shared->sharedRunning = false;
				break;
			}
			//break out of the while loop
			else{
				break;
			}
		}
		else
		{
			//inproper inputs handler
			cout << "Invalid input entered." << endl;
		}
	}
	//to avoid core dump in the case no is entered first and no threads were created
	if(numThreads-1 != 0){ 
		thread ->flag = true;
		delete thread; 
	}

return 0;	
}//end main 
