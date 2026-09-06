// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistringsetoutofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define BFME_PARTICLE_LIST_NODE_TAIL
#include "PreRTS.h"

#define DEFINE_SHADOW_NAMES

#include "Common/ActionManager.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/GameType.h"
#include "Common/MessageStream.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Radar.h"
#include "Common/Team.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/BuildAssistant.h"
#include "Common/Recorder.h"
#include "Common/SpecialPower.h"

#include "GameClient/Anim2D.h"
#include "GameClient/ControlBar.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/Diplomacy.h"
#include "GameClient/Eva.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Drawable.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowID.h"
#include "GameClient/GUICallbacks.h"
#include "GameClient/InGameUI.h"
#include "GameClient/VideoPlayer.h"
#include "GameClient/Mouse.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/View.h"
#include "GameClient/TerrainVisual.h"
#include "GameClient/Display.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/LookAtXlat.h"
#include "GameClient/SelectionXlat.h"
#include "GameClient/Shadow.h"
#include "GameClient/GlobalLanguage.h"

#include "GameLogic/AIGuard.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/Object.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Module/MobMemberSlavedUpdate.h"

#include "Common/UnitTimings.h"

namespace {

struct BfmeIdleWorkerNode {
	BfmeIdleWorkerNode *next;
	BfmeIdleWorkerNode *prev;
	Object *object;
};

struct BfmeIdleWorkerList {
	BfmeIdleWorkerNode *head;
	bool empty() const { return head->next == head; }
	Object *front() const { return head->next->object; }
};

struct BfmeInGameUISelectView {
#define BFME_SELECT_UI_SLOT(n) virtual void bfmeSelectSlot##n() = 0;
	BFME_SELECT_UI_SLOT(0)
	BFME_SELECT_UI_SLOT(1)
	BFME_SELECT_UI_SLOT(2)
	BFME_SELECT_UI_SLOT(3)
	BFME_SELECT_UI_SLOT(4)
	BFME_SELECT_UI_SLOT(5)
	BFME_SELECT_UI_SLOT(6)
	BFME_SELECT_UI_SLOT(7)
	BFME_SELECT_UI_SLOT(8)
	BFME_SELECT_UI_SLOT(9)
	BFME_SELECT_UI_SLOT(10)
	BFME_SELECT_UI_SLOT(11)
	BFME_SELECT_UI_SLOT(12)
	BFME_SELECT_UI_SLOT(13)
	BFME_SELECT_UI_SLOT(14)
	BFME_SELECT_UI_SLOT(15)
	BFME_SELECT_UI_SLOT(16)
	BFME_SELECT_UI_SLOT(17)
	BFME_SELECT_UI_SLOT(18)
	BFME_SELECT_UI_SLOT(19)
	BFME_SELECT_UI_SLOT(20)
	BFME_SELECT_UI_SLOT(21)
	BFME_SELECT_UI_SLOT(22)
	BFME_SELECT_UI_SLOT(23)
	BFME_SELECT_UI_SLOT(24)
	BFME_SELECT_UI_SLOT(25)
	BFME_SELECT_UI_SLOT(26)
	BFME_SELECT_UI_SLOT(27)
	BFME_SELECT_UI_SLOT(28)
	BFME_SELECT_UI_SLOT(29)
	BFME_SELECT_UI_SLOT(30)
	BFME_SELECT_UI_SLOT(31)
	BFME_SELECT_UI_SLOT(32)
	BFME_SELECT_UI_SLOT(33)
	BFME_SELECT_UI_SLOT(34)
	BFME_SELECT_UI_SLOT(35)
	BFME_SELECT_UI_SLOT(36)
	BFME_SELECT_UI_SLOT(37)
	BFME_SELECT_UI_SLOT(38)
	BFME_SELECT_UI_SLOT(39)
	BFME_SELECT_UI_SLOT(40)
	BFME_SELECT_UI_SLOT(41)
	BFME_SELECT_UI_SLOT(42)
	BFME_SELECT_UI_SLOT(43)
	BFME_SELECT_UI_SLOT(44)
	BFME_SELECT_UI_SLOT(45)
	BFME_SELECT_UI_SLOT(46)
	BFME_SELECT_UI_SLOT(47)
	BFME_SELECT_UI_SLOT(48)
	BFME_SELECT_UI_SLOT(49)
	BFME_SELECT_UI_SLOT(50)
	BFME_SELECT_UI_SLOT(51)
	BFME_SELECT_UI_SLOT(52)
	BFME_SELECT_UI_SLOT(53)
	BFME_SELECT_UI_SLOT(54)
	BFME_SELECT_UI_SLOT(55)
	virtual void selectDrawable(Drawable *) = 0;
	BFME_SELECT_UI_SLOT(57)
	virtual void deselectAllDrawables() = 0;
	BFME_SELECT_UI_SLOT(59)
	virtual Int getSelectCount() = 0;
	BFME_SELECT_UI_SLOT(61)
	BFME_SELECT_UI_SLOT(62)
	BFME_SELECT_UI_SLOT(63)
	BFME_SELECT_UI_SLOT(64)
	virtual Drawable *getFirstSelectedDrawable() = 0;
#undef BFME_SELECT_UI_SLOT
};

class BfmeObjectSelectView {
public:
	virtual void bfmeObjectSlot0() = 0;
	virtual void bfmeObjectSlot1() = 0;
	virtual void bfmeObjectSlot2() = 0;
	virtual void bfmeObjectSlot3() = 0;
	virtual void bfmeObjectSlot4() = 0;
	virtual void bfmeObjectSlot5() = 0;
	virtual void bfmeObjectSlot6() = 0;
	virtual void bfmeObjectSlot7() = 0;
	virtual void bfmeObjectSlot8() = 0;
	virtual void bfmeObjectSlot9() = 0;
	virtual Drawable *getDrawable() = 0;

	unsigned char m_pad04[0x70];
	ObjectID m_id;
	unsigned char m_pad78[0x19c];
	Object *m_containedBy;
};

class BfmeMessageStreamSelectView {
public:
	virtual void bfmeMessageSlot0() = 0;
	virtual void bfmeMessageSlot1() = 0;
	virtual void bfmeMessageSlot2() = 0;
	virtual void bfmeMessageSlot3() = 0;
	virtual void bfmeMessageSlot4() = 0;
	virtual void bfmeMessageSlot5() = 0;
	virtual void bfmeMessageSlot6() = 0;
	virtual void bfmeMessageSlot7() = 0;
	virtual void bfmeMessageSlot8() = 0;
	virtual void bfmeMessageSlot9() = 0;
	virtual void bfmeMessageSlot10() = 0;
	virtual void bfmeMessageSlot11() = 0;
	virtual void bfmeMessageSlot12() = 0;
	virtual GameMessage *appendMessage(UnsignedInt type) = 0;
};

struct BfmeDrawableSelectView {
	unsigned char m_pad00[0xfc];
	Object *m_object;
};

class BfmeTacticalViewSelectView {
public:
#define BFME_TACTICAL_VIEW_SLOT(n) virtual void bfmeSlot##n() = 0;
	BFME_TACTICAL_VIEW_SLOT(0)
	BFME_TACTICAL_VIEW_SLOT(1)
	BFME_TACTICAL_VIEW_SLOT(2)
	BFME_TACTICAL_VIEW_SLOT(3)
	BFME_TACTICAL_VIEW_SLOT(4)
	BFME_TACTICAL_VIEW_SLOT(5)
	BFME_TACTICAL_VIEW_SLOT(6)
	BFME_TACTICAL_VIEW_SLOT(7)
	BFME_TACTICAL_VIEW_SLOT(8)
	BFME_TACTICAL_VIEW_SLOT(9)
	BFME_TACTICAL_VIEW_SLOT(10)
	BFME_TACTICAL_VIEW_SLOT(11)
	BFME_TACTICAL_VIEW_SLOT(12)
	BFME_TACTICAL_VIEW_SLOT(13)
	BFME_TACTICAL_VIEW_SLOT(14)
	BFME_TACTICAL_VIEW_SLOT(15)
	BFME_TACTICAL_VIEW_SLOT(16)
	BFME_TACTICAL_VIEW_SLOT(17)
	BFME_TACTICAL_VIEW_SLOT(18)
	BFME_TACTICAL_VIEW_SLOT(19)
	BFME_TACTICAL_VIEW_SLOT(20)
	virtual void lookAt(const Coord3D *) = 0;
#undef BFME_TACTICAL_VIEW_SLOT
};

}

// ?selectNextIdleWorker@InGameUI@@UAEXXZ
void InGameUI::selectNextIdleWorker(void)
{
	Int index = ThePlayerList->getLocalPlayer()->getPlayerIndex();
	BfmeIdleWorkerList *idleWorkers = (BfmeIdleWorkerList *)((char *)this + 0x131c);
	if(idleWorkers[index].empty())
	{
		DEBUG_ASSERTCRASH(FALSE, ("InGameUI::selectNextIdleWorker We're trying to select a worker when our list is empty for player %ls", ThePlayerList->getLocalPlayer()->getPlayerDisplayName().str()));
		return;
	}
	Object *selectThisObject = NULL;

	BfmeInGameUISelectView *selectView = (BfmeInGameUISelectView *)this;
	if(selectView->getSelectCount() == 0 || selectView->getSelectCount() > 1)
	{
		selectThisObject = idleWorkers[index].front();
	}
	else
	{
		Drawable *selectedDrawable = ((BfmeInGameUISelectView *)TheInGameUI)->getFirstSelectedDrawable();

		BfmeIdleWorkerNode *it = idleWorkers[index].head->next;
		while(it != idleWorkers[index].head)
		{
			Object *itObj = it->object;
			if(itObj == ((BfmeDrawableSelectView *)selectedDrawable)->m_object)
			{
				it = it->next;
				if(it != idleWorkers[index].head)
					selectThisObject = it->object;
				else
					selectThisObject = idleWorkers[index].front();
				break;
			}
			it = it->next;
		}
		if(!selectThisObject)
			selectThisObject = idleWorkers[index].front();
	}
	DEBUG_ASSERTCRASH(selectThisObject, ("InGameUI::selectNextIdleWorker Could not select the next IDLE worker"));
	if(selectThisObject)
	{
		Object *containedBy = ((BfmeObjectSelectView *)selectThisObject)->m_containedBy;
		if(containedBy)
			selectThisObject = containedBy;

		selectView->deselectAllDrawables();
		GameMessage *teamMsg = ((BfmeMessageStreamSelectView *)TheMessageStream)->appendMessage(GameMessage::MSG_CREATE_SELECTED_GROUP);
		teamMsg->appendBooleanArgument(TRUE);
		teamMsg->appendObjectIDArgument(((BfmeObjectSelectView *)selectThisObject)->m_id);
		selectView->selectDrawable(((BfmeObjectSelectView *)selectThisObject)->getDrawable());
		((BfmeTacticalViewSelectView *)TheTacticalView)->lookAt(selectThisObject->getPosition());
	}
}
