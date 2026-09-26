// cl: /DNDEBUG /MD /EHsc

// Gen_004B1720 reset, retail 0x004B19A0, 50 bytes.
// Same layout as BfmeB1044 (0x004B17E0): after bfmeClear, the 0x20/0x24 and
// 0x28/0x2C pairs are stored y-then-x. Byte at +8 is cleared first so MSVC
// keeps the zero in ebx across the call.

class Gen_004B1720
{
public:
	void bfmeClear(void);
	void bfmeReset(void);

private:
	char m_pad0[8];
	unsigned char m_flag;			// +0x08
	char m_pad1[0x18 - 9];
	int m_18;				// +0x18
	int m_1c;				// +0x1C
	int m_20;				// +0x20
	int m_24;				// +0x24
	int m_28;				// +0x28
	int m_2c;				// +0x2C
	int m_30;				// +0x30
	int m_34;				// +0x34
	int m_38;				// +0x38
	int m_3c;				// +0x3C
	int m_40;				// +0x40
};

void Gen_004B1720::bfmeReset(void)
{
	m_flag = 0;
	bfmeClear();
	m_18 = 0;
	m_1c = 0;
	m_24 = 0;
	m_20 = 0;
	m_2c = 0;
	m_28 = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
	m_3c = 0;
	m_40 = 0;
}
