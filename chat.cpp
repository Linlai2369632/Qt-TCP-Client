#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QTcpSocket *s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    setWindowTitle("聊天室");

    // 設置聊天室背景顏色為灰色
    QPalette palette;
    palette.setColor(QPalette::Base, Qt::lightGray);
    ui->teMessageBox->setPalette(palette);

    socket = s;
    connect(socket, &QTcpSocket::readyRead, this, &Chat::readSocket);
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_pbClear_clicked()
{
    ui->teMessageBox->clear();
}

void Chat::on_pbSend_clicked()
{
    QByteArray ba;
    ba.append(ui->teInput->toPlainText());
    socket->write(ba);
    ui->teInput->clear();
}

void Chat::on_pbDisconnect_clicked()
{
    socket->disconnectFromHost();
}

void Chat::readSocket()
{
    QByteArray ba = socket->readAll();
    if(!ba.isEmpty()) {
        ui->teMessageBox->append("-> " + QString(ba));
    }
}
