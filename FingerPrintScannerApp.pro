#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T13:59:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FingerPrintScannerApp
TEMPLATE = app
INCLUDEPATH += "C:\TeamProject\FingerPrintScannerApp\FingerPrintScanner"
CONFIG += console
SOURCES += main.cpp\
        mainwindow.cpp \
    FingerPrintScanner/fingerprintscanner.cpp

HEADERS  += mainwindow.h \
    FingerPrintScanner/fxISO_device.h \
    FingerPrintScanner/fxISO_engine.h \
    FingerPrintScanner/fxISO_Interchange.h \
    FingerPrintScanner/fxISOAFIS.h \
    FingerPrintScanner/fxISOdll.h \
    FingerPrintScanner/fxISOenrdlg.h \
    FingerPrintScanner/fingerprintscanner.h

FORMS    += mainwindow.ui

LIBS += "C:/TeamProject/FingerPrintScannerApp/FingerPrintScanner/lib/x64/fxISO_64.lib"
LIBS += "C:/TeamProject/FingerPrintScannerApp/FingerPrintScanner/lib/x64/fxISOenrdlg_64.lib"
LIBS += "C:/TeamProject/FingerPrintScannerApp/FingerPrintScanner/lib/x64/FingerPrintScannerDLL.lib"

win32-msvc*: QMAKE_LFLAGS += /DYNAMICBASE:NO
