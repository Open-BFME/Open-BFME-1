// ?rva00380EE0@ExperienceLevelSystem@@QAEHPAVObject@@_N@Z
// partial score=0.84 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00380EE0, 284 bytes.  The existing ExperienceTracker
// addExperiencePoints body at 0x001B28C0 loads TheExperienceLevelSystem and
// reaches this body through ILT 0x00007DBF.  The surrounding matched
// ExperienceLevelSystem methods and the 0x003806D0/0x0037FE30 callees prove
// the owner and ABI; the method name remains address-derived because no
// direct caller supplies a source-level name for this particular operation.
//
// The body has one ordinary 284-byte boundary.  Its tail at +0xFE is the
// no-level path, which returns the tracker's scalar/index field at +0x28; it
// is not a separate function or a guessed compiler funclet.

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

	Int getScalarIndex() const
	{
		return m_scalarIndex;
	}

private:
	void *m_vtable;
	void *m_parent;
	AsciiString m_currentLevelName;
	Real m_currentExperience;
	Int m_currentLevel;
	Int m_unknown14;
	Int m_experienceSink;
	Real m_experienceScalar;
	Int m_unknown20;
	Bool m_unknown24;
	unsigned char m_padding25[3];
	Int m_scalarIndex;
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

class ExperienceLevel
{
public:
	Int getRequiredExperience() const
	{
		return m_requiredExperience;
	}

	Int getRank() const
	{
		return m_rank;
	}

private:
	unsigned char m_unmodelled_000[0x10];
	Int m_requiredExperience;
	unsigned char m_unmodelled_014[0xb8];
	Int m_rank;
};

class ExperienceLevelSystem
{
public:
	void *bfmeQuery0037F050(void *object);
	ExperienceLevel *rva003806D0(
		ExperienceLevelCollection *levels, const AsciiString &name);
	Int rva00380EE0(Object *object, Bool showFeedback);
};

class Arg1;
class ObjectView;

class Rva0037FE30
{
public:
	void record(Arg1 *level, ObjectView *object, Bool showFeedback);
};

// ?rva00380EE0@ExperienceLevelSystem@@QAEHPAVObject@@_N@Z
Int ExperienceLevelSystem::rva00380EE0(Object *object, Bool showFeedback)
{
	ExperienceLevelSystem *system = this;
	ExperienceLevelCollection *levels =
		(ExperienceLevelCollection *)system->bfmeQuery0037F050(object);
	if (levels == 0)
		return 0;

	Int currentExperience =
		(Int)object->getExperienceTracker()->getCurrentExperience();
	AsciiString levelName =
		object->getExperienceTracker()->getCurrentLevelName();
	ExperienceLevel *level = system->rva003806D0(
		levels, levelName);
	ExperienceLevel *selectedLevel = 0;
	if (level == 0)
	{
	}
	else if (currentExperience < level->getRequiredExperience())
	{
	}
	else
	{
		((Rva0037FE30 *)system)->record(
			(Arg1 *)level, (ObjectView *)object, showFeedback);
		selectedLevel = level;
	}
	if (selectedLevel != 0)
		return selectedLevel->getRank();
	return object->getExperienceTracker()->getScalarIndex();
}
