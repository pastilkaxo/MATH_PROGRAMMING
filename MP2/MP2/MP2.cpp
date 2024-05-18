#include <tchar.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include "Combi.h"
#include "Auxil.h"
#include <iomanip> 
#define N (sizeof(AA)/2)
#define M 3
#include "Knapsack.h"
#define NN 18
#define NC 12


int _tmain1() {
    char  AA[][2] = { "A", "B", "C", "D" };
    std::cout << std::endl << " - Генератор множества всех подмножеств -";
    std::cout << std::endl << "Исходное множество: ";
    std::cout << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        std::cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    std::cout << "}";
    std::cout << std::endl << "Генерация всех подмножеств  ";
    combi::subset s1(sizeof(AA) / 2);         // создание генератора   
    int  n = s1.getfirst();                // первое (пустое) подмножество    
    while (n >= 0)                          // пока есть подмножества 
    {
        std::cout << std::endl << "{ ";
        for (int i = 0; i < n; i++)
            std::cout << AA[s1.ntx(i)] << ((i < n - 1) ? ", " : " ");
        std::cout << "}";
        n = s1.getnext();                   // cледующее подмножество 
    };
    std::cout << std::endl << "всего: " << s1.count() << std::endl;

    return 0;
}

int _tmain2 () {
    char  AA[][2] = { "A", "B", "C", "D", "E" };
    std::cout << std::endl << " --- Генератор сочетаний ---";
    std::cout << std::endl << "Исходное множество: ";
    std::cout << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)

        std::cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    std::cout << "}";
    std::cout << std::endl << "Генерация сочетаний ";
    combi::xcombination xc(sizeof(AA) / 2, 3);
    std::cout << "из " << xc.n << " по " << xc.m;
    int  n = xc.getfirst();
    while (n >= 0)
    {

        std::cout << std::endl << xc.nc << ": { ";

        for (int i = 0; i < n; i++)


            std::cout << AA[xc.ntx(i)] << ((i < n - 1) ? ", " : " ");

        std::cout << "}";

        n = xc.getnext();
    };
    std::cout << std::endl << "всего: " << xc.count() << std::endl;
    return 0;

}

int _tmain3() {
    char  AA[][2] = { "A", "B", "C", "D" };
    std::cout << std::endl << " --- Генератор перестановок ---";
    std::cout << std::endl << "Исходное множество: ";
    std::cout << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)

        std::cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    std::cout << "}";
    std::cout << std::endl << "Генерация перестановок ";
    combi::permutation p(sizeof(AA) / 2);
    __int64  n = p.getfirst();
    while (n >= 0)
    {
        std::cout << std::endl << std::setw(4) << p.np << ": { ";

        for (int i = 0; i < p.n; i++)

            std::cout << AA[p.ntx(i)] << ((i < p.n - 1) ? ", " : " ");

        std::cout << "}";

        n = p.getnext();
    };
    std::cout << std::endl << "всего: " << p.count() << std::endl;
    return 0;

}


int _tmain4() {
    char  AA[][2] = { "A", "B", "C", "D" };
    std::cout << std::endl << " --- Генератор размещений ---";
    std::cout << std::endl << "Исходное множество: ";
    std::cout << "{ ";
    for (int i = 0; i < N; i++)

        std::cout << AA[i] << ((i < N - 1) ? ", " : " ");
    std::cout << "}";
    std::cout << std::endl << "Генерация размещений  из  " << N << " по " << M;
    combi::accomodation s(N, M);
    int  n = s.getfirst();
    while (n >= 0)
    {

        std::cout << std::endl << std::setw(2) << s.na << ": { ";

        for (int i = 0; i < 3; i++)

            std::cout << AA[s.ntx(i)] << ((i < n - 1) ? ", " : " ");

        std::cout << "}";

        n = s.getnext();
    };
    std::cout << std::endl << "всего: " << s.count() << std::endl;
    return 0;

}

// ----------------------------------------------------------------------


int _knapsack() {
    int V = 300,                // вместимость рюкзака              
        v[NN] ,     // размер предмета каждого типа  
        c[NN];     // стоимость предмета каждого типа 
    short m[NN];                // количество предметов каждого типа  {0,1}   
    
    srand(time(0));
    for (int i = 0; i < 18; i++) {
        v[i] = mp1::iget(10, 300);
    }
    for (int i = 0; i < 18; i++) {
        c[i] = mp1::iget(5, 55);
    }

    
    int maxcc = knapsack_s(

        V,   // [in]  вместимость рюкзака 
        NN,  // [in]  количество типов предметов 
        v,   // [in]  размер предмета каждого типа  
        c,   // [in]  стоимость предмета каждого типа     
        m    // [out] количество предметов каждого типа  
    );

    std::cout << std::endl << "-------- Задача о рюкзаке --------- ";
    std::cout << std::endl << "- количество предметов : " << NN;
    std::cout << std::endl << "- вместимость рюкзака  : " << V;
    std::cout << std::endl << "- размеры предметов    : ";
    for (int i = 0; i < NN; i++) std::cout << v[i] << " ";
    std::cout << std::endl << "- стоимости предметов  : ";
    for (int i = 0; i < NN; i++) std::cout << v[i] * c[i] << " ";
    std::cout << std::endl << "- оптимальная стоимость рюкзака: " << maxcc;
    std::cout << std::endl << "- вес рюкзака: ";
    int s = 0; for (int i = 0; i < NN; i++) s += m[i] * v[i];
    std::cout << s;
    std::cout << std::endl << "- выбраны предметы: " << std::endl;
    std::cout << "Вес: \t" << "Стоимость: " << "Предмет:\t" << std::endl;
    for (int i = 0; i < NN; i++) {
            std::cout << (m[i] == 1 ? v[i] : 0) << "\t" << (m[i] == 1 ? c[i] : 0) << "\t" << m[i] << std::endl;
    }
    std::cout << std::endl << std::endl;


    return 0;

}



int _knapsack_timer() {
    clock_t t1 = 0, t2 = 0;
    int V = 300,                // вместимость рюкзака              
        v[20],     // размер предмета каждого типа  
        c[20];     // стоимость предмета каждого типа 
        short m[20];
        srand(time(0));
        for (int i = 0; i < 20; i++) {
            v[i] = mp1::iget(10, 300);
        }
        for (int i = 0; i < 20; i++) {
            c[i] = mp1::iget(5, 55);
        }


    for (int nc = 12; nc <= 20; nc++) {
        t1 = clock();
        int maxcc = knapsack_s(

            V,   // [in]  вместимость рюкзака 
            nc,  // [in]  количество типов предметов 
            v,   // [in]  размер предмета каждого типа  
            c,   // [in]  стоимость предмета каждого типа     
            m    // [out] количество предметов каждого типа  
        );
        t2 = clock();

        std::cout << std::endl << "-------- Задача о рюкзаке --------- ";
        std::cout << std::endl << "- количество предметов : " << nc;
        std::cout << std::endl << "- вместимость рюкзака  : " << V;
        std::cout << std::endl << "- размеры предметов    : ";
        for (int i = 0; i < nc; i++) std::cout << v[i] << " ";
        std::cout << std::endl << "- стоимости предметов  : ";
        for (int i = 0; i < nc; i++) std::cout << v[i] * c[i] << " ";
        std::cout << std::endl << "- оптимальная стоимость рюкзака: " << maxcc;
        std::cout << std::endl << "- вес рюкзака: ";
        int s = 0; for (int i = 0; i < nc; i++) s += m[i] * v[i];
        std::cout << s;
        std::cout << std::endl << "- выбраны предметы: ";
        for (int i = 0; i < nc; i++) std::cout << " " << m[i];
        std::cout << std::endl;
        std::cout << "Затраченное время (y.e): " << (t2 - t1) << std::endl;
        std::cout << std::endl << std::endl;

     }

    return 0;

}




int _tmain(int argc, _TCHAR* argv)
{
    setlocale(LC_ALL, "rus");
    int c;
    std::cout << "1 - Генератор подмножеств заданного множества\n"
        << "2 - Генератор сочетаний\n"
        << "3 - Генератор перестановок\n"
        << "4 - Генератор размещений\n"
        << "5 - Упрощенная задача о рюкзаке\n"
        << "6 - Зависимость времени для решения задачи о рюкзаке\n";
    std::cin >> c;
    switch (c) {
    case 1:
        _tmain1();
        break;
    case 2:
        _tmain2();
        break;
    case 3:
        _tmain3();
        break;
    case 4:
        _tmain4();
        break;
    case 5:
        _knapsack();
        break;
    case 6:
        _knapsack_timer();
        break;
    }
    system("pause");
    return 1;
}




