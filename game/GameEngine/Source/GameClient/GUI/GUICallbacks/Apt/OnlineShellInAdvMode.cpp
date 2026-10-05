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
		return m_data ? (const char *)m_data + 8 : "";
	}
};

class UserPreferences
{
public:
	virtual ~UserPreferences();

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

// Retail reaches setBool, getBool and write through ILT thunks; the thunks are
// the real call targets, so name them instead of aliasing the member names.
extern void j_00017cc9();
extern void j_0002c7cd();
extern void j_00030495();

extern const char g_rva01080FC0[2];

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
			typedef void (UserPreferences::*SetBool)( AsciiString, bool );
			union { void (*fn)(); SetBool call; } setBool = { j_00017cc9 };
			(preferences.*setBool.call)( AsciiString( "InAdvMode" ),
				output[ 0 ] == '1' || output[ 0 ] == 't' );

			typedef bool (UserPreferences::*Write)();
			union { void (*fn)(); Write call; } write = { j_00030495 };
			(preferences.*write.call)();
		}
		else
		{
			typedef bool (UserPreferences::*GetBool)( AsciiString, bool ) const;
			union { void (*fn)(); GetBool call; } getBool = { j_0002c7cd };
			const char *source = (preferences.*getBool.call)(
				AsciiString( "InAdvMode" ), false )
				? g_rva01080FC0 : "0";
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
