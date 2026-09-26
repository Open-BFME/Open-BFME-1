//-------------------------------------------------------------------------- 
// 
//  Copyright (c) Microsoft Corporation.  All rights reserved. 
// 
//  File: msinkaut.h 
//      Microsoft Tablet PC API definitions 
// 
//-------------------------------------------------------------------------- 
	
 	
 	

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* Compiler settings for msinkaut.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __msinkaut_h__
#define __msinkaut_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IInkRectangle_FWD_DEFINED__
#define __IInkRectangle_FWD_DEFINED__
typedef interface IInkRectangle IInkRectangle;
#endif 	/* __IInkRectangle_FWD_DEFINED__ */


#ifndef __IInkExtendedProperty_FWD_DEFINED__
#define __IInkExtendedProperty_FWD_DEFINED__
typedef interface IInkExtendedProperty IInkExtendedProperty;
#endif 	/* __IInkExtendedProperty_FWD_DEFINED__ */


#ifndef __IInkExtendedProperties_FWD_DEFINED__
#define __IInkExtendedProperties_FWD_DEFINED__
typedef interface IInkExtendedProperties IInkExtendedProperties;
#endif 	/* __IInkExtendedProperties_FWD_DEFINED__ */


#ifndef __IInkDrawingAttributes_FWD_DEFINED__
#define __IInkDrawingAttributes_FWD_DEFINED__
typedef interface IInkDrawingAttributes IInkDrawingAttributes;
#endif 	/* __IInkDrawingAttributes_FWD_DEFINED__ */


#ifndef __IInkTransform_FWD_DEFINED__
#define __IInkTransform_FWD_DEFINED__
typedef interface IInkTransform IInkTransform;
#endif 	/* __IInkTransform_FWD_DEFINED__ */


#ifndef __IInkGesture_FWD_DEFINED__
#define __IInkGesture_FWD_DEFINED__
typedef interface IInkGesture IInkGesture;
#endif 	/* __IInkGesture_FWD_DEFINED__ */


#ifndef __IInkCursor_FWD_DEFINED__
#define __IInkCursor_FWD_DEFINED__
typedef interface IInkCursor IInkCursor;
#endif 	/* __IInkCursor_FWD_DEFINED__ */


#ifndef __IInkCursors_FWD_DEFINED__
#define __IInkCursors_FWD_DEFINED__
typedef interface IInkCursors IInkCursors;
#endif 	/* __IInkCursors_FWD_DEFINED__ */


#ifndef __IInkCursorButton_FWD_DEFINED__
#define __IInkCursorButton_FWD_DEFINED__
typedef interface IInkCursorButton IInkCursorButton;
#endif 	/* __IInkCursorButton_FWD_DEFINED__ */


#ifndef __IInkCursorButtons_FWD_DEFINED__
#define __IInkCursorButtons_FWD_DEFINED__
typedef interface IInkCursorButtons IInkCursorButtons;
#endif 	/* __IInkCursorButtons_FWD_DEFINED__ */


#ifndef __IInkTablet_FWD_DEFINED__
#define __IInkTablet_FWD_DEFINED__
typedef interface IInkTablet IInkTablet;
#endif 	/* __IInkTablet_FWD_DEFINED__ */


#ifndef __IInkTablets_FWD_DEFINED__
#define __IInkTablets_FWD_DEFINED__
typedef interface IInkTablets IInkTablets;
#endif 	/* __IInkTablets_FWD_DEFINED__ */


#ifndef __IInkStrokeDisp_FWD_DEFINED__
#define __IInkStrokeDisp_FWD_DEFINED__
typedef interface IInkStrokeDisp IInkStrokeDisp;
#endif 	/* __IInkStrokeDisp_FWD_DEFINED__ */


#ifndef __IInkStrokes_FWD_DEFINED__
#define __IInkStrokes_FWD_DEFINED__
typedef interface IInkStrokes IInkStrokes;
#endif 	/* __IInkStrokes_FWD_DEFINED__ */


#ifndef __IInkCustomStrokes_FWD_DEFINED__
#define __IInkCustomStrokes_FWD_DEFINED__
typedef interface IInkCustomStrokes IInkCustomStrokes;
#endif 	/* __IInkCustomStrokes_FWD_DEFINED__ */


#ifndef ___IInkStrokesEvents_FWD_DEFINED__
#define ___IInkStrokesEvents_FWD_DEFINED__
typedef interface _IInkStrokesEvents _IInkStrokesEvents;
#endif 	/* ___IInkStrokesEvents_FWD_DEFINED__ */


#ifndef __IInkDisp_FWD_DEFINED__
#define __IInkDisp_FWD_DEFINED__
typedef interface IInkDisp IInkDisp;
#endif 	/* __IInkDisp_FWD_DEFINED__ */


#ifndef ___IInkEvents_FWD_DEFINED__
#define ___IInkEvents_FWD_DEFINED__
typedef interface _IInkEvents _IInkEvents;
#endif 	/* ___IInkEvents_FWD_DEFINED__ */


#ifndef __IInkRenderer_FWD_DEFINED__
#define __IInkRenderer_FWD_DEFINED__
typedef interface IInkRenderer IInkRenderer;
#endif 	/* __IInkRenderer_FWD_DEFINED__ */


#ifndef __IInkCollector_FWD_DEFINED__
#define __IInkCollector_FWD_DEFINED__
typedef interface IInkCollector IInkCollector;
#endif 	/* __IInkCollector_FWD_DEFINED__ */


#ifndef ___IInkCollectorEvents_FWD_DEFINED__
#define ___IInkCollectorEvents_FWD_DEFINED__
typedef interface _IInkCollectorEvents _IInkCollectorEvents;
#endif 	/* ___IInkCollectorEvents_FWD_DEFINED__ */


#ifndef __IInkOverlay_FWD_DEFINED__
#define __IInkOverlay_FWD_DEFINED__
typedef interface IInkOverlay IInkOverlay;
#endif 	/* __IInkOverlay_FWD_DEFINED__ */


#ifndef ___IInkOverlayEvents_FWD_DEFINED__
#define ___IInkOverlayEvents_FWD_DEFINED__
typedef interface _IInkOverlayEvents _IInkOverlayEvents;
#endif 	/* ___IInkOverlayEvents_FWD_DEFINED__ */


#ifndef __IInkPicture_FWD_DEFINED__
#define __IInkPicture_FWD_DEFINED__
typedef interface IInkPicture IInkPicture;
#endif 	/* __IInkPicture_FWD_DEFINED__ */


#ifndef ___IInkPictureEvents_FWD_DEFINED__
#define ___IInkPictureEvents_FWD_DEFINED__
typedef interface _IInkPictureEvents _IInkPictureEvents;
#endif 	/* ___IInkPictureEvents_FWD_DEFINED__ */


#ifndef __IInkRecognizer_FWD_DEFINED__
#define __IInkRecognizer_FWD_DEFINED__
typedef interface IInkRecognizer IInkRecognizer;
#endif 	/* __IInkRecognizer_FWD_DEFINED__ */


#ifndef __IInkRecognizers_FWD_DEFINED__
#define __IInkRecognizers_FWD_DEFINED__
typedef interface IInkRecognizers IInkRecognizers;
#endif 	/* __IInkRecognizers_FWD_DEFINED__ */


#ifndef ___IInkRecognitionEvents_FWD_DEFINED__
#define ___IInkRecognitionEvents_FWD_DEFINED__
typedef interface _IInkRecognitionEvents _IInkRecognitionEvents;
#endif 	/* ___IInkRecognitionEvents_FWD_DEFINED__ */


#ifndef __IInkRecognizerContext_FWD_DEFINED__
#define __IInkRecognizerContext_FWD_DEFINED__
typedef interface IInkRecognizerContext IInkRecognizerContext;
#endif 	/* __IInkRecognizerContext_FWD_DEFINED__ */


#ifndef __IInkRecognitionResult_FWD_DEFINED__
#define __IInkRecognitionResult_FWD_DEFINED__
typedef interface IInkRecognitionResult IInkRecognitionResult;
#endif 	/* __IInkRecognitionResult_FWD_DEFINED__ */


#ifndef __IInkRecognitionAlternate_FWD_DEFINED__
#define __IInkRecognitionAlternate_FWD_DEFINED__
typedef interface IInkRecognitionAlternate IInkRecognitionAlternate;
#endif 	/* __IInkRecognitionAlternate_FWD_DEFINED__ */


#ifndef __IInkRecognitionAlternates_FWD_DEFINED__
#define __IInkRecognitionAlternates_FWD_DEFINED__
typedef interface IInkRecognitionAlternates IInkRecognitionAlternates;
#endif 	/* __IInkRecognitionAlternates_FWD_DEFINED__ */


#ifndef __IInkRecognizerGuide_FWD_DEFINED__
#define __IInkRecognizerGuide_FWD_DEFINED__
typedef interface IInkRecognizerGuide IInkRecognizerGuide;
#endif 	/* __IInkRecognizerGuide_FWD_DEFINED__ */


#ifndef __IInkWordList_FWD_DEFINED__
#define __IInkWordList_FWD_DEFINED__
typedef interface IInkWordList IInkWordList;
#endif 	/* __IInkWordList_FWD_DEFINED__ */


#ifndef __InkDisp_FWD_DEFINED__
#define __InkDisp_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkDisp InkDisp;
#else
typedef struct InkDisp InkDisp;
#endif /* __cplusplus */

#endif 	/* __InkDisp_FWD_DEFINED__ */


#ifndef __InkOverlay_FWD_DEFINED__
#define __InkOverlay_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkOverlay InkOverlay;
#else
typedef struct InkOverlay InkOverlay;
#endif /* __cplusplus */

#endif 	/* __InkOverlay_FWD_DEFINED__ */


#ifndef __InkPicture_FWD_DEFINED__
#define __InkPicture_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkPicture InkPicture;
#else
typedef struct InkPicture InkPicture;
#endif /* __cplusplus */

#endif 	/* __InkPicture_FWD_DEFINED__ */


#ifndef __InkCollector_FWD_DEFINED__
#define __InkCollector_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkCollector InkCollector;
#else
typedef struct InkCollector InkCollector;
#endif /* __cplusplus */

#endif 	/* __InkCollector_FWD_DEFINED__ */


#ifndef __InkDrawingAttributes_FWD_DEFINED__
#define __InkDrawingAttributes_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkDrawingAttributes InkDrawingAttributes;
#else
typedef struct InkDrawingAttributes InkDrawingAttributes;
#endif /* __cplusplus */

#endif 	/* __InkDrawingAttributes_FWD_DEFINED__ */


#ifndef __InkRectangle_FWD_DEFINED__
#define __InkRectangle_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkRectangle InkRectangle;
#else
typedef struct InkRectangle InkRectangle;
#endif /* __cplusplus */

#endif 	/* __InkRectangle_FWD_DEFINED__ */


#ifndef __InkRenderer_FWD_DEFINED__
#define __InkRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkRenderer InkRenderer;
#else
typedef struct InkRenderer InkRenderer;
#endif /* __cplusplus */

#endif 	/* __InkRenderer_FWD_DEFINED__ */


#ifndef __InkTransform_FWD_DEFINED__
#define __InkTransform_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkTransform InkTransform;
#else
typedef struct InkTransform InkTransform;
#endif /* __cplusplus */

#endif 	/* __InkTransform_FWD_DEFINED__ */


#ifndef __InkRecognizers_FWD_DEFINED__
#define __InkRecognizers_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkRecognizers InkRecognizers;
#else
typedef struct InkRecognizers InkRecognizers;
#endif /* __cplusplus */

#endif 	/* __InkRecognizers_FWD_DEFINED__ */


#ifndef __InkRecognizerContext_FWD_DEFINED__
#define __InkRecognizerContext_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkRecognizerContext InkRecognizerContext;
#else
typedef struct InkRecognizerContext InkRecognizerContext;
#endif /* __cplusplus */

#endif 	/* __InkRecognizerContext_FWD_DEFINED__ */


#ifndef __InkRecognizerGuide_FWD_DEFINED__
#define __InkRecognizerGuide_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkRecognizerGuide InkRecognizerGuide;
#else
typedef struct InkRecognizerGuide InkRecognizerGuide;
#endif /* __cplusplus */

#endif 	/* __InkRecognizerGuide_FWD_DEFINED__ */


#ifndef __InkTablets_FWD_DEFINED__
#define __InkTablets_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkTablets InkTablets;
#else
typedef struct InkTablets InkTablets;
#endif /* __cplusplus */

#endif 	/* __InkTablets_FWD_DEFINED__ */


#ifndef __InkWordList_FWD_DEFINED__
#define __InkWordList_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkWordList InkWordList;
#else
typedef struct InkWordList InkWordList;
#endif /* __cplusplus */

#endif 	/* __InkWordList_FWD_DEFINED__ */


#ifndef __InkStrokes_FWD_DEFINED__
#define __InkStrokes_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkStrokes InkStrokes;
#else
typedef struct InkStrokes InkStrokes;
#endif /* __cplusplus */

#endif 	/* __InkStrokes_FWD_DEFINED__ */


#ifndef __IInk_FWD_DEFINED__
#define __IInk_FWD_DEFINED__
typedef interface IInk IInk;
#endif 	/* __IInk_FWD_DEFINED__ */


#ifndef __IInkLineInfo_FWD_DEFINED__
#define __IInkLineInfo_FWD_DEFINED__
typedef interface IInkLineInfo IInkLineInfo;
#endif 	/* __IInkLineInfo_FWD_DEFINED__ */


#ifndef __ISketchInk_FWD_DEFINED__
#define __ISketchInk_FWD_DEFINED__
typedef interface ISketchInk ISketchInk;
#endif 	/* __ISketchInk_FWD_DEFINED__ */


#ifndef __Ink_FWD_DEFINED__
#define __Ink_FWD_DEFINED__

#ifdef __cplusplus
typedef class Ink Ink;
#else
typedef struct Ink Ink;
#endif /* __cplusplus */

#endif 	/* __Ink_FWD_DEFINED__ */


#ifndef __SketchInk_FWD_DEFINED__
#define __SketchInk_FWD_DEFINED__

#ifdef __cplusplus
typedef class SketchInk SketchInk;
#else
typedef struct SketchInk SketchInk;
#endif /* __cplusplus */

#endif 	/* __SketchInk_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "tpcshrd.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_msinkaut_0000 */
/* [local] */ 

#ifndef _MSINKAUT_IDL_H_
#define _MSINKAUT_IDL_H_
#include <TPCError.h> // for Tablet PC Error codes
typedef 
enum enumINKMETRIC_FLAGS
    {	IMF_FONT_SELECTED_IN_HDC	= 0x1,
	IMF_ITALIC	= 0x2,
	IMF_BOLD	= 0x4
    } 	INK_METRIC_FLAGS;

typedef 
enum enumGetCandidateFlags
    {	TCF_ALLOW_RECOGNITION	= 0x1,
	TCF_FORCE_RECOGNITION	= 0x2
    } 	GET_DANDIDATE_FLAGS;

typedef struct tagINKMETRIC
    {
    INT iHeight;
    INT iFontAscent;
    INT iFontDescent;
    DWORD dwFlags;
    COLORREF color;
    } 	INKMETRIC;

typedef struct tagINKMETRIC *PINKMETRIC;














extern RPC_IF_HANDLE __MIDL_itf_msinkaut_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_msinkaut_0000_v0_0_s_ifspec;


#ifndef __MSINKAUTLib_LIBRARY_DEFINED__
#define __MSINKAUTLib_LIBRARY_DEFINED__

/* library MSINKAUTLib */
/* [helpcontext][helpstring][helpfile][version][uuid] */ 

#define INK_SERIALIZED_FORMAT	L"Ink Serialized Format"
typedef /* [helpcontext][helpstring] */ 
enum ItemSelectionConstants
    {	ISC_FirstElement	= 0,
	ISC_AllElements	= -1
    } 	InkSelectionConstants;

#define STR_GUID_X                    L"{598A6A8F-52C0-4BA0-93AF-AF357411A561}"
#define STR_GUID_Y                    L"{B53F9F75-04E0-4498-A7EE-C30DBB5A9011}"
#define STR_GUID_Z                    L"{735ADB30-0EBB-4788-A0E4-0F316490055D}"
#define STR_GUID_PAKETSTATUS          L"{6E0E07BF-AFE7-4CF7-87D1-AF6446208418}"
#define STR_GUID_TIMERTICK            L"{436510C5-FED3-45D1-8B76-71D3EA7A829D}"
#define STR_GUID_SERIALNUMBER         L"{78A81B56-0935-4493-BAAE-00541A8A16C4}"
#define STR_GUID_NORMALPRESSURE       L"{7307502D-F9F4-4E18-B3F2-2CE1B1A3610C}"
#define STR_GUID_TANGENTPRESSURE      L"{6DA4488B-5244-41EC-905B-32D89AB80809}"
#define STR_GUID_BUTTONPRESSURE       L"{8B7FEFC4-96AA-4BFE-AC26-8A5F0BE07BF5}"
#define STR_GUID_XTILTORIENTATION     L"{A8D07B3A-8BF0-40B0-95A9-B80A6BB787BF}"
#define STR_GUID_YTILTORIENTATION     L"{0E932389-1D77-43AF-AC00-5B950D6D4B2D}"
#define STR_GUID_AZIMUTHORIENTATION   L"{029123B4-8828-410B-B250-A0536595E5DC}"
#define STR_GUID_ALTITUDEORIENTATION  L"{82DEC5C7-F6BA-4906-894F-66D68DFC456C}"
#define STR_GUID_TWISTORIENTATION     L"{0D324960-13B2-41E4-ACE6-7AE9D43D2D3B}"
#define STR_GUID_PITCHROTATION        L"{7F7E57B7-BE37-4BE1-A356-7A84160E1893}"
#define STR_GUID_ROLLROTATION         L"{5D5D5E56-6BA9-4C5B-9FB0-851C91714E56}"
#define STR_GUID_YAWROTATION          L"{6A849980-7C3A-45B7-AA82-90A262950E89}"
#define INKRECOGNITIONPROPERTY_LINENUMBER		  L"{DBF29F2C-5289-4BE8-B3D8-6EF63246253E}"
#define INKRECOGNITIONPROPERTY_SEGMENTATION       L"{B3C0FE6C-FB51-4164-BA2F-844AF8F983DA}"
#define INKRECOGNITIONPROPERTY_HOTPOINT           L"{CA6F40DC-5292-452a-91FB-2181C0BEC0DE}"
#define INKRECOGNITIONPROPERTY_MAXIMUMSTROKECOUNT L"{BF0EEC4E-4B7D-47a9-8CFA-234DD24BD22A}"
#define INKRECOGNITIONPROPERTY_POINTSPERINCH      L"{7ED16B76-889C-468e-8276-0021B770187E}"
#define INKRECOGNITIONPROPERTY_CONFIDENCELEVEL    L"{7DFE11A7-FB5D-4958-8765-154ADF0D833F}"
#define INKRECOGNITIONPROPERTY_LINEMETRICS        L"{8CC24B27-30A9-4b96-9056-2D3A90DA0727}"
#define FACTOID_NONE				L"NONE"
#define FACTOID_DEFAULT				L"DEFAULT"
#define FACTOID_SYSTEMDICTIONARY	L"SYSDICT"
#define FACTOID_WORDLIST			L"WORDLIST"
#define FACTOID_EMAIL				L"EMAIL"
#define FACTOID_WEB					L"WEB"
#define FACTOID_ONECHAR				L"ONECHAR"
#define FACTOID_NUMBER				L"NUMBER"
#define FACTOID_DIGIT				L"DIGIT"
#define FACTOID_NUMBERSIMPLE		L"NUMSIMPLE"
#define FACTOID_CURRENCY			L"CURRENCY"
#define FACTOID_POSTALCODE			L"POSTALCODE"
#define FACTOID_PERCENT				L"PERCENT"
#define FACTOID_DATE				L"DATE"
#define FACTOID_TIME				L"TIME"
#define FACTOID_TELEPHONE			L"TELEPHONE"
#define FACTOID_FILENAME			L"FILENAME"
#define FACTOID_UPPERCHAR			L"UPPERCHAR"
#define FACTOID_LOWERCHAR			L"LOWERCHAR"
#define FACTOID_PUNCCHAR			L"PUNCCHAR"
#define FACTOID_JAPANESECOMMON		L"JPN_COMMON"
#define FACTOID_CHINESESIMPLECOMMON	L"CHS_COMMON"
#define FACTOID_CHINESETRADITIONALCOMMON L"CHT_COMMON"
#define FACTOID_KOREANCOMMON		L"KOR_COMMON"
#define FACTOID_HIRAGANA			L"HIRAGANA"
#define FACTOID_KATAKANA			L"KATAKANA"
#define FACTOID_KANJICOMMON		    L"KANJI_COMMON"
#define FACTOID_KANJIRARE			L"KANJI_RARE"
#define FACTOID_BOPOMOFO	        L"BOPOMOFO"
#define FACTOID_JAMO				L"JAMO"
#define FACTOID_HANGULCOMMON		L"HANGUL_COMMON"
#define FACTOID_HANGULRARE			L"HANGUL_RARE"
typedef /* [helpcontext][helpstring] */ 
enum InkBoundingBoxMode
    {	IBBM_Default	= 0,
	IBBM_NoCurveFit	= 1,
	IBBM_CurveFit	= 2,
	IBBM_PointsOnly	= 3,
	IBBM_Union	= 4
    } 	InkBoundingBoxMode;

#define IBBM_Last IBBM_Union + 1
typedef /* [helpcontext][helpstring] */ 
enum InkExtractFlags
    {	IEF_CopyFromOriginal	= 0,
	IEF_RemoveFromOriginal	= 0x1,
	IEF_Default	= IEF_RemoveFromOriginal
    } 	InkExtractFlags;

#define IEF_All  (IEF_RemoveFromOriginal | IEF_CopyFromOriginal)
typedef /* [helpcontext][helpstring] */ 
enum InkPersistenceFormat
    {	IPF_InkSerializedFormat	= 0,
	IPF_Base64InkSerializedFormat	= 1,
	IPF_GIF	= 2,
	IPF_Base64GIF	= 3
    } 	InkPersistenceFormat;

#define IPF_Last     IPF_Base64GIF + 1 
typedef /* [helpcontext][helpstring] */ 
enum InkPersistenceCompressionMode
    {	IPCM_Default	= 0,
	IPCM_MaximumCompression	= 1,
	IPCM_NoCompression	= 2
    } 	InkPersistenceCompressionMode;

typedef /* [helpcontext][helpstring] */ 
enum InkPenTip
    {	IPT_Ball	= 0,
	IPT_Rectangle	= 1
    } 	InkPenTip;

#define IPT_Last     IPT_Rectangle + 1 
typedef /* [helpcontext][helpstring] */ 
enum InkRasterOperation
    {	IRO_Black	= 1,
	IRO_NotMergePen	= 2,
	IRO_MaskNotPen	= 3,
	IRO_NotCopyPen	= 4,
	IRO_MaskPenNot	= 5,
	IRO_Not	= 6,
	IRO_XOrPen	= 7,
	IRO_NotMaskPen	= 8,
	IRO_MaskPen	= 9,
	IRO_NotXOrPen	= 10,
	IRO_NoOperation	= 11,
	IRO_MergeNotPen	= 12,
	IRO_CopyPen	= 13,
	IRO_MergePenNot	= 14,
	IRO_MergePen	= 15,
	IRO_White	= 16
    } 	InkRasterOperation;

#define IRO_Last IRO_White+1
typedef /* [helpcontext][helpstring] */ 
enum InkMousePointer
    {	IMP_Default	= 0,
	IMP_Arrow	= 1,
	IMP_Crosshair	= 2,
	IMP_Ibeam	= 3,
	IMP_SizeNESW	= 4,
	IMP_SizeNS	= 5,
	IMP_SizeNWSE	= 6,
	IMP_SizeWE	= 7,
	IMP_UpArrow	= 8,
	IMP_Hourglass	= 9,
	IMP_NoDrop	= 10,
	IMP_ArrowHourglass	= 11,
	IMP_ArrowQuestion	= 12,
	IMP_SizeAll	= 13,
	IMP_Hand	= 14,
	IMP_Custom	= 99
    } 	InkMousePointer;

typedef /* [helpcontext][helpstring] */ 
enum InkClipboardModes
    {	ICB_Copy	= 0,
	ICB_Cut	= 0x1,
	ICB_ExtractOnly	= 0x30,
	ICB_DelayedCopy	= 0x20,
	ICB_Default	= ICB_Copy
    } 	InkClipboardModes;

#define ICB_Last ICB_DelayedCopy+1
typedef /* [helpcontext][helpstring] */ 
enum InkClipboardFormats
    {	ICF_None	= 0,
	ICF_InkSerializedFormat	= 0x1,
	ICF_SketchInk	= 0x2,
	ICF_TextInk	= 0x6,
	ICF_EnhancedMetafile	= 0x8,
	ICF_Metafile	= 0x20,
	ICF_Bitmap	= 0x40,
	ICF_PasteMask	= 0x7,
	ICF_CopyMask	= 0x7f,
	ICF_Default	= ICF_CopyMask
    } 	InkClipboardFormats;

#define ICF_Last ICF_CopyMask+1
typedef /* [helpcontext][helpstring] */ 
enum SelectionHitResult
    {	SHR_None	= 0,
	SHR_NW	= SHR_None + 1,
	SHR_SE	= SHR_NW + 1,
	SHR_NE	= SHR_SE + 1,
	SHR_SW	= SHR_NE + 1,
	SHR_E	= SHR_SW + 1,
	SHR_W	= SHR_E + 1,
	SHR_N	= SHR_W + 1,
	SHR_S	= SHR_N + 1,
	SHR_Selection	= SHR_S + 1
    } 	SelectionHitResult;

typedef /* [helpcontext][helpstring] */ 
enum InkRecognitionStatus
    {	IRS_NoError	= 0,
	IRS_Interrupted	= 0x1,
	IRS_ProcessFailed	= 0x2,
	IRS_InkAddedFailed	= 0x4,
	IRS_SetAutoCompletionModeFailed	= 0x8,
	IRS_SetStrokesFailed	= 0x10,
	IRS_SetGuideFailed	= 0x20,
	IRS_SetFlagsFailed	= 0x40,
	IRS_SetFactoidFailed	= 0x80,
	IRS_SetPrefixSuffixFailed	= 0x100,
	IRS_SetWordListFailed	= 0x200
    } 	InkRecognitionStatus;

typedef /* [hidden] */ 
enum DISPID_InkRectangle
    {	DISPID_IRTop	= 1,
	DISPID_IRLeft	= DISPID_IRTop + 1,
	DISPID_IRBottom	= DISPID_IRLeft + 1,
	DISPID_IRRight	= DISPID_IRBottom + 1,
	DISPID_IRGetRectangle	= DISPID_IRRight + 1,
	DISPID_IRSetRectangle	= DISPID_IRGetRectangle + 1,
	DISPID_IRData	= DISPID_IRSetRectangle + 1
    } 	DISPID_InkRectangle;

typedef /* [hidden] */ 
enum DISPID_InkExtendedProperty
    {	DISPID_IEPGuid	= 1,
	DISPID_IEPData	= DISPID_IEPGuid + 1
    } 	DISPID_InkExtendedProperty;

typedef /* [hidden] */ 
enum DISPID_InkExtendedProperties
    {	DISPID_IEPs_NewEnum	= DISPID_NEWENUM,
	DISPID_IEPsItem	= DISPID_VALUE,
	DISPID_IEPsCount	= 1,
	DISPID_IEPsAdd	= DISPID_IEPsCount + 1,
	DISPID_IEPsRemove	= DISPID_IEPsAdd + 1,
	DISPID_IEPsClear	= DISPID_IEPsRemove + 1,
	DISPID_IEPsDoesPropertyExist	= DISPID_IEPsClear + 1
    } 	DISPID_InkExtendedProperties;

typedef /* [hidden] */ 
enum DISPID_InkDrawingAttributes
    {	DISPID_DAHeight	= 1,
	DISPID_DAColor	= DISPID_DAHeight + 1,
	DISPID_DAWidth	= DISPID_DAColor + 1,
	DISPID_DAFitToCurve	= DISPID_DAWidth + 1,
	DISPID_DAIgnorePressure	= DISPID_DAFitToCurve + 1,
	DISPID_DAAntiAliased	= DISPID_DAIgnorePressure + 1,
	DISPID_DATransparency	= DISPID_DAAntiAliased + 1,
	DISPID_DARasterOperation	= DISPID_DATransparency + 1,
	DISPID_DAPenTip	= DISPID_DARasterOperation + 1,
	DISPID_DAClone	= DISPID_DAPenTip + 1,
	DISPID_DAExtendedProperties	= DISPID_DAClone + 1
    } 	DISPID_InkDrawingAttributes;

typedef /* [hidden] */ 
enum DISPID_InkTransform
    {	DISPID_ITReset	= 1,
	DISPID_ITTranslate	= DISPID_ITReset + 1,
	DISPID_ITRotate	= DISPID_ITTranslate + 1,
	DISPID_ITReflect	= DISPID_ITRotate + 1,
	DISPID_ITShear	= DISPID_ITReflect + 1,
	DISPID_ITScale	= DISPID_ITShear + 1,
	DISPID_ITeM11	= DISPID_ITScale + 1,
	DISPID_ITeM12	= DISPID_ITeM11 + 1,
	DISPID_ITeM21	= DISPID_ITeM12 + 1,
	DISPID_ITeM22	= DISPID_ITeM21 + 1,
	DISPID_ITeDx	= DISPID_ITeM22 + 1,
	DISPID_ITeDy	= DISPID_ITeDx + 1,
	DISPID_ITGetTransform	= DISPID_ITeDy + 1,
	DISPID_ITSetTransform	= DISPID_ITGetTransform + 1,
	DISPID_ITData	= DISPID_ITSetTransform + 1
    } 	DISPID_InkTransform;

typedef 
enum InkApplicationGesture
    {	IAG_AllGestures	= 0,
	IAG_NoGesture	= 0xf000,
	IAG_Scratchout	= 0xf001,
	IAG_Triangle	= 0xf002,
	IAG_Square	= 0xf003,
	IAG_Star	= 0xf004,
	IAG_Check	= 0xf005,
	IAG_Curlicue	= 0xf010,
	IAG_DoubleCurlicue	= 0xf011,
	IAG_Circle	= 0xf020,
	IAG_DoubleCircle	= 0xf021,
	IAG_SemiCircleLeft	= 0xf028,
	IAG_SemiCircleRight	= 0xf029,
	IAG_ChevronUp	= 0xf030,
	IAG_ChevronDown	= 0xf031,
	IAG_ChevronLeft	= 0xf032,
	IAG_ChevronRight	= 0xf033,
	IAG_ArrowUp	= 0xf038,
	IAG_ArrowDown	= 0xf039,
	IAG_ArrowLeft	= 0xf03a,
	IAG_ArrowRight	= 0xf03b,
	IAG_Up	= 0xf058,
	IAG_Down	= 0xf059,
	IAG_Left	= 0xf05a,
	IAG_Right	= 0xf05b,
	IAG_UpDown	= 0xf060,
	IAG_DownUp	= 0xf061,
	IAG_LeftRight	= 0xf062,
	IAG_RightLeft	= 0xf063,
	IAG_UpLeftLong	= 0xf064,
	IAG_UpRightLong	= 0xf065,
	IAG_DownLeftLong	= 0xf066,
	IAG_DownRightLong	= 0xf067,
	IAG_UpLeft	= 0xf068,
	IAG_UpRight	= 0xf069,
	IAG_DownLeft	= 0xf06a,
	IAG_DownRight	= 0xf06b,
	IAG_LeftUp	= 0xf06c,
	IAG_LeftDown	= 0xf06d,
	IAG_RightUp	= 0xf06e,
	IAG_RightDown	= 0xf06f,
	IAG_Exclamation	= 0xf0a4,
	IAG_Tap	= 0xf0f0,
	IAG_DoubleTap	= 0xf0f1
    } 	InkApplicationGesture;

typedef 
enum InkSystemGesture
    {	ISG_Tap	= 0x10,
	ISG_DoubleTap	= 0x11,
	ISG_RightTap	= 0x12,
	ISG_Drag	= 0x13,
	ISG_RightDrag	= 0x14,
	ISG_HoldEnter	= 0x15,
	ISG_HoldLeave	= 0x16,
	ISG_HoverEnter	= 0x17,
	ISG_HoverLeave	= 0x18
    } 	InkSystemGesture;

#define ISG_First ISG_Tap
#define ISG_Last ISG_HoverLeave
typedef 
enum InkRecognitionConfidence
    {	IRC_Strong	= 0,
	IRC_Intermediate	= 1,
	IRC_Poor	= 2
    } 	InkRecognitionConfidence;

typedef /* [hidden] */ 
enum DISPID_InkGesture
    {	DISPID_IGId	= DISPID_VALUE,
	DISPID_IGGetHotPoint	= DISPID_IGId + 1,
	DISPID_IGConfidence	= DISPID_IGGetHotPoint + 1
    } 	DISPID_InkGesture;

typedef /* [hidden] */ 
enum DISPID_InkCursor
    {	DISPID_ICsrName	= DISPID_VALUE,
	DISPID_ICsrId	= 1,
	DISPID_ICsrDrawingAttributes	= DISPID_ICsrId + 1,
	DISPID_ICsrButtons	= DISPID_ICsrDrawingAttributes + 1,
	DISPID_ICsrInverted	= DISPID_ICsrButtons + 1,
	DISPID_ICsrTablet	= DISPID_ICsrInverted + 1
    } 	DISPID_InkCursor;

typedef /* [hidden] */ 
enum DISPID_InkCursors
    {	DISPID_ICs_NewEnum	= DISPID_NEWENUM,
	DISPID_ICsItem	= DISPID_VALUE,
	DISPID_ICsCount	= 1
    } 	DISPID_InkCursors;

typedef 
enum InkCursorButtonState
    {	ICBS_Unavailable	= 0,
	ICBS_Up	= ICBS_Unavailable + 1,
	ICBS_Down	= ICBS_Up + 1
    } 	InkCursorButtonState;

#define ICBS_Last ICBS_Down
typedef /* [hidden] */ 
enum DISPID_InkCursorButton
    {	DISPID_ICBName	= DISPID_VALUE,
	DISPID_ICBId	= 1,
	DISPID_ICBState	= DISPID_ICBId + 1
    } 	DISPID_InkCursorButton;

typedef /* [hidden] */ 
enum DISPID_InkCursorButtons
    {	DISPID_ICBs_NewEnum	= DISPID_NEWENUM,
	DISPID_ICBsItem	= DISPID_VALUE,
	DISPID_ICBsCount	= 1
    } 	DISPID_InkCursorButtons;

typedef 
enum TabletHardwareCapabilities
    {	THWC_Integrated	= 0x1,
	THWC_CursorMustTouch	= 0x2,
	THWC_HardProximity	= 0x4,
	THWC_CursorsHavePhysicalIds	= 0x8
    } 	TabletHardwareCapabilities;

typedef 
enum TabletPropertyMetricUnit
    {	TPMU_Default	= 0,
	TPMU_Inches	= TPMU_Default + 1,
	TPMU_Centimeters	= TPMU_Inches + 1,
	TPMU_Degrees	= TPMU_Centimeters + 1,
	TPMU_Radians	= TPMU_Degrees + 1,
	TPMU_Seconds	= TPMU_Radians + 1,
	TPMU_Pounds	= TPMU_Seconds + 1,
	TPMU_Grams	= TPMU_Pounds + 1
    } 	TabletPropertyMetricUnit;

typedef /* [hidden] */ 
enum DISPID_InkTablet
    {	DISPID_ITName	= DISPID_VALUE,
	DISPID_ITPlugAndPlayId	= 1,
	DISPID_ITPropertyMetrics	= DISPID_ITPlugAndPlayId + 1,
	DISPID_ITIsPacketPropertySupported	= DISPID_ITPropertyMetrics + 1,
	DISPID_ITMaximumInputRectangle	= DISPID_ITIsPacketPropertySupported + 1,
	DISPID_ITHardwareCapabilities	= DISPID_ITMaximumInputRectangle + 1
    } 	DISPID_InkTablet;

typedef /* [hidden] */ 
enum DISPID_InkTablets
    {	DISPID_ITs_NewEnum	= DISPID_NEWENUM,
	DISPID_ITsItem	= DISPID_VALUE,
	DISPID_ITsDefaultTablet	= 1,
	DISPID_ITsCount	= DISPID_ITsDefaultTablet + 1,
	DISPID_ITsIsPacketPropertySupported	= DISPID_ITsCount + 1
    } 	DISPID_InkTablets;

typedef /* [hidden] */ 
enum DISPID_InkStrokeDisp
    {	DISPID_ISDInkIndex	= 1,
	DISPID_ISDID	= DISPID_ISDInkIndex + 1,
	DISPID_ISDGetBoundingBox	= DISPID_ISDID + 1,
	DISPID_ISDDrawingAttributes	= DISPID_ISDGetBoundingBox + 1,
	DISPID_ISDFindIntersections	= DISPID_ISDDrawingAttributes + 1,
	DISPID_ISDGetRectangleIntersections	= DISPID_ISDFindIntersections + 1,
	DISPID_ISDClip	= DISPID_ISDGetRectangleIntersections + 1,
	DISPID_ISDHitTestCircle	= DISPID_ISDClip + 1,
	DISPID_ISDNearestPoint	= DISPID_ISDHitTestCircle + 1,
	DISPID_ISDSplit	= DISPID_ISDNearestPoint + 1,
	DISPID_ISDExtendedProperties	= DISPID_ISDSplit + 1,
	DISPID_ISDInk	= DISPID_ISDExtendedProperties + 1,
	DISPID_ISDBezierPoints	= DISPID_ISDInk + 1,
	DISPID_ISDPolylineCusps	= DISPID_ISDBezierPoints + 1,
	DISPID_ISDBezierCusps	= DISPID_ISDPolylineCusps + 1,
	DISPID_ISDSelfIntersections	= DISPID_ISDBezierCusps + 1,
	DISPID_ISDPacketCount	= DISPID_ISDSelfIntersections + 1,
	DISPID_ISDPacketSize	= DISPID_ISDPacketCount + 1,
	DISPID_ISDPacketDescription	= DISPID_ISDPacketSize + 1,
	DISPID_ISDDeleted	= DISPID_ISDPacketDescription + 1,
	DISPID_ISDGetPacketDescriptionPropertyMetrics	= DISPID_ISDDeleted + 1,
	DISPID_ISDGetPoints	= DISPID_ISDGetPacketDescriptionPropertyMetrics + 1,
	DISPID_ISDSetPoints	= DISPID_ISDGetPoints + 1,
	DISPID_ISDGetPacketData	= DISPID_ISDSetPoints + 1,
	DISPID_ISDGetPacketValuesByProperty	= DISPID_ISDGetPacketData + 1,
	DISPID_ISDSetPacketValuesByProperty	= DISPID_ISDGetPacketValuesByProperty + 1,
	DISPID_ISDGetFlattenedBezierPoints	= DISPID_ISDSetPacketValuesByProperty + 1,
	DISPID_ISDScaleToRectangle	= DISPID_ISDGetFlattenedBezierPoints + 1,
	DISPID_ISDTransform	= DISPID_ISDScaleToRectangle + 1,
	DISPID_ISDMove	= DISPID_ISDTransform + 1,
	DISPID_ISDRotate	= DISPID_ISDMove + 1,
	DISPID_ISDShear	= DISPID_ISDRotate + 1,
	DISPID_ISDScale	= DISPID_ISDShear + 1
    } 	DISPID_InkStrokeDisp;

typedef /* [hidden] */ 
enum DISPID_InkStrokes
    {	DISPID_ISs_NewEnum	= DISPID_NEWENUM,
	DISPID_ISsItem	= DISPID_VALUE,
	DISPID_ISsCount	= 1,
	DISPID_ISsValid	= DISPID_ISsCount + 1,
	DISPID_ISsInk	= DISPID_ISsValid + 1,
	DISPID_ISsAdd	= DISPID_ISsInk + 1,
	DISPID_ISsAddStrokes	= DISPID_ISsAdd + 1,
	DISPID_ISsRemove	= DISPID_ISsAddStrokes + 1,
	DISPID_ISsRemoveStrokes	= DISPID_ISsRemove + 1,
	DISPID_ISsToString	= DISPID_ISsRemoveStrokes + 1,
	DISPID_ISsModifyDrawingAttributes	= DISPID_ISsToString + 1,
	DISPID_ISsGetBoundingBox	= DISPID_ISsModifyDrawingAttributes + 1,
	DISPID_ISsScaleToRectangle	= DISPID_ISsGetBoundingBox + 1,
	DISPID_ISsTransform	= DISPID_ISsScaleToRectangle + 1,
	DISPID_ISsMove	= DISPID_ISsTransform + 1,
	DISPID_ISsRotate	= DISPID_ISsMove + 1,
	DISPID_ISsShear	= DISPID_ISsRotate + 1,
	DISPID_ISsScale	= DISPID_ISsShear + 1,
	DISPID_ISsClip	= DISPID_ISsScale + 1,
	DISPID_ISsRecognitionResult	= DISPID_ISsClip + 1,
	DISPID_ISsRemoveRecognitionResult	= DISPID_ISsRecognitionResult + 1
    } 	DISPID_InkStrokes;

typedef /* [hidden] */ 
enum DISPID_InkCustomStrokes
    {	DISPID_ICSs_NewEnum	= DISPID_NEWENUM,
	DISPID_ICSsItem	= DISPID_VALUE,
	DISPID_ICSsCount	= 1,
	DISPID_ICSsAdd	= DISPID_ICSsCount + 1,
	DISPID_ICSsRemove	= DISPID_ICSsAdd + 1,
	DISPID_ICSsClear	= DISPID_ICSsRemove + 1
    } 	DISPID_InkCustomStrokes;

typedef /* [hidden] */ 
enum DISPID_StrokeEvent
    {	DISPID_SEStrokesAdded	= 1,
	DISPID_SEStrokesRemoved	= DISPID_SEStrokesAdded + 1
    } 	DISPID_StrokeEvent;

typedef /* [hidden] */ 
enum DISPID_Ink
    {	DISPID_IStrokes	= 1,
	DISPID_IExtendedProperties	= DISPID_IStrokes + 1,
	DISPID_IGetBoundingBox	= DISPID_IExtendedProperties + 1,
	DISPID_IDeleteStrokes	= DISPID_IGetBoundingBox + 1,
	DISPID_IDeleteStroke	= DISPID_IDeleteStrokes + 1,
	DISPID_IExtractStrokes	= DISPID_IDeleteStroke + 1,
	DISPID_IExtractWithRectangle	= DISPID_IExtractStrokes + 1,
	DISPID_IDirty	= DISPID_IExtractWithRectangle + 1,
	DISPID_ICustomStrokes	= DISPID_IDirty + 1,
	DISPID_IClone	= DISPID_ICustomStrokes + 1,
	DISPID_IHitTestCircle	= DISPID_IClone + 1,
	DISPID_IHitTestWithRectangle	= DISPID_IHitTestCircle + 1,
	DISPID_IHitTestWithLasso	= DISPID_IHitTestWithRectangle + 1,
	DISPID_INearestPoint	= DISPID_IHitTestWithLasso + 1,
	DISPID_ICreateStrokes	= DISPID_INearestPoint + 1,
	DISPID_ICreateStroke	= DISPID_ICreateStrokes + 1,
	DISPID_IAddStrokesAtRectangle	= DISPID_ICreateStroke + 1,
	DISPID_IClip	= DISPID_IAddStrokesAtRectangle + 1,
	DISPID_ISave	= DISPID_IClip + 1,
	DISPID_ILoad	= DISPID_ISave + 1,
	DISPID_ICreateStrokeFromPoints	= DISPID_ILoad + 1,
	DISPID_IClipboardCopyWithRectangle	= DISPID_ICreateStrokeFromPoints + 1,
	DISPID_IClipboardCopy	= DISPID_IClipboardCopyWithRectangle + 1,
	DISPID_ICanPaste	= DISPID_IClipboardCopy + 1,
	DISPID_IClipboardPaste	= DISPID_ICanPaste + 1
    } 	DISPID_Ink;

typedef /* [hidden] */ 
enum DISPID_InkEvent
    {	DISPID_IEInkAdded	= 1,
	DISPID_IEInkDeleted	= DISPID_IEInkAdded + 1
    } 	DISPID_InkEvent;

typedef /* [hidden] */ 
enum DISPID_InkRenderer
    {	DISPID_IRGetViewTransform	= 1,
	DISPID_IRSetViewTransform	= DISPID_IRGetViewTransform + 1,
	DISPID_IRGetObjectTransform	= DISPID_IRSetViewTransform + 1,
	DISPID_IRSetObjectTransform	= DISPID_IRGetObjectTransform + 1,
	DISPID_IRDraw	= DISPID_IRSetObjectTransform + 1,
	DISPID_IRDrawStroke	= DISPID_IRDraw + 1,
	DISPID_IRPixelToInkSpace	= DISPID_IRDrawStroke + 1,
	DISPID_IRInkSpaceToPixel	= DISPID_IRPixelToInkSpace + 1,
	DISPID_IRPixelToInkSpaceFromPoints	= DISPID_IRInkSpaceToPixel + 1,
	DISPID_IRInkSpaceToPixelFromPoints	= DISPID_IRPixelToInkSpaceFromPoints + 1,
	DISPID_IRMeasure	= DISPID_IRInkSpaceToPixelFromPoints + 1,
	DISPID_IRMeasureStroke	= DISPID_IRMeasure + 1,
	DISPID_IRMove	= DISPID_IRMeasureStroke + 1,
	DISPID_IRRotate	= DISPID_IRMove + 1,
	DISPID_IRScale	= DISPID_IRRotate + 1
    } 	DISPID_InkRenderer;

typedef 
enum InkCollectorEventInterest
    {	ICEI_DefaultEvents	= -1,
	ICEI_CursorDown	= ICEI_DefaultEvents + 1,
	ICEI_Stroke	= ICEI_CursorDown + 1,
	ICEI_NewPackets	= ICEI_Stroke + 1,
	ICEI_NewInAirPackets	= ICEI_NewPackets + 1,
	ICEI_CursorButtonDown	= ICEI_NewInAirPackets + 1,
	ICEI_CursorButtonUp	= ICEI_CursorButtonDown + 1,
	ICEI_CursorInRange	= ICEI_CursorButtonUp + 1,
	ICEI_CursorOutOfRange	= ICEI_CursorInRange + 1,
	ICEI_SystemGesture	= ICEI_CursorOutOfRange + 1,
	ICEI_TabletAdded	= ICEI_SystemGesture + 1,
	ICEI_TabletRemoved	= ICEI_TabletAdded + 1,
	ICEI_MouseDown	= ICEI_TabletRemoved + 1,
	ICEI_MouseMove	= ICEI_MouseDown + 1,
	ICEI_MouseUp	= ICEI_MouseMove + 1,
	ICEI_MouseWheel	= ICEI_MouseUp + 1,
	ICEI_DblClick	= ICEI_MouseWheel + 1,
	ICEI_AllEvents	= ICEI_DblClick + 1
    } 	InkCollectorEventInterest;

typedef 
enum InkMouseButton
    {	IMF_Left	= 1,
	IMF_Right	= 2,
	IMF_Middle	= 4
    } 	InkMouseButton;

typedef 
enum InkShiftKeyModifierFlags
    {	IKM_Shift	= 0x1,
	IKM_Control	= 0x2,
	IKM_Alt	= 0x4
    } 	InkShiftKeyModifierFlags;

typedef /* [hidden] */ 
enum DISPID_InkCollectorEvent
    {	DISPID_ICEStroke	= 1,
	DISPID_ICECursorDown	= DISPID_ICEStroke + 1,
	DISPID_ICENewPackets	= DISPID_ICECursorDown + 1,
	DISPID_ICENewInAirPackets	= DISPID_ICENewPackets + 1,
	DISPID_ICECursorButtonDown	= DISPID_ICENewInAirPackets + 1,
	DISPID_ICECursorButtonUp	= DISPID_ICECursorButtonDown + 1,
	DISPID_ICECursorInRange	= DISPID_ICECursorButtonUp + 1,
	DISPID_ICECursorOutOfRange	= DISPID_ICECursorInRange + 1,
	DISPID_ICESystemGesture	= DISPID_ICECursorOutOfRange + 1,
	DISPID_ICEGesture	= DISPID_ICESystemGesture + 1,
	DISPID_ICETabletAdded	= DISPID_ICEGesture + 1,
	DISPID_ICETabletRemoved	= DISPID_ICETabletAdded + 1,
	DISPID_IOEPainting	= DISPID_ICETabletRemoved + 1,
	DISPID_IOEPainted	= DISPID_IOEPainting + 1,
	DISPID_IOESelectionChanging	= DISPID_IOEPainted + 1,
	DISPID_IOESelectionChanged	= DISPID_IOESelectionChanging + 1,
	DISPID_IOESelectionMoving	= DISPID_IOESelectionChanged + 1,
	DISPID_IOESelectionMoved	= DISPID_IOESelectionMoving + 1,
	DISPID_IOESelectionResizing	= DISPID_IOESelectionMoved + 1,
	DISPID_IOESelectionResized	= DISPID_IOESelectionResizing + 1,
	DISPID_IOEStrokesDeleting	= DISPID_IOESelectionResized + 1,
	DISPID_IOEStrokesDeleted	= DISPID_IOEStrokesDeleting + 1,
	DISPID_IPEChangeUICues	= DISPID_IOEStrokesDeleted + 1,
	DISPID_IPEClick	= DISPID_IPEChangeUICues + 1,
	DISPID_IPEDblClick	= DISPID_IPEClick + 1,
	DISPID_IPEInvalidated	= DISPID_IPEDblClick + 1,
	DISPID_IPEMouseDown	= DISPID_IPEInvalidated + 1,
	DISPID_IPEMouseEnter	= DISPID_IPEMouseDown + 1,
	DISPID_IPEMouseHover	= DISPID_IPEMouseEnter + 1,
	DISPID_IPEMouseLeave	= DISPID_IPEMouseHover + 1,
	DISPID_IPEMouseMove	= DISPID_IPEMouseLeave + 1,
	DISPID_IPEMouseUp	= DISPID_IPEMouseMove + 1,
	DISPID_IPEMouseWheel	= DISPID_IPEMouseUp + 1,
	DISPID_IPESizeModeChanged	= DISPID_IPEMouseWheel + 1,
	DISPID_IPEStyleChanged	= DISPID_IPESizeModeChanged + 1,
	DISPID_IPESystemColorsChanged	= DISPID_IPEStyleChanged + 1,
	DISPID_IPEKeyDown	= DISPID_IPESystemColorsChanged + 1,
	DISPID_IPEKeyPress	= DISPID_IPEKeyDown + 1,
	DISPID_IPEKeyUp	= DISPID_IPEKeyPress + 1,
	DISPID_IPEResize	= DISPID_IPEKeyUp + 1,
	DISPID_IPESizeChanged	= DISPID_IPEResize + 1
    } 	DISPID_InkCollectorEvent;

typedef /* [helpcontext][helpstring] */ 
enum InkOverlayEditingMode
    {	IOEM_Ink	= 0,
	IOEM_Delete	= 1,
	IOEM_Select	= 2
    } 	InkOverlayEditingMode;

#define IOEM_Last IOEM_Select + 1
typedef /* [helpcontext][helpstring] */ 
enum InkOverlayAttachMode
    {	IOAM_Behind	= 0,
	IOAM_InFront	= 1
    } 	InkOverlayAttachMode;

#define IOAM_Last IOAM_InFront+1
typedef /* [helpcontext][helpstring] */ 
enum InkPictureSizeMode
    {	IPSM_AutoSize	= 0,
	IPSM_CenterImage	= 1,
	IPSM_Normal	= 2,
	IPSM_StretchImage	= 3
    } 	InkPictureSizeMode;

#define IPSM_Last IPSM_StretchImage + 1
typedef /* [helpcontext][helpstring] */ 
enum InkOverlayEraserMode
    {	IOERM_StrokeErase	= 0,
	IOERM_PointErase	= 1
    } 	InkOverlayEraserMode;

#define IOERM_Last IOERM_PointErase + 1
typedef 
enum InkCollectionMode
    {	ICM_InkOnly	= 0,
	ICM_GestureOnly	= ICM_InkOnly + 1,
	ICM_InkAndGesture	= ICM_GestureOnly + 1
    } 	InkCollectionMode;

#define ICM_Last ICM_InkAndGesture
typedef /* [hidden] */ 
enum DISPID_InkCollector
    {	DISPID_ICEnabled	= 1,
	DISPID_ICHwnd	= DISPID_ICEnabled + 1,
	DISPID_ICPaint	= DISPID_ICHwnd + 1,
	DISPID_ICText	= DISPID_ICPaint + 1,
	DISPID_ICDefaultDrawingAttributes	= DISPID_ICText + 1,
	DISPID_ICRenderer	= DISPID_ICDefaultDrawingAttributes + 1,
	DISPID_ICInk	= DISPID_ICRenderer + 1,
	DISPID_ICAutoRedraw	= DISPID_ICInk + 1,
	DISPID_ICCollectingInk	= DISPID_ICAutoRedraw + 1,
	DISPID_ICSetEventInterest	= DISPID_ICCollectingInk + 1,
	DISPID_ICGetEventInterest	= DISPID_ICSetEventInterest + 1,
	DISPID_IOEditingMode	= DISPID_ICGetEventInterest + 1,
	DISPID_IOSelection	= DISPID_IOEditingMode + 1,
	DISPID_IOAttachMode	= DISPID_IOSelection + 1,
	DISPID_IOHitTestSelection	= DISPID_IOAttachMode + 1,
	DISPID_IODraw	= DISPID_IOHitTestSelection + 1,
	DISPID_IPPicture	= DISPID_IODraw + 1,
	DISPID_IPSizeMode	= DISPID_IPPicture + 1,
	DISPID_IPBackColor	= DISPID_IPSizeMode + 1,
	DISPID_ICCursors	= DISPID_IPBackColor + 1,
	DISPID_ICMarginX	= DISPID_ICCursors + 1,
	DISPID_ICMarginY	= DISPID_ICMarginX + 1,
	DISPID_ICSetWindowInputRectangle	= DISPID_ICMarginY + 1,
	DISPID_ICGetWindowInputRectangle	= DISPID_ICSetWindowInputRectangle + 1,
	DISPID_ICTablet	= DISPID_ICGetWindowInputRectangle + 1,
	DISPID_ICSetAllTabletsMode	= DISPID_ICTablet + 1,
	DISPID_ICSetSingleTabletIntegratedMode	= DISPID_ICSetAllTabletsMode + 1,
	DISPID_ICCollectionMode	= DISPID_ICSetSingleTabletIntegratedMode + 1,
	DISPID_ICSetGestureStatus	= DISPID_ICCollectionMode + 1,
	DISPID_ICGetGestureStatus	= DISPID_ICSetGestureStatus + 1,
	DISPID_ICDynamicRendering	= DISPID_ICGetGestureStatus + 1,
	DISPID_ICDesiredPacketDescription	= DISPID_ICDynamicRendering + 1,
	DISPID_IOEraserMode	= DISPID_ICDesiredPacketDescription + 1,
	DISPID_IOEraserWidth	= DISPID_IOEraserMode + 1,
	DISPID_ICMouseIcon	= DISPID_IOEraserWidth + 1,
	DISPID_ICMousePointer	= DISPID_ICMouseIcon + 1,
	DISPID_IPInkEnabled	= DISPID_ICMousePointer + 1,
	DISPID_ICSupportHighContrastInk	= DISPID_IPInkEnabled + 1,
	DISPID_IOSupportHighContrastSelectionUI	= DISPID_ICSupportHighContrastInk + 1
    } 	DISPID_InkCollector;

typedef /* [hidden] */ 
enum DISPID_InkRecognizer
    {	DISPID_RecoClsid	= 1,
	DISPID_RecoName	= DISPID_RecoClsid + 1,
	DISPID_RecoVendor	= DISPID_RecoName + 1,
	DISPID_RecoCapabilities	= DISPID_RecoVendor + 1,
	DISPID_RecoLanguageID	= DISPID_RecoCapabilities + 1,
	DISPID_RecoPreferredPacketDescription	= DISPID_RecoLanguageID + 1,
	DISPID_RecoCreateRecognizerContext	= DISPID_RecoPreferredPacketDescription + 1,
	DISPID_RecoSupportedProperties	= DISPID_RecoCreateRecognizerContext + 1
    } 	DISPID_InkRecognizer;

typedef 
enum InkRecognizerCapabilities
    {	IRC_DontCare	= 1,
	IRC_Object	= 2,
	IRC_FreeInput	= 4,
	IRC_LinedInput	= 8,
	IRC_BoxedInput	= 16,
	IRC_CharacterAutoCompletionInput	= 32,
	IRC_RightAndDown	= 64,
	IRC_LeftAndDown	= 128,
	IRC_DownAndLeft	= 256,
	IRC_DownAndRight	= 512,
	IRC_ArbitraryAngle	= 1024,
	IRC_Lattice	= 2048,
	IRC_AdviseInkChange	= 4096,
	IRC_StrokeReorder	= 8192
    } 	InkRecognizerCapabilities;

typedef /* [hidden] */ 
enum DISPID_InkRecognizers
    {	DISPID_IRecos_NewEnum	= DISPID_NEWENUM,
	DISPID_IRecosItem	= DISPID_VALUE,
	DISPID_IRecosCount	= 1,
	DISPID_IRecosGetDefaultRecognizer	= DISPID_IRecosCount + 1
    } 	DISPID_InkRecognizers;

typedef 
enum InkRecognizerCharacterAutoCompletionMode
    {	IRCACM_Full	= 0,
	IRCACM_Prefix	= IRCACM_Full + 1,
	IRCACM_Random	= IRCACM_Prefix + 1
    } 	InkRecognizerCharacterAutoCompletionMode;

typedef 
enum InkRecognitionModes
    {	IRM_None	= 0,
	IRM_WordModeOnly	= 1,
	IRM_Coerce	= 2,
	IRM_TopInkBreaksOnly	= 4,
	IRM_Max	= 8
    } 	InkRecognitionModes;

typedef /* [hidden] */ 
enum DISPID_InkRecognitionEvent
    {	DISPID_IRERecognitionWithAlternates	= 1,
	DISPID_IRERecognition	= DISPID_IRERecognitionWithAlternates + 1
    } 	DISPID_InkRecognitionEvent;

typedef /* [hidden] */ 
enum DISPID_InkRecoContext
    {	DISPID_IRecoCtx_Strokes	= 1,
	DISPID_IRecoCtx_CharacterAutoCompletionMode	= DISPID_IRecoCtx_Strokes + 1,
	DISPID_IRecoCtx_Factoid	= DISPID_IRecoCtx_CharacterAutoCompletionMode + 1,
	DISPID_IRecoCtx_WordList	= DISPID_IRecoCtx_Factoid + 1,
	DISPID_IRecoCtx_Recognizer	= DISPID_IRecoCtx_WordList + 1,
	DISPID_IRecoCtx_Guide	= DISPID_IRecoCtx_Recognizer + 1,
	DISPID_IRecoCtx_Flags	= DISPID_IRecoCtx_Guide + 1,
	DISPID_IRecoCtx_PrefixText	= DISPID_IRecoCtx_Flags + 1,
	DISPID_IRecoCtx_SuffixText	= DISPID_IRecoCtx_PrefixText + 1,
	DISPID_IRecoCtx_StopRecognition	= DISPID_IRecoCtx_SuffixText + 1,
	DISPID_IRecoCtx_Clone	= DISPID_IRecoCtx_StopRecognition + 1,
	DISPID_IRecoCtx_Recognize	= DISPID_IRecoCtx_Clone + 1,
	DISPID_IRecoCtx_StopBackgroundRecognition	= DISPID_IRecoCtx_Recognize + 1,
	DISPID_IRecoCtx_EndInkInput	= DISPID_IRecoCtx_StopBackgroundRecognition + 1,
	DISPID_IRecoCtx_BackgroundRecognize	= DISPID_IRecoCtx_EndInkInput + 1,
	DISPID_IRecoCtx_BackgroundRecognizeWithAlternates	= DISPID_IRecoCtx_BackgroundRecognize + 1,
	DISPID_IRecoCtx_IsStringSupported	= DISPID_IRecoCtx_BackgroundRecognizeWithAlternates + 1
    } 	DISPID_InkRecoContext;

typedef /* [helpcontext][helpstring] */ 
enum InkRecognitionAlternatesSelection
    {	IRAS_Start	= 0,
	IRAS_DefaultCount	= 10,
	IRAS_All	= -1
    } 	InkRecognitionAlternatesSelection;

typedef /* [hidden] */ 
enum DISPID_InkRecognitionResult
    {	DISPID_InkRecognitionResult_TopString	= 1,
	DISPID_InkRecognitionResult_TopAlternate	= DISPID_InkRecognitionResult_TopString + 1,
	DISPID_InkRecognitionResult_Strokes	= DISPID_InkRecognitionResult_TopAlternate + 1,
	DISPID_InkRecognitionResult_TopConfidence	= DISPID_InkRecognitionResult_Strokes + 1,
	DISPID_InkRecognitionResult_AlternatesFromSelection	= DISPID_InkRecognitionResult_TopConfidence + 1,
	DISPID_InkRecognitionResult_ModifyTopAlternate	= DISPID_InkRecognitionResult_AlternatesFromSelection + 1,
	DISPID_InkRecognitionResult_SetResultOnStrokes	= DISPID_InkRecognitionResult_ModifyTopAlternate + 1
    } 	DISPID_InkRecognitionResult;

typedef /* [hidden] */ 
enum DISPID_InkRecoAlternate
    {	DISPID_InkRecoAlternate_String	= 1,
	DISPID_InkRecoAlternate_LineNumber	= DISPID_InkRecoAlternate_String + 1,
	DISPID_InkRecoAlternate_Baseline	= DISPID_InkRecoAlternate_LineNumber + 1,
	DISPID_InkRecoAlternate_Midline	= DISPID_InkRecoAlternate_Baseline + 1,
	DISPID_InkRecoAlternate_Ascender	= DISPID_InkRecoAlternate_Midline + 1,
	DISPID_InkRecoAlternate_Descender	= DISPID_InkRecoAlternate_Ascender + 1,
	DISPID_InkRecoAlternate_Confidence	= DISPID_InkRecoAlternate_Descender + 1,
	DISPID_InkRecoAlternate_Strokes	= DISPID_InkRecoAlternate_Confidence + 1,
	DISPID_InkRecoAlternate_GetStrokesFromStrokeRanges	= DISPID_InkRecoAlternate_Strokes + 1,
	DISPID_InkRecoAlternate_GetStrokesFromTextRange	= DISPID_InkRecoAlternate_GetStrokesFromStrokeRanges + 1,
	DISPID_InkRecoAlternate_GetTextRangeFromStrokes	= DISPID_InkRecoAlternate_GetStrokesFromTextRange + 1,
	DISPID_InkRecoAlternate_GetPropertyValue	= DISPID_InkRecoAlternate_GetTextRangeFromStrokes + 1,
	DISPID_InkRecoAlternate_LineAlternates	= DISPID_InkRecoAlternate_GetPropertyValue + 1,
	DISPID_InkRecoAlternate_ConfidenceAlternates	= DISPID_InkRecoAlternate_LineAlternates + 1,
	DISPID_InkRecoAlternate_AlternatesWithConstantPropertyValues	= DISPID_InkRecoAlternate_ConfidenceAlternates + 1
    } 	DISPID_InkRecoAlternate;

typedef /* [hidden] */ 
enum DISPID_InkRecognitionAlternates
    {	DISPID_InkRecognitionAlternates_NewEnum	= DISPID_NEWENUM,
	DISPID_InkRecognitionAlternates_Item	= DISPID_VALUE,
	DISPID_InkRecognitionAlternates_Count	= 1,
	DISPID_InkRecognitionAlternates_Strokes	= DISPID_InkRecognitionAlternates_Count + 1
    } 	DISPID_InkRecognitionAlternates;

typedef /* [hidden] */ struct _InkRecoGuide
    {
    RECT rectWritingBox;
    RECT rectDrawnBox;
    long cRows;
    long cColumns;
    long midline;
    } 	InkRecoGuide;

typedef /* [hidden] */ 
enum DISPID_InkRecognizerGuide
    {	DISPID_IRGWritingBox	= 1,
	DISPID_IRGDrawnBox	= DISPID_IRGWritingBox + 1,
	DISPID_IRGRows	= DISPID_IRGDrawnBox + 1,
	DISPID_IRGColumns	= DISPID_IRGRows + 1,
	DISPID_IRGMidline	= DISPID_IRGColumns + 1,
	DISPID_IRGGuideData	= DISPID_IRGMidline + 1
    } 	DISPID_InkRecognizerGuide;

typedef /* [hidden] */ 
enum DISPID_InkWordList
    {	DISPID_InkWordList_AddWord	= 0,
	DISPID_InkWordList_RemoveWord	= DISPID_InkWordList_AddWord + 1,
	DISPID_InkWordList_Merge	= DISPID_InkWordList_RemoveWord + 1
    } 	DISPID_InkWordList;


EXTERN_C const IID LIBID_MSINKAUTLib;


#ifndef __InkConstants_MODULE_DEFINED__
#define __InkConstants_MODULE_DEFINED__


/* module InkConstants */
/* [uuid] */ 

const LONG InkMinTransparencyValue	=	0;

const LONG InkMaxTransparencyValue	=	255;

#endif /* __InkConstants_MODULE_DEFINED__ */


#ifndef __InkCollectorConstants_MODULE_DEFINED__
#define __InkCollectorConstants_MODULE_DEFINED__


/* module InkCollectorConstants */
/* [uuid] */ 

const LONG InkCollectorClipInkToMargin	=	0;

const LONG InkCollectorDefaultMargin	=	-2147483647L - 1;

#endif /* __InkCollectorConstants_MODULE_DEFINED__ */

#ifndef __IInkRectangle_INTERFACE_DEFINED__
#define __IInkRectangle_INTERFACE_DEFINED__

/* interface IInkRectangle */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRectangle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9794FF82-6071-4717-8A8B-6AC7C64A686E")
    IInkRectangle : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long *Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ long Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long *Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ long Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bottom( 
            /* [retval][out] */ long *Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Bottom( 
            /* [in] */ long Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Right( 
            /* [retval][out] */ long *Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Right( 
            /* [in] */ long Units) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_Data( 
            /* [retval][out] */ RECT *Rect) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_Data( 
            /* [in] */ RECT Rect) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRectangle( 
            /* [out] */ long *Top,
            /* [out] */ long *Left,
            /* [out] */ long *Bottom,
            /* [out] */ long *Right) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRectangle( 
            /* [in] */ long Top,
            /* [in] */ long Left,
            /* [in] */ long Bottom,
            /* [in] */ long Right) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRectangleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkRectangle * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkRectangle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkRectangle * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkRectangle * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkRectangle * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkRectangle * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkRectangle * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Top )( 
            IInkRectangle * This,
            /* [retval][out] */ long *Units);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Top )( 
            IInkRectangle * This,
            /* [in] */ long Units);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Left )( 
            IInkRectangle * This,
            /* [retval][out] */ long *Units);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Left )( 
            IInkRectangle * This,
            /* [in] */ long Units);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bottom )( 
            IInkRectangle * This,
            /* [retval][out] */ long *Units);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Bottom )( 
            IInkRectangle * This,
            /* [in] */ long Units);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Right )( 
            IInkRectangle * This,
            /* [retval][out] */ long *Units);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Right )( 
            IInkRectangle * This,
            /* [in] */ long Units);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Data )( 
            IInkRectangle * This,
            /* [retval][out] */ RECT *Rect);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Data )( 
            IInkRectangle * This,
            /* [in] */ RECT Rect);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRectangle )( 
            IInkRectangle * This,
            /* [out] */ long *Top,
            /* [out] */ long *Left,
            /* [out] */ long *Bottom,
            /* [out] */ long *Right);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRectangle )( 
            IInkRectangle * This,
            /* [in] */ long Top,
            /* [in] */ long Left,
            /* [in] */ long Bottom,
            /* [in] */ long Right);
        
        END_INTERFACE
    } IInkRectangleVtbl;

    interface IInkRectangle
    {
        CONST_VTBL struct IInkRectangleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRectangle_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRectangle_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRectangle_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRectangle_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRectangle_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRectangle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRectangle_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRectangle_get_Top(This,Units)	\
    (This)->lpVtbl -> get_Top(This,Units)

#define IInkRectangle_put_Top(This,Units)	\
    (This)->lpVtbl -> put_Top(This,Units)

#define IInkRectangle_get_Left(This,Units)	\
    (This)->lpVtbl -> get_Left(This,Units)

#define IInkRectangle_put_Left(This,Units)	\
    (This)->lpVtbl -> put_Left(This,Units)

#define IInkRectangle_get_Bottom(This,Units)	\
    (This)->lpVtbl -> get_Bottom(This,Units)

#define IInkRectangle_put_Bottom(This,Units)	\
    (This)->lpVtbl -> put_Bottom(This,Units)

#define IInkRectangle_get_Right(This,Units)	\
    (This)->lpVtbl -> get_Right(This,Units)

#define IInkRectangle_put_Right(This,Units)	\
    (This)->lpVtbl -> put_Right(This,Units)

#define IInkRectangle_get_Data(This,Rect)	\
    (This)->lpVtbl -> get_Data(This,Rect)

#define IInkRectangle_put_Data(This,Rect)	\
    (This)->lpVtbl -> put_Data(This,Rect)

#define IInkRectangle_GetRectangle(This,Top,Left,Bottom,Right)	\
    (This)->lpVtbl -> GetRectangle(This,Top,Left,Bottom,Right)

#define IInkRectangle_SetRectangle(This,Top,Left,Bottom,Right)	\
    (This)->lpVtbl -> SetRectangle(This,Top,Left,Bottom,Right)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRectangle_get_Top_Proxy( 
    IInkRectangle * This,
    /* [retval][out] */ long *Units);


void __RPC_STUB IInkRectangle_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRectangle_put_Top_Proxy( 
    IInkRectangle * This,
    /* [in] */ long Units);


void __RPC_STUB IInkRectangle_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRectangle_get_Left_Proxy( 
    IInkRectangle * This,
    /* [retval][out] */ long *Units);


void __RPC_STUB IInkRectangle_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRectangle_put_Left_Proxy( 
    IInkRectangle * This,
    /* [in] */ long Units);


void __RPC_STUB IInkRectangle_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRectangle_get_Bottom_Proxy( 
    IInkRectangle * This,
    /* [retval][out] */ long *Units);


void __RPC_STUB IInkRectangle_get_Bottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRectangle_put_Bottom_Proxy( 
    IInkRectangle * This,
    /* [in] */ long Units);


void __RPC_STUB IInkRectangle_put_Bottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRectangle_get_Right_Proxy( 
    IInkRectangle * This,
    /* [retval][out] */ long *Units);


void __RPC_STUB IInkRectangle_get_Right_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRectangle_put_Right_Proxy( 
    IInkRectangle * This,
    /* [in] */ long Units);


void __RPC_STUB IInkRectangle_put_Right_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRectangle_get_Data_Proxy( 
    IInkRectangle * This,
    /* [retval][out] */ RECT *Rect);


void __RPC_STUB IInkRectangle_get_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRectangle_put_Data_Proxy( 
    IInkRectangle * This,
    /* [in] */ RECT Rect);


void __RPC_STUB IInkRectangle_put_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRectangle_GetRectangle_Proxy( 
    IInkRectangle * This,
    /* [out] */ long *Top,
    /* [out] */ long *Left,
    /* [out] */ long *Bottom,
    /* [out] */ long *Right);


void __RPC_STUB IInkRectangle_GetRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRectangle_SetRectangle_Proxy( 
    IInkRectangle * This,
    /* [in] */ long Top,
    /* [in] */ long Left,
    /* [in] */ long Bottom,
    /* [in] */ long Right);


void __RPC_STUB IInkRectangle_SetRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRectangle_INTERFACE_DEFINED__ */


#ifndef __IInkExtendedProperty_INTERFACE_DEFINED__
#define __IInkExtendedProperty_INTERFACE_DEFINED__

/* interface IInkExtendedProperty */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkExtendedProperty;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DB489209-B7C3-411D-90F6-1548CFFF271E")
    IInkExtendedProperty : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Guid( 
            /* [retval][out] */ BSTR *Guid) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Data( 
            /* [retval][out] */ VARIANT *Data) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Data( 
            /* [in] */ VARIANT Data) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkExtendedPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkExtendedProperty * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkExtendedProperty * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkExtendedProperty * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkExtendedProperty * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkExtendedProperty * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkExtendedProperty * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkExtendedProperty * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Guid )( 
            IInkExtendedProperty * This,
            /* [retval][out] */ BSTR *Guid);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Data )( 
            IInkExtendedProperty * This,
            /* [retval][out] */ VARIANT *Data);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Data )( 
            IInkExtendedProperty * This,
            /* [in] */ VARIANT Data);
        
        END_INTERFACE
    } IInkExtendedPropertyVtbl;

    interface IInkExtendedProperty
    {
        CONST_VTBL struct IInkExtendedPropertyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkExtendedProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkExtendedProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkExtendedProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkExtendedProperty_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkExtendedProperty_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkExtendedProperty_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkExtendedProperty_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkExtendedProperty_get_Guid(This,Guid)	\
    (This)->lpVtbl -> get_Guid(This,Guid)

#define IInkExtendedProperty_get_Data(This,Data)	\
    (This)->lpVtbl -> get_Data(This,Data)

#define IInkExtendedProperty_put_Data(This,Data)	\
    (This)->lpVtbl -> put_Data(This,Data)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperty_get_Guid_Proxy( 
    IInkExtendedProperty * This,
    /* [retval][out] */ BSTR *Guid);


void __RPC_STUB IInkExtendedProperty_get_Guid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperty_get_Data_Proxy( 
    IInkExtendedProperty * This,
    /* [retval][out] */ VARIANT *Data);


void __RPC_STUB IInkExtendedProperty_get_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperty_put_Data_Proxy( 
    IInkExtendedProperty * This,
    /* [in] */ VARIANT Data);


void __RPC_STUB IInkExtendedProperty_put_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkExtendedProperty_INTERFACE_DEFINED__ */


#ifndef __IInkExtendedProperties_INTERFACE_DEFINED__
#define __IInkExtendedProperties_INTERFACE_DEFINED__

/* interface IInkExtendedProperties */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkExtendedProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("89F2A8BE-95A9-4530-8B8F-88E971E3E25F")
    IInkExtendedProperties : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Identifier,
            /* [retval][out] */ IInkExtendedProperty **Item) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Guid,
            /* [in] */ VARIANT Data,
            /* [retval][out] */ IInkExtendedProperty **InkExtendedProperty) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Identifier) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DoesPropertyExist( 
            /* [in] */ BSTR Guid,
            /* [retval][out] */ VARIANT_BOOL *DoesPropertyExist) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkExtendedPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkExtendedProperties * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkExtendedProperties * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkExtendedProperties * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkExtendedProperties * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkExtendedProperties * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkExtendedProperties * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkExtendedProperties * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IInkExtendedProperties * This,
            /* [retval][out] */ long *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IInkExtendedProperties * This,
            /* [retval][out] */ IUnknown **_NewEnum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IInkExtendedProperties * This,
            /* [in] */ VARIANT Identifier,
            /* [retval][out] */ IInkExtendedProperty **Item);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IInkExtendedProperties * This,
            /* [in] */ BSTR Guid,
            /* [in] */ VARIANT Data,
            /* [retval][out] */ IInkExtendedProperty **InkExtendedProperty);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IInkExtendedProperties * This,
            /* [in] */ VARIANT Identifier);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IInkExtendedProperties * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DoesPropertyExist )( 
            IInkExtendedProperties * This,
            /* [in] */ BSTR Guid,
            /* [retval][out] */ VARIANT_BOOL *DoesPropertyExist);
        
        END_INTERFACE
    } IInkExtendedPropertiesVtbl;

    interface IInkExtendedProperties
    {
        CONST_VTBL struct IInkExtendedPropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkExtendedProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkExtendedProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkExtendedProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkExtendedProperties_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkExtendedProperties_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkExtendedProperties_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkExtendedProperties_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkExtendedProperties_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkExtendedProperties_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkExtendedProperties_Item(This,Identifier,Item)	\
    (This)->lpVtbl -> Item(This,Identifier,Item)

#define IInkExtendedProperties_Add(This,Guid,Data,InkExtendedProperty)	\
    (This)->lpVtbl -> Add(This,Guid,Data,InkExtendedProperty)

#define IInkExtendedProperties_Remove(This,Identifier)	\
    (This)->lpVtbl -> Remove(This,Identifier)

#define IInkExtendedProperties_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IInkExtendedProperties_DoesPropertyExist(This,Guid,DoesPropertyExist)	\
    (This)->lpVtbl -> DoesPropertyExist(This,Guid,DoesPropertyExist)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_get_Count_Proxy( 
    IInkExtendedProperties * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB IInkExtendedProperties_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_get__NewEnum_Proxy( 
    IInkExtendedProperties * This,
    /* [retval][out] */ IUnknown **_NewEnum);


void __RPC_STUB IInkExtendedProperties_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_Item_Proxy( 
    IInkExtendedProperties * This,
    /* [in] */ VARIANT Identifier,
    /* [retval][out] */ IInkExtendedProperty **Item);


void __RPC_STUB IInkExtendedProperties_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_Add_Proxy( 
    IInkExtendedProperties * This,
    /* [in] */ BSTR Guid,
    /* [in] */ VARIANT Data,
    /* [retval][out] */ IInkExtendedProperty **InkExtendedProperty);


void __RPC_STUB IInkExtendedProperties_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_Remove_Proxy( 
    IInkExtendedProperties * This,
    /* [in] */ VARIANT Identifier);


void __RPC_STUB IInkExtendedProperties_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_Clear_Proxy( 
    IInkExtendedProperties * This);


void __RPC_STUB IInkExtendedProperties_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkExtendedProperties_DoesPropertyExist_Proxy( 
    IInkExtendedProperties * This,
    /* [in] */ BSTR Guid,
    /* [retval][out] */ VARIANT_BOOL *DoesPropertyExist);


void __RPC_STUB IInkExtendedProperties_DoesPropertyExist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkExtendedProperties_INTERFACE_DEFINED__ */


#ifndef __IInkDrawingAttributes_INTERFACE_DEFINED__
#define __IInkDrawingAttributes_INTERFACE_DEFINED__

/* interface IInkDrawingAttributes */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkDrawingAttributes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BF519B75-0A15-4623-ADC9-C00D436A8092")
    IInkDrawingAttributes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
            /* [retval][out] */ long *CurrentColor) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
            /* [in] */ long NewColor) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ float *CurrentWidth) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ float NewWidth) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ float *CurrentHeight) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ float NewHeight) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FitToCurve( 
            /* [retval][out] */ VARIANT_BOOL *Flag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FitToCurve( 
            /* [in] */ VARIANT_BOOL Flag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IgnorePressure( 
            /* [retval][out] */ VARIANT_BOOL *Flag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IgnorePressure( 
            /* [in] */ VARIANT_BOOL Flag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AntiAliased( 
            /* [retval][out] */ VARIANT_BOOL *Flag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AntiAliased( 
            /* [in] */ VARIANT_BOOL Flag) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Transparency( 
            /* [retval][out] */ long *CurrentTransparency) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Transparency( 
            /* [in] */ long NewTransparency) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RasterOperation( 
            /* [retval][out] */ InkRasterOperation *CurrentRasterOperation) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RasterOperation( 
            /* [in] */ InkRasterOperation NewRasterOperation) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PenTip( 
            /* [retval][out] */ InkPenTip *CurrentPenTip) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PenTip( 
            /* [in] */ InkPenTip NewPenTip) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExtendedProperties( 
            /* [retval][out] */ IInkExtendedProperties **Properties) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IInkDrawingAttributes **DrawingAttributes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkDrawingAttributesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkDrawingAttributes * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkDrawingAttributes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkDrawingAttributes * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkDrawingAttributes * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkDrawingAttributes * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkDrawingAttributes * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkDrawingAttributes * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IInkDrawingAttributes * This,
            /* [retval][out] */ long *CurrentColor);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IInkDrawingAttributes * This,
            /* [in] */ long NewColor);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IInkDrawingAttributes * This,
            /* [retval][out] */ float *CurrentWidth);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            IInkDrawingAttributes * This,
            /* [in] */ float NewWidth);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IInkDrawingAttributes * This,
            /* [retval][out] */ float *CurrentHeight);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            IInkDrawingAttributes * This,
            /* [in] */ float NewHeight);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FitToCurve )( 
            IInkDrawingAttributes * This,
            /* [retval][out] */ VARIANT_BOOL *Flag);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FitToCurve )( 
            IInkDrawingAttributes * This,
            /* [in] */ VARIANT_BOOL Flag);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IgnorePressure )( 
            IInkDrawingAttributes * This,
            /* [retval][out] */ VARIANT_BOOL *Flag);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IgnorePressure )( 
            IInkDrawingAttributes * This,
            /* [in] */ VARIANT_BOOL Flag);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AntiAliased )( 
            IInkDrawingAttributes * This,
            /* [retval][out] */ VARIANT_BOOL *Flag);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AntiAliased )( 
            IInkDrawingAttributes * This,
            /* [in] */ VARIANT_BOOL Flag);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Transparency )( 
            IInkDrawingAttributes * This,
            /* [retval][out] */ long *CurrentTransparency);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Transparency )( 
            IInkDrawingAttributes * This,
            /* [in] */ long NewTransparency);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RasterOperation )( 
            IInkDrawingAttributes * This,
            /* [retval][out] */ InkRasterOperation *CurrentRasterOperation);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RasterOperation )( 
            IInkDrawingAttributes * This,
            /* [in] */ InkRasterOperation NewRasterOperation);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PenTip )( 
            IInkDrawingAttributes * This,
            /* [retval][out] */ InkPenTip *CurrentPenTip);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PenTip )( 
            IInkDrawingAttributes * This,
            /* [in] */ InkPenTip NewPenTip);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExtendedProperties )( 
            IInkDrawingAttributes * This,
            /* [retval][out] */ IInkExtendedProperties **Properties);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IInkDrawingAttributes * This,
            /* [retval][out] */ IInkDrawingAttributes **DrawingAttributes);
        
        END_INTERFACE
    } IInkDrawingAttributesVtbl;

    interface IInkDrawingAttributes
    {
        CONST_VTBL struct IInkDrawingAttributesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkDrawingAttributes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkDrawingAttributes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkDrawingAttributes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkDrawingAttributes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkDrawingAttributes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkDrawingAttributes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkDrawingAttributes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkDrawingAttributes_get_Color(This,CurrentColor)	\
    (This)->lpVtbl -> get_Color(This,CurrentColor)

#define IInkDrawingAttributes_put_Color(This,NewColor)	\
    (This)->lpVtbl -> put_Color(This,NewColor)

#define IInkDrawingAttributes_get_Width(This,CurrentWidth)	\
    (This)->lpVtbl -> get_Width(This,CurrentWidth)

#define IInkDrawingAttributes_put_Width(This,NewWidth)	\
    (This)->lpVtbl -> put_Width(This,NewWidth)

#define IInkDrawingAttributes_get_Height(This,CurrentHeight)	\
    (This)->lpVtbl -> get_Height(This,CurrentHeight)

#define IInkDrawingAttributes_put_Height(This,NewHeight)	\
    (This)->lpVtbl -> put_Height(This,NewHeight)

#define IInkDrawingAttributes_get_FitToCurve(This,Flag)	\
    (This)->lpVtbl -> get_FitToCurve(This,Flag)

#define IInkDrawingAttributes_put_FitToCurve(This,Flag)	\
    (This)->lpVtbl -> put_FitToCurve(This,Flag)

#define IInkDrawingAttributes_get_IgnorePressure(This,Flag)	\
    (This)->lpVtbl -> get_IgnorePressure(This,Flag)

#define IInkDrawingAttributes_put_IgnorePressure(This,Flag)	\
    (This)->lpVtbl -> put_IgnorePressure(This,Flag)

#define IInkDrawingAttributes_get_AntiAliased(This,Flag)	\
    (This)->lpVtbl -> get_AntiAliased(This,Flag)

#define IInkDrawingAttributes_put_AntiAliased(This,Flag)	\
    (This)->lpVtbl -> put_AntiAliased(This,Flag)

#define IInkDrawingAttributes_get_Transparency(This,CurrentTransparency)	\
    (This)->lpVtbl -> get_Transparency(This,CurrentTransparency)

#define IInkDrawingAttributes_put_Transparency(This,NewTransparency)	\
    (This)->lpVtbl -> put_Transparency(This,NewTransparency)

#define IInkDrawingAttributes_get_RasterOperation(This,CurrentRasterOperation)	\
    (This)->lpVtbl -> get_RasterOperation(This,CurrentRasterOperation)

#define IInkDrawingAttributes_put_RasterOperation(This,NewRasterOperation)	\
    (This)->lpVtbl -> put_RasterOperation(This,NewRasterOperation)

#define IInkDrawingAttributes_get_PenTip(This,CurrentPenTip)	\
    (This)->lpVtbl -> get_PenTip(This,CurrentPenTip)

#define IInkDrawingAttributes_put_PenTip(This,NewPenTip)	\
    (This)->lpVtbl -> put_PenTip(This,NewPenTip)

#define IInkDrawingAttributes_get_ExtendedProperties(This,Properties)	\
    (This)->lpVtbl -> get_ExtendedProperties(This,Properties)

#define IInkDrawingAttributes_Clone(This,DrawingAttributes)	\
    (This)->lpVtbl -> Clone(This,DrawingAttributes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_Color_Proxy( 
    IInkDrawingAttributes * This,
    /* [retval][out] */ long *CurrentColor);


void __RPC_STUB IInkDrawingAttributes_get_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_Color_Proxy( 
    IInkDrawingAttributes * This,
    /* [in] */ long NewColor);


void __RPC_STUB IInkDrawingAttributes_put_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_Width_Proxy( 
    IInkDrawingAttributes * This,
    /* [retval][out] */ float *CurrentWidth);


void __RPC_STUB IInkDrawingAttributes_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_Width_Proxy( 
    IInkDrawingAttributes * This,
    /* [in] */ float NewWidth);


void __RPC_STUB IInkDrawingAttributes_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_Height_Proxy( 
    IInkDrawingAttributes * This,
    /* [retval][out] */ float *CurrentHeight);


void __RPC_STUB IInkDrawingAttributes_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_Height_Proxy( 
    IInkDrawingAttributes * This,
    /* [in] */ float NewHeight);


void __RPC_STUB IInkDrawingAttributes_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_FitToCurve_Proxy( 
    IInkDrawingAttributes * This,
    /* [retval][out] */ VARIANT_BOOL *Flag);


void __RPC_STUB IInkDrawingAttributes_get_FitToCurve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_FitToCurve_Proxy( 
    IInkDrawingAttributes * This,
    /* [in] */ VARIANT_BOOL Flag);


void __RPC_STUB IInkDrawingAttributes_put_FitToCurve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_IgnorePressure_Proxy( 
    IInkDrawingAttributes * This,
    /* [retval][out] */ VARIANT_BOOL *Flag);


void __RPC_STUB IInkDrawingAttributes_get_IgnorePressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_IgnorePressure_Proxy( 
    IInkDrawingAttributes * This,
    /* [in] */ VARIANT_BOOL Flag);


void __RPC_STUB IInkDrawingAttributes_put_IgnorePressure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_AntiAliased_Proxy( 
    IInkDrawingAttributes * This,
    /* [retval][out] */ VARIANT_BOOL *Flag);


void __RPC_STUB IInkDrawingAttributes_get_AntiAliased_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_AntiAliased_Proxy( 
    IInkDrawingAttributes * This,
    /* [in] */ VARIANT_BOOL Flag);


void __RPC_STUB IInkDrawingAttributes_put_AntiAliased_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_Transparency_Proxy( 
    IInkDrawingAttributes * This,
    /* [retval][out] */ long *CurrentTransparency);


void __RPC_STUB IInkDrawingAttributes_get_Transparency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_Transparency_Proxy( 
    IInkDrawingAttributes * This,
    /* [in] */ long NewTransparency);


void __RPC_STUB IInkDrawingAttributes_put_Transparency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_RasterOperation_Proxy( 
    IInkDrawingAttributes * This,
    /* [retval][out] */ InkRasterOperation *CurrentRasterOperation);


void __RPC_STUB IInkDrawingAttributes_get_RasterOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_RasterOperation_Proxy( 
    IInkDrawingAttributes * This,
    /* [in] */ InkRasterOperation NewRasterOperation);


void __RPC_STUB IInkDrawingAttributes_put_RasterOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_PenTip_Proxy( 
    IInkDrawingAttributes * This,
    /* [retval][out] */ InkPenTip *CurrentPenTip);


void __RPC_STUB IInkDrawingAttributes_get_PenTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_put_PenTip_Proxy( 
    IInkDrawingAttributes * This,
    /* [in] */ InkPenTip NewPenTip);


void __RPC_STUB IInkDrawingAttributes_put_PenTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_get_ExtendedProperties_Proxy( 
    IInkDrawingAttributes * This,
    /* [retval][out] */ IInkExtendedProperties **Properties);


void __RPC_STUB IInkDrawingAttributes_get_ExtendedProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDrawingAttributes_Clone_Proxy( 
    IInkDrawingAttributes * This,
    /* [retval][out] */ IInkDrawingAttributes **DrawingAttributes);


void __RPC_STUB IInkDrawingAttributes_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkDrawingAttributes_INTERFACE_DEFINED__ */


#ifndef __IInkTransform_INTERFACE_DEFINED__
#define __IInkTransform_INTERFACE_DEFINED__

/* interface IInkTransform */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkTransform;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("615F1D43-8703-4565-88E2-8201D2ECD7B7")
    IInkTransform : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Translate( 
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x = 0,
            /* [defaultvalue][in] */ float y = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Reflect( 
            /* [in] */ VARIANT_BOOL Horizontally,
            /* [in] */ VARIANT_BOOL Vertically) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Shear( 
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleTransform( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTransform( 
            /* [out] */ float *eM11,
            /* [out] */ float *eM12,
            /* [out] */ float *eM21,
            /* [out] */ float *eM22,
            /* [out] */ float *eDx,
            /* [out] */ float *eDy) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTransform( 
            /* [in] */ float eM11,
            /* [in] */ float eM12,
            /* [in] */ float eM21,
            /* [in] */ float eM22,
            /* [in] */ float eDx,
            /* [in] */ float eDy) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eM11( 
            /* [retval][out] */ float *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eM11( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eM12( 
            /* [retval][out] */ float *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eM12( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eM21( 
            /* [retval][out] */ float *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eM21( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eM22( 
            /* [retval][out] */ float *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eM22( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eDx( 
            /* [retval][out] */ float *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eDx( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_eDy( 
            /* [retval][out] */ float *Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_eDy( 
            /* [in] */ float Value) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_Data( 
            /* [retval][out] */ XFORM *XForm) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_Data( 
            /* [in] */ XFORM XForm) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkTransformVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkTransform * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkTransform * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkTransform * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkTransform * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkTransform * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkTransform * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkTransform * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IInkTransform * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Translate )( 
            IInkTransform * This,
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            IInkTransform * This,
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x,
            /* [defaultvalue][in] */ float y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Reflect )( 
            IInkTransform * This,
            /* [in] */ VARIANT_BOOL Horizontally,
            /* [in] */ VARIANT_BOOL Vertically);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Shear )( 
            IInkTransform * This,
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScaleTransform )( 
            IInkTransform * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTransform )( 
            IInkTransform * This,
            /* [out] */ float *eM11,
            /* [out] */ float *eM12,
            /* [out] */ float *eM21,
            /* [out] */ float *eM22,
            /* [out] */ float *eDx,
            /* [out] */ float *eDy);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTransform )( 
            IInkTransform * This,
            /* [in] */ float eM11,
            /* [in] */ float eM12,
            /* [in] */ float eM21,
            /* [in] */ float eM22,
            /* [in] */ float eDx,
            /* [in] */ float eDy);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_eM11 )( 
            IInkTransform * This,
            /* [retval][out] */ float *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_eM11 )( 
            IInkTransform * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_eM12 )( 
            IInkTransform * This,
            /* [retval][out] */ float *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_eM12 )( 
            IInkTransform * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_eM21 )( 
            IInkTransform * This,
            /* [retval][out] */ float *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_eM21 )( 
            IInkTransform * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_eM22 )( 
            IInkTransform * This,
            /* [retval][out] */ float *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_eM22 )( 
            IInkTransform * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_eDx )( 
            IInkTransform * This,
            /* [retval][out] */ float *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_eDx )( 
            IInkTransform * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_eDy )( 
            IInkTransform * This,
            /* [retval][out] */ float *Value);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_eDy )( 
            IInkTransform * This,
            /* [in] */ float Value);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Data )( 
            IInkTransform * This,
            /* [retval][out] */ XFORM *XForm);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Data )( 
            IInkTransform * This,
            /* [in] */ XFORM XForm);
        
        END_INTERFACE
    } IInkTransformVtbl;

    interface IInkTransform
    {
        CONST_VTBL struct IInkTransformVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkTransform_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkTransform_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkTransform_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkTransform_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkTransform_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkTransform_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkTransform_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkTransform_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IInkTransform_Translate(This,HorizontalComponent,VerticalComponent)	\
    (This)->lpVtbl -> Translate(This,HorizontalComponent,VerticalComponent)

#define IInkTransform_Rotate(This,Degrees,x,y)	\
    (This)->lpVtbl -> Rotate(This,Degrees,x,y)

#define IInkTransform_Reflect(This,Horizontally,Vertically)	\
    (This)->lpVtbl -> Reflect(This,Horizontally,Vertically)

#define IInkTransform_Shear(This,HorizontalComponent,VerticalComponent)	\
    (This)->lpVtbl -> Shear(This,HorizontalComponent,VerticalComponent)

#define IInkTransform_ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)	\
    (This)->lpVtbl -> ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)

#define IInkTransform_GetTransform(This,eM11,eM12,eM21,eM22,eDx,eDy)	\
    (This)->lpVtbl -> GetTransform(This,eM11,eM12,eM21,eM22,eDx,eDy)

#define IInkTransform_SetTransform(This,eM11,eM12,eM21,eM22,eDx,eDy)	\
    (This)->lpVtbl -> SetTransform(This,eM11,eM12,eM21,eM22,eDx,eDy)

#define IInkTransform_get_eM11(This,Value)	\
    (This)->lpVtbl -> get_eM11(This,Value)

#define IInkTransform_put_eM11(This,Value)	\
    (This)->lpVtbl -> put_eM11(This,Value)

#define IInkTransform_get_eM12(This,Value)	\
    (This)->lpVtbl -> get_eM12(This,Value)

#define IInkTransform_put_eM12(This,Value)	\
    (This)->lpVtbl -> put_eM12(This,Value)

#define IInkTransform_get_eM21(This,Value)	\
    (This)->lpVtbl -> get_eM21(This,Value)

#define IInkTransform_put_eM21(This,Value)	\
    (This)->lpVtbl -> put_eM21(This,Value)

#define IInkTransform_get_eM22(This,Value)	\
    (This)->lpVtbl -> get_eM22(This,Value)

#define IInkTransform_put_eM22(This,Value)	\
    (This)->lpVtbl -> put_eM22(This,Value)

#define IInkTransform_get_eDx(This,Value)	\
    (This)->lpVtbl -> get_eDx(This,Value)

#define IInkTransform_put_eDx(This,Value)	\
    (This)->lpVtbl -> put_eDx(This,Value)

#define IInkTransform_get_eDy(This,Value)	\
    (This)->lpVtbl -> get_eDy(This,Value)

#define IInkTransform_put_eDy(This,Value)	\
    (This)->lpVtbl -> put_eDy(This,Value)

#define IInkTransform_get_Data(This,XForm)	\
    (This)->lpVtbl -> get_Data(This,XForm)

#define IInkTransform_put_Data(This,XForm)	\
    (This)->lpVtbl -> put_Data(This,XForm)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_Reset_Proxy( 
    IInkTransform * This);


void __RPC_STUB IInkTransform_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_Translate_Proxy( 
    IInkTransform * This,
    /* [in] */ float HorizontalComponent,
    /* [in] */ float VerticalComponent);


void __RPC_STUB IInkTransform_Translate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_Rotate_Proxy( 
    IInkTransform * This,
    /* [in] */ float Degrees,
    /* [defaultvalue][in] */ float x,
    /* [defaultvalue][in] */ float y);


void __RPC_STUB IInkTransform_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_Reflect_Proxy( 
    IInkTransform * This,
    /* [in] */ VARIANT_BOOL Horizontally,
    /* [in] */ VARIANT_BOOL Vertically);


void __RPC_STUB IInkTransform_Reflect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_Shear_Proxy( 
    IInkTransform * This,
    /* [in] */ float HorizontalComponent,
    /* [in] */ float VerticalComponent);


void __RPC_STUB IInkTransform_Shear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_ScaleTransform_Proxy( 
    IInkTransform * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier);


void __RPC_STUB IInkTransform_ScaleTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_GetTransform_Proxy( 
    IInkTransform * This,
    /* [out] */ float *eM11,
    /* [out] */ float *eM12,
    /* [out] */ float *eM21,
    /* [out] */ float *eM22,
    /* [out] */ float *eDx,
    /* [out] */ float *eDy);


void __RPC_STUB IInkTransform_GetTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTransform_SetTransform_Proxy( 
    IInkTransform * This,
    /* [in] */ float eM11,
    /* [in] */ float eM12,
    /* [in] */ float eM21,
    /* [in] */ float eM22,
    /* [in] */ float eDx,
    /* [in] */ float eDy);


void __RPC_STUB IInkTransform_SetTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eM11_Proxy( 
    IInkTransform * This,
    /* [retval][out] */ float *Value);


void __RPC_STUB IInkTransform_get_eM11_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eM11_Proxy( 
    IInkTransform * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eM11_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eM12_Proxy( 
    IInkTransform * This,
    /* [retval][out] */ float *Value);


void __RPC_STUB IInkTransform_get_eM12_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eM12_Proxy( 
    IInkTransform * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eM12_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eM21_Proxy( 
    IInkTransform * This,
    /* [retval][out] */ float *Value);


void __RPC_STUB IInkTransform_get_eM21_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eM21_Proxy( 
    IInkTransform * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eM21_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eM22_Proxy( 
    IInkTransform * This,
    /* [retval][out] */ float *Value);


void __RPC_STUB IInkTransform_get_eM22_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eM22_Proxy( 
    IInkTransform * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eM22_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eDx_Proxy( 
    IInkTransform * This,
    /* [retval][out] */ float *Value);


void __RPC_STUB IInkTransform_get_eDx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eDx_Proxy( 
    IInkTransform * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eDx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_eDy_Proxy( 
    IInkTransform * This,
    /* [retval][out] */ float *Value);


void __RPC_STUB IInkTransform_get_eDy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_eDy_Proxy( 
    IInkTransform * This,
    /* [in] */ float Value);


void __RPC_STUB IInkTransform_put_eDy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTransform_get_Data_Proxy( 
    IInkTransform * This,
    /* [retval][out] */ XFORM *XForm);


void __RPC_STUB IInkTransform_get_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkTransform_put_Data_Proxy( 
    IInkTransform * This,
    /* [in] */ XFORM XForm);


void __RPC_STUB IInkTransform_put_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkTransform_INTERFACE_DEFINED__ */


#ifndef __IInkGesture_INTERFACE_DEFINED__
#define __IInkGesture_INTERFACE_DEFINED__

/* interface IInkGesture */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkGesture;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3BDC0A97-04E5-4e26-B813-18F052D41DEF")
    IInkGesture : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Confidence( 
            /* [retval][out] */ InkRecognitionConfidence *Confidence) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Id( 
            /* [retval][out] */ InkApplicationGesture *Id) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHotPoint( 
            /* [out][in] */ long *X,
            /* [out][in] */ long *Y) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkGestureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkGesture * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkGesture * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkGesture * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkGesture * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkGesture * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkGesture * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkGesture * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Confidence )( 
            IInkGesture * This,
            /* [retval][out] */ InkRecognitionConfidence *Confidence);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Id )( 
            IInkGesture * This,
            /* [retval][out] */ InkApplicationGesture *Id);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHotPoint )( 
            IInkGesture * This,
            /* [out][in] */ long *X,
            /* [out][in] */ long *Y);
        
        END_INTERFACE
    } IInkGestureVtbl;

    interface IInkGesture
    {
        CONST_VTBL struct IInkGestureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkGesture_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkGesture_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkGesture_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkGesture_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkGesture_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkGesture_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkGesture_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkGesture_get_Confidence(This,Confidence)	\
    (This)->lpVtbl -> get_Confidence(This,Confidence)

#define IInkGesture_get_Id(This,Id)	\
    (This)->lpVtbl -> get_Id(This,Id)

#define IInkGesture_GetHotPoint(This,X,Y)	\
    (This)->lpVtbl -> GetHotPoint(This,X,Y)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkGesture_get_Confidence_Proxy( 
    IInkGesture * This,
    /* [retval][out] */ InkRecognitionConfidence *Confidence);


void __RPC_STUB IInkGesture_get_Confidence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkGesture_get_Id_Proxy( 
    IInkGesture * This,
    /* [retval][out] */ InkApplicationGesture *Id);


void __RPC_STUB IInkGesture_get_Id_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkGesture_GetHotPoint_Proxy( 
    IInkGesture * This,
    /* [out][in] */ long *X,
    /* [out][in] */ long *Y);


void __RPC_STUB IInkGesture_GetHotPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkGesture_INTERFACE_DEFINED__ */


#ifndef __IInkCursor_INTERFACE_DEFINED__
#define __IInkCursor_INTERFACE_DEFINED__

/* interface IInkCursor */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkCursor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AD30C630-40C5-4350-8405-9C71012FC558")
    IInkCursor : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *Name) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Id( 
            /* [retval][out] */ long *Id) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Inverted( 
            /* [retval][out] */ VARIANT_BOOL *Status) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DrawingAttributes( 
            /* [retval][out] */ IInkDrawingAttributes **Attributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_DrawingAttributes( 
            /* [in] */ IInkDrawingAttributes *Attributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Tablet( 
            /* [retval][out] */ IInkTablet **Tablet) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Buttons( 
            /* [retval][out] */ IInkCursorButtons **Buttons) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkCursorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkCursor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkCursor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkCursor * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkCursor * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkCursor * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkCursor * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkCursor * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IInkCursor * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Id )( 
            IInkCursor * This,
            /* [retval][out] */ long *Id);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Inverted )( 
            IInkCursor * This,
            /* [retval][out] */ VARIANT_BOOL *Status);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawingAttributes )( 
            IInkCursor * This,
            /* [retval][out] */ IInkDrawingAttributes **Attributes);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DrawingAttributes )( 
            IInkCursor * This,
            /* [in] */ IInkDrawingAttributes *Attributes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tablet )( 
            IInkCursor * This,
            /* [retval][out] */ IInkTablet **Tablet);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Buttons )( 
            IInkCursor * This,
            /* [retval][out] */ IInkCursorButtons **Buttons);
        
        END_INTERFACE
    } IInkCursorVtbl;

    interface IInkCursor
    {
        CONST_VTBL struct IInkCursorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkCursor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkCursor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkCursor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkCursor_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkCursor_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkCursor_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkCursor_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkCursor_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define IInkCursor_get_Id(This,Id)	\
    (This)->lpVtbl -> get_Id(This,Id)

#define IInkCursor_get_Inverted(This,Status)	\
    (This)->lpVtbl -> get_Inverted(This,Status)

#define IInkCursor_get_DrawingAttributes(This,Attributes)	\
    (This)->lpVtbl -> get_DrawingAttributes(This,Attributes)

#define IInkCursor_putref_DrawingAttributes(This,Attributes)	\
    (This)->lpVtbl -> putref_DrawingAttributes(This,Attributes)

#define IInkCursor_get_Tablet(This,Tablet)	\
    (This)->lpVtbl -> get_Tablet(This,Tablet)

#define IInkCursor_get_Buttons(This,Buttons)	\
    (This)->lpVtbl -> get_Buttons(This,Buttons)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_Name_Proxy( 
    IInkCursor * This,
    /* [retval][out] */ BSTR *Name);


void __RPC_STUB IInkCursor_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_Id_Proxy( 
    IInkCursor * This,
    /* [retval][out] */ long *Id);


void __RPC_STUB IInkCursor_get_Id_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_Inverted_Proxy( 
    IInkCursor * This,
    /* [retval][out] */ VARIANT_BOOL *Status);


void __RPC_STUB IInkCursor_get_Inverted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_DrawingAttributes_Proxy( 
    IInkCursor * This,
    /* [retval][out] */ IInkDrawingAttributes **Attributes);


void __RPC_STUB IInkCursor_get_DrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkCursor_putref_DrawingAttributes_Proxy( 
    IInkCursor * This,
    /* [in] */ IInkDrawingAttributes *Attributes);


void __RPC_STUB IInkCursor_putref_DrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_Tablet_Proxy( 
    IInkCursor * This,
    /* [retval][out] */ IInkTablet **Tablet);


void __RPC_STUB IInkCursor_get_Tablet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursor_get_Buttons_Proxy( 
    IInkCursor * This,
    /* [retval][out] */ IInkCursorButtons **Buttons);


void __RPC_STUB IInkCursor_get_Buttons_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkCursor_INTERFACE_DEFINED__ */


#ifndef __IInkCursors_INTERFACE_DEFINED__
#define __IInkCursors_INTERFACE_DEFINED__

/* interface IInkCursors */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkCursors;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A248C1AC-C698-4e06-9E5C-D57F77C7E647")
    IInkCursors : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IInkCursor **Cursor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkCursorsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkCursors * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkCursors * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkCursors * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkCursors * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkCursors * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkCursors * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkCursors * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IInkCursors * This,
            /* [retval][out] */ long *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IInkCursors * This,
            /* [retval][out] */ IUnknown **_NewEnum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IInkCursors * This,
            /* [in] */ long Index,
            /* [retval][out] */ IInkCursor **Cursor);
        
        END_INTERFACE
    } IInkCursorsVtbl;

    interface IInkCursors
    {
        CONST_VTBL struct IInkCursorsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkCursors_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkCursors_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkCursors_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkCursors_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkCursors_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkCursors_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkCursors_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkCursors_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkCursors_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkCursors_Item(This,Index,Cursor)	\
    (This)->lpVtbl -> Item(This,Index,Cursor)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursors_get_Count_Proxy( 
    IInkCursors * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB IInkCursors_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursors_get__NewEnum_Proxy( 
    IInkCursors * This,
    /* [retval][out] */ IUnknown **_NewEnum);


void __RPC_STUB IInkCursors_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCursors_Item_Proxy( 
    IInkCursors * This,
    /* [in] */ long Index,
    /* [retval][out] */ IInkCursor **Cursor);


void __RPC_STUB IInkCursors_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkCursors_INTERFACE_DEFINED__ */


#ifndef __IInkCursorButton_INTERFACE_DEFINED__
#define __IInkCursorButton_INTERFACE_DEFINED__

/* interface IInkCursorButton */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkCursorButton;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("85EF9417-1D59-49b2-A13C-702C85430894")
    IInkCursorButton : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *Name) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Id( 
            /* [retval][out] */ BSTR *Id) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ InkCursorButtonState *CurrentState) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkCursorButtonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkCursorButton * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkCursorButton * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkCursorButton * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkCursorButton * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkCursorButton * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkCursorButton * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkCursorButton * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IInkCursorButton * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Id )( 
            IInkCursorButton * This,
            /* [retval][out] */ BSTR *Id);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_State )( 
            IInkCursorButton * This,
            /* [retval][out] */ InkCursorButtonState *CurrentState);
        
        END_INTERFACE
    } IInkCursorButtonVtbl;

    interface IInkCursorButton
    {
        CONST_VTBL struct IInkCursorButtonVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkCursorButton_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkCursorButton_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkCursorButton_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkCursorButton_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkCursorButton_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkCursorButton_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkCursorButton_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkCursorButton_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define IInkCursorButton_get_Id(This,Id)	\
    (This)->lpVtbl -> get_Id(This,Id)

#define IInkCursorButton_get_State(This,CurrentState)	\
    (This)->lpVtbl -> get_State(This,CurrentState)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursorButton_get_Name_Proxy( 
    IInkCursorButton * This,
    /* [retval][out] */ BSTR *Name);


void __RPC_STUB IInkCursorButton_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursorButton_get_Id_Proxy( 
    IInkCursorButton * This,
    /* [retval][out] */ BSTR *Id);


void __RPC_STUB IInkCursorButton_get_Id_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursorButton_get_State_Proxy( 
    IInkCursorButton * This,
    /* [retval][out] */ InkCursorButtonState *CurrentState);


void __RPC_STUB IInkCursorButton_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkCursorButton_INTERFACE_DEFINED__ */


#ifndef __IInkCursorButtons_INTERFACE_DEFINED__
#define __IInkCursorButtons_INTERFACE_DEFINED__

/* interface IInkCursorButtons */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkCursorButtons;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3671CC40-B624-4671-9FA0-DB119D952D54")
    IInkCursorButtons : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Identifier,
            /* [retval][out] */ IInkCursorButton **Button) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkCursorButtonsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkCursorButtons * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkCursorButtons * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkCursorButtons * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkCursorButtons * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkCursorButtons * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkCursorButtons * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkCursorButtons * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IInkCursorButtons * This,
            /* [retval][out] */ long *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IInkCursorButtons * This,
            /* [retval][out] */ IUnknown **_NewEnum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IInkCursorButtons * This,
            /* [in] */ VARIANT Identifier,
            /* [retval][out] */ IInkCursorButton **Button);
        
        END_INTERFACE
    } IInkCursorButtonsVtbl;

    interface IInkCursorButtons
    {
        CONST_VTBL struct IInkCursorButtonsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkCursorButtons_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkCursorButtons_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkCursorButtons_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkCursorButtons_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkCursorButtons_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkCursorButtons_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkCursorButtons_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkCursorButtons_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkCursorButtons_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkCursorButtons_Item(This,Identifier,Button)	\
    (This)->lpVtbl -> Item(This,Identifier,Button)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursorButtons_get_Count_Proxy( 
    IInkCursorButtons * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB IInkCursorButtons_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCursorButtons_get__NewEnum_Proxy( 
    IInkCursorButtons * This,
    /* [retval][out] */ IUnknown **_NewEnum);


void __RPC_STUB IInkCursorButtons_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCursorButtons_Item_Proxy( 
    IInkCursorButtons * This,
    /* [in] */ VARIANT Identifier,
    /* [retval][out] */ IInkCursorButton **Button);


void __RPC_STUB IInkCursorButtons_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkCursorButtons_INTERFACE_DEFINED__ */


#ifndef __IInkTablet_INTERFACE_DEFINED__
#define __IInkTablet_INTERFACE_DEFINED__

/* interface IInkTablet */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkTablet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2DE25EAA-6EF8-42d5-AEE9-185BC81B912D")
    IInkTablet : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *Name) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PlugAndPlayId( 
            /* [retval][out] */ BSTR *Id) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaximumInputRectangle( 
            /* [retval][out] */ IInkRectangle **Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HardwareCapabilities( 
            /* [retval][out] */ TabletHardwareCapabilities *Capabilities) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IsPacketPropertySupported( 
            /* [in] */ BSTR packetPropertyName,
            /* [retval][out] */ VARIANT_BOOL *Supported) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPropertyMetrics( 
            /* [in] */ BSTR propertyName,
            /* [out] */ long *Minimum,
            /* [out] */ long *Maximum,
            /* [out] */ TabletPropertyMetricUnit *Units,
            /* [out] */ float *Resolution) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkTabletVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkTablet * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkTablet * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkTablet * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkTablet * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkTablet * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkTablet * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkTablet * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IInkTablet * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PlugAndPlayId )( 
            IInkTablet * This,
            /* [retval][out] */ BSTR *Id);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaximumInputRectangle )( 
            IInkTablet * This,
            /* [retval][out] */ IInkRectangle **Rectangle);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HardwareCapabilities )( 
            IInkTablet * This,
            /* [retval][out] */ TabletHardwareCapabilities *Capabilities);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsPacketPropertySupported )( 
            IInkTablet * This,
            /* [in] */ BSTR packetPropertyName,
            /* [retval][out] */ VARIANT_BOOL *Supported);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPropertyMetrics )( 
            IInkTablet * This,
            /* [in] */ BSTR propertyName,
            /* [out] */ long *Minimum,
            /* [out] */ long *Maximum,
            /* [out] */ TabletPropertyMetricUnit *Units,
            /* [out] */ float *Resolution);
        
        END_INTERFACE
    } IInkTabletVtbl;

    interface IInkTablet
    {
        CONST_VTBL struct IInkTabletVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkTablet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkTablet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkTablet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkTablet_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkTablet_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkTablet_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkTablet_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkTablet_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define IInkTablet_get_PlugAndPlayId(This,Id)	\
    (This)->lpVtbl -> get_PlugAndPlayId(This,Id)

#define IInkTablet_get_MaximumInputRectangle(This,Rectangle)	\
    (This)->lpVtbl -> get_MaximumInputRectangle(This,Rectangle)

#define IInkTablet_get_HardwareCapabilities(This,Capabilities)	\
    (This)->lpVtbl -> get_HardwareCapabilities(This,Capabilities)

#define IInkTablet_IsPacketPropertySupported(This,packetPropertyName,Supported)	\
    (This)->lpVtbl -> IsPacketPropertySupported(This,packetPropertyName,Supported)

#define IInkTablet_GetPropertyMetrics(This,propertyName,Minimum,Maximum,Units,Resolution)	\
    (This)->lpVtbl -> GetPropertyMetrics(This,propertyName,Minimum,Maximum,Units,Resolution)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTablet_get_Name_Proxy( 
    IInkTablet * This,
    /* [retval][out] */ BSTR *Name);


void __RPC_STUB IInkTablet_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTablet_get_PlugAndPlayId_Proxy( 
    IInkTablet * This,
    /* [retval][out] */ BSTR *Id);


void __RPC_STUB IInkTablet_get_PlugAndPlayId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTablet_get_MaximumInputRectangle_Proxy( 
    IInkTablet * This,
    /* [retval][out] */ IInkRectangle **Rectangle);


void __RPC_STUB IInkTablet_get_MaximumInputRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTablet_get_HardwareCapabilities_Proxy( 
    IInkTablet * This,
    /* [retval][out] */ TabletHardwareCapabilities *Capabilities);


void __RPC_STUB IInkTablet_get_HardwareCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTablet_IsPacketPropertySupported_Proxy( 
    IInkTablet * This,
    /* [in] */ BSTR packetPropertyName,
    /* [retval][out] */ VARIANT_BOOL *Supported);


void __RPC_STUB IInkTablet_IsPacketPropertySupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTablet_GetPropertyMetrics_Proxy( 
    IInkTablet * This,
    /* [in] */ BSTR propertyName,
    /* [out] */ long *Minimum,
    /* [out] */ long *Maximum,
    /* [out] */ TabletPropertyMetricUnit *Units,
    /* [out] */ float *Resolution);


void __RPC_STUB IInkTablet_GetPropertyMetrics_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkTablet_INTERFACE_DEFINED__ */


#ifndef __IInkTablets_INTERFACE_DEFINED__
#define __IInkTablets_INTERFACE_DEFINED__

/* interface IInkTablets */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkTablets;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("112086D9-7779-4535-A699-862B43AC1863")
    IInkTablets : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultTablet( 
            /* [retval][out] */ IInkTablet **DefaultTablet) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IInkTablet **Tablet) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IsPacketPropertySupported( 
            /* [in] */ BSTR packetPropertyName,
            /* [retval][out] */ VARIANT_BOOL *Supported) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkTabletsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkTablets * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkTablets * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkTablets * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkTablets * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkTablets * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkTablets * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkTablets * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IInkTablets * This,
            /* [retval][out] */ long *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IInkTablets * This,
            /* [retval][out] */ IUnknown **_NewEnum);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultTablet )( 
            IInkTablets * This,
            /* [retval][out] */ IInkTablet **DefaultTablet);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IInkTablets * This,
            /* [in] */ long Index,
            /* [retval][out] */ IInkTablet **Tablet);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsPacketPropertySupported )( 
            IInkTablets * This,
            /* [in] */ BSTR packetPropertyName,
            /* [retval][out] */ VARIANT_BOOL *Supported);
        
        END_INTERFACE
    } IInkTabletsVtbl;

    interface IInkTablets
    {
        CONST_VTBL struct IInkTabletsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkTablets_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkTablets_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkTablets_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkTablets_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkTablets_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkTablets_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkTablets_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkTablets_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkTablets_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkTablets_get_DefaultTablet(This,DefaultTablet)	\
    (This)->lpVtbl -> get_DefaultTablet(This,DefaultTablet)

#define IInkTablets_Item(This,Index,Tablet)	\
    (This)->lpVtbl -> Item(This,Index,Tablet)

#define IInkTablets_IsPacketPropertySupported(This,packetPropertyName,Supported)	\
    (This)->lpVtbl -> IsPacketPropertySupported(This,packetPropertyName,Supported)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTablets_get_Count_Proxy( 
    IInkTablets * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB IInkTablets_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTablets_get__NewEnum_Proxy( 
    IInkTablets * This,
    /* [retval][out] */ IUnknown **_NewEnum);


void __RPC_STUB IInkTablets_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkTablets_get_DefaultTablet_Proxy( 
    IInkTablets * This,
    /* [retval][out] */ IInkTablet **DefaultTablet);


void __RPC_STUB IInkTablets_get_DefaultTablet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTablets_Item_Proxy( 
    IInkTablets * This,
    /* [in] */ long Index,
    /* [retval][out] */ IInkTablet **Tablet);


void __RPC_STUB IInkTablets_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkTablets_IsPacketPropertySupported_Proxy( 
    IInkTablets * This,
    /* [in] */ BSTR packetPropertyName,
    /* [retval][out] */ VARIANT_BOOL *Supported);


void __RPC_STUB IInkTablets_IsPacketPropertySupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkTablets_INTERFACE_DEFINED__ */


#ifndef __IInkStrokeDisp_INTERFACE_DEFINED__
#define __IInkStrokeDisp_INTERFACE_DEFINED__

/* interface IInkStrokeDisp */
/* [unique][dual][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IInkStrokeDisp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43242FEA-91D1-4a72-963E-FBB91829CFA2")
    IInkStrokeDisp : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ long *ID) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BezierPoints( 
            /* [retval][out] */ VARIANT *Points) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DrawingAttributes( 
            /* [retval][out] */ IInkDrawingAttributes **DrawAttrs) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_DrawingAttributes( 
            /* [in] */ IInkDrawingAttributes *DrawAttrs) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ink( 
            /* [retval][out] */ IInkDisp **Ink) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExtendedProperties( 
            /* [retval][out] */ IInkExtendedProperties **Properties) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PolylineCusps( 
            /* [retval][out] */ VARIANT *Cusps) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BezierCusps( 
            /* [retval][out] */ VARIANT *Cusps) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelfIntersections( 
            /* [retval][out] */ VARIANT *Intersections) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PacketCount( 
            /* [retval][out] */ long *plCount) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PacketSize( 
            /* [retval][out] */ long *plSize) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PacketDescription( 
            /* [retval][out] */ VARIANT *PacketDescription) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Deleted( 
            /* [retval][out] */ VARIANT_BOOL *Deleted) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBoundingBox( 
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle **Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE FindIntersections( 
            /* [in] */ IInkStrokes *Strokes,
            /* [retval][out] */ VARIANT *Intersections) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRectangleIntersections( 
            /* [in] */ IInkRectangle *Rectangle,
            /* [retval][out] */ VARIANT *Intersections) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clip( 
            /* [in] */ IInkRectangle *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE HitTestCircle( 
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ float Radius,
            /* [retval][out] */ VARIANT_BOOL *Intersects) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE NearestPoint( 
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [defaultvalue][out][in] */ float *Distance,
            /* [retval][out] */ float *Point) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Split( 
            /* [in] */ float SplitAt,
            /* [retval][out] */ IInkStrokeDisp **NewStroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPacketDescriptionPropertyMetrics( 
            /* [in] */ BSTR PropertyName,
            /* [out] */ long *Minimum,
            /* [out] */ long *Maximum,
            /* [out] */ TabletPropertyMetricUnit *Units,
            /* [out] */ float *Resolution) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPoints( 
            /* [in][defaultvalue] */ long Index,
            /* [in][defaultvalue] */ long Count,
            /* [retval][out] */ VARIANT *Points) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPoints( 
            /* [in] */ VARIANT Points,
            /* [defaultvalue][in] */ long Index,
            /* [defaultvalue][in] */ long Count,
            /* [retval][out] */ long *NumberOfPointsSet) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPacketData( 
            /* [defaultvalue][in] */ long Index,
            /* [defaultvalue][in] */ long Count,
            /* [retval][out] */ VARIANT *PacketData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPacketValuesByProperty( 
            /* [in] */ BSTR PropertyName,
            /* [defaultvalue][in] */ long Index,
            /* [defaultvalue][in] */ long Count,
            /* [retval][out] */ VARIANT *PacketValues) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPacketValuesByProperty( 
            /* [in] */ BSTR bstrPropertyName,
            /* [in] */ VARIANT PacketValues,
            /* [defaultvalue][in] */ long Index,
            /* [defaultvalue][in] */ long Count,
            /* [retval][out] */ long *NumberOfPacketsSet) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFlattenedBezierPoints( 
            /* [defaultvalue][in] */ long FittingError,
            /* [retval][out] */ VARIANT *FlattenedBezierPoints) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IInkTransform *Transform,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleToRectangle( 
            /* [in] */ IInkRectangle *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x = 0,
            /* [defaultvalue][in] */ float y = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Shear( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleTransform( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkStrokeDispVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkStrokeDisp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkStrokeDisp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkStrokeDisp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkStrokeDisp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkStrokeDisp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkStrokeDisp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkStrokeDisp * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ long *ID);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BezierPoints )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ VARIANT *Points);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawingAttributes )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ IInkDrawingAttributes **DrawAttrs);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DrawingAttributes )( 
            IInkStrokeDisp * This,
            /* [in] */ IInkDrawingAttributes *DrawAttrs);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ink )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ IInkDisp **Ink);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExtendedProperties )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ IInkExtendedProperties **Properties);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PolylineCusps )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ VARIANT *Cusps);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BezierCusps )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ VARIANT *Cusps);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SelfIntersections )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ VARIANT *Intersections);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PacketCount )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ long *plCount);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PacketSize )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ long *plSize);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PacketDescription )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ VARIANT *PacketDescription);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Deleted )( 
            IInkStrokeDisp * This,
            /* [retval][out] */ VARIANT_BOOL *Deleted);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetBoundingBox )( 
            IInkStrokeDisp * This,
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle **Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FindIntersections )( 
            IInkStrokeDisp * This,
            /* [in] */ IInkStrokes *Strokes,
            /* [retval][out] */ VARIANT *Intersections);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRectangleIntersections )( 
            IInkStrokeDisp * This,
            /* [in] */ IInkRectangle *Rectangle,
            /* [retval][out] */ VARIANT *Intersections);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clip )( 
            IInkStrokeDisp * This,
            /* [in] */ IInkRectangle *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HitTestCircle )( 
            IInkStrokeDisp * This,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ float Radius,
            /* [retval][out] */ VARIANT_BOOL *Intersects);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NearestPoint )( 
            IInkStrokeDisp * This,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [defaultvalue][out][in] */ float *Distance,
            /* [retval][out] */ float *Point);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Split )( 
            IInkStrokeDisp * This,
            /* [in] */ float SplitAt,
            /* [retval][out] */ IInkStrokeDisp **NewStroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPacketDescriptionPropertyMetrics )( 
            IInkStrokeDisp * This,
            /* [in] */ BSTR PropertyName,
            /* [out] */ long *Minimum,
            /* [out] */ long *Maximum,
            /* [out] */ TabletPropertyMetricUnit *Units,
            /* [out] */ float *Resolution);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPoints )( 
            IInkStrokeDisp * This,
            /* [in][defaultvalue] */ long Index,
            /* [in][defaultvalue] */ long Count,
            /* [retval][out] */ VARIANT *Points);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPoints )( 
            IInkStrokeDisp * This,
            /* [in] */ VARIANT Points,
            /* [defaultvalue][in] */ long Index,
            /* [defaultvalue][in] */ long Count,
            /* [retval][out] */ long *NumberOfPointsSet);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPacketData )( 
            IInkStrokeDisp * This,
            /* [defaultvalue][in] */ long Index,
            /* [defaultvalue][in] */ long Count,
            /* [retval][out] */ VARIANT *PacketData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPacketValuesByProperty )( 
            IInkStrokeDisp * This,
            /* [in] */ BSTR PropertyName,
            /* [defaultvalue][in] */ long Index,
            /* [defaultvalue][in] */ long Count,
            /* [retval][out] */ VARIANT *PacketValues);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPacketValuesByProperty )( 
            IInkStrokeDisp * This,
            /* [in] */ BSTR bstrPropertyName,
            /* [in] */ VARIANT PacketValues,
            /* [defaultvalue][in] */ long Index,
            /* [defaultvalue][in] */ long Count,
            /* [retval][out] */ long *NumberOfPacketsSet);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFlattenedBezierPoints )( 
            IInkStrokeDisp * This,
            /* [defaultvalue][in] */ long FittingError,
            /* [retval][out] */ VARIANT *FlattenedBezierPoints);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IInkStrokeDisp * This,
            /* [in] */ IInkTransform *Transform,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScaleToRectangle )( 
            IInkStrokeDisp * This,
            /* [in] */ IInkRectangle *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IInkStrokeDisp * This,
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            IInkStrokeDisp * This,
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x,
            /* [defaultvalue][in] */ float y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Shear )( 
            IInkStrokeDisp * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScaleTransform )( 
            IInkStrokeDisp * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier);
        
        END_INTERFACE
    } IInkStrokeDispVtbl;

    interface IInkStrokeDisp
    {
        CONST_VTBL struct IInkStrokeDispVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkStrokeDisp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkStrokeDisp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkStrokeDisp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkStrokeDisp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkStrokeDisp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkStrokeDisp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkStrokeDisp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkStrokeDisp_get_ID(This,ID)	\
    (This)->lpVtbl -> get_ID(This,ID)

#define IInkStrokeDisp_get_BezierPoints(This,Points)	\
    (This)->lpVtbl -> get_BezierPoints(This,Points)

#define IInkStrokeDisp_get_DrawingAttributes(This,DrawAttrs)	\
    (This)->lpVtbl -> get_DrawingAttributes(This,DrawAttrs)

#define IInkStrokeDisp_putref_DrawingAttributes(This,DrawAttrs)	\
    (This)->lpVtbl -> putref_DrawingAttributes(This,DrawAttrs)

#define IInkStrokeDisp_get_Ink(This,Ink)	\
    (This)->lpVtbl -> get_Ink(This,Ink)

#define IInkStrokeDisp_get_ExtendedProperties(This,Properties)	\
    (This)->lpVtbl -> get_ExtendedProperties(This,Properties)

#define IInkStrokeDisp_get_PolylineCusps(This,Cusps)	\
    (This)->lpVtbl -> get_PolylineCusps(This,Cusps)

#define IInkStrokeDisp_get_BezierCusps(This,Cusps)	\
    (This)->lpVtbl -> get_BezierCusps(This,Cusps)

#define IInkStrokeDisp_get_SelfIntersections(This,Intersections)	\
    (This)->lpVtbl -> get_SelfIntersections(This,Intersections)

#define IInkStrokeDisp_get_PacketCount(This,plCount)	\
    (This)->lpVtbl -> get_PacketCount(This,plCount)

#define IInkStrokeDisp_get_PacketSize(This,plSize)	\
    (This)->lpVtbl -> get_PacketSize(This,plSize)

#define IInkStrokeDisp_get_PacketDescription(This,PacketDescription)	\
    (This)->lpVtbl -> get_PacketDescription(This,PacketDescription)

#define IInkStrokeDisp_get_Deleted(This,Deleted)	\
    (This)->lpVtbl -> get_Deleted(This,Deleted)

#define IInkStrokeDisp_GetBoundingBox(This,BoundingBoxMode,Rectangle)	\
    (This)->lpVtbl -> GetBoundingBox(This,BoundingBoxMode,Rectangle)

#define IInkStrokeDisp_FindIntersections(This,Strokes,Intersections)	\
    (This)->lpVtbl -> FindIntersections(This,Strokes,Intersections)

#define IInkStrokeDisp_GetRectangleIntersections(This,Rectangle,Intersections)	\
    (This)->lpVtbl -> GetRectangleIntersections(This,Rectangle,Intersections)

#define IInkStrokeDisp_Clip(This,Rectangle)	\
    (This)->lpVtbl -> Clip(This,Rectangle)

#define IInkStrokeDisp_HitTestCircle(This,X,Y,Radius,Intersects)	\
    (This)->lpVtbl -> HitTestCircle(This,X,Y,Radius,Intersects)

#define IInkStrokeDisp_NearestPoint(This,X,Y,Distance,Point)	\
    (This)->lpVtbl -> NearestPoint(This,X,Y,Distance,Point)

#define IInkStrokeDisp_Split(This,SplitAt,NewStroke)	\
    (This)->lpVtbl -> Split(This,SplitAt,NewStroke)

#define IInkStrokeDisp_GetPacketDescriptionPropertyMetrics(This,PropertyName,Minimum,Maximum,Units,Resolution)	\
    (This)->lpVtbl -> GetPacketDescriptionPropertyMetrics(This,PropertyName,Minimum,Maximum,Units,Resolution)

#define IInkStrokeDisp_GetPoints(This,Index,Count,Points)	\
    (This)->lpVtbl -> GetPoints(This,Index,Count,Points)

#define IInkStrokeDisp_SetPoints(This,Points,Index,Count,NumberOfPointsSet)	\
    (This)->lpVtbl -> SetPoints(This,Points,Index,Count,NumberOfPointsSet)

#define IInkStrokeDisp_GetPacketData(This,Index,Count,PacketData)	\
    (This)->lpVtbl -> GetPacketData(This,Index,Count,PacketData)

#define IInkStrokeDisp_GetPacketValuesByProperty(This,PropertyName,Index,Count,PacketValues)	\
    (This)->lpVtbl -> GetPacketValuesByProperty(This,PropertyName,Index,Count,PacketValues)

#define IInkStrokeDisp_SetPacketValuesByProperty(This,bstrPropertyName,PacketValues,Index,Count,NumberOfPacketsSet)	\
    (This)->lpVtbl -> SetPacketValuesByProperty(This,bstrPropertyName,PacketValues,Index,Count,NumberOfPacketsSet)

#define IInkStrokeDisp_GetFlattenedBezierPoints(This,FittingError,FlattenedBezierPoints)	\
    (This)->lpVtbl -> GetFlattenedBezierPoints(This,FittingError,FlattenedBezierPoints)

#define IInkStrokeDisp_Transform(This,Transform,ApplyOnPenWidth)	\
    (This)->lpVtbl -> Transform(This,Transform,ApplyOnPenWidth)

#define IInkStrokeDisp_ScaleToRectangle(This,Rectangle)	\
    (This)->lpVtbl -> ScaleToRectangle(This,Rectangle)

#define IInkStrokeDisp_Move(This,HorizontalComponent,VerticalComponent)	\
    (This)->lpVtbl -> Move(This,HorizontalComponent,VerticalComponent)

#define IInkStrokeDisp_Rotate(This,Degrees,x,y)	\
    (This)->lpVtbl -> Rotate(This,Degrees,x,y)

#define IInkStrokeDisp_Shear(This,HorizontalMultiplier,VerticalMultiplier)	\
    (This)->lpVtbl -> Shear(This,HorizontalMultiplier,VerticalMultiplier)

#define IInkStrokeDisp_ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)	\
    (This)->lpVtbl -> ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_ID_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ long *ID);


void __RPC_STUB IInkStrokeDisp_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_BezierPoints_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ VARIANT *Points);


void __RPC_STUB IInkStrokeDisp_get_BezierPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_DrawingAttributes_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ IInkDrawingAttributes **DrawAttrs);


void __RPC_STUB IInkStrokeDisp_get_DrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_putref_DrawingAttributes_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ IInkDrawingAttributes *DrawAttrs);


void __RPC_STUB IInkStrokeDisp_putref_DrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_Ink_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ IInkDisp **Ink);


void __RPC_STUB IInkStrokeDisp_get_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_ExtendedProperties_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ IInkExtendedProperties **Properties);


void __RPC_STUB IInkStrokeDisp_get_ExtendedProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_PolylineCusps_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ VARIANT *Cusps);


void __RPC_STUB IInkStrokeDisp_get_PolylineCusps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_BezierCusps_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ VARIANT *Cusps);


void __RPC_STUB IInkStrokeDisp_get_BezierCusps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_SelfIntersections_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ VARIANT *Intersections);


void __RPC_STUB IInkStrokeDisp_get_SelfIntersections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_PacketCount_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ long *plCount);


void __RPC_STUB IInkStrokeDisp_get_PacketCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_PacketSize_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ long *plSize);


void __RPC_STUB IInkStrokeDisp_get_PacketSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_PacketDescription_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ VARIANT *PacketDescription);


void __RPC_STUB IInkStrokeDisp_get_PacketDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_get_Deleted_Proxy( 
    IInkStrokeDisp * This,
    /* [retval][out] */ VARIANT_BOOL *Deleted);


void __RPC_STUB IInkStrokeDisp_get_Deleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_GetBoundingBox_Proxy( 
    IInkStrokeDisp * This,
    /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
    /* [retval][out] */ IInkRectangle **Rectangle);


void __RPC_STUB IInkStrokeDisp_GetBoundingBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_FindIntersections_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ IInkStrokes *Strokes,
    /* [retval][out] */ VARIANT *Intersections);


void __RPC_STUB IInkStrokeDisp_FindIntersections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_GetRectangleIntersections_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ IInkRectangle *Rectangle,
    /* [retval][out] */ VARIANT *Intersections);


void __RPC_STUB IInkStrokeDisp_GetRectangleIntersections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Clip_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ IInkRectangle *Rectangle);


void __RPC_STUB IInkStrokeDisp_Clip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_HitTestCircle_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ long X,
    /* [in] */ long Y,
    /* [in] */ float Radius,
    /* [retval][out] */ VARIANT_BOOL *Intersects);


void __RPC_STUB IInkStrokeDisp_HitTestCircle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_NearestPoint_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ long X,
    /* [in] */ long Y,
    /* [defaultvalue][out][in] */ float *Distance,
    /* [retval][out] */ float *Point);


void __RPC_STUB IInkStrokeDisp_NearestPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Split_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ float SplitAt,
    /* [retval][out] */ IInkStrokeDisp **NewStroke);


void __RPC_STUB IInkStrokeDisp_Split_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_GetPacketDescriptionPropertyMetrics_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ BSTR PropertyName,
    /* [out] */ long *Minimum,
    /* [out] */ long *Maximum,
    /* [out] */ TabletPropertyMetricUnit *Units,
    /* [out] */ float *Resolution);


void __RPC_STUB IInkStrokeDisp_GetPacketDescriptionPropertyMetrics_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_GetPoints_Proxy( 
    IInkStrokeDisp * This,
    /* [in][defaultvalue] */ long Index,
    /* [in][defaultvalue] */ long Count,
    /* [retval][out] */ VARIANT *Points);


void __RPC_STUB IInkStrokeDisp_GetPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_SetPoints_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ VARIANT Points,
    /* [defaultvalue][in] */ long Index,
    /* [defaultvalue][in] */ long Count,
    /* [retval][out] */ long *NumberOfPointsSet);


void __RPC_STUB IInkStrokeDisp_SetPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_GetPacketData_Proxy( 
    IInkStrokeDisp * This,
    /* [defaultvalue][in] */ long Index,
    /* [defaultvalue][in] */ long Count,
    /* [retval][out] */ VARIANT *PacketData);


void __RPC_STUB IInkStrokeDisp_GetPacketData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_GetPacketValuesByProperty_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ BSTR PropertyName,
    /* [defaultvalue][in] */ long Index,
    /* [defaultvalue][in] */ long Count,
    /* [retval][out] */ VARIANT *PacketValues);


void __RPC_STUB IInkStrokeDisp_GetPacketValuesByProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_SetPacketValuesByProperty_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ BSTR bstrPropertyName,
    /* [in] */ VARIANT PacketValues,
    /* [defaultvalue][in] */ long Index,
    /* [defaultvalue][in] */ long Count,
    /* [retval][out] */ long *NumberOfPacketsSet);


void __RPC_STUB IInkStrokeDisp_SetPacketValuesByProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_GetFlattenedBezierPoints_Proxy( 
    IInkStrokeDisp * This,
    /* [defaultvalue][in] */ long FittingError,
    /* [retval][out] */ VARIANT *FlattenedBezierPoints);


void __RPC_STUB IInkStrokeDisp_GetFlattenedBezierPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Transform_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ IInkTransform *Transform,
    /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);


void __RPC_STUB IInkStrokeDisp_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_ScaleToRectangle_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ IInkRectangle *Rectangle);


void __RPC_STUB IInkStrokeDisp_ScaleToRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Move_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ float HorizontalComponent,
    /* [in] */ float VerticalComponent);


void __RPC_STUB IInkStrokeDisp_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Rotate_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ float Degrees,
    /* [defaultvalue][in] */ float x,
    /* [defaultvalue][in] */ float y);


void __RPC_STUB IInkStrokeDisp_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_Shear_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier);


void __RPC_STUB IInkStrokeDisp_Shear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokeDisp_ScaleTransform_Proxy( 
    IInkStrokeDisp * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier);


void __RPC_STUB IInkStrokeDisp_ScaleTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkStrokeDisp_INTERFACE_DEFINED__ */


#ifndef __IInkStrokes_INTERFACE_DEFINED__
#define __IInkStrokes_INTERFACE_DEFINED__

/* interface IInkStrokes */
/* [unique][dual][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IInkStrokes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F1F4C9D8-590A-4963-B3AE-1935671BB6F3")
    IInkStrokes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ink( 
            /* [retval][out] */ IInkDisp **Ink) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecognitionResult( 
            /* [retval][out] */ IInkRecognitionResult **RecognitionResult) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ToString( 
            /* [retval][out] */ BSTR *ToString) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IInkStrokeDisp **Stroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ IInkStrokeDisp *InkStroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddStrokes( 
            /* [in] */ IInkStrokes *InkStrokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ IInkStrokeDisp *InkStroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveStrokes( 
            /* [in] */ IInkStrokes *InkStrokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ModifyDrawingAttributes( 
            /* [in] */ IInkDrawingAttributes *DrawAttrs) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBoundingBox( 
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle **BoundingBox) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IInkTransform *Transform,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleToRectangle( 
            /* [in] */ IInkRectangle *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x = 0,
            /* [defaultvalue][in] */ float y = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Shear( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleTransform( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clip( 
            /* [in] */ IInkRectangle *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveRecognitionResult( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkStrokesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkStrokes * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkStrokes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkStrokes * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkStrokes * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkStrokes * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkStrokes * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkStrokes * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IInkStrokes * This,
            /* [retval][out] */ long *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IInkStrokes * This,
            /* [retval][out] */ IUnknown **_NewEnum);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ink )( 
            IInkStrokes * This,
            /* [retval][out] */ IInkDisp **Ink);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RecognitionResult )( 
            IInkStrokes * This,
            /* [retval][out] */ IInkRecognitionResult **RecognitionResult);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToString )( 
            IInkStrokes * This,
            /* [retval][out] */ BSTR *ToString);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IInkStrokes * This,
            /* [in] */ long Index,
            /* [retval][out] */ IInkStrokeDisp **Stroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IInkStrokes * This,
            /* [in] */ IInkStrokeDisp *InkStroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddStrokes )( 
            IInkStrokes * This,
            /* [in] */ IInkStrokes *InkStrokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IInkStrokes * This,
            /* [in] */ IInkStrokeDisp *InkStroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveStrokes )( 
            IInkStrokes * This,
            /* [in] */ IInkStrokes *InkStrokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ModifyDrawingAttributes )( 
            IInkStrokes * This,
            /* [in] */ IInkDrawingAttributes *DrawAttrs);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetBoundingBox )( 
            IInkStrokes * This,
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle **BoundingBox);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IInkStrokes * This,
            /* [in] */ IInkTransform *Transform,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScaleToRectangle )( 
            IInkStrokes * This,
            /* [in] */ IInkRectangle *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IInkStrokes * This,
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            IInkStrokes * This,
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x,
            /* [defaultvalue][in] */ float y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Shear )( 
            IInkStrokes * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScaleTransform )( 
            IInkStrokes * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clip )( 
            IInkStrokes * This,
            /* [in] */ IInkRectangle *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveRecognitionResult )( 
            IInkStrokes * This);
        
        END_INTERFACE
    } IInkStrokesVtbl;

    interface IInkStrokes
    {
        CONST_VTBL struct IInkStrokesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkStrokes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkStrokes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkStrokes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkStrokes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkStrokes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkStrokes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkStrokes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkStrokes_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkStrokes_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkStrokes_get_Ink(This,Ink)	\
    (This)->lpVtbl -> get_Ink(This,Ink)

#define IInkStrokes_get_RecognitionResult(This,RecognitionResult)	\
    (This)->lpVtbl -> get_RecognitionResult(This,RecognitionResult)

#define IInkStrokes_ToString(This,ToString)	\
    (This)->lpVtbl -> ToString(This,ToString)

#define IInkStrokes_Item(This,Index,Stroke)	\
    (This)->lpVtbl -> Item(This,Index,Stroke)

#define IInkStrokes_Add(This,InkStroke)	\
    (This)->lpVtbl -> Add(This,InkStroke)

#define IInkStrokes_AddStrokes(This,InkStrokes)	\
    (This)->lpVtbl -> AddStrokes(This,InkStrokes)

#define IInkStrokes_Remove(This,InkStroke)	\
    (This)->lpVtbl -> Remove(This,InkStroke)

#define IInkStrokes_RemoveStrokes(This,InkStrokes)	\
    (This)->lpVtbl -> RemoveStrokes(This,InkStrokes)

#define IInkStrokes_ModifyDrawingAttributes(This,DrawAttrs)	\
    (This)->lpVtbl -> ModifyDrawingAttributes(This,DrawAttrs)

#define IInkStrokes_GetBoundingBox(This,BoundingBoxMode,BoundingBox)	\
    (This)->lpVtbl -> GetBoundingBox(This,BoundingBoxMode,BoundingBox)

#define IInkStrokes_Transform(This,Transform,ApplyOnPenWidth)	\
    (This)->lpVtbl -> Transform(This,Transform,ApplyOnPenWidth)

#define IInkStrokes_ScaleToRectangle(This,Rectangle)	\
    (This)->lpVtbl -> ScaleToRectangle(This,Rectangle)

#define IInkStrokes_Move(This,HorizontalComponent,VerticalComponent)	\
    (This)->lpVtbl -> Move(This,HorizontalComponent,VerticalComponent)

#define IInkStrokes_Rotate(This,Degrees,x,y)	\
    (This)->lpVtbl -> Rotate(This,Degrees,x,y)

#define IInkStrokes_Shear(This,HorizontalMultiplier,VerticalMultiplier)	\
    (This)->lpVtbl -> Shear(This,HorizontalMultiplier,VerticalMultiplier)

#define IInkStrokes_ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)	\
    (This)->lpVtbl -> ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier)

#define IInkStrokes_Clip(This,Rectangle)	\
    (This)->lpVtbl -> Clip(This,Rectangle)

#define IInkStrokes_RemoveRecognitionResult(This)	\
    (This)->lpVtbl -> RemoveRecognitionResult(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokes_get_Count_Proxy( 
    IInkStrokes * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB IInkStrokes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokes_get__NewEnum_Proxy( 
    IInkStrokes * This,
    /* [retval][out] */ IUnknown **_NewEnum);


void __RPC_STUB IInkStrokes_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokes_get_Ink_Proxy( 
    IInkStrokes * This,
    /* [retval][out] */ IInkDisp **Ink);


void __RPC_STUB IInkStrokes_get_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkStrokes_get_RecognitionResult_Proxy( 
    IInkStrokes * This,
    /* [retval][out] */ IInkRecognitionResult **RecognitionResult);


void __RPC_STUB IInkStrokes_get_RecognitionResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_ToString_Proxy( 
    IInkStrokes * This,
    /* [retval][out] */ BSTR *ToString);


void __RPC_STUB IInkStrokes_ToString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Item_Proxy( 
    IInkStrokes * This,
    /* [in] */ long Index,
    /* [retval][out] */ IInkStrokeDisp **Stroke);


void __RPC_STUB IInkStrokes_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Add_Proxy( 
    IInkStrokes * This,
    /* [in] */ IInkStrokeDisp *InkStroke);


void __RPC_STUB IInkStrokes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_AddStrokes_Proxy( 
    IInkStrokes * This,
    /* [in] */ IInkStrokes *InkStrokes);


void __RPC_STUB IInkStrokes_AddStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Remove_Proxy( 
    IInkStrokes * This,
    /* [in] */ IInkStrokeDisp *InkStroke);


void __RPC_STUB IInkStrokes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_RemoveStrokes_Proxy( 
    IInkStrokes * This,
    /* [in] */ IInkStrokes *InkStrokes);


void __RPC_STUB IInkStrokes_RemoveStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_ModifyDrawingAttributes_Proxy( 
    IInkStrokes * This,
    /* [in] */ IInkDrawingAttributes *DrawAttrs);


void __RPC_STUB IInkStrokes_ModifyDrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_GetBoundingBox_Proxy( 
    IInkStrokes * This,
    /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
    /* [retval][out] */ IInkRectangle **BoundingBox);


void __RPC_STUB IInkStrokes_GetBoundingBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Transform_Proxy( 
    IInkStrokes * This,
    /* [in] */ IInkTransform *Transform,
    /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);


void __RPC_STUB IInkStrokes_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_ScaleToRectangle_Proxy( 
    IInkStrokes * This,
    /* [in] */ IInkRectangle *Rectangle);


void __RPC_STUB IInkStrokes_ScaleToRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Move_Proxy( 
    IInkStrokes * This,
    /* [in] */ float HorizontalComponent,
    /* [in] */ float VerticalComponent);


void __RPC_STUB IInkStrokes_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Rotate_Proxy( 
    IInkStrokes * This,
    /* [in] */ float Degrees,
    /* [defaultvalue][in] */ float x,
    /* [defaultvalue][in] */ float y);


void __RPC_STUB IInkStrokes_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Shear_Proxy( 
    IInkStrokes * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier);


void __RPC_STUB IInkStrokes_Shear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_ScaleTransform_Proxy( 
    IInkStrokes * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier);


void __RPC_STUB IInkStrokes_ScaleTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_Clip_Proxy( 
    IInkStrokes * This,
    /* [in] */ IInkRectangle *Rectangle);


void __RPC_STUB IInkStrokes_Clip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkStrokes_RemoveRecognitionResult_Proxy( 
    IInkStrokes * This);


void __RPC_STUB IInkStrokes_RemoveRecognitionResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkStrokes_INTERFACE_DEFINED__ */


#ifndef __IInkCustomStrokes_INTERFACE_DEFINED__
#define __IInkCustomStrokes_INTERFACE_DEFINED__

/* interface IInkCustomStrokes */
/* [unique][dual][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IInkCustomStrokes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7E23A88F-C30E-420f-9BDB-28902543F0C1")
    IInkCustomStrokes : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Identifier,
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [in] */ IInkStrokes *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Identifier) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkCustomStrokesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkCustomStrokes * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkCustomStrokes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkCustomStrokes * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkCustomStrokes * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkCustomStrokes * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkCustomStrokes * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkCustomStrokes * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IInkCustomStrokes * This,
            /* [retval][out] */ long *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IInkCustomStrokes * This,
            /* [retval][out] */ IUnknown **_NewEnum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IInkCustomStrokes * This,
            /* [in] */ VARIANT Identifier,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IInkCustomStrokes * This,
            /* [in] */ BSTR Name,
            /* [in] */ IInkStrokes *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IInkCustomStrokes * This,
            /* [in] */ VARIANT Identifier);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IInkCustomStrokes * This);
        
        END_INTERFACE
    } IInkCustomStrokesVtbl;

    interface IInkCustomStrokes
    {
        CONST_VTBL struct IInkCustomStrokesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkCustomStrokes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkCustomStrokes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkCustomStrokes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkCustomStrokes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkCustomStrokes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkCustomStrokes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkCustomStrokes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkCustomStrokes_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkCustomStrokes_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkCustomStrokes_Item(This,Identifier,Strokes)	\
    (This)->lpVtbl -> Item(This,Identifier,Strokes)

#define IInkCustomStrokes_Add(This,Name,Strokes)	\
    (This)->lpVtbl -> Add(This,Name,Strokes)

#define IInkCustomStrokes_Remove(This,Identifier)	\
    (This)->lpVtbl -> Remove(This,Identifier)

#define IInkCustomStrokes_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_get_Count_Proxy( 
    IInkCustomStrokes * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB IInkCustomStrokes_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_get__NewEnum_Proxy( 
    IInkCustomStrokes * This,
    /* [retval][out] */ IUnknown **_NewEnum);


void __RPC_STUB IInkCustomStrokes_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_Item_Proxy( 
    IInkCustomStrokes * This,
    /* [in] */ VARIANT Identifier,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkCustomStrokes_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_Add_Proxy( 
    IInkCustomStrokes * This,
    /* [in] */ BSTR Name,
    /* [in] */ IInkStrokes *Strokes);


void __RPC_STUB IInkCustomStrokes_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_Remove_Proxy( 
    IInkCustomStrokes * This,
    /* [in] */ VARIANT Identifier);


void __RPC_STUB IInkCustomStrokes_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCustomStrokes_Clear_Proxy( 
    IInkCustomStrokes * This);


void __RPC_STUB IInkCustomStrokes_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkCustomStrokes_INTERFACE_DEFINED__ */


#ifndef ___IInkStrokesEvents_DISPINTERFACE_DEFINED__
#define ___IInkStrokesEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IInkStrokesEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IInkStrokesEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F33053EC-5D25-430a-928F-76A6491DDE15")
    _IInkStrokesEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IInkStrokesEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IInkStrokesEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IInkStrokesEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IInkStrokesEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IInkStrokesEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IInkStrokesEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IInkStrokesEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IInkStrokesEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IInkStrokesEventsVtbl;

    interface _IInkStrokesEvents
    {
        CONST_VTBL struct _IInkStrokesEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IInkStrokesEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IInkStrokesEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IInkStrokesEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IInkStrokesEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IInkStrokesEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IInkStrokesEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IInkStrokesEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IInkStrokesEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IInkDisp_INTERFACE_DEFINED__
#define __IInkDisp_INTERFACE_DEFINED__

/* interface IInkDisp */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkDisp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9D398FA0-C4E2-4fcd-9973-975CAAF47EA6")
    IInkDisp : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExtendedProperties( 
            /* [retval][out] */ IInkExtendedProperties **Properties) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Dirty( 
            /* [retval][out] */ VARIANT_BOOL *Dirty) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Dirty( 
            /* [in] */ VARIANT_BOOL Dirty) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CustomStrokes( 
            /* [retval][out] */ IInkCustomStrokes **ppunkInkCustomStrokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBoundingBox( 
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle **Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteStrokes( 
            /* [defaultvalue][in] */ IInkStrokes *Strokes = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteStroke( 
            /* [in] */ IInkStrokeDisp *Stroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ExtractStrokes( 
            /* [defaultvalue][in] */ IInkStrokes *Strokes,
            /* [defaultvalue][in] */ InkExtractFlags ExtractFlags,
            /* [retval][out] */ IInkDisp **ExtractedInk) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ExtractWithRectangle( 
            /* [in] */ IInkRectangle *Rectangle,
            /* [defaultvalue][in] */ InkExtractFlags extractFlags,
            /* [retval][out] */ IInkDisp **ExtractedInk) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clip( 
            /* [in] */ IInkRectangle *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IInkDisp **NewInk) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE HitTestCircle( 
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ float radius,
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE HitTestWithRectangle( 
            /* [in] */ IInkRectangle *SelectionRectangle,
            /* [in] */ float IntersectPercent,
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE HitTestWithLasso( 
            /* [in] */ VARIANT Points,
            /* [in] */ float IntersectPercent,
            /* [defaultvalue][out][in] */ VARIANT *LassoPoints,
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE NearestPoint( 
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [defaultvalue][out][in] */ float *PointOnStroke,
            /* [defaultvalue][out][in] */ float *DistanceFromPacket,
            /* [retval][out] */ IInkStrokeDisp **Stroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateStrokes( 
            /* [defaultvalue][in] */ VARIANT StrokeIds,
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddStrokesAtRectangle( 
            /* [in] */ IInkStrokes *SourceStrokes,
            /* [in] */ IInkRectangle *TargetRectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [defaultvalue][in] */ InkPersistenceFormat PersistenceFormat,
            /* [defaultvalue][in] */ InkPersistenceCompressionMode CompressionMode,
            /* [retval][out] */ VARIANT *Data) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ VARIANT Data) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateStroke( 
            /* [in] */ VARIANT PacketData,
            /* [in] */ VARIANT PacketDescription,
            /* [retval][out] */ IInkStrokeDisp **Stroke) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ClipboardCopyWithRectangle( 
            /* [in] */ IInkRectangle *Rectangle,
            /* [defaultvalue][in] */ InkClipboardFormats ClipboardFormats,
            /* [defaultvalue][in] */ InkClipboardModes ClipboardModes,
            /* [retval][out] */ IDataObject **DataObject) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ClipboardCopy( 
            /* [defaultvalue][in] */ IInkStrokes *strokes,
            /* [defaultvalue][in] */ InkClipboardFormats ClipboardFormats,
            /* [defaultvalue][in] */ InkClipboardModes ClipboardModes,
            /* [retval][out] */ IDataObject **DataObject) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CanPaste( 
            /* [defaultvalue][in] */ IDataObject *DataObject,
            /* [retval][out] */ VARIANT_BOOL *CanPaste) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ClipboardPaste( 
            /* [defaultvalue][in] */ long x,
            /* [defaultvalue][in] */ long y,
            /* [defaultvalue][in] */ IDataObject *DataObject,
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkDispVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkDisp * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkDisp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkDisp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkDisp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkDisp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkDisp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkDisp * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Strokes )( 
            IInkDisp * This,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ExtendedProperties )( 
            IInkDisp * This,
            /* [retval][out] */ IInkExtendedProperties **Properties);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dirty )( 
            IInkDisp * This,
            /* [retval][out] */ VARIANT_BOOL *Dirty);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dirty )( 
            IInkDisp * This,
            /* [in] */ VARIANT_BOOL Dirty);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CustomStrokes )( 
            IInkDisp * This,
            /* [retval][out] */ IInkCustomStrokes **ppunkInkCustomStrokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetBoundingBox )( 
            IInkDisp * This,
            /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
            /* [retval][out] */ IInkRectangle **Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteStrokes )( 
            IInkDisp * This,
            /* [defaultvalue][in] */ IInkStrokes *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DeleteStroke )( 
            IInkDisp * This,
            /* [in] */ IInkStrokeDisp *Stroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExtractStrokes )( 
            IInkDisp * This,
            /* [defaultvalue][in] */ IInkStrokes *Strokes,
            /* [defaultvalue][in] */ InkExtractFlags ExtractFlags,
            /* [retval][out] */ IInkDisp **ExtractedInk);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ExtractWithRectangle )( 
            IInkDisp * This,
            /* [in] */ IInkRectangle *Rectangle,
            /* [defaultvalue][in] */ InkExtractFlags extractFlags,
            /* [retval][out] */ IInkDisp **ExtractedInk);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clip )( 
            IInkDisp * This,
            /* [in] */ IInkRectangle *Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IInkDisp * This,
            /* [retval][out] */ IInkDisp **NewInk);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HitTestCircle )( 
            IInkDisp * This,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [in] */ float radius,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HitTestWithRectangle )( 
            IInkDisp * This,
            /* [in] */ IInkRectangle *SelectionRectangle,
            /* [in] */ float IntersectPercent,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HitTestWithLasso )( 
            IInkDisp * This,
            /* [in] */ VARIANT Points,
            /* [in] */ float IntersectPercent,
            /* [defaultvalue][out][in] */ VARIANT *LassoPoints,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *NearestPoint )( 
            IInkDisp * This,
            /* [in] */ long X,
            /* [in] */ long Y,
            /* [defaultvalue][out][in] */ float *PointOnStroke,
            /* [defaultvalue][out][in] */ float *DistanceFromPacket,
            /* [retval][out] */ IInkStrokeDisp **Stroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateStrokes )( 
            IInkDisp * This,
            /* [defaultvalue][in] */ VARIANT StrokeIds,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddStrokesAtRectangle )( 
            IInkDisp * This,
            /* [in] */ IInkStrokes *SourceStrokes,
            /* [in] */ IInkRectangle *TargetRectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IInkDisp * This,
            /* [defaultvalue][in] */ InkPersistenceFormat PersistenceFormat,
            /* [defaultvalue][in] */ InkPersistenceCompressionMode CompressionMode,
            /* [retval][out] */ VARIANT *Data);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IInkDisp * This,
            /* [in] */ VARIANT Data);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateStroke )( 
            IInkDisp * This,
            /* [in] */ VARIANT PacketData,
            /* [in] */ VARIANT PacketDescription,
            /* [retval][out] */ IInkStrokeDisp **Stroke);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClipboardCopyWithRectangle )( 
            IInkDisp * This,
            /* [in] */ IInkRectangle *Rectangle,
            /* [defaultvalue][in] */ InkClipboardFormats ClipboardFormats,
            /* [defaultvalue][in] */ InkClipboardModes ClipboardModes,
            /* [retval][out] */ IDataObject **DataObject);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClipboardCopy )( 
            IInkDisp * This,
            /* [defaultvalue][in] */ IInkStrokes *strokes,
            /* [defaultvalue][in] */ InkClipboardFormats ClipboardFormats,
            /* [defaultvalue][in] */ InkClipboardModes ClipboardModes,
            /* [retval][out] */ IDataObject **DataObject);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CanPaste )( 
            IInkDisp * This,
            /* [defaultvalue][in] */ IDataObject *DataObject,
            /* [retval][out] */ VARIANT_BOOL *CanPaste);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClipboardPaste )( 
            IInkDisp * This,
            /* [defaultvalue][in] */ long x,
            /* [defaultvalue][in] */ long y,
            /* [defaultvalue][in] */ IDataObject *DataObject,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        END_INTERFACE
    } IInkDispVtbl;

    interface IInkDisp
    {
        CONST_VTBL struct IInkDispVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkDisp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkDisp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkDisp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkDisp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkDisp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkDisp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkDisp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkDisp_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkDisp_get_ExtendedProperties(This,Properties)	\
    (This)->lpVtbl -> get_ExtendedProperties(This,Properties)

#define IInkDisp_get_Dirty(This,Dirty)	\
    (This)->lpVtbl -> get_Dirty(This,Dirty)

#define IInkDisp_put_Dirty(This,Dirty)	\
    (This)->lpVtbl -> put_Dirty(This,Dirty)

#define IInkDisp_get_CustomStrokes(This,ppunkInkCustomStrokes)	\
    (This)->lpVtbl -> get_CustomStrokes(This,ppunkInkCustomStrokes)

#define IInkDisp_GetBoundingBox(This,BoundingBoxMode,Rectangle)	\
    (This)->lpVtbl -> GetBoundingBox(This,BoundingBoxMode,Rectangle)

#define IInkDisp_DeleteStrokes(This,Strokes)	\
    (This)->lpVtbl -> DeleteStrokes(This,Strokes)

#define IInkDisp_DeleteStroke(This,Stroke)	\
    (This)->lpVtbl -> DeleteStroke(This,Stroke)

#define IInkDisp_ExtractStrokes(This,Strokes,ExtractFlags,ExtractedInk)	\
    (This)->lpVtbl -> ExtractStrokes(This,Strokes,ExtractFlags,ExtractedInk)

#define IInkDisp_ExtractWithRectangle(This,Rectangle,extractFlags,ExtractedInk)	\
    (This)->lpVtbl -> ExtractWithRectangle(This,Rectangle,extractFlags,ExtractedInk)

#define IInkDisp_Clip(This,Rectangle)	\
    (This)->lpVtbl -> Clip(This,Rectangle)

#define IInkDisp_Clone(This,NewInk)	\
    (This)->lpVtbl -> Clone(This,NewInk)

#define IInkDisp_HitTestCircle(This,X,Y,radius,Strokes)	\
    (This)->lpVtbl -> HitTestCircle(This,X,Y,radius,Strokes)

#define IInkDisp_HitTestWithRectangle(This,SelectionRectangle,IntersectPercent,Strokes)	\
    (This)->lpVtbl -> HitTestWithRectangle(This,SelectionRectangle,IntersectPercent,Strokes)

#define IInkDisp_HitTestWithLasso(This,Points,IntersectPercent,LassoPoints,Strokes)	\
    (This)->lpVtbl -> HitTestWithLasso(This,Points,IntersectPercent,LassoPoints,Strokes)

#define IInkDisp_NearestPoint(This,X,Y,PointOnStroke,DistanceFromPacket,Stroke)	\
    (This)->lpVtbl -> NearestPoint(This,X,Y,PointOnStroke,DistanceFromPacket,Stroke)

#define IInkDisp_CreateStrokes(This,StrokeIds,Strokes)	\
    (This)->lpVtbl -> CreateStrokes(This,StrokeIds,Strokes)

#define IInkDisp_AddStrokesAtRectangle(This,SourceStrokes,TargetRectangle)	\
    (This)->lpVtbl -> AddStrokesAtRectangle(This,SourceStrokes,TargetRectangle)

#define IInkDisp_Save(This,PersistenceFormat,CompressionMode,Data)	\
    (This)->lpVtbl -> Save(This,PersistenceFormat,CompressionMode,Data)

#define IInkDisp_Load(This,Data)	\
    (This)->lpVtbl -> Load(This,Data)

#define IInkDisp_CreateStroke(This,PacketData,PacketDescription,Stroke)	\
    (This)->lpVtbl -> CreateStroke(This,PacketData,PacketDescription,Stroke)

#define IInkDisp_ClipboardCopyWithRectangle(This,Rectangle,ClipboardFormats,ClipboardModes,DataObject)	\
    (This)->lpVtbl -> ClipboardCopyWithRectangle(This,Rectangle,ClipboardFormats,ClipboardModes,DataObject)

#define IInkDisp_ClipboardCopy(This,strokes,ClipboardFormats,ClipboardModes,DataObject)	\
    (This)->lpVtbl -> ClipboardCopy(This,strokes,ClipboardFormats,ClipboardModes,DataObject)

#define IInkDisp_CanPaste(This,DataObject,CanPaste)	\
    (This)->lpVtbl -> CanPaste(This,DataObject,CanPaste)

#define IInkDisp_ClipboardPaste(This,x,y,DataObject,Strokes)	\
    (This)->lpVtbl -> ClipboardPaste(This,x,y,DataObject,Strokes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDisp_get_Strokes_Proxy( 
    IInkDisp * This,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkDisp_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDisp_get_ExtendedProperties_Proxy( 
    IInkDisp * This,
    /* [retval][out] */ IInkExtendedProperties **Properties);


void __RPC_STUB IInkDisp_get_ExtendedProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDisp_get_Dirty_Proxy( 
    IInkDisp * This,
    /* [retval][out] */ VARIANT_BOOL *Dirty);


void __RPC_STUB IInkDisp_get_Dirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDisp_put_Dirty_Proxy( 
    IInkDisp * This,
    /* [in] */ VARIANT_BOOL Dirty);


void __RPC_STUB IInkDisp_put_Dirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDisp_get_CustomStrokes_Proxy( 
    IInkDisp * This,
    /* [retval][out] */ IInkCustomStrokes **ppunkInkCustomStrokes);


void __RPC_STUB IInkDisp_get_CustomStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_GetBoundingBox_Proxy( 
    IInkDisp * This,
    /* [defaultvalue][in] */ InkBoundingBoxMode BoundingBoxMode,
    /* [retval][out] */ IInkRectangle **Rectangle);


void __RPC_STUB IInkDisp_GetBoundingBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_DeleteStrokes_Proxy( 
    IInkDisp * This,
    /* [defaultvalue][in] */ IInkStrokes *Strokes);


void __RPC_STUB IInkDisp_DeleteStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_DeleteStroke_Proxy( 
    IInkDisp * This,
    /* [in] */ IInkStrokeDisp *Stroke);


void __RPC_STUB IInkDisp_DeleteStroke_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_ExtractStrokes_Proxy( 
    IInkDisp * This,
    /* [defaultvalue][in] */ IInkStrokes *Strokes,
    /* [defaultvalue][in] */ InkExtractFlags ExtractFlags,
    /* [retval][out] */ IInkDisp **ExtractedInk);


void __RPC_STUB IInkDisp_ExtractStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_ExtractWithRectangle_Proxy( 
    IInkDisp * This,
    /* [in] */ IInkRectangle *Rectangle,
    /* [defaultvalue][in] */ InkExtractFlags extractFlags,
    /* [retval][out] */ IInkDisp **ExtractedInk);


void __RPC_STUB IInkDisp_ExtractWithRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_Clip_Proxy( 
    IInkDisp * This,
    /* [in] */ IInkRectangle *Rectangle);


void __RPC_STUB IInkDisp_Clip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_Clone_Proxy( 
    IInkDisp * This,
    /* [retval][out] */ IInkDisp **NewInk);


void __RPC_STUB IInkDisp_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_HitTestCircle_Proxy( 
    IInkDisp * This,
    /* [in] */ long X,
    /* [in] */ long Y,
    /* [in] */ float radius,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkDisp_HitTestCircle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_HitTestWithRectangle_Proxy( 
    IInkDisp * This,
    /* [in] */ IInkRectangle *SelectionRectangle,
    /* [in] */ float IntersectPercent,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkDisp_HitTestWithRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_HitTestWithLasso_Proxy( 
    IInkDisp * This,
    /* [in] */ VARIANT Points,
    /* [in] */ float IntersectPercent,
    /* [defaultvalue][out][in] */ VARIANT *LassoPoints,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkDisp_HitTestWithLasso_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_NearestPoint_Proxy( 
    IInkDisp * This,
    /* [in] */ long X,
    /* [in] */ long Y,
    /* [defaultvalue][out][in] */ float *PointOnStroke,
    /* [defaultvalue][out][in] */ float *DistanceFromPacket,
    /* [retval][out] */ IInkStrokeDisp **Stroke);


void __RPC_STUB IInkDisp_NearestPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_CreateStrokes_Proxy( 
    IInkDisp * This,
    /* [defaultvalue][in] */ VARIANT StrokeIds,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkDisp_CreateStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_AddStrokesAtRectangle_Proxy( 
    IInkDisp * This,
    /* [in] */ IInkStrokes *SourceStrokes,
    /* [in] */ IInkRectangle *TargetRectangle);


void __RPC_STUB IInkDisp_AddStrokesAtRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_Save_Proxy( 
    IInkDisp * This,
    /* [defaultvalue][in] */ InkPersistenceFormat PersistenceFormat,
    /* [defaultvalue][in] */ InkPersistenceCompressionMode CompressionMode,
    /* [retval][out] */ VARIANT *Data);


void __RPC_STUB IInkDisp_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_Load_Proxy( 
    IInkDisp * This,
    /* [in] */ VARIANT Data);


void __RPC_STUB IInkDisp_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_CreateStroke_Proxy( 
    IInkDisp * This,
    /* [in] */ VARIANT PacketData,
    /* [in] */ VARIANT PacketDescription,
    /* [retval][out] */ IInkStrokeDisp **Stroke);


void __RPC_STUB IInkDisp_CreateStroke_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_ClipboardCopyWithRectangle_Proxy( 
    IInkDisp * This,
    /* [in] */ IInkRectangle *Rectangle,
    /* [defaultvalue][in] */ InkClipboardFormats ClipboardFormats,
    /* [defaultvalue][in] */ InkClipboardModes ClipboardModes,
    /* [retval][out] */ IDataObject **DataObject);


void __RPC_STUB IInkDisp_ClipboardCopyWithRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_ClipboardCopy_Proxy( 
    IInkDisp * This,
    /* [defaultvalue][in] */ IInkStrokes *strokes,
    /* [defaultvalue][in] */ InkClipboardFormats ClipboardFormats,
    /* [defaultvalue][in] */ InkClipboardModes ClipboardModes,
    /* [retval][out] */ IDataObject **DataObject);


void __RPC_STUB IInkDisp_ClipboardCopy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_CanPaste_Proxy( 
    IInkDisp * This,
    /* [defaultvalue][in] */ IDataObject *DataObject,
    /* [retval][out] */ VARIANT_BOOL *CanPaste);


void __RPC_STUB IInkDisp_CanPaste_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDisp_ClipboardPaste_Proxy( 
    IInkDisp * This,
    /* [defaultvalue][in] */ long x,
    /* [defaultvalue][in] */ long y,
    /* [defaultvalue][in] */ IDataObject *DataObject,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkDisp_ClipboardPaste_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkDisp_INTERFACE_DEFINED__ */


#ifndef ___IInkEvents_DISPINTERFACE_DEFINED__
#define ___IInkEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IInkEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IInkEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("427B1865-CA3F-479a-83A9-0F420F2A0073")
    _IInkEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IInkEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IInkEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IInkEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IInkEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IInkEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IInkEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IInkEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IInkEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IInkEventsVtbl;

    interface _IInkEvents
    {
        CONST_VTBL struct _IInkEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IInkEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IInkEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IInkEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IInkEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IInkEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IInkEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IInkEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IInkEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IInkRenderer_INTERFACE_DEFINED__
#define __IInkRenderer_INTERFACE_DEFINED__

/* interface IInkRenderer */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRenderer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E6257A9C-B511-4f4c-A8B0-A7DBC9506B83")
    IInkRenderer : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetViewTransform( 
            /* [in] */ IInkTransform *ViewTransform) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetViewTransform( 
            /* [in] */ IInkTransform *ViewTransform) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetObjectTransform( 
            /* [in] */ IInkTransform *ObjectTransform) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetObjectTransform( 
            /* [in] */ IInkTransform *ObjectTransform) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ long hDC,
            /* [in] */ IInkStrokes *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE DrawStroke( 
            /* [in] */ long hDC,
            /* [in] */ IInkStrokeDisp *Stroke,
            /* [defaultvalue][in] */ IInkDrawingAttributes *DrawingAttributes = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE PixelToInkSpace( 
            /* [in] */ long hDC,
            /* [out][in] */ long *x,
            /* [out][in] */ long *y) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE InkSpaceToPixel( 
            /* [in] */ long hdcDisplay,
            /* [out][in] */ long *x,
            /* [out][in] */ long *y) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE PixelToInkSpaceFromPoints( 
            /* [in] */ long hDC,
            /* [out][in] */ VARIANT *Points) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE InkSpaceToPixelFromPoints( 
            /* [in] */ long hDC,
            /* [out][in] */ VARIANT *Points) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Measure( 
            /* [in] */ IInkStrokes *Strokes,
            /* [retval][out] */ IInkRectangle **Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE MeasureStroke( 
            /* [in] */ IInkStrokeDisp *Stroke,
            /* [defaultvalue][in] */ IInkDrawingAttributes *DrawingAttributes,
            /* [retval][out] */ IInkRectangle **Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x = 0,
            /* [defaultvalue][in] */ float y = 0) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleTransform( 
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth = -1) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRendererVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkRenderer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkRenderer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkRenderer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkRenderer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkRenderer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkRenderer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkRenderer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetViewTransform )( 
            IInkRenderer * This,
            /* [in] */ IInkTransform *ViewTransform);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetViewTransform )( 
            IInkRenderer * This,
            /* [in] */ IInkTransform *ViewTransform);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetObjectTransform )( 
            IInkRenderer * This,
            /* [in] */ IInkTransform *ObjectTransform);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetObjectTransform )( 
            IInkRenderer * This,
            /* [in] */ IInkTransform *ObjectTransform);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Draw )( 
            IInkRenderer * This,
            /* [in] */ long hDC,
            /* [in] */ IInkStrokes *Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DrawStroke )( 
            IInkRenderer * This,
            /* [in] */ long hDC,
            /* [in] */ IInkStrokeDisp *Stroke,
            /* [defaultvalue][in] */ IInkDrawingAttributes *DrawingAttributes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PixelToInkSpace )( 
            IInkRenderer * This,
            /* [in] */ long hDC,
            /* [out][in] */ long *x,
            /* [out][in] */ long *y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InkSpaceToPixel )( 
            IInkRenderer * This,
            /* [in] */ long hdcDisplay,
            /* [out][in] */ long *x,
            /* [out][in] */ long *y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PixelToInkSpaceFromPoints )( 
            IInkRenderer * This,
            /* [in] */ long hDC,
            /* [out][in] */ VARIANT *Points);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InkSpaceToPixelFromPoints )( 
            IInkRenderer * This,
            /* [in] */ long hDC,
            /* [out][in] */ VARIANT *Points);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Measure )( 
            IInkRenderer * This,
            /* [in] */ IInkStrokes *Strokes,
            /* [retval][out] */ IInkRectangle **Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MeasureStroke )( 
            IInkRenderer * This,
            /* [in] */ IInkStrokeDisp *Stroke,
            /* [defaultvalue][in] */ IInkDrawingAttributes *DrawingAttributes,
            /* [retval][out] */ IInkRectangle **Rectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Move )( 
            IInkRenderer * This,
            /* [in] */ float HorizontalComponent,
            /* [in] */ float VerticalComponent);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            IInkRenderer * This,
            /* [in] */ float Degrees,
            /* [defaultvalue][in] */ float x,
            /* [defaultvalue][in] */ float y);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScaleTransform )( 
            IInkRenderer * This,
            /* [in] */ float HorizontalMultiplier,
            /* [in] */ float VerticalMultiplier,
            /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);
        
        END_INTERFACE
    } IInkRendererVtbl;

    interface IInkRenderer
    {
        CONST_VTBL struct IInkRendererVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRenderer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRenderer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRenderer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRenderer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRenderer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRenderer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRenderer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRenderer_GetViewTransform(This,ViewTransform)	\
    (This)->lpVtbl -> GetViewTransform(This,ViewTransform)

#define IInkRenderer_SetViewTransform(This,ViewTransform)	\
    (This)->lpVtbl -> SetViewTransform(This,ViewTransform)

#define IInkRenderer_GetObjectTransform(This,ObjectTransform)	\
    (This)->lpVtbl -> GetObjectTransform(This,ObjectTransform)

#define IInkRenderer_SetObjectTransform(This,ObjectTransform)	\
    (This)->lpVtbl -> SetObjectTransform(This,ObjectTransform)

#define IInkRenderer_Draw(This,hDC,Strokes)	\
    (This)->lpVtbl -> Draw(This,hDC,Strokes)

#define IInkRenderer_DrawStroke(This,hDC,Stroke,DrawingAttributes)	\
    (This)->lpVtbl -> DrawStroke(This,hDC,Stroke,DrawingAttributes)

#define IInkRenderer_PixelToInkSpace(This,hDC,x,y)	\
    (This)->lpVtbl -> PixelToInkSpace(This,hDC,x,y)

#define IInkRenderer_InkSpaceToPixel(This,hdcDisplay,x,y)	\
    (This)->lpVtbl -> InkSpaceToPixel(This,hdcDisplay,x,y)

#define IInkRenderer_PixelToInkSpaceFromPoints(This,hDC,Points)	\
    (This)->lpVtbl -> PixelToInkSpaceFromPoints(This,hDC,Points)

#define IInkRenderer_InkSpaceToPixelFromPoints(This,hDC,Points)	\
    (This)->lpVtbl -> InkSpaceToPixelFromPoints(This,hDC,Points)

#define IInkRenderer_Measure(This,Strokes,Rectangle)	\
    (This)->lpVtbl -> Measure(This,Strokes,Rectangle)

#define IInkRenderer_MeasureStroke(This,Stroke,DrawingAttributes,Rectangle)	\
    (This)->lpVtbl -> MeasureStroke(This,Stroke,DrawingAttributes,Rectangle)

#define IInkRenderer_Move(This,HorizontalComponent,VerticalComponent)	\
    (This)->lpVtbl -> Move(This,HorizontalComponent,VerticalComponent)

#define IInkRenderer_Rotate(This,Degrees,x,y)	\
    (This)->lpVtbl -> Rotate(This,Degrees,x,y)

#define IInkRenderer_ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier,ApplyOnPenWidth)	\
    (This)->lpVtbl -> ScaleTransform(This,HorizontalMultiplier,VerticalMultiplier,ApplyOnPenWidth)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_GetViewTransform_Proxy( 
    IInkRenderer * This,
    /* [in] */ IInkTransform *ViewTransform);


void __RPC_STUB IInkRenderer_GetViewTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_SetViewTransform_Proxy( 
    IInkRenderer * This,
    /* [in] */ IInkTransform *ViewTransform);


void __RPC_STUB IInkRenderer_SetViewTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_GetObjectTransform_Proxy( 
    IInkRenderer * This,
    /* [in] */ IInkTransform *ObjectTransform);


void __RPC_STUB IInkRenderer_GetObjectTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_SetObjectTransform_Proxy( 
    IInkRenderer * This,
    /* [in] */ IInkTransform *ObjectTransform);


void __RPC_STUB IInkRenderer_SetObjectTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_Draw_Proxy( 
    IInkRenderer * This,
    /* [in] */ long hDC,
    /* [in] */ IInkStrokes *Strokes);


void __RPC_STUB IInkRenderer_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_DrawStroke_Proxy( 
    IInkRenderer * This,
    /* [in] */ long hDC,
    /* [in] */ IInkStrokeDisp *Stroke,
    /* [defaultvalue][in] */ IInkDrawingAttributes *DrawingAttributes);


void __RPC_STUB IInkRenderer_DrawStroke_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_PixelToInkSpace_Proxy( 
    IInkRenderer * This,
    /* [in] */ long hDC,
    /* [out][in] */ long *x,
    /* [out][in] */ long *y);


void __RPC_STUB IInkRenderer_PixelToInkSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_InkSpaceToPixel_Proxy( 
    IInkRenderer * This,
    /* [in] */ long hdcDisplay,
    /* [out][in] */ long *x,
    /* [out][in] */ long *y);


void __RPC_STUB IInkRenderer_InkSpaceToPixel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_PixelToInkSpaceFromPoints_Proxy( 
    IInkRenderer * This,
    /* [in] */ long hDC,
    /* [out][in] */ VARIANT *Points);


void __RPC_STUB IInkRenderer_PixelToInkSpaceFromPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_InkSpaceToPixelFromPoints_Proxy( 
    IInkRenderer * This,
    /* [in] */ long hDC,
    /* [out][in] */ VARIANT *Points);


void __RPC_STUB IInkRenderer_InkSpaceToPixelFromPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_Measure_Proxy( 
    IInkRenderer * This,
    /* [in] */ IInkStrokes *Strokes,
    /* [retval][out] */ IInkRectangle **Rectangle);


void __RPC_STUB IInkRenderer_Measure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_MeasureStroke_Proxy( 
    IInkRenderer * This,
    /* [in] */ IInkStrokeDisp *Stroke,
    /* [defaultvalue][in] */ IInkDrawingAttributes *DrawingAttributes,
    /* [retval][out] */ IInkRectangle **Rectangle);


void __RPC_STUB IInkRenderer_MeasureStroke_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_Move_Proxy( 
    IInkRenderer * This,
    /* [in] */ float HorizontalComponent,
    /* [in] */ float VerticalComponent);


void __RPC_STUB IInkRenderer_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_Rotate_Proxy( 
    IInkRenderer * This,
    /* [in] */ float Degrees,
    /* [defaultvalue][in] */ float x,
    /* [defaultvalue][in] */ float y);


void __RPC_STUB IInkRenderer_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRenderer_ScaleTransform_Proxy( 
    IInkRenderer * This,
    /* [in] */ float HorizontalMultiplier,
    /* [in] */ float VerticalMultiplier,
    /* [defaultvalue][in] */ VARIANT_BOOL ApplyOnPenWidth);


void __RPC_STUB IInkRenderer_ScaleTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRenderer_INTERFACE_DEFINED__ */


#ifndef __IInkCollector_INTERFACE_DEFINED__
#define __IInkCollector_INTERFACE_DEFINED__

/* interface IInkCollector */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkCollector;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F0F060B5-8B1F-4a7c-89EC-880692588A4F")
    IInkCollector : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ long *CurrentWindow) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hWnd( 
            /* [in] */ long NewWindow) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultDrawingAttributes( 
            /* [retval][out] */ IInkDrawingAttributes **CurrentAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_DefaultDrawingAttributes( 
            /* [in] */ IInkDrawingAttributes *NewAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Renderer( 
            /* [retval][out] */ IInkRenderer **CurrentInkRenderer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Renderer( 
            /* [in] */ IInkRenderer *NewInkRenderer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ink( 
            /* [retval][out] */ IInkDisp **Ink) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Ink( 
            /* [in] */ IInkDisp *NewInk) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoRedraw( 
            /* [retval][out] */ VARIANT_BOOL *AutoRedraw) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoRedraw( 
            /* [in] */ VARIANT_BOOL AutoRedraw) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CollectingInk( 
            /* [retval][out] */ VARIANT_BOOL *Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CollectionMode( 
            /* [retval][out] */ InkCollectionMode *Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CollectionMode( 
            /* [in] */ InkCollectionMode Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DynamicRendering( 
            /* [retval][out] */ VARIANT_BOOL *Enabled) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DynamicRendering( 
            /* [in] */ VARIANT_BOOL Enabled) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DesiredPacketDescription( 
            /* [retval][out] */ VARIANT *PacketGuids) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DesiredPacketDescription( 
            /* [in] */ VARIANT PacketGuids) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouseIcon( 
            /* [retval][out] */ IPictureDisp **MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MouseIcon( 
            /* [in] */ IPictureDisp *MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_MouseIcon( 
            /* [in] */ IPictureDisp *MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MousePointer( 
            /* [retval][out] */ InkMousePointer *MousePointer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MousePointer( 
            /* [in] */ InkMousePointer MousePointer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cursors( 
            /* [retval][out] */ IInkCursors **Cursors) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarginX( 
            /* [retval][out] */ long *MarginX) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarginX( 
            /* [in] */ long MarginX) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarginY( 
            /* [retval][out] */ long *MarginY) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarginY( 
            /* [in] */ long MarginY) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Tablet( 
            /* [retval][out] */ IInkTablet **SingleTablet) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupportHighContrastInk( 
            /* [retval][out] */ VARIANT_BOOL *Support) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SupportHighContrastInk( 
            /* [in] */ VARIANT_BOOL Support) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGestureStatus( 
            /* [in] */ InkApplicationGesture Gesture,
            /* [in] */ VARIANT_BOOL Listen) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGestureStatus( 
            /* [in] */ InkApplicationGesture Gesture,
            /* [retval][out] */ VARIANT_BOOL *Listening) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowInputRectangle( 
            /* [out][in] */ IInkRectangle **WindowInputRectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWindowInputRectangle( 
            /* [in] */ IInkRectangle *WindowInputRectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAllTabletsMode( 
            /* [defaultvalue][in] */ VARIANT_BOOL UseMouseForInput = -1) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSingleTabletIntegratedMode( 
            /* [in] */ IInkTablet *Tablet) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEventInterest( 
            /* [in] */ InkCollectorEventInterest EventId,
            /* [retval][out] */ VARIANT_BOOL *Listen) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventInterest( 
            /* [in] */ InkCollectorEventInterest EventId,
            /* [in] */ VARIANT_BOOL Listen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkCollectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkCollector * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkCollector * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkCollector * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkCollector * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkCollector * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkCollector * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkCollector * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_hWnd )( 
            IInkCollector * This,
            /* [retval][out] */ long *CurrentWindow);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_hWnd )( 
            IInkCollector * This,
            /* [in] */ long NewWindow);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IInkCollector * This,
            /* [retval][out] */ VARIANT_BOOL *Collecting);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IInkCollector * This,
            /* [in] */ VARIANT_BOOL Collecting);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultDrawingAttributes )( 
            IInkCollector * This,
            /* [retval][out] */ IInkDrawingAttributes **CurrentAttributes);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DefaultDrawingAttributes )( 
            IInkCollector * This,
            /* [in] */ IInkDrawingAttributes *NewAttributes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Renderer )( 
            IInkCollector * This,
            /* [retval][out] */ IInkRenderer **CurrentInkRenderer);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Renderer )( 
            IInkCollector * This,
            /* [in] */ IInkRenderer *NewInkRenderer);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ink )( 
            IInkCollector * This,
            /* [retval][out] */ IInkDisp **Ink);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Ink )( 
            IInkCollector * This,
            /* [in] */ IInkDisp *NewInk);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoRedraw )( 
            IInkCollector * This,
            /* [retval][out] */ VARIANT_BOOL *AutoRedraw);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoRedraw )( 
            IInkCollector * This,
            /* [in] */ VARIANT_BOOL AutoRedraw);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CollectingInk )( 
            IInkCollector * This,
            /* [retval][out] */ VARIANT_BOOL *Collecting);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CollectionMode )( 
            IInkCollector * This,
            /* [retval][out] */ InkCollectionMode *Mode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CollectionMode )( 
            IInkCollector * This,
            /* [in] */ InkCollectionMode Mode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DynamicRendering )( 
            IInkCollector * This,
            /* [retval][out] */ VARIANT_BOOL *Enabled);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DynamicRendering )( 
            IInkCollector * This,
            /* [in] */ VARIANT_BOOL Enabled);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DesiredPacketDescription )( 
            IInkCollector * This,
            /* [retval][out] */ VARIANT *PacketGuids);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DesiredPacketDescription )( 
            IInkCollector * This,
            /* [in] */ VARIANT PacketGuids);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MouseIcon )( 
            IInkCollector * This,
            /* [retval][out] */ IPictureDisp **MouseIcon);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MouseIcon )( 
            IInkCollector * This,
            /* [in] */ IPictureDisp *MouseIcon);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_MouseIcon )( 
            IInkCollector * This,
            /* [in] */ IPictureDisp *MouseIcon);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MousePointer )( 
            IInkCollector * This,
            /* [retval][out] */ InkMousePointer *MousePointer);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MousePointer )( 
            IInkCollector * This,
            /* [in] */ InkMousePointer MousePointer);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cursors )( 
            IInkCollector * This,
            /* [retval][out] */ IInkCursors **Cursors);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarginX )( 
            IInkCollector * This,
            /* [retval][out] */ long *MarginX);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarginX )( 
            IInkCollector * This,
            /* [in] */ long MarginX);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarginY )( 
            IInkCollector * This,
            /* [retval][out] */ long *MarginY);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarginY )( 
            IInkCollector * This,
            /* [in] */ long MarginY);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tablet )( 
            IInkCollector * This,
            /* [retval][out] */ IInkTablet **SingleTablet);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SupportHighContrastInk )( 
            IInkCollector * This,
            /* [retval][out] */ VARIANT_BOOL *Support);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SupportHighContrastInk )( 
            IInkCollector * This,
            /* [in] */ VARIANT_BOOL Support);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetGestureStatus )( 
            IInkCollector * This,
            /* [in] */ InkApplicationGesture Gesture,
            /* [in] */ VARIANT_BOOL Listen);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetGestureStatus )( 
            IInkCollector * This,
            /* [in] */ InkApplicationGesture Gesture,
            /* [retval][out] */ VARIANT_BOOL *Listening);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindowInputRectangle )( 
            IInkCollector * This,
            /* [out][in] */ IInkRectangle **WindowInputRectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetWindowInputRectangle )( 
            IInkCollector * This,
            /* [in] */ IInkRectangle *WindowInputRectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAllTabletsMode )( 
            IInkCollector * This,
            /* [defaultvalue][in] */ VARIANT_BOOL UseMouseForInput);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSingleTabletIntegratedMode )( 
            IInkCollector * This,
            /* [in] */ IInkTablet *Tablet);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEventInterest )( 
            IInkCollector * This,
            /* [in] */ InkCollectorEventInterest EventId,
            /* [retval][out] */ VARIANT_BOOL *Listen);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventInterest )( 
            IInkCollector * This,
            /* [in] */ InkCollectorEventInterest EventId,
            /* [in] */ VARIANT_BOOL Listen);
        
        END_INTERFACE
    } IInkCollectorVtbl;

    interface IInkCollector
    {
        CONST_VTBL struct IInkCollectorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkCollector_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkCollector_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkCollector_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkCollector_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkCollector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkCollector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkCollector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkCollector_get_hWnd(This,CurrentWindow)	\
    (This)->lpVtbl -> get_hWnd(This,CurrentWindow)

#define IInkCollector_put_hWnd(This,NewWindow)	\
    (This)->lpVtbl -> put_hWnd(This,NewWindow)

#define IInkCollector_get_Enabled(This,Collecting)	\
    (This)->lpVtbl -> get_Enabled(This,Collecting)

#define IInkCollector_put_Enabled(This,Collecting)	\
    (This)->lpVtbl -> put_Enabled(This,Collecting)

#define IInkCollector_get_DefaultDrawingAttributes(This,CurrentAttributes)	\
    (This)->lpVtbl -> get_DefaultDrawingAttributes(This,CurrentAttributes)

#define IInkCollector_putref_DefaultDrawingAttributes(This,NewAttributes)	\
    (This)->lpVtbl -> putref_DefaultDrawingAttributes(This,NewAttributes)

#define IInkCollector_get_Renderer(This,CurrentInkRenderer)	\
    (This)->lpVtbl -> get_Renderer(This,CurrentInkRenderer)

#define IInkCollector_putref_Renderer(This,NewInkRenderer)	\
    (This)->lpVtbl -> putref_Renderer(This,NewInkRenderer)

#define IInkCollector_get_Ink(This,Ink)	\
    (This)->lpVtbl -> get_Ink(This,Ink)

#define IInkCollector_putref_Ink(This,NewInk)	\
    (This)->lpVtbl -> putref_Ink(This,NewInk)

#define IInkCollector_get_AutoRedraw(This,AutoRedraw)	\
    (This)->lpVtbl -> get_AutoRedraw(This,AutoRedraw)

#define IInkCollector_put_AutoRedraw(This,AutoRedraw)	\
    (This)->lpVtbl -> put_AutoRedraw(This,AutoRedraw)

#define IInkCollector_get_CollectingInk(This,Collecting)	\
    (This)->lpVtbl -> get_CollectingInk(This,Collecting)

#define IInkCollector_get_CollectionMode(This,Mode)	\
    (This)->lpVtbl -> get_CollectionMode(This,Mode)

#define IInkCollector_put_CollectionMode(This,Mode)	\
    (This)->lpVtbl -> put_CollectionMode(This,Mode)

#define IInkCollector_get_DynamicRendering(This,Enabled)	\
    (This)->lpVtbl -> get_DynamicRendering(This,Enabled)

#define IInkCollector_put_DynamicRendering(This,Enabled)	\
    (This)->lpVtbl -> put_DynamicRendering(This,Enabled)

#define IInkCollector_get_DesiredPacketDescription(This,PacketGuids)	\
    (This)->lpVtbl -> get_DesiredPacketDescription(This,PacketGuids)

#define IInkCollector_put_DesiredPacketDescription(This,PacketGuids)	\
    (This)->lpVtbl -> put_DesiredPacketDescription(This,PacketGuids)

#define IInkCollector_get_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> get_MouseIcon(This,MouseIcon)

#define IInkCollector_put_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> put_MouseIcon(This,MouseIcon)

#define IInkCollector_putref_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> putref_MouseIcon(This,MouseIcon)

#define IInkCollector_get_MousePointer(This,MousePointer)	\
    (This)->lpVtbl -> get_MousePointer(This,MousePointer)

#define IInkCollector_put_MousePointer(This,MousePointer)	\
    (This)->lpVtbl -> put_MousePointer(This,MousePointer)

#define IInkCollector_get_Cursors(This,Cursors)	\
    (This)->lpVtbl -> get_Cursors(This,Cursors)

#define IInkCollector_get_MarginX(This,MarginX)	\
    (This)->lpVtbl -> get_MarginX(This,MarginX)

#define IInkCollector_put_MarginX(This,MarginX)	\
    (This)->lpVtbl -> put_MarginX(This,MarginX)

#define IInkCollector_get_MarginY(This,MarginY)	\
    (This)->lpVtbl -> get_MarginY(This,MarginY)

#define IInkCollector_put_MarginY(This,MarginY)	\
    (This)->lpVtbl -> put_MarginY(This,MarginY)

#define IInkCollector_get_Tablet(This,SingleTablet)	\
    (This)->lpVtbl -> get_Tablet(This,SingleTablet)

#define IInkCollector_get_SupportHighContrastInk(This,Support)	\
    (This)->lpVtbl -> get_SupportHighContrastInk(This,Support)

#define IInkCollector_put_SupportHighContrastInk(This,Support)	\
    (This)->lpVtbl -> put_SupportHighContrastInk(This,Support)

#define IInkCollector_SetGestureStatus(This,Gesture,Listen)	\
    (This)->lpVtbl -> SetGestureStatus(This,Gesture,Listen)

#define IInkCollector_GetGestureStatus(This,Gesture,Listening)	\
    (This)->lpVtbl -> GetGestureStatus(This,Gesture,Listening)

#define IInkCollector_GetWindowInputRectangle(This,WindowInputRectangle)	\
    (This)->lpVtbl -> GetWindowInputRectangle(This,WindowInputRectangle)

#define IInkCollector_SetWindowInputRectangle(This,WindowInputRectangle)	\
    (This)->lpVtbl -> SetWindowInputRectangle(This,WindowInputRectangle)

#define IInkCollector_SetAllTabletsMode(This,UseMouseForInput)	\
    (This)->lpVtbl -> SetAllTabletsMode(This,UseMouseForInput)

#define IInkCollector_SetSingleTabletIntegratedMode(This,Tablet)	\
    (This)->lpVtbl -> SetSingleTabletIntegratedMode(This,Tablet)

#define IInkCollector_GetEventInterest(This,EventId,Listen)	\
    (This)->lpVtbl -> GetEventInterest(This,EventId,Listen)

#define IInkCollector_SetEventInterest(This,EventId,Listen)	\
    (This)->lpVtbl -> SetEventInterest(This,EventId,Listen)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_hWnd_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ long *CurrentWindow);


void __RPC_STUB IInkCollector_get_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkCollector_put_hWnd_Proxy( 
    IInkCollector * This,
    /* [in] */ long NewWindow);


void __RPC_STUB IInkCollector_put_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_Enabled_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ VARIANT_BOOL *Collecting);


void __RPC_STUB IInkCollector_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkCollector_put_Enabled_Proxy( 
    IInkCollector * This,
    /* [in] */ VARIANT_BOOL Collecting);


void __RPC_STUB IInkCollector_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_DefaultDrawingAttributes_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ IInkDrawingAttributes **CurrentAttributes);


void __RPC_STUB IInkCollector_get_DefaultDrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkCollector_putref_DefaultDrawingAttributes_Proxy( 
    IInkCollector * This,
    /* [in] */ IInkDrawingAttributes *NewAttributes);


void __RPC_STUB IInkCollector_putref_DefaultDrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_Renderer_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ IInkRenderer **CurrentInkRenderer);


void __RPC_STUB IInkCollector_get_Renderer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkCollector_putref_Renderer_Proxy( 
    IInkCollector * This,
    /* [in] */ IInkRenderer *NewInkRenderer);


void __RPC_STUB IInkCollector_putref_Renderer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_Ink_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ IInkDisp **Ink);


void __RPC_STUB IInkCollector_get_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkCollector_putref_Ink_Proxy( 
    IInkCollector * This,
    /* [in] */ IInkDisp *NewInk);


void __RPC_STUB IInkCollector_putref_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_AutoRedraw_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ VARIANT_BOOL *AutoRedraw);


void __RPC_STUB IInkCollector_get_AutoRedraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkCollector_put_AutoRedraw_Proxy( 
    IInkCollector * This,
    /* [in] */ VARIANT_BOOL AutoRedraw);


void __RPC_STUB IInkCollector_put_AutoRedraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_CollectingInk_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ VARIANT_BOOL *Collecting);


void __RPC_STUB IInkCollector_get_CollectingInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_CollectionMode_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ InkCollectionMode *Mode);


void __RPC_STUB IInkCollector_get_CollectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkCollector_put_CollectionMode_Proxy( 
    IInkCollector * This,
    /* [in] */ InkCollectionMode Mode);


void __RPC_STUB IInkCollector_put_CollectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_DynamicRendering_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ VARIANT_BOOL *Enabled);


void __RPC_STUB IInkCollector_get_DynamicRendering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkCollector_put_DynamicRendering_Proxy( 
    IInkCollector * This,
    /* [in] */ VARIANT_BOOL Enabled);


void __RPC_STUB IInkCollector_put_DynamicRendering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_DesiredPacketDescription_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ VARIANT *PacketGuids);


void __RPC_STUB IInkCollector_get_DesiredPacketDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkCollector_put_DesiredPacketDescription_Proxy( 
    IInkCollector * This,
    /* [in] */ VARIANT PacketGuids);


void __RPC_STUB IInkCollector_put_DesiredPacketDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_MouseIcon_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ IPictureDisp **MouseIcon);


void __RPC_STUB IInkCollector_get_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkCollector_put_MouseIcon_Proxy( 
    IInkCollector * This,
    /* [in] */ IPictureDisp *MouseIcon);


void __RPC_STUB IInkCollector_put_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkCollector_putref_MouseIcon_Proxy( 
    IInkCollector * This,
    /* [in] */ IPictureDisp *MouseIcon);


void __RPC_STUB IInkCollector_putref_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_MousePointer_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ InkMousePointer *MousePointer);


void __RPC_STUB IInkCollector_get_MousePointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkCollector_put_MousePointer_Proxy( 
    IInkCollector * This,
    /* [in] */ InkMousePointer MousePointer);


void __RPC_STUB IInkCollector_put_MousePointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_Cursors_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ IInkCursors **Cursors);


void __RPC_STUB IInkCollector_get_Cursors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_MarginX_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ long *MarginX);


void __RPC_STUB IInkCollector_get_MarginX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkCollector_put_MarginX_Proxy( 
    IInkCollector * This,
    /* [in] */ long MarginX);


void __RPC_STUB IInkCollector_put_MarginX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_MarginY_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ long *MarginY);


void __RPC_STUB IInkCollector_get_MarginY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkCollector_put_MarginY_Proxy( 
    IInkCollector * This,
    /* [in] */ long MarginY);


void __RPC_STUB IInkCollector_put_MarginY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_Tablet_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ IInkTablet **SingleTablet);


void __RPC_STUB IInkCollector_get_Tablet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkCollector_get_SupportHighContrastInk_Proxy( 
    IInkCollector * This,
    /* [retval][out] */ VARIANT_BOOL *Support);


void __RPC_STUB IInkCollector_get_SupportHighContrastInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkCollector_put_SupportHighContrastInk_Proxy( 
    IInkCollector * This,
    /* [in] */ VARIANT_BOOL Support);


void __RPC_STUB IInkCollector_put_SupportHighContrastInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCollector_SetGestureStatus_Proxy( 
    IInkCollector * This,
    /* [in] */ InkApplicationGesture Gesture,
    /* [in] */ VARIANT_BOOL Listen);


void __RPC_STUB IInkCollector_SetGestureStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCollector_GetGestureStatus_Proxy( 
    IInkCollector * This,
    /* [in] */ InkApplicationGesture Gesture,
    /* [retval][out] */ VARIANT_BOOL *Listening);


void __RPC_STUB IInkCollector_GetGestureStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCollector_GetWindowInputRectangle_Proxy( 
    IInkCollector * This,
    /* [out][in] */ IInkRectangle **WindowInputRectangle);


void __RPC_STUB IInkCollector_GetWindowInputRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCollector_SetWindowInputRectangle_Proxy( 
    IInkCollector * This,
    /* [in] */ IInkRectangle *WindowInputRectangle);


void __RPC_STUB IInkCollector_SetWindowInputRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCollector_SetAllTabletsMode_Proxy( 
    IInkCollector * This,
    /* [defaultvalue][in] */ VARIANT_BOOL UseMouseForInput);


void __RPC_STUB IInkCollector_SetAllTabletsMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCollector_SetSingleTabletIntegratedMode_Proxy( 
    IInkCollector * This,
    /* [in] */ IInkTablet *Tablet);


void __RPC_STUB IInkCollector_SetSingleTabletIntegratedMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCollector_GetEventInterest_Proxy( 
    IInkCollector * This,
    /* [in] */ InkCollectorEventInterest EventId,
    /* [retval][out] */ VARIANT_BOOL *Listen);


void __RPC_STUB IInkCollector_GetEventInterest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkCollector_SetEventInterest_Proxy( 
    IInkCollector * This,
    /* [in] */ InkCollectorEventInterest EventId,
    /* [in] */ VARIANT_BOOL Listen);


void __RPC_STUB IInkCollector_SetEventInterest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkCollector_INTERFACE_DEFINED__ */


#ifndef ___IInkCollectorEvents_DISPINTERFACE_DEFINED__
#define ___IInkCollectorEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IInkCollectorEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IInkCollectorEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("11A583F2-712D-4fea-ABCF-AB4AF38EA06B")
    _IInkCollectorEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IInkCollectorEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IInkCollectorEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IInkCollectorEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IInkCollectorEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IInkCollectorEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IInkCollectorEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IInkCollectorEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IInkCollectorEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IInkCollectorEventsVtbl;

    interface _IInkCollectorEvents
    {
        CONST_VTBL struct _IInkCollectorEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IInkCollectorEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IInkCollectorEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IInkCollectorEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IInkCollectorEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IInkCollectorEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IInkCollectorEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IInkCollectorEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IInkCollectorEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IInkOverlay_INTERFACE_DEFINED__
#define __IInkOverlay_INTERFACE_DEFINED__

/* interface IInkOverlay */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkOverlay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b82a463b-c1c5-45a3-997c-deab5651b67a")
    IInkOverlay : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ long *CurrentWindow) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hWnd( 
            /* [in] */ long NewWindow) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultDrawingAttributes( 
            /* [retval][out] */ IInkDrawingAttributes **CurrentAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_DefaultDrawingAttributes( 
            /* [in] */ IInkDrawingAttributes *NewAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Renderer( 
            /* [retval][out] */ IInkRenderer **CurrentInkRenderer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Renderer( 
            /* [in] */ IInkRenderer *NewInkRenderer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ink( 
            /* [retval][out] */ IInkDisp **Ink) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Ink( 
            /* [in] */ IInkDisp *NewInk) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoRedraw( 
            /* [retval][out] */ VARIANT_BOOL *AutoRedraw) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoRedraw( 
            /* [in] */ VARIANT_BOOL AutoRedraw) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CollectingInk( 
            /* [retval][out] */ VARIANT_BOOL *Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CollectionMode( 
            /* [retval][out] */ InkCollectionMode *Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CollectionMode( 
            /* [in] */ InkCollectionMode Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DynamicRendering( 
            /* [retval][out] */ VARIANT_BOOL *Enabled) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DynamicRendering( 
            /* [in] */ VARIANT_BOOL Enabled) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DesiredPacketDescription( 
            /* [retval][out] */ VARIANT *PacketGuids) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DesiredPacketDescription( 
            /* [in] */ VARIANT PacketGuids) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouseIcon( 
            /* [retval][out] */ IPictureDisp **MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MouseIcon( 
            /* [in] */ IPictureDisp *MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_MouseIcon( 
            /* [in] */ IPictureDisp *MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MousePointer( 
            /* [retval][out] */ InkMousePointer *MousePointer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MousePointer( 
            /* [in] */ InkMousePointer MousePointer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EditingMode( 
            /* [retval][out] */ InkOverlayEditingMode *EditingMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EditingMode( 
            /* [in] */ InkOverlayEditingMode EditingMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Selection( 
            /* [retval][out] */ IInkStrokes **Selection) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Selection( 
            /* [in] */ IInkStrokes *Selection) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EraserMode( 
            /* [retval][out] */ InkOverlayEraserMode *EraserMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EraserMode( 
            /* [in] */ InkOverlayEraserMode EraserMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EraserWidth( 
            /* [retval][out] */ long *EraserWidth) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EraserWidth( 
            /* [in] */ long newEraserWidth) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttachMode( 
            /* [retval][out] */ InkOverlayAttachMode *AttachMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AttachMode( 
            /* [in] */ InkOverlayAttachMode AttachMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cursors( 
            /* [retval][out] */ IInkCursors **Cursors) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarginX( 
            /* [retval][out] */ long *MarginX) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarginX( 
            /* [in] */ long MarginX) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarginY( 
            /* [retval][out] */ long *MarginY) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarginY( 
            /* [in] */ long MarginY) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Tablet( 
            /* [retval][out] */ IInkTablet **SingleTablet) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupportHighContrastInk( 
            /* [retval][out] */ VARIANT_BOOL *Support) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SupportHighContrastInk( 
            /* [in] */ VARIANT_BOOL Support) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupportHighContrastSelectionUI( 
            /* [retval][out] */ VARIANT_BOOL *Support) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SupportHighContrastSelectionUI( 
            /* [in] */ VARIANT_BOOL Support) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE HitTestSelection( 
            /* [in] */ long x,
            /* [in] */ long y,
            /* [retval][out] */ SelectionHitResult *SelArea) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ IInkRectangle *Rect) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGestureStatus( 
            /* [in] */ InkApplicationGesture Gesture,
            /* [in] */ VARIANT_BOOL Listen) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGestureStatus( 
            /* [in] */ InkApplicationGesture Gesture,
            /* [retval][out] */ VARIANT_BOOL *Listening) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowInputRectangle( 
            /* [out][in] */ IInkRectangle **WindowInputRectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWindowInputRectangle( 
            /* [in] */ IInkRectangle *WindowInputRectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAllTabletsMode( 
            /* [defaultvalue][in] */ VARIANT_BOOL UseMouseForInput = -1) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSingleTabletIntegratedMode( 
            /* [in] */ IInkTablet *Tablet) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEventInterest( 
            /* [in] */ InkCollectorEventInterest EventId,
            /* [retval][out] */ VARIANT_BOOL *Listen) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventInterest( 
            /* [in] */ InkCollectorEventInterest EventId,
            /* [in] */ VARIANT_BOOL Listen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkOverlayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkOverlay * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkOverlay * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkOverlay * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkOverlay * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkOverlay * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkOverlay * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkOverlay * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_hWnd )( 
            IInkOverlay * This,
            /* [retval][out] */ long *CurrentWindow);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_hWnd )( 
            IInkOverlay * This,
            /* [in] */ long NewWindow);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IInkOverlay * This,
            /* [retval][out] */ VARIANT_BOOL *Collecting);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IInkOverlay * This,
            /* [in] */ VARIANT_BOOL Collecting);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultDrawingAttributes )( 
            IInkOverlay * This,
            /* [retval][out] */ IInkDrawingAttributes **CurrentAttributes);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DefaultDrawingAttributes )( 
            IInkOverlay * This,
            /* [in] */ IInkDrawingAttributes *NewAttributes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Renderer )( 
            IInkOverlay * This,
            /* [retval][out] */ IInkRenderer **CurrentInkRenderer);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Renderer )( 
            IInkOverlay * This,
            /* [in] */ IInkRenderer *NewInkRenderer);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ink )( 
            IInkOverlay * This,
            /* [retval][out] */ IInkDisp **Ink);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Ink )( 
            IInkOverlay * This,
            /* [in] */ IInkDisp *NewInk);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoRedraw )( 
            IInkOverlay * This,
            /* [retval][out] */ VARIANT_BOOL *AutoRedraw);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoRedraw )( 
            IInkOverlay * This,
            /* [in] */ VARIANT_BOOL AutoRedraw);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CollectingInk )( 
            IInkOverlay * This,
            /* [retval][out] */ VARIANT_BOOL *Collecting);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CollectionMode )( 
            IInkOverlay * This,
            /* [retval][out] */ InkCollectionMode *Mode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CollectionMode )( 
            IInkOverlay * This,
            /* [in] */ InkCollectionMode Mode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DynamicRendering )( 
            IInkOverlay * This,
            /* [retval][out] */ VARIANT_BOOL *Enabled);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DynamicRendering )( 
            IInkOverlay * This,
            /* [in] */ VARIANT_BOOL Enabled);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DesiredPacketDescription )( 
            IInkOverlay * This,
            /* [retval][out] */ VARIANT *PacketGuids);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DesiredPacketDescription )( 
            IInkOverlay * This,
            /* [in] */ VARIANT PacketGuids);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MouseIcon )( 
            IInkOverlay * This,
            /* [retval][out] */ IPictureDisp **MouseIcon);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MouseIcon )( 
            IInkOverlay * This,
            /* [in] */ IPictureDisp *MouseIcon);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_MouseIcon )( 
            IInkOverlay * This,
            /* [in] */ IPictureDisp *MouseIcon);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MousePointer )( 
            IInkOverlay * This,
            /* [retval][out] */ InkMousePointer *MousePointer);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MousePointer )( 
            IInkOverlay * This,
            /* [in] */ InkMousePointer MousePointer);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EditingMode )( 
            IInkOverlay * This,
            /* [retval][out] */ InkOverlayEditingMode *EditingMode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EditingMode )( 
            IInkOverlay * This,
            /* [in] */ InkOverlayEditingMode EditingMode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Selection )( 
            IInkOverlay * This,
            /* [retval][out] */ IInkStrokes **Selection);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Selection )( 
            IInkOverlay * This,
            /* [in] */ IInkStrokes *Selection);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EraserMode )( 
            IInkOverlay * This,
            /* [retval][out] */ InkOverlayEraserMode *EraserMode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EraserMode )( 
            IInkOverlay * This,
            /* [in] */ InkOverlayEraserMode EraserMode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EraserWidth )( 
            IInkOverlay * This,
            /* [retval][out] */ long *EraserWidth);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EraserWidth )( 
            IInkOverlay * This,
            /* [in] */ long newEraserWidth);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AttachMode )( 
            IInkOverlay * This,
            /* [retval][out] */ InkOverlayAttachMode *AttachMode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AttachMode )( 
            IInkOverlay * This,
            /* [in] */ InkOverlayAttachMode AttachMode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cursors )( 
            IInkOverlay * This,
            /* [retval][out] */ IInkCursors **Cursors);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarginX )( 
            IInkOverlay * This,
            /* [retval][out] */ long *MarginX);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarginX )( 
            IInkOverlay * This,
            /* [in] */ long MarginX);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarginY )( 
            IInkOverlay * This,
            /* [retval][out] */ long *MarginY);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarginY )( 
            IInkOverlay * This,
            /* [in] */ long MarginY);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tablet )( 
            IInkOverlay * This,
            /* [retval][out] */ IInkTablet **SingleTablet);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SupportHighContrastInk )( 
            IInkOverlay * This,
            /* [retval][out] */ VARIANT_BOOL *Support);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SupportHighContrastInk )( 
            IInkOverlay * This,
            /* [in] */ VARIANT_BOOL Support);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SupportHighContrastSelectionUI )( 
            IInkOverlay * This,
            /* [retval][out] */ VARIANT_BOOL *Support);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SupportHighContrastSelectionUI )( 
            IInkOverlay * This,
            /* [in] */ VARIANT_BOOL Support);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HitTestSelection )( 
            IInkOverlay * This,
            /* [in] */ long x,
            /* [in] */ long y,
            /* [retval][out] */ SelectionHitResult *SelArea);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Draw )( 
            IInkOverlay * This,
            /* [in] */ IInkRectangle *Rect);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetGestureStatus )( 
            IInkOverlay * This,
            /* [in] */ InkApplicationGesture Gesture,
            /* [in] */ VARIANT_BOOL Listen);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetGestureStatus )( 
            IInkOverlay * This,
            /* [in] */ InkApplicationGesture Gesture,
            /* [retval][out] */ VARIANT_BOOL *Listening);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindowInputRectangle )( 
            IInkOverlay * This,
            /* [out][in] */ IInkRectangle **WindowInputRectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetWindowInputRectangle )( 
            IInkOverlay * This,
            /* [in] */ IInkRectangle *WindowInputRectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAllTabletsMode )( 
            IInkOverlay * This,
            /* [defaultvalue][in] */ VARIANT_BOOL UseMouseForInput);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSingleTabletIntegratedMode )( 
            IInkOverlay * This,
            /* [in] */ IInkTablet *Tablet);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEventInterest )( 
            IInkOverlay * This,
            /* [in] */ InkCollectorEventInterest EventId,
            /* [retval][out] */ VARIANT_BOOL *Listen);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventInterest )( 
            IInkOverlay * This,
            /* [in] */ InkCollectorEventInterest EventId,
            /* [in] */ VARIANT_BOOL Listen);
        
        END_INTERFACE
    } IInkOverlayVtbl;

    interface IInkOverlay
    {
        CONST_VTBL struct IInkOverlayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkOverlay_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkOverlay_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkOverlay_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkOverlay_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkOverlay_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkOverlay_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkOverlay_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkOverlay_get_hWnd(This,CurrentWindow)	\
    (This)->lpVtbl -> get_hWnd(This,CurrentWindow)

#define IInkOverlay_put_hWnd(This,NewWindow)	\
    (This)->lpVtbl -> put_hWnd(This,NewWindow)

#define IInkOverlay_get_Enabled(This,Collecting)	\
    (This)->lpVtbl -> get_Enabled(This,Collecting)

#define IInkOverlay_put_Enabled(This,Collecting)	\
    (This)->lpVtbl -> put_Enabled(This,Collecting)

#define IInkOverlay_get_DefaultDrawingAttributes(This,CurrentAttributes)	\
    (This)->lpVtbl -> get_DefaultDrawingAttributes(This,CurrentAttributes)

#define IInkOverlay_putref_DefaultDrawingAttributes(This,NewAttributes)	\
    (This)->lpVtbl -> putref_DefaultDrawingAttributes(This,NewAttributes)

#define IInkOverlay_get_Renderer(This,CurrentInkRenderer)	\
    (This)->lpVtbl -> get_Renderer(This,CurrentInkRenderer)

#define IInkOverlay_putref_Renderer(This,NewInkRenderer)	\
    (This)->lpVtbl -> putref_Renderer(This,NewInkRenderer)

#define IInkOverlay_get_Ink(This,Ink)	\
    (This)->lpVtbl -> get_Ink(This,Ink)

#define IInkOverlay_putref_Ink(This,NewInk)	\
    (This)->lpVtbl -> putref_Ink(This,NewInk)

#define IInkOverlay_get_AutoRedraw(This,AutoRedraw)	\
    (This)->lpVtbl -> get_AutoRedraw(This,AutoRedraw)

#define IInkOverlay_put_AutoRedraw(This,AutoRedraw)	\
    (This)->lpVtbl -> put_AutoRedraw(This,AutoRedraw)

#define IInkOverlay_get_CollectingInk(This,Collecting)	\
    (This)->lpVtbl -> get_CollectingInk(This,Collecting)

#define IInkOverlay_get_CollectionMode(This,Mode)	\
    (This)->lpVtbl -> get_CollectionMode(This,Mode)

#define IInkOverlay_put_CollectionMode(This,Mode)	\
    (This)->lpVtbl -> put_CollectionMode(This,Mode)

#define IInkOverlay_get_DynamicRendering(This,Enabled)	\
    (This)->lpVtbl -> get_DynamicRendering(This,Enabled)

#define IInkOverlay_put_DynamicRendering(This,Enabled)	\
    (This)->lpVtbl -> put_DynamicRendering(This,Enabled)

#define IInkOverlay_get_DesiredPacketDescription(This,PacketGuids)	\
    (This)->lpVtbl -> get_DesiredPacketDescription(This,PacketGuids)

#define IInkOverlay_put_DesiredPacketDescription(This,PacketGuids)	\
    (This)->lpVtbl -> put_DesiredPacketDescription(This,PacketGuids)

#define IInkOverlay_get_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> get_MouseIcon(This,MouseIcon)

#define IInkOverlay_put_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> put_MouseIcon(This,MouseIcon)

#define IInkOverlay_putref_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> putref_MouseIcon(This,MouseIcon)

#define IInkOverlay_get_MousePointer(This,MousePointer)	\
    (This)->lpVtbl -> get_MousePointer(This,MousePointer)

#define IInkOverlay_put_MousePointer(This,MousePointer)	\
    (This)->lpVtbl -> put_MousePointer(This,MousePointer)

#define IInkOverlay_get_EditingMode(This,EditingMode)	\
    (This)->lpVtbl -> get_EditingMode(This,EditingMode)

#define IInkOverlay_put_EditingMode(This,EditingMode)	\
    (This)->lpVtbl -> put_EditingMode(This,EditingMode)

#define IInkOverlay_get_Selection(This,Selection)	\
    (This)->lpVtbl -> get_Selection(This,Selection)

#define IInkOverlay_put_Selection(This,Selection)	\
    (This)->lpVtbl -> put_Selection(This,Selection)

#define IInkOverlay_get_EraserMode(This,EraserMode)	\
    (This)->lpVtbl -> get_EraserMode(This,EraserMode)

#define IInkOverlay_put_EraserMode(This,EraserMode)	\
    (This)->lpVtbl -> put_EraserMode(This,EraserMode)

#define IInkOverlay_get_EraserWidth(This,EraserWidth)	\
    (This)->lpVtbl -> get_EraserWidth(This,EraserWidth)

#define IInkOverlay_put_EraserWidth(This,newEraserWidth)	\
    (This)->lpVtbl -> put_EraserWidth(This,newEraserWidth)

#define IInkOverlay_get_AttachMode(This,AttachMode)	\
    (This)->lpVtbl -> get_AttachMode(This,AttachMode)

#define IInkOverlay_put_AttachMode(This,AttachMode)	\
    (This)->lpVtbl -> put_AttachMode(This,AttachMode)

#define IInkOverlay_get_Cursors(This,Cursors)	\
    (This)->lpVtbl -> get_Cursors(This,Cursors)

#define IInkOverlay_get_MarginX(This,MarginX)	\
    (This)->lpVtbl -> get_MarginX(This,MarginX)

#define IInkOverlay_put_MarginX(This,MarginX)	\
    (This)->lpVtbl -> put_MarginX(This,MarginX)

#define IInkOverlay_get_MarginY(This,MarginY)	\
    (This)->lpVtbl -> get_MarginY(This,MarginY)

#define IInkOverlay_put_MarginY(This,MarginY)	\
    (This)->lpVtbl -> put_MarginY(This,MarginY)

#define IInkOverlay_get_Tablet(This,SingleTablet)	\
    (This)->lpVtbl -> get_Tablet(This,SingleTablet)

#define IInkOverlay_get_SupportHighContrastInk(This,Support)	\
    (This)->lpVtbl -> get_SupportHighContrastInk(This,Support)

#define IInkOverlay_put_SupportHighContrastInk(This,Support)	\
    (This)->lpVtbl -> put_SupportHighContrastInk(This,Support)

#define IInkOverlay_get_SupportHighContrastSelectionUI(This,Support)	\
    (This)->lpVtbl -> get_SupportHighContrastSelectionUI(This,Support)

#define IInkOverlay_put_SupportHighContrastSelectionUI(This,Support)	\
    (This)->lpVtbl -> put_SupportHighContrastSelectionUI(This,Support)

#define IInkOverlay_HitTestSelection(This,x,y,SelArea)	\
    (This)->lpVtbl -> HitTestSelection(This,x,y,SelArea)

#define IInkOverlay_Draw(This,Rect)	\
    (This)->lpVtbl -> Draw(This,Rect)

#define IInkOverlay_SetGestureStatus(This,Gesture,Listen)	\
    (This)->lpVtbl -> SetGestureStatus(This,Gesture,Listen)

#define IInkOverlay_GetGestureStatus(This,Gesture,Listening)	\
    (This)->lpVtbl -> GetGestureStatus(This,Gesture,Listening)

#define IInkOverlay_GetWindowInputRectangle(This,WindowInputRectangle)	\
    (This)->lpVtbl -> GetWindowInputRectangle(This,WindowInputRectangle)

#define IInkOverlay_SetWindowInputRectangle(This,WindowInputRectangle)	\
    (This)->lpVtbl -> SetWindowInputRectangle(This,WindowInputRectangle)

#define IInkOverlay_SetAllTabletsMode(This,UseMouseForInput)	\
    (This)->lpVtbl -> SetAllTabletsMode(This,UseMouseForInput)

#define IInkOverlay_SetSingleTabletIntegratedMode(This,Tablet)	\
    (This)->lpVtbl -> SetSingleTabletIntegratedMode(This,Tablet)

#define IInkOverlay_GetEventInterest(This,EventId,Listen)	\
    (This)->lpVtbl -> GetEventInterest(This,EventId,Listen)

#define IInkOverlay_SetEventInterest(This,EventId,Listen)	\
    (This)->lpVtbl -> SetEventInterest(This,EventId,Listen)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_hWnd_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ long *CurrentWindow);


void __RPC_STUB IInkOverlay_get_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_hWnd_Proxy( 
    IInkOverlay * This,
    /* [in] */ long NewWindow);


void __RPC_STUB IInkOverlay_put_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_Enabled_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ VARIANT_BOOL *Collecting);


void __RPC_STUB IInkOverlay_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_Enabled_Proxy( 
    IInkOverlay * This,
    /* [in] */ VARIANT_BOOL Collecting);


void __RPC_STUB IInkOverlay_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_DefaultDrawingAttributes_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ IInkDrawingAttributes **CurrentAttributes);


void __RPC_STUB IInkOverlay_get_DefaultDrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkOverlay_putref_DefaultDrawingAttributes_Proxy( 
    IInkOverlay * This,
    /* [in] */ IInkDrawingAttributes *NewAttributes);


void __RPC_STUB IInkOverlay_putref_DefaultDrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_Renderer_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ IInkRenderer **CurrentInkRenderer);


void __RPC_STUB IInkOverlay_get_Renderer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkOverlay_putref_Renderer_Proxy( 
    IInkOverlay * This,
    /* [in] */ IInkRenderer *NewInkRenderer);


void __RPC_STUB IInkOverlay_putref_Renderer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_Ink_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ IInkDisp **Ink);


void __RPC_STUB IInkOverlay_get_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkOverlay_putref_Ink_Proxy( 
    IInkOverlay * This,
    /* [in] */ IInkDisp *NewInk);


void __RPC_STUB IInkOverlay_putref_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_AutoRedraw_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ VARIANT_BOOL *AutoRedraw);


void __RPC_STUB IInkOverlay_get_AutoRedraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_AutoRedraw_Proxy( 
    IInkOverlay * This,
    /* [in] */ VARIANT_BOOL AutoRedraw);


void __RPC_STUB IInkOverlay_put_AutoRedraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_CollectingInk_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ VARIANT_BOOL *Collecting);


void __RPC_STUB IInkOverlay_get_CollectingInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_CollectionMode_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ InkCollectionMode *Mode);


void __RPC_STUB IInkOverlay_get_CollectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_CollectionMode_Proxy( 
    IInkOverlay * This,
    /* [in] */ InkCollectionMode Mode);


void __RPC_STUB IInkOverlay_put_CollectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_DynamicRendering_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ VARIANT_BOOL *Enabled);


void __RPC_STUB IInkOverlay_get_DynamicRendering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_DynamicRendering_Proxy( 
    IInkOverlay * This,
    /* [in] */ VARIANT_BOOL Enabled);


void __RPC_STUB IInkOverlay_put_DynamicRendering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_DesiredPacketDescription_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ VARIANT *PacketGuids);


void __RPC_STUB IInkOverlay_get_DesiredPacketDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_DesiredPacketDescription_Proxy( 
    IInkOverlay * This,
    /* [in] */ VARIANT PacketGuids);


void __RPC_STUB IInkOverlay_put_DesiredPacketDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_MouseIcon_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ IPictureDisp **MouseIcon);


void __RPC_STUB IInkOverlay_get_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_MouseIcon_Proxy( 
    IInkOverlay * This,
    /* [in] */ IPictureDisp *MouseIcon);


void __RPC_STUB IInkOverlay_put_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkOverlay_putref_MouseIcon_Proxy( 
    IInkOverlay * This,
    /* [in] */ IPictureDisp *MouseIcon);


void __RPC_STUB IInkOverlay_putref_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_MousePointer_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ InkMousePointer *MousePointer);


void __RPC_STUB IInkOverlay_get_MousePointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_MousePointer_Proxy( 
    IInkOverlay * This,
    /* [in] */ InkMousePointer MousePointer);


void __RPC_STUB IInkOverlay_put_MousePointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_EditingMode_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ InkOverlayEditingMode *EditingMode);


void __RPC_STUB IInkOverlay_get_EditingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_EditingMode_Proxy( 
    IInkOverlay * This,
    /* [in] */ InkOverlayEditingMode EditingMode);


void __RPC_STUB IInkOverlay_put_EditingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_Selection_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ IInkStrokes **Selection);


void __RPC_STUB IInkOverlay_get_Selection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_Selection_Proxy( 
    IInkOverlay * This,
    /* [in] */ IInkStrokes *Selection);


void __RPC_STUB IInkOverlay_put_Selection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_EraserMode_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ InkOverlayEraserMode *EraserMode);


void __RPC_STUB IInkOverlay_get_EraserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_EraserMode_Proxy( 
    IInkOverlay * This,
    /* [in] */ InkOverlayEraserMode EraserMode);


void __RPC_STUB IInkOverlay_put_EraserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_EraserWidth_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ long *EraserWidth);


void __RPC_STUB IInkOverlay_get_EraserWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_EraserWidth_Proxy( 
    IInkOverlay * This,
    /* [in] */ long newEraserWidth);


void __RPC_STUB IInkOverlay_put_EraserWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_AttachMode_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ InkOverlayAttachMode *AttachMode);


void __RPC_STUB IInkOverlay_get_AttachMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_AttachMode_Proxy( 
    IInkOverlay * This,
    /* [in] */ InkOverlayAttachMode AttachMode);


void __RPC_STUB IInkOverlay_put_AttachMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_Cursors_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ IInkCursors **Cursors);


void __RPC_STUB IInkOverlay_get_Cursors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_MarginX_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ long *MarginX);


void __RPC_STUB IInkOverlay_get_MarginX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_MarginX_Proxy( 
    IInkOverlay * This,
    /* [in] */ long MarginX);


void __RPC_STUB IInkOverlay_put_MarginX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_MarginY_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ long *MarginY);


void __RPC_STUB IInkOverlay_get_MarginY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_MarginY_Proxy( 
    IInkOverlay * This,
    /* [in] */ long MarginY);


void __RPC_STUB IInkOverlay_put_MarginY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_Tablet_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ IInkTablet **SingleTablet);


void __RPC_STUB IInkOverlay_get_Tablet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_SupportHighContrastInk_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ VARIANT_BOOL *Support);


void __RPC_STUB IInkOverlay_get_SupportHighContrastInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_SupportHighContrastInk_Proxy( 
    IInkOverlay * This,
    /* [in] */ VARIANT_BOOL Support);


void __RPC_STUB IInkOverlay_put_SupportHighContrastInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkOverlay_get_SupportHighContrastSelectionUI_Proxy( 
    IInkOverlay * This,
    /* [retval][out] */ VARIANT_BOOL *Support);


void __RPC_STUB IInkOverlay_get_SupportHighContrastSelectionUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkOverlay_put_SupportHighContrastSelectionUI_Proxy( 
    IInkOverlay * This,
    /* [in] */ VARIANT_BOOL Support);


void __RPC_STUB IInkOverlay_put_SupportHighContrastSelectionUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_HitTestSelection_Proxy( 
    IInkOverlay * This,
    /* [in] */ long x,
    /* [in] */ long y,
    /* [retval][out] */ SelectionHitResult *SelArea);


void __RPC_STUB IInkOverlay_HitTestSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_Draw_Proxy( 
    IInkOverlay * This,
    /* [in] */ IInkRectangle *Rect);


void __RPC_STUB IInkOverlay_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_SetGestureStatus_Proxy( 
    IInkOverlay * This,
    /* [in] */ InkApplicationGesture Gesture,
    /* [in] */ VARIANT_BOOL Listen);


void __RPC_STUB IInkOverlay_SetGestureStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_GetGestureStatus_Proxy( 
    IInkOverlay * This,
    /* [in] */ InkApplicationGesture Gesture,
    /* [retval][out] */ VARIANT_BOOL *Listening);


void __RPC_STUB IInkOverlay_GetGestureStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_GetWindowInputRectangle_Proxy( 
    IInkOverlay * This,
    /* [out][in] */ IInkRectangle **WindowInputRectangle);


void __RPC_STUB IInkOverlay_GetWindowInputRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_SetWindowInputRectangle_Proxy( 
    IInkOverlay * This,
    /* [in] */ IInkRectangle *WindowInputRectangle);


void __RPC_STUB IInkOverlay_SetWindowInputRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_SetAllTabletsMode_Proxy( 
    IInkOverlay * This,
    /* [defaultvalue][in] */ VARIANT_BOOL UseMouseForInput);


void __RPC_STUB IInkOverlay_SetAllTabletsMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_SetSingleTabletIntegratedMode_Proxy( 
    IInkOverlay * This,
    /* [in] */ IInkTablet *Tablet);


void __RPC_STUB IInkOverlay_SetSingleTabletIntegratedMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_GetEventInterest_Proxy( 
    IInkOverlay * This,
    /* [in] */ InkCollectorEventInterest EventId,
    /* [retval][out] */ VARIANT_BOOL *Listen);


void __RPC_STUB IInkOverlay_GetEventInterest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkOverlay_SetEventInterest_Proxy( 
    IInkOverlay * This,
    /* [in] */ InkCollectorEventInterest EventId,
    /* [in] */ VARIANT_BOOL Listen);


void __RPC_STUB IInkOverlay_SetEventInterest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkOverlay_INTERFACE_DEFINED__ */


#ifndef ___IInkOverlayEvents_DISPINTERFACE_DEFINED__
#define ___IInkOverlayEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IInkOverlayEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IInkOverlayEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("31179b69-e563-489e-b16f-712f1e8a0651")
    _IInkOverlayEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IInkOverlayEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IInkOverlayEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IInkOverlayEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IInkOverlayEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IInkOverlayEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IInkOverlayEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IInkOverlayEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IInkOverlayEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IInkOverlayEventsVtbl;

    interface _IInkOverlayEvents
    {
        CONST_VTBL struct _IInkOverlayEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IInkOverlayEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IInkOverlayEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IInkOverlayEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IInkOverlayEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IInkOverlayEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IInkOverlayEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IInkOverlayEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IInkOverlayEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IInkPicture_INTERFACE_DEFINED__
#define __IInkPicture_INTERFACE_DEFINED__

/* interface IInkPicture */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkPicture;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e85662e0-379a-40d7-9b5c-757d233f9923")
    IInkPicture : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ long *CurrentWindow) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DefaultDrawingAttributes( 
            /* [retval][out] */ IInkDrawingAttributes **CurrentAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_DefaultDrawingAttributes( 
            /* [in] */ IInkDrawingAttributes *NewAttributes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Renderer( 
            /* [retval][out] */ IInkRenderer **CurrentInkRenderer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Renderer( 
            /* [in] */ IInkRenderer *NewInkRenderer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ink( 
            /* [retval][out] */ IInkDisp **Ink) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Ink( 
            /* [in] */ IInkDisp *NewInk) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoRedraw( 
            /* [retval][out] */ VARIANT_BOOL *AutoRedraw) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoRedraw( 
            /* [in] */ VARIANT_BOOL AutoRedraw) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CollectingInk( 
            /* [retval][out] */ VARIANT_BOOL *Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CollectionMode( 
            /* [retval][out] */ InkCollectionMode *Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CollectionMode( 
            /* [in] */ InkCollectionMode Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DynamicRendering( 
            /* [retval][out] */ VARIANT_BOOL *Enabled) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DynamicRendering( 
            /* [in] */ VARIANT_BOOL Enabled) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DesiredPacketDescription( 
            /* [retval][out] */ VARIANT *PacketGuids) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DesiredPacketDescription( 
            /* [in] */ VARIANT PacketGuids) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MouseIcon( 
            /* [retval][out] */ IPictureDisp **MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MouseIcon( 
            /* [in] */ IPictureDisp *MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_MouseIcon( 
            /* [in] */ IPictureDisp *MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MousePointer( 
            /* [retval][out] */ InkMousePointer *MousePointer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MousePointer( 
            /* [in] */ InkMousePointer MousePointer) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EditingMode( 
            /* [retval][out] */ InkOverlayEditingMode *EditingMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EditingMode( 
            /* [in] */ InkOverlayEditingMode EditingMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Selection( 
            /* [retval][out] */ IInkStrokes **Selection) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Selection( 
            /* [in] */ IInkStrokes *Selection) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EraserMode( 
            /* [retval][out] */ InkOverlayEraserMode *EraserMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EraserMode( 
            /* [in] */ InkOverlayEraserMode EraserMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EraserWidth( 
            /* [retval][out] */ long *EraserWidth) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EraserWidth( 
            /* [in] */ long newEraserWidth) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Picture( 
            /* [in] */ IPictureDisp *pPicture) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Picture( 
            /* [in] */ IPictureDisp *pPicture) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Picture( 
            /* [retval][out] */ IPictureDisp **ppPicture) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SizeMode( 
            /* [in] */ InkPictureSizeMode smNewSizeMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SizeMode( 
            /* [retval][out] */ InkPictureSizeMode *smSizeMode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR newColor) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pColor) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cursors( 
            /* [retval][out] */ IInkCursors **Cursors) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarginX( 
            /* [retval][out] */ long *MarginX) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarginX( 
            /* [in] */ long MarginX) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarginY( 
            /* [retval][out] */ long *MarginY) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarginY( 
            /* [in] */ long MarginY) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Tablet( 
            /* [retval][out] */ IInkTablet **SingleTablet) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupportHighContrastInk( 
            /* [retval][out] */ VARIANT_BOOL *Support) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SupportHighContrastInk( 
            /* [in] */ VARIANT_BOOL Support) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupportHighContrastSelectionUI( 
            /* [retval][out] */ VARIANT_BOOL *Support) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SupportHighContrastSelectionUI( 
            /* [in] */ VARIANT_BOOL Support) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE HitTestSelection( 
            /* [in] */ long x,
            /* [in] */ long y,
            /* [retval][out] */ SelectionHitResult *SelArea) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGestureStatus( 
            /* [in] */ InkApplicationGesture Gesture,
            /* [in] */ VARIANT_BOOL Listen) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGestureStatus( 
            /* [in] */ InkApplicationGesture Gesture,
            /* [retval][out] */ VARIANT_BOOL *Listening) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowInputRectangle( 
            /* [out][in] */ IInkRectangle **WindowInputRectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWindowInputRectangle( 
            /* [in] */ IInkRectangle *WindowInputRectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAllTabletsMode( 
            /* [defaultvalue][in] */ VARIANT_BOOL UseMouseForInput = -1) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSingleTabletIntegratedMode( 
            /* [in] */ IInkTablet *Tablet) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEventInterest( 
            /* [in] */ InkCollectorEventInterest EventId,
            /* [retval][out] */ VARIANT_BOOL *Listen) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEventInterest( 
            /* [in] */ InkCollectorEventInterest EventId,
            /* [in] */ VARIANT_BOOL Listen) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InkEnabled( 
            /* [retval][out] */ VARIANT_BOOL *Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InkEnabled( 
            /* [in] */ VARIANT_BOOL Collecting) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pbool) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL vbool) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkPictureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkPicture * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkPicture * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkPicture * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkPicture * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkPicture * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkPicture * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkPicture * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_hWnd )( 
            IInkPicture * This,
            /* [retval][out] */ long *CurrentWindow);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultDrawingAttributes )( 
            IInkPicture * This,
            /* [retval][out] */ IInkDrawingAttributes **CurrentAttributes);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DefaultDrawingAttributes )( 
            IInkPicture * This,
            /* [in] */ IInkDrawingAttributes *NewAttributes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Renderer )( 
            IInkPicture * This,
            /* [retval][out] */ IInkRenderer **CurrentInkRenderer);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Renderer )( 
            IInkPicture * This,
            /* [in] */ IInkRenderer *NewInkRenderer);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ink )( 
            IInkPicture * This,
            /* [retval][out] */ IInkDisp **Ink);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Ink )( 
            IInkPicture * This,
            /* [in] */ IInkDisp *NewInk);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AutoRedraw )( 
            IInkPicture * This,
            /* [retval][out] */ VARIANT_BOOL *AutoRedraw);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AutoRedraw )( 
            IInkPicture * This,
            /* [in] */ VARIANT_BOOL AutoRedraw);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CollectingInk )( 
            IInkPicture * This,
            /* [retval][out] */ VARIANT_BOOL *Collecting);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CollectionMode )( 
            IInkPicture * This,
            /* [retval][out] */ InkCollectionMode *Mode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CollectionMode )( 
            IInkPicture * This,
            /* [in] */ InkCollectionMode Mode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DynamicRendering )( 
            IInkPicture * This,
            /* [retval][out] */ VARIANT_BOOL *Enabled);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DynamicRendering )( 
            IInkPicture * This,
            /* [in] */ VARIANT_BOOL Enabled);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DesiredPacketDescription )( 
            IInkPicture * This,
            /* [retval][out] */ VARIANT *PacketGuids);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DesiredPacketDescription )( 
            IInkPicture * This,
            /* [in] */ VARIANT PacketGuids);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MouseIcon )( 
            IInkPicture * This,
            /* [retval][out] */ IPictureDisp **MouseIcon);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MouseIcon )( 
            IInkPicture * This,
            /* [in] */ IPictureDisp *MouseIcon);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_MouseIcon )( 
            IInkPicture * This,
            /* [in] */ IPictureDisp *MouseIcon);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MousePointer )( 
            IInkPicture * This,
            /* [retval][out] */ InkMousePointer *MousePointer);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MousePointer )( 
            IInkPicture * This,
            /* [in] */ InkMousePointer MousePointer);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EditingMode )( 
            IInkPicture * This,
            /* [retval][out] */ InkOverlayEditingMode *EditingMode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EditingMode )( 
            IInkPicture * This,
            /* [in] */ InkOverlayEditingMode EditingMode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Selection )( 
            IInkPicture * This,
            /* [retval][out] */ IInkStrokes **Selection);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Selection )( 
            IInkPicture * This,
            /* [in] */ IInkStrokes *Selection);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EraserMode )( 
            IInkPicture * This,
            /* [retval][out] */ InkOverlayEraserMode *EraserMode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EraserMode )( 
            IInkPicture * This,
            /* [in] */ InkOverlayEraserMode EraserMode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EraserWidth )( 
            IInkPicture * This,
            /* [retval][out] */ long *EraserWidth);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EraserWidth )( 
            IInkPicture * This,
            /* [in] */ long newEraserWidth);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Picture )( 
            IInkPicture * This,
            /* [in] */ IPictureDisp *pPicture);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Picture )( 
            IInkPicture * This,
            /* [in] */ IPictureDisp *pPicture);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Picture )( 
            IInkPicture * This,
            /* [retval][out] */ IPictureDisp **ppPicture);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SizeMode )( 
            IInkPicture * This,
            /* [in] */ InkPictureSizeMode smNewSizeMode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SizeMode )( 
            IInkPicture * This,
            /* [retval][out] */ InkPictureSizeMode *smSizeMode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IInkPicture * This,
            /* [in] */ OLE_COLOR newColor);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IInkPicture * This,
            /* [retval][out] */ OLE_COLOR *pColor);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Cursors )( 
            IInkPicture * This,
            /* [retval][out] */ IInkCursors **Cursors);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarginX )( 
            IInkPicture * This,
            /* [retval][out] */ long *MarginX);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarginX )( 
            IInkPicture * This,
            /* [in] */ long MarginX);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MarginY )( 
            IInkPicture * This,
            /* [retval][out] */ long *MarginY);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MarginY )( 
            IInkPicture * This,
            /* [in] */ long MarginY);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tablet )( 
            IInkPicture * This,
            /* [retval][out] */ IInkTablet **SingleTablet);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SupportHighContrastInk )( 
            IInkPicture * This,
            /* [retval][out] */ VARIANT_BOOL *Support);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SupportHighContrastInk )( 
            IInkPicture * This,
            /* [in] */ VARIANT_BOOL Support);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SupportHighContrastSelectionUI )( 
            IInkPicture * This,
            /* [retval][out] */ VARIANT_BOOL *Support);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SupportHighContrastSelectionUI )( 
            IInkPicture * This,
            /* [in] */ VARIANT_BOOL Support);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HitTestSelection )( 
            IInkPicture * This,
            /* [in] */ long x,
            /* [in] */ long y,
            /* [retval][out] */ SelectionHitResult *SelArea);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetGestureStatus )( 
            IInkPicture * This,
            /* [in] */ InkApplicationGesture Gesture,
            /* [in] */ VARIANT_BOOL Listen);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetGestureStatus )( 
            IInkPicture * This,
            /* [in] */ InkApplicationGesture Gesture,
            /* [retval][out] */ VARIANT_BOOL *Listening);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindowInputRectangle )( 
            IInkPicture * This,
            /* [out][in] */ IInkRectangle **WindowInputRectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetWindowInputRectangle )( 
            IInkPicture * This,
            /* [in] */ IInkRectangle *WindowInputRectangle);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAllTabletsMode )( 
            IInkPicture * This,
            /* [defaultvalue][in] */ VARIANT_BOOL UseMouseForInput);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSingleTabletIntegratedMode )( 
            IInkPicture * This,
            /* [in] */ IInkTablet *Tablet);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEventInterest )( 
            IInkPicture * This,
            /* [in] */ InkCollectorEventInterest EventId,
            /* [retval][out] */ VARIANT_BOOL *Listen);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEventInterest )( 
            IInkPicture * This,
            /* [in] */ InkCollectorEventInterest EventId,
            /* [in] */ VARIANT_BOOL Listen);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InkEnabled )( 
            IInkPicture * This,
            /* [retval][out] */ VARIANT_BOOL *Collecting);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InkEnabled )( 
            IInkPicture * This,
            /* [in] */ VARIANT_BOOL Collecting);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IInkPicture * This,
            /* [retval][out] */ VARIANT_BOOL *pbool);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IInkPicture * This,
            /* [in] */ VARIANT_BOOL vbool);
        
        END_INTERFACE
    } IInkPictureVtbl;

    interface IInkPicture
    {
        CONST_VTBL struct IInkPictureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkPicture_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkPicture_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkPicture_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkPicture_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkPicture_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkPicture_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkPicture_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkPicture_get_hWnd(This,CurrentWindow)	\
    (This)->lpVtbl -> get_hWnd(This,CurrentWindow)

#define IInkPicture_get_DefaultDrawingAttributes(This,CurrentAttributes)	\
    (This)->lpVtbl -> get_DefaultDrawingAttributes(This,CurrentAttributes)

#define IInkPicture_putref_DefaultDrawingAttributes(This,NewAttributes)	\
    (This)->lpVtbl -> putref_DefaultDrawingAttributes(This,NewAttributes)

#define IInkPicture_get_Renderer(This,CurrentInkRenderer)	\
    (This)->lpVtbl -> get_Renderer(This,CurrentInkRenderer)

#define IInkPicture_putref_Renderer(This,NewInkRenderer)	\
    (This)->lpVtbl -> putref_Renderer(This,NewInkRenderer)

#define IInkPicture_get_Ink(This,Ink)	\
    (This)->lpVtbl -> get_Ink(This,Ink)

#define IInkPicture_putref_Ink(This,NewInk)	\
    (This)->lpVtbl -> putref_Ink(This,NewInk)

#define IInkPicture_get_AutoRedraw(This,AutoRedraw)	\
    (This)->lpVtbl -> get_AutoRedraw(This,AutoRedraw)

#define IInkPicture_put_AutoRedraw(This,AutoRedraw)	\
    (This)->lpVtbl -> put_AutoRedraw(This,AutoRedraw)

#define IInkPicture_get_CollectingInk(This,Collecting)	\
    (This)->lpVtbl -> get_CollectingInk(This,Collecting)

#define IInkPicture_get_CollectionMode(This,Mode)	\
    (This)->lpVtbl -> get_CollectionMode(This,Mode)

#define IInkPicture_put_CollectionMode(This,Mode)	\
    (This)->lpVtbl -> put_CollectionMode(This,Mode)

#define IInkPicture_get_DynamicRendering(This,Enabled)	\
    (This)->lpVtbl -> get_DynamicRendering(This,Enabled)

#define IInkPicture_put_DynamicRendering(This,Enabled)	\
    (This)->lpVtbl -> put_DynamicRendering(This,Enabled)

#define IInkPicture_get_DesiredPacketDescription(This,PacketGuids)	\
    (This)->lpVtbl -> get_DesiredPacketDescription(This,PacketGuids)

#define IInkPicture_put_DesiredPacketDescription(This,PacketGuids)	\
    (This)->lpVtbl -> put_DesiredPacketDescription(This,PacketGuids)

#define IInkPicture_get_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> get_MouseIcon(This,MouseIcon)

#define IInkPicture_put_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> put_MouseIcon(This,MouseIcon)

#define IInkPicture_putref_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> putref_MouseIcon(This,MouseIcon)

#define IInkPicture_get_MousePointer(This,MousePointer)	\
    (This)->lpVtbl -> get_MousePointer(This,MousePointer)

#define IInkPicture_put_MousePointer(This,MousePointer)	\
    (This)->lpVtbl -> put_MousePointer(This,MousePointer)

#define IInkPicture_get_EditingMode(This,EditingMode)	\
    (This)->lpVtbl -> get_EditingMode(This,EditingMode)

#define IInkPicture_put_EditingMode(This,EditingMode)	\
    (This)->lpVtbl -> put_EditingMode(This,EditingMode)

#define IInkPicture_get_Selection(This,Selection)	\
    (This)->lpVtbl -> get_Selection(This,Selection)

#define IInkPicture_put_Selection(This,Selection)	\
    (This)->lpVtbl -> put_Selection(This,Selection)

#define IInkPicture_get_EraserMode(This,EraserMode)	\
    (This)->lpVtbl -> get_EraserMode(This,EraserMode)

#define IInkPicture_put_EraserMode(This,EraserMode)	\
    (This)->lpVtbl -> put_EraserMode(This,EraserMode)

#define IInkPicture_get_EraserWidth(This,EraserWidth)	\
    (This)->lpVtbl -> get_EraserWidth(This,EraserWidth)

#define IInkPicture_put_EraserWidth(This,newEraserWidth)	\
    (This)->lpVtbl -> put_EraserWidth(This,newEraserWidth)

#define IInkPicture_putref_Picture(This,pPicture)	\
    (This)->lpVtbl -> putref_Picture(This,pPicture)

#define IInkPicture_put_Picture(This,pPicture)	\
    (This)->lpVtbl -> put_Picture(This,pPicture)

#define IInkPicture_get_Picture(This,ppPicture)	\
    (This)->lpVtbl -> get_Picture(This,ppPicture)

#define IInkPicture_put_SizeMode(This,smNewSizeMode)	\
    (This)->lpVtbl -> put_SizeMode(This,smNewSizeMode)

#define IInkPicture_get_SizeMode(This,smSizeMode)	\
    (This)->lpVtbl -> get_SizeMode(This,smSizeMode)

#define IInkPicture_put_BackColor(This,newColor)	\
    (This)->lpVtbl -> put_BackColor(This,newColor)

#define IInkPicture_get_BackColor(This,pColor)	\
    (This)->lpVtbl -> get_BackColor(This,pColor)

#define IInkPicture_get_Cursors(This,Cursors)	\
    (This)->lpVtbl -> get_Cursors(This,Cursors)

#define IInkPicture_get_MarginX(This,MarginX)	\
    (This)->lpVtbl -> get_MarginX(This,MarginX)

#define IInkPicture_put_MarginX(This,MarginX)	\
    (This)->lpVtbl -> put_MarginX(This,MarginX)

#define IInkPicture_get_MarginY(This,MarginY)	\
    (This)->lpVtbl -> get_MarginY(This,MarginY)

#define IInkPicture_put_MarginY(This,MarginY)	\
    (This)->lpVtbl -> put_MarginY(This,MarginY)

#define IInkPicture_get_Tablet(This,SingleTablet)	\
    (This)->lpVtbl -> get_Tablet(This,SingleTablet)

#define IInkPicture_get_SupportHighContrastInk(This,Support)	\
    (This)->lpVtbl -> get_SupportHighContrastInk(This,Support)

#define IInkPicture_put_SupportHighContrastInk(This,Support)	\
    (This)->lpVtbl -> put_SupportHighContrastInk(This,Support)

#define IInkPicture_get_SupportHighContrastSelectionUI(This,Support)	\
    (This)->lpVtbl -> get_SupportHighContrastSelectionUI(This,Support)

#define IInkPicture_put_SupportHighContrastSelectionUI(This,Support)	\
    (This)->lpVtbl -> put_SupportHighContrastSelectionUI(This,Support)

#define IInkPicture_HitTestSelection(This,x,y,SelArea)	\
    (This)->lpVtbl -> HitTestSelection(This,x,y,SelArea)

#define IInkPicture_SetGestureStatus(This,Gesture,Listen)	\
    (This)->lpVtbl -> SetGestureStatus(This,Gesture,Listen)

#define IInkPicture_GetGestureStatus(This,Gesture,Listening)	\
    (This)->lpVtbl -> GetGestureStatus(This,Gesture,Listening)

#define IInkPicture_GetWindowInputRectangle(This,WindowInputRectangle)	\
    (This)->lpVtbl -> GetWindowInputRectangle(This,WindowInputRectangle)

#define IInkPicture_SetWindowInputRectangle(This,WindowInputRectangle)	\
    (This)->lpVtbl -> SetWindowInputRectangle(This,WindowInputRectangle)

#define IInkPicture_SetAllTabletsMode(This,UseMouseForInput)	\
    (This)->lpVtbl -> SetAllTabletsMode(This,UseMouseForInput)

#define IInkPicture_SetSingleTabletIntegratedMode(This,Tablet)	\
    (This)->lpVtbl -> SetSingleTabletIntegratedMode(This,Tablet)

#define IInkPicture_GetEventInterest(This,EventId,Listen)	\
    (This)->lpVtbl -> GetEventInterest(This,EventId,Listen)

#define IInkPicture_SetEventInterest(This,EventId,Listen)	\
    (This)->lpVtbl -> SetEventInterest(This,EventId,Listen)

#define IInkPicture_get_InkEnabled(This,Collecting)	\
    (This)->lpVtbl -> get_InkEnabled(This,Collecting)

#define IInkPicture_put_InkEnabled(This,Collecting)	\
    (This)->lpVtbl -> put_InkEnabled(This,Collecting)

#define IInkPicture_get_Enabled(This,pbool)	\
    (This)->lpVtbl -> get_Enabled(This,pbool)

#define IInkPicture_put_Enabled(This,vbool)	\
    (This)->lpVtbl -> put_Enabled(This,vbool)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_hWnd_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ long *CurrentWindow);


void __RPC_STUB IInkPicture_get_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_DefaultDrawingAttributes_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ IInkDrawingAttributes **CurrentAttributes);


void __RPC_STUB IInkPicture_get_DefaultDrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkPicture_putref_DefaultDrawingAttributes_Proxy( 
    IInkPicture * This,
    /* [in] */ IInkDrawingAttributes *NewAttributes);


void __RPC_STUB IInkPicture_putref_DefaultDrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_Renderer_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ IInkRenderer **CurrentInkRenderer);


void __RPC_STUB IInkPicture_get_Renderer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkPicture_putref_Renderer_Proxy( 
    IInkPicture * This,
    /* [in] */ IInkRenderer *NewInkRenderer);


void __RPC_STUB IInkPicture_putref_Renderer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_Ink_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ IInkDisp **Ink);


void __RPC_STUB IInkPicture_get_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkPicture_putref_Ink_Proxy( 
    IInkPicture * This,
    /* [in] */ IInkDisp *NewInk);


void __RPC_STUB IInkPicture_putref_Ink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_AutoRedraw_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ VARIANT_BOOL *AutoRedraw);


void __RPC_STUB IInkPicture_get_AutoRedraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_AutoRedraw_Proxy( 
    IInkPicture * This,
    /* [in] */ VARIANT_BOOL AutoRedraw);


void __RPC_STUB IInkPicture_put_AutoRedraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_CollectingInk_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ VARIANT_BOOL *Collecting);


void __RPC_STUB IInkPicture_get_CollectingInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_CollectionMode_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ InkCollectionMode *Mode);


void __RPC_STUB IInkPicture_get_CollectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_CollectionMode_Proxy( 
    IInkPicture * This,
    /* [in] */ InkCollectionMode Mode);


void __RPC_STUB IInkPicture_put_CollectionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_DynamicRendering_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ VARIANT_BOOL *Enabled);


void __RPC_STUB IInkPicture_get_DynamicRendering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_DynamicRendering_Proxy( 
    IInkPicture * This,
    /* [in] */ VARIANT_BOOL Enabled);


void __RPC_STUB IInkPicture_put_DynamicRendering_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_DesiredPacketDescription_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ VARIANT *PacketGuids);


void __RPC_STUB IInkPicture_get_DesiredPacketDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_DesiredPacketDescription_Proxy( 
    IInkPicture * This,
    /* [in] */ VARIANT PacketGuids);


void __RPC_STUB IInkPicture_put_DesiredPacketDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_MouseIcon_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ IPictureDisp **MouseIcon);


void __RPC_STUB IInkPicture_get_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_MouseIcon_Proxy( 
    IInkPicture * This,
    /* [in] */ IPictureDisp *MouseIcon);


void __RPC_STUB IInkPicture_put_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkPicture_putref_MouseIcon_Proxy( 
    IInkPicture * This,
    /* [in] */ IPictureDisp *MouseIcon);


void __RPC_STUB IInkPicture_putref_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_MousePointer_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ InkMousePointer *MousePointer);


void __RPC_STUB IInkPicture_get_MousePointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_MousePointer_Proxy( 
    IInkPicture * This,
    /* [in] */ InkMousePointer MousePointer);


void __RPC_STUB IInkPicture_put_MousePointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_EditingMode_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ InkOverlayEditingMode *EditingMode);


void __RPC_STUB IInkPicture_get_EditingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_EditingMode_Proxy( 
    IInkPicture * This,
    /* [in] */ InkOverlayEditingMode EditingMode);


void __RPC_STUB IInkPicture_put_EditingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_Selection_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ IInkStrokes **Selection);


void __RPC_STUB IInkPicture_get_Selection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_Selection_Proxy( 
    IInkPicture * This,
    /* [in] */ IInkStrokes *Selection);


void __RPC_STUB IInkPicture_put_Selection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_EraserMode_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ InkOverlayEraserMode *EraserMode);


void __RPC_STUB IInkPicture_get_EraserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_EraserMode_Proxy( 
    IInkPicture * This,
    /* [in] */ InkOverlayEraserMode EraserMode);


void __RPC_STUB IInkPicture_put_EraserMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_EraserWidth_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ long *EraserWidth);


void __RPC_STUB IInkPicture_get_EraserWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_EraserWidth_Proxy( 
    IInkPicture * This,
    /* [in] */ long newEraserWidth);


void __RPC_STUB IInkPicture_put_EraserWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkPicture_putref_Picture_Proxy( 
    IInkPicture * This,
    /* [in] */ IPictureDisp *pPicture);


void __RPC_STUB IInkPicture_putref_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_Picture_Proxy( 
    IInkPicture * This,
    /* [in] */ IPictureDisp *pPicture);


void __RPC_STUB IInkPicture_put_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_Picture_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ IPictureDisp **ppPicture);


void __RPC_STUB IInkPicture_get_Picture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_SizeMode_Proxy( 
    IInkPicture * This,
    /* [in] */ InkPictureSizeMode smNewSizeMode);


void __RPC_STUB IInkPicture_put_SizeMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_SizeMode_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ InkPictureSizeMode *smSizeMode);


void __RPC_STUB IInkPicture_get_SizeMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_BackColor_Proxy( 
    IInkPicture * This,
    /* [in] */ OLE_COLOR newColor);


void __RPC_STUB IInkPicture_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_BackColor_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ OLE_COLOR *pColor);


void __RPC_STUB IInkPicture_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_Cursors_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ IInkCursors **Cursors);


void __RPC_STUB IInkPicture_get_Cursors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_MarginX_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ long *MarginX);


void __RPC_STUB IInkPicture_get_MarginX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_MarginX_Proxy( 
    IInkPicture * This,
    /* [in] */ long MarginX);


void __RPC_STUB IInkPicture_put_MarginX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_MarginY_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ long *MarginY);


void __RPC_STUB IInkPicture_get_MarginY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_MarginY_Proxy( 
    IInkPicture * This,
    /* [in] */ long MarginY);


void __RPC_STUB IInkPicture_put_MarginY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_Tablet_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ IInkTablet **SingleTablet);


void __RPC_STUB IInkPicture_get_Tablet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_SupportHighContrastInk_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ VARIANT_BOOL *Support);


void __RPC_STUB IInkPicture_get_SupportHighContrastInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_SupportHighContrastInk_Proxy( 
    IInkPicture * This,
    /* [in] */ VARIANT_BOOL Support);


void __RPC_STUB IInkPicture_put_SupportHighContrastInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_SupportHighContrastSelectionUI_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ VARIANT_BOOL *Support);


void __RPC_STUB IInkPicture_get_SupportHighContrastSelectionUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_SupportHighContrastSelectionUI_Proxy( 
    IInkPicture * This,
    /* [in] */ VARIANT_BOOL Support);


void __RPC_STUB IInkPicture_put_SupportHighContrastSelectionUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkPicture_HitTestSelection_Proxy( 
    IInkPicture * This,
    /* [in] */ long x,
    /* [in] */ long y,
    /* [retval][out] */ SelectionHitResult *SelArea);


void __RPC_STUB IInkPicture_HitTestSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkPicture_SetGestureStatus_Proxy( 
    IInkPicture * This,
    /* [in] */ InkApplicationGesture Gesture,
    /* [in] */ VARIANT_BOOL Listen);


void __RPC_STUB IInkPicture_SetGestureStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkPicture_GetGestureStatus_Proxy( 
    IInkPicture * This,
    /* [in] */ InkApplicationGesture Gesture,
    /* [retval][out] */ VARIANT_BOOL *Listening);


void __RPC_STUB IInkPicture_GetGestureStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkPicture_GetWindowInputRectangle_Proxy( 
    IInkPicture * This,
    /* [out][in] */ IInkRectangle **WindowInputRectangle);


void __RPC_STUB IInkPicture_GetWindowInputRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkPicture_SetWindowInputRectangle_Proxy( 
    IInkPicture * This,
    /* [in] */ IInkRectangle *WindowInputRectangle);


void __RPC_STUB IInkPicture_SetWindowInputRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkPicture_SetAllTabletsMode_Proxy( 
    IInkPicture * This,
    /* [defaultvalue][in] */ VARIANT_BOOL UseMouseForInput);


void __RPC_STUB IInkPicture_SetAllTabletsMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkPicture_SetSingleTabletIntegratedMode_Proxy( 
    IInkPicture * This,
    /* [in] */ IInkTablet *Tablet);


void __RPC_STUB IInkPicture_SetSingleTabletIntegratedMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkPicture_GetEventInterest_Proxy( 
    IInkPicture * This,
    /* [in] */ InkCollectorEventInterest EventId,
    /* [retval][out] */ VARIANT_BOOL *Listen);


void __RPC_STUB IInkPicture_GetEventInterest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkPicture_SetEventInterest_Proxy( 
    IInkPicture * This,
    /* [in] */ InkCollectorEventInterest EventId,
    /* [in] */ VARIANT_BOOL Listen);


void __RPC_STUB IInkPicture_SetEventInterest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_InkEnabled_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ VARIANT_BOOL *Collecting);


void __RPC_STUB IInkPicture_get_InkEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_InkEnabled_Proxy( 
    IInkPicture * This,
    /* [in] */ VARIANT_BOOL Collecting);


void __RPC_STUB IInkPicture_put_InkEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkPicture_get_Enabled_Proxy( 
    IInkPicture * This,
    /* [retval][out] */ VARIANT_BOOL *pbool);


void __RPC_STUB IInkPicture_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkPicture_put_Enabled_Proxy( 
    IInkPicture * This,
    /* [in] */ VARIANT_BOOL vbool);


void __RPC_STUB IInkPicture_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkPicture_INTERFACE_DEFINED__ */


#ifndef ___IInkPictureEvents_DISPINTERFACE_DEFINED__
#define ___IInkPictureEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IInkPictureEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IInkPictureEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("60ff4fee-22ff-4484-acc1-d308d9cd7ea3")
    _IInkPictureEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IInkPictureEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IInkPictureEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IInkPictureEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IInkPictureEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IInkPictureEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IInkPictureEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IInkPictureEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IInkPictureEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IInkPictureEventsVtbl;

    interface _IInkPictureEvents
    {
        CONST_VTBL struct _IInkPictureEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IInkPictureEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IInkPictureEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IInkPictureEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IInkPictureEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IInkPictureEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IInkPictureEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IInkPictureEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IInkPictureEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IInkRecognizer_INTERFACE_DEFINED__
#define __IInkRecognizer_INTERFACE_DEFINED__

/* interface IInkRecognizer */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognizer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("782BF7CF-034B-4396-8A32-3A1833CF6B56")
    IInkRecognizer : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *Name) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Vendor( 
            /* [retval][out] */ BSTR *Vendor) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Capabilities( 
            /* [retval][out] */ InkRecognizerCapabilities *CapabilitiesFlags) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Languages( 
            /* [retval][out] */ VARIANT *Languages) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SupportedProperties( 
            /* [retval][out] */ VARIANT *SupportedProperties) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PreferredPacketDescription( 
            /* [retval][out] */ VARIANT *PreferredPacketDescription) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateRecognizerContext( 
            /* [retval][out] */ IInkRecognizerContext **Context) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognizerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkRecognizer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkRecognizer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkRecognizer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkRecognizer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkRecognizer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkRecognizer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkRecognizer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IInkRecognizer * This,
            /* [retval][out] */ BSTR *Name);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Vendor )( 
            IInkRecognizer * This,
            /* [retval][out] */ BSTR *Vendor);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Capabilities )( 
            IInkRecognizer * This,
            /* [retval][out] */ InkRecognizerCapabilities *CapabilitiesFlags);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Languages )( 
            IInkRecognizer * This,
            /* [retval][out] */ VARIANT *Languages);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SupportedProperties )( 
            IInkRecognizer * This,
            /* [retval][out] */ VARIANT *SupportedProperties);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreferredPacketDescription )( 
            IInkRecognizer * This,
            /* [retval][out] */ VARIANT *PreferredPacketDescription);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateRecognizerContext )( 
            IInkRecognizer * This,
            /* [retval][out] */ IInkRecognizerContext **Context);
        
        END_INTERFACE
    } IInkRecognizerVtbl;

    interface IInkRecognizer
    {
        CONST_VTBL struct IInkRecognizerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognizer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognizer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognizer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognizer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognizer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognizer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognizer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognizer_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define IInkRecognizer_get_Vendor(This,Vendor)	\
    (This)->lpVtbl -> get_Vendor(This,Vendor)

#define IInkRecognizer_get_Capabilities(This,CapabilitiesFlags)	\
    (This)->lpVtbl -> get_Capabilities(This,CapabilitiesFlags)

#define IInkRecognizer_get_Languages(This,Languages)	\
    (This)->lpVtbl -> get_Languages(This,Languages)

#define IInkRecognizer_get_SupportedProperties(This,SupportedProperties)	\
    (This)->lpVtbl -> get_SupportedProperties(This,SupportedProperties)

#define IInkRecognizer_get_PreferredPacketDescription(This,PreferredPacketDescription)	\
    (This)->lpVtbl -> get_PreferredPacketDescription(This,PreferredPacketDescription)

#define IInkRecognizer_CreateRecognizerContext(This,Context)	\
    (This)->lpVtbl -> CreateRecognizerContext(This,Context)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_Name_Proxy( 
    IInkRecognizer * This,
    /* [retval][out] */ BSTR *Name);


void __RPC_STUB IInkRecognizer_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_Vendor_Proxy( 
    IInkRecognizer * This,
    /* [retval][out] */ BSTR *Vendor);


void __RPC_STUB IInkRecognizer_get_Vendor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_Capabilities_Proxy( 
    IInkRecognizer * This,
    /* [retval][out] */ InkRecognizerCapabilities *CapabilitiesFlags);


void __RPC_STUB IInkRecognizer_get_Capabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_Languages_Proxy( 
    IInkRecognizer * This,
    /* [retval][out] */ VARIANT *Languages);


void __RPC_STUB IInkRecognizer_get_Languages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_SupportedProperties_Proxy( 
    IInkRecognizer * This,
    /* [retval][out] */ VARIANT *SupportedProperties);


void __RPC_STUB IInkRecognizer_get_SupportedProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_get_PreferredPacketDescription_Proxy( 
    IInkRecognizer * This,
    /* [retval][out] */ VARIANT *PreferredPacketDescription);


void __RPC_STUB IInkRecognizer_get_PreferredPacketDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizer_CreateRecognizerContext_Proxy( 
    IInkRecognizer * This,
    /* [retval][out] */ IInkRecognizerContext **Context);


void __RPC_STUB IInkRecognizer_CreateRecognizerContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognizer_INTERFACE_DEFINED__ */


#ifndef __IInkRecognizers_INTERFACE_DEFINED__
#define __IInkRecognizers_INTERFACE_DEFINED__

/* interface IInkRecognizers */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognizers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9CCC4F12-B0B7-4a8b-BF58-4AECA4E8CEFD")
    IInkRecognizers : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDefaultRecognizer( 
            /* [defaultvalue][in] */ long lcid,
            /* [retval][out] */ IInkRecognizer **DefaultRecognizer) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IInkRecognizer **InkRecognizer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognizersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkRecognizers * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkRecognizers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkRecognizers * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkRecognizers * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkRecognizers * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkRecognizers * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkRecognizers * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IInkRecognizers * This,
            /* [retval][out] */ long *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IInkRecognizers * This,
            /* [retval][out] */ IUnknown **_NewEnum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDefaultRecognizer )( 
            IInkRecognizers * This,
            /* [defaultvalue][in] */ long lcid,
            /* [retval][out] */ IInkRecognizer **DefaultRecognizer);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IInkRecognizers * This,
            /* [in] */ long Index,
            /* [retval][out] */ IInkRecognizer **InkRecognizer);
        
        END_INTERFACE
    } IInkRecognizersVtbl;

    interface IInkRecognizers
    {
        CONST_VTBL struct IInkRecognizersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognizers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognizers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognizers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognizers_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognizers_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognizers_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognizers_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognizers_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkRecognizers_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkRecognizers_GetDefaultRecognizer(This,lcid,DefaultRecognizer)	\
    (This)->lpVtbl -> GetDefaultRecognizer(This,lcid,DefaultRecognizer)

#define IInkRecognizers_Item(This,Index,InkRecognizer)	\
    (This)->lpVtbl -> Item(This,Index,InkRecognizer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizers_get_Count_Proxy( 
    IInkRecognizers * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB IInkRecognizers_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizers_get__NewEnum_Proxy( 
    IInkRecognizers * This,
    /* [retval][out] */ IUnknown **_NewEnum);


void __RPC_STUB IInkRecognizers_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizers_GetDefaultRecognizer_Proxy( 
    IInkRecognizers * This,
    /* [defaultvalue][in] */ long lcid,
    /* [retval][out] */ IInkRecognizer **DefaultRecognizer);


void __RPC_STUB IInkRecognizers_GetDefaultRecognizer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizers_Item_Proxy( 
    IInkRecognizers * This,
    /* [in] */ long Index,
    /* [retval][out] */ IInkRecognizer **InkRecognizer);


void __RPC_STUB IInkRecognizers_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognizers_INTERFACE_DEFINED__ */


#ifndef ___IInkRecognitionEvents_DISPINTERFACE_DEFINED__
#define ___IInkRecognitionEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IInkRecognitionEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IInkRecognitionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("17BCE92F-2E21-47FD-9D33-3C6AFBFD8C59")
    _IInkRecognitionEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IInkRecognitionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IInkRecognitionEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IInkRecognitionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IInkRecognitionEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IInkRecognitionEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IInkRecognitionEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IInkRecognitionEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IInkRecognitionEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IInkRecognitionEventsVtbl;

    interface _IInkRecognitionEvents
    {
        CONST_VTBL struct _IInkRecognitionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IInkRecognitionEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IInkRecognitionEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IInkRecognitionEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IInkRecognitionEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IInkRecognitionEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IInkRecognitionEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IInkRecognitionEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IInkRecognitionEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IInkRecognizerContext_INTERFACE_DEFINED__
#define __IInkRecognizerContext_INTERFACE_DEFINED__

/* interface IInkRecognizerContext */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognizerContext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C68F52F9-32A3-4625-906C-44FC23B40958")
    IInkRecognizerContext : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Strokes( 
            /* [in] */ IInkStrokes *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CharacterAutoCompletionMode( 
            /* [retval][out] */ InkRecognizerCharacterAutoCompletionMode *Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CharacterAutoCompletionMode( 
            /* [in] */ InkRecognizerCharacterAutoCompletionMode Mode) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Factoid( 
            /* [retval][out] */ BSTR *Factoid) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Factoid( 
            /* [in] */ BSTR factoid) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Guide( 
            /* [retval][out] */ IInkRecognizerGuide **RecognizerGuide) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Guide( 
            /* [in] */ IInkRecognizerGuide *RecognizerGuide) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PrefixText( 
            /* [retval][out] */ BSTR *Prefix) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PrefixText( 
            /* [in] */ BSTR Prefix) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SuffixText( 
            /* [retval][out] */ BSTR *Suffix) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SuffixText( 
            /* [in] */ BSTR Suffix) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecognitionFlags( 
            /* [retval][out] */ InkRecognitionModes *Modes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecognitionFlags( 
            /* [in] */ InkRecognitionModes Modes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WordList( 
            /* [retval][out] */ IInkWordList **WordList) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_WordList( 
            /* [in] */ IInkWordList *WordList) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Recognizer( 
            /* [retval][out] */ IInkRecognizer **Recognizer) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Recognize( 
            /* [out][in] */ InkRecognitionStatus *RecognitionStatus,
            /* [retval][out] */ IInkRecognitionResult **RecognitionResult) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE StopBackgroundRecognition( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE EndInkInput( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE BackgroundRecognize( 
            /* [optional][in] */ VARIANT CustomData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE BackgroundRecognizeWithAlternates( 
            /* [optional][in] */ VARIANT CustomData) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IInkRecognizerContext **RecoContext) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IsStringSupported( 
            /* [in] */ BSTR String,
            /* [retval][out] */ VARIANT_BOOL *Supported) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognizerContextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkRecognizerContext * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkRecognizerContext * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkRecognizerContext * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkRecognizerContext * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkRecognizerContext * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkRecognizerContext * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkRecognizerContext * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Strokes )( 
            IInkRecognizerContext * This,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Strokes )( 
            IInkRecognizerContext * This,
            /* [in] */ IInkStrokes *Strokes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CharacterAutoCompletionMode )( 
            IInkRecognizerContext * This,
            /* [retval][out] */ InkRecognizerCharacterAutoCompletionMode *Mode);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CharacterAutoCompletionMode )( 
            IInkRecognizerContext * This,
            /* [in] */ InkRecognizerCharacterAutoCompletionMode Mode);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Factoid )( 
            IInkRecognizerContext * This,
            /* [retval][out] */ BSTR *Factoid);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Factoid )( 
            IInkRecognizerContext * This,
            /* [in] */ BSTR factoid);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Guide )( 
            IInkRecognizerContext * This,
            /* [retval][out] */ IInkRecognizerGuide **RecognizerGuide);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Guide )( 
            IInkRecognizerContext * This,
            /* [in] */ IInkRecognizerGuide *RecognizerGuide);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrefixText )( 
            IInkRecognizerContext * This,
            /* [retval][out] */ BSTR *Prefix);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PrefixText )( 
            IInkRecognizerContext * This,
            /* [in] */ BSTR Prefix);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SuffixText )( 
            IInkRecognizerContext * This,
            /* [retval][out] */ BSTR *Suffix);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SuffixText )( 
            IInkRecognizerContext * This,
            /* [in] */ BSTR Suffix);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RecognitionFlags )( 
            IInkRecognizerContext * This,
            /* [retval][out] */ InkRecognitionModes *Modes);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RecognitionFlags )( 
            IInkRecognizerContext * This,
            /* [in] */ InkRecognitionModes Modes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WordList )( 
            IInkRecognizerContext * This,
            /* [retval][out] */ IInkWordList **WordList);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_WordList )( 
            IInkRecognizerContext * This,
            /* [in] */ IInkWordList *WordList);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Recognizer )( 
            IInkRecognizerContext * This,
            /* [retval][out] */ IInkRecognizer **Recognizer);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Recognize )( 
            IInkRecognizerContext * This,
            /* [out][in] */ InkRecognitionStatus *RecognitionStatus,
            /* [retval][out] */ IInkRecognitionResult **RecognitionResult);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopBackgroundRecognition )( 
            IInkRecognizerContext * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EndInkInput )( 
            IInkRecognizerContext * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BackgroundRecognize )( 
            IInkRecognizerContext * This,
            /* [optional][in] */ VARIANT CustomData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BackgroundRecognizeWithAlternates )( 
            IInkRecognizerContext * This,
            /* [optional][in] */ VARIANT CustomData);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IInkRecognizerContext * This,
            /* [retval][out] */ IInkRecognizerContext **RecoContext);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *IsStringSupported )( 
            IInkRecognizerContext * This,
            /* [in] */ BSTR String,
            /* [retval][out] */ VARIANT_BOOL *Supported);
        
        END_INTERFACE
    } IInkRecognizerContextVtbl;

    interface IInkRecognizerContext
    {
        CONST_VTBL struct IInkRecognizerContextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognizerContext_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognizerContext_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognizerContext_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognizerContext_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognizerContext_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognizerContext_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognizerContext_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognizerContext_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkRecognizerContext_putref_Strokes(This,Strokes)	\
    (This)->lpVtbl -> putref_Strokes(This,Strokes)

#define IInkRecognizerContext_get_CharacterAutoCompletionMode(This,Mode)	\
    (This)->lpVtbl -> get_CharacterAutoCompletionMode(This,Mode)

#define IInkRecognizerContext_put_CharacterAutoCompletionMode(This,Mode)	\
    (This)->lpVtbl -> put_CharacterAutoCompletionMode(This,Mode)

#define IInkRecognizerContext_get_Factoid(This,Factoid)	\
    (This)->lpVtbl -> get_Factoid(This,Factoid)

#define IInkRecognizerContext_put_Factoid(This,factoid)	\
    (This)->lpVtbl -> put_Factoid(This,factoid)

#define IInkRecognizerContext_get_Guide(This,RecognizerGuide)	\
    (This)->lpVtbl -> get_Guide(This,RecognizerGuide)

#define IInkRecognizerContext_putref_Guide(This,RecognizerGuide)	\
    (This)->lpVtbl -> putref_Guide(This,RecognizerGuide)

#define IInkRecognizerContext_get_PrefixText(This,Prefix)	\
    (This)->lpVtbl -> get_PrefixText(This,Prefix)

#define IInkRecognizerContext_put_PrefixText(This,Prefix)	\
    (This)->lpVtbl -> put_PrefixText(This,Prefix)

#define IInkRecognizerContext_get_SuffixText(This,Suffix)	\
    (This)->lpVtbl -> get_SuffixText(This,Suffix)

#define IInkRecognizerContext_put_SuffixText(This,Suffix)	\
    (This)->lpVtbl -> put_SuffixText(This,Suffix)

#define IInkRecognizerContext_get_RecognitionFlags(This,Modes)	\
    (This)->lpVtbl -> get_RecognitionFlags(This,Modes)

#define IInkRecognizerContext_put_RecognitionFlags(This,Modes)	\
    (This)->lpVtbl -> put_RecognitionFlags(This,Modes)

#define IInkRecognizerContext_get_WordList(This,WordList)	\
    (This)->lpVtbl -> get_WordList(This,WordList)

#define IInkRecognizerContext_putref_WordList(This,WordList)	\
    (This)->lpVtbl -> putref_WordList(This,WordList)

#define IInkRecognizerContext_get_Recognizer(This,Recognizer)	\
    (This)->lpVtbl -> get_Recognizer(This,Recognizer)

#define IInkRecognizerContext_Recognize(This,RecognitionStatus,RecognitionResult)	\
    (This)->lpVtbl -> Recognize(This,RecognitionStatus,RecognitionResult)

#define IInkRecognizerContext_StopBackgroundRecognition(This)	\
    (This)->lpVtbl -> StopBackgroundRecognition(This)

#define IInkRecognizerContext_EndInkInput(This)	\
    (This)->lpVtbl -> EndInkInput(This)

#define IInkRecognizerContext_BackgroundRecognize(This,CustomData)	\
    (This)->lpVtbl -> BackgroundRecognize(This,CustomData)

#define IInkRecognizerContext_BackgroundRecognizeWithAlternates(This,CustomData)	\
    (This)->lpVtbl -> BackgroundRecognizeWithAlternates(This,CustomData)

#define IInkRecognizerContext_Clone(This,RecoContext)	\
    (This)->lpVtbl -> Clone(This,RecoContext)

#define IInkRecognizerContext_IsStringSupported(This,String,Supported)	\
    (This)->lpVtbl -> IsStringSupported(This,String,Supported)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_Strokes_Proxy( 
    IInkRecognizerContext * This,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkRecognizerContext_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_putref_Strokes_Proxy( 
    IInkRecognizerContext * This,
    /* [in] */ IInkStrokes *Strokes);


void __RPC_STUB IInkRecognizerContext_putref_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_CharacterAutoCompletionMode_Proxy( 
    IInkRecognizerContext * This,
    /* [retval][out] */ InkRecognizerCharacterAutoCompletionMode *Mode);


void __RPC_STUB IInkRecognizerContext_get_CharacterAutoCompletionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_put_CharacterAutoCompletionMode_Proxy( 
    IInkRecognizerContext * This,
    /* [in] */ InkRecognizerCharacterAutoCompletionMode Mode);


void __RPC_STUB IInkRecognizerContext_put_CharacterAutoCompletionMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_Factoid_Proxy( 
    IInkRecognizerContext * This,
    /* [retval][out] */ BSTR *Factoid);


void __RPC_STUB IInkRecognizerContext_get_Factoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_put_Factoid_Proxy( 
    IInkRecognizerContext * This,
    /* [in] */ BSTR factoid);


void __RPC_STUB IInkRecognizerContext_put_Factoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_Guide_Proxy( 
    IInkRecognizerContext * This,
    /* [retval][out] */ IInkRecognizerGuide **RecognizerGuide);


void __RPC_STUB IInkRecognizerContext_get_Guide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_putref_Guide_Proxy( 
    IInkRecognizerContext * This,
    /* [in] */ IInkRecognizerGuide *RecognizerGuide);


void __RPC_STUB IInkRecognizerContext_putref_Guide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_PrefixText_Proxy( 
    IInkRecognizerContext * This,
    /* [retval][out] */ BSTR *Prefix);


void __RPC_STUB IInkRecognizerContext_get_PrefixText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_put_PrefixText_Proxy( 
    IInkRecognizerContext * This,
    /* [in] */ BSTR Prefix);


void __RPC_STUB IInkRecognizerContext_put_PrefixText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_SuffixText_Proxy( 
    IInkRecognizerContext * This,
    /* [retval][out] */ BSTR *Suffix);


void __RPC_STUB IInkRecognizerContext_get_SuffixText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_put_SuffixText_Proxy( 
    IInkRecognizerContext * This,
    /* [in] */ BSTR Suffix);


void __RPC_STUB IInkRecognizerContext_put_SuffixText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_RecognitionFlags_Proxy( 
    IInkRecognizerContext * This,
    /* [retval][out] */ InkRecognitionModes *Modes);


void __RPC_STUB IInkRecognizerContext_get_RecognitionFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_put_RecognitionFlags_Proxy( 
    IInkRecognizerContext * This,
    /* [in] */ InkRecognitionModes Modes);


void __RPC_STUB IInkRecognizerContext_put_RecognitionFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_WordList_Proxy( 
    IInkRecognizerContext * This,
    /* [retval][out] */ IInkWordList **WordList);


void __RPC_STUB IInkRecognizerContext_get_WordList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_putref_WordList_Proxy( 
    IInkRecognizerContext * This,
    /* [in] */ IInkWordList *WordList);


void __RPC_STUB IInkRecognizerContext_putref_WordList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_get_Recognizer_Proxy( 
    IInkRecognizerContext * This,
    /* [retval][out] */ IInkRecognizer **Recognizer);


void __RPC_STUB IInkRecognizerContext_get_Recognizer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_Recognize_Proxy( 
    IInkRecognizerContext * This,
    /* [out][in] */ InkRecognitionStatus *RecognitionStatus,
    /* [retval][out] */ IInkRecognitionResult **RecognitionResult);


void __RPC_STUB IInkRecognizerContext_Recognize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_StopBackgroundRecognition_Proxy( 
    IInkRecognizerContext * This);


void __RPC_STUB IInkRecognizerContext_StopBackgroundRecognition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_EndInkInput_Proxy( 
    IInkRecognizerContext * This);


void __RPC_STUB IInkRecognizerContext_EndInkInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_BackgroundRecognize_Proxy( 
    IInkRecognizerContext * This,
    /* [optional][in] */ VARIANT CustomData);


void __RPC_STUB IInkRecognizerContext_BackgroundRecognize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_BackgroundRecognizeWithAlternates_Proxy( 
    IInkRecognizerContext * This,
    /* [optional][in] */ VARIANT CustomData);


void __RPC_STUB IInkRecognizerContext_BackgroundRecognizeWithAlternates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_Clone_Proxy( 
    IInkRecognizerContext * This,
    /* [retval][out] */ IInkRecognizerContext **RecoContext);


void __RPC_STUB IInkRecognizerContext_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognizerContext_IsStringSupported_Proxy( 
    IInkRecognizerContext * This,
    /* [in] */ BSTR String,
    /* [retval][out] */ VARIANT_BOOL *Supported);


void __RPC_STUB IInkRecognizerContext_IsStringSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognizerContext_INTERFACE_DEFINED__ */


#ifndef __IInkRecognitionResult_INTERFACE_DEFINED__
#define __IInkRecognitionResult_INTERFACE_DEFINED__

/* interface IInkRecognitionResult */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognitionResult;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3BC129A8-86CD-45ad-BDE8-E0D32D61C16D")
    IInkRecognitionResult : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TopString( 
            /* [retval][out] */ BSTR *TopString) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TopAlternate( 
            /* [retval][out] */ IInkRecognitionAlternate **TopAlternate) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TopConfidence( 
            /* [retval][out] */ InkRecognitionConfidence *TopConfidence) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AlternatesFromSelection( 
            /* [defaultvalue][in] */ long selectionStart,
            /* [defaultvalue][in] */ long selectionLength,
            /* [defaultvalue][in] */ long maximumAlternates,
            /* [retval][out] */ IInkRecognitionAlternates **AlternatesFromSelection) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ModifyTopAlternate( 
            /* [in] */ IInkRecognitionAlternate *Alternate) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetResultOnStrokes( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognitionResultVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkRecognitionResult * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkRecognitionResult * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkRecognitionResult * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkRecognitionResult * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkRecognitionResult * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkRecognitionResult * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkRecognitionResult * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopString )( 
            IInkRecognitionResult * This,
            /* [retval][out] */ BSTR *TopString);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopAlternate )( 
            IInkRecognitionResult * This,
            /* [retval][out] */ IInkRecognitionAlternate **TopAlternate);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TopConfidence )( 
            IInkRecognitionResult * This,
            /* [retval][out] */ InkRecognitionConfidence *TopConfidence);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Strokes )( 
            IInkRecognitionResult * This,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AlternatesFromSelection )( 
            IInkRecognitionResult * This,
            /* [defaultvalue][in] */ long selectionStart,
            /* [defaultvalue][in] */ long selectionLength,
            /* [defaultvalue][in] */ long maximumAlternates,
            /* [retval][out] */ IInkRecognitionAlternates **AlternatesFromSelection);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ModifyTopAlternate )( 
            IInkRecognitionResult * This,
            /* [in] */ IInkRecognitionAlternate *Alternate);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetResultOnStrokes )( 
            IInkRecognitionResult * This);
        
        END_INTERFACE
    } IInkRecognitionResultVtbl;

    interface IInkRecognitionResult
    {
        CONST_VTBL struct IInkRecognitionResultVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognitionResult_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognitionResult_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognitionResult_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognitionResult_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognitionResult_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognitionResult_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognitionResult_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognitionResult_get_TopString(This,TopString)	\
    (This)->lpVtbl -> get_TopString(This,TopString)

#define IInkRecognitionResult_get_TopAlternate(This,TopAlternate)	\
    (This)->lpVtbl -> get_TopAlternate(This,TopAlternate)

#define IInkRecognitionResult_get_TopConfidence(This,TopConfidence)	\
    (This)->lpVtbl -> get_TopConfidence(This,TopConfidence)

#define IInkRecognitionResult_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkRecognitionResult_AlternatesFromSelection(This,selectionStart,selectionLength,maximumAlternates,AlternatesFromSelection)	\
    (This)->lpVtbl -> AlternatesFromSelection(This,selectionStart,selectionLength,maximumAlternates,AlternatesFromSelection)

#define IInkRecognitionResult_ModifyTopAlternate(This,Alternate)	\
    (This)->lpVtbl -> ModifyTopAlternate(This,Alternate)

#define IInkRecognitionResult_SetResultOnStrokes(This)	\
    (This)->lpVtbl -> SetResultOnStrokes(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_get_TopString_Proxy( 
    IInkRecognitionResult * This,
    /* [retval][out] */ BSTR *TopString);


void __RPC_STUB IInkRecognitionResult_get_TopString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_get_TopAlternate_Proxy( 
    IInkRecognitionResult * This,
    /* [retval][out] */ IInkRecognitionAlternate **TopAlternate);


void __RPC_STUB IInkRecognitionResult_get_TopAlternate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_get_TopConfidence_Proxy( 
    IInkRecognitionResult * This,
    /* [retval][out] */ InkRecognitionConfidence *TopConfidence);


void __RPC_STUB IInkRecognitionResult_get_TopConfidence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_get_Strokes_Proxy( 
    IInkRecognitionResult * This,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkRecognitionResult_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_AlternatesFromSelection_Proxy( 
    IInkRecognitionResult * This,
    /* [defaultvalue][in] */ long selectionStart,
    /* [defaultvalue][in] */ long selectionLength,
    /* [defaultvalue][in] */ long maximumAlternates,
    /* [retval][out] */ IInkRecognitionAlternates **AlternatesFromSelection);


void __RPC_STUB IInkRecognitionResult_AlternatesFromSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_ModifyTopAlternate_Proxy( 
    IInkRecognitionResult * This,
    /* [in] */ IInkRecognitionAlternate *Alternate);


void __RPC_STUB IInkRecognitionResult_ModifyTopAlternate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionResult_SetResultOnStrokes_Proxy( 
    IInkRecognitionResult * This);


void __RPC_STUB IInkRecognitionResult_SetResultOnStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognitionResult_INTERFACE_DEFINED__ */


#ifndef __IInkRecognitionAlternate_INTERFACE_DEFINED__
#define __IInkRecognitionAlternate_INTERFACE_DEFINED__

/* interface IInkRecognitionAlternate */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognitionAlternate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7E660AD-77E4-429b-ADDA-873780D1FC4A")
    IInkRecognitionAlternate : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_String( 
            /* [retval][out] */ BSTR *RecoString) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Confidence( 
            /* [retval][out] */ InkRecognitionConfidence *Confidence) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Baseline( 
            /* [retval][out] */ VARIANT *Baseline) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Midline( 
            /* [retval][out] */ VARIANT *Midline) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ascender( 
            /* [retval][out] */ VARIANT *Ascender) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Descender( 
            /* [retval][out] */ VARIANT *Descender) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LineNumber( 
            /* [retval][out] */ long *LineNumber) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LineAlternates( 
            /* [retval][out] */ IInkRecognitionAlternates **LineAlternates) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConfidenceAlternates( 
            /* [retval][out] */ IInkRecognitionAlternates **ConfidenceAlternates) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStrokesFromStrokeRanges( 
            /* [in] */ IInkStrokes *Strokes,
            /* [retval][out] */ IInkStrokes **GetStrokesFromStrokeRanges) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStrokesFromTextRange( 
            /* [out][in] */ long *selectionStart,
            /* [out][in] */ long *selectionLength,
            /* [retval][out] */ IInkStrokes **GetStrokesFromTextRange) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTextRangeFromStrokes( 
            /* [in] */ IInkStrokes *Strokes,
            /* [out][in] */ long *selectionStart,
            /* [out][in] */ long *selectionLength) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AlternatesWithConstantPropertyValues( 
            /* [in] */ BSTR PropertyType,
            /* [retval][out] */ IInkRecognitionAlternates **AlternatesWithConstantPropertyValues) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPropertyValue( 
            /* [in] */ BSTR PropertyType,
            /* [retval][out] */ VARIANT *PropertyValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognitionAlternateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkRecognitionAlternate * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkRecognitionAlternate * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkRecognitionAlternate * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkRecognitionAlternate * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkRecognitionAlternate * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkRecognitionAlternate * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkRecognitionAlternate * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_String )( 
            IInkRecognitionAlternate * This,
            /* [retval][out] */ BSTR *RecoString);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Confidence )( 
            IInkRecognitionAlternate * This,
            /* [retval][out] */ InkRecognitionConfidence *Confidence);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Baseline )( 
            IInkRecognitionAlternate * This,
            /* [retval][out] */ VARIANT *Baseline);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Midline )( 
            IInkRecognitionAlternate * This,
            /* [retval][out] */ VARIANT *Midline);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ascender )( 
            IInkRecognitionAlternate * This,
            /* [retval][out] */ VARIANT *Ascender);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Descender )( 
            IInkRecognitionAlternate * This,
            /* [retval][out] */ VARIANT *Descender);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineNumber )( 
            IInkRecognitionAlternate * This,
            /* [retval][out] */ long *LineNumber);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Strokes )( 
            IInkRecognitionAlternate * This,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineAlternates )( 
            IInkRecognitionAlternate * This,
            /* [retval][out] */ IInkRecognitionAlternates **LineAlternates);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConfidenceAlternates )( 
            IInkRecognitionAlternate * This,
            /* [retval][out] */ IInkRecognitionAlternates **ConfidenceAlternates);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetStrokesFromStrokeRanges )( 
            IInkRecognitionAlternate * This,
            /* [in] */ IInkStrokes *Strokes,
            /* [retval][out] */ IInkStrokes **GetStrokesFromStrokeRanges);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetStrokesFromTextRange )( 
            IInkRecognitionAlternate * This,
            /* [out][in] */ long *selectionStart,
            /* [out][in] */ long *selectionLength,
            /* [retval][out] */ IInkStrokes **GetStrokesFromTextRange);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetTextRangeFromStrokes )( 
            IInkRecognitionAlternate * This,
            /* [in] */ IInkStrokes *Strokes,
            /* [out][in] */ long *selectionStart,
            /* [out][in] */ long *selectionLength);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AlternatesWithConstantPropertyValues )( 
            IInkRecognitionAlternate * This,
            /* [in] */ BSTR PropertyType,
            /* [retval][out] */ IInkRecognitionAlternates **AlternatesWithConstantPropertyValues);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPropertyValue )( 
            IInkRecognitionAlternate * This,
            /* [in] */ BSTR PropertyType,
            /* [retval][out] */ VARIANT *PropertyValue);
        
        END_INTERFACE
    } IInkRecognitionAlternateVtbl;

    interface IInkRecognitionAlternate
    {
        CONST_VTBL struct IInkRecognitionAlternateVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognitionAlternate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognitionAlternate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognitionAlternate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognitionAlternate_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognitionAlternate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognitionAlternate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognitionAlternate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognitionAlternate_get_String(This,RecoString)	\
    (This)->lpVtbl -> get_String(This,RecoString)

#define IInkRecognitionAlternate_get_Confidence(This,Confidence)	\
    (This)->lpVtbl -> get_Confidence(This,Confidence)

#define IInkRecognitionAlternate_get_Baseline(This,Baseline)	\
    (This)->lpVtbl -> get_Baseline(This,Baseline)

#define IInkRecognitionAlternate_get_Midline(This,Midline)	\
    (This)->lpVtbl -> get_Midline(This,Midline)

#define IInkRecognitionAlternate_get_Ascender(This,Ascender)	\
    (This)->lpVtbl -> get_Ascender(This,Ascender)

#define IInkRecognitionAlternate_get_Descender(This,Descender)	\
    (This)->lpVtbl -> get_Descender(This,Descender)

#define IInkRecognitionAlternate_get_LineNumber(This,LineNumber)	\
    (This)->lpVtbl -> get_LineNumber(This,LineNumber)

#define IInkRecognitionAlternate_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkRecognitionAlternate_get_LineAlternates(This,LineAlternates)	\
    (This)->lpVtbl -> get_LineAlternates(This,LineAlternates)

#define IInkRecognitionAlternate_get_ConfidenceAlternates(This,ConfidenceAlternates)	\
    (This)->lpVtbl -> get_ConfidenceAlternates(This,ConfidenceAlternates)

#define IInkRecognitionAlternate_GetStrokesFromStrokeRanges(This,Strokes,GetStrokesFromStrokeRanges)	\
    (This)->lpVtbl -> GetStrokesFromStrokeRanges(This,Strokes,GetStrokesFromStrokeRanges)

#define IInkRecognitionAlternate_GetStrokesFromTextRange(This,selectionStart,selectionLength,GetStrokesFromTextRange)	\
    (This)->lpVtbl -> GetStrokesFromTextRange(This,selectionStart,selectionLength,GetStrokesFromTextRange)

#define IInkRecognitionAlternate_GetTextRangeFromStrokes(This,Strokes,selectionStart,selectionLength)	\
    (This)->lpVtbl -> GetTextRangeFromStrokes(This,Strokes,selectionStart,selectionLength)

#define IInkRecognitionAlternate_AlternatesWithConstantPropertyValues(This,PropertyType,AlternatesWithConstantPropertyValues)	\
    (This)->lpVtbl -> AlternatesWithConstantPropertyValues(This,PropertyType,AlternatesWithConstantPropertyValues)

#define IInkRecognitionAlternate_GetPropertyValue(This,PropertyType,PropertyValue)	\
    (This)->lpVtbl -> GetPropertyValue(This,PropertyType,PropertyValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_String_Proxy( 
    IInkRecognitionAlternate * This,
    /* [retval][out] */ BSTR *RecoString);


void __RPC_STUB IInkRecognitionAlternate_get_String_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Confidence_Proxy( 
    IInkRecognitionAlternate * This,
    /* [retval][out] */ InkRecognitionConfidence *Confidence);


void __RPC_STUB IInkRecognitionAlternate_get_Confidence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Baseline_Proxy( 
    IInkRecognitionAlternate * This,
    /* [retval][out] */ VARIANT *Baseline);


void __RPC_STUB IInkRecognitionAlternate_get_Baseline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Midline_Proxy( 
    IInkRecognitionAlternate * This,
    /* [retval][out] */ VARIANT *Midline);


void __RPC_STUB IInkRecognitionAlternate_get_Midline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Ascender_Proxy( 
    IInkRecognitionAlternate * This,
    /* [retval][out] */ VARIANT *Ascender);


void __RPC_STUB IInkRecognitionAlternate_get_Ascender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Descender_Proxy( 
    IInkRecognitionAlternate * This,
    /* [retval][out] */ VARIANT *Descender);


void __RPC_STUB IInkRecognitionAlternate_get_Descender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_LineNumber_Proxy( 
    IInkRecognitionAlternate * This,
    /* [retval][out] */ long *LineNumber);


void __RPC_STUB IInkRecognitionAlternate_get_LineNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_Strokes_Proxy( 
    IInkRecognitionAlternate * This,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkRecognitionAlternate_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_LineAlternates_Proxy( 
    IInkRecognitionAlternate * This,
    /* [retval][out] */ IInkRecognitionAlternates **LineAlternates);


void __RPC_STUB IInkRecognitionAlternate_get_LineAlternates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_get_ConfidenceAlternates_Proxy( 
    IInkRecognitionAlternate * This,
    /* [retval][out] */ IInkRecognitionAlternates **ConfidenceAlternates);


void __RPC_STUB IInkRecognitionAlternate_get_ConfidenceAlternates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_GetStrokesFromStrokeRanges_Proxy( 
    IInkRecognitionAlternate * This,
    /* [in] */ IInkStrokes *Strokes,
    /* [retval][out] */ IInkStrokes **GetStrokesFromStrokeRanges);


void __RPC_STUB IInkRecognitionAlternate_GetStrokesFromStrokeRanges_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_GetStrokesFromTextRange_Proxy( 
    IInkRecognitionAlternate * This,
    /* [out][in] */ long *selectionStart,
    /* [out][in] */ long *selectionLength,
    /* [retval][out] */ IInkStrokes **GetStrokesFromTextRange);


void __RPC_STUB IInkRecognitionAlternate_GetStrokesFromTextRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_GetTextRangeFromStrokes_Proxy( 
    IInkRecognitionAlternate * This,
    /* [in] */ IInkStrokes *Strokes,
    /* [out][in] */ long *selectionStart,
    /* [out][in] */ long *selectionLength);


void __RPC_STUB IInkRecognitionAlternate_GetTextRangeFromStrokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_AlternatesWithConstantPropertyValues_Proxy( 
    IInkRecognitionAlternate * This,
    /* [in] */ BSTR PropertyType,
    /* [retval][out] */ IInkRecognitionAlternates **AlternatesWithConstantPropertyValues);


void __RPC_STUB IInkRecognitionAlternate_AlternatesWithConstantPropertyValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternate_GetPropertyValue_Proxy( 
    IInkRecognitionAlternate * This,
    /* [in] */ BSTR PropertyType,
    /* [retval][out] */ VARIANT *PropertyValue);


void __RPC_STUB IInkRecognitionAlternate_GetPropertyValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognitionAlternate_INTERFACE_DEFINED__ */


#ifndef __IInkRecognitionAlternates_INTERFACE_DEFINED__
#define __IInkRecognitionAlternates_INTERFACE_DEFINED__

/* interface IInkRecognitionAlternates */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognitionAlternates;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("286A167F-9F19-4c61-9D53-4F07BE622B84")
    IInkRecognitionAlternates : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IInkRecognitionAlternate **InkRecoAlternate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognitionAlternatesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkRecognitionAlternates * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkRecognitionAlternates * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkRecognitionAlternates * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkRecognitionAlternates * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkRecognitionAlternates * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkRecognitionAlternates * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkRecognitionAlternates * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IInkRecognitionAlternates * This,
            /* [retval][out] */ long *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IInkRecognitionAlternates * This,
            /* [retval][out] */ IUnknown **_NewEnum);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Strokes )( 
            IInkRecognitionAlternates * This,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IInkRecognitionAlternates * This,
            /* [in] */ long Index,
            /* [retval][out] */ IInkRecognitionAlternate **InkRecoAlternate);
        
        END_INTERFACE
    } IInkRecognitionAlternatesVtbl;

    interface IInkRecognitionAlternates
    {
        CONST_VTBL struct IInkRecognitionAlternatesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognitionAlternates_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognitionAlternates_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognitionAlternates_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognitionAlternates_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognitionAlternates_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognitionAlternates_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognitionAlternates_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognitionAlternates_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkRecognitionAlternates_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkRecognitionAlternates_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkRecognitionAlternates_Item(This,Index,InkRecoAlternate)	\
    (This)->lpVtbl -> Item(This,Index,InkRecoAlternate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternates_get_Count_Proxy( 
    IInkRecognitionAlternates * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB IInkRecognitionAlternates_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternates_get__NewEnum_Proxy( 
    IInkRecognitionAlternates * This,
    /* [retval][out] */ IUnknown **_NewEnum);


void __RPC_STUB IInkRecognitionAlternates_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternates_get_Strokes_Proxy( 
    IInkRecognitionAlternates * This,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkRecognitionAlternates_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkRecognitionAlternates_Item_Proxy( 
    IInkRecognitionAlternates * This,
    /* [in] */ long Index,
    /* [retval][out] */ IInkRecognitionAlternate **InkRecoAlternate);


void __RPC_STUB IInkRecognitionAlternates_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognitionAlternates_INTERFACE_DEFINED__ */


#ifndef __IInkRecognizerGuide_INTERFACE_DEFINED__
#define __IInkRecognizerGuide_INTERFACE_DEFINED__

/* interface IInkRecognizerGuide */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkRecognizerGuide;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D934BE07-7B84-4208-9136-83C20994E905")
    IInkRecognizerGuide : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WritingBox( 
            /* [retval][out] */ IInkRectangle **Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WritingBox( 
            /* [in] */ IInkRectangle *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DrawnBox( 
            /* [retval][out] */ IInkRectangle **Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DrawnBox( 
            /* [in] */ IInkRectangle *Rectangle) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rows( 
            /* [retval][out] */ long *Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Rows( 
            /* [in] */ long Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Columns( 
            /* [retval][out] */ long *Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Columns( 
            /* [in] */ long Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Midline( 
            /* [retval][out] */ long *Units) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Midline( 
            /* [in] */ long Units) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_GuideData( 
            /* [retval][out] */ InkRecoGuide *pRecoGuide) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_GuideData( 
            /* [in] */ InkRecoGuide recoGuide) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkRecognizerGuideVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkRecognizerGuide * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkRecognizerGuide * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkRecognizerGuide * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkRecognizerGuide * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkRecognizerGuide * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkRecognizerGuide * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkRecognizerGuide * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WritingBox )( 
            IInkRecognizerGuide * This,
            /* [retval][out] */ IInkRectangle **Rectangle);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WritingBox )( 
            IInkRecognizerGuide * This,
            /* [in] */ IInkRectangle *Rectangle);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DrawnBox )( 
            IInkRecognizerGuide * This,
            /* [retval][out] */ IInkRectangle **Rectangle);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DrawnBox )( 
            IInkRecognizerGuide * This,
            /* [in] */ IInkRectangle *Rectangle);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rows )( 
            IInkRecognizerGuide * This,
            /* [retval][out] */ long *Units);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Rows )( 
            IInkRecognizerGuide * This,
            /* [in] */ long Units);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Columns )( 
            IInkRecognizerGuide * This,
            /* [retval][out] */ long *Units);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Columns )( 
            IInkRecognizerGuide * This,
            /* [in] */ long Units);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Midline )( 
            IInkRecognizerGuide * This,
            /* [retval][out] */ long *Units);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Midline )( 
            IInkRecognizerGuide * This,
            /* [in] */ long Units);
        
        /* [helpcontext][helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GuideData )( 
            IInkRecognizerGuide * This,
            /* [retval][out] */ InkRecoGuide *pRecoGuide);
        
        /* [helpcontext][helpstring][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GuideData )( 
            IInkRecognizerGuide * This,
            /* [in] */ InkRecoGuide recoGuide);
        
        END_INTERFACE
    } IInkRecognizerGuideVtbl;

    interface IInkRecognizerGuide
    {
        CONST_VTBL struct IInkRecognizerGuideVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkRecognizerGuide_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkRecognizerGuide_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkRecognizerGuide_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkRecognizerGuide_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkRecognizerGuide_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkRecognizerGuide_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkRecognizerGuide_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkRecognizerGuide_get_WritingBox(This,Rectangle)	\
    (This)->lpVtbl -> get_WritingBox(This,Rectangle)

#define IInkRecognizerGuide_put_WritingBox(This,Rectangle)	\
    (This)->lpVtbl -> put_WritingBox(This,Rectangle)

#define IInkRecognizerGuide_get_DrawnBox(This,Rectangle)	\
    (This)->lpVtbl -> get_DrawnBox(This,Rectangle)

#define IInkRecognizerGuide_put_DrawnBox(This,Rectangle)	\
    (This)->lpVtbl -> put_DrawnBox(This,Rectangle)

#define IInkRecognizerGuide_get_Rows(This,Units)	\
    (This)->lpVtbl -> get_Rows(This,Units)

#define IInkRecognizerGuide_put_Rows(This,Units)	\
    (This)->lpVtbl -> put_Rows(This,Units)

#define IInkRecognizerGuide_get_Columns(This,Units)	\
    (This)->lpVtbl -> get_Columns(This,Units)

#define IInkRecognizerGuide_put_Columns(This,Units)	\
    (This)->lpVtbl -> put_Columns(This,Units)

#define IInkRecognizerGuide_get_Midline(This,Units)	\
    (This)->lpVtbl -> get_Midline(This,Units)

#define IInkRecognizerGuide_put_Midline(This,Units)	\
    (This)->lpVtbl -> put_Midline(This,Units)

#define IInkRecognizerGuide_get_GuideData(This,pRecoGuide)	\
    (This)->lpVtbl -> get_GuideData(This,pRecoGuide)

#define IInkRecognizerGuide_put_GuideData(This,recoGuide)	\
    (This)->lpVtbl -> put_GuideData(This,recoGuide)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_get_WritingBox_Proxy( 
    IInkRecognizerGuide * This,
    /* [retval][out] */ IInkRectangle **Rectangle);


void __RPC_STUB IInkRecognizerGuide_get_WritingBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_put_WritingBox_Proxy( 
    IInkRecognizerGuide * This,
    /* [in] */ IInkRectangle *Rectangle);


void __RPC_STUB IInkRecognizerGuide_put_WritingBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_get_DrawnBox_Proxy( 
    IInkRecognizerGuide * This,
    /* [retval][out] */ IInkRectangle **Rectangle);


void __RPC_STUB IInkRecognizerGuide_get_DrawnBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_put_DrawnBox_Proxy( 
    IInkRecognizerGuide * This,
    /* [in] */ IInkRectangle *Rectangle);


void __RPC_STUB IInkRecognizerGuide_put_DrawnBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_get_Rows_Proxy( 
    IInkRecognizerGuide * This,
    /* [retval][out] */ long *Units);


void __RPC_STUB IInkRecognizerGuide_get_Rows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_put_Rows_Proxy( 
    IInkRecognizerGuide * This,
    /* [in] */ long Units);


void __RPC_STUB IInkRecognizerGuide_put_Rows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_get_Columns_Proxy( 
    IInkRecognizerGuide * This,
    /* [retval][out] */ long *Units);


void __RPC_STUB IInkRecognizerGuide_get_Columns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_put_Columns_Proxy( 
    IInkRecognizerGuide * This,
    /* [in] */ long Units);


void __RPC_STUB IInkRecognizerGuide_put_Columns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_get_Midline_Proxy( 
    IInkRecognizerGuide * This,
    /* [retval][out] */ long *Units);


void __RPC_STUB IInkRecognizerGuide_get_Midline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_put_Midline_Proxy( 
    IInkRecognizerGuide * This,
    /* [in] */ long Units);


void __RPC_STUB IInkRecognizerGuide_put_Midline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_get_GuideData_Proxy( 
    IInkRecognizerGuide * This,
    /* [retval][out] */ InkRecoGuide *pRecoGuide);


void __RPC_STUB IInkRecognizerGuide_get_GuideData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE IInkRecognizerGuide_put_GuideData_Proxy( 
    IInkRecognizerGuide * This,
    /* [in] */ InkRecoGuide recoGuide);


void __RPC_STUB IInkRecognizerGuide_put_GuideData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkRecognizerGuide_INTERFACE_DEFINED__ */


#ifndef __IInkWordList_INTERFACE_DEFINED__
#define __IInkWordList_INTERFACE_DEFINED__

/* interface IInkWordList */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkWordList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("76BA3491-CB2F-406b-9961-0E0C4CDAAEF2")
    IInkWordList : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AddWord( 
            /* [in] */ BSTR NewWord) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveWord( 
            /* [in] */ BSTR RemoveWord) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Merge( 
            /* [in] */ IInkWordList *MergeWordList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkWordListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkWordList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkWordList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkWordList * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkWordList * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkWordList * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkWordList * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkWordList * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddWord )( 
            IInkWordList * This,
            /* [in] */ BSTR NewWord);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveWord )( 
            IInkWordList * This,
            /* [in] */ BSTR RemoveWord);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Merge )( 
            IInkWordList * This,
            /* [in] */ IInkWordList *MergeWordList);
        
        END_INTERFACE
    } IInkWordListVtbl;

    interface IInkWordList
    {
        CONST_VTBL struct IInkWordListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkWordList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkWordList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkWordList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkWordList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkWordList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkWordList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkWordList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkWordList_AddWord(This,NewWord)	\
    (This)->lpVtbl -> AddWord(This,NewWord)

#define IInkWordList_RemoveWord(This,RemoveWord)	\
    (This)->lpVtbl -> RemoveWord(This,RemoveWord)

#define IInkWordList_Merge(This,MergeWordList)	\
    (This)->lpVtbl -> Merge(This,MergeWordList)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkWordList_AddWord_Proxy( 
    IInkWordList * This,
    /* [in] */ BSTR NewWord);


void __RPC_STUB IInkWordList_AddWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkWordList_RemoveWord_Proxy( 
    IInkWordList * This,
    /* [in] */ BSTR RemoveWord);


void __RPC_STUB IInkWordList_RemoveWord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkWordList_Merge_Proxy( 
    IInkWordList * This,
    /* [in] */ IInkWordList *MergeWordList);


void __RPC_STUB IInkWordList_Merge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkWordList_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_InkDisp;

#ifdef __cplusplus

class DECLSPEC_UUID("937C1A34-151D-4610-9CA6-A8CC9BDB5D83")
InkDisp;
#endif

EXTERN_C const CLSID CLSID_InkOverlay;

#ifdef __cplusplus

class DECLSPEC_UUID("65d00646-cde3-4a88-9163-6769f0f1a97d")
InkOverlay;
#endif

EXTERN_C const CLSID CLSID_InkPicture;

#ifdef __cplusplus

class DECLSPEC_UUID("04a1e553-fe36-4fde-865e-344194e69424")
InkPicture;
#endif

EXTERN_C const CLSID CLSID_InkCollector;

#ifdef __cplusplus

class DECLSPEC_UUID("43FB1553-AD74-4ee8-88E4-3E6DAAC915DB")
InkCollector;
#endif

EXTERN_C const CLSID CLSID_InkDrawingAttributes;

#ifdef __cplusplus

class DECLSPEC_UUID("D8BF32A2-05A5-44c3-B3AA-5E80AC7D2576")
InkDrawingAttributes;
#endif

EXTERN_C const CLSID CLSID_InkRectangle;

#ifdef __cplusplus

class DECLSPEC_UUID("43B07326-AAE0-4B62-A83D-5FD768B7353C")
InkRectangle;
#endif

EXTERN_C const CLSID CLSID_InkRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("9C1CC6E4-D7EB-4eeb-9091-15A7C8791ED9")
InkRenderer;
#endif

EXTERN_C const CLSID CLSID_InkTransform;

#ifdef __cplusplus

class DECLSPEC_UUID("E3D5D93C-1663-4A78-A1A7-22375DFEBAEE")
InkTransform;
#endif

EXTERN_C const CLSID CLSID_InkRecognizers;

#ifdef __cplusplus

class DECLSPEC_UUID("9FD4E808-F6E6-4e65-98D3-AA39054C1255")
InkRecognizers;
#endif

EXTERN_C const CLSID CLSID_InkRecognizerContext;

#ifdef __cplusplus

class DECLSPEC_UUID("AAC46A37-9229-4fc0-8CCE-4497569BF4D1")
InkRecognizerContext;
#endif

EXTERN_C const CLSID CLSID_InkRecognizerGuide;

#ifdef __cplusplus

class DECLSPEC_UUID("8770D941-A63A-4671-A375-2855A18EBA73")
InkRecognizerGuide;
#endif

EXTERN_C const CLSID CLSID_InkTablets;

#ifdef __cplusplus

class DECLSPEC_UUID("6E4FCB12-510A-4d40-9304-1DA10AE9147C")
InkTablets;
#endif

EXTERN_C const CLSID CLSID_InkWordList;

#ifdef __cplusplus

class DECLSPEC_UUID("9DE85094-F71F-44f1-8471-15A2FA76FCF3")
InkWordList;
#endif

EXTERN_C const CLSID CLSID_InkStrokes;

#ifdef __cplusplus

class DECLSPEC_UUID("48F491BC-240E-4860-B079-A1E94D3D2C86")
InkStrokes;
#endif

#ifndef __IInk_INTERFACE_DEFINED__
#define __IInk_INTERFACE_DEFINED__

/* interface IInk */
/* [unique][hidden][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInk;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("03F8E511-43A1-11D3-8BB6-0080C7D6BAD5")
    IInk : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IInkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInk * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInk * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInk * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInk * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInk * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInk * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInk * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IInkVtbl;

    interface IInk
    {
        CONST_VTBL struct IInkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInk_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInk_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInk_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInk_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInk_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInk_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInk_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInk_INTERFACE_DEFINED__ */


#ifndef __IInkLineInfo_INTERFACE_DEFINED__
#define __IInkLineInfo_INTERFACE_DEFINED__

/* interface IInkLineInfo */
/* [unique][hidden][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IInkLineInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9C1C5AD6-F22F-4DE4-B453-A2CC482E7C33")
    IInkLineInfo : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetFormat( 
            INKMETRIC *pim) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetFormat( 
            INKMETRIC *pim) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetInkExtent( 
            INKMETRIC *pim,
            UINT *pnWidth) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetCandidate( 
            UINT nCandidateNum,
            LPWSTR pwcRecogWord,
            UINT *pcwcRecogWord,
            DWORD dwFlags) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetCandidate( 
            UINT nCandidateNum,
            LPWSTR strRecogWord) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Recognize( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkLineInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkLineInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkLineInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkLineInfo * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetFormat )( 
            IInkLineInfo * This,
            INKMETRIC *pim);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFormat )( 
            IInkLineInfo * This,
            INKMETRIC *pim);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetInkExtent )( 
            IInkLineInfo * This,
            INKMETRIC *pim,
            UINT *pnWidth);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCandidate )( 
            IInkLineInfo * This,
            UINT nCandidateNum,
            LPWSTR pwcRecogWord,
            UINT *pcwcRecogWord,
            DWORD dwFlags);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCandidate )( 
            IInkLineInfo * This,
            UINT nCandidateNum,
            LPWSTR strRecogWord);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Recognize )( 
            IInkLineInfo * This);
        
        END_INTERFACE
    } IInkLineInfoVtbl;

    interface IInkLineInfo
    {
        CONST_VTBL struct IInkLineInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkLineInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkLineInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkLineInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkLineInfo_SetFormat(This,pim)	\
    (This)->lpVtbl -> SetFormat(This,pim)

#define IInkLineInfo_GetFormat(This,pim)	\
    (This)->lpVtbl -> GetFormat(This,pim)

#define IInkLineInfo_GetInkExtent(This,pim,pnWidth)	\
    (This)->lpVtbl -> GetInkExtent(This,pim,pnWidth)

#define IInkLineInfo_GetCandidate(This,nCandidateNum,pwcRecogWord,pcwcRecogWord,dwFlags)	\
    (This)->lpVtbl -> GetCandidate(This,nCandidateNum,pwcRecogWord,pcwcRecogWord,dwFlags)

#define IInkLineInfo_SetCandidate(This,nCandidateNum,strRecogWord)	\
    (This)->lpVtbl -> SetCandidate(This,nCandidateNum,strRecogWord)

#define IInkLineInfo_Recognize(This)	\
    (This)->lpVtbl -> Recognize(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IInkLineInfo_SetFormat_Proxy( 
    IInkLineInfo * This,
    INKMETRIC *pim);


void __RPC_STUB IInkLineInfo_SetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IInkLineInfo_GetFormat_Proxy( 
    IInkLineInfo * This,
    INKMETRIC *pim);


void __RPC_STUB IInkLineInfo_GetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IInkLineInfo_GetInkExtent_Proxy( 
    IInkLineInfo * This,
    INKMETRIC *pim,
    UINT *pnWidth);


void __RPC_STUB IInkLineInfo_GetInkExtent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IInkLineInfo_GetCandidate_Proxy( 
    IInkLineInfo * This,
    UINT nCandidateNum,
    LPWSTR pwcRecogWord,
    UINT *pcwcRecogWord,
    DWORD dwFlags);


void __RPC_STUB IInkLineInfo_GetCandidate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IInkLineInfo_SetCandidate_Proxy( 
    IInkLineInfo * This,
    UINT nCandidateNum,
    LPWSTR strRecogWord);


void __RPC_STUB IInkLineInfo_SetCandidate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IInkLineInfo_Recognize_Proxy( 
    IInkLineInfo * This);


void __RPC_STUB IInkLineInfo_Recognize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkLineInfo_INTERFACE_DEFINED__ */


#ifndef __ISketchInk_INTERFACE_DEFINED__
#define __ISketchInk_INTERFACE_DEFINED__

/* interface ISketchInk */
/* [unique][hidden][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISketchInk;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4563688-98EB-4646-B279-44DA14D45748")
    ISketchInk : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ISketchInkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISketchInk * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISketchInk * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISketchInk * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISketchInk * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISketchInk * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISketchInk * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISketchInk * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } ISketchInkVtbl;

    interface ISketchInk
    {
        CONST_VTBL struct ISketchInkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISketchInk_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISketchInk_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISketchInk_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISketchInk_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISketchInk_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISketchInk_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISketchInk_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISketchInk_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Ink;

#ifdef __cplusplus

class DECLSPEC_UUID("13DE4A42-8D21-4C8E-BF9C-8F69CB068FCA")
Ink;
#endif

EXTERN_C const CLSID CLSID_SketchInk;

#ifdef __cplusplus

class DECLSPEC_UUID("F0291081-E87C-4E07-97DA-A0A03761E586")
SketchInk;
#endif
#endif /* __MSINKAUTLib_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_msinkaut_0297 */
/* [local] */ 

#endif /* of #define _MSINKAUT_IDL_H_*/


extern RPC_IF_HANDLE __MIDL_itf_msinkaut_0297_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_msinkaut_0297_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


