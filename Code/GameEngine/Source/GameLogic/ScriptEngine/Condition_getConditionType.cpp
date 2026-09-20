// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class Condition
{
public:
	enum ConditionType
	{
		CONDITION_FALSE = 0
	};

	virtual ~Condition();
	ConditionType getConditionType();

private:
	ConditionType m_conditionType;
};

// @?getConditionType@Condition@@QAE?AW4ConditionType@1@XZ 0x002ED4B0
Condition::ConditionType Condition::getConditionType()
{
	return m_conditionType;
}
