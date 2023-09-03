#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QTcpSocket>
#include <QPalette>

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QTcpSocket *s, QWidget *parent = nullptr);
    ~Chat();

private slots:
    void on_pbClear_clicked();

    void on_pbSend_clicked();

    void on_pbDisconnect_clicked();

    void readSocket();

private:
    Ui::Chat *ui;
    QTcpSocket *socket;
};

#endif // CHAT_H
