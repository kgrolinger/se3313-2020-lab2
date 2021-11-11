#include <iostream>
#include "SharedObject.h"

using namespace std;

struct MyShared{
	int sharedThreadID;
	int sharedReportID;
	int sharedDelay;
	bool sharedRunning;
};

int main(void)
{
	cout << "I am a reader" << endl;
	Shared<MyShared> sharedMemory("sharedMemory");
	
	//Reader will poll the shared memory to determine if it is in use
	//then it will display the data. If it is not, it will break 
	while (true){
		if (sharedMemory->sharedRunning == true){
			cout << "ThreadID: " << sharedMemory->sharedThreadID <<" ReportID: "<<sharedMemory->sharedReportID <<" Delay: " <<sharedMemory->sharedDelay << endl;
			sleep(1); 
		}else {
			//When a user enters n the value of Running will be set to false and the loop will break causing the reader to terminate
			break;
		}
	}
	//return 0;
}