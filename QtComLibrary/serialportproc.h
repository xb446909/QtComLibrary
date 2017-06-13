#ifndef SERIALPORTPROC_H
#define SERIALPORTPROC_H

#include <QSerialPort>
#include "comlibrary.h"

class SerialPortProc : public QSerialPort
{
    Q_OBJECT
public:
    SerialPortProc(RecvCallback pCallback, QObject* parent = nullptr);
    void setParity(int nParity);

public slots:
    void readReadySlot();

private:
    RecvCallback recvCallback;
};

#endif // SERIALPORTPROC_H
