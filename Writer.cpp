#include <iostream>
#include "thread.h"
#include "SharedObject.h"
#include <thread>
#include <unistd.h>

struct MyShared{
    int threadId;
    int reportId;
    int time;

public:
MyShared(int tId, int rId, int tm)
{
    threadId = tId;
    reportId = rId;
    time = tm;
}    
    
};

class WriterThread : public Thread{
	public:
		int 	threadNum;
		bool	flag = false;
		int delay;
		int reportId = 0;
		//MyShared share;
		
		
		WriterThread(int d, int num):Thread(8*1000){
			this->threadNum = num; //or whatever you want/need here
			delay = d;


		}

		virtual long ThreadMain(void) override{
		
			//declare shared memory var so this thread can access it
			Shared<MyShared> sharedMemory ("sharedMemory");
			while(true)
			{
				this->reportId++;
				sleep(delay);
				sharedMemory->threadId = threadNum;
				if(flag){//Exit loop to end the thread
					break;
				}
			}
		}
};

int main(void)
{
	////////////////////////////////////////////////////////////////////////
	// This is a possible starting point for using threads and shared memory. 
	// You do not have to start with this
	////////////////////////////////////////////////////////////////////////
	/*...
	Shared<MyShared> shared("sharedMemory", true); //This is the owner of sharedMamory
	...
	while(true){
		...
		//create thread using user input
		thread1 = new WriterThread(xyz); //add arguments as needed
		...
	}
	//example for one thread thread1
	thread1->flag= true;
	delete thread1;
	*/
	
	Shared<MyShared> shared("sharedMemory", true);
	std::cout << "I am a Writer" << std::endl;
	std::string nThread = "";
	int delay = 0;
	WriterThread* thread1;
	int tCount = 0;
	while(true)
	{
	    tCount++;
	    std::cout << "\nWould you like to create a new thread (y/n)?\n";
	    std::cin >> nThread;
	    if(nThread == "n")
	    {
	        break;
	    }
	    std::cout << "\nWhat is the Time delay for this Thread in s?\n";
	    std::cin >> delay;
	    thread1 = new WriterThread(tCount, delay);
	    
	    
	    
	}
	

}


////////////////////////////////////////////////////////////////////////
// This is a possible starting point for using threads and shared memory. 
// You do not have to start with this
////////////////////////////////////////////////////////////////////////


