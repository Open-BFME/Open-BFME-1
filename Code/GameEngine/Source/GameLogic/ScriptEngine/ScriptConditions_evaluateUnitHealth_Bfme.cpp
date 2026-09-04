// cl: /DNDEBUG /DWIN32 /MD
// BFME layout of the unit-health comparison condition.

typedef bool Bool;

class Parameter
{
public:
	int getInt(void) const { return m_int; }

private:
	unsigned char m_beforeInt[0x8];
	int m_int;
};

class BfmeBody
{
public:
	unsigned char m_beforeHealth[0x28];
	int m_health;
};

class Object
{
public:
	unsigned char m_beforeBody[0x210];
	BfmeBody *m_body;
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
	virtual Object *getUnitNamed(Parameter *) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateUnitHealth(Parameter *, Parameter *, Parameter *);
};

// ?evaluateUnitHealth@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateUnitHealth(
	Parameter *pUnitParm, Parameter *pComparisonParm, Parameter *pHealthPercent)
{
	Object *theObj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (theObj) {
		BfmeBody *body = theObj->m_body;
		if (body) {
			int comparison = pComparisonParm->getInt();
			int current = body->m_health;
			Bool result;
			switch (comparison) {
			case 0: result = current < pHealthPercent->getInt(); break;
			case 1: result = current <= pHealthPercent->getInt(); break;
			case 2: result = current == pHealthPercent->getInt(); break;
			case 3: result = current >= pHealthPercent->getInt(); break;
			case 4: result = current > pHealthPercent->getInt(); break;
			case 5: result = current != pHealthPercent->getInt(); break;
			default: result = false; break;
			}
			if (result)
				return true;
		}
	}

	return false;
}
