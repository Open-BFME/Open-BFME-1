// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F6D70. m_94 = 1; m_28 = 0.

class Gen_006f6d70
{
public:
	void reset(void);

private:
	unsigned char m_pad28[0x28];
	int m_28;
	unsigned char m_pad94[0x94 - 0x2C];
	unsigned char m_94;
};

// ?reset@Gen_006f6d70@@QAEXXZ
void Gen_006f6d70::reset(void)
{
	m_94 = 1;
	m_28 = 0;
}
