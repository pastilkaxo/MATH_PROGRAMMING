#include <stdio.h>
#include "Auxil.h" 
#include <ctime>    
namespace mp1
{
    void start()                          
    {
        srand((unsigned)time(NULL));
    };
    double dget(double rmin, double rmax) 
    {
        return ((double)rand() / (double)RAND_MAX) * (rmax - rmin) + rmin;
    };
    int iget(int rmin, int rmax)         

    {
        return (int)dget((double)rmin, (double)rmax);
    };
}
