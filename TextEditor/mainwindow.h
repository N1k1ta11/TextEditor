#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTranslator>

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
    void on_buttonSave_clicked();


    void on_buttonOpen_clicked();

    void on_buttonRef_clicked();

    void on_buttonOnlyRead_clicked();

    //void on_languages_currentTextChanged(const QString &arg1);

    void on_languages_textActivated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QString path = "";
    QTranslator translator;

    bool readOnly = false;
};
#endif // MAINWINDOW_H
