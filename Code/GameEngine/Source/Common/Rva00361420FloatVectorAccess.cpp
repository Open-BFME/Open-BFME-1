// Address-derived reconstruction of the 67-byte retail body at RVA 0x00361420.
// The bytes prove a [first,last) array of 0x58-byte elements at +0x18/+0x1C,
// a signed bounds check, and a float-returning element call.  The rel32 call
// targets the existing retail thunk at RVA 0x0002CC5F.  Class and method names
// remain descriptive because no trustworthy higher-level identity is known.

typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt m_pad[ 0x3C / sizeof( UnsignedInt ) ];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Rva003608F0FloatElement
{
public:
	__declspec( noinline ) float value();

private:
	char m_lead[ 0x28 ];
	int m_endFrame;
	int m_startFrame;
	char m_tail[ 0x28 ];
};

float Rva003608F0FloatElement::value()
{
	UnsignedInt now = TheGameLogic->m_frame;
	int start = m_startFrame;
	UnsignedInt elapsed = now - start;
	double fraction = static_cast< float >( elapsed ) /
		static_cast< double >( m_endFrame - start );
	if ( fraction > 1.0 )
		return 1.0f;
	return fraction;
}

class Rva00361420FloatRange
{
public:
	unsigned int size() const { return m_last - m_first; }
	Rva003608F0FloatElement &operator[]( int index ) { return m_first[ index ]; }

private:
	Rva003608F0FloatElement *m_first;
	Rva003608F0FloatElement *m_last;
};

class Rva00361420FloatVector
{
public:
	float valueAt( int index );

private:
	char m_lead[ 0x18 ];
	Rva00361420FloatRange m_values;
};

float Rva00361420FloatVector::valueAt( int index )
{
	if ( index >= 0 && static_cast<unsigned int>( index ) < m_values.size() ) {
		return m_values[ index ].value();
	}

	return 0.0f;
}
