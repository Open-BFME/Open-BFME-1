// stlport
// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/Common/Thing /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?addExperiencePoints@ExperienceTracker@@: game/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp
// Snapshot supplies the vtable pointer; parent is at +0x04.
// Recursive experience-sink forwarding with BFME shared-experience scaling.

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
	Bool isTrainable() const
	{
		return m_isTrainable;
	}

private:
	unsigned char m_unreconstructed_008[0x487 - 0x008];
	Bool m_isTrainable;

	friend class ThingTemplateRef;
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

// The BFME five-argument path uses the game-logic and player-list ILTs
// directly.  These names describe only the observed call ABI; they do not
// claim ownership of the unresolved retail bodies behind those thunks.
#define BFME_GAMELOGIC_LOOKUP_VISIBLE
#include "GameLogicObjectLookup.h"
class GameLogicPortraitShim {
public:
 bool isInMultiplayerOrSkirmishGame();
};

extern GameLogic *TheGameLogic;

class PlayerList
{
public:
	Int unidentified_000df510(Bool includeFields);
};

extern PlayerList *ThePlayerList;

class GlobalData
{
};

extern GlobalData *TheWritableGlobalData;

class Gen_00083240
{
public:
	Real bfmeGet100(Int playerIndex) const;
	Real bfmeGet80(Int playerIndex) const;
};

// 0x00380EE0 (via ILT 0x00007DBF): __thiscall, RET 8, integer EAX result;
// Its integer result is ignored; full retail body returns that integer.

class ExperienceLevelSystem
{
public:
	Int bfmeExperienceForNextLevel(Object *object, Int *outLevel);
	Int rva00380EE0(Object *object, Bool showFeedback);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;


class BfmeThingEFE
{
public:
	BfmeThingEFE(ExperienceTracker *tracker);

private:
	unsigned char m_data[0x14];
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
	Real bfmeScaleLivingWorldExperience(Real amount) const;


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


// ?isTrainable@ExperienceTracker@@QBE_NXZ
__forceinline Bool ExperienceTracker::isTrainable() const
{
	return m_parent->getTemplate()->isTrainable();
}

// ?addExperiencePoints@ExperienceTracker@@QAEXM_N000@Z
// Retail overload reached through ILT 0x00010096.  The sink walk, shared
// experience scaling, and final level-system notification follow the
// five-argument BFME call sites; provideFeedback is intentionally unused by
// this retail body.
void ExperienceTracker::addExperiencePoints(
	Real experienceGain,
	Bool canScaleForBonus,
	Bool isShared,
	Bool allowLevelGain,
	Bool provideFeedback)
{
	GameLogic *gameLogic = TheGameLogic;
	if (m_experienceSink != 0)
	{
		Object *sink = gameLogic->findObjectByID(m_experienceSink);
		if (sink != 0)
		{
			sink->m_experienceTracker->addExperiencePoints(
				experienceGain * m_experienceScalar, canScaleForBonus,
				isShared, true, provideFeedback);
			return;
		}
	}

	if (!isTrainable())
		return;

	Real scaledExperience = experienceGain;
	if (isShared)
	{
		scaledExperience = experienceGain * m_experienceScalar;
		if (((GameLogicPortraitShim *)gameLogic)->isInMultiplayerOrSkirmishGame())
		{
			const Int playerIndex =
				ThePlayerList->unidentified_000df510(false);
			if (m_parent->isKindOf((KindOfType)7))
				scaledExperience *=
					reinterpret_cast<Gen_00083240 *>(
						reinterpret_cast<char *>(TheWritableGlobalData) + 0xee0)
					->bfmeGet100(playerIndex);
			else
				scaledExperience *=
					reinterpret_cast<Gen_00083240 *>(
						reinterpret_cast<char *>(TheWritableGlobalData) + 0xee0)
					->bfmeGet80(playerIndex);
		}
	}

	if (canScaleForBonus)
		scaledExperience =
			bfmeScaleLivingWorldExperience(scaledExperience);

	m_currentExperience += scaledExperience;
	TheExperienceLevelSystem->rva00380EE0(
		m_parent, allowLevelGain);

	(void)provideFeedback;
}
