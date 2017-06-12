#ifndef SERIALPORTPROC_H
#define SERIALPORTPROC_H

#include <QSerialPort>

class SerialPortProc : public QSerialPort
{
    Q_OBJECT
public:
    SerialPortProc();
    void setParity(int nParity);
};

#endif // SERIALPORTPROC_H
