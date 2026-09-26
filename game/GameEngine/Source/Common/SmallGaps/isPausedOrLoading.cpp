// ?isPausedOrLoading@@YAHXZ
struct Rva0075B660Logic { char m_pad[0x6b]; bool m_flag; };
struct Rva0075B660State { char m_pad[0x54]; bool m_flag; };
extern Rva0075B660Logic* TheBfmeGameLogic;
extern Rva0075B660State* TheGameState;
int isPausedOrLoading()
{
	if ((TheBfmeGameLogic && TheBfmeGameLogic->m_flag) || (TheGameState && TheGameState->m_flag))
		return 1;
	return 0;
}
