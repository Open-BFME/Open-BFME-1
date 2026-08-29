// ?selectAndCall@Rva00479270Router@@QAEHXZ
// partial score=0.91 date=2026-08-29
class Rva00479270Router
{
public:
	virtual int slot0( void ) = 0;
	virtual int slot1( void ) = 0;

	int selectAndCall( void );

private:
	Rva00479270Router *m_primary;
	Rva00479270Router *m_fallback;
};

int Rva00479270Router::selectAndCall( void )
{
	if ( m_primary )
	{
		return m_primary->slot1();
	}

	return m_fallback->slot1();
}
