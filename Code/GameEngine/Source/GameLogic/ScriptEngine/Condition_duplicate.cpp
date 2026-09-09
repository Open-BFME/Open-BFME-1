// cl: /DNDEBUG /MD /EHsc
// Real BFME Condition::duplicate body at RVA 0x00357D30.
//
// Identity is independently established by the matched OrCondition::duplicate
// caller at RVA 0x0035A460, which calls this body through the named
// Condition::duplicate ILT.  The Condition layout here follows the matched
// setConditionType body at 0x00355D10: m_numParms is +0x08, m_parms starts at
// +0x0c, and m_nextAndCondition is +0x3c.  The matched constructor at
// 0x00357CC0 proves the 0x4c allocation and the inline constructor stores.

typedef int Int;
typedef bool Bool;

class AsciiString
{
public:
	AsciiString &operator=( const AsciiString &other )
	{
		set( other );
		return *this;
	}
	void set( const AsciiString &other );

private:
	void *m_data;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Parameter
{
private:
	int m_paramType;
	Bool m_initialized;
	int m_int;
	float m_real;
	AsciiString m_string;
	Coord3D m_coord;
	unsigned int m_status0;
	unsigned int m_status1;
};

class ConditionDuplicateShim;

class Condition
{
public:
	enum ConditionType
	{
		CONDITION_FALSE = 0
	};

	Condition( ConditionType type );
	virtual ~Condition();
	void setConditionType( ConditionType type );

private:
	friend class ConditionDuplicateShim;
	ConditionType m_conditionType;
	int m_numParms;
	Parameter *m_parms[ 12 ];
	Condition *m_nextAndCondition;
	int m_customData;
	int m_customFrame;
	int m_hasWarnings;
};

// The named Condition::duplicate entry at 0x0001C189 is the incremental-link
// thunk.  The full body is its existing, pinned TU-local target at 0x00357D30.
class ConditionDuplicateShim
{
public:
	Condition *run() const;
};

Condition::Condition( ConditionType type ) :
	m_conditionType( type ),
	m_numParms( 0 ),
	m_nextAndCondition( 0 ),
	m_customData( 0 ),
	m_customFrame( 0 ),
	m_hasWarnings( false )
{
	for ( Int i = 0; i < 12; ++i )
		m_parms[ i ] = 0;
	setConditionType( type );
}

// ?run@ConditionDuplicateShim@@QBEPAVCondition@@XZ
Condition *ConditionDuplicateShim::run() const
{
	const Condition *self = reinterpret_cast<const Condition *>( this );
	Condition *pNew = new Condition( self->m_conditionType );
	Int i;
	for ( i = 0; i < self->m_numParms && i < pNew->m_numParms; ++i )
	{
		*pNew->m_parms[ i ] = *self->m_parms[ i ];
	}

	Condition *pLink = self->m_nextAndCondition;
	Condition *pCur = pNew;
	while ( pLink )
	{
		pCur->m_nextAndCondition = new Condition( pLink->m_conditionType );
		pCur = pCur->m_nextAndCondition;
		for ( i = 0; i < pLink->m_numParms; ++i )
		{
			*pCur->m_parms[ i ] = *pLink->m_parms[ i ];
		}
		pLink = pLink->m_nextAndCondition;
	}

	return pNew;
}
