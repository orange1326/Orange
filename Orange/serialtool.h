#ifndef SERIALTOOL_H
#define SERIALTOOL_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QVector>

class SerialTool : public QObject
{
    Q_OBJECT

public:
    //Serial Set
    QString serialName;
    QString serialBaud;
    QString serialDataBit;
    QString serialCheckBit;
    QString serialStopBit;
    QString serialFlowBit;
    //Receive Set
    bool displayForm;
    bool receiveAutoNewlineFlag;
    bool showSendContentFlag;
    bool showInfoTimeFlag;
    //Send Set
    bool sendForm;
    bool sendAutoNewlineFlag;
    bool repeatSendFlag;
    int repeatSendmS;
public:
    SerialTool();
    SerialTool(QObject *parent);

    bool openSerial();
    void closeSerial();
    bool clearSerial();
    QVector<QString> getSerialName();
    QSerialPort *getCurrentOpenSerial();
    bool checkPullSerial(QString serialName);
    bool isOpen();
    void writeSerial(const QByteArray array);
public slots:
    void searchSerial();
private:
    QSerialPort *serialPort;
    QSerialPortInfo *serialPortInfo;
    QList<QSerialPortInfo> serialPortLists;
    QVector<QString> serialNameVector;
    QByteArray array;

    void openSerialConfig();
};

#endif // SERIALTOOL_H
