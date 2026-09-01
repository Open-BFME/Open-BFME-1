// cl: /DNDEBUG /MD /EHsc
// Condition's BFME layout is fixed by its exact setConditionType body and by
// the 12 pointer stores in this constructor.  The constructor logic is the
// released Zero Hour source shape with the retail BFME vtable and call targets.

class Parameter;

class Condition
{
public:
	enum ConditionType
	{
		CONDITION_FALSE = 0
	};

	Condition(ConditionType type);
	virtual ~Condition();
	void setConditionType(ConditionType type);

private:
	ConditionType m_conditionType;
	int m_hasWarnings;
	Parameter *m_parms[12];
	int m_customData;
	int m_customFrame;
	int m_numParms;
	Condition *m_nextAndCondition;
};

Condition::Condition(ConditionType type) :
	m_conditionType(type),
	m_hasWarnings(false),
	m_customData(0),
	m_customFrame(0),
	m_numParms(0),
	m_nextAndCondition(0)
{
	for (int i = 0; i < 12; ++i)
		m_parms[i] = 0;

	setConditionType(type);
}
