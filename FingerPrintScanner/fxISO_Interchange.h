#ifndef __FXINTERCHANGE_H
#define __FXINTERCHANGE_H


#ifdef __cplusplus
extern "C" {
#endif


	
#ifdef WIN32
	// win32
	#ifdef _LIB
		#define _fxexport
	#else
		#define _fxexport __declspec(dllexport)
	#endif

	#define _fxcall __stdcall
#else
	// linux
	#define _fxexportDlg 
	#define _fxcall 
#endif // LINUX



//==============================================================================
//===========================  ANSI/NIST-ITL 1-2007  ===========================
//==============================================================================
// The following functions are used to export fingerprints with information 
// relating to the subject of the transaction in an "ANSI/NIST-ITL 1-2007" format.
//==============================================================================

//------------------------------------------------------------------------------
// ------------------------ FxISO_Subject_ResetRecord -------------------------
//		Resets the "Subject" object, and sets it ready to accept new data
//------------------------------------------------------------------------------
_fxexport void _fxcall FxISO_Subject_ResetRecord();



//------------------------------------------------------------------------------
// ---------------------- FxISO_Subject_SetGenericField -----------------------
// Sets a text string to the generic field defined by the given field number
// The callee should know the ITL format of the field
//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_Subject_SetGenericField(int fieldNum, char *text);
// PARAMETERS
//		fieldNum:    Input - the record number
//		text:        Input - textual data in ITL format
// RETURNS
//			FxISO_OK if everithing is ok

//------------------------------------------------------------------------------
// ------------------------ Subject information fields ------------------------
// The following are generic fields defined by the given field number
//------------------------------------------------------------------------------
#define SubjectDAR	4	//Date of Record
#define SubjectDLU	5	//Date of Last Update
#define SubjectSCT	6	//Send Copy To
#define SubjectCNO	7	//Case Number
#define SubjectSQN	8	//Sequence Number
#define SubjectMID	9	//Latent Identifier
#define SubjectCRN	10	//Criminal Reference Number
#define SubjectORN	11	//Other Reference Number
#define SubjectMN1	12	//Miscellaneous Identification Number
#define SubjectMN2	13	//Miscellaneous Identification Number
#define SubjectMN3	14	//Miscellaneous Identification Number
#define SubjectMN4	15	//Miscellaneous Identification Number
#define SubjectMN5	16	//Miscellaneous Identification Number
#define SubjectFNU	17	//Finger Number
#define SubjectFIB	18	//Fingerprint Identification Byte
#define SubjectDPR	19	//Date Fingerprinted
#define SubjectTOF	20	//Time of Fingerprinting
#define SubjectRFP	21	//Reason Fingerprinted
#define SubjectPOA	22	//Place Of Arrest
#define SubjectOBU	23	//Owning Bureau
#define SubjectDON	24	//Date of Notice
#define SubjectSIM	25	//Station Inputting Latent
#define SubjectQLM	26	//Quality Measure
#define SubjectCCP	27	//Coarse Classification of Patterns
#define SubjectFCP	28	//Fine Classification of Patterns
#define SubjectNLF	29	//Nominal File
#define SubjectNAM	30	//Name
#define SubjectMNA	31	//Maiden Name
#define SubjectADD	32	//Address
#define SubjectTRU	33	//True Identity
#define SubjectAKA	34	//Aliases
#define SubjectDOB	35	//Date of Birth
#define SubjectDBR	36	//Date of Birth Range
#define SubjectPOB	37	//Place of Birth
#define SubjectNAT	38	//Nationality
#define SubjectSEX	39	//Sex
#define SubjectCOL	40	//Color
#define SubjectHGT	41	//Height
#define SubjectBLD	42	//Build
#define SubjectHAI	43	//Hair
#define SubjectFAC	44	//Face
#define SubjectLAN	45	//Languages Spoken
#define SubjectPHO	46	//Photograph Number
#define SubjectPSP	47	//Passport Number
#define SubjectMAR	48	//Marks etc
#define SubjectOCC	49	//Occupation
#define SubjectWNG	50	//Warning
#define SubjectMDO	51	//Modus Operandi
#define SubjectGAC	52	//Geographical Area of Crime
#define SubjectGSA	53	//Geographical Search Area
#define SubjectOTY	54	//Offence Type
#define SubjectDOO	55	//Date of Offence
#define SubjectDOR	56	//Date of Offence Range
#define SubjectDSR	57	//Date of Offence Search Range
#define SubjectTOO	58	//Time of Offence
#define SubjectTOR	59	//Time of Offence Range
#define SubjectTSR	60	//Time of Offence Search Range
#define SubjectTLM	61	//Time Limit
#define SubjectICP	62	//ICPO/GS
#define SubjectINF	63	//Additional Information
#define SubjectRLS	64	//Respondents List
#define SubjectCOU	65	//Recipient Countries
#define SubjectRES	66	//Result
#define SubjectALF	67	//Alert Flag
#define SubjectTCF	68	//Target Criminal Flag
#define SubjectIDF	69	//Identified Flag
#define SubjectMPF	70	//Latent Priority Flag
#define SubjectTUF	71	//Tie Up Flag
#define SubjectRNK	72	//Rank
#define SubjectDSG	73	//Date signature
#define SubjectERM	74	//Status/Error Message Field
#define SubjectFFN	75	//Father´s Family Name
#define SubjectMMN	76	//Mothers´s Maiden Name
#define SubjectBRT	77	//Broadcast Request To
#define SubjectFPR	78	//Finger Present
#define SubjectARI	79	//Additional Response Information
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// -------------------------- FxISO_Subject_SetName ---------------------------
// Sets the name and surname of the subject
//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_Subject_SetName(char *name, char *surname);
// PARAMETERS
//		name:    Input - the subject name
//		surname: Input - the subject surname
// RETURNS
//			FxISO_OK if everithing is ok


//------------------------------------------------------------------------------
// ------------------------- FxISO_Subject_SetBirth ---------------------------
// Sets the birth information of the subject
//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_Subject_SetBirth(int day, int month, int year, char *placeCountry, char *placeTown, char *nationality, char *sex);
// PARAMETERS
//		day:          Input - day number [1..31]
//		month:        Input - month number [1..12]
//		year:         Input - four digits year number
//		placeCountry: Input - the country of birth
//		placeTown:    Input - the town of birth
//		nationality:  Input - the nationality of the fingerprinted subject
//		sex:          Input - the sex in [F,M,U] as Female, Male, Undetermined
// RETURNS
//			FxISO_OK if everithing is ok

//------------------------------------------------------------------------------
// ------------------------ FxISO_Subject_SetAddress --------------------------
// Sets the address of the subject
//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_Subject_SetAddress(char *address);
// PARAMETERS
//		address:      Input - the address, max 128 bytes
// RETURNS
//			FxISO_OK if everithing is ok

//------------------------------------------------------------------------------
// ------------------------- FxISO_Subject_SetFamily --------------------------
// Sets the family information for the subject
//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_Subject_SetFamily(char *fatherName, char *fatherSurname, char *motherName, char *motherMaidenName);
// PARAMETERS
//		fatherName:          Input - the father name
//		fatherSurname:       Input - the father name
//		motherName:          Input - the mother name
//		motherMaidenSurname: Input - the mother name
// RETURNS
//			FxISO_OK if everithing is ok

//------------------------------------------------------------------------------
// ----------------------- FxISO_Subject_SetOccupation ------------------------
// Sets the occupation of the subject
//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_Subject_SetOccupation(char *occupation);
// PARAMETERS
//		occupation:          Input - the occupation type
// RETURNS
//			FxISO_OK if everithing is ok


//------------------------------------------------------------------------------
// ------------------------- FxISO_Subject_SetHeight --------------------------
// Sets the Height of the subject
//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_Subject_SetHeight(int height);
// PARAMETERS
//		height:  Input - the height in cm
// RETURNS
//			FxISO_OK if everithing is ok


//------------------------------------------------------------------------------
// -------------------------- FxISO_Subject_SetHair ---------------------------
// Sets the Hair color and/or style of the subject
//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_Subject_SetHair(char *hair);
// PARAMETERS
//		hair:    Input - a free text description of the color and style of the subject's hair
// RETURNS
//			FxISO_OK if everithing is ok



//------------------------------------------------------------------------------
// ---------------------- FxISO_Subject_ExportITL2007 -------------------------
// Export the subject data alongside with the fingerprint images in the AFIS 
// object in an ITL2007 format
//------------------------------------------------------------------------------
_fxexport int _fxcall FxISO_Subject_ExportITL2007(char *filename, char *originatingAgency, char *destinationAgency, float wsqBitRate);
// PARAMETERS
//		filename:    Input - the name of the output file
//		originatingAgency
//		destinationAgency
//		wsqBitRate
// RETURNS
//			FxISO_OK if everithing is ok


#ifdef __cplusplus
}
#endif


#endif //__FXINTERCHANGE_H
