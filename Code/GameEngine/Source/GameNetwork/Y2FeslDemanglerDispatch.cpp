// cl: /GX-
// jabba gamebrowserdemangler.cpp inbound dispatch @ 0x00800E50 (230B).
// Logs "<-D", promotes raw header into Rva007E8810, switches on FourCC:
// ECHO -> onConnectReply; PROB+flag -> bfmeDo1052; PROB -> bfmeFreeVNC.

class Rva007E8810Message
{
public:
	Rva007E8810Message();                                              // 0x007E8810
	~Rva007E8810Message();                                             // 0x007E86C0
	int getInt( const char *key, int defaultValue );                   // 0x007E8900

	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	unsigned m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30;
	char m_pad31[3];
};

struct Rva00800E50Header
{
	unsigned m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
};

struct Rva00800E50Stamp
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

void __cdecl Rva007F91D0( Rva00800E50Header *hdr, const char *dir );

class Rva00800E50Owner
{
public:
	void onDispatch( Rva00800E50Header *hdr );
	void onConnectReply( Rva007E8810Message *msg );                    // 0x00800780
	void bfmeDo1052( int a, Rva00800E50Stamp *p, int r );              // 0x00800BD0
	void bfmeFreeVNC( Rva007E8810Message *msg );                       // 0x00800CD0
};

void Rva00800E50Owner::onDispatch( Rva00800E50Header *hdr )
{
	int flags;
	char flagged;

	flags = hdr->m_04;
	// Bit-form of the sign test emits retail's jns (flags < 0 emits jge).
	if( ( flags & 0x80000000 ) && ( flags & 0x40000000 ) )
		flagged = 1;
	else
		flagged = 0;

	Rva007F91D0( hdr, "<-D" );

	{
		Rva007E8810Message msg;
		// Counter-swap load temps so MSVC emits retail [esi+0xc] then [esi+8].
		int first;
		int second;
		int t04;
		int t18;
		unsigned type;
		int t1c;
		int t20;

		first = hdr->m_0C;
		second = hdr->m_08;
		t04 = hdr->m_04;
		msg.m_10 = second;
		t18 = hdr->m_18;
		msg.m_14 = first;
		type = hdr->m_00;
		msg.m_20 = t04;
		t1c = hdr->m_1C;
		msg.m_04 = t18;
		t20 = hdr->m_20;
		msg.m_1C = type;
		msg.m_08 = t1c;
		msg.m_0C = t20;

		if( type != 'ECHO' )
		{
			if( type == 'PROB' )
			{
				if( flagged )
					bfmeDo1052( 0, (Rva00800E50Stamp *)&msg, msg.getInt( "TID", 0 ) );
				else
					bfmeFreeVNC( &msg );
			}
		}
		else
		{
			onConnectReply( &msg );
		}
	}
}
