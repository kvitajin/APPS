#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/param.h>
#include <pthread.h>

#define TYPE int

class generator
{
public:
    int id;
    int from;
    int length;
    int maxlength;
    int* field;

    generator(int id, int od, int delka, int maxdelka, int* pole){
        this->length = delka;
        this->maxlength = maxdelka;
        this->id = id;
        this->from = od;
        this->field = pole;

    }

};

void* fillIt(void * void_arg){
    generator *lol = ( generator * ) void_arg;

    srand( ( int ) time( NULL ) );

    for ( int i = lol->from; i < (lol->from + lol->length); i++ )
    {
        lol->field[ i ] = rand() % lol->maxlength;
        if (i < (lol->from+5)){
            printf( "The thread %d generated number %d \n", lol->id, lol->field[i]);
        }
    }

}

#define LENGTH_LIMIT 100000000
#define NumOfThreads 2


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
    int my_length = 100000000;

    // array allocation
    TYPE *my_array = new TYPE [ my_length ];
    if ( !my_array )
    {
        printf( "Not enought memory for array!\n" );
        return 1;
    }
    /////////////////////////////////////////////////////////////////////////////////

    pthread_t threads [NumOfThreads];
    generator* genArg[NumOfThreads];

    for (int i = 0; i < NumOfThreads; i++){
        generator* fuckit = new generator ((i+1), (i*LENGTH_LIMIT/NumOfThreads), (LENGTH_LIMIT/NumOfThreads), LENGTH_LIMIT, my_array);
        genArg[i] = fuckit;
    }

   for (int j = 0; j < NumOfThreads; j++){
        pthread_create( &threads[j], NULL, fillIt, genArg[j]);
    }

    for (unsigned long thread : threads) {
        pthread_join(thread, NULL );
    }





}














