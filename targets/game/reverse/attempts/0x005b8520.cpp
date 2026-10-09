// ?translateGameMessage@SelectionTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
// partial score=0.566 date=2026-10-09
// ?translateGameMessage@SelectionTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/mouselayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// SelectionXlat.cpp
// Message stream translator
// Author: Michael S. Booth, January 2001

// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ActionManager.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/MessageStream.h"
#include "Common/MiscAudio.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingTemplate.h"

#include "GameLogic/Damage.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Squad.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/UpdateModule.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Display.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Keyboard.h"
#include "GameClient/SelectionInfo.h"
#include "GameClient/SelectionXlat.h"
#include "GameClient/TerrainVisual.h"


#include <hash_map>
#include "GameLogic/TerrainLogic.h"
Bool areAllSelected(const DrawableList &listToCheck);
extern Int Rva00459060(Bool mode);
namespace Rva005B8520ABI {
// ?getPickTypesForContext@Rva005B8520ABI@@YAI_N@Z absent-from-retail
static __forceinline UnsignedInt getPickTypesForContext(Bool mode) { return Rva00459060(mode); }
}

extern void bfmeGoEGEb();
class Rva000C4A70 { public: Bool field() const; };
class Rva005B8520Terrain { public: PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *point); };
class BFMEActionObject { public: Bool testStatus(Int status) const; };
class BFMERopeDrawableGetPositionShim { public: const Coord3D *get() const; };
class Rva005B8520Mouse {
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void unused06();
    virtual void unused07();
    virtual void unused08();
    virtual void unused09();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void slot38(Int cursor);
};
class Rva005B8520ObjectSlots {
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void unused06();
    virtual void unused07();
    virtual void unused08();
    virtual void unused09();
    virtual Drawable *getDrawable();
};
static __forceinline Object *bfmeDrawableObject(const Drawable *draw) { return *(Object *const *)((const char *)draw+0xFC); }
static __forceinline ObjectID bfmeObjectID(const Object *obj) { return *(const ObjectID *)((const char *)obj+0x74); }
static __forceinline Drawable *bfmeObjectDrawable(const Object *obj) { return ((Rva005B8520ObjectSlots *)obj)->getDrawable(); }
static __forceinline Object *bfmeContainedBy(const Object *obj) { return *(Object *const *)((const char *)obj+0x214); }
static __forceinline ObjectID bfmeObjectField78(const Object *obj) { return *(const ObjectID *)((const char *)obj+0x78); }
static __forceinline Team *bfmeObjectTeam(const Object *obj) { return *(Team *const *)((const char *)obj+0x23C); }
static __forceinline Bool bfmeObjectDead(const Object *obj) { return (*(const unsigned int *)((const char *)obj+0x344)&1)!=0; }
static __forceinline DrawableID bfmeDrawableID(const Drawable *draw) { return draw->getID(); }
static __forceinline Bool bfmeDrawableSelected(const Drawable *draw) { return *(const Bool *)((const char *)draw+0x3AC); }
static __forceinline Drawable *bfmeNextDrawable(const Drawable *draw) { return *(Drawable *const *)((const char *)draw+0x104); }
static __forceinline const Coord3D *bfmeDrawablePosition(const Drawable *draw) { return ((const BFMERopeDrawableGetPositionShim *)draw)->get(); }
static __forceinline Bool &bfmeUIByte(unsigned int offset) { return *(Bool *)((char *)TheInGameUI+offset); }
static __forceinline UnsignedInt bfmeMouseWord(unsigned int offset) { return *(const UnsignedInt *)((const char *)TheMouse+offset); }
static __forceinline Bool bfmeAlternateMouse() { return *(const Bool *)((const char *)TheGlobalData+0x60); }
static __forceinline unsigned int bfmeGameFrame() { return *(const unsigned int *)((const char *)TheGameLogic+0x3C); }
static __forceinline Player *bfmeLocalPlayer() { return *(Player **)((char *)ThePlayerList+0x0C); }
class BfmeVecAK {
public:
    Object **m_bfmeStart;
    Object **m_bfmeFinish;
    Object **m_bfmeEnd;
    Int size() const { return m_bfmeFinish-m_bfmeStart; }
    Object *operator[](Int i) const { return m_bfmeStart[i]; }
};
class Gen_0018BC70 { public: BfmeVecAK *bfmeCompact(Bool restart); };
static __forceinline BfmeVecAK *bfmeLiveObjects(Squad *squad) { return ((Gen_0018BC70 *)squad)->bfmeCompact(FALSE); }
class Rva005B8520UI {
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void unused06();
    virtual void unused07();
    virtual void unused08();
    virtual void unused09();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void unused14();
    virtual void unused15();
    virtual void unused16();
    virtual void unused17();
    virtual void unused18();
    virtual void unused19();
    virtual void unused20();
    virtual void unused21();
    virtual void unused22();
    virtual void unused23();
    virtual void unused24();
    virtual void slot64(Bool value);
    virtual void endAreaSelectHint(const GameMessage *msg);
    virtual void unused27();
    virtual void unused28();
    virtual void unused29();
    virtual void createMouseoverHint(const GameMessage *msg);
    virtual void unused31();
    virtual void unused32();
    virtual void unused33();
    virtual void unused34();
    virtual void unused35();
    virtual void unused36();
    virtual void unused37();
    virtual void unused38();
    virtual void unused39();
    virtual void setScrolling(Bool value);
    virtual Bool isScrolling();
    virtual void setSelecting(Bool value);
    virtual void unused43();
    virtual void unused44();
    virtual void unused45();
    virtual void unused46();
    virtual const CommandButton *getGUICommand() const;
    virtual void unused48();
    virtual void unused49();
    virtual ObjectID getPendingPlaceSourceObjectID();
    virtual void unused51();
    virtual void unused52();
    virtual void unused53();
    virtual void unused54();
    virtual void unused55();
    virtual void selectDrawable(Drawable *draw);
    virtual void deselectDrawable(Drawable *draw);
    virtual void deselectAllDrawables();
    virtual void unused59();
    virtual Int getSelectCount();
    virtual void unused61();
    virtual UnsignedInt getFrameSelectionChanged();
    virtual const DrawableList *getAllSelectedDrawables() const;
    virtual void unused64();
    virtual void unused65();
    virtual void unused66();
    virtual void unused67();
    virtual Bool isAnySelectedKindOf(KindOfType type);
    virtual void unused69();
    virtual void unused70();
    virtual void unused71();
    virtual void unused72();
    virtual void unused73();
    virtual void unused74();
    virtual void unused75();
    virtual void unused76();
    virtual void unused77();
    virtual void unused78();
    virtual void unused79();
    virtual void unused80();
    virtual void unused81();
    virtual void unused82();
    virtual void unused83();
    virtual void unused84();
    virtual Bool isQuitMenuVisible() const;
};
static __forceinline Rva005B8520UI *selectionUI() { return (Rva005B8520UI *)TheInGameUI; }
class Rva005B8520View {
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void unused06();
    virtual void unused07();
    virtual void unused08();
    virtual Drawable *pickDrawable(const ICoord2D *point, Bool attack, Int flags);
    virtual void iterateDrawablesInRegion(const IRegion2D *region, Bool (*callback)(Drawable *, void *), void *data);
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void unused14();
    virtual void unused15();
    virtual void unused16();
    virtual void unused17();
    virtual void unused18();
    virtual void unused19();
    virtual void unused20();
    virtual void lookAt(const Coord3D *point);
    virtual void unused22();
    virtual void unused23();
    virtual void unused24();
    virtual void unused25();
    virtual void unused26();
    virtual void unused27();
    virtual void unused28();
    virtual void unused29();
    virtual void unused30();
    virtual void unused31();
    virtual void unused32();
    virtual void unused33();
    virtual void unused34();
    virtual void unused35();
    virtual void unused36();
    virtual void unused37();
    virtual void unused38();
    virtual void unused39();
    virtual void unused40();
    virtual void unused41();
    virtual void unused42();
    virtual void unused43();
    virtual void unused44();
    virtual void unused45();
    virtual void unused46();
    virtual void unused47();
    virtual void unused48();
    virtual void unused49();
    virtual void unused50();
    virtual void unused51();
    virtual void unused52();
    virtual void unused53();
    virtual void unused54();
    virtual void unused55();
    virtual void unused56();
    virtual void unused57();
    virtual void unused58();
    virtual void unused59();
    virtual void unused60();
    virtual void unused61();
    virtual void unused62();
    virtual void unused63();
    virtual void unused64();
    virtual void unused65();
    virtual void unused66();
    virtual void unused67();
    virtual void unused68();
    virtual void getPosition(Coord3D *point);
    virtual void unused70();
    virtual void unused71();
    virtual void unused72();
    virtual void unused73();
    virtual void unused74();
    virtual void unused75();
    virtual void unused76();
    virtual void unused77();
    virtual void unused78();
    virtual void unused79();
    virtual void unused80();
    virtual void unused81();
    virtual void unused82();
    virtual void unused83();
    virtual void unused84();
    virtual void unused85();
    virtual void unused86();
    virtual void unused87();
    virtual void unused88();
    virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *point, Bool value);
    virtual void unused90();
    virtual void unused91();
    virtual void unused92();
    virtual void unused93();
    virtual void unused94();
    virtual void unused95();
    virtual void unused96();
    virtual void unused97();
    virtual void unused98();
    virtual void unused99();
    virtual void unused100();
    virtual void unused101();
    virtual void unused102();
    virtual void slot19C();
    virtual void setMouseLock(Bool value);
    virtual void unused105();
    virtual void unused106();
    virtual void unused107();
    virtual void unused108();
    virtual void unused109();
    virtual void unused110();
    virtual void unused111();
    virtual void unused112();
    virtual void unused113();
    virtual Bool slot1C8();
};
static __forceinline Rva005B8520View *selectionView() { return (Rva005B8520View *)TheTacticalView; }
class Rva005B8520Client {
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void unused06();
    virtual void unused07();
    virtual void unused08();
    virtual void unused09();
    virtual void unused10();
    virtual Drawable *findDrawableByID(DrawableID id);
    virtual void unused12();
    virtual GameMessage::Type evaluateContextCommand(Drawable *draw, const Coord3D *position, Int type);
    virtual void unused14();
    virtual void unused15();
    virtual void unused16();
    virtual void unused17();
    virtual void unused18();
    virtual void unused19();
    virtual void unused20();
    virtual void unused21();
    virtual void unused22();
    virtual void unused23();
    virtual void unused24();
    virtual void unused25();
    virtual void unused26();
    virtual void unused27();
    virtual void unused28();
    virtual void unused29();
    virtual void unused30();
    virtual Drawable *getDrawableList();
};
static __forceinline Rva005B8520Client *selectionClient() { return (Rva005B8520Client *)TheGameClient; }
class Rva005B8520Point : public ICoord2D {
public:
    Rva005B8520Point(const ICoord2D &point) { x=point.x; y=point.y; }
};
class Rva005B8520UILasso {
public:
    void appendPoint(Rva005B8520Point point);
    Int iterate(Bool (*callback)(Drawable *, void *), void *data);
};
class BfmeOwnerVNY { public: void bfmeResetVNY(); };
static __forceinline void resetLasso() { ((BfmeOwnerVNY *)TheInGameUI)->bfmeResetVNY(); }
static __forceinline void appendLassoPoint(ICoord2D point) { ((Rva005B8520UILasso *)TheInGameUI)->appendPoint(point); }
namespace Rva005B8520Layout {
class PickDrawableStruct : public ::PickDrawableStruct {
public:
    unsigned int m_reservedMask[(56-sizeof(::PickDrawableStruct))/4];
};
}
typedef char Rva005B8520PickSize[sizeof(Rva005B8520Layout::PickDrawableStruct)==56?1:-1];
namespace _STL {
template <> struct hash<ObjectID> { size_t operator()(ObjectID key) const { return (size_t)key; } };
}
typedef std::hash_map<UnsignedInt, Bool> Rva005B8520SelectedIDs;

namespace _STL {
extern template hash_map<UnsignedInt, Bool, hash<UnsignedInt>, equal_to<UnsignedInt>, allocator<pair<const UnsignedInt, Bool> > >::hash_map();
}
typedef char Rva005B8520MapSize[sizeof(Rva005B8520SelectedIDs)==20?1:-1];


class Rva005B8520Stream {
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual void unused03();
    virtual void unused04();
    virtual void unused05();
    virtual void unused06();
    virtual void unused07();
    virtual void unused08();
    virtual void unused09();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual GameMessage *appendMessage(GameMessage::Type type);
};
static __forceinline Rva005B8520Stream *selectionStream() { return (Rva005B8520Stream *)TheMessageStream; }
// ?translateGameMessage@SelectionTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
GameMessageDisposition SelectionTranslator::translateGameMessage(const GameMessage *msg)
{
    GameMessageDisposition disp = KEEP_MESSAGE;
    if (bfmeUIByte(0x0D) && bfmeUIByte(0x0E) && !((Rva005B8520UI *)TheInGameUI)->isQuitMenuVisible())
    {
    Int t=msg->getType();
    switch (t)
    {
    case 3:
    {
        Rva005B8520Point pixel=msg->getArgument(0)->pixel;
        if (m_leftMouseButtonIsDown)
        {
            if (!bfmeMouseWord(0x4D28))
            {
                m_leftMouseButtonIsDown=FALSE;
                ((Rva005B8520View *)TheTacticalView)->setMouseLock(FALSE);
                ((Rva005B8520UI *)TheInGameUI)->setSelecting(FALSE);
                ((Rva005B8520UI *)TheInGameUI)->endAreaSelectHint(NULL);
            }
        }
        if (m_leftMouseButtonIsDown)
        {
                ICoord2D delta;
                delta.x=abs(pixel.x-m_selectFeedbackAnchor.x);
                delta.y=abs(pixel.y-m_selectFeedbackAnchor.y);
                if ((UnsignedInt)delta.x>bfmeMouseWord(0x10EC) || (UnsignedInt)delta.y>bfmeMouseWord(0x10EC))
                {
                    if (!m_dragSelecting)
                    {
                        m_dragSelecting=TRUE;
                        *(Bool *)((char *)this+6)=TRUE;
                        ((Rva005B8520View *)TheTacticalView)->setMouseLock(TRUE);
                        ((Rva005B8520UI *)TheInGameUI)->setSelecting(TRUE);
                    }
                }
                if (m_dragSelecting)
                {
                    if (bfmeUIByte(0x1318))
                    {
                        ((Rva005B8520UILasso *)TheInGameUI)->appendPoint(pixel);
                        ((Rva005B8520UI *)TheInGameUI)->slot64(FALSE);
                    }
                    else
                    {
                        GameMessage *hintMsg=((Rva005B8520Stream *)TheMessageStream)->appendMessage((GameMessage::Type)152);
                        IRegion2D pixelRegion;
                        buildRegion(&m_selectFeedbackAnchor,&pixel,&pixelRegion);
                        hintMsg->appendPixelRegionArgument(pixelRegion);
                    }
                }
        }
        else
        {
            Coord3D position;
            Int pickType=Rva005B8520ABI::getPickTypesForContext(TRUE);
            Bool forceAttackMode=bfmeUIByte(0x12B1);
            Drawable *underCursor=((Rva005B8520View *)TheTacticalView)->pickDrawable(&pixel,forceAttackMode,pickType);
            Object *objUnderCursor=underCursor?bfmeDrawableObject(underCursor):NULL;
            Object *selectedObj=NULL;
            if (((Rva005B8520UI *)TheInGameUI)->getSelectCount()==1)
            {
                Drawable *draw=*((Rva005B8520UI *)TheInGameUI)->getAllSelectedDrawables()->begin();
                selectedObj=draw?bfmeDrawableObject(draw):NULL;
            }
            if (objUnderCursor && (!selectedObj || !selectedObj->isKindOf((KindOfType)133)))
            {
                if (objUnderCursor->isKindOf((KindOfType)59) && !objUnderCursor->isKindOf((KindOfType)117) && !objUnderCursor->isKindOf((KindOfType)149)
                    && ((Rva005B8520UI *)TheInGameUI)->getSelectCount()>0 && !((Rva005B8520UI *)TheInGameUI)->isAnySelectedKindOf((KindOfType)92)
                    && !((Rva005B8520UI *)TheInGameUI)->isAnySelectedKindOf((KindOfType)54) && !((Rva005B8520UI *)TheInGameUI)->isAnySelectedKindOf((KindOfType)146))
                {
                    ((Rva005B8520View *)TheTacticalView)->screenToTerrain(&pixel,&position,FALSE);
                    if (((Rva005B8520Terrain *)TheTerrainLogic)->getLayerForDestination(NULL,&position)!=(PathfindLayerEnum)1) goto mouseoverTerrain;
                }
                if ((!bfmeObjectDead(objUnderCursor) || ((Rva000C4A70 *)objUnderCursor)->field() || objUnderCursor->isKindOf((KindOfType)57)))
                {
                    GameMessage *mouseoverMessage=((Rva005B8520Stream *)TheMessageStream)->appendMessage((GameMessage::Type)148);
                    mouseoverMessage->appendDrawableIDArgument(bfmeDrawableID(underCursor));
                    break;
                }
            }
        mouseoverTerrain:
            ((Rva005B8520View *)TheTacticalView)->screenToTerrain(&pixel,&position,FALSE);
            GameMessage *mouseoverMessage=((Rva005B8520Stream *)TheMessageStream)->appendMessage((GameMessage::Type)149);
            mouseoverMessage->appendLocationArgument(position);
        }
        break;
    }
    case 148:
    {
        if (((Rva005B8520UI *)TheInGameUI)->isScrolling()) break;
        DrawableID id=msg->getArgument(0)->drawableID;
        Drawable *draw=((Rva005B8520Client *)TheGameClient)->findDrawableByID(id);
        if (!draw) break;
        GameMessage::Type msgType=((Rva005B8520Client *)TheGameClient)->evaluateContextCommand(draw,bfmeDrawablePosition(draw),2);
        if (msgType==GameMessage::MSG_INVALID)
        {
            ((Rva005B8520UI *)TheInGameUI)->createMouseoverHint(msg);
            disp=DESTROY_MESSAGE;
            const CommandButton *command=((Rva005B8520UI *)TheInGameUI)->getGUICommand();
            Bool ignoreCommand=FALSE;
            if (command)
            {
                Int commandType=command->getCommandType();
                if (commandType==9 || commandType==10 || commandType==11 || commandType==12) ignoreCommand=TRUE;
            }
            if (!ignoreCommand && !draw->getTemplate()->isKindOf((KindOfType)6))
            {
                if (CanSelectDrawable(draw,FALSE)) ((Rva005B8520Mouse *)TheMouse)->slot38(13);
                else ((Rva005B8520Mouse *)TheMouse)->slot38(2);
            }
        }
        break;
    }
    case 23:
    {
        Bool dragSelecting=*(Bool *)((char *)this+6);
        *(Bool *)((char *)this+6)=FALSE;
        if (((Rva005B8520UI *)TheInGameUI)->isQuitMenuVisible() || (TheTacticalView && ((Rva005B8520View *)TheTacticalView)->slot1C8()))
        {
            disp=DESTROY_MESSAGE;
            break;
        }
        IRegion2D selectionRegion=msg->getArgument(0)->pixelRegion;
        Bool isPoint=selectionRegion.height()==0 && selectionRegion.width()==0;
        DrawableList drawablesThatWillSelect;
        Rva005B8520Layout::PickDrawableStruct pds;
        pds.drawableListToFill=&drawablesThatWillSelect;
        ((Bool *)&pds)[5]=dragSelecting;
        if (bfmeUIByte(0x1318) || !isPoint)
        {
            ((UnsignedInt *)&pds)[10]|=0x800;
            ((UnsignedInt *)&pds)[11]|=0x80;
        }
        if (bfmeUIByte(0x1318))
        {
            ((Rva005B8520UILasso *)TheInGameUI)->iterate(addDrawableToList,&pds);
            resetLasso();
            bfmeUIByte(0x1318)=FALSE;
            bfmeUIByte(0x12B1)=FALSE;
        }
        else ((Rva005B8520View *)TheTacticalView)->iterateDrawablesInRegion(&selectionRegion,addDrawableToList,&pds);
        Bool addToGroup=bfmeUIByte(0x12B3);
        if (drawablesThatWillSelect.empty() && !addToGroup)
        {
            const CommandButton *command=((Rva005B8520UI *)TheInGameUI)->getGUICommand();
            Int commandType=command?command->getCommandType():0;
            Bool ignoreCommand=command && (commandType==23 || commandType==36 || commandType==31 || commandType==22 || commandType==25 || commandType==28 || commandType==29);
            if (bfmeAlternateMouse() && !ignoreCommand) bfmeGoEGEb();
            break;
        }
        const DrawableList *currentList=((Rva005B8520UI *)TheInGameUI)->getAllSelectedDrawables();
        if (((Rva005B8520UI *)TheInGameUI)->getGUICommand()) break;
        SelectionInfo si;
        if (contextCommandForNewSelection(currentList,&drawablesThatWillSelect,&si,isPoint)) break;
        if (si.currentCountEnemies>0 || si.currentCountCivilians>0 || si.currentCountFriends>0 || si.currentCountMineBuildings>0) addToGroup=FALSE;
        if (si.newCountMine>0)
        {
            si.selectMine=TRUE;
            if (si.newCountMine==1 && si.newCountMineBuildings==1)
            {
                addToGroup=FALSE;
                si.selectMineBuildings=TRUE;
            }
        }
        else if (si.newCountEnemies>0 && si.newCountCivilians>0 && si.newCountFriends>0) break;
        else if (si.newCountEnemies==1) { addToGroup=FALSE; si.selectEnemies=TRUE; }
        else if (si.newCountCivilians==1) { addToGroup=FALSE; si.selectCivilians=TRUE; }
        else if (si.newCountFriends==1) { addToGroup=FALSE; si.selectFriends=TRUE; }
        if (!(si.selectMine || si.selectEnemies || si.selectCivilians || si.selectFriends)) break;
        m_lastGroupSelGroup=-1;
        disp=DESTROY_MESSAGE;
        if (bfmeUIByte(0x12B3) && isPoint && areAllSelected(drawablesThatWillSelect))
        {
            GameMessage *newMsg=((Rva005B8520Stream *)TheMessageStream)->appendMessage((GameMessage::Type)1004);
            Drawable *draw=NULL;
            DrawableListIt it;
            for (it=drawablesThatWillSelect.begin();it!=drawablesThatWillSelect.end();++it)
            {
                draw=*it;
                if (!draw) continue;
                Object *objToDeselect=bfmeDrawableObject(draw);
                if (!objToDeselect) continue;
                newMsg->appendObjectIDArgument(bfmeObjectID(objToDeselect));
                ((Rva005B8520UI *)TheInGameUI)->deselectDrawable(draw);
            }
        }
        else
        {
            if (!addToGroup) ((Rva005B8520UI *)TheInGameUI)->deselectAllDrawables();
            GameMessage *newMsg=((Rva005B8520Stream *)TheMessageStream)->appendMessage((GameMessage::Type)1001);
            newMsg->appendBooleanArgument(!addToGroup);
            Player *localPlayer=bfmeLocalPlayer();
            Rva005B8520SelectedIDs selectedIDs;
            Drawable *draw=NULL;
            DrawableListIt it;
            for (it=drawablesThatWillSelect.begin();it!=drawablesThatWillSelect.end();++it)
            {
                draw=*it;
                if (!draw) continue;
                Object *obj=bfmeDrawableObject(draw);
                if (!obj) continue;
                ObjectID containedID=bfmeObjectField78(obj);
                if (containedID!=INVALID_ID)
                {
                    Object *container=TheGameLogic->findObjectByID(containedID);
                    if (container && container->isKindOf((KindOfType)108))
                    {
                        if (((BFMEActionObject *)container)->testStatus(3)) continue;
                        obj=container;
                        draw=((Rva005B8520ObjectSlots *)(container))->getDrawable();
                    }
                }
                Object *containedBy=bfmeContainedBy(obj);
                if (containedBy && !obj->isKindOf((KindOfType)54))
                {
                    obj=containedBy;
                    draw=((Rva005B8520ObjectSlots *)(containedBy))->getDrawable();
                }
                Drawable *drawToSelect=NULL;
                ObjectID objToAppend=INVALID_ID;
                if (si.selectMine && obj->isLocallyControlled())
                {
                    if (!obj->isKindOf((KindOfType)7) || si.selectMineBuildings)
                    {
                        drawToSelect=draw;
                        objToAppend=bfmeObjectID(obj);
                    }
                }
                else
                {
                    Relationship rel=localPlayer->getRelationship(bfmeObjectTeam(obj));
                    if ((si.selectEnemies && rel==ENEMIES) || (si.selectCivilians && rel==NEUTRAL) || (si.selectFriends && rel==ALLIES))
                    {
                        drawToSelect=draw;
                        objToAppend=bfmeObjectID(obj);
                    }
                }
                if (drawToSelect && objToAppend!=INVALID_ID)
                {
                    Rva005B8520SelectedIDs::iterator already=selectedIDs.find(objToAppend);
                    if (already!=selectedIDs.end()) continue;
                    newMsg->appendObjectIDArgument(objToAppend);
                    ((Rva005B8520UI *)TheInGameUI)->selectDrawable(drawToSelect);
                    selectedIDs[objToAppend]=TRUE;
                }
            }
        }
        break;
    }
    case 4:
    {
        m_leftMouseButtonIsDown=TRUE;
        resetLasso();
        if (TheKeyboard->isCtrl())
        {
            bfmeUIByte(0x1318)=TRUE;
            ((Rva005B8520UILasso *)TheInGameUI)->appendPoint(msg->getArgument(0)->pixel);
        }
        else
        {
            bfmeUIByte(0x1318)=FALSE;
            m_selectFeedbackAnchor=msg->getArgument(0)->pixel;
        }
        break;
    }
    case 6:
    {
        m_leftMouseButtonIsDown=FALSE;
        if (m_dragSelecting)
        {
            m_dragSelecting=FALSE;
            if (bfmeUIByte(0x1318))
            {
                ((Rva005B8520View *)TheTacticalView)->setMouseLock(FALSE);
                ((Rva005B8520UI *)TheInGameUI)->setSelecting(FALSE);
                ((Rva005B8520UILasso *)TheInGameUI)->appendPoint(msg->getArgument(0)->pixel);
                ((Rva005B8520UI *)TheInGameUI)->endAreaSelectHint(NULL);
            }
            else
            {
                ((Rva005B8520View *)TheTacticalView)->setMouseLock(FALSE);
                ((Rva005B8520UI *)TheInGameUI)->setSelecting(FALSE);
                ((Rva005B8520UI *)TheInGameUI)->endAreaSelectHint(NULL);
                GameMessage *dragMsg=((Rva005B8520Stream *)TheMessageStream)->appendMessage((GameMessage::Type)1059);
                IRegion2D selectionRegion;
                buildRegion(&m_selectFeedbackAnchor,&msg->getArgument(0)->pixel,&selectionRegion);
                dragMsg->appendPixelRegionArgument(selectionRegion);
            }
        }
        break;
    }
    case 14:
    {
        m_deselectFeedbackAnchor=msg->getArgument(0)->pixel;
        m_lastClick=(UnsignedInt)msg->getArgument(2)->integer;
        ((Rva005B8520View *)TheTacticalView)->getPosition(&m_deselectDownCameraPosition);
        break;
    }
    case 16:
    {
        ICoord2D delta,pixel;
        UnsignedInt currentTime;
        Coord3D cameraPos;
        ((Rva005B8520View *)TheTacticalView)->getPosition(&cameraPos);
        cameraPos.sub(&m_deselectDownCameraPosition);
        pixel=msg->getArgument(0)->pixel;
        currentTime=(UnsignedInt)msg->getArgument(2)->integer;
        delta.x=m_deselectFeedbackAnchor.x-pixel.x;
        delta.y=m_deselectFeedbackAnchor.y-pixel.y;
        if ((UnsignedInt)abs(delta.x)>bfmeMouseWord(0x10EC) || (UnsignedInt)abs(delta.y)>bfmeMouseWord(0x10EC)) break;
        if (currentTime-m_lastClick>2*bfmeMouseWord(0x10F4)) { ((Rva005B8520View *)TheTacticalView)->slot19C(); break; }
        if (cameraPos.length()>bfmeMouseWord(0x10F0)) break;
        if (((Rva005B8520UI *)TheInGameUI)->getGUICommand() && !bfmeAlternateMouse())
        {
            disp=DESTROY_MESSAGE;
            ((Rva005B8520UI *)TheInGameUI)->setScrolling(FALSE);
        }
        else if (!bfmeAlternateMouse() || ((Rva005B8520UI *)TheInGameUI)->getPendingPlaceSourceObjectID()!=INVALID_ID) bfmeGoEGEb();
        break;
    }
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    {
        Int group=t-49;
        if (group>=0 && group<10)
        {
            GameMessage *newmsg=((Rva005B8520Stream *)TheMessageStream)->appendMessage((GameMessage::Type)(1005+group));
            Drawable *drawable=((Rva005B8520Client *)TheGameClient)->getDrawableList();
            while (drawable!=NULL)
            {
                if (bfmeDrawableSelected(drawable) && bfmeDrawableObject(drawable) && bfmeDrawableObject(drawable)->isLocallyControlled())
                    newmsg->appendObjectIDArgument(bfmeObjectID(bfmeDrawableObject(drawable)));
                drawable=bfmeNextDrawable(drawable);
            }
        }
        disp=DESTROY_MESSAGE;
        break;
    }
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    {
        Int group=t-59;
        if (group>=0 && group<10)
        {
            UnsignedInt now=bfmeGameFrame();
            if (m_lastGroupSelTime==0) m_lastGroupSelTime=now;
            if (m_lastGroupSelGroup>=0)
            {
                if (((Rva005B8520UI *)TheInGameUI)->getFrameSelectionChanged()>m_lastGroupSelTime) m_lastGroupSelGroup=-1;
                else
                {
                    Player *player=bfmeLocalPlayer();
                    Squad *selectedSquad=player?player->getHotkeySquad(m_lastGroupSelGroup):NULL;
                    if (!selectedSquad) m_lastGroupSelGroup=-1;
                    else
                    {
                            BfmeVecAK *objlist=bfmeLiveObjects(selectedSquad);
                            Int numObjs=objlist->size();
                            for (Int i=0;i<numObjs;++i)
                            {
                                Drawable *draw=((Rva005B8520ObjectSlots *)((*objlist)[i]))->getDrawable();
                                if (draw && !bfmeDrawableSelected(draw)) { m_lastGroupSelGroup=-1; break; }
                            }
                    }
                }
            }
            if (now-m_lastGroupSelTime<5 && group==m_lastGroupSelGroup)
            {
                Player *player=bfmeLocalPlayer();
                if (player)
                {
                    Squad *selectedSquad=player->getHotkeySquad(group);
                    if (selectedSquad)
                    {
                        BfmeVecAK *objlist=bfmeLiveObjects(selectedSquad);
                        Int numObjs=objlist->size();
                        if (numObjs>0) ((Rva005B8520View *)TheTacticalView)->lookAt(((const BFMERopeDrawableGetPositionShim *)((Rva005B8520ObjectSlots *)((*objlist)[numObjs-1]))->getDrawable())->get());
                    }
                }
            }
            else
            {
                GameMessage *newMsg=((Rva005B8520Stream *)TheMessageStream)->appendMessage((GameMessage::Type)1003);
                newMsg->appendBooleanArgument(TRUE);
                ((Rva005B8520UI *)TheInGameUI)->deselectAllDrawables();
                ((Rva005B8520Stream *)TheMessageStream)->appendMessage((GameMessage::Type)(1015+group));
                Player *player=bfmeLocalPlayer();
                if (player)
                {
                    Squad *selectedSquad=player->getHotkeySquad(group);
                    if (selectedSquad)
                    {
                        BfmeVecAK *objlist=bfmeLiveObjects(selectedSquad);
                        Int numObjs=objlist->size();
                        for (Int i=0;i<numObjs;++i)
                        {
                            if ((*objlist)[i]->getControllingPlayer()==player) ((Rva005B8520UI *)TheInGameUI)->selectDrawable(((Rva005B8520ObjectSlots *)((*objlist)[i]))->getDrawable());
                        }
                    }
                }
            }
            m_lastGroupSelTime=now;
            m_lastGroupSelGroup=group;
        }
        disp=DESTROY_MESSAGE;
        break;
    }
    case 69:
    case 70:
    case 71:
    case 72:
    case 73:
    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
    {
        Int group=t-69;
        if (group>=0 && group<10)
        {
            UnsignedInt now=bfmeGameFrame();
            if (!m_lastGroupSelTime) m_lastGroupSelTime=now;
            if (now-m_lastGroupSelTime<5 && group==m_lastGroupSelGroup)
            {
                Player *player=bfmeLocalPlayer();
                if (player)
                {
                    Squad *selectedSquad=player->getHotkeySquad(group);
                    if (selectedSquad)
                    {
                        BfmeVecAK *objlist=bfmeLiveObjects(selectedSquad);
                        Int numObjs=objlist->size();
                        if (numObjs>0) ((Rva005B8520View *)TheTacticalView)->lookAt(((const BFMERopeDrawableGetPositionShim *)((Rva005B8520ObjectSlots *)((*objlist)[numObjs-1]))->getDrawable())->get());
                    }
                }
            }
            else
            {
                ((Rva005B8520Stream *)TheMessageStream)->appendMessage((GameMessage::Type)(1025+group));
                Player *player=bfmeLocalPlayer();
                if (player)
                {
                    Squad *selectedSquad=player->getHotkeySquad(group);
                    if (selectedSquad)
                    {
                        BfmeVecAK *objlist=bfmeLiveObjects(selectedSquad);
                        Int numObjs=objlist->size();
                        for (Int i=0;i<numObjs;++i) ((Rva005B8520UI *)TheInGameUI)->selectDrawable(((Rva005B8520ObjectSlots *)((*objlist)[i]))->getDrawable());
                    }
                }
            }
            m_lastGroupSelTime=now;
            m_lastGroupSelGroup=group;
        }
        disp=DESTROY_MESSAGE;
        break;
    }
    case 79:
    case 80:
    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
    case 86:
    case 87:
    case 88:
    {
        Int group=t-79;
        if (group>=1 && group<=10)
        {
            Player *player=bfmeLocalPlayer();
            if (player)
            {
                Squad *selectedSquad=player->getHotkeySquad(group);
                if (selectedSquad)
                {
                    BfmeVecAK *objlist=bfmeLiveObjects(selectedSquad);
                    Int numObjs=objlist->size();
                    if (numObjs>0) ((Rva005B8520View *)TheTacticalView)->lookAt(((const BFMERopeDrawableGetPositionShim *)((Rva005B8520ObjectSlots *)((*objlist)[numObjs-1]))->getDrawable())->get());
                }
            }
        }
        disp=DESTROY_MESSAGE;
        break;
    }
    case 109:
        m_leftMouseButtonIsDown=FALSE;
        break;
    }
    }
    else
    {
        if (m_dragSelecting)
        {
            m_dragSelecting=FALSE;
            ((Rva005B8520UI *)TheInGameUI)->setSelecting(FALSE);
            ((Rva005B8520UI *)TheInGameUI)->endAreaSelectHint(NULL);
            ((Rva005B8520View *)TheTacticalView)->setMouseLock(FALSE);
        }
        return KEEP_MESSAGE;
    }
    return disp;
}
