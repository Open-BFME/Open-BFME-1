// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// FIND_HOME_BASE_OF_PLAYER action at retail RVA 0x002F0BE0.

#include "StringInline.h"

#include "../../../Include/Common/ScalarTypes.h"


class Object
{
};

class BfmeEntryYQ
{
};

// The per-player lookup goes through ILT 0x0004AF84, the ledger's 5-byte row
// ?j_0004af84@@YAXXZ (game/gen_small/thunks_036.cpp), as tools/callees.py
// 0x2f0be0 167 prints.  Nothing defines the pinned
// ?bfmeFindYQ@BfmeThingYQ@@QAEPAVBfmeEntryYQ@@HH@Z, so the call names the
// thunk through a raw pointer bridge that keeps the thiscall shape.
void j_0004af84();
class BfmeThingYQ
{
};

class BfmeThingERK
{
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	UnsignedShort getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *found);
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
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void bindUnitReference(Object *object, const AsciiString &name) = 0;
	void assignUnitReference(const AsciiString &name, Object *object);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

void bfmeApplyERK(BfmeThingERK *first, BfmeThingERK *second);

typedef int (__cdecl *BfmeApplyERKResult)(BfmeThingERK *, BfmeThingERK *);

class ScriptActions
{
protected:
	void doSetUnitReferenceToHomeBaseOfPlayer(const AsciiString &playerName,
		const AsciiString &referenceName, Bool insideMap);
};

void ScriptActions::doSetUnitReferenceToHomeBaseOfPlayer(const AsciiString &playerName,
	const AsciiString &referenceName, Bool insideMap)
{
	UnsignedShort mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(playerName, 0);
	void *bestObject = 0;
	BfmeThingERK *bestCandidate = 0;
	if (mask)
	{
		do
		{
			Player *player = ThePlayerList->getEachPlayerFromMask(mask);
			if (player)
			{
				BfmeThingERK *candidate;
				union
				{
					void (*raw)(void);
					BfmeEntryYQ *(BfmeThingYQ::*typed)(int, int);
				} findYQ;
				findYQ.raw = &j_0004af84;
				void *object = (((BfmeThingYQ *)player)->*findYQ.typed)(
					*(const int *)(const void *)&insideMap, (int)&candidate);
				if (candidate)
				{
					if (bestCandidate &&
						((BfmeApplyERKResult)bfmeApplyERK)(bestCandidate,
							candidate) >= 0)
						continue;
					bestObject = object;
					bestCandidate = candidate;
				}
			}
		} while (mask);
	}

	if (bestObject)
	{
		TheScriptEngine->assignUnitReference(referenceName,
			(Object *)bestObject);
		TheScriptEngine->bindUnitReference((Object *)bestObject,
			referenceName);
	}
}
