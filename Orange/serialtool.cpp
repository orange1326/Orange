#include "serialtool.h"
#include <qdebug.h>

SerialTool::SerialTool()
{
    serialPort = new QSerialPort();
}

SerialTool::SerialTool(QObject *parent) : QObject(parent)
{
    serialPort = new QSerialPort();
}

void SerialTool::openSerialConfig()
{
    serialPort->setPortName(serialName);
    //set baud
    switch (serialBaud.toLong()) {
    case 1200:
        serialPort->setBaudRate(QSerialPort::Baud1200);
        break;
    case 2400:
        serialPort->setBaudRate(QSerialPort::Baud2400);
        break;
    case 4800:
        serialPort->setBaudRate(QSerialPort::Baud4800);
        break;
    case 9600:
        serialPort->setBaudRate(QSerialPort::Baud9600);
        break;
    case 19200:
        serialPort->setBaudRate(QSerialPort::Baud19200);
        break;
    case 38400:
        serialPort->setBaudRate(QSerialPort::Baud38400);
        break;
    case 57600:
        serialPort->setBaudRate(QSerialPort::Baud57600);
        break;
    case 115200:
        serialPort->setBaudRate(QSerialPort::Baud115200);
        break;
    default:
        serialPort->setBaudRate(QSerialPort::UnknownBaud);
        break;
    }
    //set databit
    switch (serialDataBit.toInt()) {
    case 5:
        serialPort->setDataBits(QSerialPort::Data5);
        break;
    case 6:
        serialPort->setDataBits(QSerialPort::Data6);
        break;
    case 7:
        serialPort->setDataBits(QSerialPort::Data7);
        break;
    case 8:
        serialPort->setDataBits(QSerialPort::Data8);
        break;
    default:
        serialPort->setDataBits(QSerialPort::UnknownDataBits);
        break;
    }
    //qDebug() << serialPort->dataBits();
    //set parity
    switch (0) {
    case 0:
        serialPort->setParity(QSerialPort::NoParity);
        break;
    case 2:
        serialPort->setParity(QSerialPort::EvenParity);
        break;
    case 3:
        serialPort->setParity(QSerialPort::OddParity);
        break;
    case 4:
        serialPort->setParity(QSerialPort::SpaceParity);
        break;
    case 5:
        serialPort->setParity(QSerialPort::MarkParity);
        break;
    default:
        serialPort->setParity(QSerialPort::UnknownParity);
        break;
    }
    //set stopbit
    switch (serialStopBit.toInt()) {
    case 1:
        serialPort->setStopBits(QSerialPort::OneStop);
        break;
    case 3:
        serialPort->setStopBits(QSerialPort::OneAndHalfStop);
        break;
    case 2:
        serialPort->setStopBits(QSerialPort::TwoStop);
        break;
    default:
        serialPort->setStopBits(QSerialPort::UnknownStopBits);
        break;
    }

    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->setReadBufferSize(1024);
}

bool SerialTool::openSerial()
{
    if(serialPort->isOpen())
        return true;
    openSerialConfig();

    return serialPort->open(QSerialPort::ReadWrite);
}

void SerialTool::closeSerial()
{
    if(serialPort->isOpen())
        serialPort->close();
}

void SerialTool::searchSerial()
{
    serialPortLists = serialPortInfo->availablePorts();
    serialNameVector.clear();
    for(int i = 0;i < serialPortLists.count();i++)
    {
        serialNameVector.append(serialPortLists.at(i).portName());
    }
}

QVector<QString> SerialTool::getSerialName()
{
    return serialNameVector;
}

QSerialPort *SerialTool::getCurrentOpenSerial()
{
    return serialPort;
}

bool SerialTool::checkPullSerial(QString serialName)
{
    int i = serialNameVector.count();
    for(int j=0;j<i;j++)
    {
        if(serialName == serialNameVector.at(j))
        {
            return false;
        }
    }
    serialPort->close();
    return true;
}

bool SerialTool::isOpen()
{
    return serialPort->isOpen();
}

void SerialTool::writeSerial(const QByteArray array)
{
    serialPort->write(array);
}

