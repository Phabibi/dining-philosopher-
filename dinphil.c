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


enum s {eating = 1 , thinking = 0};

struct philosepher
{
     enum s state;
};

struct philosepher philarr[4];

void initilize()
{
  for(int i = 0 ; i < 4 ; i++)
  {
    struct philosepher phil;
    phil.state = thinking;
    philarr[i] = phil;
  }



};

void prompt()
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

  if(buffer[0] == 'P' && characters == 2)
  {
    printf("the states are:\n");

    for(int i = 0 ; i < 4 ; i++)
    {
      printf(" %d", philarr[i].state );
    }
    printf("\n");

  }

  if(buffer[0] == 'E' && characters == 4)         /*criticall need to implemet*/
  {
    char temp_string[1] = {buffer[2]};
    int temp_index = atoi(temp_string);
    philarr[temp_index].state = eating;
  }

  if(buffer[0] == 'T' && characters == 4)   /*criticall need to implemet*/
  {
    char temp_string[1] = {buffer[2]};
    int temp_index = atoi(temp_string);
    philarr[temp_index].state = thinking;
  }


}


void main ()
{
  initilize();
  while(true)
  {
    prompt();
  };
}
