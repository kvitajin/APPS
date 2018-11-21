#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/param.h>
#include <pthread.h>
#include <cctype>
#include <iostream>

#define TYPE char

class character
{
public:
    int id;
    int from, to;
    char * data;
    long int data_len;

    character(int id, int od, int doo, char* pole, long int delka){
        this->id = id;
        this->from = od;
        this->to = doo;
        this->data = pole;
        this->data_len = delka;

 }

  static void* generate(void*);
  static void* sort_me(void*);
  static void* show(void*);
  static void* show_all(void*);

};

 void* character::generate(void* void_arg){
	 character*lol = ( character * ) void_arg;

	 srand( ( int ) time( NULL )+ lol->id );

	 for ( int i = lol->from; i < lol->to; i++ )
	     {
	         lol->data[ i ] = (rand() % 57) + 'A';
	         while(!(std::isalpha(lol->data[i]))){
	        	 lol->data[ i ] = (rand() % 57) + 'A';
	         }
	     }
}

 void* character::show(void* void_arg){
 	 character*lol = ( character * ) void_arg;
 	 for (int a = lol->from; a < lol->to; a++){
 		 printf("%c", lol->data[a]);
 	 }
 	printf("\n");

 }

 void* character::show_all(void* void_arg){
  	 character*lol = ( character * ) void_arg;
  	 for (int a = 0; a < lol->data_len; a++){
  		 printf("%c", lol->data[a]);
  	 }
  	 printf("\n");

  }

 void swap(char *xp, char *yp)
  {
      char temp = *xp;
      *xp = *yp;
      *yp = temp;
  }


 void* character::sort_me(void* void_arg){
  	 character*lol = ( character * ) void_arg;
  	 for (int i = lol-> from; i < lol->to-1; i++){
  		 for (int j=lol->from; j < lol->to-i-1; j++){
  			 if ((int)lol->data[j] > (int)lol->data[j+1]){
  				 swap(&lol->data[j], &lol->data[j+1]);
  			 }
  		 }
  	 }

 }


#define LENGTH_LIMIT 100000000
#define NumOfThreads 4


int main( int na, char **arg )
{
   /* if ( na != 2 )
    {
        printf( "Specify number of elements, at least %d.\n", LENGTH_LIMIT );
        return 0;
    }

    int my_length = atoi( arg[ 1 ] );

    if ( my_length < LENGTH_LIMIT )
    {
        printf( "The number of elements must be at least %d.\n", LENGTH_LIMIT );
        return 0;
    }*/
// arguments set
    int my_length = 1000000;

    // array allocation
    TYPE *my_array = new TYPE [ LENGTH_LIMIT ];
    if ( !my_array )
    {
        printf( "Not enought memory for array!\n" );
        return 1;
    }
    /////////////////////////////////////////////////////////////////////////////////

    pthread_t threads [NumOfThreads];
    character* genArg[NumOfThreads];

    for (int i = 0; i < NumOfThreads; i++){
        character* ehm = new character ((i+1), (i*LENGTH_LIMIT/NumOfThreads), ((i+1)*LENGTH_LIMIT/NumOfThreads), my_array, (long int)LENGTH_LIMIT);
        genArg[i] = ehm;
    }
    std::cout<<"\n1";

   for (int c = 0; c < NumOfThreads; c++){
        pthread_create( &threads[c], NULL, character::generate, genArg[c]);
    }
    std::cout<<"\n2";

   for (int j = 0; j < NumOfThreads; j++){
	    pthread_join( threads[j], NULL);
   }
   //
    std::cout<<"\n3";


    for (int j = 0; j < NumOfThreads; j++){
           pthread_create( &threads[j], NULL, character::show, genArg[j]);
       }
    std::cout<<"\n4";


    for (int j = 0; j < NumOfThreads; j++){
	    pthread_join( threads[j], NULL);
   }
    std::cout<<"\n5";

    //

   for (int j = 0; j < NumOfThreads; j++){
		  pthread_create( &threads[j], NULL, character::sort_me, genArg[j]);
   }
    std::cout<<"\n6";


    for (int j = 0; j < NumOfThreads; j++){
 	    pthread_join( threads[j], NULL);
    }
   //
    std::cout<<"\n7";


    pthread_create( &threads[0], NULL, character::show_all, genArg[0]);
    std::cout<<"\n8";

    for (int j = 0; j < NumOfThreads; j++){
   	    pthread_join( threads[j], NULL);
      }
    std::cout<<"\n9";

//
}













