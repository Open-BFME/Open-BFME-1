// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// FIND_HOME_BASE_OF_PLAYER action at retail RVA 0x002F0BE0.

#include "StringInline.h"

typedef bool Bool;
typedef unsigned short UnsignedShort;

class Object
{
};

class BfmeEntryYQ
{
};

class BfmeThingYQ
{
public:
	BfmeEntryYQ *bfmeFindYQ(int kind, int output);
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
	void doFindHomeBaseOfPlayer(const AsciiString &playerName,
		const AsciiString &referenceName, Bool insideMap);
};

void ScriptActions::doFindHomeBaseOfPlayer(const AsciiString &playerName,
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
				void *object = ((BfmeThingYQ *)player)->bfmeFindYQ(
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
