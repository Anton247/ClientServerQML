#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QHash>
#include <QTcpSocket>

class TcpServer : public QObject
{
  Q_OBJECT
  public:
    explicit TcpServer(QObject *parent = nullptr);

  signals:
    void newMessage(const QByteArray &message);

  public slots:
    void sendMessage(const QString &message);


  private slots:
    void onNewConnection();
    void onReadyRead();
    void onNewMessage(const QByteArray &ba);
    void onDisconnected();

  private:
    QTcpServer _server;
    QHash<QString, QTcpSocket*> _clients;

    QString getClientKey(const QTcpSocket *client) const;


};

#endif // TCPSERVER_H
