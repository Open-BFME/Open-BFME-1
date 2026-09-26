// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?onStructureProduced@AIPlayer@@UAEXPAVObject@@0@Z: game/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// AIPlayer::onStructureProduced, 0x00162D30, 613 bytes.
// Identity: slot 8 (+0x20) of the AIPlayer vtable 0x010968B0 (and of the
// AISkirmishPlayer table 0x01096FB0) routes through ILT 0x0002E285 here, and
// the matched Player::onStructureConstructionComplete (0x000C9600) calls that
// slot with (builder, structure), as the Zero Hour twin does. The body is the
// twin minus the script attachment: the Dict keys are the StaticNameKeys at
// VA 0x012A77E8 "objectName", 0x012A77F8 "objectInitialHealth" and
// 0x012A7820 "objectUnsellable", and the debug line appends
// " - Building completed." (VA 0x01096A30) before checkForSupplyCenter.
// BFME clears the two status bits with two separate masks, and the hole
// search after the second findTemplate is gone, leaving isEquivalentTo's
// result unused.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

#define NULL 0

enum NameKeyType { NAMEKEY_INVALID = 0 };

// BFME numbering, as DozerActionDoActionState_update.cpp spells it.
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_RECONSTRUCTING = 21
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class StaticNameKey
{
public:
	NameKeyType key() const;
	operator NameKeyType() const { return key(); }
private:
	mutable NameKeyType m_key;
	const char *m_name;
};

extern const StaticNameKey TheKey_objectName;
extern const StaticNameKey TheKey_objectInitialHealth;
extern const StaticNameKey TheKey_objectUnsellable;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
public:
	Dict(Int numPairsToPreAllocate = 0);
	~Dict() { releaseData(); }
	void setBool(NameKeyType key, Bool value);
	void setInt(NameKeyType key, Int value);
	void setAsciiString(NameKeyType key, const AsciiString &value);
private:
	void releaseData();
	void *m_data;
};

// Native BitFlags over STLport bitset, as Rva00256AE0StatusAttach.cpp and
// docs/shape_levers.md "A three-word flag record may be native BitFlags".
template <int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };
	BitFlags(_dummy_kInit, Int index) { m_bits.set(index); }
private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;
#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
private:
	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName() const { return m_nameString; }
	Bool isEquivalentTo(const ThingTemplate *tt) const;
private:
	unsigned char m_unmodelled008[0x20 - 0x08];
	AsciiString m_nameString;					// +0x20
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		if (!m_template)
			return NULL;
		return (const ThingTemplate *)m_template->getFinalOverride();
	}
	Int getID() const { return m_id; }
	void updateObjValuesFromMapProperties(Dict *properties);
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);
	void clearStatus(const ObjectStatusMaskType &objectStatus) { setStatus(objectStatus, false); }
private:
	void *m_vtable;
	const ThingTemplate *m_template;			// +0x04
	unsigned char m_unmodelled008[0x74 - 0x08];
	Int m_id;						// +0x74
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h
class BuildListInfo
{
public:
	AsciiString getBuildingName() const;
	AsciiString getTemplateName() const;
	BuildListInfo *getNext() const { return m_nextBuildList; }
	Int getHealth() const { return m_health; }
	Bool getUnsellable() const { return m_unsellable; }
	Int getObjectID() const { return m_objectID; }
	// The flag at +0x50 is written through the offset: retail stores a BYTE
	// there (mov byte ptr [esi+0x50],bl), which is the Zero Hour twin's
	// setUnderConstruction(false), while the layout witness names +0x50
	// m_objectTimestamp, a 32-bit field.
	void setUnderConstruction(Bool construction)
	{
		*(Bool *)((char *)this + 0x50) = construction;
	}
private:
	void *m_vtable;
	unsigned char m_unmodelled004[0x2c - 0x04];
	BuildListInfo *m_nextBuildList;				// +0x2C
	unsigned char m_unmodelled030[0x34 - 0x30];
	Int m_health;						// +0x34
	unsigned char m_unmodelled038[0x39 - 0x38];
	Bool m_unsellable;					// +0x39
	unsigned char m_unmodelled03a[0x48 - 0x3a];
	Int m_objectID;						// +0x48
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	BuildListInfo *getBuildList() { return m_pBuildList; }
private:
	unsigned char m_unmodelled000[0x1c0];
	BuildListInfo *m_pBuildList;				// +0x1C0
};

struct GlobalData
{
	char m_unmodelled000[0xa88];
	Int m_debugAI;						// +0xA88
};

extern GlobalData *TheGlobalData;

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	BFME_VIRTUAL_SLOT(00) BFME_VIRTUAL_SLOT(01) BFME_VIRTUAL_SLOT(02)
	BFME_VIRTUAL_SLOT(03) BFME_VIRTUAL_SLOT(04) BFME_VIRTUAL_SLOT(05)
	BFME_VIRTUAL_SLOT(06) BFME_VIRTUAL_SLOT(07) BFME_VIRTUAL_SLOT(08)
	BFME_VIRTUAL_SLOT(09) BFME_VIRTUAL_SLOT(10) BFME_VIRTUAL_SLOT(11)
	BFME_VIRTUAL_SLOT(12) BFME_VIRTUAL_SLOT(13) BFME_VIRTUAL_SLOT(14)
	BFME_VIRTUAL_SLOT(15) BFME_VIRTUAL_SLOT(16) BFME_VIRTUAL_SLOT(17)
	BFME_VIRTUAL_SLOT(18) BFME_VIRTUAL_SLOT(19) BFME_VIRTUAL_SLOT(20)
	BFME_VIRTUAL_SLOT(21) BFME_VIRTUAL_SLOT(22) BFME_VIRTUAL_SLOT(23)
	BFME_VIRTUAL_SLOT(24) BFME_VIRTUAL_SLOT(25) BFME_VIRTUAL_SLOT(26)
	BFME_VIRTUAL_SLOT(27) BFME_VIRTUAL_SLOT(28)
	// vtable 0x010E7A30 slot 29 (+0x74) -> ILT 0x00031F25 -> body 0x00349730
	virtual void rva00349730(Object *obj, const AsciiString &name);

	void AppendDebugMessage(const AsciiString &strToAdd, Bool mustAdd);
};
#undef BFME_VIRTUAL_SLOT

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	virtual void onStructureProduced(Object *factory, Object *bldg);
protected:
	void checkForSupplyCenter(BuildListInfo *info, Object *bldg);
private:
	unsigned char m_unmodelled004[0x0c - 0x04];
	Player *m_player;					// +0x0C
	unsigned char m_unmodelled010[0x20 - 0x10];
	Int m_buildDelay;					// +0x20
	Int m_teamDelay;					// +0x24
};

void AIPlayer::onStructureProduced(Object *factory, Object *bldg)
{
	m_teamDelay = 0;
	m_buildDelay = 0;
	BuildListInfo *info;
	for (info = m_player->getBuildList(); info; info = info->getNext())
	{
		if (info->getObjectID() != bldg->getID())
			continue;
		Dict d;
		d.setAsciiString(TheKey_objectName, info->getBuildingName());
		d.setInt(TheKey_objectInitialHealth, info->getHealth());
		d.setBool(TheKey_objectUnsellable, info->getUnsellable());

		info->setUnderConstruction(false);
		bldg->updateObjValuesFromMapProperties(&d);
		bldg->clearStatus(MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_UNDER_CONSTRUCTION));
		bldg->clearStatus(MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_RECONSTRUCTING));

		TheScriptEngine->rva00349730(bldg, AsciiString(""));
		if (TheGlobalData->m_debugAI)
		{
			AsciiString bldgName = bldg->getTemplate()->getName();
			// StringBase<char>::concat(const char *, int) at 0x00887D60, length folded.
			((StringBase<char> *)&bldgName)->concat(" - Building completed.", 22);
			TheScriptEngine->AppendDebugMessage(bldgName, false);
		}
		checkForSupplyCenter(info, bldg);
		return;
	}

	for (info = m_player->getBuildList(); info; info = info->getNext())
	{
		const ThingTemplate *bldgPlan = TheThingFactory->findTemplate(info->getTemplateName());
		if (!bldgPlan)
			continue;
		if (!bldgPlan->isEquivalentTo(bldg->getTemplate()))
			continue;
	}
}
