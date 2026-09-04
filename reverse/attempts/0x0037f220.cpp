// ?bfmeMpSkirmishFlagFind@@YGXPAUBfmeFlagPair@@PAUBfmeFlagIter@@PAVBfmeFlagCandidate@@@Z
// partial score=0.72 date=2026-09-04
// cl: /DNDEBUG /MD /EHs-c-
//
// Open-BFME5: linked-list find at retail 0x0037F220 (74B). Walks next-at-+0
// from start until end sentinel or first node whose MP/skirmish flag byte is
// clear (same +0xD9/+0xDA split as bfmeMpSkirmishFlagGate).

class BfmeFlagCandidate
{
public:
	BfmeFlagCandidate *m_next;
	char m_pad4[0xD5];
	bool m_flagD9;
	bool m_flagDA;
};

struct BfmeFlagIter
{
	BfmeFlagCandidate *m_node;
};

struct BfmeFlagPair
{
	BfmeFlagIter m_end;
	BfmeFlagCandidate *m_found;
};

class GameLogicPortraitShim
{
public:
	bool isInMultiplayerOrSkirmishGame();
};

extern GameLogicPortraitShim *TheGameLogic;

static bool bfmeFlagClear(BfmeFlagCandidate *node)
{
	if (TheGameLogic->isInMultiplayerOrSkirmishGame())
		return !node->m_flagD9;
	return !node->m_flagDA;
}

// ?bfmeMpSkirmishFlagFind@@YGXPAUBfmeFlagPair@@PAUBfmeFlagIter@@PAVBfmeFlagCandidate@@@Z
void __stdcall bfmeMpSkirmishFlagFind(BfmeFlagPair *out, BfmeFlagIter *end, BfmeFlagCandidate *start)
{
	BfmeFlagCandidate *node = start;
	for (;;)
	{
		node = node->m_next;
		if (node == end->m_node)
			break;
		if (bfmeFlagClear(node))
			break;
	}
	out->m_end = *end;
	out->m_found = node;
}
