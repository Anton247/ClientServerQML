#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "TcpServer.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
      &app, []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection);

  TcpServer tcpServer;

  engine.rootContext()->setContextProperty("server", &tcpServer);
  engine.loadFromModule("Server", "Main");

  return app.exec();
}
