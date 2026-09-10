// ??0BfmeAptScreenOnlineCustomMatch@@QAE@H@Z
// partial score=0.18 date=2026-09-10
// BfmeAptScreenOnlineCustomMatch constructor, retail 0x00545310, 1935 bytes.
//
// The constructor is kept in its own translation unit so its multiple
// inheritance layout and MSVC EH state table stay independent of the guarded
// allocation wrappers in S4GuardedNewWithOneArg.cpp.

#include "../../../../../reference/shims/stringinline/StringInline.h"

class __declspec( novtable ) BfmeAptGameWindow
{
public:
	BfmeAptGameWindow( int a )
	{
		m_f04 = 0; m_f08 = 0; m_f0c = 0; m_f10 = 0; m_f14 = 0; m_f18 = 0;
		m_f1c = 0; m_f20 = 0; m_f24 = 0; m_f28 = 0; m_f2c = 0; m_f30 = 0;
		m_arg = a;
		m_f38 = 0;
	}
	virtual ~BfmeAptGameWindow()
	{
		bfmeDestroy();
	}
	void bfmeDestroy();

private:
	int m_f04, m_f08, m_f0c, m_f10, m_f14, m_f18, m_f1c, m_f20, m_f24, m_f28, m_f2c, m_f30;
	int m_arg;
	int m_f38;
};

class BfmeAptScreenSecondary
{
public:
	BfmeAptScreenSecondary() {}
	virtual ~BfmeAptScreenSecondary() {}
};

class BfmeCustomMatchMember40
{
public:
	BfmeCustomMatchMember40( void *secondaryBase, int size );
	~BfmeCustomMatchMember40();

private:
	unsigned char m_data[ 0x134 ];
};

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual void unused04();
	virtual void unused08();
	virtual bool write();
	void setInt( AsciiString key, int value );
	int getInt( AsciiString key, int defaultValue );

private:
	unsigned char m_data[ 0x6C ];
};

class CustomMatchPreferences : public UserPreferences
{
public:
	CustomMatchPreferences();
	virtual ~CustomMatchPreferences();
};

class GameSpyInfo
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
};

extern GameSpyInfo *TheGameSpyInfo;

class __multiple_inheritance FunctorTarget;
typedef void ( FunctorTarget::*FunctorMethod )( void );

struct FunctorBinding
{
	FunctorBinding( FunctorTarget *target, unsigned int unmodelled, FunctorMethod method )
		: m_target( target ), m_unmodelled( unmodelled ), m_method( method ) {}

	FunctorTarget *m_target;
	unsigned int m_unmodelled;
	FunctorMethod m_method;
};

class Rva00539A60FunctorHolder
{
public:
	Rva00539A60FunctorHolder( FunctorBinding binding );

	void *m_ptr;
};

struct GameSpyStagingRoomFields
{
	unsigned char m_unmodelled[ 0x43C ];
	bool m_flag43C;
};
extern GameSpyStagingRoomFields *TheGameSpyGame;

class BfmeAptScreenOnlineCustomMatch;
extern BfmeAptScreenOnlineCustomMatch *TheBfmeOnlineCustomMatch;

class __multiple_inheritance BfmeAptScreenOnlineCustomMatch
	: public BfmeAptGameWindow, public BfmeAptScreenSecondary
{
public:
	BfmeAptScreenOnlineCustomMatch( int a );

	void showAptScreen( const AsciiString &name, Rva00539A60FunctorHolder callback );

	void cancelPopUpJoin();
	void createGame();
	void joinGame();
	void acceptJoinGame();
	void chatEnter();
	void playGame();
	void cancel();
	void refresh();
	void onOpenCreateDialog();
	void cancelPopUpCreate();
	void cancelPopUpHost();
	void sortByName();
	void sortByGameType();
	void sortByNumPlayers();
	void sortByPing();
	void initGadgets();

private:
	BfmeCustomMatchMember40 m_mid;
	CustomMatchPreferences m_prefs;
	AsciiString m_unusedName;
	int m_primarySort;
	int m_secondarySort;
};

extern const void *BfmeAptScreenOnlineCustomMatchVftable[];
extern const void *BfmeAptScreenOnlineCustomMatchSecondaryVftable[];

#define BFME_OCM_REGISTER( LITERAL, METHOD ) \
	{ \
		FunctorMethod callback = (FunctorMethod)&BfmeAptScreenOnlineCustomMatch::METHOD; \
		AsciiString name( LITERAL ); \
		showAptScreen( name, Rva00539A60FunctorHolder( \
			FunctorBinding( (FunctorTarget *)this, 0, callback ) ) ); \
	}

BfmeAptScreenOnlineCustomMatch::BfmeAptScreenOnlineCustomMatch( int a )
	: BfmeAptGameWindow( a )
	, m_mid( (char *)this + 0x3C, 0x10 )
	, m_prefs()
	, m_unusedName( "APT:NULL" )
{
	m_primarySort = 8;
	m_secondarySort = 4;

	if( TheBfmeOnlineCustomMatch == 0 )
	{
		TheBfmeOnlineCustomMatch = this;

		BFME_OCM_REGISTER( "AptOnline::CustomMatch::CancelPopUpJoin", cancelPopUpJoin )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::CreateGame", createGame )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::JoinGame", joinGame )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::AcceptJoinGame", acceptJoinGame )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::ChatEnter", chatEnter )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::PlayGame", playGame )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::Cancel", cancel )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::Refresh", refresh )
		BFME_OCM_REGISTER( "AptOnline::OnOpenCreateDialog", onOpenCreateDialog )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::CancelPopUpCreate", cancelPopUpCreate )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::CancelPopUpHost", cancelPopUpHost )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::SortName", sortByName )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::SortGameType", sortByGameType )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::SortNumPlayers", sortByNumPlayers )
		BFME_OCM_REGISTER( "AptOnline::CustomMatch::SortPing", sortByPing )
		BFME_OCM_REGISTER( "AptOnlineCustomMatch::InitGadgets", initGadgets )
	}

	m_primarySort = m_prefs.getInt( AsciiString( "PrimarySort" ), m_primarySort );
	m_secondarySort = m_prefs.getInt( AsciiString( "SecondarySort" ), m_secondarySort );

	if( TheGameSpyGame )
		TheGameSpyGame->m_flag43C = false;
}
