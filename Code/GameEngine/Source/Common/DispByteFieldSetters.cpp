// 47 thirteen-byte __thiscall members with one shape:
//
//     mov al,[esp+4] / mov [ecx+<DISP>],al / ret 4
//
// One byte is taken out of a dword argument slot and stored at a fixed
// displacement from `this`.  The load is `mov al` and the store is `mov ...,al`,
// so the member is one byte wide however the argument was declared.
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

#define BFME_DISP_BYTE_SETTER( NAME, DISP )                                        \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( unsigned char value );                                      \
                                                                              \
		char          m_lead[ DISP ];                                         \
		unsigned char m_value;                                                \
	};                                                                        \
	void NAME::set( unsigned char value )                                     \
	{                                                                         \
		m_value = value;                                                      \
	}

BFME_DISP_BYTE_SETTER( Rva000F91E0ByteSlot, 0x90 )
BFME_DISP_BYTE_SETTER( Rva0010CEE0ByteSlot, 0x11D )
BFME_DISP_BYTE_SETTER( Rva00160470ByteSlot, 0x294 )
BFME_DISP_BYTE_SETTER( Rva0016A730ByteSlot, 0x336 )
BFME_DISP_BYTE_SETTER( Rva0016A7C0ByteSlot, 0x332 )
BFME_DISP_BYTE_SETTER( Rva0016A810ByteSlot, 0x335 )
BFME_DISP_BYTE_SETTER( Rva001BD390ByteSlot, 0x342 )
BFME_DISP_BYTE_SETTER( Rva001BDBB0ByteSlot, 0x32C )
BFME_DISP_BYTE_SETTER( Rva001F8490ByteSlot, 0xA0 )
BFME_DISP_BYTE_SETTER( Rva00207740ByteSlot, 0xE4 )
BFME_DISP_BYTE_SETTER( Rva00212870ByteSlot, 0xD1 )
BFME_DISP_BYTE_SETTER( Rva002196F0ByteSlot, 0x96 )
BFME_DISP_BYTE_SETTER( Rva0022F770ByteSlot, 0xE8 )
BFME_DISP_BYTE_SETTER( Rva00230840ByteSlot, 0x121 )
BFME_DISP_BYTE_SETTER( Rva002325E0ByteSlot, 0x120 )
BFME_DISP_BYTE_SETTER( Rva002897E0ByteSlot, 0x190 )
BFME_DISP_BYTE_SETTER( Rva00292F90ByteSlot, 0x337 )
BFME_DISP_BYTE_SETTER( Rva002B4300ByteSlot, 0x32F )
BFME_DISP_BYTE_SETTER( Rva002BB980ByteSlot, 0x488 )
BFME_DISP_BYTE_SETTER( Rva002C7D90ByteSlot, 0xD6 )
BFME_DISP_BYTE_SETTER( Rva002C7DB0ByteSlot, 0xD4 )
BFME_DISP_BYTE_SETTER( Rva002ED1B0ByteSlot, 0x91 )
BFME_DISP_BYTE_SETTER( Rva002ED270ByteSlot, 0x295 )
BFME_DISP_BYTE_SETTER( Rva002ED400ByteSlot, 0xBC )
BFME_DISP_BYTE_SETTER( Rva002ED3F0ByteSlot, 0x12B0 )
BFME_DISP_BYTE_SETTER( Rva002ED410ByteSlot, 0xBD )
BFME_DISP_BYTE_SETTER( Rva003828B0ByteSlot, 0x12BE )
BFME_DISP_BYTE_SETTER( Rva003967F0ByteSlot, 0x29E )
BFME_DISP_BYTE_SETTER( Rva003C5F00ByteSlot, 0xA8 )
BFME_DISP_BYTE_SETTER( Rva004021A0ByteSlot, 0x224 )
BFME_DISP_BYTE_SETTER( Rva0043A6C0ByteSlot, 0x12B2 )
BFME_DISP_BYTE_SETTER( Rva004D3E30ByteSlot, 0x429 )
BFME_DISP_BYTE_SETTER( Rva004E9B30ByteSlot, 0xA0 )
BFME_DISP_BYTE_SETTER( Rva0052ADD0ByteSlot, 0x254 )
BFME_DISP_BYTE_SETTER( Rva005B7360ByteSlot, 0x1318 )
BFME_DISP_BYTE_SETTER( Rva005BE120ByteSlot, 0x1AC )
BFME_DISP_BYTE_SETTER( Rva00637220ByteSlot, 0x6FC )
BFME_DISP_BYTE_SETTER( Rva00642B40ByteSlot, 0x3C0 )
BFME_DISP_BYTE_SETTER( Rva00642BB0ByteSlot, 0x8C )
BFME_DISP_BYTE_SETTER( Rva00642BE0ByteSlot, 0x3D8 )
BFME_DISP_BYTE_SETTER( Rva00642C40ByteSlot, 0x3E4 )
BFME_DISP_BYTE_SETTER( Rva00684C40ByteSlot, 0x3A4 )
BFME_DISP_BYTE_SETTER( Rva0073B5B0ByteSlot, 0x115 )
BFME_DISP_BYTE_SETTER( Rva00746090ByteSlot, 0x2480 )
BFME_DISP_BYTE_SETTER( Rva007460B0ByteSlot, 0x248D )
BFME_DISP_BYTE_SETTER( Rva007460D0ByteSlot, 0x248E )
BFME_DISP_BYTE_SETTER( Rva00746100ByteSlot, 0x2438 )
BFME_DISP_BYTE_SETTER( Rva00751D80ByteSlot, 0x232 )
BFME_DISP_BYTE_SETTER( Rva00751DD0ByteSlot, 0x231 )
