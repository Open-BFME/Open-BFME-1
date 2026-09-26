// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include <string.h>

// SaveLoad.apt's provider callback.  The constructor registers this member
// together with a small integer selector; retail passes that selector through
// the callback's pointer-shaped argument.
class BfmeAptScreenSaveLoad
{
public:
	void _bfme_provide( const char *selector, void *value, bool setting );

private:
	char m_unmodelled[ 0x270 ];
	int m_field270;
	int m_field274;
};

// ?_bfme_provide@BfmeAptScreenSaveLoad@@QAEXPBDPAX_N@Z
void BfmeAptScreenSaveLoad::_bfme_provide(
	const char *selector, void *value, bool setting )
{
	char *text = (char *)value;
	int which = (int)selector;
	text[ 0 ] = '0';
	text[ 1 ] = 0;

	switch( which )
	{
		case 0:
			if( !setting )
			{
				if( m_field270 == 3 )
					strcpy( text, "Save" );
				else if( m_field270 == 2 )
					strcpy( text, "Load" );
			}
			break;

		case 1:
			if( !setting )
			{
				text[ 0 ] = 0;
				if( m_field274 & 1 )
					strcat( text, "Campaign" );
				if( m_field274 & 2 )
					strcat( text, "Skirmish" );
				if( m_field274 & 4 )
					strcat( text, "Replay" );
			}
			break;
	}
}
