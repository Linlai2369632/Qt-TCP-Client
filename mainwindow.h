#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "client.h"
#include "chat.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    client *myClient;
    Chat *myChat;

private slots:
    void on_pbConnect_clicked();

    bool init();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
