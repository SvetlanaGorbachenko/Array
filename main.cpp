#include "includes.h"
#include "array.h"
#include "backup.h"
#include <crtdbg.h>
int main()
{
    std::cout << std::endl << "****************** testing Array class objects *******************" << std::endl;

    {
        std::cout << std::endl << "-------------- create empty Array obj -------------" << std::endl;
        Array arr(0);
        for(int i = 0; i < 20; ++i)
            arr.pushBack(rand()%26 + 'A');
        arr.show();

        std::cout << std::endl << "-------------- create Array obj from another one (check copy constructor) -------------" <<std::endl;
        Array arr1(arr);
        arr1.show();

        std::cout<< std::endl << "-------------- create Array obj from simple array (check Array(int *pAr, int size) constructor) -------------"<<std::endl;
        int arrS[] = {65, 66, 67, 68};

        Array arr3(arrS, 4);
        arr3.show();

        arr3.saveToFile("test.txt", 'w');

       //  get data audition
        std::cout << "arrt----------------------" << std::endl;
        Array arrt(0);
        arrt.getDataFromFile("test.txt");
        arrt.show();




        std::cout << std::endl << "****************** the work with backup class object *******************" << std::endl;
       // Array a5(0);
        BackUp bU;
        arr.setBackUp(&bU);
        //if class BackUp don't have data members but only function-members, then we don't need create
        //class instance, we can call function-member from null-class-pointer ???????
       // arr.getDataFromFile("test.txt");
        arr.show();
        arr.saveToFile("s1.txt", 'w');


        std::cout << "\n testing operators overloading " << std::endl;
        int Arr[] = { 2, 8, 9, 44, 6 };
        std::cout << "sizeof(Arr) " << sizeof(Arr) <<  std::endl;
        Array Ar(Arr, sizeof(Arr) / sizeof(int));
        Array Ar2(Ar);

        Ar.show();
        Ar2.show();

        std::cout << "\n************   show Ar + Ar2   ***********" <<  std::endl;
        std::cout << Ar + Ar2 <<  std::endl;

        std::cout << "\n************    45 + Ar2   ***********" <<  std::endl;
        std::cout << 45 + Ar2 <<  std::endl;

        std::cout << "\n************    Ar2 + 12   ***********" <<  std::endl;
        std::cout << Ar2 + 12 <<  std::endl;

    }


    std::cout<< std::endl << "**************** check for memmory leaks  ***************************"<<std::endl;
    if(_CrtDumpMemoryLeaks())
       std::cout<<"MemoryLeaks !!!"<<std::endl;
    else
       std::cout<<"Memory OK !!!"<<std::endl;




   return 0;
}
