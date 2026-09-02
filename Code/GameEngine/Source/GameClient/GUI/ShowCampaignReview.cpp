// cl: /DNDEBUG /MD
//
// Retail 0x0050DCB0: BFME replacement of ZH TheShell->push for CampaignReview.
// Returns true at once if the CampaignReview singleton at 0x012F495C exists;
// otherwise Shell::push("CampaignReview.apt", false).  No /EHsc: retail
// carries the by-value stash without a registered handler.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void push( AsciiString filename, bool shutdownImmediate = false );
};

extern Shell *TheShell;
extern void *g_obj12F495C;

// ?_bfme_showCampaignReview@@YA_NXZ
bool _bfme_showCampaignReview( void )
{
	if( g_obj12F495C == 0 )
		TheShell->push( AsciiString( "CampaignReview.apt" ), false );
	return true;
}
