// cl: /DNDEBUG /MD /EHsc
//
// Rva00608FE0Element copy constructor, retail 0x006089C0 (227 bytes).
// parseSoundUpgrade appends this 0x210-byte record to the sound-upgrade
// vector. The copy preserves its scalar fields and invokes the four member
// copy constructors used by the retail record layout.

struct BfmeLegendStringVec
{
	BfmeLegendStringVec( const BfmeLegendStringVec &other );
	~BfmeLegendStringVec();

	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
};

#pragma comment(linker, "/alternatename:??0BfmeLegendStringVec@@QAE@ABU0@@Z=?j_00015474@@YAXXZ")
#pragma comment(linker, "/alternatename:??1BfmeLegendStringVec@@QAE@XZ=??1SubsystemLegendEntry@@QAE@XZ")

struct Rva00606A80Member
{
	Rva00606A80Member( const Rva00606A80Member &other );
	~Rva00606A80Member();

	char m_body[ 0x1B4 ];
};

#pragma comment(linker, "/alternatename:??0Rva00606A80Member@@QAE@ABU0@@Z=?j_0001ff64@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00606A80Member@@QAE@XZ=??1BfmeLegendStringVec@@QAE@XZ")

struct Rva00606E60Member
{
	Rva00606E60Member( const Rva00606E60Member &other );
	~Rva00606E60Member();

	char m_body[ 0x0C ];
};

#pragma comment(linker, "/alternatename:??0Rva00606E60Member@@QAE@ABU0@@Z=?j_00032515@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00606E60Member@@QAE@XZ=??1BfmeLegendStringVec@@QAE@XZ")

struct Rva00608FE0Pod
{
	int m_first;
	int m_second;
	int m_third;
	int m_fourth;
	int m_fifth;
	int m_sixth;
};

struct Rva00608FE0Element
{
	Rva00608FE0Element( const Rva00608FE0Element &other );

	Rva00608FE0Pod m_pod0;
	Rva00608FE0Pod m_pod18;
	BfmeLegendStringVec m_member30;
	BfmeLegendStringVec m_member3C;
	Rva00606A80Member m_member48;
	Rva00606E60Member m_member1FC;
	int m_field208;
	unsigned char m_field20C;
	char m_padding20D[ 3 ];
};

Rva00608FE0Element::Rva00608FE0Element( const Rva00608FE0Element &other )
	: m_pod0( other.m_pod0 ),
	  m_pod18( other.m_pod18 ),
	  m_member30( other.m_member30 ),
	  m_member3C( other.m_member3C ),
	  m_member48( other.m_member48 ),
	  m_member1FC( other.m_member1FC )
{
	m_field208 = other.m_field208;
	m_field20C = other.m_field20C;
}
