// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?evaluateNamedOwnedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// Lift the ScriptConditions::evaluateNamedOwnedByPlayer __emit thunk to clean C++.
//
// Zero Hour compares one unit's controlling player against one named player.
// BFME resolves the player name to a 16-bit mask instead and walks every player
// in it, exactly like ScriptActions::doGiveMoney -- same PlayerList accessor,
// same by-reference mask that the accessor consumes, so the trailing
// `cmp word ptr [esp+0xc], 0` is the loop condition rather than a second test.
//
// The mask lands in the first parameter's stack slot: both Parameters are dead
// by then and MSVC reuses the space. It is stored with a full dword `mov` even
// though it is 16 bits wide, because the reused slot is four bytes and only the
// `cmp word ptr` that closes the loop reads it back.
//
// Both ScriptEngine entry points take the AsciiString rather than the Parameter,
// which only works because Parameter carries its string at offset 0 -- getString
// compiles to nothing and the raw Parameter pointer is what gets pushed. The
// second one is not identified: ILT 0x000230B5 lands on 0x0034DB40, an SEH body
// that forwards to TheScriptEngine's virtual +0x4C and returns the mask. That is
// a different body from the mask resolver at 0x0034CB60 already pinned for
// doGiveMoney, so it carries an address-derived name.

typedef int Int;
typedef bool Bool;
typedef unsigned short UnsignedShort;

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	unsigned char m_unreconstructed_00[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	// retail pushes the Parameter pointer unchanged, so the string is at +0x00
	AsciiString m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;		///< ILT thunk at 0x00020824
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);	///< ILT thunk at 0x0002EE60
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual Object *getUnitNamed(const AsciiString &name);	///< vtable +0x68

	/// address-derived name -- do not treat as an identity. Body at 0x0034DB40
	/// forwards to TheScriptEngine's virtual +0x4C.
	UnsignedShort unidentified_0034DB40(const AsciiString &name);	///< ILT thunk at 0x000230B5
};

extern ScriptEngine *TheScriptEngine;					///< retail [0x012F076C]
extern PlayerList *ThePlayerList;						///< retail [0x012ED748]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateNamedOwnedByPlayer(Parameter *, Parameter *);
};

// ?evaluateNamedOwnedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateNamedOwnedByPlayer(Parameter *unitParm, Parameter *playerParm)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitParm->getString());
	if (!theUnit) {
		return false;
	}

	UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(playerParm->getString());
	while (mask != 0) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (theUnit->getControllingPlayer() == player) {
			return true;
		}
	}

	return false;
}
