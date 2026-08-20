// cl: /DNDEBUG /MD /EHsc

// Retail 0x007304B0. Store a 16-bit value at m_24[m_8 * b + a] with bounds checks.

class Gen_007304b0
{
public:
	void store(int a, int b, short v);

private:
	unsigned char m_pad8[0x08];
	int m_8;
	unsigned char m_pad20[0x20 - 0x0C];
	int m_20;
	short *m_24;
};

// ?store@Gen_007304b0@@QAEXHHF@Z
void Gen_007304b0::store(int a, int b, short v)
{
	int idx = m_8 * b + a;
	if (idx < 0)
		return;
	if (idx >= m_20)
		return;
	if (!m_24)
		return;
	m_24[idx] = v;
}
