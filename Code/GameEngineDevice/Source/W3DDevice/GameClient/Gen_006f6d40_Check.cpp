// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F6D40. return m_94 && m_90 != 2.

class Gen_006f6d40
{
public:
	int check(void) const;

private:
	unsigned char m_pad90[0x90];
	int m_90;
	unsigned char m_94;
};

// ?check@Gen_006f6d40@@QBEHXZ
int Gen_006f6d40::check(void) const
{
	if (m_94 && m_90 != 2)
		return 1;
	return 0;
}
