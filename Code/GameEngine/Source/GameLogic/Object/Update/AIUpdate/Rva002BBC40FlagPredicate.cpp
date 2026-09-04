// cl: /DNDEBUG /MD
//
// Address-derived recovery of the flag and range predicate at retail RVA
// 0x002BBC40.  The lookup helper is the retail ILT at 0x000479BA; the two
// coordinate fields and the frame gate are fixed by the body itself.

typedef unsigned int UnsignedInt;

struct Rva002BBC40Coord3D
{
	float m_x;
	float m_y;
	float m_z;
};

struct Rva002BBC40Scratch
{
	float m_xDifference;
	int m_unused04;
	int m_unused08;
};

struct Rva002BBC40Point
{
	unsigned char m_unreconstructed000[ 0x38 ];
	Rva002BBC40Coord3D m_position;

	Rva002BBC40Coord3D *getPosition()
	{
		return &m_position;
	}
};

class Rva002BBC40FrameSource
{
private:
	unsigned char m_unreconstructed000[ 0x3c ];

public:
	UnsignedInt m_frame3c;
};

class Rva002BBC40Owner
{
public:
	virtual void ownerAnchor();
	unsigned char check( void *key );

private:
	volatile unsigned char m_flagByte04;
	float m_x08;
	float m_y0c;
	unsigned char m_unreconstructed010[ 4 ];
	float m_limit14;
	UnsignedInt m_frameLimit18;
};

extern Rva002BBC40FrameSource *g_Rva002F0898;
extern void j_000479ba();

typedef Rva002BBC40Point *(__fastcall *Rva002BBC40Lookup)( void *key );

// ?check@Rva002BBC40Owner@@QAE_NPAX@Z
unsigned char Rva002BBC40Owner::check( void *key )
{
	Rva002BBC40Point *point =
		((Rva002BBC40Lookup)j_000479ba)( key );
	if ( point == 0 )
	{
		unsigned char flag = m_flagByte04;
		flag >>= 2;
		flag &= 1;
		return flag;
	}

	UnsignedInt flags = *(UnsignedInt *)&m_flagByte04;
	Rva002BBC40FrameSource *frameSource = g_Rva002F0898;
	if ( (flags & 2) != 0 &&
		frameSource->m_frame3c >= m_frameLimit18 )
		return 1;

	if ( (flags & 1) != 0 )
	{
		point = ((Rva002BBC40Lookup)j_000479ba)( key );
		Rva002BBC40Coord3D *position = point->getPosition();
		volatile float *yField = &position->m_y;
		float yDifference = *yField;
		Rva002BBC40Scratch scratch;
		*(volatile float *)&scratch.m_xDifference = position->m_x - m_x08;
		yDifference -= m_y0c;
		float ySquare = yDifference;
		ySquare *= yDifference;
		if ( ySquare + scratch.m_xDifference * scratch.m_xDifference > m_limit14 )
			return true;
	}
	return false;
}
