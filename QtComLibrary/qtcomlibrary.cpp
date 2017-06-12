#include "qtcomlibrary.h"
#include "iniconfig.h"
#include "serialportproc.h"
#include <QSharedPointer>

#ifndef USE_IN_QT_APP
int _argc = 1;
QSharedPointer<QCoreApplication> app(new QCoreApplication(_argc, nullptr));
#endif

QHash<int, QSharedPointer<SerialPortProc>> g_serialProc;

int OpenCOM(int nId, const char* szIniPath)
{
    g_serialProc.remove(nId);
    g_serialProc.insert(nId, QSharedPointer<SerialPortProc>(new SerialPortProc()));
    auto serialProc = g_serialProc[nId];

    IniConfig config(szIniPath);
    QString section = QString().sprintf("SerialPort%d", nId);
    QVariant portName = config.GetValue(section, "PortName", "COM1");
    QVariant baudRate = config.GetValue(section, "BaudRate", 115200);
    QVariant dataBits = config.GetValue(section, "DataBits", 8);
    QVariant parity = config.GetValue(section, "Parity", 0);
    QVariant stopBits = config.GetValue(section, "StopBits", 1);

    serialProc->setPortName(portName.toString());
    serialProc->setBaudRate(baudRate.toInt());
    serialProc->setDataBits((QSerialPort::DataBits)dataBits.toInt());
    serialProc->setParity(parity.toInt());
    serialProc->setStopBits((QSerialPort::StopBits)stopBits.toInt());
    serialProc->open(QSerialPort::ReadWrite);

    return 0;
}
