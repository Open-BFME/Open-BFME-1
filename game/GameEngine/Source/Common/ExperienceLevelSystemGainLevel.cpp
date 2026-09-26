// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// BFME retail 0x00381050.  The matched gainLevels loop and the ScriptActions
// UNIT_GAIN_LEVEL caller both name this as
// ExperienceLevelSystem::gainLevel(Object *, Bool).  Object owns its
// ExperienceTracker pointer at +0x210; the tracker's current-level name is the
// real one-pointer AsciiString at +0x08.

#include "ascii_string.h"

typedef bool Bool;

class ExperienceLevel;
// Neutral borrowed circular-list-like collection owned by the system map.
// Its original typedef and element wrapper are not yet established.
class ExperienceLevelCollection;
class Object;

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

	// Address-derived member names state ownership and ABI without inventing
	// semantics.  The first body is already matched; the other two remain
	// generated.
	ExperienceLevelCollection *rva0037F050(Object *object);
	ExperienceLevel *rva003806D0(
		ExperienceLevelCollection *currentLevels, const AsciiString &levelName);
	void rva00380110(ExperienceLevel *level, Object *object,
		Bool showExperienceFX, Bool unknownFlag);
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
