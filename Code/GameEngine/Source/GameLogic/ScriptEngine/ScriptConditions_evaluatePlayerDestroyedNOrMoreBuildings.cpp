// cl: /DNDEBUG /MD /EHsc
// BFME reconstruction of the unimplemented player-building destruction test.

typedef bool Bool;
typedef unsigned short UnsignedShort;

class Parameter
{
};

class Player
{
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	UnsignedShort unidentified_0034DB40(Parameter *);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
	Bool evaluatePlayerDestroyedNOrMoreBuildings(Parameter *, Parameter *, Parameter *);
};

// ?evaluatePlayerDestroyedNOrMoreBuildings@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerDestroyedNOrMoreBuildings(
	Parameter *playerParm, Parameter *, Parameter *opponentParm)
{
	UnsignedShort playerMask = TheScriptEngine->unidentified_0034DB40(playerParm);
	Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
	UnsignedShort opponentMask = TheScriptEngine->unidentified_0034DB40(opponentParm);
	Player *opponent = ThePlayerList->getEachPlayerFromMask(opponentMask);
	if (!player || !opponent) {
		return false;
	}

	return false;
}
