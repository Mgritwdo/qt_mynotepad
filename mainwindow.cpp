#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //绑定信号
    connect(ui->newAction,&QAction::triggered,this,&MainWindow::newActionSlot);
    connect(ui->openAction,&QAction::triggered,this,&MainWindow::openActionSlot);
    connect(ui->action_S,&QAction::triggered,this,&MainWindow::saveActionSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newActionSlot()
{
    //清空文本框
    ui->textEdit->clear();

    //更改标题框
    this->setWindowTitle("新建文本文档.txt");
}

void MainWindow::openActionSlot()
{
    QString filestr = QFileDialog::getOpenFileName(this,"请选择一个文件",QCoreApplication::applicationFilePath(),"*.txt");
//    qDebug() << filestr;

    QFile file(filestr);
    file.open(QIODevice::ReadOnly);
    QByteArray ba = file.readAll();
    ui->textEdit->setText(QString(ba));
}

void MainWindow::saveActionSlot()
{
    QString filestr = QFileDialog::getSaveFileName(this,"请选择一个文件",QCoreApplication::applicationFilePath());

    if( filestr.isEmpty())
    {

    }
    else
    {
        QFile file(filestr);
        file.open(QIODevice::WriteOnly);
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText());
        file.write(ba);
        file.close();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *k)
{
    if( k->modifiers() == Qt::ControlModifier && k->key() == Qt::Key_S )    //Ctrl+S同时被按下
    {
        this->saveActionSlot();
    }
}
