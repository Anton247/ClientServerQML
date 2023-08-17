#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "TcpClient.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
      &app, []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection);

  TcpClient client;

  engine.rootContext()->setContextProperty("client", &client);

  engine.loadFromModule("Client", "Main");

  return app.exec();
}
