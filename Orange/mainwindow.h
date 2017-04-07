#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialtool.h"
#include <QPushButton>
#include <QTimer>
#include <QDialog>
#include <QMessageBox>

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
    SerialTool *serialTool;
    QTimer *timer;
    QTimer *timerRepeat;
    QTextCodec *codec;

    void toolBarConfig();
    void serialConfig();
    void menuBarConfig();
    void uiDataUpdata();
private slots:
    void on_pushButton_open_clicked();
    void on_pushButton_clear_dispaly_clicked();
    void on_pushButton_send_clicked();

    void display();
    void searchAndShowResult();
    void showAboutDialog();
    void showSerialResult();
    void repeatSend();
};

#endif // MAINWINDOW_H
