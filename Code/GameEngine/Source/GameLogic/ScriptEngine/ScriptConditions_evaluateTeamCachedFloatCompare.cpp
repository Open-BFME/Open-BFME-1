// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// ScriptConditions team cached-float comparison, retail 0x00325E50.

#include "StringInline.h"

typedef bool Bool;
typedef float Real;

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

	unsigned char m_beforeInt[8];
	int m_int;
	Real m_real;
	AsciiString m_string;
};

class Team;

class Rva000F72D0FrameCachedValue
{
public:
	Real value(Real range);
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
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateTeamCachedFloatCompare(Parameter *, Parameter *, Parameter *, Parameter *);
};

// ?evaluateTeamCachedFloatCompare@ScriptConditions@@IAE_NPAVParameter@@000@Z
Bool ScriptConditions::evaluateTeamCachedFloatCompare(
	Parameter *pTeamParm, Parameter *pComparisonParm,
	Parameter *pValueParm, Parameter *pContextParm)
{
	if (pTeamParm) {
		if (pContextParm) {
			if (pComparisonParm) {
				if (pValueParm) {
					Rva000F72D0FrameCachedValue *theTeam =
						(Rva000F72D0FrameCachedValue *)TheScriptEngine->getTeamNamed(
						pTeamParm->getString(), false);
					if (theTeam) {
						Real range = pContextParm->m_real;
						Real value = theTeam->value(range);
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
