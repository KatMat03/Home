#include "MyTCPServer.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QRegularExpression>

MyTCPServer::MyTCPServer(int port, QObject *parent) : QObject{parent}
{
    _server = new QTcpServer(this);
    connect(_server, &QTcpServer::newConnection,
            this, &MyTCPServer::on_client_connecting);
    _isStarted = _server->listen(QHostAddress::Any, port);
    if(!_isStarted)
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started...";
    }
}

void MyTCPServer::on_client_connecting()
{
    qDebug() << "a client connected to serwer";
    auto socket = _server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &MyTCPServer::clientDataReady);
    connect(socket, &QTcpSocket::disconnected, this, &MyTCPServer::clientDisconnected);
    _socketsList.append(socket);
    socket->write("Weelcome to this Server");
    emit newClientConnected();
}
bool MyTCPServer::isStarted() const
{
    return _isStarted;
}
void MyTCPServer::sendToAll(QString message)
{
    foreach (auto socket, _socketsList)
    {
        socket->write(message.toUtf8());
    }
}
void MyTCPServer::clientDataReady()
{
    auto socket = qobject_cast<QTcpSocket *> (sender());
    auto data = QString(socket->readAll());
    emit dataReceived(data);
    foreach (auto s, _socketsList)
    {
        if (s != socket)
        {
          s->write(data.toUtf8());
        }
    }
}
void MyTCPServer::clientDisconnected()
{
    emit clientDisconnect();
}
