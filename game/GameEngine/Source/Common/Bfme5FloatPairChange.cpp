// ILT 0x000152DF -> 0x00564BB0, the matched ?bfmeGo1077A@@YAXHMM@Z (BfmeConv1077.cpp).
void bfmeGo1077A(int handle, float first, float second);

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
		bfmeGo1077A(m_bfmeHandle, first, second);
		m_bfmeFirst = first;
		m_bfmeSecond = second;
	}
}
