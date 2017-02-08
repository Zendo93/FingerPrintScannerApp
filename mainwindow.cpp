#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QByteArray>
#include <QFileDialog>
#include "stdio.h"
#include "./FingerPrintScanner/fingerprintscanner.h"
#include "./FingerPrintScanner/fxISOdll.h"
#include "./FingerPrintScanner/fxISOenrdlg.h"
#include "./FingerPrintScanner/fxISOAFIS.h"
#include "./FingerPrintScanner/fxISO_Interchange.h"
#include <iostream>
using namespace std;
#pragma comment(lib,"user32.lib")
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sharedMemory = new QSharedMemory("QSharedMemory");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_fingerPrintScannerButton_clicked()
{

    int err;
    int i=0;
    FingerPrintScanner *scanner = new FingerPrintScanner();
    QString pathTofolder = scanner->openFileChooser();
    cout << pathTofolder.toStdString() << endl;
    if (pathTofolder.compare("") != 0)
    {
        char *path= scanner->convertQStringtoCharPointer(pathTofolder);
        cout << path <<endl;
        scanner->inicializeScanner();
        while(true)
        {
            i = i +1;
            err = scanner->runTheScanner();
            if (err)
            {
                scanner->deinicializeScanner();
                break;
            }
            path = scanner->incrementFileName(pathTofolder, i);
            cout << path <<endl;
            err = scanner->saveCapturedFinger(path);
            if (err)
            {
                scanner->deinicializeScanner();
                break;
            }
            MessageBox(NULL, L"Your fingerprint was succesfully saved", L"Result", MB_OK);
        }

        path = NULL;
        delete path;
    }
    scanner = NULL;
    delete scanner;

}


void MainWindow::on_QShared_pushButton_clicked()

{

    if (sharedMemory->isAttached())

    {
        sharedMemory->detach();

    }



    int err;

    // inicializacia a spustenie scannera
    FingerPrintScanner *scanner = new FingerPrintScanner();
    scanner->inicializeScanner();
    err = scanner->runTheScanner(); // tu sa zablokuje

    if (err)
    {
        scanner->deinicializeScanner();
        return;
    }



    if(scanner->saveCapturedFingerIntoBuffer() == FxISO_InvalidParameter){
      return;
    }


    int size = 250000;

    // vytvara sa novy pamatovy segment
    if (!sharedMemory->create(size)) {
        cout << "Unable to create shared memory segment." << endl;
        return;
    }

    // exkluzivny pristup procesu zdielanej pamate
    sharedMemory->lock();
        char *to = (char*)sharedMemory->data();
        const unsigned char *from = scanner->getBuffer();
        memcpy(to, from, qMin(sharedMemory->size(), size));
    sharedMemory->unlock();

    // koniec exkluzivneho pristupu
    scanner->deinicializeScanner();
    scanner = NULL;
    delete scanner;

}
