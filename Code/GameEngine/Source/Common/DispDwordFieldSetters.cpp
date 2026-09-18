// 53 thirteen-byte __thiscall members with one shape:
//
//     mov eax,[esp+4] / mov [ecx+<DISP>],eax / ret 4
//
// One dword argument is stored at a fixed displacement from `this` and nothing
// is returned -- `ret 4` with eax never set up as a result.  The mirror image of
// DispDwordFieldGetters.cpp, and every displacement here is likewise a multiple
// of four.
//
// WHAT THE BYTES SHOW AND WHAT THEY DO NOT.  The displacement is a disp32 in
// every member -- MSVC 7.1 uses disp8 whenever the offset fits in a signed
// byte, so every offset here is at least 0x80, and the encoding itself is why
// this family is separable from the far larger disp8 one.  The operand size and
// the displacement are read straight off the instruction stream; nothing else
// about these functions is asserted.  Members before the accessed one are
// spelled as a lead array because their types are not witnessed here, only
// their total size.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define BFME_DISP_DWORD_SETTER( NAME, DISP )                                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( int value );                                                \
                                                                              \
		char m_lead[ DISP ];                                                  \
		int  m_value;                                                         \
	};                                                                        \
	void NAME::set( int value )                                               \
	{                                                                         \
		m_value = value;                                                      \
	}

BFME_DISP_DWORD_SETTER( Rva000C97B0DwordSlot, 0x260 )
BFME_DISP_DWORD_SETTER( Rva000C9870DwordSlot, 0x6A0 )
BFME_DISP_DWORD_SETTER( Rva000C9C60DwordSlot, 0x644 )
BFME_DISP_DWORD_SETTER( Rva000DF1E0DwordSlot, 0x274 )
BFME_DISP_DWORD_SETTER( Rva00133C20DwordSlot, 0x38C )
BFME_DISP_DWORD_SETTER( Rva0014FD70DwordSlot, 0x31C )
BFME_DISP_DWORD_SETTER( Rva00150020DwordSlot, 0x21C )
BFME_DISP_DWORD_SETTER( Rva001B40A0DwordSlot, 0x470 )
BFME_DISP_DWORD_SETTER( Rva001BD450DwordSlot, 0x358 )
BFME_DISP_DWORD_SETTER( Rva001BD6C0DwordSlot, 0x2EC )
BFME_DISP_DWORD_SETTER( Rva001BEC40DwordSlot, 0x314 )
BFME_DISP_DWORD_SETTER( Rva001BF400DwordSlot, 0x19C )
BFME_DISP_DWORD_SETTER( Rva001D3ED0DwordSlot, 0x348 )
BFME_DISP_DWORD_SETTER( Rva001D3F20DwordSlot, 0x348 )
BFME_DISP_DWORD_SETTER( Rva001F83F0DwordSlot, 0xA8 )
BFME_DISP_DWORD_SETTER( Rva00201AD0DwordSlot, 0xB0 )
BFME_DISP_DWORD_SETTER( Rva00230790DwordSlot, 0xE8 )
BFME_DISP_DWORD_SETTER( Rva0025A780DwordSlot, 0x18F8 )
BFME_DISP_DWORD_SETTER( Rva0025D930DwordSlot, 0xAC )
BFME_DISP_DWORD_SETTER( Rva0026FE90DwordSlot, 0x168 )
BFME_DISP_DWORD_SETTER( Rva0029BBA0DwordSlot, 0x258 )
BFME_DISP_DWORD_SETTER( Rva002A5930DwordSlot, 0x3A0 )
BFME_DISP_DWORD_SETTER( Rva002AB3A0DwordSlot, 0x2E4 )
BFME_DISP_DWORD_SETTER( Rva002BB8C0DwordSlot, 0x468 )
BFME_DISP_DWORD_SETTER( Rva002BB910DwordSlot, 0x478 )
BFME_DISP_DWORD_SETTER( Rva002BB9D0DwordSlot, 0x3F8 )
BFME_DISP_DWORD_SETTER( Rva002BB9E0DwordSlot, 0x3FC )
BFME_DISP_DWORD_SETTER( Rva003D5620DwordSlot, 0x844 )
BFME_DISP_DWORD_SETTER( Rva00410610DwordSlot, 0x2F0 )
BFME_DISP_DWORD_SETTER( Rva00410C60DwordSlot, 0xE0 )
BFME_DISP_DWORD_SETTER( Rva0042E320DwordSlot, 0x2E8 )
BFME_DISP_DWORD_SETTER( Rva0047A330DwordSlot, 0x1C8 )
BFME_DISP_DWORD_SETTER( Rva0049D010DwordSlot, 0x26C )
BFME_DISP_DWORD_SETTER( Rva004AB820DwordSlot, 0x294 )
BFME_DISP_DWORD_SETTER( Rva004F9540DwordSlot, 0x41C )
BFME_DISP_DWORD_SETTER( Rva004F9570DwordSlot, 0x42C )
BFME_DISP_DWORD_SETTER( Rva004F9580DwordSlot, 0x430 )
BFME_DISP_DWORD_SETTER( Rva004F95A0DwordSlot, 0x434 )
BFME_DISP_DWORD_SETTER( Rva004F95C0DwordSlot, 0x438 )
BFME_DISP_DWORD_SETTER( Rva004F95E0DwordSlot, 0x454 )
BFME_DISP_DWORD_SETTER( Rva00537520DwordSlot, 0x460 )
BFME_DISP_DWORD_SETTER( Rva005A6380DwordSlot, 0x1B4 )
BFME_DISP_DWORD_SETTER( Rva00642C00DwordSlot, 0x3E0 )
BFME_DISP_DWORD_SETTER( Rva00642C20DwordSlot, 0x3DC )
BFME_DISP_DWORD_SETTER( Rva006516C0DwordSlot, 0x464 )
BFME_DISP_DWORD_SETTER( Rva00662990DwordSlot, 0x344 )
BFME_DISP_DWORD_SETTER( Rva006C5BB0DwordSlot, 0x3018 )
BFME_DISP_DWORD_SETTER( Rva006C5BC0DwordSlot, 0x301C )
BFME_DISP_DWORD_SETTER( Rva006E1830DwordSlot, 0xA8 )
BFME_DISP_DWORD_SETTER( Rva006E7B00DwordSlot, 0x868 )
BFME_DISP_DWORD_SETTER( Rva00746010DwordSlot, 0x23C4 )
BFME_DISP_DWORD_SETTER( Rva00746150DwordSlot, 0x23BC )
BFME_DISP_DWORD_SETTER( Rva00751BB0DwordSlot, 0x314 )
BFME_DISP_DWORD_SETTER( Rva008A0C20DwordSlot, 0x129C )
BFME_DISP_DWORD_SETTER( Rva00955B50DwordSlot, 0xEC )
