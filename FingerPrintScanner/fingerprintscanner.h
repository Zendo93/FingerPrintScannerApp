#ifndef FINGERPRINTSCANNER_H
#define FINGERPRINTSCANNER_H

#include <QString>
#include <QByteArray>
#include <QBuffer>
#include "fxISOdll.h"
#include "fxISOAFIS.h"
#include "fxISOenrdlg.h"
#include "fxISO_Interchange.h"

class FingerPrintScanner
{

public:
    FingerPrintScanner();
    QString FingerPrintScanner::openFileChooser();
    char *FingerPrintScanner::convertQStringtoCharPointer(QString pathTotFolder);
    char *FingerPrintScanner::incrementFileName(QString pathTotFolder, int i);
    void FingerPrintScanner::inicializeScanner();
    int FingerPrintScanner::runTheScanner();
    int FingerPrintScanner::saveCapturedFinger(char *path);
    int FingerPrintScanner::saveCapturedFingerIntoBuffer();
    unsigned char *FingerPrintScanner::getBuffer();
    void FingerPrintScanner::deinicializeScanner();

private:
    FxBuffer gImage;
    BYTE *buffer;
    float imageQuality;
    char * afterConversionChar;
    int err;
};


#endif // FINGERPRINTSCANNER_H
