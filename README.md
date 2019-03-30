# Readers-Writers-Solution-using-Semaphores 


PROBLEM STATEMENT:-There is a shared resource which should be accessed by multiple processes. 
There are two types of processes in this context. They are reader and writer. 
Any number of readers can read from the shared resource simultaneously, but only one writer can write to the shared resource.
When a writer is writing data to the resource, no other process can access the resource. 
A writer cannot write to the resource if there are non zero number of readers accessing the resource at that time.



Before going for the solution let me expain what i have done 
I used threads as the main agents to do the the required functions(producing and consuming)
I selected threads so that my program will run for many threads at the same time(i.e.PARALLEL PROCESS)
Then I implmented semphores on my OWN semaphore (in two ways)

First way:which uses only  while loop but disadvantage is Busy Waiting(wastes cpu cycles)  
  
Secondway Way:which uses queue datastucture to store block() threads

see the files semphores library files to get full code.
Here i implemented 3 main semaphores functions  
1) sem_init_(for inilization of any semapores)
2) sem_wait (act as w(s) signal)
3) sem_post (act as v(s) signal) 

here i implemented the same function name and syntax ( such as type of parameteres and no_of para) as there in inbuilt.
i implemented in that way because i want to test with inbuilt semaphore code(i.e. i will just import my semaphore library 
instead to see whether is it giving simillar seqeuence of threads with the solution obtained by inbuilt semapore library)  
this is the good way for testingtypedef struct


struct for  first way
{ 
 atomic_int s;// atomic varible to protect through control section  
 pthread_mutex_t lock1; // lock for sem wait   
 
}



struct for the second way {
   atomic_int s;  // semaphore varible
   queue Q;           // queue for storing blocked threads
   pthread_mutex_t lock1; 
   pthread_mutex_t lock2;
   pthread_mutex_t excusion_between_signal_ans_wait ;
}




prerequisite : c language,idea about semaphores
 
The solution i have written for this problem is deadlock free 
Solutions :-
The readers–writers problem has several variations, all involving
priorities. The simplest one, referred to as the first readers–writers problem,
requires that no reader be kept waiting unless a writer has already obtained
permission to use the shared object. 

here  semaphores used 
sem_t wrt; // semaphore to control mutual excision b/w two writers and (a writer)&(a reader) 
sem_t mutex; // semaphore to control mutual excision b/w two writers and two readers
int readcount=0; // to see how manyreders are redaing at a particular time 

do {
wait(rw mutex);
...
/* writing is performed */
...
signal(rw mutex);
} while (true);

The structure of a writer process.


do {
wait(mutex);
read count++;
if (read count == 1)
wait(rw mutex);
signal(mutex);
...
/* reading is performed */
...
wait(mutex);
read count--;
if (read count == 0)
signal(rw mutex);
signal(mutex);
} while (true);

The structure of a reader process


this code deadlock free but lttole cjance o starvation is there 

part from this code in semaphore implemtation i used linked list bascially it is the queue formed by linked list  
