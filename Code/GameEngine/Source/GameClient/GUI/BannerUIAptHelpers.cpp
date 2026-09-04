// cl: /DNDEBUG /MD /EHsc
//
// BannerUI.apt helpers at 0x0050D400..0x0050D6C0. DeleteBanner is reloc-named
// by the matched BannerUI::removeMovieBanner caller; the three siblings share
// the same sprintf / BannerUI.apt lookup / scripted-UI dispatch shape.

extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *destination, const char *format, ... );

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class WindowManager
{
public:
	int unidentified_00036854( const AsciiString &movie );
	void unidentified_00015235( int movie, const char *function, int argumentCount,
		const void *argument1, const void *argument2, int unused1, int unused2,
		int unused3 );
};

extern WindowManager *g_theWindowManager;

void DeleteBanner( int id )
{
	char idText[ 16 ];
	sprintf( idText, "%d", id );
	AsciiString movie( "BannerUI.apt" );
	g_theWindowManager->unidentified_00015235(
		g_theWindowManager->unidentified_00036854( movie ),
		"DeleteBanner", 1, idText, 0, 0, 0, 0 );
}
