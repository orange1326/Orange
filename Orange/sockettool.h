#ifndef SOCKETTOOL_H
#define SOCKETTOOL_H

#include <QObject>
#include <QtNetwork/QUdpSocket>


class SocketTool : public QObject
{
    Q_OBJECT

public:
    SocketTool();
};

#endif // SOCKETTOOL_H
