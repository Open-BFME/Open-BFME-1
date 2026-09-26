// ?evaluateObjectDistanceRva003239A0@ScriptConditions@@IAE_NPAVCondition@@@Z
// partial score=0.55 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
// Retail 0x003239A0: compares the distance between two named objects.
extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)

class Parameter
{
public:
	int getInt() const { return m_int; }
	float getReal() const { return m_real; }
private:
	char m_unknown[8];
	int m_int;
	float m_real;
};

class Condition
{
public:
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_numParms)
			return m_parameters[index];
		return 0;
	}
private:
	char m_unknown[8];
	int m_numParms;
	Parameter *m_parameters[12];
};

struct Coord3D { float x, y, z; };
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
private:
	char m_unknown[0x38];
	Coord3D m_position;
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
	bool evaluateObjectDistanceRva003239A0(Condition *condition);
};

bool ScriptConditions::evaluateObjectDistanceRva003239A0(Condition *condition)
{
	Object *first = TheScriptEngine->getUnitNamed(condition->getParameter(0));
	Object *second = TheScriptEngine->getUnitNamed(condition->getParameter(1));
	if (!first || !second)
		return false;
	const Coord3D *a = first->getPosition();
	const Coord3D *b = second->getPosition();
	Coord3D delta = *a;
	delta.x -= b->x;
	delta.y -= b->y;
	delta.z -= b->z;
	float distance = (float)sqrt(delta.z * delta.z + delta.y * delta.y + delta.x * delta.x);
	float value = condition->getParameter(3)->getReal();
	switch (condition->getParameter(2)->getInt()) {
	case 0: return distance < value;
	case 1: return distance <= value;
	case 2: return distance == value;
	case 3: return distance >= value;
	case 4: return distance > value;
	case 5: return distance != value;
	}
	return false;
}
