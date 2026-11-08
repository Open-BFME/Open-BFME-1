// readable body of ?evaluateSciencePurchasePoints@ScriptConditions@@IAE_NPAVParameter@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// Open-BFME5 conversions.

struct BfmeT1089
{
	char m_bfmePad[8];
	int m_bfme08;
};

// TU-local layout view of Player. The `this`-only helpers are the pinned rows at the ILTs
// retail calls: 0x000C9580 (?call@Rva000C9580, bool) and Player::countBuildings.
class Rva000C9580
{
public:
	bool call(void);
};

class Player
{
public:
	int countBuildings(void);
	char m_bfmePad[0x264];
	int m_sciencePurchasePoints;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(unsigned short &mask);
};

class Parameter;

class ScriptEngine
{
public:
	unsigned short unidentified_0034DB40(Parameter *parameter);
};

// Retail 0x00EED748 is ThePlayerList (see game_engine_subsystems.h), so the
// global is spelled with its defining name; the PlayerList above carries only the
// pinned getEachPlayerFromMask row this body calls.
// 0x012F076C is retail's TheScriptEngine singleton; the ScriptEngine view above
// carries only the pinned player-mask resolver (row 0x0034DB40).
extern PlayerList *ThePlayerList;
extern ScriptEngine *TheScriptEngine;

// Retail keeps the resolver's whole EAX (no zero-extension of the 16-bit mask),
// so the row is called through its own symbol with an int result view.
static __forceinline int nextPlayerMask(Parameter *parameter)
{
	typedef int (ScriptEngine::*Raw)(Parameter *);
	Raw raw = reinterpret_cast<Raw>(&ScriptEngine::unidentified_0034DB40);
	return (TheScriptEngine->*raw)(parameter);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	int getInt() const { return m_int; }

private:
	char m_unreconstructed00[8];
	int m_int;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	bool evaluateSciencePurchasePoints(Parameter *playerParm, Parameter *pointsParm);
};

// ?evaluateSciencePurchasePoints@ScriptConditions@@IAE_NPAVParameter@@0@Z
bool ScriptConditions::evaluateSciencePurchasePoints(
	Parameter *playerParm, Parameter *pointsParm)
{
	int n = pointsParm->getInt();

	pointsParm = reinterpret_cast<Parameter *>(
		nextPlayerMask(playerParm));
	while ((short)reinterpret_cast<int>(pointsParm)) {
		Player *r = ThePlayerList->getEachPlayerFromMask(
			*reinterpret_cast<unsigned short *>(&pointsParm));

		if (r && r->m_sciencePurchasePoints >= n)
			return true;
	}
	return false;
}

char __stdcall bfmeGo1089B(int a)
{
	a = nextPlayerMask((Parameter *)a);
	while ((short)a) {
		Player *r = ThePlayerList->getEachPlayerFromMask(*(unsigned short *)&a);

		if (r && reinterpret_cast<Rva000C9580 *>(r)->call())
			return 1;
	}
	return 0;
}

char __stdcall bfmeGo1089C(BfmeT1089 *t, int a)
{
	int n;

	a = nextPlayerMask((Parameter *)a);
	n = 0;
	while ((short)a) {
		Player *r = ThePlayerList->getEachPlayerFromMask(*(unsigned short *)&a);

		if (r)
			n += r->countBuildings();
	}
	return t->m_bfme08 >= n;
}
