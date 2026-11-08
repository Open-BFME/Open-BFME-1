// readable body of ?evaluateScienceAcquired@ScriptConditions@@IAE_NPAVParameter@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// Open-BFME5 conversions.

struct BfmeB1091
{
	char m_bfmePad[0x3c];
	unsigned int m_bfme3c;
};

struct BfmeM1091
{
	char m_bfmePad[0x11f8];
	float m_bfme11f8;
};

// Rows at the ILTs retail calls: Player::isCapableOfPurchasingScience (0x000CFDF0),
// hasAnyBuildFacility (0x000CE100), hasAnyObjects (0x000CE0B0); the view carries only those.
enum ScienceType { SCIENCE_INVALID = -1 };

class Player
{
public:
	bool isCapableOfPurchasingScience(ScienceType science) const;
	bool hasAnyBuildFacility() const;
	bool hasAnyObjects(bool flag) const;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(unsigned short &mask);
};

class AsciiString;

// ScienceStore::getScienceFromInternalName (0x000E7460).
class ScienceStore
{
public:
	ScienceType getScienceFromInternalName(const AsciiString &name) const;
};

class Parameter;

// Retail's TheScriptEngine (0x012F076C); the view carries the player-mask resolver (row 0x0034DB40).
class ScriptEngine
{
public:
	unsigned short unidentified_0034DB40(Parameter *parameter);
};
extern ScriptEngine *TheScriptEngine;

// Retail keeps the resolver's whole EAX (no zero-extension of the 16-bit mask),
// so the row is called through its own symbol with an int result view.
static __forceinline int nextPlayerMask(int parameter)
{
	typedef int (ScriptEngine::*Raw)(Parameter *);
	Raw raw = reinterpret_cast<Raw>(&ScriptEngine::unidentified_0034DB40);
	return (TheScriptEngine->*raw)((Parameter *)parameter);
}

class GameLogic;
// 0x012F0898 is retail's `GameLogic *TheGameLogic`; BfmeB1091 is this TU's
// local view of the same global, so cast at the use.
extern GameLogic *TheGameLogic;
// 0x012ED5C8 is retail's `GlobalData *TheWritableGlobalData`; BfmeM1091 is the TU's view of it.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
#define g_bfmeM1091 ((BfmeM1091 *)TheWritableGlobalData)
extern ScienceStore *TheScienceStore;
// 0x012ED748 is retail's `PlayerList *ThePlayerList`.
extern PlayerList *ThePlayerList;



// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	bool evaluateScienceAcquired(Parameter *playerParm, Parameter *scienceParm);
};

// ?evaluateScienceAcquired@ScriptConditions@@IAE_NPAVParameter@@0@Z
bool ScriptConditions::evaluateScienceAcquired(
	Parameter *playerParm, Parameter *scienceParm)
{
	ScienceType e = TheScienceStore->getScienceFromInternalName(
		*reinterpret_cast<const AsciiString *>(reinterpret_cast<char *>(scienceParm) + 0x10));

	if (e == SCIENCE_INVALID)
		return false;
	scienceParm = reinterpret_cast<Parameter *>(
		nextPlayerMask(reinterpret_cast<int>(playerParm)));
	while ((short)reinterpret_cast<int>(scienceParm)) {
		Player *r = ThePlayerList->getEachPlayerFromMask(
			*reinterpret_cast<unsigned short *>(&scienceParm));

		if (r && r->isCapableOfPurchasingScience(e))
			return true;
	}
	return false;
}

char __stdcall bfmeGo1091B(int a)
{
	unsigned int n = ((BfmeB1091 *)TheGameLogic)->m_bfme3c;

	if (n < (unsigned int)(int)(g_bfmeM1091 ? g_bfmeM1091->m_bfme11f8 * 5.0f : 25.0f))
		return 0;
	a = nextPlayerMask(a);
	while ((short)a) {
		Player *r = ThePlayerList->getEachPlayerFromMask(*(unsigned short *)&a);

		if (r && r->hasAnyBuildFacility())
			return 0;
	}
	return 1;
}

char __stdcall bfmeGo1091C(int a)
{
	unsigned int n = ((BfmeB1091 *)TheGameLogic)->m_bfme3c;

	if (n < (unsigned int)(int)(g_bfmeM1091 ? g_bfmeM1091->m_bfme11f8 * 5.0f : 25.0f))
		return 0;
	a = nextPlayerMask(a);
	while ((short)a) {
		Player *r = ThePlayerList->getEachPlayerFromMask(*(unsigned short *)&a);

		if (r && r->hasAnyObjects(false))
			return 0;
	}
	return 1;
}
