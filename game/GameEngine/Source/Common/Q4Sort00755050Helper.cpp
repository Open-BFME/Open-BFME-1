// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

class Drawable
{
public:
	DrawableID getID( void ) const;
};

class Rva00765AC0
{
public:
	unsigned char ready( void ) const;
};

class GameLODManager
{
public:
	char m_pad[ 0x170c ];
	int m_level;
};

extern GameLODManager *TheGameLODManager;

struct Q4Sort00751F50Record
{
	char m_pad00[ 8 ];
	Drawable *m_drawable;
	char m_pad0c[ 8 ];
	Rva00765AC0 *m_state;

	bool compare( const Q4Sort00751F50Record &other, int *outLeft,
		int *outRight ) const;
};

// Retail RVA 0x00751F50. The comparator at 0x00752B80 calls this helper with
// the two nested records and two output slots. The call chain identifies the
// Drawable and ready checks, while the retail offsets identify this record's
// fields at +0x08 and +0x14.
bool Q4Sort00751F50Record::compare( const Q4Sort00751F50Record &other,
	int *outLeft, int *outRight ) const
{
	*outRight = 0;
	*outLeft = 0;
	if ( m_state == 0 )
		return false;
	else
	{
		if ( m_state != other.m_state )
			return false;

		int divisor = 3;
		if ( TheGameLODManager->m_level == 0 )
			divisor = 1;
		*outLeft = m_drawable->getID() % divisor;
		*outRight = other.m_drawable->getID() % divisor;
		return m_state->ready();
	}
}
