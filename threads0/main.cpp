#include <iostream>
#include <thread>
#include <stdlib.h>
#include <sys/time.h>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

/*********************
 * Edie's shit
 *********************/
random_device rd;


class Pole{
    std::vector<int> pole;
    int size;
public:
    Pole(int size);
    void    fillArray(int from, int to);
    void    sortAray();
    int     getSize();
    void    printPole(int n);
    void    printPrvek(int n);
};

void Pole::fillArray(int from, int to) {
    for (int i =from; i < to; ++i) {
        pole[i]=rd()%this->size;
    }
}

void Pole::sortAray() {
    std::sort(pole.begin(), pole.end());
}

int Pole::getSize() {
    return (int)this->pole.size();
}

void Pole::printPole(int n=1) {

    for (int j = 0; j < pole.size(); ++j) {
        if (j%n==0){
            std::cout   <<  pole[j] <<  " ";
        }
    }
    /*for (int i : pole) {
        std::cout<< i <<" ";
    }*/

}

Pole::Pole(int size) {
    this->size=size;
    this->pole.resize(size);
}

void Pole::printPrvek(int n) {
//    int N=pole.size()/n;
    for (int j = 0; j < pole.size(); ++j) {
        if (j%n==0){
            std::cout <<    "Vlakno:" << pthread_self() <<  "\nPrvek:"  <<  pole[j] <<  "\n";
        }
    }
}




/**********************
 * Someone's else shit
 **********************/

/*
void fill_array(int *arr, int x, int y)
{

    for(int i = x; i < y; i++)
    {
        arr[i] = rd() % 1000 + 1;
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
 */
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
    /*const int len = 100;
    int *arr = create_array(len);
    fill_array_threads(arr, len, 2);
    //fill_array(arr, 10, 20);
    //b_sort(arr, len);
    print_array(arr, len);*/
    int thread, siz;
    std::cout   <<  "zadej pocet vlaken:";
    std::cin    >>  thread;
    std::cout   <<  "zadej celikost pole:";
    std::cin    >>  siz;
    if (thread>4 or thread<0){
        std::cout   <<  "spatny pocet vlaken";
        return 1;
    }
    if (siz<1 or siz>100000000){
        std::cout   <<  "spatna velikost pole";
        return 1;
    }
    Pole *arry= new Pole(siz);


    /*int size=arry->getSize();

    std::thread te (&Pole::fillArray, arry, 0, size/3);
    std::thread te2 (&Pole::fillArray, arry,size/3,2*(size/3));
    std::thread te3 (&Pole::fillArray, arry,2*(size/3), size);

    te.join();
    te2.join();
    te3.join();

    arry->printPole();
    std::cout<<"\n";

    arry->sortAray();
    arry->printPole();
*/
    clock_t before, after;
    before=clock();
    int size=arry->getSize();
    if (thread==1) {
        arry->fillArray(0, size);
    }else if (thread==2) {
        std::thread te(&Pole::fillArray, arry, 0, size / 2);
        std::thread te2(&Pole::fillArray, arry, size / 2, size);

        te.join();
        te2.join();

    }else if (thread==3) {
        std::thread te(&Pole::fillArray, arry, 0, size / 3);
        std::thread te2(&Pole::fillArray, arry, size / 3, 2 * (size / 3));
        std::thread te3(&Pole::fillArray, arry, 2 * (size / 3), size);

        te.join();
        te2.join();
        te3.join();
    } else if (thread==4) {
        std::thread te(&Pole::fillArray, arry, 0, size / 4);
        std::thread te2(&Pole::fillArray, arry, size / 4, 2 * (size / 4));
        std::thread te3(&Pole::fillArray, arry, 2 * (size / 4), 3 * (size / 4));
        std::thread te4(&Pole::fillArray, arry, 3 * (size / 4), size);



        te.join();
        te2.join();
        te3.join();
        te4.join();
    }
    after=clock();
    //arry->printPrvek(5);
    double timeTick=after-before;
    double timeMs=timeTick/(CLOCKS_PER_SEC/1000);
    std::cout   <<  "Time: "    <<   timeMs   <<  "\n";
    //printf( "The fill time: %d [ms]\n", timeval_to_ms( &time_before, &time_after ) );
    std::cout<<"\n";

   /* arry->sortAray();
    arry->printPrvek(5);
*/



    return 0;
}
