#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QPicture>
#include <QPixmap>
#include <QByteArray>
#include <QScrollBar>
#include <QTextCodec>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/image/orange.png"));
    this->setWindowTitle("Orange Tool");

    serialTool = new SerialTool();

    timer = new QTimer(this);
    codec = QTextCodec::codecForName("GB18030");

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
}

void MainWindow::serialConfig()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(searchAndShowResult()));
    timer->start(500);

    connect(serialTool->getCurrentOpenSerial(),SIGNAL(readyRead()),this,SLOT(display()));
}

void MainWindow::uiDataUpdata()
{
    //Serial Set parameter
    serialTool->serialName = ui->comboBox_serial->currentText();
    serialTool->serialBaud = ui->comboBox_baudRate->currentText();
    serialTool->serialDataBit = ui->comboBox_dataBit->currentText();
    serialTool->serialCheckBit = ui->comboBox_checkBit->currentText();
    serialTool->serialStopBit = ui->comboBox_stopBit->currentText();
    serialTool->serialFlowBit = ui->comboBox_flowBit->currentText();
    //Receive Set parameter
    serialTool->displayForm = ui->radioButtonR_ASCII->isChecked();
    serialTool->receiveAutoNewlineFlag = ui->checkBox_auto_newlineReceiver->isChecked();
    serialTool->showSendContentFlag = ui->checkBox_show_send->isChecked();
    serialTool->showInfoTimeFlag = ui->checkBox_show_time->isChecked();
    //Send Set parameter
    serialTool->sendForm = ui->radioButtonS_ASCII->isChecked();
    serialTool->sendAutoNewlineFlag = ui->checkBox_auto_newlineSender->isChecked();
    serialTool->repeatSendFlag = ui->checkBox_repeat->isChecked();
    serialTool->repeatSendmS = ui->spinBox_time->value();
}

void MainWindow::on_pushButton_open_clicked()
{
    uiDataUpdata();
    if(ui->pushButton_open->text() == "打开")
    {
        if(ui->comboBox_serial->currentText() == "Default")
        {
            return;
        }
        if(serialTool->openSerial())
        {
            ui->pushButton_open->setText("关闭");
        }
    }
    else if(ui->pushButton_open->text() == "关闭")
    {
        serialTool->closeSerial();
        ui->pushButton_open->setText("打开");
    }
}

void MainWindow::display()
{
    QListWidgetItem *itemReceiver;
    QByteArray arraySerial = serialTool->getCurrentOpenSerial()->readAll();
    if(ui->radioButtonR_ASCII->isChecked())
    {
        itemReceiver = new QListWidgetItem(codec->toUnicode(arraySerial));
    }
    else
    {
        itemReceiver = new QListWidgetItem(arraySerial.toHex());
    }
    ui->listWidget_display->addItem(itemReceiver);

    ui->listWidget_display->verticalScrollBar()
            ->setMaximum(ui->listWidget_display->verticalScrollBar()->maximum()+1);
    ui->listWidget_display->verticalScrollBar()
            ->setValue(ui->listWidget_display->verticalScrollBar()->maximum());
}

void MainWindow::searchAndShowResult()
{
    serialTool->searchSerial();
    qDebug() << serialTool->checkPullSerial(serialTool->getCurrentOpenSerial()->portName());
    if(!serialTool->checkPullSerial(
                serialTool->getCurrentOpenSerial()->portName()))
    {
        if(serialTool->isOpen())
        {
        return;
        }
    }
    if(serialTool->getSerialName().size() > 0)
    {
        showSerialResult();
    }
    else
    {
        ui->comboBox_serial->clear();
        ui->comboBox_serial->addItem("Default");
        ui->pushButton_open->setText("打开");
        return;
    }
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
    ui->comboBox_serial->clear();
    for(int i = 0;i < serialTool->getSerialName().size();i++)
    {
        ui->comboBox_serial->addItem(serialTool->getSerialName().at(i));
    }
}

void MainWindow::on_pushButton_clear_dispaly_clicked()
{
    ui->listWidget_display->clear();
}

void MainWindow::on_pushButton_send_clicked()
{
    QListWidgetItem *itemSender;
    //qDebug() << QByteArray().append(ui->textEdit_input->toPlainText()).toHex();
    if(serialTool->isOpen())
    {
        if(ui->checkBox_auto_newlineSender->isChecked())
        {
            serialTool->getCurrentOpenSerial()
                    ->write(QByteArray((ui->textEdit_input->toPlainText()+"\n").toLatin1()));
        }
        else
        {
            serialTool->getCurrentOpenSerial()
                    ->write(QByteArray(ui->textEdit_input->toPlainText().toLatin1()));
        }

        if(ui->checkBox_show_send->isChecked())
        {
            itemSender = new QListWidgetItem(ui->textEdit_input->toPlainText());
            itemSender->setTextColor(QColor(241,90,122));
            ui->listWidget_display->addItem(itemSender);
        }

        if(ui->checkBox_repeat->isChecked())
        {
            timerRepeat = new QTimer(this);
            connect(timerRepeat,SIGNAL(timeout()),this,SLOT(repeatSend()));
            //qDebug() << ui->spinBox_time->value();
            timerRepeat->start(ui->spinBox_time->value());
        }
    }
}

void MainWindow::repeatSend()
{
    serialTool->getCurrentOpenSerial()
            ->write(ui->textEdit_input->toPlainText().toLatin1());
    qDebug() << ui->textEdit_input->toPlainText();
}
