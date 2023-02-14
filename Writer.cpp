#include <iostream>
#include "thread.h"
#include "SharedObject.h"
#include <thread>
#include <stack>
#include <unistd.h>
#include <time.h>

using namespace std;

struct MyShared{
    int thId;
    int repId;
    int tDelay;
    int tElap;
    
};

class WriterThread : public Thread{
	public:
		int threadNum;
		bool flag = false;
		int delay;
		int reportId = 0;
		//MyShared share;
		
		
		WriterThread(int d, int num):Thread(8*1000){
			threadNum = num; 
			delay = d;


		}

		virtual long ThreadMain(void) override{
		
			//declare shared memory var so this thread can access it
			Shared<MyShared> sharedMemory ("sharedMemory");
			while(true)
			{
				this->reportId++;
				time_t first = time(0);
				sleep(delay);
				time_t last = time(0);
				sharedMemory->thId = threadNum;
				sharedMemory->repId = reportId;
				sharedMemory->tDelay = delay;
				sharedMemory->tElap = (last-first);
				
				if(flag == true)
				{
				    break;
				}
			}
		return 1;	
		}
};

int main(void)
{
	
	Shared<MyShared> shared("sharedMemory", true);
	std::cout << "I am a Writer" << std::endl;
	std::string nThread = "";
	int delay = 0;
	WriterThread* th;
	stack<WriterThread*> tStack;
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
	    th = new WriterThread(tCount, delay);
	    tStack.push(th);
	    
	    
	    
	}
	while(!tStack.isEmpty)
	{
	    thTop = tStack.top();
	    thTop->flag = true;
	    delete thTop;
	    tStack.pop();
	}

}


