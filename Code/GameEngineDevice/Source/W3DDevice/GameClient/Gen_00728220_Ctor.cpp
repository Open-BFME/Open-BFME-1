// cl: /DNDEBUG /MD /EHsc

// Retail 0x00728220. Non-polymorphic constructor that zeros eight dwords,
// then two bytes and a word -- 0x24 bytes, no vptr store.

class Gen_00728220
{
public:
	Gen_00728220(void);

private:
	int m_0;
	int m_4;
	int m_8;
	int m_c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	unsigned char m_20;
	unsigned char m_21;
	unsigned short m_22;
};

// ??0Gen_00728220@@QAE@XZ
Gen_00728220::Gen_00728220(void)
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
	m_c = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_21 = 0;
	m_22 = 0;
}
