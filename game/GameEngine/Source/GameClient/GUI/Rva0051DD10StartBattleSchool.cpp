// cl: /DNDEBUG /MD /EHsc

// FILE: Rva0051DD10StartBattleSchool.cpp
// A third leftover on d_0050fec0.asm, beside Rva0051D960ShellPush.cpp and
// Rva0051DA30StartGameMode7.cpp: a shell callback that ignores its int
// argument and clears a flag byte on its own object.
//
// It runs the MainMenuToBattleSchool window transition and turns the
// FlashTutorial user preference off, then writes the preference file.  Both
// names are the literals at 0x0110633C and 0x0110632C.
//
// TheShell is read twice because the transition runs in between, so the
// source tests it twice.

typedef bool Bool;
typedef int Int;

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual Bool write();

	void setBool( AsciiString key, Bool value );

private:
	unsigned char m_unmodelled004[ 0x10 ];
};

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
	void setGroup( AsciiString name, Bool reverse );
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	unsigned char m_unmodelled000[ 0x59 ];
	Bool m_field59;
};

extern Shell *TheShell;

// game/GameEngine/Source/Common/S3GuardedIndirectRelease.cpp owns the body at
// 0x0057F100 this reaches through ILT 0x0004393C, on the Shell singleton.
class Rva0057F100
{
public:
	void giveBack();
};

class Rva0051DD10Host
{
public:
	void startBattleSchool( Int unused );

private:
	char m_lead[ 0x25D ];
	Bool m_field25D;
};

// @?startBattleSchool@Rva0051DD10Host@@QAEXH@Z 0x0051DD10
void Rva0051DD10Host::startBattleSchool( Int )
{
	if ( TheShell != 0 )
		TheShell->m_field59 = true;

	TheTransitionHandler->setGroup( AsciiString( "MainMenuToBattleSchool" ), false );

	if ( TheShell != 0 )
		( (Rva0057F100 *)TheShell )->giveBack();

	OptionPreferences preferences;
	preferences.setBool( AsciiString( "FlashTutorial" ), false );
	preferences.write();

	m_field25D = false;
}
