// cl: /DNDEBUG /MD /EHsc
// ?fits@Rva00678220@@QBEDPBVOpen2678220Holder@@@Z

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

char Rva00678220::fits( const Open2678220Holder *holder ) const
{
	int cost = 0;
	const Open2678220Info *info = holder->m_info;

	if( m_first != info->m_first )
		cost = 2;
	if( m_second != info->m_second )
		cost += 2;

	return m_used + cost + 8 <= 0x1dc;
}
