// cl: /DNDEBUG /MD
// Retail RVA 0x001A1A40. Stores one argument and ten constants into a single
// object and hands the object back in eax, which is what a constructor does.
// No call, no relocation and nothing that names the owner, so the class keeps
// an address-derived name.

class Rva001A1A40Owner
{
public:
	Rva001A1A40Owner( int value );

	int m_bfmeField000;
	int m_bfmeField004;
	int m_bfmeField008;
	int m_bfmeField00C;
	int m_bfmeField010;
	int m_bfmeField014;
	unsigned char m_bfmeField018;
	unsigned char m_bfmePad019[ 0x0f ];
	int m_bfmeField028;
	unsigned char m_bfmeField02C;
	unsigned char m_bfmeField02D;
	unsigned short m_bfmeField02E;
};

Rva001A1A40Owner::Rva001A1A40Owner( int value )
{
	m_bfmeField00C = 0;
	m_bfmeField010 = value;
	m_bfmeField014 = 0;
	m_bfmeField018 = 0;
	m_bfmeField028 = 1;
	m_bfmeField02C = 1;
	m_bfmeField02D = 1;
	m_bfmeField02E = 0xffff;
	m_bfmeField000 = 0;
	m_bfmeField004 = 0;
	m_bfmeField008 = 0;
}
