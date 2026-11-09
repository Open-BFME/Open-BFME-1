// Open-BFME5 conversions.

// Retail 0x01128428 is the vftable COMDAT ??_7Rva007AFF00Owner@@6B@ (dir32_addresses.csv), which
// Rva007AFF00OwnerDtor.cpp emits; the stand-in name g_bfmeVftSE resolved nothing.
extern "C" void *__identifier("??_7Rva007AFF00Owner@@6B@")[];

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
	m_bfme00 = __identifier("??_7Rva007AFF00Owner@@6B@");
	reinterpret_cast<Rva007AEB70State *>(this)->initializeFields();
}
