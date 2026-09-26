// ?doUnitGarrisonNearestBuilding@ScriptActions@@IAEXABVAsciiString@@@Z
// partial score=0.68 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/scriptenginelayout /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"

namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#include "Common/AudioAffect.h"
#include "Common/AudioHandleSpecialValues.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/MapObject.h"
#include "Common/PartitionSolver.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "Common/Radar.h"
#include "Common/SpecialPower.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Team.h"
#include "Common/Upgrade.h"

#include "GameClient/Anim2D.h"
#include "GameClient/CampaignManager.h"
#include "GameClient/CommandXlat.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/Eva.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"
#include "GameClient/GUICallbacks.h"
#include "GameClient/InGameUI.h"
#include "GameClient/LookAtXlat.h"
#include "GameClient/MessageBox.h"
#include "GameClient/Mouse.h"
#include "GameClient/View.h"
#include "GameClient/GlobalLanguage.h"
#include "GameClient/Snow.h"

#include "GameLogic/AI.h"
#include "GameLogic/AISkirmishPlayer.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/CaveContain.h"
#include "GameLogic/Module/CommandButtonHuntUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/DeliverPayloadAIUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Module/TransportContain.h"
#include "GameLogic/Module/MobNexusContain.h"
#include "GameLogic/Module/RailroadGuideAIUpdate.h"
#include "GameLogic/Module/StickyBombUpdate.h"
#include "GameLogic/ObjectTypes.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/ScriptActions.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/VictoryConditions.h"
#include "GameLogic/AIPathfind.h"

class BFMERetailScriptEngineVTable
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

class BfmeObjectModules
{
public:
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }

private:
	unsigned char m_pad00[0x1fc];
	ContainModuleInterface *m_contain;
	unsigned char m_pad200[4];
	AIUpdateInterface *m_ai;
};

class BfmeContainVtbl130
{
public:
#define BFME_CONTAIN_SLOT(n) virtual void containSlot##n() = 0;
	BFME_CONTAIN_SLOT(00) BFME_CONTAIN_SLOT(01) BFME_CONTAIN_SLOT(02)
	BFME_CONTAIN_SLOT(03) BFME_CONTAIN_SLOT(04) BFME_CONTAIN_SLOT(05)
	BFME_CONTAIN_SLOT(06) BFME_CONTAIN_SLOT(07) BFME_CONTAIN_SLOT(08)
	BFME_CONTAIN_SLOT(09) BFME_CONTAIN_SLOT(10) BFME_CONTAIN_SLOT(11)
	BFME_CONTAIN_SLOT(12) BFME_CONTAIN_SLOT(13) BFME_CONTAIN_SLOT(14)
	BFME_CONTAIN_SLOT(15) BFME_CONTAIN_SLOT(16) BFME_CONTAIN_SLOT(17)
	BFME_CONTAIN_SLOT(18) BFME_CONTAIN_SLOT(19) BFME_CONTAIN_SLOT(20)
	BFME_CONTAIN_SLOT(21) BFME_CONTAIN_SLOT(22) BFME_CONTAIN_SLOT(23)
	BFME_CONTAIN_SLOT(24) BFME_CONTAIN_SLOT(25) BFME_CONTAIN_SLOT(26)
	BFME_CONTAIN_SLOT(27) BFME_CONTAIN_SLOT(28) BFME_CONTAIN_SLOT(29)
	BFME_CONTAIN_SLOT(30) BFME_CONTAIN_SLOT(31) BFME_CONTAIN_SLOT(32)
	BFME_CONTAIN_SLOT(33) BFME_CONTAIN_SLOT(34) BFME_CONTAIN_SLOT(35)
	BFME_CONTAIN_SLOT(36) BFME_CONTAIN_SLOT(37) BFME_CONTAIN_SLOT(38)
	BFME_CONTAIN_SLOT(39) BFME_CONTAIN_SLOT(40) BFME_CONTAIN_SLOT(41)
	BFME_CONTAIN_SLOT(42) BFME_CONTAIN_SLOT(43) BFME_CONTAIN_SLOT(44)
	BFME_CONTAIN_SLOT(45) BFME_CONTAIN_SLOT(46) BFME_CONTAIN_SLOT(47)
	BFME_CONTAIN_SLOT(48) BFME_CONTAIN_SLOT(49) BFME_CONTAIN_SLOT(50)
	BFME_CONTAIN_SLOT(51) BFME_CONTAIN_SLOT(52) BFME_CONTAIN_SLOT(53)
	BFME_CONTAIN_SLOT(54) BFME_CONTAIN_SLOT(55) BFME_CONTAIN_SLOT(56)
	BFME_CONTAIN_SLOT(57) BFME_CONTAIN_SLOT(58) BFME_CONTAIN_SLOT(59)
	BFME_CONTAIN_SLOT(60) BFME_CONTAIN_SLOT(61) BFME_CONTAIN_SLOT(62)
	BFME_CONTAIN_SLOT(63) BFME_CONTAIN_SLOT(64) BFME_CONTAIN_SLOT(65)
	BFME_CONTAIN_SLOT(66) BFME_CONTAIN_SLOT(67) BFME_CONTAIN_SLOT(68)
	BFME_CONTAIN_SLOT(69) BFME_CONTAIN_SLOT(70) BFME_CONTAIN_SLOT(71)
	BFME_CONTAIN_SLOT(72) BFME_CONTAIN_SLOT(73) BFME_CONTAIN_SLOT(74)
	BFME_CONTAIN_SLOT(75)
#undef BFME_CONTAIN_SLOT
	virtual PlayerMaskType getPlayerWhoEntered() const = 0;
};

// BFME's partition search returns a ref-counted range through this widened
// manager view, rather than the Zero Hour SimpleObjectIterator declaration.
struct BfmeRangeNode;
struct BfmeRange;

struct BfmeWideResult
{
	void *m_value;
	BfmeWideResult() {}
	BfmeWideResult(const BfmeWideResult &that) : m_value(that.m_value) {}
	~BfmeWideResult();
};

class BfmeWideForwardC
{
	char m_pad[0x0c];
	void *m_source;

public:
	BfmeWideResult bfmeForwardWideC(int a, int b, int c, int d);
};

struct BfmeRangeNode
{
	Object *m_object;
	unsigned int m_pad;
};

struct BfmeRange
{
	BfmeRangeNode *m_begin;
	BfmeRangeNode *m_first;
	BfmeRangeNode *m_end;
	BfmeRangeNode *m_current;
	unsigned int m_refCount;
};

extern void Gen0082E5F0(void *, unsigned int);

__forceinline BfmeWideResult::~BfmeWideResult()
{
	BfmeRange *range = (BfmeRange *)m_value;
	if (!range || --range->m_refCount != 0) {
		return;
	}
	BfmeRangeNode *begin = range->m_begin;
	if (begin) {
		unsigned int bytes = (unsigned int)(((char *)range->m_end -
			(char *)begin) / 8) * 8;
		if (bytes > 0x80) {
			::operator delete(begin);
		} else {
			Gen0082E5F0(begin, bytes);
		}
	}
	::operator delete(range);
}

#pragma comment(linker, "/alternatename:?bfmeForwardWideC@BfmeWideForwardC@@QAE?AUBfmeWideResult@@HHHH@Z=?bfmeForwardWideC@BfmeWideForwardC@@QAE?AUBfmeWideResult@@HHHHH@Z")

extern void d_009f2ae0();

class BfmeFilterLinkCall
{
public:
	PartitionFilter *link(PartitionFilter *next);
};

static __forceinline PartitionFilter *bfmeLinkFilter(PartitionFilter *head,
	PartitionFilter *next)
{
	typedef PartitionFilter *(BfmeFilterLinkCall::*Call)(PartitionFilter *);
	union { void (*raw)(); Call member; } call;
	call.raw = d_009f2ae0;
	return (((BfmeFilterLinkCall *)head)->*call.member)(next);
}

extern void j_00020824();
extern void j_0003251f();

class BfmeThingCall
{
public:
	Bool isKindOf(KindOfType kind) const;
};

static __forceinline Player *bfmeGetControllingPlayer(const Object *object)
{
	typedef Player *(BfmeThingCall::*Call)(void) const;
	union { void (*raw)(); Call member; } call;
	call.raw = j_00020824;
	return (((BfmeThingCall *)object)->*call.member)();
}

static __forceinline Bool bfmeIsKindOf(const Object *object, KindOfType kind)
{
	typedef Bool (BfmeThingCall::*Call)(KindOfType) const;
	union { void (*raw)(); Call member; } call;
	call.raw = j_0003251f;
	return (((BfmeThingCall *)object)->*call.member)(kind);
}

extern ScriptEngine *TheScriptEngine;

#define REALLY_FAR (100000 * MAP_XY_FACTOR)

// ?doUnitGarrisonNearestBuilding@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doUnitGarrisonNearestBuilding(const AsciiString &unitName)
{
	Object *theUnit = ((BFMERetailScriptEngineVTable *)TheScriptEngine)->getUnitNamed(unitName);
	if (!theUnit) {
		return;
	}

	AIUpdateInterface *ai = ((BfmeObjectModules *)theUnit)->getAIUpdateInterface();
	if (!ai) {
		return;
	}

	PartitionFilterAcceptByKindOf f1(MAKE_KINDOF_MASK(KINDOF_STRUCTURE), KINDOFMASK_NONE);
	PartitionFilterSameMapStatus filterMapStatus(theUnit);
	PartitionFilter *filter = bfmeLinkFilter((PartitionFilter *)&f1, &filterMapStatus);
	BfmeWideResult wideResult = ((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
		(int)((char *)theUnit + 0x38), 0x49742400, 2, (int)filter);
	BfmeRange *range = (BfmeRange *)wideResult.m_value;
	++range->m_refCount;

	for (BfmeRangeNode *node = range->m_current; node != range->m_first;
		node = range->m_current) {
		Object *theBuilding = node->m_object;
		range->m_current = node + 1;
		if (!theBuilding) {
			break;
		}
		ContainModuleInterface *contain =
			((BfmeObjectModules *)theBuilding)->getContain();
		if (!contain) {
			DEBUG_CRASH(("doUnitGarrisonNearestBuilding script -- building doesn't have a container."));
			continue;
		}

		PlayerMaskType player =
			((BfmeContainVtbl130 *)contain)->getPlayerWhoEntered();
		if (!((bfmeIsKindOf(theBuilding, KINDOF_STRUCTURE) && player == 0) ||
			(player == bfmeGetControllingPlayer(theUnit)->getPlayerMask()))) {
			continue;
		}

		ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
		ai->aiEnter(theBuilding, CMD_FROM_SCRIPT);
		break;
	}

}
