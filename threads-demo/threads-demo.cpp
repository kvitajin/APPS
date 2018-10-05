// ***********************************************************************
//
// Demo program for subject Computer Architectures and Paralel systems 
// Petr Olivka, Dept. of Computer Science, FEECS, VSB-TU Ostrava
// email:petr.olivka@vsb.cz
//
// Threads programming example for Linux (10/2016)
// For the propper testing is necessary to have at least 2 cores CPU
//
// ***********************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/param.h>
#include <pthread.h>

#define TYPE int

struct thread_argument
{
    int id;                 // user identification
    int from, length;       // data range
    TYPE *data;             // array
    TYPE max;               // result 
};

// function search_max search the largest number in part of array
// from the left (included) up to the right element
TYPE search_max( int left, int length, TYPE *array )
{
    TYPE max_elem = array[ left ];
    for ( int i = 1; i < length; i++ )
        if ( max_elem < array[ left + i ] )
            max_elem = array[ left + i ];
    return max_elem;
}

// Thread will search the largest element in array 
// from element arg->from with length of arg->length.
// Result will be stored to arg->max.
void *my_thread( void *void_arg )
{
    thread_argument *ptr_data = ( thread_argument * ) void_arg;

    printf( "Thread %d started from %d with length %d...\n",
        ptr_data->id, ptr_data->from, ptr_data->length );

    ptr_data->max = search_max( ptr_data->from, ptr_data->length, ptr_data->data );

    printf( "Found maximum in thread %d is %d\n", ptr_data->id, ptr_data->max );

    return NULL;
}

// Time interval between two measurements
int timeval_to_ms( timeval *before, timeval *after )
{
    timeval res;
    timersub( after, before, &res );
    return 1000 * res.tv_sec + res.tv_usec / 1000;
}

#define LENGTH_LIMIT 10000000

int main( int na, char **arg )
{
    // The number of elements must be used as program argument
    if ( na != 2 ) 
    { 
        printf( "Specify number of elements, at least %d.\n", LENGTH_LIMIT ); 
        return 0; 
    }
    int my_length = atoi( arg[ 1 ] );
    if ( my_length < LENGTH_LIMIT ) 
    { 
        printf( "The number of elements must be at least %d.\n", LENGTH_LIMIT ); 
        return 0; 
    }

    // array allocation
    TYPE *my_array = new TYPE [ my_length ];
    if ( !my_array ) 
    {
        printf( "Not enought memory for array!\n" );
        return 1;
    }

    // Initialization of random number generator
    srand( ( int ) time( NULL ) );

    printf( "Random numbers generetion started..." );
    for ( int i = 0; i < my_length; i++ )
    {
            my_array[ i ] = rand() % ( my_length * 10 );
            if ( !( i % LENGTH_LIMIT ) ) 
            {
                printf( "." ); 
                fflush( stdout );
            }
    }

    printf( "\nMaximum number search using two threads...\n" );
    pthread_t pt1, pt2;
    thread_argument ta1, ta2;
    timeval time_before, time_after;

    // Initialization of thread arguments
    ta1.id = 1;
    ta1.from = 0;
    ta1.length = my_length / 2;
    ta1.data = my_array;

    ta2.id = 2;
    ta2.from = ta1.length;
    ta2.length = my_length - ta1.length;
    ta2.data = my_array;

    // Time recording before searching
    gettimeofday( &time_before, NULL );


    // Threads starting
    pthread_create( &pt1, NULL, my_thread, &ta1 );
    pthread_create( &pt2, NULL, my_thread, &ta2 );

    // Waiting for threads completion 
    pthread_join( pt1, NULL );
    pthread_join( pt2, NULL );

    // Time recording after searching
    gettimeofday( &time_after, NULL );

    printf( "The found maximum: %d\n", MAX( ta1.max, ta2.max ) );
    printf( "The search time: %d [ms]\n", timeval_to_ms( &time_before, &time_after ) );

    printf( "\nMaximum number search using one thread...\n" );

    gettimeofday( &time_before, NULL );

    // Searching in single thread
    TYPE M = search_max( 0, my_length, my_array );

    gettimeofday( &time_after, NULL );

    printf( "The found maximum: %d\n", M );
    printf( "The search time: %d [ms]\n", timeval_to_ms( &time_before, &time_after ) );
}
