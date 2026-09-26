// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" int __cdecl strcmp( const char *, const char * );

class INI
{
public:
	const char *getNextTokenOrNull( const char *seps );
	const char *getNextTokenOrNull( void )
	{
		return getNextTokenOrNull( m_seps );
	}

private:
	char m_padding[ 0x41c ];
	const char *m_seps;
};

// The PathFindRule field stores two mode bytes in its owning region
// reinforcement record.  The field table passes that record as instance and
// leaves store unused.
void parsePathFindRule( INI *ini, void *instance, void *, const void * )
{
	const char *token = ini->getNextTokenOrNull();
	if( token == 0 )
		return;

	unsigned char *mode = (unsigned char *)instance;
	if( strcmp( token, "AllRegions" ) == 0 )
	{
		mode[ 0x20 ] = 0;
		mode[ 0x21 ] = 0;
		return;
	}

	if( strcmp( token, "PlayerOwned" ) == 0 )
	{
		mode[ 0x20 ] = 0;
		mode[ 0x21 ] = 1;
		return;
	}

	if( strcmp( token, "EnabledOrPlayerOwned" ) == 0 )
	{
		mode[ 0x20 ] = 1;
		mode[ 0x21 ] = 0;
	}
}
