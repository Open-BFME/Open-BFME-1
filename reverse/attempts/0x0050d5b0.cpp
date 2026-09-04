// ?SetBannerState@@YAXHI@Z
// partial score=0.94 date=2026-09-04
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
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }
};

class WindowManager
{
public:
	int unidentified_00036854( const AsciiString &movie );
	void unidentified_00015235( int movie, const char *function, int argumentCount,
		const void *argument1, const void *argument2, const void *argument3,
		const void *argument4, const void *argument5 );
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

void AddBanner( int id, const AsciiString &name, const AsciiString &label )
{
	char idText[ 16 ];
	sprintf( idText, "%d", id );
	AsciiString movie( "BannerUI.apt" );
	g_theWindowManager->unidentified_00015235(
		g_theWindowManager->unidentified_00036854( movie ),
		"AddBanner", 3, idText, name.str(), label.str(), 0, 0 );
}

void SetBannerState( int id, unsigned int state )
{
	char idText[ 16 ];
	const char *label;
	sprintf( idText, "%d", id );
	switch( state )
	{
	case 0: label = "_available"; break;
	case 1: label = "_engaging"; break;
	case 2: label = "_waiting"; break;
	case 3: label = "_disabled"; break;
	default: return;
	}
	AsciiString movie( "BannerUI.apt" );
	g_theWindowManager->unidentified_00015235(
		g_theWindowManager->unidentified_00036854( movie ),
		"SetBannerState", 2, idText, label, 0, 0, 0 );
}

void SetBannerProgress( int id, int progress )
{
	char idText[ 16 ];
	char progressText[ 16 ];
	sprintf( idText, "%d", id );
	sprintf( progressText, "%d", progress );
	AsciiString movie( "BannerUI.apt" );
	g_theWindowManager->unidentified_00015235(
		g_theWindowManager->unidentified_00036854( movie ),
		"SetBannerProgress", 2, idText, progressText, 0, 0, 0 );
}
