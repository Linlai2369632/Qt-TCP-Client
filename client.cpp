#include "client.h"
#include <qDebug>

client::client(QString add, QString p)
{
    this->address = add;
    this->port = p;

    connect2Host();
}

client::~client()
{

}

void client::connect2Host()
{
    socket = new QTcpSocket;

    connect(socket, &QTcpSocket::connected, [this]() {
        qDebug("連線伺服器成功");
        QWidget *widget = new QWidget();
        QMessageBox::information(widget, "連接提示", "連線伺服器成功");
        emit connectionStatus(true); // 連線成功時發射信號，用來通知主介面。
    });

    // 將 QAbstractSocket::error 信號與 lambda 函式連接
    connect(socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                [this](QAbstractSocket::SocketError socketError) {
        QWidget *widget = new QWidget();
        QString errorMessage;
        switch (socketError) {
            case QAbstractSocket::ConnectionRefusedError:
                errorMessage = "連線被拒絕，可能服務器未啟動或未在指定端口監聽。";
                break;
            case QAbstractSocket::HostNotFoundError:
                errorMessage = "找不到目標主機，請確認地址是否正確。";
                break;
            case QAbstractSocket::SocketAccessError:
                errorMessage = "對套接字的訪問被拒絕，可能缺少訪問權限。";
                break;
            default:
                errorMessage = "連線失敗，錯誤描述：" + socket->errorString();
                break;
        }
        qWarning() << errorMessage;
        QMessageBox::warning(widget, "連接警告", errorMessage);
        emit connectionStatus(false);
    });

    socket->connectToHost(QHostAddress(address), port.toShort());

    connect(socket, &QTcpSocket::disconnected, [this](){
        qDebug("連線伺服器失敗");
        QWidget *widget = new QWidget();
        QMessageBox::warning(widget, "連接警告", "與伺服器斷開連線" );
        emit connectionStatus(false); // 斷線時發射信號
    });
}
