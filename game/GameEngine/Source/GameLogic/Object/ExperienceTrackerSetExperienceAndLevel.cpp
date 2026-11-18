// stlport
// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/Common/Thing /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?setExperienceAndLevel@ExperienceTracker@@: game/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp
// Snapshot supplies the vtable pointer; parent is at +0x04.
// Zero Hour's tail-recursive experience-sink forwarding, which MSVC turns
// into the retail sink loop, followed by BFME's level-system update and
// scalar-table refresh.

#include "../../../Include/Common/ScalarTypes.h"



class Xfer;
class AsciiString;

#include "ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

private:
	void *m_vtable;
	Overridable *m_nextOverride;

	friend class Thing;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:

private:
	unsigned char m_unreconstructed_008[0x487 - 0x008];
	Bool m_isTrainable;

	friend class ThingTemplateRef;
	friend class ExperienceTracker;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const;
	Bool isKindOf(enum KindOfType kind) const;

protected:
	virtual ~Thing();

private:
	const ThingTemplate *m_template;
};

inline const ThingTemplate *Thing::getTemplate() const
{
	const ThingTemplate *const volatile *templateSlot = &m_template;
	const ThingTemplate *thingTemplate = *templateSlot;
	if (thingTemplate == 0)
		return 0;
	if (thingTemplate->m_nextOverride)
		thingTemplate = static_cast<const ThingTemplate *>(
			thingTemplate->m_nextOverride->getFinalOverride());
	return thingTemplate;
}

class ExperienceTracker;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	unsigned char m_unreconstructed[0x210 - 0x08];
	ExperienceTracker *m_experienceTracker;
};

#define BFME_GAMELOGIC_LOOKUP_VISIBLE
#include "GameLogicObjectLookup.h"

extern GameLogic *TheGameLogic;

// 0x00380EE0 (via ILT 0x00007DBF): __thiscall, RET 8, integer EAX result.
class ExperienceLevelSystem
{
public:
	Int rva00380EE0(Object *object, Bool showFeedback);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

class BfmeThingEFE
{
public:
	Real bfmeAt(Int count) const;

private:
	void *m_vtable;
	ExperienceTracker *m_tracker;
	Real m_scalar;
	Int m_baseCount;
	void *m_vec;

	friend class ExperienceTracker;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

// Reference interface: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ExperienceTracker.h; BFME field widths and offsets follow retail constructor stores.
class ExperienceTracker : public Snapshot
{
public:
	ExperienceTracker(Object *parent);
	virtual ~ExperienceTracker();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

	__forceinline Bool isTrainable() const;
	void setExperienceAndLevel(Real experienceIn, Bool provideFeedback);

private:
	Object *m_parent;
	AsciiString m_levelName;
	Real m_currentExperience;
	Int m_currentLevel;
	Int m_unknown14;
	Int m_experienceSink;
	Real m_experienceScalar;
	Int m_unknown20;
	bool m_unknown24;
	unsigned char m_padding25[3];
	Int m_scalarIndex;
	BfmeThingEFE *m_scalarTable;
};

// ?isTrainable@ExperienceTracker@@QBE_NXZ
__forceinline Bool ExperienceTracker::isTrainable() const
{
	return m_parent->getTemplate()->m_isTrainable;
}

// ?setExperienceAndLevel@ExperienceTracker@@QAEXM_N@Z
// Retail 0x001B26D0 (137 bytes); the ILT thunk 0x000326F5 confirms this
// decorated name. Zero Hour's body forwards to the sink tracker; BFME then
// asks the level system and refreshes the scalar table on a level change.
void ExperienceTracker::setExperienceAndLevel(Real experienceIn, Bool provideFeedback)
{
	if (m_experienceSink != 0)
	{
		// I have been set up to give my experience to someone else
		Object *sinkPointer = TheGameLogic->findObjectByID(m_experienceSink);
		if (sinkPointer)
		{
			sinkPointer->m_experienceTracker->setExperienceAndLevel(experienceIn, provideFeedback);
			return;
		}
	}

	Object *parent = m_parent;
	if (!parent->getTemplate()->m_isTrainable)
		return; //safety

	m_currentExperience = experienceIn;

	Int levelIndex = TheExperienceLevelSystem->rva00380EE0(parent, true);
	if (provideFeedback && levelIndex != 0)
	{
		BfmeThingEFE *table = m_scalarTable;
		if (levelIndex != table->m_baseCount)
		{
			table->m_baseCount = levelIndex;
			table->m_scalar = table->bfmeAt(levelIndex);
		}
	}
}
