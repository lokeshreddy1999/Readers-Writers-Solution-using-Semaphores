#include "semaphore_lib_without_busywaiting.h" 
#define NUMB_THREADS 6 //specify the no of threads




sem_t wrt; // semaphore to control mutual excision b/w two writers and (a writer)&(a reader) 
sem_t mutex; // semaphore to control mutual excision b/w two writers and two readers
int readcount=0; 
void give_content() // decide what to write in this function 
{ 
  int value;
  value=10;

  FILE *fp;
    fp= fopen ("intermediate.txt", "w"); // this is the file where we writers writes the data  
    for(int i = 0; i < value;i++)
    {
        fprintf (fp, "This is line %d\n",i + 1);
    }
    fclose(fp);
     
}

void read_content() // read from intermediate.txt
{
   FILE *fptr;
   fptr = fopen("intermediate.txt", "r");
   if (fptr == NULL)
      {
        printf("Cannot open file \n");
        exit(0);
      }
      char ch;
   ch = fgetc(fptr);
     while (ch != EOF)
      {
        printf ("%c", ch);
        ch = fgetc(fptr);

      }
     fclose(fptr);
}


void *writer(void *thread_n)  
{
  int n1=*(int *)thread_n;

   sem_wait(&wrt);
   give_content();
   printf("writer %d completed it's work in file\n", n1);  
   sem_post(&wrt);

    
    
}

void *reader(void *thread_n)
{
   int n1=*(int *)thread_n;

    sem_wait(&mutex);
    readcount++;
    if(readcount==1)
    sem_wait(&wrt);
    sem_post(&mutex);
      


     read_content();
    
     printf("reader %d completed it's work in file\n", n1);
      sem_wait(&mutex);
    readcount--;
    if(readcount==0)
    sem_post(&wrt);
    sem_post(&mutex);
 
     
    
   
}



int main(int argc, int **argv) 
{
   sem_init(&wrt,0,1);// wrt=1;at starting 
   sem_init(&mutex,0,1); // mutex=1;at starting 
   pthread_t thread_read[NUMB_THREADS]; // read threads
   pthread_t thread_write[NUMB_THREADS]; // write threads
   int thread_numb[NUMB_THREADS];
   for (int i = 0; i < NUMB_THREADS;i++ ) 
   {
       thread_numb[i] = i;
       pthread_create(thread_read + i,NULL, reader,thread_numb + i);
       pthread_create(thread_write + i,NULL, writer,thread_numb + i);      
   }

   for (int i = 0; i < NUMB_THREADS; i++)
   {
      pthread_join(thread_write[i], NULL); // do till all threads satisfied
      pthread_join(thread_read[i], NULL);  // do till all threads satisfied
   }

   
 
   
       

}





