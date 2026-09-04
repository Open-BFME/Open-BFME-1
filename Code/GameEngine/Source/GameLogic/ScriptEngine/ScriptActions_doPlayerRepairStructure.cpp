// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// readable body of ?doPlayerRepairStructure@ScriptActions@@IAEXABVAsciiString@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// Identity: executeAction jump-table arm 257 is PLAYER_REPAIR_NAMED_STRUCTURE.
// BFME looks up the named structure first (ScriptEngine slot 27 by value), then
// the player via getPlayerMaskFromAsciiString + ThePlayerList::getEachPlayerFromMask,
// then Player vslot +0x1C (repairStructure) with Object::m_id at +0x74.

#include "StringInline.h"

typedef bool Bool;
typedef unsigned int ObjectID;

class Object
{
	unsigned char m_pad[0x74];
public:
	ObjectID m_id;
};

class Player
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void repairStructure(ObjectID structureID);
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual Object *getUnitNamedByValue(AsciiString name);
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	unsigned short getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(unsigned short &mask);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptActions
{
protected:
	void doPlayerRepairStructure(const AsciiString &playerName,
		const AsciiString &structureName);
};

void ScriptActions::doPlayerRepairStructure(const AsciiString &playerName,
	const AsciiString &structureName)
{
	Object *pStructure = TheScriptEngine->getUnitNamedByValue(structureName);
	if (pStructure)
	{
		unsigned short mask =
			((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
				->getPlayerMaskFromAsciiString(playerName, 0);
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (pPlayer)
			pPlayer->repairStructure(pStructure->m_id);
	}
}
