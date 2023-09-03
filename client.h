#ifndef CLIENT_H
#define CLIENT_H

#include "QTcpSocket"
#include <QWidget>
#include <QMessageBox>
#include <QHostAddress>
#include <QObject>

class client : public QTcpSocket
{
    Q_OBJECT
public:
    client(QString address, QString port);
    QTcpSocket *socket;

    void connect2Host();
public:
    explicit client(QWidget *parent = nullptr);
    ~client();

private:
    QString address;

    QString port;

signals:
    void connectionStatus(bool connected);
};

#endif // CLIENT_H
