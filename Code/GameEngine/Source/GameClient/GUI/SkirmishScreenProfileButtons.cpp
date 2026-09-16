// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Three BfmeAptScreenSkirmish button handlers with no ledger row: retail
// 0x00579230, 0x00579240 and 0x00579250. The constructor registers them under
// the selector strings "AptSkirmish::Profile", "AptSkirmish::SkirmishProfile"
// and "AptSkirmish::Skirmish::PersonaOk". The first two set the screen mode at
// +0x400, which SkirmishScreenInitGadgets.cpp already calls m_mode, to 8. The
// third restores that mode from the saved copy at +0x404 and clears the copy.

class BfmeAptScreenSkirmish
{
public:
	void _bfme_profile( const char *name );
	void _bfme_skirmishProfile( const char *name );
	void _bfme_personaOk( const char *name );

private:
	unsigned char m_unmodelled_00[ 0x400 ];
	int m_mode;
	int m_savedMode;
};

void BfmeAptScreenSkirmish::_bfme_profile( const char *name )
{
	(void)name;
	m_mode = 8;
}

void BfmeAptScreenSkirmish::_bfme_skirmishProfile( const char *name )
{
	(void)name;
	m_mode = 8;
}

void BfmeAptScreenSkirmish::_bfme_personaOk( const char *name )
{
	(void)name;
	if( m_savedMode != -1 )
	{
		m_mode = m_savedMode;
		m_savedMode = -1;
	}
}
