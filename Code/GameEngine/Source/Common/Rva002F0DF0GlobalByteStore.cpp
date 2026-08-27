// Open-BFME: global byte store reconstructed from retail RVA 0x002F0DF0.

class Rva002F0DF0Global
{
public:
	char m_pad0[0xBD];
	unsigned char m_flag;
};

extern Rva002F0DF0Global *g_Rva002F0DF0Global;

void __stdcall Rva002F0DF0Store(unsigned char value)
{
	g_Rva002F0DF0Global->m_flag = value;
}
