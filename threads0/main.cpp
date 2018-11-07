#include <iostream>
#include <thread>
#include <stdlib.h>
#include <time.h>

using namespace std;

void fill_array(int *arr, int x, int y)
{
    srand (time(NULL));
    for(int i = x; i < y; i++)
    {
        arr[i] = rand() % 1000 + 1;
    }
}

void fill_array_threads(int *arr, int len, int threads_count)
{
    if(threads_count == 1)
    {
        thread t{fill_array, arr, 0, len};
        t.join();
    }
    else if(threads_count == 2)
    {
        thread t{fill_array, arr, 0, len/2};
        thread t2{fill_array, arr, len/2 + 1, len};
        t.join();
        t2.join();
    }
    else if(threads_count == 3)
    {
        thread t{fill_array, arr, 0, len/3};
        thread t2{fill_array, arr, len/3 + 1, (len/3)*2};
        thread t3{fill_array, arr, (len/3)*2 + 1, len};
        t.join();
        t2.join();
        t3.join();
    }
}

int *create_array(int len)
{
    int *arr = new int[len];
    for(int i = 0; i < len; i++)
    {
        arr[i] = i;
    }

    return arr;
}

void print_array(int *arr ,int len)
{
    for(int i = 0; i < len; i++)
    {
        cout << arr[i] << endl;
    }
}

void sw(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}
/*
void b_sort(int &arr, int len)
{
    for(int z = 0; z < len - 1; z++)
    {
        bool stop = true;
        for(int i = 0; i < len - z - 1; i++)
        {
            if(arr[i] > arr[i + 1])
            {
                sw(arr[i], arr[i + 1]);
                bool stop = false;
            }
        }
        if(stop)
        {
            break;
        }
    }
}*/

int main()
{
    const int len = 100;
    int *arr = create_array(len);
    fill_array_threads(arr, len, 2);
    //fill_array(arr, 10, 20);
    //b_sort(arr, len);
    print_array(arr, len);


    return 0;
}
