#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

class Semaphore
{
private:
    sem_t * pSem;
    bool owner;
    std::string fullName;
public:
    Semaphore(std::string const & name,int initialState = 0, bool createAsOwner = false)
        : owner(createAsOwner),fullName("/"+name)
    {
        if (createAsOwner)
        {
            sem_unlink(fullName.c_str()); // Just in case
            pSem=sem_open(fullName.c_str(), O_CREAT, 0666,initialState);
        }
        else
            pSem=sem_open(fullName.c_str(),0);
        if (pSem == SEM_FAILED)
            throw std::string("Couldn't create semaphore");
    }
    virtual ~Semaphore(void)
    {
        sem_close(pSem);
        if (owner)
            sem_unlink(fullName.c_str());
    }

    void Wait()
    {
        sem_wait(pSem);
    }
    void Signal()
    {
        sem_post(pSem);
    }
};

#endif // SEMAPHORE_H
