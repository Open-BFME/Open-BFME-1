// cl: /DNDEBUG /MD /EHsc

#include <stdio.h>
#include <string.h>

struct Gen_0052B440GameLogic
{
	unsigned char m_unmodelled[0x10C];
	int m_gameMode;
};

class Gen_0052B440
{
public:
	void bfmeProvide(const char *selector, void *value, bool setting);

private:
	unsigned char m_unmodelled[0x258];
	void **m_playersBegin;
	void **m_playersEnd;
	void **m_playersLimit;
	int m_screenType;
};

enum
{
	BFME_NUM_OF_PLAYERS = 0,
	BFME_IN_SKIRMISH = 1,
	BFME_PLAYER_STATUS = 1,
	BFME_GAME_SKIRMISH = 2
};

// The Objectives/PlayerStatus constructor at 0x0052C660 binds ILT 0x00025B08
// for the two-entry { NumOfPlayers, InSkirmish } provider table.  Its retail
// method spelling is not exposed, so the class and method remain surrogates.
// ?bfmeProvide@Gen_0052B440@@QAEXPBDPAX_N@Z
void Gen_0052B440::bfmeProvide(const char *selector, void *value, bool setting)
{
	char *output = (char *)value;
	output[0] = '0';
	output[1] = '\0';

	switch ((int)selector)
	{
	case BFME_NUM_OF_PLAYERS:
		if (!setting && m_screenType == BFME_PLAYER_STATUS)
			sprintf(output, "%d", m_playersEnd - m_playersBegin);
		break;

	case BFME_IN_SKIRMISH:
		if (!setting)
		{
			Gen_0052B440GameLogic *gameLogic =
				*(Gen_0052B440GameLogic **)0x012F0898;
			strcpy(output,
				gameLogic && gameLogic->m_gameMode == BFME_GAME_SKIRMISH ? "1" : "0");
		}
		break;
	}
}
