#ifndef SHAREDOBJECT_H
#define SHAREDOBJECT_H

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

template<class T> class Shared
{
private:
    int memoryIdentifier;
    std::string fullName;
    T * ptr;
    bool owner;
public:
    Shared(std::string const & name, bool createAsOwner=false)
        : owner(createAsOwner)
    {
        fullName = "/" + name;
        if (createAsOwner)
        {
            shm_unlink(fullName.c_str());   // Just in case. Clean up.
            memoryIdentifier = shm_open(fullName.c_str(),O_RDWR | O_CREAT, 0666);
            ftruncate(memoryIdentifier,sizeof(T));
        }
        else
            memoryIdentifier = shm_open(fullName.c_str(),O_RDWR, 0666);
        if (memoryIdentifier < 0)
            throw std::string("Unable to access shared memory object");
        ptr =(T*) mmap(NULL,sizeof(T),PROT_READ | PROT_WRITE,MAP_SHARED,memoryIdentifier,0);
    }
    virtual ~Shared(void)
    {
        munmap(ptr,sizeof(T));
        if (owner)
            shm_unlink(fullName.c_str());
    }
    T * get(void)
    {
        return ptr;
    }
    T const * get (void) const
    {
        return ptr;
    }
    T & operator*(void)
    {
        return *get();
    }
    T const & operator*(void) const
    {
        return *get();
    }
    T * operator->(void)
    {
        return get();
    }
    T const * operator->(void) const
    {
        return get();
    }
    operator T*(void)
    {
       return get();
    }
    operator T const * (void) const
    {
        return get();
    }
};

#endif // SHAREDOBJECT_H
