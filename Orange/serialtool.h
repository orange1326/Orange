#ifndef SERIALTOOL_H
#define SERIALTOOL_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QVector>

class SerialTool : public QObject
{
    Q_OBJECT

public:
    SerialTool();
    SerialTool(QObject *parent);

    bool openSerial(QVector<QString> *para);
    void closeSerial();
    bool clearSerial();
    QVector<QString> getSerialName();
    QSerialPort *getCurrentOpenSerial();
    bool isOpen();
public slots:
    void searchSerial();
private:
    QSerialPort *serial_port;
    QSerialPortInfo *serial_port_info;

    QString string_serialport;
    QString string_lastSerialport;
    QString string_serialinfo;

    QVector<QString> serial_name_vector;
    QByteArray array;
    void openSerialConfig(QVector<QString> *para);
};

#endif // SERIALTOOL_H
