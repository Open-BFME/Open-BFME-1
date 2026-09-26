// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// The OnlineShell constructor at 0x0055D150 registers ILT 0x0002BA1C for
// OnlineAdvMode and OnlineShellStartScreen.  The callback's case 0 returns
// the shell's current file name; case 1 gets or stores the GameSpy misc
// preference named InAdvMode.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

protected:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};

class UserPreferences
{
public:
	virtual ~UserPreferences();
	void setBool( AsciiString key, bool value );
	bool getBool( AsciiString key, bool defaultValue ) const;
	virtual bool write();

private:
	unsigned char m_unmodelled[ 0x10 ];
};

class GameSpyMiscPreferences : public UserPreferences
{
public:
	GameSpyMiscPreferences();
	virtual ~GameSpyMiscPreferences();
};

#pragma comment(linker, "/alternatename:??0GameSpyMiscPreferences@@QAE@XZ=?j_000267e2@@YAXXZ")
#pragma comment(linker, "/alternatename:??1GameSpyMiscPreferences@@UAE@XZ=?j_000141a0@@YAXXZ")
#pragma comment(linker, "/alternatename:?setBool@UserPreferences@@QAEXVAsciiString@@_N@Z=?j_00017cc9@@YAXXZ")
#pragma comment(linker, "/alternatename:?getBool@UserPreferences@@QBE_NVAsciiString@@_N@Z=?j_0002c7cd@@YAXXZ")
#pragma comment(linker, "/alternatename:?write@UserPreferences@@UAE_NXZ=?j_00030495@@YAXXZ")

extern char g_bfmeJpegSingleMessage;
extern char g_bfmeJpegExtendedMessage;

class BfmeAptScreenOnlineShell
{
public:
	void _bfme_onlineAdvMode( const char *selector, void *value, bool setting );

private:
	unsigned char m_unmodelled[ 0x270 ];
	AsciiString m_fileName;
};

// ?_bfme_onlineAdvMode@BfmeAptScreenOnlineShell@@QAEXPBDPAX_N@Z
void BfmeAptScreenOnlineShell::_bfme_onlineAdvMode(
	const char *selector, void *value, bool setting )
{
	char *output = (char *)value;
	if( !setting )
		output[ 0 ] = 0;

	switch( (int)selector )
	{
	case 0:
		if( !setting )
		{
			const char *source = m_fileName.str();
			char *destination = output;
			char copied;
			do
			{
				copied = *source++;
				*destination++ = copied;
			} while( copied != 0 );
		}
		break;

	case 1:
	{
		GameSpyMiscPreferences preferences;
		if( setting )
		{
			preferences.setBool( AsciiString( "InAdvMode" ),
				output[ 0 ] == '1' || output[ 0 ] == 't' );
			preferences.write();
		}
		else
		{
			const char *source = preferences.getBool(
				AsciiString( "InAdvMode" ), false )
				? &g_bfmeJpegSingleMessage : &g_bfmeJpegExtendedMessage;
			char *destination = output;
			char copied;
			do
			{
				copied = *source++;
				*destination++ = copied;
			} while( copied != 0 );
		}
	}
		break;
	}
}
