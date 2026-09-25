// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
//
// Retail 0x005EE460, 62 bytes through the int3 run at +0x3E.  Its only
// references are .rdata slots 0x0111250C and 0x01112AF8 holding its ILT
// 0x00003F62; no class owning them is named, so the name keeps the address.
// Kind 3 is the one real test: the slot selected by +0x58 is empty and the
// float at +0x50 is under 0.01.  That arm returns a 32-bit 0/1 while the
// constant arms return 8-bit, which is why the retail tails differ in width.

struct Rva005EE460Slot
{
	int m_value;
	int m_unmodelled04;
};

class Rva005EE460Owner
{
public:
	bool test( int kind ) const;
private:
	char m_unmodelled00[ 0x14 ];
	Rva005EE460Slot m_slots[ 7 ];
	char m_unmodelled4C[ 4 ];
	float m_value50;
	char m_unmodelled54[ 4 ];
	int m_index58;
};

bool Rva005EE460Owner::test( int kind ) const
{
	switch( kind )
	{
	case 3:
		return m_slots[ m_index58 ].m_value == 0 && m_value50 < 0.01f;
	case 4:
		return false;
	}
	return true;
}
