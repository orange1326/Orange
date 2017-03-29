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
    void toolBarConfig();

    void serialConfig();
    
    void menuBarConfig();
private:
    Ui::MainWindow *ui;
    SerialTool *serialTool;
    QTimer *timer;
    QTimer *timer2;
    QTimer *timerRepeat;
    QTextCodec *codec;

private slots:
    void on_pushButton_open_clicked();
    void on_pushButton_clear_dispaly_clicked();
    void on_pushButton_send_clicked();
    void on_radioButton2_ASCII_clicked();

public slots:
    void display();
    void setCurrentRow(int row);
    void showAboutDialog();
    void showSerialResult();
    void repeatSend();
};

#endif // MAINWINDOW_H
