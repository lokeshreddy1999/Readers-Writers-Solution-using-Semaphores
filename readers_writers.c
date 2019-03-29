#include "semaphore_lib_without_busywaiting.h" 
#define NUMB_THREADS 6



sem_t wrt;
sem_t mutex;
int readcount=0;
void give_content()
{ 
  int value;
  value=10;

  FILE *fp;
    fp= fopen ("intermediate.txt", "w");
    for(int i = 0; i < value;i++)
    {
        fprintf (fp, "This is line %d\n",i + 1);
    }
    fclose(fp);
     
}

void read_content()
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
   sem_init(&wrt,0,1);
   sem_init(&mutex,0,1);
   pthread_t thread_read[NUMB_THREADS];
   pthread_t thread_write[NUMB_THREADS];
   int thread_numb[NUMB_THREADS];
   for (int i = 0; i < NUMB_THREADS;i++ ) 
   {
       thread_numb[i] = i;
       pthread_create(thread_read + i,NULL, reader,thread_numb + i);
       pthread_create(thread_write + i,NULL, writer,thread_numb + i);      
   }

   for (int i = 0; i < NUMB_THREADS; i++)
   {
      pthread_join(thread_write[i], NULL);
      pthread_join(thread_read[i], NULL);
   }

   
 
   


}





