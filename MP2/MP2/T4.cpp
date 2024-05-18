#include "Combi.h"
namespace combi
{
    accomodation::accomodation(short n, short m)
    {
        this->n = n;
        this->m = m;
        this->cgen = new xcombination(n, m);
        this->pgen = new permutation(m);
        this->sset = new short[m];
        this->reset();
    }
    void  accomodation::reset()
    {
        this->na = 0;
        this->cgen->reset();
        this->pgen->reset();
        this->cgen->getfirst();
    };
    short accomodation::getfirst()
    {
        short rc = (this->n >= this->m) ? this->m : -1;
        if (rc > 0)
        {
            for (int i = 0; i <= this->m; i++)
                this->sset[i] = this->cgen->sset[this->pgen->ntx(i)];
        };
        return rc;
    };
    short accomodation::getnext()
    {
        short rc;
        this->na++;
        if ((this->pgen->getnext()) > 0) rc = this->getfirst();
        else  if ((rc = this->cgen->getnext()) > 0)
        {
            this->pgen->reset();  rc = this->getfirst();
        };
        return rc;
    };
    short accomodation::ntx(short i)
    {
        return this->sset[i];
    };

    unsigned __int64 fact4(unsigned __int64 x) { return (x == 0) ? 1 : (x * fact4(x - 1)); };

    unsigned __int64  accomodation::count() const
    {

        return (this->n >= this->m) ?
            fact4(this->n) / fact4(this->n - this->m) : 0;
    };
}
