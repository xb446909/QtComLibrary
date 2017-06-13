#include "serialportproc.h"

SerialPortProc::SerialPortProc(RecvCallback pCallback, QObject *parent)
    : QSerialPort(parent)
    , recvCallback(pCallback)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readReadySlot()));
}

void SerialPortProc::setParity(int nParity)
{
    switch (nParity) {
    case 0:
        QSerialPort::setParity(QSerialPort::NoParity);
        break;
    case 1:
        QSerialPort::setParity(QSerialPort::OddParity);
        break;
    case 2:
        QSerialPort::setParity(QSerialPort::EvenParity);
        break;
    case 3:
        QSerialPort::setParity(QSerialPort::SpaceParity);
        break;
    case 4:
        QSerialPort::setParity(QSerialPort::MarkParity);
        break;
    default:
        QSerialPort::setParity(QSerialPort::UnknownParity);
        break;
    }
}

void SerialPortProc::readReadySlot()
{
    QByteArray bytes = readAll();
    recvCallback(bytes.size(), bytes.data());
}
