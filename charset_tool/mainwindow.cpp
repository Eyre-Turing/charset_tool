#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_outputButton_clicked()
{
    QString input = ui->inputLineEdit->text();
    QString charset = ui->charsetLineEdit->text();
    QTextCodec *codec = QTextCodec::codecForName(charset.toUtf8());
    QByteArray byteArray = codec->fromUnicode(input);
    int len = byteArray.size();
    QString outputString = "";
    for(int i=0; i<len; ++i)
    {
        unsigned char a = byteArray[i];
        outputString.append("\\x"+QString::number(a, 16));
    }
    ui->outputLineEdit->setText(outputString);
}

void MainWindow::on_humanButton_clicked()
{
    QString input = ui->inputLineEdit->text();
    QString charset = ui->charsetLineEdit->text();
    QTextCodec *codec = QTextCodec::codecForName(charset.toUtf8());
    QStringList inputs = input.mid(1).split("\\");
    QByteArray byteArray;
    foreach(QString i, inputs)
    {
        if(i.length())
        {
            unsigned char a;
            if(i[0]=='x' || i[0]=='X')
            {
                a = i.mid(1).toInt(0, 16);
            }
            else
            {
                a = i.toInt(0, 16);
            }
            byteArray.append(a);
        }
        else
        {
            ui->outputLineEdit->setText("输入有问题");
            return ;
        }
    }
    QString output = codec->toUnicode(byteArray);
    ui->outputLineEdit->setText(output);
}
