#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_pushButton_clicked()
{
    bool line1 = false,line2 = false,line3 = false;

    if(ui->lineEdit_2->text() != "")
    {
        line1 = true;
    }
    if(ui->lineEdit_3->text() != "")
    {
        line2 = true;
    }
    if(ui->lineEdit_4->text() != "")
    {
        line3 = true;
    }

    QFile *InputFile;
    QFile *OutputFile;
    QDir dir("D:/detech");
    if(!dir.exists())
    {
      dir.mkdir("D:/detech");
    }


    QByteArray Temp;
    int dark_file_num = 1;
    int light_file_num = 1;
    int wave_file_num = 1;
    QByteArray string1 = ui->lineEdit_2->text().toLocal8Bit();
    QByteArray string2 = ui->lineEdit_3->text().toLocal8Bit();
    QByteArray string3 = ui->lineEdit_4->text().toLocal8Bit();

    InputFile = new QFile(ui->lineEdit->text());
    OutputFile = new QFile(QObject::tr("%1").arg(dark_file_num));

    InputFile->open(QIODevice::ReadOnly | QIODevice::Text);
    OutputFile->open(QIODevice::WriteOnly | QIODevice::Text);

/********/
    while(!InputFile->atEnd())
    {
        Temp = InputFile->readLine();
        if(Temp.contains(string1) && line1 == true)
        {
            dark_file_num++;
            OutputFile->close();
            OutputFile = new QFile(QObject::tr("D:/detech/%1%2").arg(ui->lineEdit_2->text()).arg(dark_file_num));
            OutputFile->open(QIODevice::WriteOnly | QIODevice::Text);
        }
        if(Temp.contains(string2) && line2 == true)
        {
            light_file_num++;
            OutputFile->close();
            OutputFile = new QFile(QObject::tr("D:/detech/%1%2").arg(ui->lineEdit_3->text()).arg(light_file_num));
            OutputFile->open(QIODevice::WriteOnly | QIODevice::Text);
        }
        if(Temp.contains(string3) && line3 == true)
        {
            wave_file_num++;
            OutputFile->close();
            OutputFile = new QFile(QObject::tr("D:/detech/%1%2").arg(ui->lineEdit_4->text()).arg(wave_file_num));
            OutputFile->open(QIODevice::WriteOnly | QIODevice::Text);
        }
        OutputFile->write(Temp);
    }
/*****/

    InputFile->close();
    OutputFile->close();

    QMessageBox::information(0,"over","detech over");

    return;
}
