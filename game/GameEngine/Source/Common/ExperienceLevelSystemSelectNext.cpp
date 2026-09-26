// ExperienceLevelSystem::rva003806D0, BFME retail 0x003806D0 (148 bytes).
// The matched gainLevel and bfmeExperienceForNextLevel callers name the
// ExperienceLevelSystem owner.  Their calls pass the borrowed ExperienceLevel
// list and the const AsciiString reference used by this member.
// cl: /DNDEBUG /MD /EHsc- /Igame/Libraries/Source/WWVegas/WWLib
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
	unsigned char m_singlePlayerOnly;
	unsigned char m_multiPlayerOnly;
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

class ExperienceLevelSystem
{
public:
	ExperienceLevel *rva003806D0(
		ExperienceLevelCollection *currentLevels, const AsciiString &levelName);
	ExperienceLevel *findLevel(const AsciiString &levelName);
};

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
			{
				level = static_cast<ExperienceLevel *>(next);
				goto checkLevel;
			}
			level = static_cast<ExperienceLevel *>(const_cast<Overridable *>(
				final->friend_getFinalOverride()));
		}

	checkLevel:
		if ((unsigned char)(((GameLogicShim *)TheBfmeGameLogic)->unidentified_0001e0ab() ?
			!level->m_singlePlayerOnly : !level->m_multiPlayerOnly) != false)
		{
			if (level->m_requiredExperience > threshold &&
				level->m_requiredExperience < bestRequiredExperience)
			{
				bestRequiredExperience = level->m_requiredExperience;
				bestLevel = level;
			}
		}
	}

	return bestLevel;
}
