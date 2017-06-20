#ifndef QTCOMLIBRARY_H
#define QTCOMLIBRARY_H

#include "comlibrary.h"
#include <QtGlobal>
#include <QDebug>

extern "C" Q_DECL_EXPORT int OpenCOM(int nId, const char* szIniPath, RecvCallback pCallback);
extern "C" Q_DECL_EXPORT int ReadCOM(int nId, char* szRead, int nBufLen, int nTimeoutMs);
extern "C" Q_DECL_EXPORT int WriteCOM(int nId, char* szWrite, int nBufLen);
extern "C" Q_DECL_EXPORT int CloseCOM(int nId);

#endif // QTCOMLIBRARY_H
