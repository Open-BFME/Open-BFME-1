// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?doPlayerSetScienceAvailability@ScriptActions@@IAEXABVAsciiString@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// Lift the ScriptActions::doPlayerSetScienceAvailability __emit thunk to clean C++.
//
// Zero Hour resolves one Player and sets one science's availability on it. BFME
// walks a player mask instead, the same generalisation as doGiveMoney and
// doPlayerGrantScience, with getEachPlayerFromMask consuming the mask by
// reference so the trailing `cmp word ptr` closes the loop.
//
// This one is a while and not a do-while: the loop head is aligned and retail
// jumps over the padding to enter it, and the callee-saved registers are pushed
// after the mask guard rather than in the prologue. Both follow from the
// pre-tested form.
//
// The two lookups are per-player and run in the opposite order from the
// parameter list -- the availability name is resolved first and the science name
// second, but they are pushed science-then-availability, which is the argument
// order of the setter.
//
// The availability lookup is a Player member here rather than a ScienceStore
// one, which is not where Zero Hour puts it, so it carries an address-derived
// name instead of ZH's.

typedef int Int;
typedef unsigned short UnsignedShort;

class AsciiString;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

enum ScienceAvailabilityType
{
	SCIENCE_AVAILABILITY_INVALID = -1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	/// address-derived name -- do not treat as an identity. Body at 0x000CFE80.
	ScienceAvailabilityType unidentified_000CFE80(const AsciiString &name);	///< ILT thunk at 0x00030260

	void setScienceAvailability(ScienceType science, ScienceAvailabilityType avail);	///< ILT thunk at 0x00010DED
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
	void doPlayerSetScienceAvailability(const AsciiString &, const AsciiString &, const AsciiString &);
};

// ?doPlayerSetScienceAvailability@ScriptActions@@IAEXABVAsciiString@@00@Z
void ScriptActions::doPlayerSetScienceAvailability(const AsciiString &playerName,
	const AsciiString &scienceName, const AsciiString &availabilityName)
{
	UnsignedShort mask = TheScriptEngine->getPlayerMaskFromAsciiString(playerName, 0);

	while (mask != 0)
	{
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player)
		{
			ScienceAvailabilityType avail = player->unidentified_000CFE80(availabilityName);
			if (avail != SCIENCE_AVAILABILITY_INVALID)
			{
				ScienceType science = TheScienceStore->getScienceFromInternalName(scienceName);
				if (science != SCIENCE_INVALID)
				{
					player->setScienceAvailability(science, avail);
				}
			}
		}
	}
}
