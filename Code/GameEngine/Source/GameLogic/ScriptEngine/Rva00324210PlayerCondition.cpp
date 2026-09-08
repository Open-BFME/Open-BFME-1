// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// stlport
// Raw-ABI reconstruction of retail RVA 0x00324210.  The owner and the
// meaning of the absolute operand at 0x258 are not established by the
// available caller evidence, so this translation unit keeps the identity
// address-derived.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned short PlayerMaskType;

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }
	Int getInt(void) const { return m_int; }

private:
	unsigned char m_beforeInt[8];
	Int m_int;
	float m_real;
	AsciiString m_string;
};

class Player;

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
};

class PlayerList
{
};

class BfmePlayerListGetPlayerFromMask
{
public:
	Player *getPlayerFromMask(PlayerMaskType mask);
};

class ScriptEngine
{
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern void j_0001dde5(void);

static __forceinline Player *bfmeGetPlayerFromMask(PlayerList *players,
	PlayerMaskType mask)
{
	typedef Player *(BfmePlayerListGetPlayerFromMask::*Function)(
		PlayerMaskType);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001dde5;
	return (reinterpret_cast<BfmePlayerListGetPlayerFromMask *>(players)->*
		fn.member)(mask);
}

class Rva00324210PlayerCondition
{
public:
	Bool evaluate(Parameter *playerParm, Parameter *comparisonParm,
		Parameter *valueParm);
};

Bool Rva00324210PlayerCondition::evaluate(Parameter *playerParm,
	Parameter *comparisonParm, Parameter *valueParm)
{
	PlayerMaskType mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
		->getPlayerMaskFromAsciiString(
		playerParm->getString(), 0);
	Player *player = bfmeGetPlayerFromMask(ThePlayerList, mask);
	if (player) {
		return false;
	}

	Int comparison = comparisonParm->getInt();
	Int current = *reinterpret_cast<volatile Int *>(0x258);
	Bool result;
	switch (comparison) {
	case 0: result = current < valueParm->getInt(); break;
	case 1: result = current <= valueParm->getInt(); break;
	case 2: result = current == valueParm->getInt(); break;
	case 3: result = current >= valueParm->getInt(); break;
	case 4: result = current > valueParm->getInt(); break;
	case 5: result = current != valueParm->getInt(); break;
	default: result = false; break;
	}
	if (result) {
		return true;
	}
	return false;
}
