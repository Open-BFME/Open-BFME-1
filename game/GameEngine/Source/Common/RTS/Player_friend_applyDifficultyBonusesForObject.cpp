// cl: /DNDEBUG /MD /EHsc
// BFME's difficulty bonus is an AI-upgrade grant, not ZH's health/weapon-bonus
// pair. Object::setReceivingDifficultyBonus (matched) calls this through the
// ILT at 0x0002278C, which lands on 0x000CE560.

typedef bool Bool;

enum GameDifficulty
{
	DIFFICULTY_EASY = 0,
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

NameKeyType NAMEKEY(const char *name);

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	void set(const char *text);
	const char *str() const { return m_data ? m_data + 8 : ""; }

private:
	const char *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
// BFME's PlayerTemplate FieldParse table (0x00C847E0) puts PlayableSide at +0xBD.
class PlayerTemplate
{
public:
	Bool isPlayableSide() const { return m_playableSide; }

	unsigned char m_unreconstructed[0xBD];
	Bool m_playableSide;					///< retail this+0xBD
};

class AIPlayer
{
public:
	GameDifficulty getAIDifficulty() const;
};

class Player;
class UpgradeTemplate;

class Object
{
public:
	Bool bfmeIsComputerControlled() const;
	Player *getControllingPlayer() const;
	void giveUpgrade(const UpgradeTemplate *upgrade);
};

class GameLogic
{
public:
	Bool _bfme_isInMultiplayerOrSkirmishGame();

	unsigned char m_unreconstructed[0x9C];
	GameDifficulty m_gameDifficulty;				///< retail this+0x9C, stored by matched GameLogic::prepareNewGame
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgradeByKey(NameKeyType key) const;
};

extern GameLogic *TheGameLogic;
extern UpgradeCenter *TheUpgradeCenter;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
// BFME m_playerTemplate at +0x04 and m_ai at +0x220.
class Player
{
public:
	void friend_applyDifficultyBonusesForObject(Object *obj, Bool apply);

	// Zero Hour Player.h's inline accessor. Reading the template through it,
	// rather than the member directly, is what gives retail's allocation:
	// this in EDI and the Object in ESI.
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }

	void *m_vtable;
	const PlayerTemplate *m_playerTemplate;			///< retail this+0x04
	unsigned char m_unreconstructed_08[0x220 - 0x08];
	AIPlayer *m_ai;						///< retail this+0x220
};

// ?friend_applyDifficultyBonusesForObject@Player@@QAEXPAVObject@@_N@Z
void Player::friend_applyDifficultyBonusesForObject(Object *obj, Bool apply)
{
	if (!apply)
		return;
	if (!obj)
		return;
	if (obj->bfmeIsComputerControlled())
		return;
	if (!obj->getControllingPlayer())
		return;
	if (!obj->getControllingPlayer()->getPlayerTemplate())
		return;
	if (!obj->getControllingPlayer()->getPlayerTemplate()->isPlayableSide())
		return;

	AsciiString name;
	if (TheGameLogic->_bfme_isInMultiplayerOrSkirmishGame() && m_ai)
	{
		switch (m_ai->getAIDifficulty())
		{
		case DIFFICULTY_EASY:
			name.set("Upgrade_EasyAIMultiPlayer");
			break;
		case DIFFICULTY_NORMAL:
			name.set("Upgrade_MediumAIMultiPlayer");
			break;
		case DIFFICULTY_HARD:
			name.set("Upgrade_HardAIMultiPlayer");
			break;
		}
	}
	else
	{
		switch (TheGameLogic->m_gameDifficulty)
		{
		case DIFFICULTY_EASY:
			name.set("Upgrade_EasyAISinglePlayer");
			break;
		case DIFFICULTY_NORMAL:
			name.set("Upgrade_MediumAISinglePlayer");
			break;
		case DIFFICULTY_HARD:
			name.set("Upgrade_HardAISinglePlayer");
			break;
		}
	}

	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgradeByKey(NAMEKEY(name.str()));
	if (upgrade)
		obj->giveUpgrade(upgrade);
}
