// readable body of ?evaluatePlayerHasPower@ScriptConditions@@IAE_NPAVParameter@@@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// Open-BFME5 conversions.

struct BfmeT1090
{
	char m_bfmePad[8];
	int m_bfme08;
};

// Row at 0x004C7E10 (pinned ?isLimitAtLeastCount@Rva000C7E10Object@@QBE_NXZ): the sub-object at Player+0xA4.
class Rva000C7E10Object
{
public:
	bool isLimitAtLeastCount(void) const;
	char m_bfmePad[4];
};

// TU-local layout view of Player; getRankLevelCap is the pinned row at the call's ILT.
class Player
{
public:
	int getRankLevelCap(void);
	char m_bfmePad[0xa4];
	Rva000C7E10Object m_bfmeSub;
	char m_bfmePad1[0x17c];
	int m_bfme224;
	char m_bfmePad2[0x30];
	int m_bfme258;
};

// The global at 0x00EED748 is retail's ThePlayerList, declared with the
// defining spelling ?ThePlayerList@@3PAVPlayerList@@A.
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

// 0x012F076C is retail's TheScriptEngine singleton; the class is declared by
// GameLogic/ScriptEngine/script_engine.h, and this TU's ScriptEngine view above
// carries only the pinned player-mask resolver (row 0x0034DB40) this body calls.
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	bool evaluatePlayerHasPower(Parameter *playerParm);
};

char __stdcall bfmeGo1090A(int a, BfmeT1090 *t)
{
	a = nextPlayerMask((Parameter *)a);
	while ((short)a) {
		Player *r = ThePlayerList->getEachPlayerFromMask(*(unsigned short *)&a);

		if (r && t->m_bfme08 - 1 == r->m_bfme224)
			return 1;
	}
	return 0;
}

char __stdcall bfmeGo1090B(int a)
{
	a = nextPlayerMask((Parameter *)a);
	while ((short)a) {
		Player *r = ThePlayerList->getEachPlayerFromMask(*(unsigned short *)&a);

		if (r) {
			Rva000C7E10Object *s = &r->m_bfmeSub;

			if (s && s->isLimitAtLeastCount())
				return 1;
		}
	}
	return 0;
}

// ?evaluatePlayerHasPower@ScriptConditions@@IAE_NPAVParameter@@@Z
bool ScriptConditions::evaluatePlayerHasPower(Parameter *playerParm)
{
	playerParm = reinterpret_cast<Parameter *>(
		nextPlayerMask(playerParm));
	while ((short)reinterpret_cast<int>(playerParm)) {
		Player *r = ThePlayerList->getEachPlayerFromMask(
			*reinterpret_cast<unsigned short *>(&playerParm));

		if (r) {
			int v = r->m_bfme258;

			if (v >= r->getRankLevelCap())
				return 1;
		}
	}
	return 0;
}
