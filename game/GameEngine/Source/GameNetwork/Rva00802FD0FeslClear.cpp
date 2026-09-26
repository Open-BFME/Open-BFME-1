// cl: /GX-
// Rva00803080 teardown companion of set/removePendingRequest: drop from the
// service list while pending, free the 0x10-stride request block, clear the
// DirtySock ping ref at +8.

struct Rva00807BA0Ping;
struct Rva00808140Ref;
void Rva00808140( Rva00808140Ref *ref );

struct Rva00803080Request
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;

	static void operator delete( void *block, unsigned int size );
};

struct Rva007EAServiceList
{
	void remove( class Rva00803080 *owner );
};

struct Rva007EAServiceHub
{
	char m_pad[0x0C];
	Rva007EAServiceList *m_services;
};

class Rva00803080
{
public:
	void clear();

	void *m_00;
	Rva007EAServiceHub *m_04;
	Rva00808140Ref *m_08;
	Rva00803080Request *m_0C;
	int m_10;
};

void Rva00803080::clear()
{
	if( m_10 > 0 )
		m_04->m_services->remove( this );

	if( m_0C )
	{
		Rva00803080Request::operator delete( m_0C, sizeof( Rva00803080Request ) );
		m_0C = 0;
	}

	m_10 = 0;

	if( m_08 )
	{
		Rva00808140( m_08 );
		m_08 = 0;
	}
}
