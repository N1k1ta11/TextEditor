#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTranslator>
#include <QShortcut>
#include <QSharedPointer>
#include <QMdiArea>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_save();
    void on_open();
    void on_ref();
    void on_onlyRead();
    void on_createDocument();
    void on_changeLanguages(const QString&);
    void on_changeTheme(const QString&);
    void on_print();

private:
    Ui::MainWindow *ui;
    QTranslator translator;
    QMdiArea* area;
    QKeySequence* keySave, *keyOpen, *keyCreate, *keyPrint, *keyExit;

    void defaultStyleSheet();

    qint32 indexDoc = 0;
};
#endif // MAINWINDOW_H
