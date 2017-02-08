//----------------------------------------------------------------------------------------------------
//
// Company:	BiometriKa s.r.l. - www.biometrika.it
// E-mail:	info@biometrika.it
//
// Copyright(C) 2014, Biometrika s.r.l.
// All rights reserved.
//
//	In this header all "FxISO_Dev_" functions to interact with the fingerprint 
//	scanner device are defined:
//
//	This header is included from the main "fxisoDll.h" header.
//
//----------------------------------------------------------------------------------------------------
#ifndef FXISO_DEVICE_H
#define FXISO_DEVICE_H
	

#ifdef __cplusplus
extern "C" {
#endif


// Acquisition Targets
#define TARGET_PC 1
#define TARGET_SCANNER 2

// Connections
#define CONNECTION_ON 1
#define CONNECTION_OFF 2

//Fingerprint Led colors
#define FING_LED_OFF       0
#define FING_LED_RED       1
#define FING_LED_ORANGE    2
#define FING_LED_GREEN     3
#define FING_LED_BLUE      4


//------------------------------------------------------------------------------
// ------------------ Enumeration methods to address devices -------------------
//------------------------------------------------------------------------------
// Functions to open a scanner different from the default scanner, and to know
// the properties of the connected scanners
//------------------------------------------------------------------------------

//Structure for enumeration of connected devices
typedef struct
{
	DWORD devID;			//handle of the device
	DWORD width, height;	//width and height of the image
	DWORD dpi;				//Dot Per Inch of the image
	DWORD status;			//status of the scanner
	BYTE serialNumber[16];	//univocal scanner serial number
	char scannerName[16];	//"HiScan", "Fx3000", "Fx2000"...
	BYTE unused[16];		//reserved for future use
} FxDevInfo;

_fxexport FXISOerror _fxcall FxISO_Dev_Enumerate(int *nScanners);
//	Start the enumeration of the connected devices. 
//	PARAMETERS
//		nScanners: Output - the number of scanners connected
//	RETURNED VALUE
//		FXISO_OK: the function succeeded

_fxexport FXISOerror _fxcall FxISO_Dev_GetNext(FxDevInfo *scannerInfo);
//	Get the info on the first available scanner. 
//	Repeatedly calling this functions all the scanners are queried.
//	PARAMETERS
//		scannerInfo: Output - info structure on the available scanner. The "devID" field is the device handle.
//	RETURNED VALUE
//		FXISO_OK: the function succeeded

_fxexport FXISOerror _fxcall FxISO_Dev_SetActive(DWORD hDevice);
//	Set the default scanner that will be opened for the next acquisition. 
//	PARAMETERS
//		hDevice: Input - the handle of a scanner as returned in the "devID" field of 
//                       the info device returned by a call to FxISO_Dev_GetNextDevice()
//	RETURNED VALUE
//		FXISO_OK: the function succeeded

_fxexport FXISOerror _fxcall FxISO_Dev_GetActive(FxDevInfo *scannerInfo);
//	Get the default scanner that is used for acquisitions
//	PARAMETERS
//		scannerInfo: Output - the info structure on the current active scanner.
//	RETURNED VALUE
//		FXISO_OK: the function succeeded
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// ---------------------- FX Scanner Additional Commands -----------------------
//------------------------------------------------------------------------------
// All these functions begins with FxISO_Dev_ and gives access to specific scanner 
// features
//------------------------------------------------------------------------------

_fxexport int _fxcall FxISO_Dev_Standby(void);
// Put the sensor in standy mode (power save)
// The sensor must be re-activated before calling acquisition/setting function  
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FxISOSCAN errors) 

_fxexport int _fxcall FxISO_Dev_Resume(void);
// Re-activate the sensor from standby mode.
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FxISOSCAN errors) 

_fxexport int _fxcall FxISO_Dev_GetConfig(unsigned char* LiveMode,unsigned char* InternalLight,unsigned char* RedLed,unsigned char* GreenLed);
// Read the sensor configuration: 
// If a NULL value is passed as a parameter pointer the corresponding setting is ignored
// PARAMETERS
//       LiveMode: Output - denotes the visual feedback mode during acquisition; use:
//                 1 for FULL_IMAGE
//                 2 for HALF_IMAGE
//                 3 for BLIND
//  InternalLight: Output - Internal light (red leds) activation ( 1:ON - 2:OFF )
//         RedLed: Output - Red led activation ( 1:ON - 2:OFF )
//       GreenLed: Output - Green Led activation ( 1:ON - 2:OFF )
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FxISOSCAN errors) 

_fxexport int _fxcall FxISO_Dev_SetConfig(unsigned char* LiveMode,unsigned char* InternalLight,unsigned char* RedLed,unsigned char* GreenLed);
// Set the sensor configuration: 
// If a NULL value is passed as a parameter pointer the corresponding setting is ignored
// PARAMETERS
//       LiveMode: Input - denotes the visual feedback mode during acquisition; use:
//                 1 for FULL_IMAGE (Default)
//                 2 for HALF_IMAGE
//                 3 for BLIND
//  InternalLight: Input - Internal light (red leds) activation ( 1:ON - 2:OFF )
//         RedLed: Input - Red led activation ( 1:ON - 2:OFF )
//       GreenLed: Input - Green Led activation ( 1:ON - 2:OFF )
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FxISOSCAN errors) 

_fxexport int _fxcall FxISO_Dev_SetAcquisitionTarget(unsigned char Target);
// Set the target of fingerprint acquisition. 
//   By defualt all the acquisition functions FxISO_Fing_Acquire... acquire a fingerprint image
//   on the PC (the default Target is the PC).
//   To perform Match On Board (only with scanners supporting MOB like FX3000) the acquisition
//   target must be the Scanner, so that the (last) fingerprint image is stored into the scanner
//   and not transferred to the PC. Even if the scanner is set as acquisition target, depending
//   on the LiveMode set with FxISO_Dev_SetConfig, the intermediate fingerprint images collcted during
//   the acquisition process can be still sent to the PC to provide a visual feedback to the user.
//   If one wants to avoid sending (intermediate) fingerprint images to the PC, he/she can
//   simply set LiveMode = BLIND.  
// PARAMETERS
//     Target: 1 TARGET_PC  (Default)
//						 2 TARGET_SCANNER
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FX3SCAN errors) 

_fxexport int _fxcall FxISO_Dev_ForceScannerConnection(unsigned char Connection);
// By default each time an FxISO_Dev_*** or FX3_MOB_*** command have to be executed, a new communication
//   is established with the scanner and, at the end of the command, the communication channel is closed.
//   This is OK for most of the standard applications, while it could be not good for applications
//   using MOB capabilities of MOB scanners (like Fx3000). In fact, if the application needs to send
//   a sequence of FX3_MOB commands, opening and closing the communication channel at each single
//   command is not efficient. By using this command the application can force the communication channel
//   to remain open (CONNECTION_ON) until an explicit closing command is sent (CONNECTION_OFF).
//   The command also works for non-MOB scanners like Fx2000. 
// PARAMETERS
//     Connection: 1 CONNECTION_ON    
//								 2 CONNECTION_OFF  
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FX3SCAN errors) 

_fxexport int _fxcall FxISO_Dev_SetFakeDetection(unsigned char LatentCheck,unsigned char LivenessCheck);
// Set the sensor fake detection mode: 
//   When fake detection is enabled the acquisition function may return an error (see the above FX3SCAN errors)
//   in case a fake finger has been detected
//       LatentCheck: Input - enables/disables check of latent fingerprint left on the sensor surface
//                    O Disabled
//                    1 Enabled
//     LivenessCheck: Input - enables/disables check of finger liveness (not yet implemented)
//                    O Disabled
//                    1 Enabled
//       
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FX3SCAN errors) 

_fxexport int _fxcall FxISO_Dev_EnterAutoDetection(void);
// Enter AutoDetection mode: this function must be called before FxISO_Dev_Presence
//  The internal illumination is activated and the two led turned off.
//  The sensor is ready to be polled by using FxISO_Dev_Presence
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FX3SCAN errors) 

_fxexport int _fxcall FxISO_Dev_Presence(unsigned char* Presence);
// Polls the sensor to check the fingerprint presence
// Before using this function you must enter Autodetection mode (FxISO_Dev_EnterAutoDetection)
// At the end of AutoDetection you must call FxISO_Dev_ExitAutoDetection  
// The function takes about 150 ms before returning, even if practically
//   no CPU time is wasted since the PC CPU is internally released by the function during the sensor computations;   
//   therefore the PC can implement a strict polling routine without the risk of subtracting useful time
//   to other processes.  
// PARAMETERS
//     Presence: indicates the finger presence on the sensor
//       0: indicates minimum presence (no finger on the sensor)
//       100: indicates maxinum presence
//   FxISO_OK: the function succeeded
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FX3SCAN errors) 


_fxexport int _fxcall FxISO_Dev_ExitAutoDetection(void);
// Exit AutoDetection mode: this function must be called to leave autodetection mode
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FX3SCAN errors) 


_fxexport FXISOerror _fxcall FxISO_Dev_SetAcquisitionRotation(int rotation);
//Set the rotation of the fingerprint scanner as follows:
//	0: Normal
//	1: 90° clockwise rotation
//	2: 180° rotation
//	3: 90° counterclockwise rotation
// RETURNED VALUE
//	FxISO_OK: the function succeeded
//	FxISO_InvalidMode: rotation not supported


_fxexport FXISOerror _fxcall FxISO_Dev_ActivateCleaning(BOOL enableAuto, BOOL enableUser);
//	Enable the image cleaning procedure in automatic every time the scanner starts an acquisition
//	PARAMETERS
//		enableAuto: Input - TRUE to enable the authomatic image cleaning at every acquisition; FALSE to disable
//		enableUser: Input - TRUE to enable the user to perform a clean of the image when the AGI is displayed
//	RETURNED VALUE
//		FX3_OK: the function succeeded


#define LED_442_HAND_RIGHT   0x3C0
#define LED_442_HAND_LEFT    0x00F
#define LED_442_THUMBS       0x030
#define THUMB_RIGHT_BITMASK  0x020
#define INDEX_RIGHT_BITMASK  0x040
#define MEDIUM_RIGHT_BITMASK 0x080
#define RING_RIGHT_BITMASK   0x100
#define LITTLE_RIGHT_BITMASK 0x200
#define THUMB_LEFT_BITMASK   0x010
#define INDEX_LEFT_BITMASK   0x008
#define MEDIUM_LEFT_BITMASK  0x004
#define RING_LEFT_BITMASK    0x002
#define LITTLE_LEFT_BITMASK  0x001

_fxexport FXISOerror _fxcall FxISO_Dev_EnlightIndicationLed(DWORD activationFlag);
// Enlight the indicator leds on HiScan-FG scanner and 442 scanners.
// Acquisition functions will use the indicator leds, and will turn off the leds 
// automatically at the end of the acquisition.
// PARAMETERS
//      activationFlag: Input - is the activation flag of the scanner's indicator leds
//								It is the same bitmask of the EGI dialog (cfr. fxISOenrdlg.h). 
//								Values are here reported for quick reference:
//										THUMB_RIGHT_BITMASK  0x020
//										INDEX_RIGHT_BITMASK  0x040
//										MEDIUM_RIGHT_BITMASK 0x080
//										RING_RIGHT_BITMASK   0x100
//										LITTLE_RIGHT_BITMASK 0x200
//										THUMB_LEFT_BITMASK   0x010
//										INDEX_LEFT_BITMASK   0x008
//										MEDIUM_LEFT_BITMASK  0x004
//										RING_LEFT_BITMASK    0x002
//										LITTLE_LEFT_BITMASK  0x001
//								Up to 3 fingerprint leds can be turned on at the same time
//								combining the bitmasks.
//								Additional values are available for 442 scanners:		
//										LED_442_HAND_RIGHT   0x3C0
//										LED_442_HAND_LEFT    0x00F
//										LED_442_THUMBS       0x030
//								Only listed values are accepted, invalid values are ignored
// RETURNED VALUE
//     FxISO_OK: the function succeeded


_fxexport FXISOerror _fxcall FxISO_Dev_SetFingerprintLedColor(BYTE vFingerprintLedStatus[10]);
// Sets immediately the color of indicator leds on HiScan-FG scanner.
// It is responsability of the application to turn on/off the leds.
// PARAMETERS
//      vFingerprintLedStatus: Input - is an array, one byte for each fingerprint led.
//                              The fingerprint numeration is the same used in the models,
//                              from FING_RIGHT_THUMB=0 to FING_LEFT_LITTLE=9.
//                              Each led can be set to a different status: 
//								FING_LED_OFF / FING_LED_RED / FING_LED_ORANGE / FING_LED_GREEN / FING_LED_BLUE
//								No more that 3 fingerprint leds can be turned on at the same time.
// RETURNED VALUE
//     FxISO_OK: the function succeeded

_fxexport FXISOerror _fxcall FxISO_Dev_SetAcquisitionDPI(int DPI);
// When working with a scanner that supports more than one DPI settings, it changes the acquisition DPI
// For example the Fx2100 that by default works at 500 DPI, can be set in 569 DPI mode.
// PARAMETERS
//      DPI: Input - the DPI value, 500 or 569. If an invalid DPI is set, the scanner is 
//                   initialized to the default DPI value and an error is returned
// RETURNED VALUE
//     FxISO_OK: the function succeeded
//     FxISO_InvalidParameter: the DPI is not valid, or the scanner doesn't allow multiple settings

//------------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif

#endif // FXISO_DEVICE_H
