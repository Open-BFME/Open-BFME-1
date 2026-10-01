// cl: /DNDEBUG /MD /EHs-c-
//
// Open-BFME5: free stdcall gate at retail 0x0037E810 (79B). Rejects a null
// holder or when candidate equals holder->current; otherwise returns the
// negation of candidate+0xD9 in multiplayer/skirmish (GameLogic mode predicate
// ILT 0x0001E0AB) or candidate+0xDA otherwise.

class BfmeFlagCandidate
{
public:
	char m_pad[0xD9];
	bool m_flagD9;
	bool m_flagDA;
};

struct BfmeFlagHolder
{
	BfmeFlagCandidate *m_current;
};

// TU-local view of the retail GameLogic; the global itself is the canonical
// ?TheGameLogic@@3PAVGameLogic@@A from GameLogic/System/GameLogic.cpp.
class GameLogic;

class GameLogicPortraitShim
{
public:
	bool isInMultiplayerOrSkirmishGame();
};

extern GameLogic *TheGameLogic;

// ?bfmeMpSkirmishFlagGate@@YG_NPAUBfmeFlagHolder@@PAVBfmeFlagCandidate@@@Z
bool __stdcall bfmeMpSkirmishFlagGate(BfmeFlagHolder *holder, BfmeFlagCandidate *candidate)
{
	if (!holder)
		return false;
	if (candidate == holder->m_current)
		return false;
	if (((GameLogicPortraitShim *)TheGameLogic)->isInMultiplayerOrSkirmishGame())
		return !candidate->m_flagD9;
	return !candidate->m_flagDA;
}
