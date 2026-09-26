// cl: /DNDEBUG /MD /EHsc

// Retail 0x006E82E0. Scale/color reset: six 1.0f stores then 0, 1, 0.

class Gen_006e82e0
{
public:
	void reset(void);

private:
	int m_0;
	int m_4;
	int m_8;
	float m_c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
};

// ?reset@Gen_006e82e0@@QAEXXZ
void Gen_006e82e0::reset(void)
{
	m_18 = 1.0f;
	m_1c = 1.0f;
	m_20 = 1.0f;
	m_c = 1.0f;
	m_10 = 1.0f;
	m_14 = 1.0f;
	m_4 = 0;
	m_0 = 1;
	m_8 = 0;
}
