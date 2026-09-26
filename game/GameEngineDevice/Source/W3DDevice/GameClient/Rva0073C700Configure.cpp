// cl: /DNDEBUG /MD
// Address-derived reconstruction of retail 0x0073C700.

class Gen0002A1B2
{
public:
	void set(int first, int second, float duration);

	char m_body[8];
};

class Rva0073C700
{
public:
	virtual void dummy();
	void configure(int value, int duration, int first, int second, int stored, int unused);

	int m_04;
	int m_08;
	int m_0c;
	Gen0002A1B2 m_ease;
	int m_18;
	int m_1c;
	int m_20;
	char m_24;
	int m_28;
	char m_padding2c[0x1864 - 0x2c];
	int m_values[0x101];
	char m_padding1c68[0x1c74 - 0x1c68];
	int m_filled[0xff];
	int m_numValues;
};

void Rva0073C700::configure(int value, int duration, int first, int second, int stored, int unused)
{
	int i = 0;
	while (i < 0x101)
	{
		m_values[i] = 0;
		++i;
	}
	i = 0;
	while (i < 0xff)
	{
		m_filled[i] = 0;
		++i;
	}
	i = 0;
	if (m_numValues > 0)
	{
		do
		{
			m_filled[i] = value;
			++i;
		} while (i < m_numValues);
	}
	m_04 = duration > 1 ? duration : 1;
	m_08 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_28 = 1;
	m_ease.set(first, second, (float)duration);
	m_0c = stored;
	m_24 = 1;
}
