#include "serialtool.h"
#include <qdebug.h>

SerialTool::SerialTool()
{
    serial_port = new QSerialPort();
}

SerialTool::SerialTool(QObject *parent) : QObject(parent)
{
    serial_port = new QSerialPort();
}

void SerialTool::openSerialConfig(QVector<QString> *para)
{
    serial_port->setPortName(para->at(0));
    for(int i = 0;i<5;i++)
    {
        //qDebug() << para->at(i);
    }
    //set baud
    switch (para->at(1).toLong()) {
    case 1200:
        serial_port->setBaudRate(QSerialPort::Baud1200);
        break;
    case 2400:
        serial_port->setBaudRate(QSerialPort::Baud2400);
        break;
    case 4800:
        serial_port->setBaudRate(QSerialPort::Baud4800);
        break;
    case 9600:
        serial_port->setBaudRate(QSerialPort::Baud9600);
        break;
    case 19200:
        serial_port->setBaudRate(QSerialPort::Baud19200);
        break;
    case 38400:
        serial_port->setBaudRate(QSerialPort::Baud38400);
        break;
    case 57600:
        serial_port->setBaudRate(QSerialPort::Baud57600);
        break;
    case 115200:
        serial_port->setBaudRate(QSerialPort::Baud115200);
        break;
    default:
        serial_port->setBaudRate(QSerialPort::UnknownBaud);
        break;
    }
    //set databit
    switch (para->at(2).toInt()) {
    case 5:
        serial_port->setDataBits(QSerialPort::Data5);
        break;
    case 6:
        serial_port->setDataBits(QSerialPort::Data6);
        break;
    case 7:
        serial_port->setDataBits(QSerialPort::Data7);
        break;
    case 8:
        serial_port->setDataBits(QSerialPort::Data8);
        break;
    default:
        serial_port->setDataBits(QSerialPort::UnknownDataBits);
        break;
    }
    //set parity
    switch (0) {
    case 0:
        serial_port->setParity(QSerialPort::NoParity);
        break;
    case 2:
        serial_port->setParity(QSerialPort::EvenParity);
        break;
    case 3:
        serial_port->setParity(QSerialPort::OddParity);
        break;
    case 4:
        serial_port->setParity(QSerialPort::SpaceParity);
        break;
    case 5:
        serial_port->setParity(QSerialPort::MarkParity);
        break;
    default:
        serial_port->setParity(QSerialPort::UnknownParity);
        break;
    }
    //set stopbit
    switch (para->at(4).toInt()) {
    case 1:
        serial_port->setStopBits(QSerialPort::OneStop);
        break;
    case 3:
        serial_port->setStopBits(QSerialPort::OneAndHalfStop);
        break;
    case 2:
        serial_port->setStopBits(QSerialPort::TwoStop);
        break;
    default:
        serial_port->setStopBits(QSerialPort::UnknownStopBits);
        break;
    }

    serial_port->setFlowControl(QSerialPort::NoFlowControl);
    serial_port->setReadBufferSize(1024);
}

bool SerialTool::openSerial(QVector<QString> *para)
{
    if(serial_port->isOpen())
        return true;
    openSerialConfig(para);

    return serial_port->open(QSerialPort::ReadWrite);
}

void SerialTool::closeSerial()
{
    if(serial_port->isOpen())
        serial_port->close();
}

void SerialTool::searchSerial()
{
    QList<QSerialPortInfo> lists= serial_port_info->availablePorts();
    //qDebug() << "SerialList:" + lists.count();
    if(lists.count() == 0)
    {
        serial_name_vector.clear();
        string_lastSerialport.clear();
        string_serialport.clear();
    }
    for(int i = 0;i<lists.count();i++)
    {
        string_serialport.clear();
        //qDebug() << lists.at(i).portName();
        string_serialport.append(lists.at(i).portName());
        if(string_serialport == "\n")
        {
            continue;
        }
        //qDebug() << string_serialport + " " + string_lastSerialport;

        if(string_serialport == string_lastSerialport)
        {
            //qDebug() << serial_name_vector.at(0);
            //qDebug() << "12344";
            continue;
        }
        string_lastSerialport = string_serialport;
        serial_name_vector.append(string_serialport);
    }
}
QVector<QString> SerialTool::getSerialName()
{
    return serial_name_vector;
}

QSerialPort *SerialTool::getCurrentOpenSerial()
{
    return serial_port;
}

bool SerialTool::isOpen()
{
    return serial_port->isOpen();
}

