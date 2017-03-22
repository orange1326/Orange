#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/image/orange.png"));
    this->setWindowTitle("Orange Tool");

    toolBarConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::toolBarConfig()
{
    QLabel *label_status = new QLabel("");
    statusBar()->addWidget(new QLabel("Tx"));
}
