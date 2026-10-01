// ?isPausedOrLoading@@YAHXZ
//
// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU reads the bool at +0x6B through
// its own file-local view of the object.
class GameLogic;

extern GameLogic *TheGameLogic;

struct Rva0075B660Logic { char m_pad[0x6b]; bool m_flag; };
struct Rva0075B660State { char m_pad[0x54]; bool m_flag; };
extern Rva0075B660State* TheGameState;

int isPausedOrLoading()
{
	if (((Rva0075B660Logic *)TheGameLogic && ((Rva0075B660Logic *)TheGameLogic)->m_flag) || (TheGameState && TheGameState->m_flag))
		return 1;
	return 0;
}
