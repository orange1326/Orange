#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/image/orange.png"));
    this->setWindowTitle("Orange Tool");

    serialTool = new SerialTool();
    timer = new QTimer(this);


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
MainWindow::toolBarConfig()
{
    QLabel *label_status = new QLabel("");
    statusBar()->addWidget(new QLabel("Tx"));
}

void MainWindow::serialConfig()
{
    connect(timer,SIGNAL(timeout()),this,SLOT(display()));
    timer->start(1000);

    connect(serialTool->getCurrentOpenSerial(),SIGNAL(readyRead()),this,SLOT(display()));
}

void MainWindow::on_pushButton_open_clicked()
{
    if(ui->comboBox_serial->currentText() == "Default")
    {
        return;
    }
    QVector<QString> *parameter = new QVector<QString>;
    parameter->append(ui->comboBox_serial->currentText());
    parameter->append(ui->comboBox_baudRate->currentText());
    parameter->append(ui->comboBox_checkBit->currentText());
    parameter->append(ui->comboBox_dataBit->currentText());
    parameter->append(ui->comboBox_stopBit->currentText());
    serialTool->openSerial(parameter);
}

void MainWindow::display()
{
    //QByteArray array = serialTool->getCurrentOpenSerial()->readAll();
    QListWidgetItem *item = new QListWidgetItem("HHH");
    //connect(ui->listWidget_display,SIGNAL(),this,SLOT(setCurrentRow(int)));
    ui->listWidget_display->setCurrentRow(ui->listWidget_display->count());
    qDebug() << ui->listWidget_display->count() << endl;
    qDebug() << ui->listWidget_display->currentRow() << endl;
    ui->listWidget_display->addItem(item);
}

void MainWindow::setCurrentRow(int row)
{
    qDebug() << sizeof(int) << endl;
}

void MainWindow::showAboutDialog()
{
    QMessageBox *box = new QMessageBox();

    box->setWindowIcon(QIcon(":/image/orange.png"));
    box->setWindowTitle("About");
    box->setInformativeText("Version:1.0.0");
    box->show();
}

void MainWindow::on_pushButton_clear_dispaly_clicked()
{
    ui->listWidget_display->clear();
}
