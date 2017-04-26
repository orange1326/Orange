#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialtool.h"
#include "sockettool.h"
#include <QPushButton>
#include <QTimer>
#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <qdebug.h>
#include <QPicture>
#include <QPixmap>
#include <QByteArray>
#include <QScrollBar>
#include <QTextCodec>
#include <QPalette>
#include <QCloseEvent>
#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
    void saveInfo();
    void recoverInfo();

    SerialTool *serialTool;
    QTimer *timer;
    QTimer *timerRepeat;
    QTextCodec *codec;

    //Serial Data
    QString receiverContent;
    QString sendContent;

    QListWidgetItem *itemReceiver;
    QListWidgetItem *itemSender;

    bool showSendFlag;
    //toolBar ui
    QLabel *lab_status;
    QLabel *lab_RX;
    QLabel *lab_TX;
    int RX_bytes;
    int TX_bytes;
    enum StatusFlag{OPEN,CLOSE,DEFAULT};
    void updateToolBar(StatusFlag flag);

    void toolBarConfig();
    void serialConfig();
    void menuBarConfig();
    void customFunConfig();
    void uiDataUpdata();
private slots:
    void on_pushButton_open_clicked();
    void on_pushButton_clear_dispaly_clicked();
    void on_pushButton_send_clicked();

    void display();
    void readMessage();
    void searchAndShowResult();
    void showAboutDialog();
    void showSerialResult();
    void repeatSend();
    void on_action_S_2_triggered();
    void on_actionTCP_IP_T_triggered();
signals:
    void showConent();
};

#endif // MAINWINDOW_H
