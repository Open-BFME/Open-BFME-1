// cl: /DNDEBUG /MD /EHs-c-
// Neutral recovery of retail RVA 0x0037F220.
//
// Retail callers enter this member through ILT 0x00041295 with
// TheExperienceLevelSystem in ECX.  They copy one 8-byte iterator aggregate
// by value and reserve a hidden result slot; the returned iterator is copied
// back as the same two-word aggregate.  The receiver is not read by this
// helper, but the member ABI is part of the observed call contract.
//
// The mode query is on TheGameLogic at relocation +0x18, not on
// TheExperienceLevelSystem.  The node's next pointer is followed at +0, and
// the two observed mode flags are at +0xD9 and +0xDA.  The iterator names and
// node view are RVA-specific so they do not claim identity for other
// similarly shaped flag pairs.

class GameLogicPortraitShim
{
public:
	bool isInMultiplayerOrSkirmishGame();
};

extern GameLogicPortraitShim *TheGameLogic;

struct Rva0037F220Node
{
	Rva0037F220Node *m_next;
	char m_record[0xD5];
	bool m_singlePlayerOnly;
	bool m_multiPlayerOnly;
};

struct Rva0037F220Iterator
{
	Rva0037F220Node *m_sentinel;
	Rva0037F220Node *m_current;
};

static bool rva0037F220Clear(Rva0037F220Node *node)
{
	if (TheGameLogic->isInMultiplayerOrSkirmishGame())
		return !node->m_singlePlayerOnly;
	return !node->m_multiPlayerOnly;
}

class ExperienceLevelSystem
{
public:
	Rva0037F220Iterator rva0037F220(Rva0037F220Iterator value);
};

Rva0037F220Iterator ExperienceLevelSystem::rva0037F220(
	Rva0037F220Iterator value)
{
	Rva0037F220Node *node = value.m_current;
	while ((node = node->m_next) != value.m_sentinel->m_next &&
		!rva0037F220Clear(node))
	{
	}
	value.m_current = node;
	return value;
}
