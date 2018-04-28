#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
class BackUp;

class Array
{
    int m_nSize;
    int m_iCurrInd;
    int * m_pArr;
    BackUp *m_pbackUp;

    void addMem();

public:
    Array(int size);
    Array(const Array & R);
    Array(const int *pArr, int nSize);
    ~Array();


    void show();
    void pushBack(int el);
    int size();
    void getDataFromFile(const char *pFileName);
    void setBackUp(BackUp *pbackUp);
    void saveToFile(const char *fileName, char cMode);

    //overloading

    //for Ar = Ar2
    Array & operator=(const Array &R);

    //for Ar1 + Ar2
    Array operator+(const Array &R);

    //for int + Ar
    friend Array operator+ (const int a, const Array &A);

    //for Ar + int
    Array operator+ (const int a);

    //for cout << Ar
    friend std::ostream & operator<<(std::ostream & out, const Array &A);

};

#endif // ARRAY_H
