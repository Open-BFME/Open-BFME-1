// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 003248E0. Condition 134 counts trees inside a named trigger.
// The condition and terrain frame fields are independently witnessed offsets.

#include "ascii_string.h"

typedef bool Bool;

class PolygonTrigger;

class Parameter
{
public:
	int getInt() const { return m_int; }
	const AsciiString &getString() const { return m_string; }

private:
	char m_pad00[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

class Condition
{
public:
	int getCustomData() const { return m_customData; }
	unsigned int getCustomFrame() const { return m_customFrame; }
	void setCustomData(int value) { m_customData = value; }
	void setCustomFrame(unsigned int value) { m_customFrame = value; }

private:
	char m_pad00[0x44];
	int m_customData;
	unsigned int m_customFrame;
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
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString) = 0;

	unsigned int getFrameObjectCountChanged() const { return m_frameObjectCountChanged; }

private:
	char m_pad04[0x170d8 - 4];
	unsigned int m_frameObjectCountChanged;
};

extern ScriptEngine *TheScriptEngine;
extern void j_0002784a();

class TerrainLogic
{
public:
	int countTrees(PolygonTrigger *trigger)
	{
		typedef int (TerrainLogic::*Function)(PolygonTrigger *);
		union { void (*raw)(void); Function member; } fn;
		fn.raw = j_0002784a;
		return (this->*fn.member)(trigger);
	}

	unsigned int getFrameObjectCountChanged() const { return m_frameObjectCountChanged; }

private:
	char m_pad00[0x18f0];
	unsigned int m_frameObjectCountChanged;
};

extern TerrainLogic *TheTerrainLogic;

class Rva003248E0Condition
{
public:
	Bool evaluate(Condition *, Parameter *, Parameter *, Parameter *);
};

Bool Rva003248E0Condition::evaluate(Condition *pCondition,
	Parameter *pComparisonParm, Parameter *pCountParm, Parameter *pTriggerParm)
{
	AsciiString triggerName = pTriggerParm->getString();
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(
		pTriggerParm->getString());
	if (pTrig == 0) {
		return false;
	}

	unsigned int terrainFrame = TheTerrainLogic->getFrameObjectCountChanged();
	if (terrainFrame <= pCondition->getCustomFrame()) {
		int cached = pCondition->getCustomData();
		if (cached == -1) {
			return false;
		}
		if (cached == 1) {
			return true;
		}
	}

	int count = TheTerrainLogic->countTrees(pTrig);
	Bool comparison = false;
	switch (pComparisonParm->getInt()) {
	case 0:
		comparison = count < pCountParm->getInt();
		break;
	case 1:
		comparison = count <= pCountParm->getInt();
		break;
	case 2:
		comparison = count == pCountParm->getInt();
		break;
	case 3:
		comparison = count >= pCountParm->getInt();
		break;
	case 4:
		comparison = count > pCountParm->getInt();
		break;
	case 5:
		comparison = count != pCountParm->getInt();
		break;
	}

	pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
	if (comparison) {
		pCondition->setCustomData(1);
		return true;
	}
	pCondition->setCustomData(-1);
	return false;
}
