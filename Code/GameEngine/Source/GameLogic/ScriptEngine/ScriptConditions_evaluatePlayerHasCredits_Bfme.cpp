// cl: /DNDEBUG /MD
// Open-BFME5: BFME player-mask reconstruction of evaluatePlayerHasCredits.

typedef bool Bool;
typedef unsigned short PlayerMaskType;
typedef unsigned int UnsignedInt;

class Parameter
{
public:
	int getInt() const { return m_int; }
	char m_pad00[8];
	int m_int;
};

class Money
{
public:
	virtual void unused();

	UnsignedInt countMoney() const { return m_money; }

private:
	UnsignedInt m_money;
	int m_playerIndex;
};

class Player
{
public:
	Money *getMoney() { return &m_money; }

private:
	char m_pad00[0x48];
	Money m_money;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class ScriptEngine
{
public:
	PlayerMaskType unidentified_0034DB40(Parameter *parameter);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
	Bool evaluatePlayerHasCredits(Parameter *creditsParm,
		Parameter *comparisonParm, Parameter *playerParm);
};

// ?evaluatePlayerHasCredits@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerHasCredits(Parameter *creditsParm,
	Parameter *comparisonParm, Parameter *playerParm)
{
	PlayerMaskType playerMask =
		TheScriptEngine->unidentified_0034DB40(playerParm);
	int totalMoney = 0;
	while (playerMask)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (player)
		{
			if (player->getMoney())
				totalMoney += player->getMoney()->countMoney();
		}
	}

	int comparison = comparisonParm->getInt();
	Bool result = false;
	switch (comparison)
	{
	case 0: result = creditsParm->m_int < totalMoney; break;
	case 1: result = creditsParm->m_int <= totalMoney; break;
	case 2: result = creditsParm->m_int == totalMoney; break;
	case 3: result = creditsParm->m_int >= totalMoney; break;
	case 4: result = creditsParm->m_int > totalMoney; break;
	case 5: result = creditsParm->m_int != totalMoney; break;
	}
	return result;
}
