#include "sockettool.h"

SocketTool::SocketTool()
{
    QUdpSocket *sender;
    sender = new QUdpSocket();

    QHostAddress serverAddress = QHostAddress("192.168.191.2");

    QByteArray datagram = "hello world!";
    qDebug() << "asas";
    sender->writeDatagram(datagram.data(),datagram.size(),serverAddress,45454);
    /*
    qint64 writeDatagram(const char *data,qint64 size,const QHostAddress &address,quint16 port);
    qint64 writeDatagram(const QByteArray &datagram,const QHostAddress &host,quint16 port);
    */
}
