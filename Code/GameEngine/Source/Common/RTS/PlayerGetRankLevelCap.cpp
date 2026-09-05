// cl: /DNDEBUG /MD /EHsc
// Retail 0x000CBDC0: rank-level cap for a Player. Local living-world campaign
// uses min(Rva003BCC10::current, RankInfoStore::getRankLevelCount). Otherwise
// min of the player-template cap (+0xC4 for modes 2/1/5, +0xC8 else) and the
// rank count. Descriptive BFME-only name; not ZH getRankLevel.

typedef int Int;
typedef bool Bool;

class RankInfoStore
{
public:
	Int getRankLevelCount(void) const;
};

class GameLogic
{
public:
	Bool _bfme_isInLivingWorldCampaign(void);
	char m_pad[0x10c];
	Int m_gameMode;
};

class Rva003BCC10
{
public:
	Int current(void);
};

class PlayerTemplate
{
public:
	char m_pad[0xc4];
	Int m_capModes125;
	Int m_capOtherModes;
};

class PlayerList
{
public:
	char m_pad[0x0c];
	class Player *m_local;
};

class Player
{
public:
	Int getRankLevelCap(void);

	char m_pad00[4];
	PlayerTemplate *m_playerTemplate;
};

extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
extern RankInfoStore *TheRankInfoStore;
extern Rva003BCC10 *TheLivingWorldLogic;

Int Player::getRankLevelCap(void)
{
	PlayerList *list = ThePlayerList;
	Int slot[2];

	if (this == list->m_local && TheGameLogic->_bfme_isInLivingWorldCampaign())
	{
		slot[1] = TheRankInfoStore->getRankLevelCount();
		slot[0] = TheLivingWorldLogic->current();
		return *((slot[0] < slot[1]) ? &slot[0] : &slot[1]);
	}

	if (m_playerTemplate)
	{
		Int mode = TheGameLogic->m_gameMode;
		if (mode == 2 || mode == 1 || mode == 5)
		{
			slot[0] = TheRankInfoStore->getRankLevelCount();
			slot[1] = m_playerTemplate->m_capModes125;
		}
		else
		{
			slot[0] = TheRankInfoStore->getRankLevelCount();
			slot[1] = m_playerTemplate->m_capOtherModes;
		}
		return *((slot[1] < slot[0]) ? &slot[1] : &slot[0]);
	}

	return TheRankInfoStore->getRankLevelCount();
}
