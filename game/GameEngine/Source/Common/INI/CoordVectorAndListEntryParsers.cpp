// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: four small INI field parsers from retail TUs built with STLport
// exceptions off.  Two (0x000BF470 and 0x000BF4E0, 81 B each) scan a Coord3D
// and push it onto one of two list<Coord3D> objects the instance points at
// (pointers at +0xA8 and +0xAC; the same bytes would also read as push_front
// on value members): the list push_back is inline (node from the node allocator, the
// element copied by the out-of-line _Copy_Construct body, four link stores).
// Two (0x003BADA0 and 0x0061ACA0, 94 B, byte twins in different retail TUs)
// scan a Coord2D and push it onto the vector<Coord2D> the store argument
// points at: the inline push_back fast path with the out-of-line copy plus
// the _M_insert_overflow slow path.  Retail did not inline the copy-construct
// helpers (they are the 23/29-byte template-grid bodies at 0x001E21F0 and
// 0x000B73B0) while the vendor headers do so the containers are modelled by
// hand.  Owner classes and field names are address-derived.

#define NULL 0

struct Coord2D
{
	float x, y;
};

struct Coord3D
{
	float x, y, z;
};

class INI
{
public:
	static void parseCoord2D( INI *ini, void *instance, void *store, const void *userData );
	static void parseCoord3D( INI *ini, void *instance, void *store, const void *userData );
};

struct Rva000BF470FalseType
{
	Rva000BF470FalseType() {}
};

void *__cdecl Rva0082E540NodeAllocate( unsigned int bytes );
void __cdecl Rva000B73B0CopyConstruct( Coord3D *where, const Coord3D &value );
void __cdecl Rva001E21F0CopyConstruct( Coord2D *where, const Coord2D &value );

struct Rva000BF470ListNode
{
	Rva000BF470ListNode *m_next;
	Rva000BF470ListNode *m_prev;
	Coord3D m_data;
};

class Rva000BF470List
{
public:
	void push_back( const Coord3D &value )
	{
		Rva000BF470ListNode *position = m_node;
		Rva000BF470ListNode *node = (Rva000BF470ListNode *)Rva0082E540NodeAllocate( sizeof( Rva000BF470ListNode ) );
		Rva000B73B0CopyConstruct( &node->m_data, value );
		Rva000BF470ListNode *previous = position->m_prev;
		node->m_next = position;
		node->m_prev = previous;
		previous->m_next = node;
		position->m_prev = node;
	}

private:
	Rva000BF470ListNode *m_node;
};

struct Rva000BF470Owner
{
	char m_unreconstructed[ 0xA8 ];
	Rva000BF470List *m_pointsA;
	Rva000BF470List *m_pointsB;
};

class Rva000BF470
{
public:
	static void parseCoord3DListA( INI *ini, void *instance, void *store, const void *userData );
	static void parseCoord3DListB( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseCoord3DListA@Rva000BF470@@SAXPAVINI@@PAX1PBX@Z
void Rva000BF470::parseCoord3DListA( INI *ini, void *instance, void *, const void * )
{
	Coord3D point;
	INI::parseCoord3D( ini, NULL, &point, NULL );
	((Rva000BF470Owner *)instance)->m_pointsA->push_back( point );
}

// ?parseCoord3DListB@Rva000BF470@@SAXPAVINI@@PAX1PBX@Z
void Rva000BF470::parseCoord3DListB( INI *ini, void *instance, void *, const void * )
{
	Coord3D point;
	INI::parseCoord3D( ini, NULL, &point, NULL );
	((Rva000BF470Owner *)instance)->m_pointsB->push_back( point );
}

class Rva003BADA0Vector
{
public:
	void push_back( const Coord2D &value )
	{
		if( m_finish != m_endOfStorage )
		{
			Rva001E21F0CopyConstruct( m_finish, value );
			++m_finish;
		}
		else
			_M_insert_overflow( m_finish, value, Rva000BF470FalseType(), 1, true );
	}

private:
	void _M_insert_overflow( Coord2D *pos, const Coord2D &value, const Rva000BF470FalseType &, unsigned int n, bool atEnd );

	Coord2D *m_start;
	Coord2D *m_finish;
	Coord2D *m_endOfStorage;
};

class Rva003BADA0
{
public:
	static void parseCoord2DVectorEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseCoord2DVectorEntry@Rva003BADA0@@SAXPAVINI@@PAX1PBX@Z
void Rva003BADA0::parseCoord2DVectorEntry( INI *ini, void *instance, void *store, const void * )
{
	Coord2D point;
	INI::parseCoord2D( ini, instance, &point, NULL );
	((Rva003BADA0Vector *)store)->push_back( point );
}

class Rva0061ACA0
{
public:
	static void parseCoord2DVectorEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseCoord2DVectorEntry@Rva0061ACA0@@SAXPAVINI@@PAX1PBX@Z
void Rva0061ACA0::parseCoord2DVectorEntry( INI *ini, void *instance, void *store, const void * )
{
	Coord2D point;
	INI::parseCoord2D( ini, instance, &point, NULL );
	((Rva003BADA0Vector *)store)->push_back( point );
}
