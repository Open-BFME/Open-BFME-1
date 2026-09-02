// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class WWMath
{
public:
	static float Random_Float();
};

class Gen0060BE20
{
public:
	void updateGate();

private:
	void refresh();
	void onRandomGate();
	void onLimitPassed();

	char m_head[0x30];
	unsigned int m_value;
	char m_gap[0x04];
	unsigned int m_lower;
	unsigned int m_upper;
	unsigned int m_limit;
};

void Gen0060BE20::updateGate()
{
	refresh();

	if (m_value > m_lower && m_value < m_upper && WWMath::Random_Float() > 0.7f)
		onRandomGate();

	if (m_value > m_limit)
		onLimitPassed();
}
