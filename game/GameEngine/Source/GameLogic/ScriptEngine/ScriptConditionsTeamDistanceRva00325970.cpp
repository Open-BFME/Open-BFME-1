// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// Retail 0x00325970: compare estimated distance between two script teams.
#include "StringInline.h"
#include <math.h>

typedef bool Bool;
typedef float Real;
typedef int Int;

class Parameter
{
public:
	// This caller reads these fields directly in retail. Keeping its layout
	// view free of accessors avoids emitting competing Parameter COMDATs.
	char m_beforeInt[8];
	Int m_int;
	Real m_real;
	AsciiString m_string;
};

class Condition
{
public:
	Parameter *getParameter(Int index)
	{
		if (index >= 0 && index < m_numParms)
			return m_parameters[index];
		return 0;
	}
private:
	char m_unknown[8];
	Int m_numParms;
	Parameter *m_parameters[12];
};

struct Coord3D { Real x, y, z; };
class Team
{
public:
	Bool hasAnyObjects(Bool includeSpecialObjects) const;
	Coord3D *getEstimateTeamPosition(Coord3D *position) const;
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
	Bool evaluateDistanceBetweenTeamsRva00325970(Condition *condition);
};

Bool ScriptConditions::evaluateDistanceBetweenTeamsRva00325970(Condition *condition)
{
	Team *first = TheScriptEngine->getTeamNamed(condition->getParameter(0)->m_string, false);
	Team *second = TheScriptEngine->getTeamNamed(condition->getParameter(1)->m_string, false);
	if (!first || !second || !first->hasAnyObjects(false) || !second->hasAnyObjects(false))
		return false;
	Coord3D firstPosition;
	Coord3D secondPosition;
	first->getEstimateTeamPosition(&firstPosition);
	const Coord3D *q = second->getEstimateTeamPosition(&secondPosition);
	firstPosition.x -= q->x;
	firstPosition.y -= q->y;
	firstPosition.z -= q->z;
	Real distance = (Real)sqrt(firstPosition.z * firstPosition.z +
		firstPosition.y * firstPosition.y + firstPosition.x * firstPosition.x);
	Real threshold = condition->getParameter(3)->m_real;
	switch (condition->getParameter(2)->m_int) {
	case 0: if (distance < threshold) return true; break;
	case 1: if (distance <= threshold) return true; break;
	case 2: if (distance == threshold) return true; break;
	case 3: if (distance >= threshold) return true; break;
	case 4: if (distance > threshold) return true; break;
	case 5: if (distance != threshold) return true; break;
	}
	return false;
}
