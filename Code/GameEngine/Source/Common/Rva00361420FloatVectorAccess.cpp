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

	int m_unknown0;
	int m_id;
	char m_name[ 0x18 ];
	int m_state;
	int m_duration;
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
	Rva003608F0FloatElement &operator[]( unsigned int index ) { return m_first[ index ]; }
	const Rva003608F0FloatElement &operator[]( unsigned int index ) const { return m_first[ index ]; }
	Rva003608F0FloatElement &operator[]( int index ) { return m_first[ index ]; }
	const Rva003608F0FloatElement &operator[]( int index ) const { return m_first[ index ]; }

private:
	Rva003608F0FloatElement *m_first;
	Rva003608F0FloatElement *m_last;
};


class Rva00361420FloatVector
{
public:
	void resetAllStates();
	int getState( int index ) const;
	void startState( int index );
	float valueAt( int index );
	int getRemainingFrames( int index ) const;
	int findFirstNamedId() const;

private:
	char m_lead[ 0x18 ];
	Rva00361420FloatRange m_values;
};

void Rva00361420FloatVector::resetAllStates()
{
	for ( unsigned int i = 0; i < m_values.size(); ++i ) {
		m_values[ i ].m_state = 1;
	}
}

int Rva00361420FloatVector::getState( int index ) const
{
	if ( index >= 0 && static_cast<unsigned int>( index ) < m_values.size() ) {
		return m_values[ index ].m_state;
	}

	return 1;
}

void Rva00361420FloatVector::startState( int index )
{
	if ( index >= 0 && static_cast<unsigned int>( index ) < m_values.size() ) {
		Rva003608F0FloatElement &elem = m_values[ index ];
		if ( elem.m_state == 0 ) {
			elem.m_state = 2;
			elem.m_startFrame = TheGameLogic->m_frame;
			elem.m_endFrame = TheGameLogic->m_frame + elem.m_duration;
		}
	}
}

float Rva00361420FloatVector::valueAt( int index )
{
	if ( index >= 0 && static_cast<unsigned int>( index ) < m_values.size() ) {
		return m_values[ index ].value();
	}

	return 0.0f;
}

int Rva00361420FloatVector::getRemainingFrames( int index ) const
{
	if ( index >= 0 && static_cast<unsigned int>( index ) < m_values.size() ) {
		const Rva003608F0FloatElement &elem = m_values[ index ];
		int frame = TheGameLogic->m_frame;
		if ( frame < elem.m_endFrame ) {
			return elem.m_endFrame - frame;
		}
	}

	return 0;
}


int Rva00361420FloatVector::findFirstNamedId() const
{
	for ( unsigned int i = 0; i < m_values.size(); ++i ) {
		if ( m_values[ i ].m_name[ 0 ] != '\0' ) {
			return m_values[ i ].m_id;
		}
	}

	return -1;
}

