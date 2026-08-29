// ?d_00765ac0@@YAXXZ
// partial score=0.97 date=2026-08-28
// ---------------------------------------------------------------------------
// 0x00765AC0 -- ten slots, then two fallbacks.
//
//     xor eax,eax / lea edx,[ecx+4] / cmp [edx],0 / jne used / inc eax
//     add edx,4 / cmp eax,0xa / jb / mov al,1 / ret
//     used: mov al,[ecx+0x40] / test al,al / jne / mov eax,[ecx+0x38]
//     shr eax,5 / and al,1 / ret
//
// Two induction variables -- a walking pointer and a counter compared against
// ten -- is an indexed `for`, not a pointer scan, and `jb` makes the index
// UNSIGNED (a signed one compiles to `jl` and one byte more).  `shr 5` then `and al,1` is
// bit five of the dword at +0x38 read as a bool.

class Rva00765AC0
{
public:
	unsigned char ready( void ) const;
	int m_pad;
	void *m_slots[ 10 ];
	char m_pad2[ 0xc ];
	unsigned int m_bits;
	char m_pad3[ 4 ];
	bool m_override;
};

// @?ready@Rva00765AC0@@QBE_NXZ 0x00765AC0
unsigned char Rva00765AC0::ready( void ) const
{
	for( unsigned int i = 0; i < 10; ++i )
	{
		if( m_slots[ i ] != 0 )
		{
			if( m_override )
				return 1;
			return ( ( m_bits >> 5 ) & 1 ) != 0;
		}
	}
	return 1;
}

