// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?doPlayerGrantScience@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// Lift the ScriptActions::doPlayerGrantScience __emit thunk to clean C++.
//
// Zero Hour resolves one Player from the name and grants the science to it.
// BFME generalised the player half exactly as it did for doGiveMoney: the name
// becomes a 16-bit mask and the body walks every player in it, with
// getEachPlayerFromMask consuming the mask by reference, which is what makes the
// trailing `cmp word ptr [esp+0xc], 0` the loop condition.
//
// The science is resolved first, before the player mask -- retail reads the
// second parameter at [esp+8] before it has pushed anything. ZH resolves the
// player first, so the two statements are swapped relative to the reference.
//
// SCIENCE_INVALID is -1 rather than 0, so the guard is a cmp against -1 and not
// a test; the mask guard right after it is a plain test because 0 is its
// sentinel.

typedef int Int;
typedef unsigned short UnsignedShort;

class AsciiString;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void grantScience(ScienceType science);						///< ILT thunk at 0x0000C33D
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);			///< ILT thunk at 0x0002EE60
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Science.h
class ScienceStore
{
public:
	ScienceType getScienceFromInternalName(const AsciiString &name);	///< ILT thunk at 0x0004B36C
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	UnsignedShort getPlayerMaskFromAsciiString(const AsciiString &name, bool *unused);	///< ILT thunk at 0x0004B290
};

extern ScienceStore *TheScienceStore;								///< retail [0x012ED7AC]
extern BfmeScriptEngine_getPlayerMaskFromAsciiString *TheScriptEngine;	///< retail [0x012F076C]
extern PlayerList *ThePlayerList;									///< retail [0x012ED748]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doPlayerGrantScience(const AsciiString &, const AsciiString &);
};

// ?doPlayerGrantScience@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doPlayerGrantScience(const AsciiString &playerName, const AsciiString &scienceName)
{
	ScienceType science = TheScienceStore->getScienceFromInternalName(scienceName);
	if (science == SCIENCE_INVALID)
	{
		return;
	}

	UnsignedShort mask = TheScriptEngine->getPlayerMaskFromAsciiString(playerName, 0);
	if (mask == 0)
	{
		return;
	}

	do
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
		{
			player->grantScience(science);
		}
	} while (mask != 0);
}
