// ?xfer@GameClient@@MAEXPAVXfer@@@Z
// partial score=0.2498 date=2026-09-28
// cl: /Iinputs/reference/shims/gameclientxfer /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// ?xfer@GameClient@@MAEXPAVXfer@@@Z
// partial 2026-09-28 opus-5.5: 1376/1361 B, 991 differing bytes, shape 0.521
// (prior 1373 B / 999, shape 0.508). Structural fix over the prior bank: the
// briefing list + camera-yaw block is guarded by Xfer slot 3 (+0x0C, retail
// +0x176), and only the camera yaw is version-gated. Residue: retail keeps
// the incoming Snapshot-subobject this in EBP (lea edi,[ebp-8] per GameClient
// use) where ours rebases once (add ebp,-8); retail lays the load loop and the
// throw blocks out after the epilogue. Inverting the save/load test is worse.
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: GameClient.cpp ////////////////////////////////////////////////////
// Implementation of GameClient singleton
// Author: Michael S. Booth, March 2001
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "GameClient/GameClient.h"
#include "Common/MapObject.h"
#include "Common/NameKeyGenerator.h"

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/ActionManager.h"
#include "Common/GameEngine.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "Common/GameLOD.h"
#include "GameClient/Anim2D.h"
#include "GameClient/CampaignManager.h"
#include "GameClient/ChallengeGenerals.h"
#include "GameClient/CommandXlat.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Diplomacy.h"
#include "GameClient/Display.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/Drawable.h"
#include "GameClient/DrawGroupInfo.h"
#include "GameClient/Eva.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GlobalLanguage.h"
#include "GameClient/GraphDraw.h"
#include "GameClient/GUICommandTranslator.h"
#include "GameClient/HeaderTemplate.h"
#include "GameClient/HintSpy.h"
#include "GameClient/HotKey.h"
#include "GameClient/IMEManager.h"
#include "GameClient/InGameUI.h"
#include "GameClient/Keyboard.h"
#include "GameClient/LanguageFilter.h"
#include "GameClient/LookAtXlat.h"
#include "GameClient/MetaEvent.h"
#include "GameClient/Mouse.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/PlaceEventTranslator.h"
#include "GameClient/RayEffect.h"
#include "GameClient/SelectionXlat.h"
#include "GameClient/Shell.h"
#include "GameClient/Snow.h"
#include "GameClient/TerrainVisual.h"
#include "GameClient/View.h"
#include "GameClient/VideoPlayer.h"
#include "GameClient/WindowXlat.h"
#include "GameLogic/FPUControl.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/GhostObject.h"
#include "GameLogic/Object.h"
#include "GameLogic/ScriptEngine.h"		// For TheScriptEngine - jkmcd
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

GameClient::DrawableTOCEntry *GameClient::findTOCEntryById( UnsignedShort id )
{

	DrawableTOCList &retailTOC = *(DrawableTOCList *)((char *)this + 0xf0);
	for( DrawableTOCListIterator it = retailTOC.begin(); it != retailTOC.end(); ++it )
		if( (*it).id == id )
			return &(*it);

	return NULL;

}  // end findTOCEntryById

static Bool shouldSaveDrawable(const Drawable* draw)
{
	if ((*(const unsigned char *)((const char *)draw + 0x110) & 0x10) != 0)
	{
		if (*(Object *const *)((const char *)draw + 0xfc) == NULL)
		{
			return false;
		}
		else
		{
			DEBUG_CRASH(("You should not ever set DRAWABLE_STATUS_NO_SAVE for a Drawable with an object. (%s)\n",draw->getTemplate()->getName().str()));
		}
	}
	return true;
}


class RetailXferView { public:
	virtual void slot0();
	virtual bool IsLoading();
	virtual bool IsStoring();
	virtual bool slot3();
	virtual bool IsLightCRC();
	virtual int beginBlock(const char *);
	virtual void endBlock();
	virtual void skipBlock();
	virtual void slot8();
	virtual void slot9();
	virtual void Version(unsigned char *);
	virtual void slot11();
	virtual void Snapshot(Drawable *);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void UnicodeStringValue(UnicodeString *);
	virtual void AsciiStringValue(AsciiString *);
	virtual void Real(float *);
	virtual void slot28();
	virtual void UnsignedInt(unsigned int *);
	virtual void Int(int *);
	virtual void UnsignedShort(unsigned short *);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void Bool(bool *);
};
void UpdateDiplomacyBriefingText(const UnicodeString &, bool);
void UpdateDiplomacyBriefingText(const AsciiString &, bool);
class RetailGameClientView { public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual bool slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void AsciiStringValue(AsciiString *);
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual Drawable *getDrawableList();
};
static const ThingTemplate *retailTemplate(const Drawable *draw)
{
	const ThingTemplate *tmpl = *(ThingTemplate *const *)((const char *)draw + 4);
	if (tmpl == 0) return 0;
	const Overridable *next = *(Overridable *const *)((const char *)tmpl + 4);
	if (next != 0) return (const ThingTemplate *)next->getFinalOverride();
	return tmpl;
}
static const AsciiString &retailThingName(const ThingTemplate *tmpl)
{
	return *(const AsciiString *)((const char *)tmpl + 0x20);
}
static const AsciiString &retailTemplateName(const Drawable *draw)
{
	return retailThingName(retailTemplate(draw));
}
class MidVirtualSlot90Receiver;
void Rva0010C3C0(MidVirtualSlot90Receiver *, void *);
class BfmeThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
class BFMEThingFactory { public: Drawable *newDrawable(const ThingTemplate *, DrawableStatus, int); };
extern StaticNameKey CameraYawAngleKey;
inline UnicodeString::UnicodeString() : m_text(0) {}
inline UnicodeString::UnicodeString(const UnicodeString &o)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&o);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
struct BfmeXferException { char *text; int tag; };
extern "C" BfmeXferException *__cdecl bfmeFormatText(BfmeXferException *, int, const char *, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
void GameClient::xfer( Xfer *xfer )
{
	RetailXferView *view = reinterpret_cast<RetailXferView *>(xfer);
	if (view->IsLightCRC()) return;

	// version
	unsigned char version[2] = { 1, 2 };
	view->Version( version );

	// client frame number
	view->UnsignedInt( &m_frame );

	//
	// note that we do not do the id counter here, we did it in the game state block because
	// it's important to do that part very early in the load process
	//
	// !!!DON'T DO THIS!!! ----> xfer->xferDrawableID( &m_nextDrawableID ); <---- !!!DON'T DO THIS!!! 

	//
	// xfer a table of contents that contain thing template and indentifier pairs.  this
	// table of contents is good for this save file only as unique numbers are only
	// generated and stored for the actual things that are on this map
	//
	xferDrawableTOC( xfer );

	// drawable count
	Drawable *draw;
	UnsignedShort drawableCount = 0;
	for( draw = reinterpret_cast<RetailGameClientView *>(this)->getDrawableList(); draw; draw = *(Drawable **)((char *)draw + 0x104) )
	{
		if (view->IsStoring() && !shouldSaveDrawable(draw))
			continue;
		drawableCount++;
	}
	view->UnsignedShort( &drawableCount );

	// drawable data
	DrawableTOCEntry *tocEntry;
	ObjectID objectID;
	if( view->IsStoring() )
	{
	
		// iterate all drawables
		for( draw = reinterpret_cast<RetailGameClientView *>(this)->getDrawableList(); draw; draw = *(Drawable **)((char *)draw + 0x104) )
		{
			if (!shouldSaveDrawable(draw))
				continue;

			// get TOC entry for this drawable
			tocEntry = findTOCEntryByName( retailTemplateName(draw) );
			if( tocEntry == NULL )
			{

				DEBUG_CRASH(( "GameClient::xfer - Drawable TOC entry not found for '%s'\n", retailTemplateName(draw).str() ));
				BfmeXferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (void *)0x011DFE5C);

			}  // end if

			// xfer toc id entry
			view->UnsignedShort( &tocEntry->id );

			// begin data block
			view->beginBlock("Drawable");

			// write the object ID this drawable is attached to
			objectID = *(Object **)((char *)draw + 0xfc) ? (*(Object **)((char *)draw + 0xfc))->getID() : INVALID_ID;
			Rva0010C3C0( (MidVirtualSlot90Receiver *)xfer, &objectID );

			// write snapshot data
			view->Snapshot( draw );

			// end data block
			view->endBlock();

		}  // end for, draw

	}  // end if, save
	else
	{
		UnsignedShort tocID;
		const ThingTemplate *thingTemplate;
		Int dataSize;

		// read all entries
		for( UnsignedShort i = 0; i < drawableCount; ++i )
		{

			// read toc id entry
			view->UnsignedShort( &tocID );

			// find TOC entry with this identifier
			tocEntry = findTOCEntryById( tocID );
			if( tocEntry == NULL )
			{

				DEBUG_CRASH(( "GameClient::xfer - No TOC entry match for id '%d'\n", tocID ));
				BfmeXferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (void *)0x011DFE5C);

			}  // end if

			// read data block size
			dataSize = view->beginBlock("Drawable");

			// find matching thing template
			thingTemplate = ((BfmeThingFactory *)TheThingFactory)->findTemplate( tocEntry->name );
			if( thingTemplate == NULL )
			{

				DEBUG_CRASH(( "GameClient::xfer - Unrecognized thing template '%s', skipping.  ENGINEERS - Are you *sure* it's OK to be ignoring this object from the save file???  Think hard about it!\n",
											tocEntry->name.str() ));
				view->skipBlock();
				continue;

			}  // end if

			// read the object ID this drawable is attached to (if any)
			Rva0010C3C0( (MidVirtualSlot90Receiver *)xfer, &objectID );

			//
			// if we have an attached object ID, we won't create a new drawable, we'll use the
			// one that has been created and attached to the object already
			//
			if( objectID != INVALID_ID )
			{
				Object *object = TheGameLogic->findObjectByID( objectID );

				// sanity
				if( object == NULL )
				{

					DEBUG_CRASH(( "GameClient::xfer - Cannot find object '%d' that is supposed to be attached to this drawable '%s'\n",
												objectID, retailThingName(thingTemplate).str() ));
					BfmeXferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (void *)0x011DFE5C);

				}  // end if

				// get the drawable from the object
				draw = object->getDrawable();
				if( draw == NULL )
				{

					DEBUG_CRASH(( "GameClient::xfer - There is no drawable attached to the object '%s' (%d) and there should be\n",
												object->getTemplate()->getName().str(), object->getID() ));
					BfmeXferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (void *)0x011DFE5C);

				}  // end if

				// srj sez: some objects (eg, diguised bombtrucks) may have an "abnormal" drawable. so check.
				//
				// note carefully: we do NOT want to use isEquivalentTo() here, because different object reskins
				// SHOULD count as different templates for our purposes here (which are purely visual). however, we
				// do need to compare getFinalOverride, because retailTemplate(draw) is always gonna return the final
				// override, while TheThingFactory->findTemplate does not.
				//
				const ThingTemplate* drawTemplate = retailTemplate(draw);
				if (drawTemplate->getFinalOverride() != thingTemplate->getFinalOverride())
				{
					TheGameClient->destroyDrawable( draw );
					draw = ((BFMEThingFactory *)TheThingFactory)->newDrawable( thingTemplate, DRAWABLE_STATUS_NONE, -1 );
					TheGameLogic->bindObjectAndDrawable(object, draw);
				}

			}  // end if
			else
			{

				//
				// there was no object attached to this drawable when we saved, we need to create a
				// whole brand new drawable now
				//
				draw = ((BFMEThingFactory *)TheThingFactory)->newDrawable( thingTemplate, DRAWABLE_STATUS_NONE, -1 );
				
				// sanity
				if( draw == NULL )
				{

					DEBUG_CRASH(( "GameClient::xfer - Unable to create drawable for '%s'\n",
												retailThingName(thingTemplate).str() ));
					BfmeXferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (void *)0x011DFE5C);

				}  // end if

			}  // end else

			// xfer the drawable data
			view->Snapshot( draw );

			// end block (not necessary since this is a no-op but symettrically nice)
			view->endBlock();

		}  // end for, i

	}  // end else, load
	
	// xfer the in-game mission briefing history list
	if (!view->slot3())
	{
		if( view->IsStoring() )
		{
			BriefingList *bList = GetBriefingTextList();
			Int numEntries = bList->size();
			view->Int(&numEntries);
			DEBUG_LOG(("Saving %d briefing lines\n", numEntries));
			for (BriefingList::const_iterator bIt = bList->begin(); bIt != bList->end(); ++bIt)
			{
				UnicodeString tempStr = *bIt;
				DEBUG_LOG(("'%s'\n", tempStr.str()));
				view->UnicodeStringValue(&tempStr);
			}
		}
		else // XFER_LOAD
		{
			Int numEntries = 0;
			view->Int(&numEntries);
			DEBUG_LOG(("Loading %d briefing lines\n", numEntries));
			UpdateDiplomacyBriefingText(AsciiString::TheEmptyString, TRUE); // clear out briefing list first
			while (numEntries-- > 0)
			{
				UnicodeString tempStr;
				view->UnicodeStringValue(&tempStr);
				DEBUG_LOG(("'%s'\n", tempStr.str()));
				UpdateDiplomacyBriefingText(tempStr, FALSE);
			}
		}
		if (version[1] >= 2)
		{
			Bool hasYaw = false;
			Real yaw = MapObject::TheWorldDict.getReal(CameraYawAngleKey.key(), &hasYaw);
			view->Bool(&hasYaw);
			view->Real(&yaw);
			if (hasYaw && view->IsLoading())
				MapObject::TheWorldDict.setReal(CameraYawAngleKey.key(), yaw);
		}
	}

	Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, (char *)this + 0xb4);
	void *evaSnapshot = TheEva ? (char *)TheEva + 8 : 0;
	view->Snapshot((Drawable *)evaSnapshot);
	view->AsciiStringValue((AsciiString *)((char *)this + 0xb8));
	view->Bool((bool *)((char *)this + 0xbc));
	view->Bool((bool *)((char *)this + 0xbd));
}  // end xfer
