// ?rva003806D0@ExperienceLevelSystem@@QAEPAVExperienceLevel@@PAVExperienceLevelCollection@@ABVAsciiString@@@Z
// partial score=0.88 date=2026-09-10
// Scratch probe for retail 0x003806D0.  This is deliberately outside Code/.
// New lever: use the landed D8-byte ExperienceLevel layout and leave the
// selected level unchanged when its first override has no further link.
// cl: /DNDEBUG /MD /EHsc- /ICode/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

#pragma inline_recursion(on)
#pragma inline_depth(1)

class ExperienceLevelSystem;

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride(void)
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

protected:
	friend class ExperienceLevelSystem;
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class ExperienceLevel
	: public Overridable
{
public:
	unsigned char m_unmodelled_00c[4];
	Int m_requiredExperience;
	unsigned char m_unmodelled_014[0xbd];
	Bool m_singlePlayerOnly;
	Bool m_multiPlayerOnly;
};

struct ExperienceLevelNode
{
	ExperienceLevelNode *m_next;
	ExperienceLevelNode *m_previous;
	ExperienceLevel m_value;
};

class ExperienceLevelCollection
{
public:
	ExperienceLevelNode *m_sentinel;
};

class GameLogic
{
public:
	Bool isInMultiplayerOrSkirmishGame();
};

extern GameLogic *TheBfmeGameLogic;

class ExperienceLevelSystem
{
public:
	ExperienceLevel *findLevel(const AsciiString &name);
	ExperienceLevel *rva003806D0(
		ExperienceLevelCollection *levels, const AsciiString &name);
};

ExperienceLevel *ExperienceLevelSystem::rva003806D0(
	ExperienceLevelCollection *levels, const AsciiString &name)
{
	ExperienceLevel *current;
	Int currentRequiredExperience;
	ExperienceLevelNode *node;
	Int nextRequiredExperience;
	ExperienceLevel *next;
	current = findLevel(name);
	currentRequiredExperience = 0;
	if (current != 0)
		currentRequiredExperience = current->m_requiredExperience;

	node = levels->m_sentinel->m_next;
	nextRequiredExperience = 0x7fffffff;
	next = 0;
	if (node != levels->m_sentinel)
	{
		do
		{
			ExperienceLevel *level = &node->m_value;
			ExperienceLevel *selected = level;
			if (level->m_nextOverride != 0)
			{
				selected = (ExperienceLevel *)
					level->m_nextOverride->friend_getFinalOverride();
			}

			Bool permitted;
			if (TheBfmeGameLogic->isInMultiplayerOrSkirmishGame())
				permitted = !selected->m_singlePlayerOnly;
			else
				permitted = !selected->m_multiPlayerOnly;

			if (permitted &&
				selected->m_requiredExperience > currentRequiredExperience &&
				selected->m_requiredExperience < nextRequiredExperience)
			{
				nextRequiredExperience = selected->m_requiredExperience;
				next = selected;
			}

			node = node->m_next;
		} while (node != levels->m_sentinel);
	}
	return next;
}
