// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME5: clean C++ reconstruction of InGameUI::selectMatchingAcrossScreen
// at 0x0043EF70.  The local declarations retain the BFME retail virtual slots
// used by this body without changing shared headers.

typedef int Int;
typedef char Bool;
typedef unsigned short WCHAR;

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class BfmeStateDO
{
private:
	char m_padding[0x2C];

public:
	unsigned char m_bfmeFirst;
	unsigned char m_bfmeSecond;
};

template <typename T> class StringBase
{
friend class UnicodeString;

private:
	StringBase( void );
	StringBase( const StringBase<T> &that );
	StringBase( const T *text );
	void releaseBuffer( void );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString( void ) { m_data = 0; }
	UnicodeString( const WCHAR *text )
	{
		((StringBase<WCHAR> *)this)->StringBase<WCHAR>::StringBase( text );
	}
	UnicodeString( const UnicodeString &that )
	{
		((StringBase<WCHAR> *)this)->StringBase<WCHAR>::StringBase(
			*(const StringBase<WCHAR> *)&that);
	}
	~UnicodeString( void );

private:
	void *m_data;
};

class GameTextInterface
{
public:
	virtual void vfn00( void );
	virtual void vfn01( void );
	virtual void vfn02( void );
	virtual void vfn03( void );
	virtual void vfn04( void );
	virtual void vfn05( void );
	virtual void vfn06( void );
	virtual void vfn07( void );
	virtual void vfn08( void );
	virtual void vfn09( void );
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );
};

class TacticalViewFadeShim
{
public:
	virtual void vfn00( void );
	virtual void vfn01( void );
	virtual void vfn02( void );
	virtual void vfn03( void );
	virtual void vfn04( void );
	virtual void vfn05( void );
	virtual void vfn06( void );
	virtual void vfn07( void );
	virtual void vfn08( void );
	virtual void vfn09( void );
	virtual void vfn0A( void );
	virtual void vfn0B( void );
	virtual void vfn0C( void );
	virtual void vfn0D( void );
	virtual void setWidth( Int width );
	virtual Int getWidth( void );
	virtual void setHeight( Int height );
	virtual Int getHeight( void );
	virtual void setOrigin( Int x, Int y );
	virtual void getOrigin( Int *x, Int *y );
};

class InGameUI
{
public:
	virtual void vfn00( void );
	virtual void vfn01( void );
	virtual void vfn02( void );
	virtual void vfn03( void );
	virtual void vfn04( void );
	virtual void vfn05( void );
	virtual void vfn06( void );
	virtual void vfn07( void );
	virtual void vfn08( void );
	virtual void vfn09( void );
	virtual void vfn0A( void );
	virtual void vfn0B( void );
	virtual void vfn0C( void );
	virtual void message( UnicodeString format, ... );
	virtual void vfn0E( void );
	virtual void vfn0F( void );
	virtual void vfn10( void );
	virtual void vfn11( void );
	virtual void vfn12( void );
	virtual void vfn13( void );
	virtual void vfn14( void );
	virtual void vfn15( void );
	virtual void vfn16( void );
	virtual void vfn17( void );
	virtual void vfn18( void );
	virtual void vfn19( void );
	virtual void vfn1A( void );
	virtual void vfn1B( void );
	virtual void vfn1C( void );
	virtual void vfn1D( void );
	virtual void vfn1E( void );
	virtual void vfn1F( void );
	virtual void vfn20( void );
	virtual void vfn21( void );
	virtual void vfn22( void );
	virtual void vfn23( void );
	virtual void vfn24( void );
	virtual void vfn25( void );
	virtual void vfn26( void );
	virtual void vfn27( void );
	virtual void vfn28( void );
	virtual void vfn29( void );
	virtual void vfn2A( void );
	virtual void vfn2B( void );
	virtual void vfn2C( void );
	virtual void vfn2D( void );
	virtual void vfn2E( void );
	virtual void vfn2F( void );
	virtual void vfn30( void );
	virtual void vfn31( void );
	virtual void vfn32( void );
	virtual void vfn33( void );
	virtual void vfn34( void );
	virtual void vfn35( void );
	virtual void vfn36( void );
	virtual void vfn37( void );
	virtual void vfn38( void );
	virtual void vfn39( void );
	virtual void vfn3A( void );
	virtual void vfn3B( void );
	virtual void vfn3C( void );
	virtual void vfn3D( void );
	virtual void vfn3E( void );
	virtual void vfn3F( void );
	virtual void vfn40( void );
	virtual void vfn41( void );
	virtual void vfn42( void );
	virtual void vfn43( void );
	virtual void vfn44( void );
	virtual void vfn45( void );
	virtual void vfn46( void );
	virtual void vfn47( void );
	virtual void vfn48( void );
	virtual void vfn49( void );
	virtual void vfn4A( void );
	virtual void vfn4B( void );
	virtual void vfn4C( void );
	virtual void vfn4D( void );
	virtual void vfn4E( void );
	virtual void vfn4F( void );
	virtual void vfn50( void );
	virtual void vfn51( void );
	virtual void vfn52( void );
	virtual void vfn53( void );
	virtual void vfn54( void );
	virtual void vfn55( void );
	virtual void vfn56( void );
	virtual void vfn57( void );
	virtual void vfn58( void );
	virtual int selectMatchingAcrossScreen( void );
	virtual int selectMatchingAcrossRegion( IRegion2D *region );
	virtual void buildRegion( const ICoord2D *anchor, const ICoord2D *dest,
		IRegion2D *region );
};

extern GameTextInterface *TheGameText;
extern InGameUI *TheInGameUI;
extern TacticalViewFadeShim *TheTacticalViewFadeShim;
extern BfmeStateDO *g_bfmeStateDO;

int InGameUI::selectMatchingAcrossScreen( void )
{
	BfmeStateDO *state = g_bfmeStateDO;
	if (state != 0 && state->m_bfmeFirst != 0 && state->m_bfmeSecond != 0)
		return 0;

	ICoord2D origin;
	ICoord2D size;
	IRegion2D region;
	TheTacticalViewFadeShim->getOrigin(&origin.x, &origin.y);
	size.x = TheTacticalViewFadeShim->getWidth();
	size.y = TheTacticalViewFadeShim->getHeight();
	buildRegion(&origin, &size, &region);
	Int numSelected = selectMatchingAcrossRegion(&region);
	if (numSelected == -1)
	{
		UnicodeString message = TheGameText->fetch("GUI:NothingSelected");
		TheInGameUI->message(message);
	}
	else if (numSelected != 0)
	{
		UnicodeString message = TheGameText->fetch("GUI:SelectedAcrossScreen");
		TheInGameUI->message(message);
	}
	return numSelected;
}
