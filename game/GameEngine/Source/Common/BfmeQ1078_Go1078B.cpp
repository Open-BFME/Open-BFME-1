// cl: /O2
// BfmeQ1078::bfmeGo1078B, retail 0x00517AF0, 84 bytes, ret 0xC.
// Same 0x15 / byte-1 / flag-bit gate as BfmeQ1076::bfmeGo1076A, plus a
// this+0x3D8 skip and a this+0x3A8 dispatch: 1 -> landed Rva00516690,
// 4 or 9 -> landed BfmeR1102::bfmeGo1102B(0) on the same object.

class BfmeR1102
{
public:
	void bfmeGo1102B( int a );
};

void Rva00516690( void );

class BfmeQ1078
{
public:
	int bfmeGo1078B( int a, char b, char c );

	char m_bfmePad[ 0x3A8 ];
	int m_bfme3a8;
	char m_bfmePad2[ 0x3D8 - 0x3AC ];
	char m_bfme3d8;
};

int BfmeQ1078::bfmeGo1078B( int a, char b, char c )
{
	if ( !m_bfme3d8 )
	{
		if ( a == 0x15 )
		{
			int k = (unsigned char)b;
			if ( k - 1 == 0 )
			{
				if ( c & 1 )
				{
					switch ( m_bfme3a8 )
					{
					case 1:
						Rva00516690();
						return 1;
					case 4:
					case 9:
						reinterpret_cast< BfmeR1102 * >( this )->bfmeGo1102B( 0 );
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
