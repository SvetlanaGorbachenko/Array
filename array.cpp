#include "array.h"
#include "includes.h"
#include "backup.h"

Array::Array(int n):m_nSize(n), m_iCurrInd(0), m_pArr(0), m_pbackUp(0){ //set null value for m_pbackUp pointer
    if(n <= 0) {
        m_pArr = 0;
        m_nSize = 0;
    } else {
        m_pArr = new int [n];
    }
    std::cout << "constructor Array(int n) " << this << std::endl;
}

Array::Array(const Array & R):m_nSize(R.m_nSize), m_iCurrInd(R.m_iCurrInd), m_pArr(0), m_pbackUp(0){
    if(R.m_pArr != 0) {
        m_pbackUp = R.m_pbackUp;
        m_pArr = new int[m_nSize];
        memcpy(m_pArr, R.m_pArr, sizeof(int) * R.m_iCurrInd);
    }

    std::cout << "Array(const Array & R) " << this << " from " << &R << ' ' << m_nSize << std::endl;

}

Array::Array(const int *pArr, int nSize):m_nSize(nSize), m_iCurrInd(nSize), m_pArr(0), m_pbackUp(0){ // and here
    if(nSize <= 0) {
        m_nSize = 0;
        m_iCurrInd = 0;

    } else {
        m_pArr = new int[nSize];
        memcpy(m_pArr, pArr, sizeof(int) * nSize);
        m_iCurrInd = nSize;
    }
    std::cout << "Array(const int *, int) " << this << " " << m_nSize << std::endl;
}

Array::~Array() {
    if(m_pArr != 0)
        delete [] m_pArr;

    std::cout << "destructor ~Array() for " << this << std::endl;
}

void Array::show() {
    for(int i = 0; i < m_iCurrInd; ++i)
        std::cout << std::setw(3) << m_pArr[i];
    std::cout << std::endl;
}

void Array::addMem() {
    int newSize = (m_nSize == 0 ? 1 : m_nSize * 2);
    int *pTempArr = new int[newSize];
    if(m_nSize <= 50) {
       for(int i = 0; i < m_nSize; ++i)
            pTempArr[i] = m_pArr[i];
    } else {
        memcpy(pTempArr, m_pArr, sizeof(int) * m_nSize);
    }
    delete [] m_pArr;
    std::cout << "addMem for " << m_pArr  << " size: " << newSize << std::endl;
    m_nSize = newSize;
    m_pArr = pTempArr;

}

void Array::pushBack(int el) {
    if(m_iCurrInd == m_nSize) {
        addMem();
    }
    m_pArr[m_iCurrInd++] = el;
}

int Array::size() {
    return m_iCurrInd;
}

void Array::getDataFromFile(const char *pFileName) {
    int ntempSize = 0;
    void *pData = 0;
    pData = m_pbackUp->loadData(pFileName, ntempSize);
    if(pData != 0 && ntempSize != 0) {
        std::cout <<"I get data" << std::endl;
        m_nSize = ntempSize/sizeof(int);
        m_iCurrInd = ntempSize = ntempSize/sizeof(int);
        m_pArr = (int *)pData;
    }
}

void Array::setBackUp(BackUp *pbackUp) {
    m_pbackUp = pbackUp;
}

void Array::saveToFile(const char *fileName, char cMode) {
    if(m_pbackUp->saveData(fileName, m_pArr, sizeof(int) * m_iCurrInd, cMode))
        std::cout << "the file was save";
    else
        std::cout << "the file wasn't save";
}

// overloading
Array & Array::operator=(const Array &R)
{
    std::cout << "Array::operator= \n";

    if (this != &R)
    {
        this->~Array();
        this->m_nSize = R.m_nSize;
        this->m_pArr = new int[this->m_nSize];
        if (this->m_nSize < 50)
        {
            for (int i = 0; i < this->m_nSize; ++i)
                this->m_pArr[i] = R.m_pArr[i];
        }
        else
            memcpy(this->m_pArr, R.m_pArr, sizeof(int) * R.m_nSize);
    }

    return *this;
}

Array Array::operator+(const Array &R)
{
    std::cout << "call Array::operator+" << std::endl;
    int *pAr = 0;
    int size = m_nSize + R.m_nSize;
    if (size > 0)
    {
        pAr = new int[size];
        int iPos = 0;

        for (int i = 0; i < m_nSize; ++i)
            pAr[iPos++] = m_pArr[i];
        for(int i = 0; i < R.m_nSize; ++i)
            pAr[iPos++] = R.m_pArr[i];
    }
    Array ptemp(pAr, size);
    if(pAr != 0)
        delete [] pAr;
    return ptemp;
}

Array  operator+ (const int a, const Array &A)
{
    int nSize = A.m_nSize + 1;
    int *pArr = new int[nSize];
    int iPos(1);
    pArr[0] = a;

    for (int i = 0; i < A.m_nSize; ++i)
        pArr[iPos++] = A.m_pArr[i];

    Array pNewArray(pArr, nSize);
    delete[] pArr;

    std::cout << "operator + for int and Array obj" << std::endl;

    return pNewArray;
}


Array Array::operator+(const int a)
{
    int *pAr = new int[m_nSize + 1];
    for (int i = 0; i < m_nSize; ++i)
        pAr[i] = m_pArr[i];
    pAr[m_nSize] = a;

    Array A(pAr, m_nSize + 1);
    delete[] pAr;

    return A;
}

std::ostream & operator<<(std::ostream & out, const Array &A)
{
    for (int i = 0; i < A.m_nSize; ++i)
    {
        out << A.m_pArr[i] << " ";
    }
    out << std::endl;

    return out;
}

