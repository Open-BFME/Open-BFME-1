// cl: /DNDEBUG /MD
// Retail 0x007AEB70: initialize the scalar tail and sixteen-entry table.

class Rva007AEB70State
{
private:
	char m_padding[0x68];
	volatile int m_value68;
	volatile int m_value6C;
	volatile int m_value70;
	volatile bool m_flag74;
	char m_padding75[3];
	volatile int m_value78;
	volatile int m_value7C;
	volatile int m_value80;
	volatile bool m_flag84;
	volatile bool m_flag85;
	char m_padding86[2];
	float m_limit88;
	float m_limit8C;
	float m_limit90;
	int m_table[16];

public:
	void initializeFields();
};

void Rva007AEB70State::initializeFields()
{
	m_value68 = 0;
	m_value6C = 0;
	m_value70 = 0;
	m_flag74 = false;
	m_value78 = 0;
	m_value7C = 0;
	m_value80 = 0;
	m_flag84 = false;
	m_flag85 = false;
	m_limit88 = -100.0f;
	m_limit8C = -100.0f;
	m_limit90 = -100.0f;
	for ( int i = 0; i < 16; ++i )
		m_table[i] = 0;
}
