// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F75F0. Set +0x29 and +0x2A to 1.

class Gen_006f75f0
{
public:
	void set(void);

private:
	unsigned char m_pad[0x29];
	unsigned char m_29;
	unsigned char m_2a;
};

// ?set@Gen_006f75f0@@QAEXXZ
void Gen_006f75f0::set(void)
{
	m_2a = 1;
	m_29 = 1;
}
