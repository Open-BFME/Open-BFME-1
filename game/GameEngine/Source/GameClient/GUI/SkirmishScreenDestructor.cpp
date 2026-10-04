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

extern WindowManager *g_rva012F19E8WindowManager;
extern void *g_obj12F4B54;
// The three Skirmish vftables this destructor restores, each spelled exactly
// as the object that defines it spells it: the primary view selected by the
// Rva0057DA50Primary base at +0x00, the Rva00465200GameWindow base at +0x218
// and the complete-object table at +0x258. The defining class is
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptSkirmishConstructor.cpp,
// whose base list gives these three mangled names.
extern "C" const void *__identifier("??_7BfmeAptScreenSkirmish@@6BRva0057DA50Primary@@@")[];
extern "C" const void *__identifier("??_7BfmeAptScreenSkirmish@@6BRva00465200GameWindow@@@")[];
extern "C" const void *__identifier("??_7BfmeAptScreenSkirmish@@6B@")[];

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
	*(const void ***)this = __identifier("??_7BfmeAptScreenSkirmish@@6BRva0057DA50Primary@@@");
	*(const void ***)((char *)this + 0x218) = __identifier("??_7BfmeAptScreenSkirmish@@6BRva00465200GameWindow@@@");
	*(const void ***)((char *)this + 0x258) = __identifier("??_7BfmeAptScreenSkirmish@@6B@");

	if( g_obj12F4B54 == this )
	{
		if( g_rva012F19E8WindowManager )
		{
			AsciiString name( "Skirmish/tooltipPlayerLevelIcon" );
			g_rva012F19E8WindowManager->removeAptObject( name );
		}
		{
			AsciiString name( "AptSkirmish::InitGadgets" );
			_bfme_closeAptScreen( name );
		}
		g_obj12F4B54 = 0;
	}
}
