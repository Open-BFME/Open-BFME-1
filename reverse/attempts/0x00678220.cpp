// ?d_00678220@@YAXXZ
// partial score=0.97 date=2026-08-29
// ---------------------------------------------------------------------------
// 0x00678220 -- two byte fields against two dwords, each mismatch costing two.
//
//     movzx esi,byte [ecx+0x1fb] / cmp esi,edi / je / mov eax,2
//     movzx esi,byte [ecx+0x1fa] / cmp esi,[edx+0xc] / je / add eax,2
//     mov ecx,[ecx+0x1e0] / lea edx,[ecx+eax+8] / cmp edx,0x1dc / setle al
//
// `setle` is signed, so the budget comparison is on ints; the two field
// comparisons zero-extend a byte into a dword each, which is a `bool`-width
// member read against an int-width one.

class Open2678220Info
{
public:
	char m_pad[ 0xc ];
	int m_second;
	int m_gap;
	int m_first;
};

class Open2678220Holder
{
public:
	Open2678220Info *m_info;
};

class Rva00678220
{
public:
	char fits( const Open2678220Holder *holder ) const;

	char m_pad[ 0x1e0 ];
	int m_used;
	char m_pad2[ 0x16 ];
	unsigned char m_second;
	unsigned char m_first;
};

// @?fits@Rva00678220@@QBEDPBVOpen2678220Holder@@@Z 0x00678220
char Rva00678220::fits( const Open2678220Holder *holder ) const
{
	const Open2678220Info *info = holder->m_info;

	int cost = 0;
	if( m_first != info->m_first )
		cost = 2;
	if( m_second != info->m_second )
		cost += 2;

	return m_used + cost + 8 <= 0x1dc;
}

