#ifndef __FXISOENR_H
#define __FXISOENR_H

#ifdef __cplusplus
extern "C" {
#endif

// fx3enrdlg.h

// values for AGI_type
#define AUTOMATIC 1
#define SUPERVISED 2
#define ON_LINE 4
#define OFF_LINE 5

#define FxISOENR_InsufficientMemory  201
#define FxISOENR_NullModel 202

#ifndef THUMB_RIGHT_BITMASK
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
#endif

//Example of some masks:
#define HAND_RIGHT_BITMASK   (THUMB_RIGHT_BITMASK|INDEX_RIGHT_BITMASK|MEDIUM_RIGHT_BITMASK|RING_RIGHT_BITMASK|LITTLE_RIGHT_BITMASK)
#define HAND_LEFT_BITMASK    (THUMB_LEFT_BITMASK|INDEX_LEFT_BITMASK|MEDIUM_LEFT_BITMASK|RING_LEFT_BITMASK|LITTLE_LEFT_BITMASK)

//This enables all the fingers:
#define FINGERS_ALL_BITMASK  (HAND_RIGHT_BITMASK|HAND_LEFT_BITMASK)


#ifndef FXDLL_LINUX
	// win32
	#ifdef _USRDLL
	#define _fxexportDlg extern "C"
	#else
	#define _fxexportDlg
	#endif

	#define _fxcall __stdcall

#else
	// linux
	#define _fxexportDlg 
	#define _fxcall 
#endif // FXOEM_LINUX

//------------------------------------------------------------------------------
// ---------------------------- Enrollment dialog ------------------------------
// The following function opens an Enrollment dialog (EGI) that operates on the 
// model stored in MultiModel slot. 
// NOTE: SingleModel is modified by this dialog.
//------------------------------------------------------------------------------

_fxexportDlg int _fxcall FxISO_MM_EnrollmentDlg(int AGI_type, 
                                                           HWND hwnd, int x, int y,
                                                           int det_thr, float timeout, float delay, 
														   DWORD fingMask);
// Opens the Enrollment Graphical Interface (EGI) to edit the model loaded in MMslot
// For every enrollement opens an AGI dialog box which shows the live grabbing.
// PARAMETERS
//   AGI_type: Input - specify if the acquisition is Automatic (Auto) or operator Supervised (Manual) 
//   hwnd:     Input - handler of the window which will be the parent window of EGI and AGI
//                     NULL can be used for console applications or if an hwnd is not available.
//   x,y:      Input - coordinates of the first corner (left,up) where EGI and AGI will be drawn. 
//                     Use negative valeus (i.e. -1,-1) to automatically center EGI and AGI in the screen.             
//   det_thr:  Input - detection presence threshold (0-100); as soon as "detection" 
//                     exceeds det_th a fingerprint image is captured and returned.  
//   timeout:  Input - timeout (in seconds) before considering to close the window without the finger
//   delay:    Input - delay (in seconds). The finger should be continuously acquired for at least
//                     this delay before considering the fingerprint image stable
//   fingMask: Input - this parameter define if a finger is enabled or not for enrollment.
//						Suggested mask is FINGERS_ALL_BITMASK.
//						If fingMask is left 0 no finger is enabled for enrollment, and the only 
//						operation allowed is the delete.
// RETURNED VALUE
//   FxISO_OK: the function succeeded, a valid fingerprint image has been copied in FingSlot
//   FxISO_Cancel: the user pressed the button 'Cancel'
//   FxISO_TimeOut: the function returned because of the timeout
//   >= FxISO_AcquisitionError: an hardware/software problem has been encountered;  
//                            if > FxISO_AcquisitionError the residual (value - FxISO_AcquisitionError )
//                            defines the acquisition suberror occurred (see the FxISOSCAN errors) 





#ifdef __cplusplus
}
#endif


#endif //__FXISOENR_H
