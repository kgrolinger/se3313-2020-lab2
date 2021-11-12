#include <iostream>
#include "SharedObject.h"
#include "Semaphore.h"

struct MyShared{
	int sharedThreadID;
	int sharedReportID;
	int sharedDelay;
	bool sharedRunning;
};


int main(void)
{
	std::cout << "I am a reader" << std::endl;

	Semaphore readerSem("readerSemaphore");
	Shared<MyShared> sharedMemory("sharedMemory"); //ownership set to false when omitted

	//Reader will poll the shared memory to determine if it is in use, if it is in use
	// then it will display the data, if it is not it will break 
	while (true){
		if (sharedMemory->sharedRunning == true){
			readerSem.Wait();
			std::cout << "ThreadID: " << sharedMemory->sharedThreadID <<" ReportID: "<<sharedMemory->sharedReportID <<" Delay: " <<sharedMemory->sharedDelay <<std::endl;
			sleep(1);
		}else {
			//When a user enters n the value of Running will be set to false and the loop will break causing the reader to terminate
			break;
		}
	}
	//return 0;
}