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
class BfmeInfoBW;
class BfmeAgentBW;
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
	// generated.  The query and award helpers are the matched ledger rows
	// ?bfmeQuery0037F050@ExperienceLevelSystem@@QAEPAXPAX@Z (0x0037F050) and
	// ?bfmeAwardBW@ExperienceLevelSystem@@QAEXPAVBfmeInfoBW@@PAVBfmeAgentBW@@PAXD@Z
	// (0x00380110); both are non-owning thiscall members reached through the
	// normal 5-byte ILT entries, so the respelled calls keep the same ECX
	// receiver and push sequence (pointer-sized first args; the bool/char
	// flag slots both push one dword).
	void *bfmeQuery0037F050(void *record);
	ExperienceLevel *rva003806D0(
		ExperienceLevelCollection *currentLevels, const AsciiString &levelName);
	void bfmeAwardBW(BfmeInfoBW *info, BfmeAgentBW *agent, void *extra,
		char bonus);
};

// ?gainLevel@ExperienceLevelSystem@@QAEXPAVObject@@_N@Z
void ExperienceLevelSystem::gainLevel(
	Object *object, Bool showExperienceFX)
{
	ExperienceLevelCollection *currentLevels =
		(ExperienceLevelCollection *)bfmeQuery0037F050((void *)object);
	if (currentLevels == 0)
		return;

	AsciiString levelName =
		object->getExperienceTracker()->getCurrentLevelName();
	ExperienceLevel *nextLevel = rva003806D0(currentLevels, levelName);
	if (nextLevel != 0)
	{
		// Retail pushes this flag's 4-byte incoming slot as-is (mov ecx,[..] /
		// push ecx, no test/setne), the same raw-dword passthrough the matched
		// bfmeAwardBW body documents with its RawBool union.  A Bool local
		// would materialise a byte copy here, so read the slot as a dword.
		bfmeAwardBW((BfmeInfoBW *)nextLevel, (BfmeAgentBW *)object,
			*(void **)&showExperienceFX, (char)false);
	}
}
