#ifndef QTCOMLIBRARY_H
#define QTCOMLIBRARY_H

#include "comlibrary.h"
#include <QtGlobal>
#include <QDebug>

extern "C" int OpenCOM(int nId, const char* szIniPath, RecvCallback pCallback);
extern "C" int ReadCOM(int nId, char* szRead, int nBufLen, int nTimeoutMs);
extern "C" int WriteCOM(int nId, char* szWrite, int nBufLen);

#endif // QTCOMLIBRARY_H
