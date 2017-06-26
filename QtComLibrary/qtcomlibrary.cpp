#include "qtcomlibrary.h"
#include "iniconfig.h"
#include "serialportproc.h"
#include <QSharedPointer>
#include <QCoreApplication>

#ifndef USE_IN_QT_APPLICATION
int _argc = 1;
QSharedPointer<QCoreApplication> app(new QCoreApplication(_argc, nullptr));
#endif

QHash<int, QSharedPointer<SerialPortProc>> g_serialProc;

int OpenCOM(int nId, const char* szIniPath, RecvCallback pCallback)
{

#ifndef USE_IN_QT_APPLICATION
    QCoreApplication::processEvents();      // For create internal event process loop
#endif

    g_serialProc.remove(nId);
    g_serialProc.insert(nId, QSharedPointer<SerialPortProc>(new SerialPortProc(pCallback)));
    auto serialProc = g_serialProc[nId];


    IniConfig config(szIniPath);
    QString section = QString().sprintf("SerialPort%d", nId);
    QVariant portName = config.GetValue(section, "PortName", "COM1");
    QVariant baudRate = config.GetValue(section, "BaudRate", 115200);
    QVariant dataBits = config.GetValue(section, "DataBits", 8);
    QVariant parity = config.GetValue(section, "Parity", 0);
    QVariant stopBits = config.GetValue(section, "StopBits", 1);

    serialProc->setPortName(portName.toString());

    if (!serialProc->open(QSerialPort::ReadWrite))
    {
        qDebug() << "Open " << portName.toString() << " error";
        return -1;
    }
    else
    {
        serialProc->setBaudRate(baudRate.toInt());
        serialProc->setDataBits((QSerialPort::DataBits)dataBits.toInt());
        serialProc->setParity(parity.toInt());
        serialProc->setStopBits((QSerialPort::StopBits)stopBits.toInt());
        serialProc->clearError();
        serialProc->clear();
    }

    return 0;
}

int ReadCOM(int nId, char* szRead, int nBufLen, int nTimeoutMs)
{
    if (!g_serialProc.contains(nId))
    {
        qDebug() << "Wrong id: " << __func__;
        return -1;
    }
    auto serialProc = g_serialProc[nId];
    if (serialProc->waitForReadyRead(nTimeoutMs))
    {
        QByteArray bytes = serialProc->readAll();
        int nReadSize = (bytes.size() > nBufLen) ? nBufLen : bytes.size();
        memcpy(szRead, bytes.data(), nReadSize);
        return nReadSize;
    }
    else
    {
        qDebug() << "Receive timeout";
        return -1;
    }
    return 0;
}

int WriteCOM(int nId, char* szWrite, int nBufLen)
{
    if (!g_serialProc.contains(nId))
    {
        qDebug() << "Wrong id: " << __func__;
        return -1;
    }
    auto serialProc = g_serialProc[nId];
    int nRet = serialProc->write(szWrite, nBufLen);
    serialProc->waitForBytesWritten(3000);
    return nRet;
}

int CloseCOM(int nId)
{
    if (!g_serialProc.contains(nId))
    {
        qDebug() << "Wrong id: " << __func__;
        return -1;
    }
    auto serialProc = g_serialProc[nId];
    serialProc->close();
    g_serialProc.remove(nId);
    return 0;
}

