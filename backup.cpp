#include "backup.h"
#include "includes.h"
#include <stdio.h>
BackUp::BackUp(){
    std::cout << "constructor BackUp " << this << std::endl;
}

BackUp::~BackUp(){
    std::cout << "destructor BackUp " << this << std::endl;
}

void* BackUp::loadData(const char *fileName, int &nSize) {
    FILE * pF = fopen(fileName, "rb");
    size_t fsize = 0;
    if(pF != NULL) {
        fseek(pF, 0L, SEEK_END);
        fsize = ftell(pF);
        fseek(pF, 0L, SEEK_SET);

        char *pData = new char[fsize];
        nSize = fread(pData, (size_t)sizeof(char), fsize, pF);

        fclose(pF);
        return pData;
    }
    return 0;
}

bool BackUp::saveData(const char *fileName, void *pData, int nSize, char cMode) {
    //a - append to the end,    w - create new file or rewrite data in existing file
    char* strM = new char[3];
    strM[0] = cMode;
    strM[1] = 'b';
    strM[2] = '\0';

    if(cMode != 'a' && cMode != 'w')
        strM[0] = 'w';

    FILE *pF = fopen(fileName, strM);
    if(pF != 0) {
        fwrite(pData, 1, nSize, pF);
        fclose(pF);
        return true;
    }

    return false;
}

