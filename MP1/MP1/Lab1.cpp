#include <iostream>
#include <ctime>
#include <locale>
#include <tchar.h>
#include "Auxil.h"
#include <stdio.h>


unsigned long long fib(unsigned);

int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "rus");
    clock_t t1 = 0, t2 = 0;

    mp1::start();
    for (unsigned i = 300; i <= 450; i++)
    {  
        t1 = clock();
        auto n = fib(i);
        t2 = clock();
        std::cout << i << " - " << n << " : " << (t2-t1) << "\n";
    }

    std::cout << std::endl;
    system("pause");
    return 0;

}

unsigned long long fib(unsigned n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fib(n - 1) + fib(n - 2);
}
