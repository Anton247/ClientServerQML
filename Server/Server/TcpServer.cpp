#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent)
    : QObject{parent}
{
  connect(&_server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);
  connect(this, &TcpServer::newMessage, this, &TcpServer::onNewMessage);
  if(_server.listen(QHostAddress::Any, 45000)){
    qDebug()<<"listerning...";
  }

}

void TcpServer::sendMessage(const QString &message)
{
  emit newMessage(message.toUtf8());
}

void TcpServer::onNewConnection()
{
  const auto client = _server.nextPendingConnection();
  if(client == nullptr){
    return;
  }

  qDebug()<<"New client connected";

  _clients.insert(this->getClientKey(client), client);

  connect(client, &QTcpSocket::readyRead, this, &TcpServer::onReadyRead);
  connect(client, &QTcpSocket::disconnected, this, &TcpServer::onDisconnected);
}

void TcpServer::onReadyRead()
{
  const auto client = qobject_cast<QTcpSocket*>(sender());
  if(client == nullptr)
    return;

  const auto message = this->getClientKey(client).toUtf8() + ": " + client->readAll();

  emit newMessage(message);
}

void TcpServer::onNewMessage(const QByteArray &ba)
{
  for(const auto &client : _clients){
    client->write(ba);
    client->flush();
  }
}

void TcpServer::onDisconnected()
{
  const auto client = qobject_cast<QTcpSocket*>(sender());
  if(client == nullptr)
    return;

  _clients.remove(this->getClientKey(client));
}

QString TcpServer::getClientKey(const QTcpSocket *client) const
{
  return   client->peerAddress().toString().append(":").append(QString::number(client->peerPort()));
}
