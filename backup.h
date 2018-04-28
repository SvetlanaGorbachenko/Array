#ifndef BACKUP_H
#define BACKUP_H

class BackUp
{

public:
    BackUp();
    ~BackUp();

    bool saveData(const char *fileName, void *pData, int nSize, char cMode);   //a - append to the end,    w - create new file or rewrite data in existing file
    void *loadData(const char *fileName, int &nSize);


};

#endif // BACKUP_H
