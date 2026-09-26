// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// ExperienceLevelSystem::bfmeExperienceForNextLevel, retail 0x00381100.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

class ExperienceLevelCollection;
class ExperienceLevel;

class ExperienceTracker
{
public:
	const AsciiString &getCurrentLevelName() const
	{
		return m_currentLevelName;
	}

	Real getCurrentExperience() const
	{
		return m_currentExperience;
	}

private:
	void *m_vtable;
	void *m_parent;
	AsciiString m_currentLevelName;
	Real m_currentExperience;
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
	void *bfmeQuery0037F050(void *object);
	ExperienceLevel *rva003806D0(
		ExperienceLevelCollection *levels, const AsciiString &name);
	Int bfmeExperienceForNextLevel(Object *object, Int *outLevel);
};

struct ExperienceLevelFields
{
	unsigned char m_unmodelled_000[0x10];
	Int m_requiredExperience;
	unsigned char m_unmodelled_014[0xb8];
	Int m_rank;
};

// ?bfmeExperienceForNextLevel@ExperienceLevelSystem@@QAEHPAVObject@@PAH@Z
Int ExperienceLevelSystem::bfmeExperienceForNextLevel(
	Object *object, Int *outLevel)
{
	ExperienceLevelCollection *levels = (ExperienceLevelCollection *)
		bfmeQuery0037F050(object);
	if (levels == 0)
		return 0;

	AsciiString levelName = object->getExperienceTracker()->getCurrentLevelName();
	ExperienceLevelFields *level = (ExperienceLevelFields *)
		rva003806D0(levels, levelName);
	if (level == 0)
		return 0;

	Int currentExperience = (Int)
		object->getExperienceTracker()->getCurrentExperience();
	if (outLevel != 0)
		*outLevel = level->m_rank;
	return level->m_requiredExperience - currentExperience;
}
