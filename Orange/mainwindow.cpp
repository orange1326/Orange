#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QPicture>
#include <QPixmap>
#include <QByteArray>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/image/orange.png"));
    this->setWindowTitle("Orange Tool");

    serialTool = new SerialTool();
    timer = new QTimer(this);
    timer2 = new QTimer(this);


    menuBarConfig();
    toolBarConfig();
    serialConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::menuBarConfig()
{
    connect(ui->action_A,SIGNAL(triggered(bool)),this,SLOT(showAboutDialog()));
}

void MainWindow::toolBarConfig()
{
    QLabel *label_status3 = new QLabel("no serial");
    QLabel *label_status = new QLabel("TX:");
    QLabel *label_status2 = new QLabel("RX:");
    statusBar()->addWidget(label_status3);
    statusBar()->addWidget(label_status);
    statusBar()->addWidget(label_status2);
}

void MainWindow::serialConfig()
{
    connect(timer,SIGNAL(timeout()),serialTool,SLOT(searchSerial()));
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(showSerialResult()));
    timer2->start(1000);

    connect(serialTool->getCurrentOpenSerial(),SIGNAL(readyRead()),this,SLOT(display()));
}

void MainWindow::on_pushButton_open_clicked()
{
    if(ui->pushButton_open->text() == "打开")
    {
        if(ui->comboBox_serial->currentText() == "Default")
        {
            return;
        }
        QVector<QString> *parameter = new QVector<QString>;
        parameter->append(ui->comboBox_serial->currentText());
        parameter->append(ui->comboBox_baudRate->currentText());
        parameter->append(ui->comboBox_dataBit->currentText());
        parameter->append(ui->comboBox_checkBit->currentText());
        parameter->append(ui->comboBox_stopBit->currentText());
        serialTool->openSerial(parameter);
        qDebug() << "open serial";
    }
    else
    if(ui->pushButton_open->text() == "关闭")
    {
        serialTool->closeSerial();
        ui->pushButton_open->setText("打开");
    }
}

void MainWindow::display()
{
    QListWidgetItem *item;
    QByteArray arraySerial = serialTool->getCurrentOpenSerial()->readAll();
    if(ui->radioButton2_ASCII->isChecked())
    {
        item = new QListWidgetItem(arraySerial);
    }
    else
    {
        item = new QListWidgetItem(arraySerial.toHex());
    }
    //qDebug() << "list " << ui->listWidget_display->count();
    ui->listWidget_display->verticalScrollBar()->setValue(ui->listWidget_display->count()+1);
    //qDebug() << "bar " << ui->listWidget_display->verticalScrollBar()->value();
    ui->listWidget_display->addItem(item);
}

void MainWindow::setCurrentRow(int row)
{
    qDebug() << row << endl;
}

void MainWindow::showAboutDialog()
{
    QMessageBox *box = new QMessageBox();

    box->setWindowIcon(QIcon(":/image/orange.png"));
    box->setWindowTitle("About");
    box->setInformativeText("Version:1.0.0");
    box->show();
}

void MainWindow::showSerialResult()
{
    int serialCount = serialTool->getSerialName().size();
    //qDebug() << serialCount;
    //qDebug() << serialTool->isOpen();
    if(serialTool->isOpen())
    {
        ui->pushButton_open->setText("关闭");
        ui->label_pic->setPixmap(QPixmap(":/image/orange.png"));
    }
    if(serialCount == 0)
    {
        ui->comboBox_serial->clear();
        ui->comboBox_serial->addItem("Default");
        return;
    }
    for(int i = 0;i < serialCount;i++)
    {
        if(ui->comboBox_serial->currentText() == "Default")
        {
            ui->comboBox_serial->removeItem(0);
        }
        if(serialTool->getSerialName().at(0) == ui->comboBox_serial->currentText())
        {
            return;
        }
        ui->comboBox_serial->addItem(serialTool->getSerialName().at(0));
    }
}

void MainWindow::on_pushButton_clear_dispaly_clicked()
{
    ui->listWidget_display->clear();
}

void MainWindow::on_pushButton_send_clicked()
{
    if(serialTool->isOpen())
    {
        serialTool->getCurrentOpenSerial()->write(QByteArray(ui->textEdit_input->toPlainText().toLatin1()));
        qDebug() << ui->textEdit_input->toPlainText();
    }
}

void MainWindow::on_radioButton2_ASCII_clicked()
{

}
