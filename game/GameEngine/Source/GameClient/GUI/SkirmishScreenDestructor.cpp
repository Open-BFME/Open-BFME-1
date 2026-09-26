#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"
// Retail 0x00579480: BfmeAptScreenSkirmish destructor.

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase( const T *text );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	~UnicodeString() {}
};

class WindowManager
{
public:
	void removeAptObject( const AsciiString &name );
};

void _bfme_closeAptScreen( const AsciiString &name );

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

class BfmeAptFunctorMarker
{
public:
	virtual void slot00() = 0;

private:
	char m_unmodelled[ 0x3C ];
};

class BfmeAptScreenSecondary
{
public:
	virtual ~BfmeAptScreenSecondary() {}
};

class Gen_uwm_0000b42e
{
public:
	~Gen_uwm_0000b42e();

private:
	void *m_vftable;
	char m_unmodelled[ 0x130 ];
};

class Gen_uwm_0004ac4b
{
public:
	~Gen_uwm_0004ac4b();

private:
	void *m_vftable;
	char m_unmodelled[ 0x18 ];
};

class Gen_uwm_00046b82
{
public:
	~Gen_uwm_00046b82();

private:
	void *m_vftable;
	char m_unmodelled[ 0x14 ];
};

class Gen_uwm_0003f6d4
{
public:
	~Gen_uwm_0003f6d4();

private:
	void *m_vftable;
	char m_unmodelled[ 0x38 ];
};

class Gen_uwm_0004598f
{
public:
	~Gen_uwm_0004598f();

private:
	void *m_vftable;
	char m_unmodelled[ 0x10 ];
};

extern WindowManager *g_theWindowManager;
extern void *g_obj12F4B54;

class __declspec(novtable) BfmeAptScreenSkirmish
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker,
	  public BfmeAptScreenSecondary
{
public:
	virtual ~BfmeAptScreenSkirmish();

private:
	Gen_uwm_0000b42e m_state;
	Gen_uwm_0004ac4b m_animation;
	Gen_uwm_00046b82 m_preferences;
	Gen_uwm_0003f6d4 m_honors;
	char m_unmodelled400[ 0x24 ];
	Gen_uwm_0004598f m_profile;
	UnicodeString m_unusedName;
};

BfmeAptScreenSkirmish::~BfmeAptScreenSkirmish()
{
	*(const void ***)this = (const void **)0x0110B030;
	*(const void ***)((char *)this + 0x218) = (const void **)0x0110B02C;
	*(const void ***)((char *)this + 0x258) = (const void **)0x0110AFE0;

	if( g_obj12F4B54 == this )
	{
		if( g_theWindowManager )
		{
			AsciiString name( "Skirmish/tooltipPlayerLevelIcon" );
			g_theWindowManager->removeAptObject( name );
		}
		{
			AsciiString name( "AptSkirmish::InitGadgets" );
			_bfme_closeAptScreen( name );
		}
		g_obj12F4B54 = 0;
	}
}
