#include <iostream>

/*
struct MyShared{
	...;
};*/

int main(void)
{
	std::cout << "I am a Writer" << std::endl;
	
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
}


////////////////////////////////////////////////////////////////////////
// This is a possible starting point for using threads and shared memory. 
// You do not have to start with this
////////////////////////////////////////////////////////////////////////
/*class WriterThread : public Thread{
	public:
		int 	threadNum;
		bool	flag;
		
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
*/
