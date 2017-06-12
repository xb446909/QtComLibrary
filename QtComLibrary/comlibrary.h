#ifndef COMLIBRARY_H
#define COMLIBRARY_H

typedef int(*RecvCallback)(int nSize, const char* szRecv);

typedef int(*fOpenCOM)(int nId, const char* szIniPath);

#endif // COMLIBRARY_H
