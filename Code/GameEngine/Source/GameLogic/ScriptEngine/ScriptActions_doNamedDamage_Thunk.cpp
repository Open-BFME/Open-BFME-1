// cl: /DNDEBUG /MD /EHsc
// readable body of ?doNamedDamage@ScriptActions@@IAEXABVAsciiString@@H@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp

typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

class AsciiString;

struct BFMEDamageInfoInput
{
	unsigned char m_unreconstructed00[8];
	ObjectID m_sourceID;
	unsigned char m_unreconstructed0C[4];
	int m_damageType;
	unsigned char m_unreconstructed14[4];
	int m_deathType;
	Real m_amount;
	Bool m_kill;
};

struct BFMEDamageInfo
{
	BFMEDamageInfo();

	BFMEDamageInfoInput in;
	unsigned char m_unreconstructed24[0x5c - 0x24];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void attemptDamage(BFMEDamageInfo *) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doNamedDamage(const AsciiString &, int);
};

// ?doNamedDamage@ScriptActions@@IAEXABVAsciiString@@H@Z
void ScriptActions::doNamedDamage(const AsciiString &unitName, int damageAmount)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (!unit) {
		return;
	}

	BFMEDamageInfo damageInfo;
	damageInfo.in.m_damageType = 8;
	damageInfo.in.m_deathType = 0;
	damageInfo.in.m_sourceID = 0;
	damageInfo.in.m_amount = damageAmount;
	unit->attemptDamage(&damageInfo);
}
