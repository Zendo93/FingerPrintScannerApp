//----------------------------------------------------------------------------------------------------
//
// Company:	BiometriKa s.r.l. - www.biometrika.it
// E-mail:	info@biometrika.it
//
// Copyright(C) 2014, Biometrika s.r.l.
// All rights reserved.
//
// This is the main header for FxISO SDK.
// Including this, all FxISO_xxx_ functions are available to the developer, where "xxx" is:
//		"Dev": scanner specific functions that works with the device
//		"Mem": functions to handle memory buffers, that can hold images and models
//		"Fing": functions used to acquire fingerprint images to the internal "Fing" slot
//		"SM": functions that works on the Single-Model slot (usually the one just acquired)
//		"MM": functions that works on the Multi-Model slot (usually the model stored)
//		"Eng": functions to perform the match between SM and MM models.
// The header is conveniently split in several files, included at the end of this.
//
//----------------------------------------------------------------------------------------------------
// FXDLL_LINUX must be defined for compilation under Linux
//----------------------------------------------------------------------------------------------------

#ifndef HEADER_FXISODLL_H
#define HEADER_FXISODLL_H

#ifndef FXDLL_LINUX
	// win32
#ifndef ARM9
	#ifndef WINVER
		#include <windows.h>
  #endif

  #if WINVER<0x0400
		#error WINVER must be at least 0x0400
  #endif
	
	#define _fxcall __stdcall
#else
	#include "type.h"
	#include "Target.h"
	#define _fxcall
#endif

	#ifdef _LIB
		#define _fxexport
	#else
		#define _fxexport __declspec(dllexport)
	#endif

#else // linux
	#define _fxexport 
	#define _fxcall 
	#ifndef HWND
	#define HWND void*
	#endif
	typedef unsigned char BYTE;
	typedef unsigned int DWORD;
	typedef int BOOL;
#endif // FXDLL_LINUX


#ifdef __cplusplus
extern "C" {
#endif

//Error codes
typedef int FXISOerror;
#define FxISO_OK                        0
#define FxISO_InsufficientMemory        1
#define FxISO_TimeOut                   3
#define FxISO_FileNotExisting           4
#define FxISO_InvalidFingerprintData    5
#define FxISO_TooLowQuality             6
#define FxISO_InvalidModelFile          7
#define FxISO_ModelNotCreated           8
#define FxISO_CannotWritetoDisk         9
#define FxISO_CannotUpdateModel         10
#define FxISO_InvalidMode               11
#define FxISO_FingerprintNotAvailable   12
#define FxISO_CannotProcessFingerprint  13
#define FxISO_LowNumberOfMinutiae       14
#define FxISO_ModelNotAvailable         15
#define FxISO_Cancel                    16
#define FxISO_InvalidSize               17
#define FxISO_InvalidParameter          18
#define FxISO_InitNotCalled             20

#define FxISO_AcquisitionError          100
// Acquisition error specification (added to FxISO_Acquisition Error)
	#define FxISO_SCAN_DllNotFound 10
	#define FxISO_SCAN_CorruptedDll 11
	#define FxISO_SCAN_InitializationFailure 12
	#define FxISO_SCAN_SettingFailure 13
	#define FxISO_SCAN_GrabbingFailure 14
	#define FxISO_SCAN_UnInitializationFailure 15
	#define FxISO_SCAN_ShowError 16
	#define FxISO_SCAN_TimerError 17
	#define FxISO_SCAN_InvalidParameters 18
	#define FxISO_SCAN_NoOnlineCapability 20
	#define FxISO_SCAN_InvalidFingerprintImage 21
	#define FxISO_SCAN_InvalidLatent 22
	#define FxISO_SCAN_InvalidLiveness 23
	#define FxISO_SCAN_FeatureNotAvailable 24
	#define FxISO_SCAN_CommunicationError 25
	#define FxISO_SCAN_FilePermissionError 26
	#define FxISO_SCAN_FileSystemError 27


//ResolutionMode
#define NATIVE_RESOLUTION 1	//NATIVE is an Obsolete definition: please use a specific DPI output
#define DPI500_RESOLUTION 2
#define DPI569_RESOLUTION 3
#define DPI1000_RESOLUTION 4


//------------------------------------------------------------------------------
// ------------------- Initial configuration functions -------------------------
//------------------------------------------------------------------------------
// Functions to initialize the library 
//------------------------------------------------------------------------------

_fxexport FXISOerror _fxcall FxISO_Init(void);
// Initialization; creates FingSlot SMslot and MMslot
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   FxISO_InsufficientMemory: insufficient memory for initialization

_fxexport FXISOerror _fxcall FxISO_End(void);
// Releases memory and terminates
// RETURNED VALUE
//   FxISO_OK: the function succeeded

_fxexport FXISOerror _fxcall FxISO_Version(char* fxISO,char* fxISOscan,char* fxISOenrdlg);
// Return the version of fxISO, fxISOscan and fxISOenrdlg dlls
// PARAMETERS
//         fxISO: Input - pointer to the char array where the fxISO.dll version will be copied.
//                      The array must be allocated by the caller (15 byte is the max size of the string returned)
//                      If the caller is not interested pass NULL          
//     fxISOscan: Input - pointer to the char array where the fxISOscan.dll version will be copied.
//                      The array must be allocated by the caller (15 byte is the max size of the string returned) 
//                      If the caller is not interested pass NULL
//   fxISOenrdlg: Input - pointer to the char array where the fxISOenrdlg.dll version will be copied.
//                      The array must be allocated by the caller (15 byte is the max size of the string returned) 
//                      If the caller is not interested pass NULL


_fxexport FXISOerror _fxcall FxISO_SetLanguage(int langCode);
// Set the language used on graphic interfaces like AGI, EGI and AFIS
// PARAMETERS
//   langCode: Input - the language code is one of follows:
//                     0 - ITALIAN
//                     1 - ENGLISH
// RETURNED VALUE
//   FxISO_OK: the function succeeded

_fxexport FXISOerror _fxcall FxISO_GetLanguage(int *langCode);
// Get the current language used on graphic interfaces like AGI, EGI and AFIS
// PARAMETERS
//   langCode: Output - the language code
// RETURNED VALUE
//   FxISO_OK: the function succeeded



//------------------------------------------------------------------------------
// ----------------- Functions to acquire an image in FingSlot -----------------
//------------------------------------------------------------------------------
// Functions to acquire an image in Automatic or Attended mode, using Biometrika
// user interface or silent mode
//------------------------------------------------------------------------------


_fxexport FXISOerror _fxcall FxISO_Fing_EnableAcquisitionRollMode(BOOL enabled, int windowPosition);
// Enable the acquisition of a rolled fingerprint
// PARAMETERS
//   enabled: Input - TRUE to enable the rolled mode, FALSE to disable
//	 windowPosition: Input -	0 for the leftmost acquisition window
//								1 for the centered acquisition window
//								2 for the rightmost acquisition window
// RETURNED VALUE
//   FxISO_OK: the function succeeded

#ifndef ARM9
_fxexport FXISOerror _fxcall FxISO_Fing_AcquireAutomatic(HWND hwnd, int x, int y, float* quality, int det_th, float timeout, float delay);
// Captures one fingerprint image automatically from the device into FingSlot
//   Opens an Auto AGI dialog box which shows the live grabbing.
// PARAMETERS
//   hwnd: Input - handler of the window which will be the parent window of ACQDIAG.
//         NULL can be used for console applications or if an hwnd is not available.
//   x,y: Input - coordinates of the first corner (left,up) where ACQDIAG will be drawn. 
//        use negative valeus (i.e. -1,-1) to automatically center ACQDIAG in the screen.             
//   quality: Output - quality of the returned fingerprint image.
//   det_th: Input - detection presence threshold (0-100);
//           as soon as "detection" exceeds det_th a fingerprint image is captured and returned.      
//   t: Input - timeout (in seconds)
//   d: Input - delay (in seconds)
//
// RETURNED VALUE
//   FxISO_OK: the function succeeded, a valid fingerprint image has been copied in FingSlot
//   FxISO_Cancel: the user pressed the button 'Cancel'
//   FxISO_TimeOut: the function returned because of the timeout
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FxISOSCAN errors) 

_fxexport FXISOerror _fxcall FxISO_Fing_AcquireSupervised(HWND hwnd, int x, int y, float* quality);
//	Captures one fingerprint image from the device into FingSlot. 
//	Supervised by the operator means: the user choose when to grab the image.
//	Opens a Manual AGI dialog box which shows the live grabbing.
// PARAMETERS
//   hwnd: Input - handler of the window which will be the parent window of manual AGI dialog box.
//         NULL can be used for console applications or if an hwnd is not available.
//   x,y: Input - coordinates of the first corner (left,up) where the AGI will be drawn. 
//        use negative valeus (i.e. -1,-1) to automatically center the AGI on the screen. 
//   quality: Output - quality of the returned fingerprint image.
// RETURNED VALUE
//   FxISO_OK: the function succeeded, a valid fingerprint image has been copied in FingSlot
//   FxISO_Cancel: the user pressed the button 'Cancel'
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the above FxISOSCAN errors) 
#endif

_fxexport FXISOerror _fxcall FxISO_Fing_MuteAcquireAutomatic(float* quality,int det_th,float timeout,float delay);
// Behaves exactly like FxISO_Fing_AcquireAutomatic, but no graphical display is performed

#ifndef __PGRABCALLBACK
typedef int (*PGRABCALLBACK)(int presence100,int quality100,unsigned char *image,unsigned short ix,unsigned short iy);
#define __PGRABCALLBACK
#endif
_fxexport FXISOerror _fxcall FxISO_Fing_CallBackAcquireSupervised(float* quality,PGRABCALLBACK cbFunc);
_fxexport FXISOerror _fxcall FxISO_Fing_CallBackAcquireAutomatic(float* quality,int det_th,float timeout,float delay,PGRABCALLBACK cbFunc);
// Behaves exactly like FxISO_Fing_AcquireSupervised and FxISO_Fing_AcquireAutomatic respectively,
//   but a callback function is here provided for supervisioning the captured images


//------------------------------------------------------------------------------
// --------- Functions to create memory buffers and Load/Save on file ----------
//------------------------------------------------------------------------------
// All these functions begins with FxISO_Mem_ and handle memory buffers used by 
// the SDK.
// Buffers are used to hold:
//	+fingerprint images
//	+compressed fingerprint images (wsq)
//	+fingerprint models
//------------------------------------------------------------------------------

typedef struct
{
	DWORD hMemory;			//Handle of the allocated memory
	int sizeUsed;			//size used
	int imageWidth;			//if the buffer holds a bitmap, these are the image width
	int imageHeight;		// and height
	DWORD reserved;			//reserved for future use
} FxBuffer;

_fxexport FXISOerror _fxcall FxISO_Mem_NewBuffer(FxBuffer *buffer);
//Allocates a memory buffer
//Each allocated buffer should be freed with a call to FxISO_Mem_DeleteBuffer() 

_fxexport FXISOerror _fxcall FxISO_Mem_DeleteBuffer(FxBuffer *buffer);
//Releases the previously allocated memory buffer

_fxexport FXISOerror _fxcall FxISO_Mem_LoadBufferFromFile(char *pathname, FxBuffer *buffer);
//Loads buffer data from "pathname" file. Automatically allocates memory for the buffer if needed
// PARAMETERS
//   pathname:	Input  - source file pathname
//	 buffer:	Output - the FxBuffer that will hold the readed informations. 
//				If the size is not enough, it will automatically allocates new memory and deallocates the old memory
//				If the file is a TIF image (or a bmp) the size is in "imageWidth" and "imageHeight" fields.
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the file has been loaded in buffer
//   FxISO_FileNotExisting: the file denoted by pathname does not exist.
//   FxISO_InvalidParameter: invalid parameter or file format.

_fxexport FXISOerror _fxcall FxISO_Mem_SaveBufferToFile(char *pathname, FxBuffer *buffer);
//Saves buffer data on "pathname" file. If data is an image a correct file name extension should be 
//used: ".bmp" to save the image as a Windows bitmap, or ".tif" to save the image in TIFF format. 
// PARAMETERS
//   pathname:	Input  - output file pathname
//	 buffer:	Input - the FxBuffer that holds the informations to be written. 
//				If the file is a TIF image (or a bmp) the size should be set in "imageWidth" and "imageHeight" fields.
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the buffer has been saved
//   FxISO_CannotWritetoDisk: the file specified by pathname cannot be written
//   FxISO_InvalidParameter: invalid parameter or file format.

_fxexport FXISOerror _fxcall FxISO_Mem_CopyBufferToArray(FxBuffer *buffer, BYTE *userArray, int nMaxItems);
//Copy the content of the memory buffer to an user defined array
// PARAMETERS
//	 buffer:	Input - the FXBuffer that holds the informations to be written. 
//	 userArray	Output - the user allocated array, destination of the copy
//	 nMaxItems	Input - the lenght of the array
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the file has been copied into the user supplied array
//   FxISO_InvalidParameter: invalid parameter or file format.

_fxexport FXISOerror _fxcall FxISO_Mem_CopyArrayToBuffer(BYTE *userArray, int nItems, FxBuffer *buffer);
//Copy the content of the user defined array to the memory buffer
// PARAMETERS
//	 userArray	Input - the user allocated array, source of the copy
//	 nMaxItems	Input - the lenght of the array
//	 buffer:	Output - the FxBuffer destination of the copy 
//				If the size is not enough, it will automatically allocates new memory and deallocates the old memory
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the file has been loaded in buffer
//   FxISO_InvalidParameter: invalid parameter or file format.


//------------------------------------------------------------------------------
// ------------------------- Bitmap specific functions -------------------------
//------------------------------------------------------------------------------
// If an FxBuffer holds a fingerprint bitmap, these functions gives access to the
// image. 
//------------------------------------------------------------------------------

_fxexport FXISOerror _fxcall FxISO_Mem_CopyImageArrayToBuffer(BYTE *imageArray, int imageWidth, int imageHeight, FxBuffer *buffer);
//Copy the content of the user defined array to the memory buffer As in "FxISO_Mem_CopyArrayToBuffer"
// and set the imageWidth and imageHeight of the buffer
// PARAMETERS
//	 userArray	 Input - the user allocated array, source of the copy, contains the image data 
//	 imageWidth	 Input - the width of the image
//	 imageHeight Input - the height of the image
//	 buffer:	 Output - the FxBuffer destination of the copy 
//				If the size is not enough, it will automatically allocates new memory and deallocates the old memory
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the file has been loaded in buffer
//   FxISO_InvalidParameter: invalid parameter

typedef struct 
{
	DWORD	size;
    DWORD	width;
	DWORD	height;
	BYTE	info[1052];
} FxBITMAPINFO;

_fxexport BYTE* _fxcall FxISO_Mem_GetImage(FxBuffer *imageBuffer, FxBITMAPINFO *bmpInfo);
// Gives access to the image stored into the buffer 
// PARAMETERS
//	imageBuffer:   Input - the buffer structure with the image.
//					The image size is stored in "imageWidth" and "imageHeight" fields.
//	bmpInfo: Output - contains the size of the image. Can be used in Windows Platform SDK functions 
//					when a BITMAPINFO is required.
// RETURNED VALUE
//	returns a pointer to the memory region where a WidthxHeight pixel image is stored by rows 
//	from the top to the bottom and in the row from the left to the right.	
//	This is the original image location stored in "imageBuffer", do NOT free this pointer.
// NOTE. Usefull to create a bitmap, for example calling:
//
//		BYTE *bmpData = FxISO_Mem_GetImage(&imageBuffer, &bmpInfo);
//		Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap.FromBITMAPINFO((BITMAPINFO*)&bmpInfo, (VOID*)bmpData);
//

_fxexport BYTE _fxcall FxISO_Mem_GetImagePixel(FxBuffer *imageBuffer, int x, int y);
//Given the (x,y) point on the image returns the pixel color. 
//If (x,y) is outside the image boundaries the color is white (255).
// PARAMETERS
//	imageBuffer:   Input - the buffer structure with the image.
//					The image size is stored in "imageWidth" and "imageHeight" fields.

_fxexport BYTE* _fxcall FxISO_Mem_GetImageRow(FxBuffer *imageBuffer, int numRow);
//Given "numRow" the number of the row, returns a pointer to an array of pixels.
//If "numRow" if beyond the image height, returns a NULL pointer.
// PARAMETERS
//	imageBuffer:   Input - the buffer structure with the image.
//					The image size is stored in "imageWidth" and "imageHeight" fields.
// RETURNED VALUE
//	returns a pointer to the memory region where a row of "Width" pixel is stored from 
//	the left to the right.
//	This is the original image location stored in "imageBuffer", do NOT free this pointer.
//


//------------------------------------------------------------------------------
// --------------- Functions to Load/Save an image in FingSlot -----------------
//------------------------------------------------------------------------------
// All these functions begins with FxISO_Fing_ and gives access to the internally 
// stored image in FingSlot
//------------------------------------------------------------------------------

_fxexport FXISOerror _fxcall FxISO_Fing_LoadFromMemory(FxBuffer* imageBuffer, float* q);
// Loads(copies) one fingerprint image from memory into FingSlot
// PARAMETERS
//   imageBuffer: Input - the buffer structure with the image.
//					The image size is stored in "imageWidth" and "imageHeight" fields.
//   q: Output - quality of the loaded fingerprint image.
// RETURNED VALUE
//   FxISO_OK: the function succeeded, a valid fingerprint image has been loaded in FingSlot
//   FxISO_TooLowQuality: the image quality is too low and it cannot be processed by FxISO;
//                      no fingerprint has been loaded in FingSlot.
//   FxISO_InvalidSize: the Width or/and Height passed are not valid

_fxexport FXISOerror _fxcall FxISO_Fing_SaveToMemory(FxBuffer* imageBuffer,
														unsigned char resolutionMode, 
														int *OutputResolution);
// Saves(copies) the fingerprint image in FingSlot to memory
// The image is saved at the required DPI resolution if supported by the fingerprint scanner.
// Images saved by this function can be reloaded into the FingSlot by using the 
// FxISO_Fing_LoadFingerprintFromMemory function
// PARAMETERS
//   imageBuffer: Output - the buffer structure with the image.
//					The image size is stored in "imageWidth" and "imageHeight" fields.
//					** NOTE **: if the "memory" handler is NULL or the allocated size is 
//					insufficient the SDK will automatically allocates a memory region.
//					The user can free the allocated buffer calling FxISO_Mem_DeAllocateBuffer()
//
//   resolutionMode: Input - DPI500_RESOLUTION, DPI569_RESOLUTION or DPI1000_RESOLUTION
//   outputResolution: Output - the resolution of the saved image
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the fingerprint image (in FingSlot) has been stored
//   FxISO_FingerprintNotAvailable: no fingerprints in FingSlot

_fxexport FXISOerror _fxcall FxISO_Fing_SaveToWSQ(FxBuffer* wsqBuffer, float bitrate,
																unsigned char resolutionMode, 
																int *OutputResolution);
// Exports the fingerprint image to a standard compressed WSQ buffer
// The image is saved at the required DPI resolution if supported by the fingerprint scanner.
// Note: images saved by this function can be reloaded into the FingSlot
// PARAMETERS
//   wsqBuffer: Output - the buffer structure with the wsq compressed image.
//						The size of the buffer is stored in "sizeUsed" field.
//					** NOTE **: if the "memory" handler is NULL or the allocated size is 
//					insufficient the SDK will automatically allocates a memory region.
//					The user should free the allocated buffer calling FxISO_Mem_DeAllocateBuffer()
//
//   bitrate: Input - the compression bit rate. Suggested values:
//                 0.75 (about 1:15 ratio, excellent compression and acceptable quality)
//                 1.0  (about 1:12 ratio)
//                 1.2  (about 1:10 ratio, good image quality)
//                 1.5  (about 1:8 ratio)
//                 2.25 (about 1:5 ratio, excellent image quality)
//   resolutionMode: Input - DPI500_RESOLUTION, DPI569_RESOLUTION or DPI1000_RESOLUTION
//   outputResolution: Output - the resolution of the saved image
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the fingerprint image (in FingSlot) has been stored
//   FxISO_FingerprintNotAvailable: no fingerprints in FingSlot

_fxexport FXISOerror _fxcall FxISO_Fing_LoadFromWSQ(FxBuffer* wsqBuffer, float* q);
// Loads one fingerprint image from a WSQ compressed buffer into FingSlot
// PARAMETERS
//   wsqBuffer: Input - the buffer structure with the wsq compressed image.
//						"memory" is a pointer to the memory region where the image is stored.
//						The size of the buffer is stored in "sizeUsed" field.
//   q: Output - quality of the loaded fingerprint image.
// RETURNED VALUE
//   FxISO_OK: the function succeeded, a valid fingerprint image has been loaded in Fslot
//   FxISO_InvalidFingerprintData: invalid file format.
//   FxISO_TooLowQuality: the image quality is too low and it cannot be processed by FxISO;
//                      no fingerprint has been loaded in FingSlot.

//------------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif

#endif // HEADER_FXISODLL_H

#include "fxISO_device.h"
#include "fxISO_engine.h"
