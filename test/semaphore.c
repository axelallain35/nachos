#include "userlib/syscall.h"
#include "userlib/libnachos.h"

int sharedCounter = 0;

void increment();

int main()
{
  int idSem = SemCreate("sem1", 1);
  n_printf("Semaphore created with id %d\n", idSem);
  V(idSem);
  P(idSem);

  threadCreate("t1", increment);
  threadCreate("t2", increment);

  return 0;
}

void increment(){
    for(int i = 0; i < 10000; i++){
        Yield();
        sharedCounter++;
        if(i % 100 == 0)
            n_printf("Shared counter: %d\n", sharedCounter);
    }
    n_printf("Shared counter: %d\n", sharedCounter);
}
