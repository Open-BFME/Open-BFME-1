// cl: /DNDEBUG /MD /EHsc

// Retail 0x0072EB10. Zero several fields and set +0x12F9 to 1.

class Gen_0072eb10
{
public:
	void reset(void);

private:
	unsigned char m_pad0c[0x0C];
	int m_0c;
	int m_10;
	int m_14;
	unsigned char m_pad12e4[0x12E4 - 0x18];
	int m_12e4;
	int m_12e8;
	unsigned char m_12ec;
	unsigned char m_pad12f9[0x12F9 - 0x12ED];
	unsigned char m_12f9;
};

// ?reset@Gen_0072eb10@@QAEXXZ
void Gen_0072eb10::reset(void)
{
	m_12ec = 0;
	m_12f9 = 1;
	m_12e8 = 0;
	m_12e4 = 0;
	m_0c = 0;
	m_10 = 0;
	m_14 = 0;
}
