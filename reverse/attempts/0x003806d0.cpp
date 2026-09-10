// ?rva003806D0@ExperienceLevelSystem@@QAEPAVExperienceLevel@@PAVExperienceLevelCollection@@ABVAsciiString@@@Z
// partial score=0.94 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// BFME retail 0x00381050.  The matched gainLevels loop and the ScriptActions
// UNIT_GAIN_LEVEL caller both name this as
// ExperienceLevelSystem::gainLevel(Object *, Bool).  Object owns its
// ExperienceTracker pointer at +0x210; the tracker's current-level name is the
// real one-pointer AsciiString at +0x08.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

class Object;

class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride();

	Overridable *friend_getNextOverride()
	{
		return m_nextOverride;
	}

	const Overridable *friend_getNextOverride() const
	{
		return m_nextOverride;
	}

	const Overridable *friend_getFinalOverride() const;

	public:
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class ExperienceLevel : public Overridable
{
public:
	AsciiString m_name;
	Int m_requiredExperience;
	unsigned char m_unmodelled_014[0xbd];
	Bool m_singlePlayerOnly;
	Bool m_multiPlayerOnly;
	unsigned char m_unmodelled_0d3[5];

};

typedef char ExperienceLevelSizeMustBeD8[
	sizeof(ExperienceLevel) == 0xd8 ? 1 : -1];

class ExperienceLevelCollection : public _STL::list<ExperienceLevel>
{
};

struct Rva00367E30Logic;

class GameLogicShim
{
public:
	Bool unidentified_0001e0ab();
};

extern Rva00367E30Logic *TheBfmeGameLogic;

static Bool experienceLevelIsAvailable(ExperienceLevel *level)
{
	if (((GameLogicShim *)TheBfmeGameLogic)->unidentified_0001e0ab())
		return !level->m_singlePlayerOnly;
	return !level->m_multiPlayerOnly;
}

class ExperienceTracker
{
public:
	const AsciiString &getCurrentLevelName() const
	{
		return m_currentLevelName;
	}

private:
	void *m_vtable;
	Object *m_parent;
	AsciiString m_currentLevelName;
};

class Object
{
public:
	ExperienceTracker *getExperienceTracker() const
	{
		return m_experienceTracker;
	}

private:
	unsigned char m_unmodelled_000[0x210];
	ExperienceTracker *m_experienceTracker;
};

class ExperienceLevelSystem
{
public:
	void gainLevel(Object *object, Bool showExperienceFX);

	ExperienceLevelCollection *rva0037F050(Object *object);
	ExperienceLevel *rva003806D0(
		ExperienceLevelCollection *currentLevels, const AsciiString &levelName);
	void rva00380110(ExperienceLevel *level, Object *object,
		Bool showExperienceFX, Bool unknownFlag);
	ExperienceLevel *findLevel(const AsciiString &levelName);
};

// ?gainLevel@ExperienceLevelSystem@@QAEXPAVObject@@_N@Z
void ExperienceLevelSystem::gainLevel(
	Object *object, Bool showExperienceFX)
{
	ExperienceLevelCollection *currentLevels = rva0037F050(object);
	if (currentLevels == 0)
		return;

	AsciiString levelName =
		object->getExperienceTracker()->getCurrentLevelName();
	ExperienceLevel *nextLevel = rva003806D0(currentLevels, levelName);
	if (nextLevel != 0)
	{
		Bool feedback = showExperienceFX;
		rva00380110(nextLevel, object, feedback, false);
	}
}

// ?rva003806D0@ExperienceLevelSystem@@QAEPAVExperienceLevel@@PAVExperienceLevelCollection@@ABVAsciiString@@@Z
ExperienceLevel *ExperienceLevelSystem::rva003806D0(
	ExperienceLevelCollection *currentLevels, const AsciiString &levelName)
{
	ExperienceLevel *currentLevel = findLevel(levelName);
	Int threshold = 0;
	if (currentLevel != 0)
		threshold = currentLevel->m_requiredExperience;

	ExperienceLevel *bestLevel = 0;
	Int bestRequiredExperience = 0x7fffffff;
	for (ExperienceLevelCollection::iterator levelIt = currentLevels->begin();
		levelIt != currentLevels->end(); ++levelIt)
	{
		ExperienceLevel *level = &(*levelIt);
		Overridable *next = level->friend_getNextOverride();
		if (next != 0)
		{
			const Overridable *final = next->friend_getNextOverride();
			if (final == 0)
				goto checkLevel;
			level = static_cast<ExperienceLevel *>(const_cast<Overridable *>(
				final->friend_getFinalOverride()));
		}

	checkLevel:
		if (experienceLevelIsAvailable(level) &&
			level->m_requiredExperience > threshold &&
			level->m_requiredExperience < bestRequiredExperience)
		{
			bestRequiredExperience = level->m_requiredExperience;
			bestLevel = level;
		}
	}

	return bestLevel;
}
