#include "TcpClient.h"

TcpClient::TcpClient(QObject *parent)
    : QObject{parent}
{
  connect(&_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
  connect(&_socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccured);
  connect(&_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}

void TcpClient::connectToHost(const QString &ip, const QString &port)
{
  _socket.connectToHost(ip, port.toUInt());
}

void TcpClient::sendMessage(const QString &message)
{
  _socket.write(message.toUtf8());
  _socket.flush();
}

void TcpClient::onConnected()
{
  qDebug() << "Connected to host";
}

void TcpClient::onErrorOccured(QAbstractSocket::SocketError error)
{
  qDebug() <<"Error:" << error;
}

void TcpClient::onReadyRead()
{
  const auto message = _socket.readAll();
  emit newMessage(message);
}
