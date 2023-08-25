#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QPushButton>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* wgt = new QWidget(this);
    setCentralWidget(wgt);
    area = new QMdiArea(this);
    setCentralWidget(wgt);
    area->setViewMode(QMdiArea::TabbedView);
    QHBoxLayout* layout = new QHBoxLayout(wgt);
    wgt->setLayout(layout);
    layout->addWidget(area);

    defaultStyleSheet();

    keySave = new QKeySequence(QKeySequence::Save);
    keyOpen = new QKeySequence(QKeySequence::Open);
    keyCreate = new QKeySequence(QKeySequence::New);
    keyPrint = new QKeySequence(QKeySequence::Print);
    keyExit = new QKeySequence(Qt::CTRL | Qt::Key_Q);

    QMenu* fileMenu = menuBar()->addMenu(tr("File"));

    QAction* saveAction = fileMenu->addAction(tr("Save"));
    saveAction->setShortcut(*keySave);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(on_save()));

    QAction* openAction = fileMenu->addAction(tr("Open"));
    openAction->setShortcut(*keyOpen);
    connect(openAction, SIGNAL(triggered()), this, SLOT(on_open()));

    QAction* openOnlyReadAction = fileMenu->addAction(tr("Open only read"));
    connect(openOnlyReadAction, SIGNAL(triggered()), this, SLOT(on_onlyRead()));

    QAction* createDocAction = fileMenu->addAction(tr("Create"));
    createDocAction->setShortcut(*keyCreate);
    connect(createDocAction, SIGNAL(triggered()), this, SLOT(on_createDocument()));

    QAction* printAction = fileMenu->addAction(tr("Print"));
    printAction->setShortcut(*keyPrint);
    connect(printAction, SIGNAL(triggered()), this, SLOT(on_print()));

    fileMenu->addSeparator();

    QAction* exitAction = fileMenu->addAction(tr("Exit"));
    exitAction->setShortcut(*keyExit);
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_save()
{
    QString path = area->currentSubWindow()->windowTitle();
    if(path.indexOf("qnew_doc")){
        path = QFileDialog::getSaveFileName();
        if(path == ""){
            return;
        }
        area->currentSubWindow()->setWindowTitle(path);
    }

    if(area->currentSubWindow() == nullptr){
        return;
    }

    QTextEdit* textEdit = dynamic_cast<QTextEdit*>(area->currentSubWindow()->widget());

    if(textEdit == nullptr){
        return;
    }

    QFile file(path);
    if(file.open(QIODevice::WriteOnly)){
        QString txt = textEdit->toPlainText();
        QByteArray array = txt.toUtf8();
        file.write(array);
    }
}

void MainWindow::on_open()
{
    QString path = QFileDialog::getOpenFileName();
    if(path==""){
        return;
    }

    QTextEdit* textEdit = new QTextEdit();
    QMdiSubWindow* window = area->addSubWindow(textEdit);
    window->setWindowTitle(path);

    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray array = file.readAll();
        QString txt(array);
        textEdit->setText(txt);
    }
}

void MainWindow::on_ref()
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


void MainWindow::on_onlyRead()
{
    QString path = QFileDialog::getOpenFileName();
    if(path == ""){
        return;
    }

    QTextEdit* textEdit = new QTextEdit();
    QMdiSubWindow* window = area->addSubWindow(textEdit);
    window->setWindowTitle(path);

    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray array = file.readAll();
        QString txt(array);
        textEdit->setText(txt);
        textEdit->setReadOnly(true);
    }
}

void MainWindow::on_changeLanguages(const QString &arg1)
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

void MainWindow::on_createDocument()
{    
    QMdiSubWindow* newWindow = area->addSubWindow(new QTextEdit());
    newWindow->setWindowTitle("qnew_doc");
    newWindow->show();
}

void MainWindow::defaultStyleSheet()
{
    setStyleSheet("QPushButton { background-color: white;"
                  "color: black; }"
                  "QMainWindow { background-color: white; }"
                  "QTextEdit { color: black; "
                  "background-color: white  }");
}

void MainWindow::on_changeTheme(const QString &arg1)
{
    if(arg1 == "Light theme"){
        defaultStyleSheet();
    } else{
        setStyleSheet("QPushButton { background-color: black;"
                      "color: white; }"
                      "QMainWindow { background-color: black; }"
                      "QTextEdit {color: white; "
                      "background-color: black}");
    }
}

void MainWindow::on_print()
{
    QMdiSubWindow* window = area->currentSubWindow();
    QTextEdit* textEdit = dynamic_cast<QTextEdit*>(window->widget());
    QPrinter printer;
    QPrintDialog dlg(&printer, this);

    if(dlg.exec() != QDialog::Accepted){
        return;
    }
    textEdit->print(&printer);
}
