#include <iostream>
#include <thread.h>
#include <SharedObject.h>

struct MyShared{

private:
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
	while(true)
	{
	    std::cout << "\nWould you like to create a new thread (y/n)?\n";
	    std::cin >> nThread;
	    if(nThread == "n")
	    {
	        break;
	    }
	    std::cout << "\nWhat is the Time delay for this Thread in s?\n";
	    std::cin >> delay;
	    thread1 = new WriterThread(delay);
	    
	}
	

}


////////////////////////////////////////////////////////////////////////
// This is a possible starting point for using threads and shared memory. 
// You do not have to start with this
////////////////////////////////////////////////////////////////////////

class WriterThread : public Thread{
	public:
		int 	threadNum;
		bool	flag;
		MyShared share;
		
		WriterThread(int in):Thread(8*1000){
			this->threadNum = in; //or whatever you want/need here
		}

		virtual long ThreadMain(void) override{
			...
			//declare shared memory var so this thread can access it
			Shared<MyShared> sharedMemory ("sharedMemory");
			while(true)
			{
				//write to shared memory
				...  
				if(flag){//Exit loop to end the thread
					break;
				}
			}
		}
};
