#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedMemory>
#include "FingerPrintScanner/fingerprintscanner.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_fingerPrintScannerButton_clicked();

    void on_QShared_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSharedMemory *sharedMemory;
private:
    void detach();
};

#endif // MAINWINDOW_H
