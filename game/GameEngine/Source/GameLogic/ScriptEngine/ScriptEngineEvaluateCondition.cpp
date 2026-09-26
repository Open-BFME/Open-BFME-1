// ScriptEngine condition dispatcher, retail RVA 0x00346300.
// Upstream ScriptEngine.cpp evaluateCondition and Scripts.h provide the
// five enum identities. Retail tail calls preserve ECX for evaluateCounter,
// evaluateFlag and evaluateTimer; default uses TheScriptConditions slot +0x24.

class Condition
{
public:
	enum ConditionType
	{
		CONDITION_FALSE, COUNTER, FLAG, CONDITION_TRUE, TIMER_EXPIRED
	};
	ConditionType getConditionType() const
	{
		return m_conditionType;
	}

private:
	char m_unreconstructed[4];
	ConditionType m_conditionType;
};

class ScriptConditionsInterface
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual bool evaluateCondition(Condition *condition);
};

extern ScriptConditionsInterface *TheScriptConditions;

class ScriptEngine
{
public:
	// Matches the already recovered evaluateTimer declaration.
	bool evaluateTimer(Condition *condition);
protected:
	bool evaluateCounter(Condition *condition);
	bool evaluateFlag(Condition *condition);
	bool evaluateCondition(Condition *condition);
};

bool ScriptEngine::evaluateCondition(Condition *condition)
{
	switch (condition->getConditionType())
	{
	default:
		return TheScriptConditions->evaluateCondition(condition);
	case Condition::CONDITION_FALSE:
		return false;
	case Condition::CONDITION_TRUE:
		return true;
	case Condition::COUNTER:
		return evaluateCounter(condition);
	case Condition::FLAG:
		return evaluateFlag(condition);
	case Condition::TIMER_EXPIRED:
		return evaluateTimer(condition);
	}
}
