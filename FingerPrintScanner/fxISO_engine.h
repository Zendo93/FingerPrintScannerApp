//----------------------------------------------------------------------------------------------------
//
// Company:	BiometriKa s.r.l. - www.biometrika.it
// E-mail:	info@biometrika.it
//
// Copyright(C) 2014, Biometrika s.r.l.
// All rights reserved.
//
//	In this header all FxISO functions related to the fingerprint recognition engine are defined:
//	"SM" and "MM" slot functions and "Eng" matching functions.
//
//	This header is included from the main "fxisoDll.h" header.
//
//----------------------------------------------------------------------------------------------------
#ifndef FXISO_ENGINE_H
#define FXISO_ENGINE_H
	

#ifdef __cplusplus
extern "C" {
#endif


// Format modes
#define ISOFORMAT_STANDARD	0
#define ISOFORMAT_CARD		1
#define ISOFORMAT_COMPACT	2

// Speed Mode
#define SPEED_MODE_STANDARD 1
#define SPEED_MODE_FAST     2

//Fingerprints position index
#define FING_POS_UNKNOWN     -1
#define FING_RIGHT_THUMB      0
#define FING_RIGHT_INDEX      1
#define FING_RIGHT_MEDIUM     2
#define FING_RIGHT_RING       3
#define FING_RIGHT_LITTLE     4
#define FING_LEFT_THUMB       5
#define FING_LEFT_INDEX       6
#define FING_LEFT_MEDIUM      7
#define FING_LEFT_RING        8
#define FING_LEFT_LITTLE      9


//------------------------------------------------------------------------------
// ---------------------------- SingleModel functions --------------------------
//------------------------------------------------------------------------------
// All these functions begins with FxISO_SM_ and operates on the SingleModel object,
// also called SMslot
//------------------------------------------------------------------------------

_fxexport FXISOerror _fxcall FxISO_SM_LoadFromMemory(FxBuffer* model, int format);
// Loads(copies) a model into SMslot from a model buffer
// PARAMETERS
//   model:  Input - the buffer structure with the model.
//					"memory" is a pointer to the memory region where a valid model is stored.
//					The size of the buffer is stored in "sizeUsed" field.
//   format: Input - one of {ISOFORMAT_STANDARD, ISOFORMAT_CARD, ISOFORMAT_COMPACT}
//					The application should know the format used to save the model.
// NOTE:
//   The format defines the size of the minutia: 6, 5 or 3 Bytes
//   If the buffer contains more than one model only the first is loaded
// RETURNED VALUE
//   FxISO_OK: the function succeeded, a 1-model has been loaded into SMslot
//   FxISO_InvalidModelFile: invalid model format.

_fxexport FXISOerror _fxcall FxISO_SM_SaveToMemory(FxBuffer* model, int format, BOOL extended);
// Writes the model from SMslot to a memory buffer
// PARAMETERS
//   model:  Output - the buffer structure with the model.
//					"memory" is a pointer to the memory region where a valid model is stored.
//					The size of the buffer is stored in "sizeUsed" field.
//					** NOTE **: if the "memory" pointer is NULL or the allocated size is 
//					insufficient the SDK will automatically allocates a memory region.
//					The user should free the allocated buffer calling FxISO_Mem_DeAllocateBuffer()
//
//   format:   Input - one of {ISOFORMAT_STANDARD, ISOFORMAT_CARD, ISOFORMAT_COMPACT}
//	 extended: Input - if TRUE saves the extended data (created by the engine for better accuracy)
//						if FALSE removes the extended data from the model, to have a smaller model
// NOTE:
//   The format defines the size of the minutia: 6, 5 or 3 Bytes
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the model from SMslot has been stored to memory
//   FxISO_ModelNotCreated: no models in SMslot.
//   FxISO_InvalidModelFile: the model in SMslot is invalid
//   FxISO_InvalidMode: mode must be 0 or 1

_fxexport FXISOerror _fxcall FxISO_SM_CreateFromFing(void);
// Creates a model in SMslot from the fingerprint image in FingSlot
// RETURNED VALUE
//   FxISO_OK: the function succeeded, a model has been stored in SMslot
//   FxISO_LowNumberOfMinutiae: (WARNING) a low number of minutiae have been detected on the 
//                              fingerprint in FingSlot; anyway, a model has been stored in SMslot
//   FxISO_FingerprintNotAvailable: no fingerprints acquired/loaded in FingSlot 
//                                  (use FxISO_AcquireFingerprint or FxISO_LoadFingerprintFromFile before)
//   FxISO_CannotProcessFingerprint: the quality of the fingerprint in FingSlot is too low;
//                                   a model cannot be created

_fxexport FXISOerror _fxcall FxISO_SM_GetQuality(float *quality);
// Get the quality of the model into SMslot
// PARAMETERS
//   quality:  Output - the quality of the model in the range 0..100
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   FxISO_ModelNotCreated: no model in SMslot

_fxexport FXISOerror _fxcall FxISO_SM_GetNumMinutiae(int *nMinutiae);
// Get the number of minutiae of the model into SMslot
// PARAMETERS
//   nMinutiae:  Output - the number of minutiae of the model 
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   FxISO_ModelNotCreated: no model in SMslot

_fxexport FXISOerror _fxcall FxISO_SM_GetMinutia(int indexMinutia, int *pixelX, int *pixelY, int *angle360, int *quality100);
// Get info on one minutia of the model into SMslot
// PARAMETERS
//   indexMinutia: Input  - the index of the minutia, from 0 to nMinutiae-1
//   pixelX:       Output - the x position on the fingerprint image at 500DPI
//   pixelY:       Output - the y position on the fingerprint image at 500DPI
//   angle360:     Output - the minutia angle, from 0 to 359 degree
//   quality100:   Output - the quality from 1 to 100. Optional for some model format: 0 means "no quality computed"
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   FxISO_ModelNotCreated: no model in SMslot
//   FxISO_InvalidParameter: wrong minutia index

_fxexport FXISOerror _fxcall FxISO_SM_GetMaxSize(int format, int* Size);
// Returns the max model Size according to the required format, extended data included
// This function can be used to determine the size of the buffer the application should 
// create to hold a model.
// PARAMETERS
//   format: Input - one of {ISOFORMAT_STANDARD, ISOFORMAT_CARD, ISOFORMAT_COMPACT}
//   Size: Output - max size for a 1-model
// NOTE:
//   The format defines the size of the minutia: 6, 5 or 3 Bytes
//	 The Overall model Size is: n*Size where n is the number of 1-models used.
// RETURNED VALUE
//   FxISO_OK: the function succeeded

_fxexport FXISOerror _fxcall FxISO_SM_SetCreationMode(int speedMode);
// Sets a given operating mode for model creation
//
// PARAMETERS
//  speed mode: SPEED_MODE_STANDARD  (max. accuracy)
//              SPEED_MODE_FAST      (max. efficiency)
//
// RETURNED VALUE:
//   FxISO_OK: the function succeeded
//   FxISO_InvalidMode: Mode not supported


//------------------------------------------------------------------------------
// ---------------------------- MultiModel functions ---------------------------
//------------------------------------------------------------------------------
// All these functions begins with FxISO_MM_ and operates on the MultiModel object,
// also called MMslot
//------------------------------------------------------------------------------

_fxexport FXISOerror _fxcall FxISO_MM_LoadFromMemory(FxBuffer* model, int format);
// Loads(copies) a model from memory into MMslot
// PARAMETERS
//   model:  Input - the buffer structure with the model.
//					"memory" is a pointer to the memory region where a valid model is stored.
//					The size of the buffer is stored in "sizeUsed" field.
//   format: Input - one of {ISOFORMAT_STANDARD, ISOFORMAT_CARD, ISOFORMAT_COMPACT}
//					The application should know the format used to save the model.
// NOTE:
//   The format defines the size of the minutia: 6, 5 or 3 Bytes
// RETURNED VALUE
//   FxISO_OK: the function succeeded, a valid model has been loaded in MMslot
//   FxISO_InvalidModelFile: invalid model format.

_fxexport FXISOerror _fxcall FxISO_MM_SaveToMemory(FxBuffer* model, int format, BOOL extended);
// Writes the model from MMslot to a memory buffer
// PARAMETERS
//   model:  Output - the buffer structure with the model.
//					"memory" is a pointer to the memory region where a valid model is stored.
//					The size of the buffer is stored in "sizeUsed" field.
//					** NOTE **: if the "memory" pointer is NULL or the allocated size is 
//					insufficient the SDK will automatically allocates a memory region.
//					The user should free the allocated buffer calling FxISO_Mem_DeAllocateBuffer()
//
//   format:   Input - one of {ISOFORMAT_STANDARD, ISOFORMAT_CARD, ISOFORMAT_COMPACT}
//	 extended: Input - if TRUE saves the extended data (created by the engine for better accuracy)
//						if FALSE removes the extended data from the model, to have a smaller model
// NOTE:
//   The format defines the size of the minutia: 6, 5 or 3 Bytes
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the model from Fslot has been stored to memory
//   FxISO_ModelNotCreated: no models in MMslot.
//   FxISO_InvalidModelFile: the model in MMslot is invalid


_fxexport FXISOerror _fxcall FxISO_MM_GetInfo(int nFingerVect[10], int *nUnknownFinger);
// Get the information of how many fingerprints are stored in the Multi Model in MMslot
// PARAMETERS
//   nFingerVect[10]: Output - vector of 10 elements, reporting the number of samples for each finger
//			0: Right Thumb
//			1: Right Forefinger
//			2: Right Middle Finger
//			3: Right Ring Finger
//			4: Right Little Finger
//			5: Left Thumb
//			6: Left Forefinger
//			7: Left Middle Finger
//			8: Left Ring Finger
//			9: Left Little Finger
//   nUnknownFinger: Output - the number of samples for a finger of unknown position
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   FxISO_ModelNotCreated: no models in MMslot.
//   FxISO_InvalidModelFile: the model in MMslot is invalid

_fxexport FXISOerror _fxcall FxISO_MM_Add_SM(int idxFingerType);
// Add the model in SMslot to the Multiple Model in MMslot
// PARAMETERS
//   idxFingerType: Input - the index of the finger from 0 to 9 or -1 if the position is unknown
// NOTE:
//   Remember to clear the MMslot with FxISO_MM_DeleteAll() before starting a new Multi Model
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the model from SMslot has been stored to MMslot
//   FxISO_ModelNotCreated: no models in SMslot.
//   FxISO_InvalidModelFile: the model in MMslot or SMslot is invalid

_fxexport FXISOerror _fxcall FxISO_MM_Extract_SM(int idxFingerType, int nSample);
// Gets the requested model in MMslot and copies it to SMslot
// PARAMETERS
//   idxFingerType: Input - the index of the finger from 0 to 9 or -1 if the position is unknown
//   nSample: Input - the number of the sample to get
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the model from MMslot has been stored to SMslot
//   FxISO_ModelNotCreated: no models in MMslot with the specified idxFinger and nSample.
//   FxISO_InvalidModelFile: the model in MMslot or SMslot is invalid

_fxexport FXISOerror _fxcall FxISO_MM_DeleteSingleModel(int idxFingerType, int nSample);
// Deletes the specified model from MMslot
// PARAMETERS
//   idxFingerType: Input - the index of the finger from 0 to 9 or -1 if the position is unknown
//   nSample: Input - the number of the sample to delete
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the model from MMslot has been deleted
//   FxISO_ModelNotCreated: no models in MMslot with the specified idxFinger and nSample.

_fxexport FXISOerror _fxcall FxISO_MM_DeleteAll();
// Deletes ALL the models in MMslot
// RETURNED VALUE
//   FxISO_OK: the function succeeded, the models from MMslot has been deleted

//------------------------------------------------------------------------------
// ------------------------- Matching Engine functions -------------------------
// The following functions configures the matching engine and perform a match 
// between the two models loaded in SingleModel and MultiModel
//------------------------------------------------------------------------------

_fxexport FXISOerror _fxcall FxISO_Eng_SetSessionKey(BOOL enableChyper, unsigned char* key);
// Sets the session key used to encrypt/decrypt models;
//
//  FxISO uses the session key to encrypt/decrypt fingerprint models.
//  In order to create encrypted models, FxISO_SetSessionKey must be called before:
//    - FxISO_SM_SaveToMemory
//    - FxISO_MM_SaveToMemory
//  On the other hand, if a model has been encrypted by using a specific key,
//  the same key must loaded into the system (by using FxISO_SetSessionKey)
//  before calling the following function to reload the model:  
//    - FxISO_SM_LoadFromMemory
//    - FxISO_MM_LoadFromMemory
//  The same session key remain valid until the FxISO_End is called or another session
//    Key is loaded over the current one. 
//  Therefore it is RESPONSABILITY of the USER APPLICATION to STORE the KEYS used
//  to encrypt the models and RELOAD them into the system when required.   
//
// PARAMETERS
//	enableChyper: Input - if TRUE enables the encryption/decryption of the models
//						if FALSE the models are non encrypted.
//  key: Input - pointer to the memory region (16 bytes) where a session key is stored
//        the session key may assume every possible value (2^128 distinct values)
// RETURNED VALUE
//   FxISO_OK: the key has been set
//

_fxexport FXISOerror _fxcall FxISO_Eng_Matching(float mins, float* similarity);
// matches the fingerprint image loaded in FingSlot (or the 1-model loaded in SMslot)
//         with the (single or multiple) model loaded in MMslot.
// PARAMETERS
//   mins: Input - minimum similarity (for multiple-models)
//   similarity: Output - similarity resulting from the matching
//               0 indicate no similarity, 1 max similarity
//               a threshold must be used to Accept or Reject the User
// RETURNED VALUE
//   FxISO_OK: the function succeeded
//   FxISO_ModelNotAvailable: no model has been loaded in MMslot
//   FxISO_FingerprintNotAvailable: neither fingerprint images nor 1-models in FingSlot or SMslot
//   FxISO_CannotProcessFingerprint: the quality of the fingerprint image in FingSlot is too low;
//                                 the matching cannot be performed


//------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // FXISO_ENGINE_H
