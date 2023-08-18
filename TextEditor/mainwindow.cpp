#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonSave_clicked()
{
    if(path==""){
        path = QFileDialog::getSaveFileName();
    }

    if(path == ""){
        return;
    }

    QFile file(path);
    if(file.open(QIODevice::WriteOnly)){
        QString txt = ui->textEdit->toPlainText();
        QByteArray array = txt.toUtf8();
        file.write(array);
    }
}



void MainWindow::on_buttonOpen_clicked()
{
    if(readOnly){
        readOnly = false;
        ui->textEdit->setReadOnly(readOnly);
    }

    path = QFileDialog::getOpenFileName();
    if(path==""){
        return;
    }

    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray array = file.readAll();
        QString txt(array);
        ui->textEdit->setText(txt);
    }
}


void MainWindow::on_buttonRef_clicked()
{
    QFile file(":/reference/ref.txt");
    if(file.open(QIODevice::ReadOnly)){
        QString txt = file.readAll();
        QMessageBox box(this);
        box.setWindowTitle(QString("Reference"));
        box.setText(txt);
        box.exec();
    }
}


void MainWindow::on_buttonOnlyRead_clicked()
{
    path = QFileDialog::getOpenFileName();
    if(path == ""){
        return;
    }

    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray array = file.readAll();
        QString txt(array);
        ui->textEdit->setText(txt);
        readOnly = true;
        ui->textEdit->setReadOnly(readOnly);
    }
}


//void MainWindow::on_languages_currentTextChanged(const QString &arg1)
//{
//    if(arg1 == "RUS"){
//        if(translator.load(":/translate/QtLanguage_ru.qm")){
//            qApp->installTranslator(&translator);
//            ui->retranslateUi(this);
//        }
//    }else{
//        if(translator.load(":/translate/QtLanguage_en.qm")){
//            qApp->installTranslator(&translator);
//            ui->retranslateUi(this);
//        }
//    }
//}


void MainWindow::on_languages_textActivated(const QString &arg1)
{
    if(arg1 == "RUS"){
        if(translator.load(":/translate/QtLanguage_ru.qm")){
            qApp->installTranslator(&translator);
            ui->retranslateUi(this);
        }
    }else{
        if(translator.load(":/translate/QtLanguage_en.qm")){
            qApp->installTranslator(&translator);
            ui->retranslateUi(this);
        }
    }
}

