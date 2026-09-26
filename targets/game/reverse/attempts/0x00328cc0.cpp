// ?d_00328cc0@@YAXXZ
// partial score=0.36 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// The player-unit condition counts matching templates over every selected player.
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef unsigned short PlayerMaskType;
typedef unsigned int UnsignedInt;
typedef int Int;

class Parameter
{
public:
	Int getInt() const { return m_int; }
	const AsciiString &getString() const { return m_string; }

private:
	unsigned char m_beforeInt[8];
	Int m_int;
	float m_real;
	AsciiString m_string;
};

class Condition
{
public:
	Int getCustomData() const { return m_customData; }
	UnsignedInt getCustomFrame() const { return m_customFrame; }
	void setCustomData(Int value) { m_customData = value; }
	void setCustomFrame(UnsignedInt value) { m_customFrame = value; }

private:
	unsigned char m_pad00[0x44];
	Int m_customData;
	UnsignedInt m_customFrame;
};

class ThingTemplate;

class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	Int prepForPlayerCounting(_STL::vector<const ThingTemplate *> &, _STL::vector<Int> &);
	void *m_words[4];
	void deleteInstance() { delete this; }
};

class ObjectTypesTemp
{
public:
	ObjectTypes *m_types;
	ObjectTypesTemp();
	~ObjectTypesTemp() { if (m_types) delete m_types; }
};

ObjectTypesTemp::ObjectTypesTemp() : m_types(0)
{
	m_types = new ObjectTypes;
}

class Player
{
public:
	void countObjectsByThingTemplate(Int, const ThingTemplate *const *, Bool, Int *, Bool) const;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &);
};

class BfmeP1087
{
public:
	PlayerMaskType bfmeNext1087(Parameter *);
};

extern BfmeP1087 *g_bfmeP1087;

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
	UnsignedInt getFrameObjectCountChanged() const
	{
		return *(const UnsignedInt *)((const char *)this + 0x170d8);
	}
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
	static void objectTypesFromParam(Parameter *, ObjectTypes *);
	Bool evaluatePlayerUnitCondition(Condition *, Parameter *, Parameter *, Parameter *, Parameter *);
};

// ?evaluatePlayerUnitCondition@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@111@Z present-unmatched
Bool ScriptConditions::evaluatePlayerUnitCondition(Condition *pCondition,
	Parameter *pPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm,
	Parameter *pUnitTypeParm)
{
	if (pCondition->getCustomData() != 0) {
		if (TheScriptEngine->getFrameObjectCountChanged() == pCondition->getCustomFrame()) {
			if (pCondition->getCustomData() == 1) return true;
			if (pCondition->getCustomData() == -1) return false;
		}
	}

	_STL::vector<Int> counts;
	_STL::vector<const ThingTemplate *> templates;
	ObjectTypesTemp types;
	ScriptConditions::objectTypesFromParam(pUnitTypeParm, types.m_types);
	Int numObjs = types.m_types->prepForPlayerCounting(templates, counts);
	if (numObjs == 0) return false;

	PlayerMaskType mask = g_bfmeP1087->bfmeNext1087(pPlayerParm);
	Int count = 0;
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
		player->countObjectsByThingTemplate(numObjs, &templates[0], true,
				&counts[0], true);
			Int total = 0;
			for (_STL::vector<Int>::iterator it = counts.begin();
				it != counts.end(); ++it) total += *it;
			count += total;
		}
	}

	Bool comparison = false;
	switch (pComparisonParm->getInt()) {
	case 0: comparison = count < pCountParm->getInt(); break;
	case 1: comparison = count <= pCountParm->getInt(); break;
	case 2: comparison = count == pCountParm->getInt(); break;
	case 3: comparison = count >= pCountParm->getInt(); break;
	case 4: comparison = count > pCountParm->getInt(); break;
	case 5: comparison = count != pCountParm->getInt(); break;
	}

	pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
	pCondition->setCustomData(-1);
	if (comparison) pCondition->setCustomData(1);
	return comparison;
}
