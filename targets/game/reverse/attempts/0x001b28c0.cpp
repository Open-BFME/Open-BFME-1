// ?addExperiencePoints@ExperienceTracker@@QAEXM_N000@Z
// partial score=0.84 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// readable body of ??0ExperienceTracker@@: Code/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp
// readable body of ?isTrainable@ExperienceTracker@@: Code/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp
// readable body of ?gainExpForLevel@ExperienceTracker@@: Code/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp
// Snapshot supplies the vtable pointer; all three bodies use the same parent at +0x04.

typedef int Int;
typedef float Real;
typedef bool Bool;

class Xfer;
class AsciiString;

template <class T>
class StringBase
{
private:
	friend class AsciiString;

	StringBase(const T *text);
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
};

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
	Bool isKindOf(Int kind) const;

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
class GameLogic
{
public:
	Object *unidentified_0001f253(Int objectID);
	Bool unidentified_0001e0ab();
};

extern GameLogic *TheBfmeGameLogic;

class Rva002EE330PlayerListThunk
{
public:
	Int unidentified_000389f6(Bool includeFields);
};

extern Rva002EE330PlayerListThunk *Rva002EE330ThePlayers;

class GlobalData
{
};

extern GlobalData *TheWritableGlobalData;

class Rva00083240ExperienceScalar
{
public:
	Real unidentified_0002d6c8(Int playerIndex);
	Real unidentified_0000a272(Int playerIndex);
};

// The jump-table targets are known from the retail call sites, but their
// semantic owners are not established in the current ledger.  Keep the
// source calls neutral and route them through the existing five-byte ILTs.
#pragma comment(linker, "/alternatename:?unidentified_0001f253@GameLogic@@QAEPAVObject@@H@Z=?j_0001f253@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_0001e0ab@GameLogic@@QAE_NXZ=?j_0001e0ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_000389f6@Rva002EE330PlayerListThunk@@QAEH_N@Z=?j_000389f6@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_0002d6c8@Rva00083240ExperienceScalar@@QAEMH@Z=?j_0002d6c8@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_0000a272@Rva00083240ExperienceScalar@@QAEMH@Z=?j_0000a272@@YAXXZ")

class ExperienceLevelSystem
{
public:
	Int bfmeExperienceForNextLevel(Object *object, Int *outLevel);
	void unidentified_00380ee0(Object *object, Bool showFeedback);
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

#pragma comment(linker, "/alternatename:?bfmeScaleLivingWorldExperience@ExperienceTracker@@QBEMM@Z=?j_0003de74@@YAXXZ")
#pragma comment(linker, "/alternatename:?unidentified_00380ee0@ExperienceLevelSystem@@QAEXPAVObject@@_N@Z=?j_00007dbf@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Thing@@QBE_NH@Z=?j_0003251f@@YAXXZ")

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
	ExperienceTracker *tracker = this;
	GameLogic *gameLogic = TheBfmeGameLogic;
	Int sinkID = tracker->m_experienceSink;
	while (sinkID != 0)
	{
		Object *sink = gameLogic->unidentified_0001f253(
			sinkID);
		if (sink == 0)
			break;

		experienceGain *= tracker->m_experienceScalar;
		tracker = sink->m_experienceTracker;
		allowLevelGain = true;
		sinkID = tracker->m_experienceSink;
	}

	if (!tracker->isTrainable())
		return;

	Real scaledExperience = experienceGain;
	if (isShared)
	{
		scaledExperience = experienceGain * tracker->m_experienceScalar;
		if (gameLogic->unidentified_0001e0ab())
		{
			const Int playerIndex =
				Rva002EE330ThePlayers->unidentified_000389f6(false);
			if (tracker->m_parent->isKindOf(7))
				scaledExperience *=
					reinterpret_cast<Rva00083240ExperienceScalar *>(
						reinterpret_cast<char *>(TheWritableGlobalData) + 0xee0)
					->unidentified_0002d6c8(playerIndex);
			else
				scaledExperience *=
					reinterpret_cast<Rva00083240ExperienceScalar *>(
						reinterpret_cast<char *>(TheWritableGlobalData) + 0xee0)
					->unidentified_0000a272(playerIndex);
		}
	}

	if (canScaleForBonus)
		scaledExperience =
			tracker->bfmeScaleLivingWorldExperience(scaledExperience);

	tracker->m_currentExperience += scaledExperience;
	TheExperienceLevelSystem->unidentified_00380ee0(
		tracker->m_parent, allowLevelGain);

	(void)provideFeedback;
}
