// BFME ScriptConditions float comparator at retail 0x00323B70.

typedef bool Bool;
typedef float Real;

class Parameter
{
public:
	int m_beforeInt[2];
	int m_int;
	Real m_real;
};

class BfmeThingFBA
{
public:
	Real bfmeGoFBAThunk(void *context);
};

#pragma comment(linker, "/alternatename:?bfmeGoFBAThunk@BfmeThingFBA@@QAEMPAX@Z=?j_0000b816@@YAXXZ")

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
	virtual BfmeThingFBA *getUnitNamed(Parameter *) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateDistanceBetweenObjects(Parameter *, Parameter *, Parameter *, Parameter *);
};

// ?evaluateDistanceBetweenObjects@ScriptConditions@@IAE_NPAVParameter@@000@Z
Bool ScriptConditions::evaluateDistanceBetweenObjects(
	Parameter *pObjectParm, Parameter *pComparisonParm,
	Parameter *pValueParm, Parameter *pContextParm)
{
	if (pObjectParm) {
		if (pContextParm) {
			if (pComparisonParm) {
				if (pValueParm) {
					BfmeThingFBA *object =
						TheScriptEngine->getUnitNamed(pObjectParm);
					if (object) {
						Real contextReal = pContextParm->m_real;
						void *context = *(void **)&contextReal;
						Real value = object->bfmeGoFBAThunk(context);
						switch (pComparisonParm->m_int) {
						case 0: return (value < pValueParm->m_real);
						case 1: return (value <= pValueParm->m_real);
						case 2: return (value == pValueParm->m_real);
						case 3: return (value >= pValueParm->m_real);
						case 4: return (value > pValueParm->m_real);
						case 5: return (value != pValueParm->m_real);
						}
					}
				}
			}
		}
	}

	return false;
}
