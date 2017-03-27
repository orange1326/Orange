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
    toolBarConfig();

    void serialConfig();
    
    void menuBarConfig();

private:
    Ui::MainWindow *ui;
    SerialTool *serialTool;
    QTimer *timer;

private slots:
    void on_pushButton_open_clicked();
    void on_pushButton_clear_dispaly_clicked();

public slots:
    void display();
    void setCurrentRow(int row);
    void showAboutDialog();
};

#endif // MAINWINDOW_H
