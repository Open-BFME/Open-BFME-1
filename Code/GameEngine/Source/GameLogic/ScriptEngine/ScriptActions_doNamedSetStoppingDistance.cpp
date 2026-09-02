// cl: /DNDEBUG /DWIN32 /MD
// Open-BFME: ScriptActions::doNamedSetStoppingDistance, retail 0x002EF710, 67 bytes.
//
// ZH twin. BFME Object m_ai is +0x204 and the current locomotor is AI+0x1CC;
// close-enough distance is locomotor+0x38. The 0.5f floor is the ZH test.

class AsciiString
{
	char *m_data;
};

class Locomotor
{
public:
	unsigned char m_pad[0x38];
	float m_closeEnoughDist;
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x1CC];
	Locomotor *m_curLocomotor;
};

class Object
{
public:
	unsigned char m_pad[0x204];
	AIUpdateInterface *m_ai;
};

class ScriptEngine
{
public:
	virtual void _se_0() = 0;
	virtual void _se_1() = 0;
	virtual void _se_2() = 0;
	virtual void _se_3() = 0;
	virtual void _se_4() = 0;
	virtual void _se_5() = 0;
	virtual void _se_6() = 0;
	virtual void _se_7() = 0;
	virtual void _se_8() = 0;
	virtual void _se_9() = 0;
	virtual void _se_10() = 0;
	virtual void _se_11() = 0;
	virtual void _se_12() = 0;
	virtual void _se_13() = 0;
	virtual void _se_14() = 0;
	virtual void _se_15() = 0;
	virtual void _se_16() = 0;
	virtual void _se_17() = 0;
	virtual void _se_18() = 0;
	virtual void _se_19() = 0;
	virtual void _se_20() = 0;
	virtual void _se_21() = 0;
	virtual void _se_22() = 0;
	virtual void _se_23() = 0;
	virtual void _se_24() = 0;
	virtual void _se_25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doNamedSetStoppingDistance(const AsciiString &unit, float stoppingDistance);
};

void ScriptActions::doNamedSetStoppingDistance(const AsciiString &unit, float stoppingDistance)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unit);
	if (theObj)
	{
		AIUpdateInterface *aiUpdate = theObj->m_ai;
		if (!aiUpdate || !aiUpdate->m_curLocomotor)
			return;

		if (stoppingDistance >= 0.5f)
			aiUpdate->m_curLocomotor->m_closeEnoughDist = stoppingDistance;
	}
}
