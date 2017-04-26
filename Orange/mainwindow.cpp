#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DEBUG 1

void myDebug(QString str)
{
    if(DEBUG)
    {
    qDebug() << str;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/image/orange.png"));
    this->setWindowTitle("Orange Tool");
    recoverInfo();
    serialTool = new SerialTool;
    SocketTool *tool = new SocketTool;

    timer = new QTimer(this);
    codec = QTextCodec::codecForName("GBK");

    menuBarConfig();
    toolBarConfig();
    serialConfig();
    customFunConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveInfo();
    event->accept();
}

void MainWindow::saveInfo()
{
    QFile file("info.cof");
    QByteArray array;
    array.append(QString::number(ui->radioButtonR_ASCII->isChecked()).append(","));
    array.append(QString::number(ui->checkBox_auto_newlineReceiver->isChecked()).append(","));
    array.append(QString::number(ui->checkBox_show_send->isChecked()).append(","));
    array.append(QString::number(ui->checkBox_show_time->isChecked()).append(","));

    array.append(QString::number(ui->radioButtonS_ASCII->isChecked()).append(","));
    array.append(QString::number(ui->checkBox_auto_newlineSender->isChecked()).append(","));
    array.append(QString::number(ui->checkBox_repeat->isChecked()).append(","));
    array.append(QString::number(ui->spinBox_time->value()));

    if(file.exists())
    {
        file.remove();
    }
    if(!file.open(QIODevice::ReadWrite))
    {
       // qDebug() << "Can't open current file!";
        return;
    }
    //qDebug() << "Write:" << array;
    file.write(array);
    file.close();
}

void MainWindow::recoverInfo()
{
    QFile file("info.cof");
    QByteArray array;
    if(!file.exists())
    {
        //qDebug() << "What's Fuck!";
        return;
    }
    if(!file.open(QIODevice::ReadWrite))
    {
        //qDebug() << "recover failed;";
    }
    array = file.readAll();
    //qDebug() << "Read:" << array;
    QList<QByteArray> list= array.split(',');
    ui->radioButtonR_ASCII->setChecked(list.at(0).toInt());
    ui->checkBox_auto_newlineReceiver->setChecked(list.at(1).toInt());
    ui->checkBox_show_send->setChecked(list.at(2).toInt());
    ui->checkBox_show_time->setChecked(list.at(3).toInt());

    ui->radioButtonS_ASCII->setChecked(list.at(4).toInt());
    ui->checkBox_auto_newlineSender->setChecked(list.at(5).toInt());
    ui->checkBox_repeat->setChecked(list.at(6).toInt());
    ui->spinBox_time->setValue(list.at(7).toInt());

    file.close();
}

void MainWindow::customFunConfig()
{
    connect(ui->pushButton_custom1, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_custom2, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_custom3, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_custom4, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_custom5, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_custom6, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_custom7, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_custom8, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_custom9, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_custom10,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->pushButton_custom11,SIGNAL(clicked()),this,SLOT(close()));
}

void MainWindow::menuBarConfig()
{
    connect(ui->action_A,SIGNAL(triggered(bool)),this,SLOT(showAboutDialog()));
}

void MainWindow::updateToolBar(StatusFlag flag)
{
    QPalette pa;
    QString status;
    status = serialTool->serialName+" is opened";
    lab_RX->setText(QString("RX:").append(QString::number(RX_bytes)).append(" Bytes"));
    lab_TX->setText(QString("TX:").append(QString::number(TX_bytes)).append(" Bytes"));
    switch (flag) {
    case OPEN:
        pa.setColor(QPalette::WindowText,Qt::green);
        lab_status->setPalette(pa);
        lab_status->setText(status);
        break;
    case CLOSE:
        pa.setColor(QPalette::WindowText,Qt::red);
        lab_status->setPalette(pa);
        lab_status->setText(ui->comboBox_serial->currentText().append(" is closed"));
        break;
    case DEFAULT:
        pa.setColor(QPalette::WindowText,Qt::black);
        lab_status->setPalette(pa);
        lab_status->setText("Serial Port not found");
        break;
    default:   
        break;
    }
}

void MainWindow::toolBarConfig()
{
    RX_bytes = 0;
    TX_bytes = 0;
    lab_status = new QLabel("Serial Port not found");
    lab_RX = new QLabel("RX:0 Bytes");
    lab_TX = new QLabel("TX:0 Bytes");

    ui->statusBar->addWidget(lab_status,5);
    ui->statusBar->addWidget(lab_RX,3);
    ui->statusBar->addWidget(lab_TX,3);
}

void MainWindow::serialConfig()
{
    showSendFlag = false;
    uiDataUpdata();
    connect(timer,SIGNAL(timeout()),this,SLOT(searchAndShowResult()));
    timer->start(500);

    connect(serialTool->getCurrentOpenSerial(),SIGNAL(readyRead()),
            this,SLOT(readMessage()));
    connect(this,SIGNAL(showConent()),this,SLOT(display()));
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
           // return;
        }
        if(serialTool->openSerial())
        {
            updateToolBar(OPEN);
            ui->pushButton_open->setText("关闭");
            ui->label_pic->setPixmap(QPixmap(":/image/orange.png").scaled(50,50));
        }
    }
    else if(ui->pushButton_open->text() == "关闭")
    {
        updateToolBar(CLOSE);
        serialTool->closeSerial();
        ui->label_pic->setPixmap(QPixmap(":/image/orange_noColor.png").scaled(50,50));
        ui->pushButton_open->setText("打开");
    }
}

void MainWindow::display()
{
    if(ui->checkBox_show_send->isChecked())
    {
        itemSender = new QListWidgetItem(sendContent);
        itemSender->setTextColor(QColor(241,90,122));
        ui->listWidget_display->addItem(itemSender);
    }
    if(!receiverContent.isEmpty())
    {
        itemReceiver = new QListWidgetItem(receiverContent);
        itemReceiver->setTextColor(QColor(21,213,90));
        ui->listWidget_display->addItem(itemReceiver);
        receiverContent.clear();
    }
    ui->listWidget_display->setCurrentRow(ui->listWidget_display->count()-1);
}

void MainWindow::readMessage()
{
    receiverContent = codec->toUnicode(serialTool->getCurrentOpenSerial()->readAll());
    if(ui->radioButtonR_HEX->isChecked())
    {
        receiverContent = receiverContent.toLatin1().toHex();
    }
    //qDebug() << "Content:" + receiverContent.size();
    if(receiverContent.count())
    {
        RX_bytes += receiverContent.size();
        emit showConent();
    }
}

void MainWindow::searchAndShowResult()
{
    serialTool->searchSerial();
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
        updateToolBar(CLOSE);
        showSerialResult();
    }
    else
    {
        updateToolBar(DEFAULT);
        ui->comboBox_serial->clear();
        ui->comboBox_serial->addItem("Default");
        ui->pushButton_open->setText("打开");
        return;
    }
}

void MainWindow::showAboutDialog()
{
    QMessageBox *box = new QMessageBox();
    box->setMinimumSize(350,1350);
    box->setMaximumSize(350,1350);
    box->setWindowIcon(QIcon(":/image/orange.png"));
    box->setWindowTitle("About");
    box->setIcon(QMessageBox::Information);
    box->setText(QString("Orange's Tool\n\n")
                 .append("Version:1.0.0\n")
                 .append("QQ:273142568\n")
                 .append("Email:273142568@qq.com\n")
                 .append("Copyright @ Orange's Studio"));
    box->setInformativeText("Provide fully customized software solutions.");
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
    sendContent = ui->textEdit_input->toPlainText();
    if(serialTool->isOpen())
    {
        if(ui->radioButtonS_HEX->isChecked())
        {
            sendContent = sendContent.toLatin1();
            //qDebug() << sendContent;
        }
        if(ui->checkBox_auto_newlineSender->isChecked())
        {
            sendContent.append("\n");
        }
        if(ui->checkBox_repeat->isChecked())
        {
            timerRepeat = new QTimer(this);
            connect(timerRepeat,SIGNAL(timeout()),this,SLOT(repeatSend()));
            timerRepeat->start(ui->spinBox_time->value());
        }
        TX_bytes += sendContent.size();
        updateToolBar(OPEN);
        serialTool->writeSerial(sendContent.toLatin1());
    }
}

void MainWindow::repeatSend()
{
    serialTool->writeSerial(ui->textEdit_input->toPlainText().toLatin1());
}

void MainWindow::on_action_S_2_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionTCP_IP_T_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}
