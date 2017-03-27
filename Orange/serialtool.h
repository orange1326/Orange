#ifndef SERIALTOOL_H
#define SERIALTOOL_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QVector>

class SerialTool
{
private:
    QVector<QString> serial_name_vector;
public:
    SerialTool();

    bool openSerial(QVector<QString> *para);
    void closeSerial();
    bool clearSerial();
    QVector<QString> getSerialName();

    QSerialPort *getCurrentOpenSerial();

public slots:
    void searchSerial();
private:
    QSerialPort *serial_port;
    QSerialPortInfo *serial_port_info;

    QString string_serialport;
    QString string_serialinfo;

    QByteArray array;
    void openSerialConfig(QVector<QString> *para);
};

#endif // SERIALTOOL_H
