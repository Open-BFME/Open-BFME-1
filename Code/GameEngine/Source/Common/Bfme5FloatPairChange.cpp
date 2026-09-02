void bfmeApplyFloatPair(int handle, float first, float second);

class Gen_005891E0
{
public:
	void bfmeSet(float first, float second);

private:
	char m_bfmeFields[0x0C];
	int m_bfmeHandle;
	float m_bfmeFirst;
	float m_bfmeSecond;
};

// ?bfmeSet@Gen_005891E0@@QAEXMM@Z
void Gen_005891E0::bfmeSet(float first, float second)
{
	if (first != m_bfmeFirst || second != second)
	{
		bfmeApplyFloatPair(m_bfmeHandle, first, second);
		m_bfmeFirst = first;
		m_bfmeSecond = second;
	}
}
