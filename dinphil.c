/*
- Description: The dining philsopher
- Author: Parsa Habibi
- Date : July 11th 2018
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

pthread_t thread_id[5];
int fork_taken[5];
pthread_mutex_t lock[5];
pthread_cond_t cv_lock[5];
pthread_cond_t cv[5];

enum State {eating = 1 , thinking = 0, hungry = 2};

struct philosepher
{
     enum State state;
};

struct philosepher philarr[5];

int LEFT;
int RIGHT;

void *philos (void *vargp)
{

  while(true)
  {
  }


}

void initilize()
{
  for(int i = 0 ; i < 5 ; i++)
  {
    struct philosepher phil;
    phil.state = thinking;
    philarr[i] = phil;
    fork_taken[i] = -1;
  }
};

int takfork(int i)
{
}

int eat(int i)
{
  /*somehow check to see if you can eat
    if ou cant eat , the go back to thinking stage. */
}

bool think(int i)
{
  while(true)
  {
    //continue thinking buddy
  };



  //if you are required to eat, let go of the mutex and thinking.
}

void *prompt(void* arg)
{
  int id = *((int *) arg);
  while(true)
  {
    if(philarr[id].state == hungry)
    {
      pthread_mutex_lock(&lock[id]);
      if (fork_taken[id] == -1) {
        fork_taken[id] = id;
      }
      pthread_mutex_unlock(&lock[id]);

      if (fork_taken[id] == id) {
        pthread_mutex_lock(&lock[(id+1)%5]);
        if (fork_taken[(id+1)%5] == -1) {
          fork_taken[(id+1)%5] = id;
        }
        pthread_mutex_unlock(&lock[(id+1)%5]);
      }

      if (fork_taken[id] == id && fork_taken[(id+1)%5] == id) {
        /// EATING
        printf("%d is eating with forks #%d and #%d\n", id, id, (id+1)%5);
        philarr[id].state = eating;

        pthread_mutex_lock(&cv_lock[id]);
        pthread_cond_wait(&cv[id], &cv_lock[id]);
        printf("%d is releasing forks #%d and #%d\n", id, id, (id+1)%5);

        pthread_mutex_lock(&lock[id]);
        fork_taken[id] = -1;
        pthread_mutex_unlock(&lock[id]);
        pthread_mutex_lock(&lock[(id+1)%5]);
        fork_taken[(id+1)%5] = -1;
        pthread_mutex_unlock(&lock[(id+1)%5]);

        pthread_mutex_unlock(&cv_lock[id]);
      }
    }
  }
}

void main ()
{
    initilize();
    for(int i = 0; i < 5 ; i++)
    {
      int *arg = malloc(sizeof(*arg));
      if ( arg == NULL ) {
          fprintf(stderr, "Couldn't allocate memory for thread arg.\n");
          exit(EXIT_FAILURE);
      }

      *arg = i;
      pthread_create(&thread_id[i],NULL,prompt,arg);
    }

    while(true)
    {
      char *buffer;
      size_t bufsize = 32;
      size_t characters;

      buffer = (char *)malloc(bufsize * sizeof(char));

      if( buffer == NULL)
      {
          perror("Unable to allocate buffer");
          exit(1);
      }
      characters = getline(&buffer,&bufsize,stdin);

      if(buffer[0] == '!' && characters == 2)
      {
        printf("you have exited the prompt\n");
        exit(1);
      }

      if(buffer[0] == 'P' && characters == 2)
      {
        printf("the states are:\n");

        for(int i = 0 ; i < 5 ; i++)
        {
          printf(" %d", philarr[i].state % 2);
        }
        printf("\n");

      }

      if(buffer[0] == 'E' && characters == 4)         /*criticall need to implemet*/
      {
        char temp_string[1] = {buffer[2]};
        int temp_index = atoi(temp_string);
        if (philarr[temp_index].state != eating) {
          philarr[temp_index].state = hungry;
        }
      }

      if(buffer[0] == 'T' && characters == 4)   /*criticall need to implemet*/
      {
        char temp_string[1] = {buffer[2]};
        int temp_index = atoi(temp_string);
        philarr[temp_index].state = thinking;
        pthread_cond_signal(&cv[temp_index]);
      }
    }

    for(int i = 0 ; i < 5 ; i++)
    {
      pthread_join(thread_id[i], NULL);
    }
}
