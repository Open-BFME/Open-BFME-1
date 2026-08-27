// One more: an accumulator that marks the slots it touched.

class Gen_001B1240
{
public:
	void bfmeAdd(float value, int first, int second);
private:
	float m_bfmeFirst[16];						// +0x00
	float m_bfmeSecond[16];						// +0x40
	unsigned int m_bfmeMaskFirst;				// +0x80
	unsigned int m_bfmeMaskSecond;				// +0x84
};

void Gen_001B1240::bfmeAdd(float value, int first, int second)
{
	m_bfmeSecond[first] += value;
	m_bfmeMaskSecond |= (1 << first);

	if (first != second)
	{
		m_bfmeFirst[second] += value;
		m_bfmeMaskFirst |= (1 << second);
	}
}
