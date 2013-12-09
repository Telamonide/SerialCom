#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QString>
#include <cstring>
#include "qextserialport.h"
#include "qextserialenumerator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QextSerialPort *myport;

public slots:
    void Button_Send_Pressed();
    void Button_Connect_Pressed();
    void ReadyRead();
    
private:
    Ui::MainWindow *ui;
    PortSettings settings;
    QTimer *timer;
};

#endif // MAINWINDOW_H
