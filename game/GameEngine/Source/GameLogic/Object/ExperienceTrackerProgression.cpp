// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ??0ExperienceTracker@@: game/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp
// readable body of ?isTrainable@ExperienceTracker@@: game/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp
// readable body of ?gainExpForLevel@ExperienceTracker@@: game/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp
// Snapshot supplies the vtable pointer; all three bodies use the same parent at +0x04.

typedef int Int;
typedef float Real;
typedef bool Bool;

class Xfer;
class AsciiString;

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

private:
	void *m_vtable;
	Overridable *m_nextOverride;

	friend class Thing;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isTrainable() const
	{
		return m_isTrainable;
	}

private:
	unsigned char m_unreconstructed_008[0x487 - 0x008];
	Bool m_isTrainable;

	friend class ThingTemplateRef;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const;

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
};

class ExperienceTracker;

class ExperienceLevelSystem
{
public:
	Int bfmeExperienceForNextLevel(Object *object, Int *outLevel);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;


class BfmeThingEFE
{
public:
	BfmeThingEFE(ExperienceTracker *tracker);

private:
	unsigned char m_data[0x14];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

// Reference interface: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ExperienceTracker.h; BFME field widths and offsets follow retail constructor stores.
class ExperienceTracker : public Snapshot
{
public:
	ExperienceTracker(Object *parent);
	virtual ~ExperienceTracker();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

	Bool isTrainable() const;
	Bool gainExpForLevel(
		Int levelsToGain,
		Bool canScaleForBonus,
		Bool provideFeedback);

	void addExperiencePoints(
		Real experienceGain,
		Bool canScaleForBonus,
		Bool isShared,
		Bool allowLevelGain,
		Bool provideFeedback);


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
	BfmeThingEFE *m_helper;
};

// ??0ExperienceTracker@@QAE@PAVObject@@@Z
ExperienceTracker::ExperienceTracker(Object *parent) :
	m_parent(parent),
	m_levelName(""),
	m_currentExperience(0.0f),
	m_currentLevel(0),
	m_unknown14(-1),
	m_experienceSink(0),
	m_experienceScalar(1.0f),
	m_unknown20(0),
	m_unknown24(false),
	m_scalarIndex(0),
	m_helper(0)
{
	m_helper = new BfmeThingEFE(this);
}

// ?isTrainable@ExperienceTracker@@QBE_NXZ
Bool ExperienceTracker::isTrainable() const
{
	return m_parent->getTemplate()->isTrainable();
}

Bool ExperienceTracker::gainExpForLevel(
	Int levelsToGain,
	Bool canScaleForBonus,
	Bool provideFeedback)
{
	const Int levelCount = levelsToGain;
	if (levelCount <= 0)
		return false;

	Bool gainedLevel = false;
	Int i = 0;
	while (i < levelCount)
	{
		Int experience = TheExperienceLevelSystem->
			bfmeExperienceForNextLevel(m_parent, 0);
		if (experience <= 0)
			break;
		addExperiencePoints(
			experience,
			false,
			false,
			canScaleForBonus,
			provideFeedback);
		++i;
		gainedLevel = true;
	}

	return gainedLevel;
}
