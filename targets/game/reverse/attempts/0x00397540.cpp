// ?logicMessageDispatcher@GameLogic@@QAEXPAVGameMessage@@PAX@Z
// partial score=0.9212086981078791 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

// FILE: GameLogicDispatch.cpp ////////////////////////////////////////////////////////////////////
// Author: Mike Booth, Colin Day
// Description: Message logic to drive the game play
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/CRCDebug.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/GlobalData.h"
#include "Common/NameKeyGenerator.h"
#include "Common/ThingFactory.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "Common/MessageStream.h"
#include "Common/MultiplayerSettings.h"
#include "Common/Recorder.h"
#include "Common/BuildAssistant.h"
#include "Common/SpecialPower.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "Common/StatsCollector.h"
#include "Common/Radar.h"

#include "GameLogic/AIPathfind.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/ObjectIter.h"
//#include "GameLogic/PartitionManager.h"
#include "GameLogic/AI.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/OpenContain.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/ScriptActions.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/VictoryConditions.h"
#include "GameLogic/Weapon.h"

#include "GameClient/CommandXlat.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/Eva.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GuiCallbacks.h"
#include "GameClient/InGameUI.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/Mouse.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/Shell.h"
#include "GameClient/Module/BeaconClientUpdate.h"
#include "GameClient/LookAtXlat.h"

#include "GameNetwork/NetworkInterface.h"


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif



static bool theBuildPlan;
static Object *thePlanSubject[64];
static int thePlanSubjectCount;

// GAP-SEAT resume note, 2026-09-28:
// Declaring the three witnessed movement-order records at function scope,
// assigning their fields only in their cases, reproduces retail's 0xAC frame.
// This is a lifetime lever, with no dummy padding. The old bank used 0x80.
// Current full extent: 12024 vs retail 12044; 5704 masked positional byte
// differences and 577 shifted relocation sites. First residue +0x53 is the
// selected-group spill at esp+0x10 vs retail esp+0x14. Not byte-exact.
// Keep the lexical-static/EH issue separate: retail has 24 unwind states,
// two initially empty, with keys 2..8 before PlaceBuilding states 9/10;
// this body still assigns the first audio guard states 0/1.
// Separate camera-position storage and split top-level declarations were
// measured and did not improve this candidate. An inline audio-event getter
// improved normalized shape slightly but made positional agreement worse;
// it is scratch only. No dispatcher source or ledger claim was changed.

// Earlier resume notes for 2026-09-27 gpt-6-astra-medium:
// Begin from this bank, not the native ZH dispatcher. Audited ABI corrections:
// AudioEventRTS has a second ObjectID=0 argument; LookAtTranslator position is
// const ICoord2D&; Eva takes message 3 plus null Coord3D; radar takes Object+0x38,
// event 0 and radius 4.0f. Case 0x40f uses command-source 2 on BOTH branches.
// All used rva-qualified thiscall declarations with an independently decoded
// ret now agree on argument cleanup. Four tail/short extents remain undecoded.
// EH has 24 retail states: 0/1 no cleanup, then seven key guards (states 2..8),
// then PlaceBuilding guard/AsciiString (9/10). Ours lacks the first two empty
// states and has PlaceBuilding first in lexical static order. Moving case 418
// below the key cases fixes guard numbering but moves physical blocks farther
// from retail; keep the original physical ordering until that is resolved.
// Frame is 0x80 vs retail 0xac. Probe full normalized shape 0.9209709286;
// code-only shape 0.972631579 excludes inline switch-table data. Neither is a
// byte-match percentage. No dispatcher source/pins/ledger were landed.
// Evidence and all finite-search variants: build/astra_seat/REPORT.md.

// Scratch-only receiver declarations. The suffix is the retail body RVA;
// no semantic identity or pin is claimed for these additional call signatures.
// Receiver is used only for direct calls, never for a presumed data layout.
struct BfmeObjectReference { Object *resolve(); };
template<class T> __forceinline T& field(const void* p, unsigned offset) {
    return *(T*)((char*)p+offset);
}
struct Dispatch397540Calls {
    Object *rva0009A510(ObjectID);
    bool rva0005C5E0();
    void rva0009B590(unsigned,int,bool,unsigned);
    bool rva001506E0();
    bool rva00151020(int,int);
    void rva00151130(int);
    void rva00150BA0(int);
    void rva00155B90(int);
    void rva00155490(int);
    void rva001563E0(Object*,int);
    void rva00156570(Object*,int);
    void rva00156380(Object*,int);
    void rva001562C0(Object*,int);
    void rva00156320(Object*,int);
    void rva001565D0(const Coord3D*,int);
    void rva00156840(const Coord3D*,int,int);
    void rva0015A130(Object*,int);
    char rva001518F0(Player*);
    void rva00387A50();
    void rva00396B00(bool,bool);
    void rva003C1AD0(bool);
    void rva003838D0(int);
    void rva003838E0(int);
    void rva00383980();
    void rva003855F0();
    void *rva00087A80();
    void *rva001BF570();
    void rva001C9B80(int);
    void rva00240780(Object*,int);
    void rva00154330(Object*,int);
    void rva0015A030(const Coord3D*,int,int);
    const UpgradeTemplate *rva0010A950(NameKeyType);
    const ThingTemplate *rva00137E80(const AsciiString&);
    Object *rva00138520(const ThingTemplate*,Team*,const void*,int);
    void rva00603520();
    void rva00411BB0();
    void rva00418880(const UnicodeString&);
    bool rva004233A0(int,const Coord3D*);
    void rva0026EE30();
    void rva000D2B70(int,GameMessage*);
    void rva000D2A60(int,GameMessage*);
    Object *rva001AA5B0(const Coord3D*);
    void rva00411F80(bool);
    void rva00155DA0(bool,Object*,int,int);
    void rva000CDD50(int,const ThingTemplate**,bool,int*,bool);
    bool rva005B53D0();
    void rva005B5420(const ICoord2D&);
    void rva00108140(const Coord3D*,int,float);
    void rva00150D80(void*,int,void*);
    void rva00156B10();
    void rva00150B60(int);
    void rva001510F0(int);
    void rva001501F0(bool);
    void rva00151560(void*,void*);
    bool rva000C99D0(const ThingTemplate*);
    void rva00156A90(Object*,int);
    void rva00150C90(unsigned,const Coord3D*,Object*,unsigned,int);
    void rva00150BE0(unsigned,unsigned,int);
    void rva00152110(unsigned,Object*,unsigned,int);
    void rva00151170(const UpgradeTemplate*,const ThingTemplate*);
    void rva00151230(const UpgradeTemplate*);
    void rva00159AD0(void*,int);
    
    void rva00150ED0(Object*,int);
    void rva00154230();
    void rva001C89E0(Player*);
    void rva00382E30(Object*,bool,unsigned,bool);
    void rva00382F50(Object*,unsigned,bool);
    void rva000D48E0(Player*,bool);
    void rva0006C3A0();
    void *rva000D4490();
    void *rva001BFE20();
    void *rva001BF670();
    bool rva001BE570();
    void *rva001BEE60(NameKeyType);
    void *rva001C39A0();
    void *rva004A0340(void*);
    void *rva0049C590(int);
    int rva000C4640();
    void rva001EDAD0(void*);
    bool rva0036E420(bool);
    bool rva0036BA40();
    bool rva00371550(Player*,void*);
    bool rva0036F8D0(Player*);
    bool rva0036BA60(Player*,const ThingTemplate*);
    void rva00376B00(bool,const ThingTemplate*);
    void rva00376C70();
    bool rva000C4D40(int);
    bool rva000A2CF0(int);
    bool rva000D3F10(int);
    void rva000D3EB0(int,bool);
    void rva00162CD0(int);
    void rva001C30F0(int,int);
    void rva001CE3F0();
    void rva000EA5A0(Object*,int);
    void rva000C8730(unsigned,bool);
    void *rva001BEF20();
    void *rva001CB020(bool);
    void rva001CE940(int);
    void rva001C9AC0(int);
    void rva001CE830(int);
    void rva001C9A10(int);
    bool rva00278830();
    bool rva001CC880(int);
    void rva000D87E0(int);
    void rva001CE6F0(unsigned);
    void rva001B33E0(bool);
    void rva000F2150(int);
    void rva000F20F0(int,bool);
    void rva0038B430(unsigned,int,unsigned,GameMessage*,bool,unsigned);
    void rva001C5800();
    void rva001C7E60(int);
    void rva00396830(float,float,float,float,float,float,float);
};
__forceinline Dispatch397540Calls* X(const void* p) { return (Dispatch397540Calls*)p; }
struct Dispatch397540Move { const Coord3D *position; bool append; void *rva_8; void *rva_c; };
void Rva00397350GlobalRallyPointFeedback(Object*,const Coord3D&);
int Rva00396D40(void*,const Coord3D*,int,int);
bool isValidBeaconPosition_001A40C0(Coord3D*);
// Only the witnessed slot is callable in each interface view. Distinct
// dummy parameter types append slots without overriding a base virtual.
template<unsigned N> struct DispatchSlotToken {};
template<unsigned N> struct DispatchSlotPadding : DispatchSlotPadding<N-1> {
    virtual void reserved(DispatchSlotToken<N>*);
};
template<> struct DispatchSlotPadding<0> {};
template<unsigned Slot,class R> struct VDispatch0 : DispatchSlotPadding<Slot/4> { virtual R invoke(); };
template<unsigned Slot,class R> __forceinline R v0(void *p) { return ((VDispatch0<Slot,R>*)p)->invoke(); }
template<unsigned Slot,class R,class A> struct VDispatch1 : DispatchSlotPadding<Slot/4> { virtual R invoke(A a); };
template<unsigned Slot,class R,class A> __forceinline R v1(void *p,A a) { return ((VDispatch1<Slot,R,A>*)p)->invoke(a); }
template<unsigned Slot,class R,class A,class B> struct VDispatch2 : DispatchSlotPadding<Slot/4> { virtual R invoke(A a,B b); };
template<unsigned Slot,class R,class A,class B> __forceinline R v2(void *p,A a,B b) { return ((VDispatch2<Slot,R,A,B>*)p)->invoke(a,b); }
template<unsigned Slot,class R,class A,class B,class C> struct VDispatch3 : DispatchSlotPadding<Slot/4> { virtual R invoke(A a,B b,C c); };
template<unsigned Slot,class R,class A,class B,class C> __forceinline R v3(void *p,A a,B b,C c) { return ((VDispatch3<Slot,R,A,B,C>*)p)->invoke(a,b,c); }
template<unsigned Slot,class R,class A,class B,class C,class D> struct VDispatch4 : DispatchSlotPadding<Slot/4> { virtual R invoke(A a,B b,C c,D d); };
template<unsigned Slot,class R,class A,class B,class C,class D> __forceinline R v4(void *p,A a,B b,C c,D d) { return ((VDispatch4<Slot,R,A,B,C,D>*)p)->invoke(a,b,c,d); }
template<unsigned Slot,class R,class A,class B,class C,class D,class E> struct VDispatch5 : DispatchSlotPadding<Slot/4> { virtual R invoke(A a,B b,C c,D d,E e); };
template<unsigned Slot,class R,class A,class B,class C,class D,class E> __forceinline R v5(void *p,A a,B b,C c,D d,E e) { return ((VDispatch5<Slot,R,A,B,C,D,E>*)p)->invoke(a,b,c,d,e); }
struct Dispatch397540View {
    bool rva_0; float rva_4,rva_8,rva_c,rva_10,rva_14,rva_18,rva_1c;
    __forceinline Dispatch397540View() { rva_0=false; rva_4=0; rva_8=0; rva_c=0; rva_1c=0; rva_18=0; rva_14=0; rva_10=0; }
};

template<unsigned Slot> struct Rva397540Message : DispatchSlotPadding<Slot/4> { virtual void __cdecl invoke(UnicodeString text,...); };
__forceinline const wchar_t* dispatchUnicodeText(const UnicodeString &s) {
    void *p=field<void*>(&s,0); return p?(const wchar_t*)((char*)p+8):L"";
}
void GameLogic::logicMessageDispatcher( GameMessage *msg, void *userData )
{
    Coord3D dispatchPosition;
    Dispatch397540Move order430,order441,order431;

	Player *thisPlayer = ThePlayerList->getNthPlayer( msg->getPlayerIndex() );
	DEBUG_ASSERTCRASH( thisPlayer, ("logicMessageDispatcher: Processing message from unknown player (player index '%d')\n", 
																	msg->getPlayerIndex()) );
	AIGroup *currentlySelectedGroup = NULL;
	if (field<int>(this, 0x10c) != 8 && field<int>(this, 0x10c) != 4)
	{
		if (msg->getType() >= GameMessage::MSG_BEGIN_NETWORK_MESSAGES && msg->getType() <= GameMessage::MSG_END_NETWORK_MESSAGES)
		{
			if (msg->getType() != 0x449 && msg->getType() != 0x446)
			{
				currentlySelectedGroup = TheAI->createGroup(); 
				CRCGEN_LOG(( "Creating AIGroup %d in GameLogic::logicMessageDispatcher()\n", (currentlySelectedGroup)?currentlySelectedGroup->getID():0 ));
				thisPlayer->getCurrentSelectionAsAIGroup(currentlySelectedGroup);
				if (X(currentlySelectedGroup)->rva001506E0())
				{
					TheAI->destroyGroup(currentlySelectedGroup);
					currentlySelectedGroup = NULL;
				}
				if (currentlySelectedGroup) {
                    if (msg->getType() == 0x41e) {
                        if (X(currentlySelectedGroup)->rva001518F0(thisPlayer)) currentlySelectedGroup = NULL;
                    } else if (msg->getType() != 0x41c && currentlySelectedGroup->removeAnyObjectsNotOwnedByPlayer(thisPlayer))
                        currentlySelectedGroup = NULL;
                }
				if(TheStatsCollector)
					TheStatsCollector->collectMsgStats(msg);
			}
		}
	}
	int msgType = msg->getType();
	switch( msgType )
	{
case 0x1f: {
    const GameMessageArgumentType *argument=msg->getArgument(0); X(TheScriptEngine)->rva003C1AD0(argument->boolean); break;
}
case 0x1e: {
    int mode=msg->getArgument(0)->integer;
    int rank=0; GameDifficulty difficulty=DIFFICULTY_NORMAL;
    if (mode==4 && field<int>(TheGameLogic,0x10c)==4) break;
    if (field<unsigned char>(msg,0x18)>=2) difficulty=(GameDifficulty)msg->getArgument(1)->integer;
    if (field<unsigned char>(msg,0x18)>=3) rank=msg->getArgument(2)->integer;
    if (field<unsigned char>(msg,0x18)>=4) {
        int fps=msg->getArgument(3)->integer;
        if (fps<1 || fps>1000) fps=field<int>(TheGlobalData,0x24);
        v1<0x2c,void>(TheGameEngine,fps);
        field<bool>(TheGlobalData,0x1e)=true;
    }
    prepareNewGame(mode,difficulty,rank);
    startNewGame(false);
    break;
}
case 0x1d: {
    if (currentlySelectedGroup) TheAI->destroyGroup(currentlySelectedGroup);
    X(this)->rva00387A50();
    GameLogic *logic=TheGameLogic;
    bool shell=false;
    if(field<int>(logic,0x10c)==2 || X(logic)->rva0005C5E0()) shell=true;
    X(logic)->rva00396B00(shell,true);
    return;
}
case 0x70:
		{
			DEBUG_LOG(("META: begin path build\n"));
			DEBUG_ASSERTCRASH(!theBuildPlan, ("mismatched theBuildPlan"));
			if (theBuildPlan == false)
			{
				theBuildPlan = true;
				thePlanSubjectCount = 0;
			}
			break;
		}
case 0x71:
		{
			DEBUG_LOG(("META: end path build\n"));
			DEBUG_ASSERTCRASH(theBuildPlan, ("mismatched theBuildPlan"));
			for( int i=0; i<thePlanSubjectCount; i++ )
			{
				AIUpdateInterface *ai = field<AIUpdateInterface*>(thePlanSubject[i],0x204);
				if (ai)
					X(ai)->rva0026EE30();
			}
			theBuildPlan = false;
			thePlanSubjectCount = 0;
			break;
		}
case 0x3e9:
case 0x3ea: {
    bool clear=msg->getArgument(0)->boolean;
    if (!thisPlayer) break;
    if (clear) {
        AIGroup *group=TheAI->createGroup();
        thisPlayer->getCurrentSelectionAsAIGroup(group);
        if (group) {
            const VecObjectID& ids=group->getAllIDs();
            for(VecObjectID::const_iterator it=ids.begin();it!=ids.end();++it) {
                Object *object=findObjectByID(*it);
                if (object) X(object)->rva001C89E0(thisPlayer);
            }
            thisPlayer->setCurrentlySelectedAIGroup(NULL);
        }
    }
    bool first=true;
    for (int i=1;i<field<unsigned char>(msg,0x18);++i) {
        Object *object=TheGameLogic->findObjectByID(msg->getArgument(i)->objectID);
        if (object) { X(TheGameLogic)->rva00382E30(object,clear && first,1u<<field<int>(thisPlayer,0x24),false); first=false; }
    }
    break;
}
case 0x3ec: {
    Player *player=ThePlayerList->getNthPlayer(msg->getPlayerIndex());
    if (player) for (int i=0;i<field<unsigned char>(msg,0x18);++i) {
        ObjectID id=msg->getArgument(i)->objectID;
        GameLogic *logic=TheGameLogic;
        Object *object=logic->findObjectByID(id);
        if (object) X(logic)->rva00382F50(object,1u<<field<int>(player,0x24),false);
    }
    break;
}
case 0x3eb: {
    if (!thisPlayer) break;
    AIGroup *group=TheAI->createGroup();
    thisPlayer->getCurrentSelectionAsAIGroup(group);
    if (group) {
        const VecObjectID& ids=group->getAllIDs();
        for(VecObjectID::const_iterator it=ids.begin();it!=ids.end();++it) {
            Object *object=findObjectByID(*it);
            if (object) X(object)->rva001C89E0(thisPlayer);
        }
        thisPlayer->setCurrentlySelectedAIGroup(NULL);
    }
    break;
}
case 0x3ed:
case 0x3ee:
case 0x3ef:
case 0x3f0:
case 0x3f1:
case 0x3f2:
case 0x3f3:
case 0x3f4:
case 0x3f5:
case 0x3f6:
		{
			Int playerIndex = msg->getPlayerIndex();
			Player *player = ThePlayerList->getNthPlayer(playerIndex);
			DEBUG_ASSERTCRASH(player != NULL, ("Could not find player for create team message"));
			if (player == NULL)
			{
				break;
			}
			player->processCreateTeamGameMessage(msg->getType() - 0x3ed, msg);
			break;
		}
case 0x3f7:
case 0x3f8:
case 0x3f9:
case 0x3fa:
case 0x3fb:
case 0x3fc:
case 0x3fd:
case 0x3fe:
case 0x3ff:
case 0x400:
		{
			Int playerIndex = msg->getPlayerIndex();
			Player *player = ThePlayerList->getNthPlayer(playerIndex);
			DEBUG_ASSERTCRASH(player != NULL, ("Could not find player for select team message"));
			if (player == NULL)
			{
				break;
			}
			X(player)->rva000D2A60(msg->getType() - 0x3f7, msg);
			break;
		}
case 0x401:
case 0x402:
case 0x403:
case 0x404:
case 0x405:
case 0x406:
case 0x407:
case 0x408:
case 0x409:
case 0x40a:
		{
			Int playerIndex = msg->getPlayerIndex();
			Player *player = ThePlayerList->getNthPlayer(playerIndex);
			DEBUG_ASSERTCRASH(player != NULL, ("Could not find player for add team message"));
			if (player == NULL)
			{
				break;
			}
			X(player)->rva000D2B70(msg->getType() - 0x401, msg);
			break;
		}
case 0x412: {
    Object *object=TheGameLogic->findObjectByID(msg->getArgument(0)->objectID);
    dispatchPosition=msg->getArgument(1)->location;
    bool feedback=msg->getArgument(2)->boolean;
    Object *target=TheGameLogic->findObjectByID(msg->getArgument(3)->objectID);
    if (object) {
        if (feedback && !target) Rva00397350GlobalRallyPointFeedback(object,dispatchPosition);
        else Rva00396D40(object,&dispatchPosition,1,0);
    }
    break;
}
case 0x40c:
		{
			WeaponSlotType weaponSlot = (WeaponSlotType)msg->getArgument( 0 )->integer;
			Int maxShotsToFire = msg->getArgument( 1 )->integer;
			if( currentlySelectedGroup && X(currentlySelectedGroup)->rva00151020( weaponSlot, LOCKED_TEMPORARILY ))
			{
				currentlySelectedGroup->groupAttackPosition( NULL, maxShotsToFire, CMD_FROM_PLAYER );
			}
			break;
		}
case 0x40e: {
    int weapon=msg->getArgument(0)->integer;
    Object *target=TheGameLogic->findObjectByID(msg->getArgument(1)->objectID);
    int shots=msg->getArgument(2)->integer;
    if (!target) break;
    if (!currentlySelectedGroup) return;
    if (X(currentlySelectedGroup)->rva00151020(weapon,1)) {
        X(currentlySelectedGroup)->rva00155B90(2);
        X(currentlySelectedGroup)->rva00151020(weapon,1);
        X(currentlySelectedGroup)->rva00155DA0(false,target,shots,0);
    }
    break;
}
case 0x40d:
		{
			WeaponSlotType weaponSlot = (WeaponSlotType)msg->getArgument( 0 )->integer;
			dispatchPosition = msg->getArgument( 1 )->location;
			Int maxShotsToFire = msg->getArgument( 2 )->integer;
			if (!currentlySelectedGroup) return; 
			{
				if (X(currentlySelectedGroup)->rva00151020( weaponSlot, LOCKED_TEMPORARILY ))
 					currentlySelectedGroup->groupAttackPosition( &dispatchPosition, maxShotsToFire, CMD_FROM_PLAYER );
			}  
			break;
		}
case 0x40f:
		{
			UnsignedInt specialPowerID = msg->getArgument( 0 )->integer;
			UnsignedInt options = msg->getArgument( 1 )->integer;
			ObjectID sourceID = msg->getArgument(2)->objectID;
			Object* source = TheGameLogic->findObjectByID(sourceID);
			if (source != NULL)
			{
				AIGroup* theGroup = TheAI->createGroup();
				theGroup->add(source);
				X(theGroup)->rva00150BE0(specialPowerID,options,2);
				TheAI->destroyGroup(theGroup);
			}
			else
			{
				if (!currentlySelectedGroup) return; 
				{
					X(currentlySelectedGroup)->rva00150BE0(specialPowerID,options,2);
				}
			}
			break;
		}
case 0x410: {
    unsigned power=msg->getArgument(0)->integer;
    dispatchPosition=msg->getArgument(1)->location;
    Object *obstacle=TheGameLogic->findObjectByID(msg->getArgument(2)->objectID);
    unsigned options=msg->getArgument(3)->integer;
    Object *source=TheGameLogic->findObjectByID(msg->getArgument(4)->objectID);
    if (source) {
        AIGroup *group=TheAI->createGroup(); group->add(source);
        X(group)->rva00150C90(power,&dispatchPosition,obstacle,options,2);
        TheAI->destroyGroup(group);
    } else {
        if (!currentlySelectedGroup) return;
        X(currentlySelectedGroup)->rva00150C90(power,&dispatchPosition,obstacle,options,0);
    }
    break;
}
case 0x411: {
    unsigned power=msg->getArgument(0)->integer;
    Object *target=TheGameLogic->findObjectByID(msg->getArgument(1)->objectID);
    if (!target) break;
    unsigned options=msg->getArgument(2)->integer;
    Object *source=TheGameLogic->findObjectByID(msg->getArgument(3)->objectID);
    dispatchPosition.x=0; dispatchPosition.y=0; dispatchPosition.z=0;
    bool location=false;
    if (field<int>(target,0x74)>=99999996 && field<int>(target,0x74)<=99999999) {
        dispatchPosition=msg->getArgument(4)->location; location=true;
    }
    if (source) {
        AIGroup *group=TheAI->createGroup(); group->add(source);
        if (location) X(group)->rva00150C90(power,&dispatchPosition,target,options,0);
        else X(group)->rva00152110(power,target,options,0);
        TheAI->destroyGroup(group);
    } else {
        if (!currentlySelectedGroup) return;
        if (location) X(currentlySelectedGroup)->rva00150C90(power,&dispatchPosition,target,options,0);
        else X(currentlySelectedGroup)->rva00152110(power,target,options,0);
    }
    break;
}
case 0x414: {
    const UpgradeTemplate *upgrade=X(TheUpgradeCenter)->rva0010A950((NameKeyType)msg->getArgument(1)->integer);
    if (!upgrade) break;
    const ThingTemplate *what=0;
    if (msg->getArgument(2)->integer) what=TheThingFactory->findByTemplateID((unsigned short)msg->getArgument(2)->integer);
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00151170(upgrade,what); break;
}
case 0x415: {
    const UpgradeTemplate *upgrade=X(TheUpgradeCenter)->rva0010A950((NameKeyType)msg->getArgument(0)->integer);
    if (!upgrade) break;
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00151230(upgrade); break;
}
case 0x413: {
    int index=msg->getArgument(0)->integer;
    ScienceType science=(ScienceType)msg->getArgument(1)->integer;
    if (science == SCIENCE_INVALID || !thisPlayer) break;
    Player *player=ThePlayerList->getNthPlayer(index);
    if (player) player->attemptToPurchaseScience(science);
    break;
}
case 0x416: {
    Object *producer=((BfmeObjectReference*)currentlySelectedGroup)->resolve();
    void *what; int id;
    if (msg->getArgument(0)->boolean) { id=msg->getArgument(1)->integer; what=0; }
    else {
        id=-1;
        const ThingTemplate *t=TheThingFactory->findByTemplateID((unsigned short)msg->getArgument(1)->integer);
        what=t?X(t)->rva00087A80():0;
    }
    int production=msg->getArgument(2)->integer;
    bool flag=msg->getArgument(3)->boolean;
    if (producer && (what || id!=-1)) {
        void *pu=X(producer)->rva001BF570();
        if (pu) {
            void *owner=v0<8,void*>(pu);
            v5<0x1c,void>(pu,what,id,owner,production,flag);
        }
    }
    break;
}
case 0x422: {
    Object *object=TheGameLogic->findObjectByID(msg->getArgument(0)->objectID);
    if (!currentlySelectedGroup) return;
    if (object) X(currentlySelectedGroup)->rva00156A90(object,0);
    break;
}
case 0x42f: {
    dispatchPosition=msg->getArgument(0)->location;
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00151130(LOCKED_TEMPORARILY);
    X(currentlySelectedGroup)->rva0015A030(&dispatchPosition,0x7fffffff,0);
    break;
}
case 0x42b:
		{
			Object *enter = TheGameLogic->findObjectByID( msg->getArgument( 1 )->objectID );
			if( enter == NULL )
				break;
			if (!currentlySelectedGroup) return; 
			{
				X(currentlySelectedGroup)->rva00151130(LOCKED_TEMPORARILY);	
				X(currentlySelectedGroup)->rva0015A130( enter, CMD_FROM_PLAYER );
			}
			break;
		}
case 0x41c: {
    Object *exiter=TheGameLogic->findObjectByID(msg->getArgument(0)->objectID);
    Object *container=((BfmeObjectReference*)currentlySelectedGroup)->resolve();
    if (!exiter || !container || exiter->getControllingPlayer()!=thisPlayer) break;
    void *contain=field<void*>(container,0x1fc);
    if (!contain || !v1<0xd4,bool>(contain,exiter)) break;
    X(exiter)->rva001C9B80(1);
    void *ai=field<void*>(exiter,0x204);
    if (ai) {
        if (X(exiter)->rva000A2CF0(0x6c)) X((char*)ai+0x20)->rva00240780(container,0);
        else X((char*)ai+0x20)->rva00154330(container,0);
    }
    break;
}
case 0x41d:
		{
			if (!currentlySelectedGroup) return; 
			{
				X(currentlySelectedGroup)->rva00151130(LOCKED_TEMPORARILY);	
				currentlySelectedGroup->groupEvacuate( CMD_FROM_PLAYER );
			}  
			break;
		}
case 0x41e: {
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00151130(1);
    X(currentlySelectedGroup)->rva00150BA0(0);
    break;
}
case 0x427:
		{
			Object *repairDepot = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );
			if( repairDepot == NULL )
				break;
			if (!currentlySelectedGroup) return; 
				X(currentlySelectedGroup)->rva001563E0( repairDepot, CMD_FROM_PLAYER );
			break;
		}
case 0x42c:
		{
			Object *dockBuilding = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );
			if( dockBuilding == NULL )
				break;
			if (!currentlySelectedGroup) return; 
				X(currentlySelectedGroup)->rva00156570( dockBuilding, CMD_FROM_PLAYER );
			break;
		}
case 0x42d: {
    dispatchPosition=msg->getArgument(0)->location;
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva001565D0(&dispatchPosition,0); break;
}
case 0x428:
		{
			Object *healDest = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );
			if( healDest == NULL )
				break;
			if (!currentlySelectedGroup) return; 
				X(currentlySelectedGroup)->rva00156380( healDest, CMD_FROM_PLAYER );
			break;
		}
case 0x429:
		{
			Object *repairTarget = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );
			if( repairTarget == NULL )
				break;
			if (!currentlySelectedGroup) return; 
				X(currentlySelectedGroup)->rva001562C0( repairTarget, CMD_FROM_PLAYER );
			break;
		}
case 0x42a:
		{
			Object *constructTarget = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );
			if( constructTarget == NULL )
				break;
			if (!currentlySelectedGroup) return; 
				X(currentlySelectedGroup)->rva00156320( constructTarget, CMD_FROM_PLAYER );
			break;
		}
case 0x425: {
    Object *enemy=TheGameLogic->findObjectByID(msg->getArgument(0)->objectID);
    dispatchPosition=msg->getArgument(1)->location;
    if (!enemy) break;
    if (field<int>(enemy,0x74)==99999999) {
        if (!field<bool>(field<void*>(TheAI,0x14),0xb8)) break;
        enemy=X(TheTerrainLogic)->rva001AA5B0(&dispatchPosition);
        if (!enemy) break;
        if (v0<0x28,void*>(enemy)) X(v0<0x28,void*>(enemy))->rva00411F80(true);
    }
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00151130(LOCKED_TEMPORARILY);
    X(currentlySelectedGroup)->rva00155DA0(true,enemy,0x7fffffff,0);
    break;
}
case 0x426: {
    dispatchPosition=msg->getArgument(0)->location;
    if (!currentlySelectedGroup) return;
    if (!currentlySelectedGroup->isIdle()) {
        X(currentlySelectedGroup)->rva00151020(PRIMARY_WEAPON,LOCKED_TEMPORARILY);
        currentlySelectedGroup->groupAttackPosition(&dispatchPosition,NO_MAX_SHOTS_LIMIT,CMD_FROM_PLAYER);
        X(currentlySelectedGroup)->rva00151130(LOCKED_TEMPORARILY);
    } else {
        X(currentlySelectedGroup)->rva00151130(LOCKED_TEMPORARILY);
        currentlySelectedGroup->groupAttackPosition(&dispatchPosition,NO_MAX_SHOTS_LIMIT,CMD_FROM_PLAYER);
    }
    break;
}
case 0x417: {
    Object *producer=((BfmeObjectReference*)currentlySelectedGroup)->resolve();
    if (!producer || producer->getControllingPlayer()!=thisPlayer) break;
    void *pu=X(producer)->rva001BF570();
    if (!pu) return;
    if (msg->getArgument(0)->boolean) {
        int id=msg->getArgument(1)->integer;
        v1<0x2c,void>(pu,id);
    } else {
        const ThingTemplate *what=TheThingFactory->findByTemplateID((unsigned short)msg->getArgument(1)->integer);
        bool flag=msg->getArgument(2)->boolean;
        v2<0x28,void>(pu,what,flag);
    }
    break;
}
case 0x418: {
    Object *object=((BfmeObjectReference*)currentlySelectedGroup)->resolve();
    const ThingTemplate *what=TheThingFactory->findByTemplateID((unsigned short)msg->getArgument(0)->integer);
    Player *owner=object?object->getControllingPlayer():0;
    if (!what || !object || !owner || !X(owner)->rva000C99D0(what)) break;
    dispatchPosition=msg->getArgument(1)->location;
    float angle=msg->getArgument(2)->real;
    v5<0x24,void>(TheBuildAssistant,object,what,&dispatchPosition,angle,owner);
    static AudioEventRTS placeBuilding(AsciiString("PlaceBuilding"),(ObjectID)0);
    placeBuilding.setObjectID((ObjectID)field<unsigned>(object,0x74));
    v1<0x44,void>(TheAudio,&placeBuilding);
    break;
}
case 0x41a: {
    Object *building=((BfmeObjectReference*)currentlySelectedGroup)->resolve();
    if (!building || (field<unsigned char>(building,0x344)&1) || building->getControllingPlayer()!=thisPlayer) break;
    bool kind=X(building)->rva000A2CF0(0x95);
    if (kind) { if (X(building)->rva000D3F10(0x67)) break; }
    else if (!X(building)->rva000C4D40(2)) break;
    void *module=X(building)->rva001BF670();
    float refund;
    if (module && v0<0x14,bool>(module) && !v0<0x28,bool>(module)) refund=v0<0x30,float>(module);
    else refund=field<float>(building,0x258);
    unsigned amount=(unsigned)refund;
    if (amount && !X(building)->rva000C4D40(0x15)) {
        if (!thisPlayer) break;
        X((char*)thisPlayer+0x48)->rva000C8730(amount,true);
    }
    if (kind) X(building)->rva001CE3F0();
    else {
        X(building)->rva000D3EB0(0x55,true);
        X(building)->rva001C30F0(8,0);
        X(building)->rva00162CD0(0x55);
    }
    if (thisPlayer) X((char*)thisPlayer+0x348)->rva000EA5A0(building,-1);
    break;
}
case 0x41b:
		{
			if (!currentlySelectedGroup) return; 
				currentlySelectedGroup->groupSell( CMD_FROM_PLAYER );
			break;
		}
case 0x41f: {
    Object *object=TheGameLogic->findObjectByID(msg->getArgument(0)->objectID);
    if (object) {
        if (!currentlySelectedGroup) return;
        X(currentlySelectedGroup)->rva00150ED0(object,0);
    }
    break;
}
case 0x430: {
    dispatchPosition=msg->getArgument(0)->location;
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00151130(LOCKED_TEMPORARILY);
    order430.position=&dispatchPosition; order430.append=false; order430.rva_8=0; order430.rva_c=0;
    X(currentlySelectedGroup)->rva00159AD0(&order430,0);
    break;
}
case 0x439: {
    int weapon=msg->getArgument(0)->integer;
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00151130(2);
    X(currentlySelectedGroup)->rva00151020(weapon,2);
    break;
}
case 0x45b: {
    int value=msg->getArgument(0)->integer;
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva001510F0(value); break;
}
case 0x456: {
    ObjectID referenceID=msg->getArgument(0)->objectID;
    Object *reference=TheGameLogic->findObjectByID(referenceID);
    bool each=true;
    bool enabled=true;
    if(referenceID && reference) {
        each=false;
        enabled=!(field<unsigned char>(X(reference)->rva001BEF20(),3)&1);
    }
    if (!currentlySelectedGroup) return;
    const VecObjectID& ids=currentlySelectedGroup->getAllIDs();
    for (VecObjectID::const_iterator it=ids.begin();it!=ids.end();++it) {
        Object *object=findObjectByID(*it);
        if (!object) continue;
        if (reference && !object->getTemplate()->isEquivalentTo(reference->getTemplate()) &&
            (!X(object)->rva000A2CF0(0x80) || !X(reference)->rva000A2CF0(0x80))) continue;
        if (each) enabled=!(field<unsigned char>(X(object)->rva001BEF20(),3)&1);
        else if ((field<unsigned char>(X(object)->rva001BEF20(),3)&1)==enabled) continue;
        void *parent=X(object)->rva001CB020(false);
        if (enabled) {
            if (parent) X(object)->rva001CE830(0x18); else X(object)->rva001C9A10(0x18);
        } else {
            if (parent) X(object)->rva001CE940(0x18); else X(object)->rva001C9AC0(0x18);
        }
        void *ai=field<void*>(object,0x204);
        if (ai && !X(ai)->rva00278830()) {
            if (X(object)->rva001CC880(0x25)) {
                X((char*)field<void*>(object,0x204)+0x20)->rva000D87E0(2);
                X(object)->rva001CE6F0(field<unsigned>(TheGameLogic,0x3c)+5);
            }
            void *drawable=field<void*>(object,0x1ec);
            if (drawable) X(drawable)->rva001B33E0(true);
        }
    }
    break;
}
case 0x45a: {
    ObjectID referenceID=msg->getArgument(0)->objectID;
    bool each=referenceID==0;
    bool enabled=each;
    if (!each) {
        Object *reference=TheGameLogic->findObjectByID(referenceID);
        enabled=reference && !X(reference)->rva000C4D40(0x17);
    }
    if (!currentlySelectedGroup) return;
    const VecObjectID& ids=currentlySelectedGroup->getAllIDs();
    for (VecObjectID::const_iterator it=ids.begin();it!=ids.end();++it) {
        Object *object=findObjectByID(*it);
        if (!object) continue;
        if (each) enabled=!X(object)->rva000C4D40(0x17);
        else if (X(object)->rva000C4D40(0x17)==enabled) continue;
        bool kind=X(object)->rva000A2CF0(0x6c);
        if (enabled) {
            if (kind) X(object)->rva000F20F0(0x17,true); else X(object)->rva000D3EB0(0x17,true);
        } else {
            if (kind) X(object)->rva000F2150(0x17); else X(object)->rva00162CD0(0x17);
        }
    }
    break;
}
case 0x44a: {
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva001501F0(true); break;
}
case 0x461: {
    int index=msg->getArgument(0)->integer;
    bool enabled=msg->getArgument(1)->boolean;
    Player *player=ThePlayerList->getNthPlayer(index);
    if (player) field<bool>(player,0x29e)=enabled;
    break;
}
case 0x455: {
    unsigned power=msg->getArgument(0)->integer;
    unsigned options=msg->getArgument(1)->integer;
    if (thisPlayer) {
        Object *object=(Object*)X(thisPlayer)->rva000D4490();
        if (object) {
            AIGroup *group=TheAI->createGroup(); group->add(object);
            X(group)->rva00150BE0(power,options,2);
            TheAI->destroyGroup(group);
        }
    }
    break;
}
case 0x458: {
    static NameKeyType key=TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
    int selected=msg->getArgument(0)->integer;
    Object *object=TheGameLogic->findObjectByID(msg->getArgument(1)->objectID);
    if (!object) break;
    void *set=X(TheControlBar)->rva004A0340(X(object)->rva001C39A0());
    if (!set) break;
    for (int i=0;i<20;++i) {
        void *button=X(set)->rva0049C590(i);
        if (button && field<int>(button,0x10)==0x16 && field<int>(button,0x6c)==selected) {
            void *module=X(object)->rva001BEE60(key);
            if (module) X(module)->rva001EDAD0(button);
            break;
        }
    }
    break;
}
case 0x457: {
    static NameKeyType key=TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
    int selected=msg->getArgument(0)->integer;
    Object *object=TheGameLogic->findObjectByID(msg->getArgument(1)->objectID);
    if (!object) break;
    void *set=X(TheControlBar)->rva004A0340(X(object)->rva001C39A0());
    if (!set) break;
    for (int i=0;i<20;++i) {
        void *button=X(set)->rva0049C590(i);
        if (button && field<int>(button,0x10)==0x17 && X(field<void*>(button,0x34))->rva000C4640()==selected) {
            void *module=X(object)->rva001BEE60(key);
            if (module) X(module)->rva001EDAD0(button);
            break;
        }
    }
    break;
}
case 0x42e:
case 0x441: {
    dispatchPosition=msg->getArgument(0)->location;
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00151130(LOCKED_TEMPORARILY);
    order441.position=&dispatchPosition; order441.append=false; order441.rva_8=0; order441.rva_c=0;
    X(currentlySelectedGroup)->rva00159AD0(&order441,0);
    break;
}
case 0x431: {
    dispatchPosition=msg->getArgument(0)->location;
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00151130(LOCKED_TEMPORARILY);
    order431.position=&dispatchPosition; order431.append=true; order431.rva_8=0; order431.rva_c=0;
    X(currentlySelectedGroup)->rva00159AD0(&order431,0);
    break;
}
case 0x432:
		{
			dispatchPosition = msg->getArgument( 0 )->location;
			GuardMode gm = (GuardMode)msg->getArgument( 1 )->integer;
			if (!currentlySelectedGroup) return; 
			{
				X(currentlySelectedGroup)->rva00156840(&dispatchPosition, gm, CMD_FROM_PLAYER);
			}
			break;
		}
case 0x433:
		{
			Object* obj = TheGameLogic->findObjectByID( msg->getArgument( 0 )->objectID );
			if (!obj)
				break;
			GuardMode gm = (GuardMode)msg->getArgument( 1 )->integer;
			if (!currentlySelectedGroup) return; 
			{
				currentlySelectedGroup->groupGuardObject(obj, gm, CMD_FROM_PLAYER);
			}
			break;
		}
case 0x434:
		{
			if (!currentlySelectedGroup) return; 
			{
				X(currentlySelectedGroup)->rva00155B90(CMD_FROM_PLAYER);
			}
			break;
		}
case 0x435:
		{
			if (!currentlySelectedGroup) return; 
			{
				X(currentlySelectedGroup)->rva00155490(CMD_FROM_PLAYER);
			}
			break;
		}
case 0x448:
case 0x442: {
    if (TheInGameUI) TheInGameUI->clearPopupMessageData();
    break;
}
case 0x453:
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00156B10();
case 0x437:
case 0x44b:
case 0x44c:
case 0x44d:
case 0x44e:
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00150D80(0,msgType,(void*)15); break;
case 0x452: {
    Object *object=TheGameLogic->findObjectByID(msg->getArgument(0)->objectID);
    if (!object) break;
    void *module=X(object)->rva001BFE20();
    if (!module || !v0<0x58,bool>(module)) break;
    v0<0x5c,void>(module);
    if (X(object)->rva001BE570()) field<bool>(TheControlBar,0x24)=true;
    break;
}
case 0x45f: {
    const ThingTemplate *what=TheThingFactory->findByTemplateID((unsigned short)msg->getArgument(1)->integer);
    if (!what) break;
    Object *object=TheGameLogic->findObjectByID(msg->getArgument(0)->objectID);
    if (!object) break;
    void *module=X(object)->rva001BFE20();
    if (!module || !v1<0x60,bool>(module,what)) break;
    v1<0x64,void>(module,what);
    if (X(object)->rva001BE570()) field<bool>(TheControlBar,0x24)=true;
    break;
}
case 0x454: {
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00151130(LOCKED_TEMPORARILY);
    X(currentlySelectedGroup)->rva00150B60(0); break;
}
case 0x436: {
    Object *object=TheGameLogic->findObjectByID(msg->getArgument(0)->objectID);
    if (!object) break;
    static NameKeyType key=TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
    void *module=X(object)->rva001BEE60(key);
    void *base=module?(char*)module-4:0;
    if (!base) {
        module=X(object)->rva001BEE60(TheNameKeyGenerator->nameToKey("GateProxyBehavior"));
        base=module?(char*)module-4:0;
        if (!base) break;
    }
    if (!v0<0x18,bool>(base) && v0<0x28,bool>(base)) v0<0x1c,void>(base);
    break;
}
case 0x438: {
    Object *object=TheGameLogic->findObjectByID(msg->getArgument(0)->objectID);
    if (!object) break;
    static NameKeyType key=TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
    void *module=X(object)->rva001BEE60(key);
    void *base=module?(char*)module-4:0;
    if (!base) {
        module=X(object)->rva001BEE60(TheNameKeyGenerator->nameToKey("GateProxyBehavior"));
        base=module?(char*)module-4:0;
        if (!base) break;
    }
    if (v0<0x18,bool>(base) && v0<0x28,bool>(base)) v0<0x20,void>(base);
    break;
}
case 0x440:
		{
			const Coord3D *loc = &msg->getArgument( 0 )->location;
			SpecialPowerType spType = (SpecialPowerType)msg->getArgument( 1 )->integer;
			ObjectID sourceID = msg->getArgument(2)->objectID;
			Object* source = TheGameLogic->findObjectByID(sourceID);
			if (source != NULL)
			{
				AIGroup* theGroup = TheAI->createGroup();
				theGroup->add(source);
				theGroup->groupOverrideSpecialPowerDestination( spType, loc, CMD_FROM_PLAYER );
				TheAI->destroyGroup(theGroup);
			}
			else
			{
				if( currentlySelectedGroup )
				{
					currentlySelectedGroup->groupOverrideSpecialPowerDestination( spType, loc, CMD_FROM_PLAYER );
				}
			}
		}
case 0x424: {
    Object *enemy=TheGameLogic->findObjectByID(msg->getArgument(0)->objectID);
    dispatchPosition=msg->getArgument(1)->location;
    if (!enemy) break;
    if (field<int>(enemy,0x74)==99999999) {
        if (!field<bool>(field<void*>(TheAI,0x14),0xb8)) break;
        enemy=X(TheTerrainLogic)->rva001AA5B0(&dispatchPosition);
        if (!enemy) break;
        if (v0<0x28,void*>(enemy)) X(v0<0x28,void*>(enemy))->rva00411F80(true);
    }
    if (!currentlySelectedGroup) return;
    X(currentlySelectedGroup)->rva00151130(LOCKED_TEMPORARILY);
    X(currentlySelectedGroup)->rva00155DA0(false,enemy,0x7fffffff,0);
    break;
}
case 0x43d: {
    Object *object=((BfmeObjectReference*)currentlySelectedGroup)->resolve();
    if (!object) return;
    static NameKeyType key=TheNameKeyGenerator->nameToKey("CastleBehavior");
    void *module=X(object)->rva001BEE60(key);
    if (module && X(module)->rva0036BA40() && X(module)->rva00371550(object->getControllingPlayer(),0))
        X(module)->rva00376C70();
    break;
}
case 0x43c: {
    Object *object=((BfmeObjectReference*)currentlySelectedGroup)->resolve();
    if (!object) return;
    static NameKeyType key=TheNameKeyGenerator->nameToKey("CastleBehavior");
    void *module=X(object)->rva001BEE60(key);
    if (module && X(module)->rva0036E420(true) && X(module)->rva00371550(object->getControllingPlayer(),0)
        && X(module)->rva0036F8D0(object->getControllingPlayer())) X(module)->rva00376B00(false,0);
    break;
}
case 0x43e: {
    Object *object=((BfmeObjectReference*)currentlySelectedGroup)->resolve();
    if (!object) return;
    const ThingTemplate *what=TheThingFactory->findByTemplateID((unsigned short)msg->getArgument(0)->integer);
    static NameKeyType key=TheNameKeyGenerator->nameToKey("CastleBehavior");
    void *module=X(object)->rva001BEE60(key);
    if (what && module && X(module)->rva0036E420(true) && X(module)->rva00371550(object->getControllingPlayer(),0)
        && X(module)->rva0036BA60(object->getControllingPlayer(),what)) X(module)->rva00376B00(false,what);
    break;
}
case 0x45c: {
    Object *object=((BfmeObjectReference*)currentlySelectedGroup)->resolve();
    if (!object) return;
    void *module=X(object)->rva001BF670();
    if (module && v0<0x1c,bool>(module) && v1<0x18,bool>(module,object->getControllingPlayer())) {
        float value=v0<0x10,float>(field<void*>(object,0x200));
        v1<0x10,void>(module,0);
        X(object)->rva001C5800();
        v1<0xa8,void>(field<void*>(object,0x200),value);
        X(object)->rva001C7E60(0);
        field<bool>(TheControlBar,0x24)=true;
    }
    break;
}
case 0x460: { v2<0xec,void>(TheInGameUI,true,thisPlayer); break; }
case 0x443:
		{
			dispatchPosition = msg->getArgument( 0 )->location;
			if (!isValidBeaconPosition_001A40C0(&dispatchPosition) || !thisPlayer) break;
			const ThingTemplate *thing = X(TheThingFactory)->rva00137E80(field<AsciiString>(field<void*>(thisPlayer,4),0xe4));
			if (thing && !v1<0x2c,bool>(TheVictoryConditions,thisPlayer))
			{
				Int count;
				X(thisPlayer)->rva000CDD50(1,&thing,false,&count,true);
				DEBUG_LOG(("Player already has %d beacons active\n", count));
				if (count >= field<int>(TheMultiplayerSettings,0x14))
				{
					if (thisPlayer == field<Player*>(ThePlayerList,0xc))
					{
						((Rva397540Message<0x34>*)TheInGameUI)->invoke( ((VDispatch2<0x28,UnicodeString,const char*,bool*>*)TheGameText)->invoke("GUI:TooManyBeacons",0) );
						static AudioEventRTS aSound("BeaconPlacementFailed",(ObjectID)0);
						aSound.setPosition(&dispatchPosition);
						aSound.setPlayerIndex(field<int>(thisPlayer,0x24));
						v1<0x44,unsigned>(TheAudio,(const AudioEventRTS*)&aSound);
					}
					break;
				}
				BitFlags<86> flags;
Object *object=X(TheThingFactory)->rva00138520(thing,field<Team*>(thisPlayer,0x230),&flags,0);
				object->setPosition( &dispatchPosition );
				object->setProducer(NULL);
				if (thisPlayer->getRelationship( field<Team*>(field<Player*>(ThePlayerList,0xc),0x230) ) == ALLIES || field<Player*>(ThePlayerList,0xc)->isPlayerObserver())
				{
					UnicodeString s;
					s.format(((VDispatch2<0x28,UnicodeString,const char*,bool*>*)TheGameText)->invoke("GUI:BeaconPlaced",0), dispatchUnicodeText(thisPlayer->getPlayerDisplayName()));
					((Rva397540Message<0x40>*)TheInGameUI)->invoke(s);
					static AudioEventRTS aSound("Gui_BeaconPlaced",(ObjectID)0);
					aSound.setPlayerIndex(field<int>(thisPlayer,0x24));
					aSound.setPosition(&dispatchPosition);
					v1<0x44,unsigned>(TheAudio,(const AudioEventRTS*)&aSound);
					X(TheRadar)->rva00108140((const Coord3D*)((char*)object+0x38),0,4.0f);
					if (field<Player*>(ThePlayerList,0xc)->getRelationship(field<Team*>(thisPlayer,0x230)) == ALLIES)
						X(TheEva)->rva004233A0(3,0);
					field<bool>(TheControlBar,0x24)=true; 
				}
				else
				{
					Int updateCount = 0;
					static NameKeyType nameKeyClientUpdate = TheNameKeyGenerator->nameToKey("BeaconClientUpdate");
					ClientUpdateModule ** clientModules = field<ClientUpdateModule**>(v0<0x28,void*>(object),0x154);
					if (clientModules)
					{
						while (*clientModules)
						{
							if (v0<0x10,NameKeyType>(*clientModules) == nameKeyClientUpdate)
							{
								X(*clientModules)->rva00603520();
								++updateCount;
							}
							++clientModules;
						}
					}
					DEBUG_ASSERTCRASH(updateCount == 1, ("Saw %d update modules for the beacon!", updateCount));
				}
			}
			else
			{
				((Rva397540Message<0x34>*)TheInGameUI)->invoke( ((VDispatch2<0x28,UnicodeString,const char*,bool*>*)TheGameText)->invoke("GUI:BeaconPlacementFailed",0) );
				static AudioEventRTS aSound("BeaconPlacementFailed",(ObjectID)0);
				aSound.setPosition(&dispatchPosition);
				aSound.setPlayerIndex(field<int>(thisPlayer,0x24));
				v1<0x44,unsigned>(TheAudio,(const AudioEventRTS*)&aSound);
			}
			break;
		}
case 0x444:
		{
			AIGroup *allSelectedObjects = NULL;
			allSelectedObjects = TheAI->createGroup();
            if (!thisPlayer) break;
			thisPlayer->getCurrentSelectionAsAIGroup(allSelectedObjects); 
			if( allSelectedObjects )
			{
				const VecObjectID& selectedObjects = allSelectedObjects->getAllIDs();
				for (VecObjectID::const_iterator it = selectedObjects.begin(); it != selectedObjects.end(); ++it)
				{
					Object *beacon = findObjectByID(*it);
					if (beacon)
					{
						const ThingTemplate *thing = X(TheThingFactory)->rva00137E80(field<AsciiString>(field<void*>(beacon->getControllingPlayer(),4),0xe4));
						if (thing->isEquivalentTo(beacon->getTemplate()))
						{
							if (beacon->getControllingPlayer() == thisPlayer)
							{
								TheGameLogic->destroyObject(beacon); 
								field<bool>(TheControlBar,0x24)=true; 
							}
							else if (thisPlayer == field<Player*>(ThePlayerList,0xc))
							{
								Drawable *beaconDrawable = (Drawable*)v0<0x28,void*>(beacon);
								if (beaconDrawable)
								{
									static NameKeyType nameKeyClientUpdate = TheNameKeyGenerator->nameToKey("BeaconClientUpdate");
									ClientUpdateModule ** clientModules = field<ClientUpdateModule**>(beaconDrawable,0x154);
									if (clientModules)
									{
										while (*clientModules)
										{
											if (v0<0x10,NameKeyType>(*clientModules) == nameKeyClientUpdate)
												X(*clientModules)->rva00603520();
											++clientModules;
										}
									}
								}
							}
						}
					}
				}
				if (X(allSelectedObjects)->rva001506E0())
				{
					TheAI->destroyGroup(allSelectedObjects);
					allSelectedObjects = NULL;
				}
			}
			break;
		}
case 0x445:
		{
			if (!currentlySelectedGroup) return; 
			{
				const VecObjectID& selectedObjects = currentlySelectedGroup->getAllIDs();
				for (VecObjectID::const_iterator it = selectedObjects.begin(); it != selectedObjects.end(); ++it)
				{
					Object *beacon = findObjectByID(*it);
					if (beacon)
					{
						Drawable *beaconDrawable = (Drawable*)v0<0x28,void*>(beacon);
						if (beaconDrawable)
						{
							UnicodeString s;
							for( int i=0; i<field<unsigned char>(msg,0x18); i++ )
							{
								wchar_t ch=msg->getArgument(i)->wChar; ((StringBase<wchar_t>*)&s)->concat(&ch,1);
							}
							if (s.isEmpty())
								X(beaconDrawable)->rva00411BB0();
							else
								X(beaconDrawable)->rva00418880(s);
						}
					}
				}
			}
			break;
		}
case 0x447:
		{
			if (!thisPlayer) break;
			if (msg->getArgument(0)->boolean)
			{
				for (Int i=0; i<field<int>(ThePlayerList,0x10); ++i)
				{
					if (i != msg->getPlayerIndex())
					{
						Player *otherPlayer = ThePlayerList->getNthPlayer(i);
						if (otherPlayer && thisPlayer->getRelationship(field<Team*>(otherPlayer,0x230)) == ALLIES &&
							otherPlayer->getRelationship(field<Team*>(thisPlayer,0x230)) == ALLIES)
						{
							if (v1<0x2c,bool>(TheVictoryConditions,otherPlayer))
								continue;
							X(otherPlayer)->rva000D48E0(thisPlayer,true);
							thisPlayer->killPlayer(); 
							break;
						}
					}
				}
				if (i == field<int>(ThePlayerList,0x10)) { thisPlayer->killPlayer(); }
 X(TheGameEngine)->rva0006C3A0();
			}
			else
			{
				thisPlayer->killPlayer();
			}
			break;
		}
case 0x446: {
    bool observe=field<Player*>(TheControlBar,0x274)==thisPlayer;
    if (field<Player*>(ThePlayerList,0xc)==thisPlayer) observe=true;
    if (TheRecorder->getMode()==RECORDERMODETYPE_PLAYBACK && field<bool>(TheGlobalData,0xc0d) && observe && v0<0x74,bool>(TheTacticalView)) {
        Dispatch397540View loc;
        dispatchPosition=msg->getArgument(0)->location;
        float angle=msg->getArgument(1)->real;
        float pitch=msg->getArgument(2)->real;
        float zoom=msg->getArgument(3)->real;
        float extra=msg->getArgument(4)->real;
        X(&loc)->rva00396830(dispatchPosition.x,dispatchPosition.y,dispatchPosition.z,angle,pitch,zoom,extra);
        v1<0x170,void>(TheTacticalView,&loc);
        if (!X(TheLookAtTranslator)->rva005B53D0()) {
            v1<0x38,void>(TheMouse,msg->getArgument(5)->integer);
            ICoord2D mousePos=msg->getArgument(6)->pixel;
            v2<0x30,void>(TheMouse,mousePos.x,mousePos.y);
            X(TheLookAtTranslator)->rva005B5420(mousePos);
        }
    }
    break;
}
case 0x449: {
    if (!thisPlayer) break;
    unsigned crc=msg->getArgument(0)->integer;
    unsigned frame=msg->getArgument(1)->integer;
    msg->getArgument(2);
    bool flag=msg->getArgument(3)->boolean;
    if (TheNetwork) {
        for (int i=0;i<8;++i) {
            if (field<int>(thisPlayer,0x2c)==0 &&
                thisPlayer->getPlayerDisplayName()==((VDispatch1<0x9c,UnicodeString,int>*)TheNetwork)->invoke(i) &&
                v1<0xac,bool>(TheNetwork,i))
                X(this)->rva0038B430(crc,msg->getPlayerIndex(),frame,msg,flag,0);
        }
    } else if (TheRecorder && TheRecorder->getMode()==RECORDERMODETYPE_PLAYBACK) {
        X(TheRecorder)->rva0009B590(crc,field<int>(thisPlayer,0x24),msg->getArgument(2)->boolean,frame);
    }
    break;
}
case 0x459: {
    if (!currentlySelectedGroup) return;
    void *arg=(void*)msg->getArgument(0)->integer;
    X(currentlySelectedGroup)->rva00151560(arg,0); break;
}
case 0x45d: { int argument=msg->getArgument(0)->integer; X(TheGameLogic)->rva003838D0(argument); break; }
case 0x45e: { int argument=msg->getArgument(0)->integer; X(TheGameLogic)->rva003838E0(argument); break; }
case 0x7d9: { X(TheGameLogic)->rva003855F0(); break; }
case 0x7ea: { X(TheGameLogic)->rva00383980(); break; }
}  
	if (currentlySelectedGroup && TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK && field<bool>(TheGlobalData,0xc0d) && field<Player*>(TheControlBar,0x274) == thisPlayer )
	{
		const VecObjectID& selectedObjects = currentlySelectedGroup->getAllIDs();
		v0<0xe8,void>(TheInGameUI);
		for (VecObjectID::const_iterator it = selectedObjects.begin(); it != selectedObjects.end(); ++it)
		{
			const Object *obj = X(this)->rva0009A510(*it);
			if (obj)
			{
				Drawable *draw = (Drawable*)v0<0x28,void*>((void*)obj);
				if (draw)
					v1<0xe0,void>(TheInGameUI,draw);
			}
		}
	}
	if( currentlySelectedGroup != NULL )
	{
		TheAI->destroyGroup(currentlySelectedGroup);
	}
}  

