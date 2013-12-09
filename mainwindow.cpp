#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->comboBox_Port->addItem(info.portName);

    ui->comboBox_Rate->addItem("9600", BAUD9600);
    ui->comboBox_Rate->addItem("1200", BAUD1200);
    ui->comboBox_Rate->addItem("2400", BAUD2400);
    ui->comboBox_Rate->addItem("4800", BAUD4800);
    ui->comboBox_Rate->addItem("19200", BAUD19200);

    settings = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};

    myport = new QextSerialPort(ui->comboBox_Port->currentText(), settings, QextSerialPort::Polling);

    timer = new QTimer(this);
    timer->setInterval(10);

    connect(ui->Button_Exit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->Button_Send, SIGNAL(clicked()), this, SLOT(Button_Send_Pressed()));
    connect(ui->Button_Connect, SIGNAL(clicked()), this, SLOT(Button_Connect_Pressed()));
    connect(myport, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
    connect(timer, SIGNAL(timeout()), this, SLOT(ReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
//    if(myport->isOpen()) myport->close();
    delete myport;
}

void MainWindow::Button_Send_Pressed()
{
    if (myport->isOpen() && !ui->plainTextEdit_Send->toPlainText().isEmpty())
        myport->write(ui->plainTextEdit_Send->toPlainText().toLatin1());
}

void MainWindow::Button_Connect_Pressed()
{
    if(!myport->isOpen())
    {
        ui->comboBox_Port->setEnabled(false);
        ui->comboBox_Rate->setEnabled(false);
        myport->setPortName(ui->comboBox_Port->currentText());
        myport->setBaudRate((BaudRateType)ui->comboBox_Rate->currentText().toInt());
        if(!myport->open(QIODevice::ReadWrite))
        {
           QMessageBox *pmb=new QMessageBox (QMessageBox::Warning,tr("Error"), tr("Unable to open port!"), QMessageBox::Ok);
           pmb->exec();
           delete pmb;
           ui->comboBox_Port->setEnabled(true);
           ui->comboBox_Rate->setEnabled(true);
        }
        else ui->Button_Connect->setText("Disconnect");
        timer->start();
    }
    else
    {
        myport->close();
        timer->stop();
        ui->comboBox_Port->setEnabled(true);
        ui->comboBox_Rate->setEnabled(true);
        ui->Button_Connect->setText("Connect");
    }
}

void MainWindow::ReadyRead()
{
    if (myport->bytesAvailable())
    {
        ui->plainTextEdit_Get->moveCursor(QTextCursor::End);
        ui->plainTextEdit_Get->insertPlainText(QString::fromLatin1(myport->readLine()));
    }
}
