#ifndef COMLIBRARY_H
#define COMLIBRARY_H

typedef int(*RecvCallback)(int nSize, const char* szRecv);

typedef int(*fOpenCOM)(int nId, const char* szIniPath, RecvCallback pCallback);
typedef int(*fReadCOM)(int nId, char* szRead, int nBufLen, int nTimeoutMs);
typedef int(*fWriteCOM)(int nId, char* szWrite, int nBufLen);

#endif // COMLIBRARY_H
