#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Client");

    myClient = nullptr;
    myChat = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::init() {
    if(ui->leHostAddress->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "主機IP不可為空");
        return false;
    }
    if(ui->leHostPort->text().isEmpty()) {
        QMessageBox::warning(this, "警告", "主機Port不可為空");
        return false;
    }

    qDebug() << "Host Address: " << ui->leHostAddress->text();
    qDebug() << "Host Port: " << ui->leHostPort->text();
    return true;
}

void MainWindow::on_pbConnect_clicked()
{
    if(!init())
        return;
    ui->pbConnect->setEnabled(false);

    // 如果 myClient 尚未建立，則建立它
    if (!myClient) {
        myClient = new client(ui->leHostAddress->text(), ui->leHostPort->text());
        // 連接信號與槽，跳到聊天介面
        connect(myClient, &client::connectionStatus, [this](bool isConnected){
            if (isConnected) {
                this->hide();
                myChat = new Chat(myClient->socket);
                myChat->show();
            }
            else {
                // 如果連線失敗，清理 myChat 物件並且顯示主視窗
                if (myChat) {
                    myChat->hide();
                    delete myChat;
                    myChat = nullptr;
                }
                this->show();
                delete myClient;
                myClient = nullptr;
                ui->pbConnect->setEnabled(true);
            }
        });
    }
}
