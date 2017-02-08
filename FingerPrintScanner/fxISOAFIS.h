#ifndef __FXAFIS_H
#define __FXAFIS_H

#include "fxISOdll.h"

#ifdef __cplusplus
extern "C" {
#endif

// FxISO AFIS Interface

//---------- Scanner type ----------
#define SCANNERDEFAULT -1
#define DISPLAY_ONLY    0
#define SINGLEFINGER    1
#define SCANNER442      2
#define SCANNERPALM     3

//---------- Fingers type bitmask ----------
#ifndef THUMB_RIGHT_BITMASK 
#define THUMB_RIGHT_BITMASK  0x0020
#define INDEX_RIGHT_BITMASK  0x0040
#define MEDIUM_RIGHT_BITMASK 0x0080
#define RING_RIGHT_BITMASK   0x0100
#define LITTLE_RIGHT_BITMASK 0x0200
#define THUMB_LEFT_BITMASK   0x0010
#define INDEX_LEFT_BITMASK   0x0008
#define MEDIUM_LEFT_BITMASK  0x0004
#define RING_LEFT_BITMASK    0x0002
#define LITTLE_LEFT_BITMASK  0x0001
#endif

//Example of some masks:
#define HAND_RIGHT_BITMASK   (THUMB_RIGHT_BITMASK|INDEX_RIGHT_BITMASK|MEDIUM_RIGHT_BITMASK|RING_RIGHT_BITMASK|LITTLE_RIGHT_BITMASK)	//0x3E0
#define HAND_LEFT_BITMASK    (THUMB_LEFT_BITMASK|INDEX_LEFT_BITMASK|MEDIUM_LEFT_BITMASK|RING_LEFT_BITMASK|LITTLE_LEFT_BITMASK)	//0x01F

//This enables all the fingers:
#define FINGERS_ALL_BITMASK  (HAND_RIGHT_BITMASK | HAND_LEFT_BITMASK)	//0x3FF

#define PALMS_BITMASK        0x0400

//Rolled/Flat mode
#define ROLLED_BITMASK		0x8000
#define FLAT_442_BITMASK	0x4000

//--- These are some AFIS modes ---
//Flat442
#define AFIS_SYSTEM_442_BITMASK		(FLAT_442_BITMASK | FINGERS_ALL_BITMASK)	//0x43FF
//Rolled + Flat442
#define AFIS_SYSTEM_10PRINT_BITMASK	(AFIS_SYSTEM_442_BITMASK | ROLLED_BITMASK)	//0xC3FF
//Rolled + Flat442 + Palm
#define AFIS_SYSTEM_PALM_BITMASK	(AFIS_SYSTEM_10PRINT_BITMASK | PALMS_BITMASK)	//0xC7FF


#ifdef WIN32
	// win32
	#ifdef _USRDLL
	#define _AFISexportDlg extern "C"
	#else
	#define _AFISexportDlg
	#endif

	#define _AFIScall __stdcall

#else
	// linux
	#define _AFISexportDlg 
	#define _AFIScall 
#endif // LINUX

//Fingerprint index for FLAT fingerprints
#define FLAT_RIGHT_THUMB      0
#define FLAT_RIGHT_INDEX      1
#define FLAT_RIGHT_MEDIUM     2
#define FLAT_RIGHT_RING       3
#define FLAT_RIGHT_LITTLE     4
#define FLAT_LEFT_THUMB       5
#define FLAT_LEFT_INDEX       6
#define FLAT_LEFT_MEDIUM      7
#define FLAT_LEFT_RING        8
#define FLAT_LEFT_LITTLE      9
//Fingerprint index for ROLLED fingerprints
#define ROLLED_RIGHT_THUMB    10
#define ROLLED_RIGHT_INDEX    11
#define ROLLED_RIGHT_MEDIUM   12
#define ROLLED_RIGHT_RING     13
#define ROLLED_RIGHT_LITTLE   14
#define ROLLED_LEFT_THUMB     15
#define ROLLED_LEFT_INDEX     16
#define ROLLED_LEFT_MEDIUM    17
#define ROLLED_LEFT_RING      18
#define ROLLED_LEFT_LITTLE    19
//Fingerprint index for 442 and PALM images
#define A442_RIGHT_HAND       20	
#define A442_LEFT_HAND        21	
#define A442_THUMBS           22	
#define PALM_RIGHT            23
#define PALM_LEFT             24


//------------------------------------------------------------------------------
// ---------------------- FxISO_AFIS_ResetImageBuffers -------------------------
// The following function reset all the AFIS images
//------------------------------------------------------------------------------
_AFISexportDlg int _AFIScall FxISO_AFIS_ResetImageBuffers();
//

//------------------------------------------------------------------------------
// ------------------------- FxISO_AFIS_EnrollmentDlg --------------------------
// The following function opens an AFIS Enrollment dialog (AFIS EGI) that operates 
// on the images passed in the structure with the given scannerType. 
//------------------------------------------------------------------------------
_AFISexportDlg int _AFIScall FxISO_AFIS_EnrollmentDlg(int scannerType, BOOL allowDelete,
												HWND hwnd, int x, int y, 
												DWORD fingMask);
// PARAMETERS
//		scannerType:  Input - specify the scanner to operate with
//		allowDelete:  Input - if TRUE previously acquired fingerprints can be deleted/modified
//		hwnd:         Input - handler of the window which will be the parent window of EGI. 
//							NULL can be used for console applications or when hwnd is not available.
//		x,y:          Input - coordinates of the first corner (left,up) where EGI will be drawn. 
//							Use negative valeus (i.e. -1,-1) to automatically center EGI on the screen.             
//		fingMask:     Input - this parameter define if a finger is enabled or not for enrollment.
//							Suggested masks are AFIS_SYSTEM_442_BITMASK or AFIS_SYSTEM_PALM_BITMASK.
//							If fingMask is left 0 no finger is enabled for enrollment, and
//							the only operation allowed is the delete (if allowDelete is TRUE).
//
// RETURNED VALUE
//		FxISO_OK: the function succeeded, valid fingerprint images are in AFIS Fingerprints buffers
//		FxISO_Cancel: the user pressed the button 'Cancel'
//		>= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
// NOTE:
//		If scannerType is "DISPLAY_ONLY" the function do not allow modification of fingerprints
//


//------------------------------------------------------------------------------
// --------------------- FxISO_AFIS_GetFingerprintImage -----------------------
// Gets the image for a particular fingerprint. 
// The image is copied to the FxBuffer "pImageBuffer"
//------------------------------------------------------------------------------
_AFISexportDlg int _AFIScall FxISO_AFIS_GetFingerprintImage(int fingerIndex, int *changed, int *quality100, FxBuffer *pImageBuffer);
// PARAMETERS
//		fingerIndex:   Input - the finger index (from FLAT_RIGHT_THUMB to PALM_LEFT)
//		changed:       Output - a code that inform of a changed image
//								0: no image available (or deleted)
//								1: the image present was not changed from the original passed
//								2: image acquired
//		quality100:    Output - the quality from 0 (Bad) to 100 (Excellent)
//		pImageBuffer:  Output - FxBuffer with the image 
// RETURNS
//		FxISO_OK is the function succeeded
// NOTE
//		Even if the image is not acquired, it returns FxISO_OK, "changed" should be checked


//------------------------------------------------------------------------------
// -------------------- FxISO_AFIS_SetFingerprintImage ------------------------
// Sets the image for a particular fingerprint. 
// The image is copied from the FxBuffer "pImageBuffer"
//------------------------------------------------------------------------------
_AFISexportDlg int _AFIScall FxISO_AFIS_SetFingerprintImage(int fingerIndex, FxBuffer *pImageBuffer, int quality100);
// PARAMETERS
//		fingerIndex:   Input - the finger index (from FLAT_RIGHT_THUMB to PALM_LEFT)
//		pImageBuffer:  Input - FxBuffer with the image 
//		quality100:    Input - the image quality (if <0 it is internally computed)
// RETURNS
//		FxISO_OK if everithing is ok


//------------------------------------------------------------------------------
// ------------------ FxISO_AFIS_GetFingerprintQualityNIST --------------------
// Gets the NIST quality for a particular fingerprint. 
//------------------------------------------------------------------------------
_AFISexportDlg int _AFIScall FxISO_AFIS_GetFingerprintQualityNIST(int fingerIndex, int *qualityNIST);
// PARAMETERS
//		fingerIndex:   Input - the finger index (single finger from FLAT_RIGHT_THUMB to ROLLED_LEFT_LITTLE)
//		qualityNIST:    Output - the image quality as NIST standard, defined in the range [1=Good, 5=Bad]
// RETURNS
//		FxISO_OK if everithing is ok


#ifdef __cplusplus
}
#endif


#endif //__AFISInterface_H
