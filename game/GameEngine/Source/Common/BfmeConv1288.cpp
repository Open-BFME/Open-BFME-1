// Open-BFME5 conversions.

extern void *g_bfmeVftSE[];

class BfmeB1050 { public: void bfmeBase1050(); };
class Rva007AEB70State { public: void initializeFields(); };

class BfmeThingSE
{
public:
	BfmeThingSE();
	void *m_bfme00;
	char m_bfmePad[0x54];
	int m_bfme58;
	int m_bfme5c;
	float m_bfme60;
	char m_bfme64;
};

BfmeThingSE::BfmeThingSE()
{
	reinterpret_cast<BfmeB1050 *>(this)->bfmeBase1050();
	m_bfme58 = 0;
	m_bfme5c = 0;
	m_bfme60 = 20.0f;
	m_bfme64 = 0;
	m_bfme00 = g_bfmeVftSE;
	reinterpret_cast<Rva007AEB70State *>(this)->initializeFields();
}
