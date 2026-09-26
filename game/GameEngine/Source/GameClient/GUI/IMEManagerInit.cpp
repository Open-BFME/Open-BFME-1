// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

// IMEManager::init at retail 0x0048D9C0 (581 bytes).
//
// This is the same BFME IMEManager object whose constructor installs vtable
// 0x010F9978 and whose exact destructor is in IMEManagerDestructor.cpp.  The
// GameClient init path calls TheIMEManager->init() immediately after the
// factory, while the retail body references the three IME window literals in
// targets/game/reverse/string_xrefs.tsv.  The fields used here are the independently
// established IME offsets: IMM contexts at +0x10/+0x14, disabled count at
// +0x18, and candidate/status windows at +0x304c/+0x3050 with the three child
// controls at +0x3054/+0x3058/+0x305c.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int NameKeyType;

class GameWindow;
class WindowLayoutInfo;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );

	// Retail's call sites extract the inline StringBase<char> buffer and call
	// the const-char overload at ILT 0x0003ADD7.  Keep this forwarding overload
	// inline; an out-of-line AsciiString overload would call retail 0x0004A1DD
	// instead and changes all three call sites.
	NameKeyType nameToKey( const AsciiString &name )
	{
		return nameToKey( name.str() );
	}
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow
{
public:
	UnsignedInt winSetStatus( UnsignedInt status );
	Int winHide( Bool hide );
	void winSetUserData( void *data );
};

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual GameWindow *winCreateFromScript( AsciiString file,
		WindowLayoutInfo *info = 0, void *extra = 0 );
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual Int winDestroy( GameWindow *window );
	virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42();
	virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47(); virtual void slot48();
	virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54();
	virtual GameWindow *winGetWindowFromId( GameWindow *parent, Int id );
};

extern GameWindowManager *TheWindowManager;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual Bool loadIniFilesFromLegend();
	virtual void slot03();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual Bool slot06( Int arg );
	virtual void slot07();
	virtual void slot08( Int arg );

protected:
	AsciiString m_name;
};

class IMEManagerInterface : public SubsystemInterface
{
public:
	virtual ~IMEManagerInterface() {}
	virtual void attach( GameWindow *window ) = 0;
	virtual void detatch() = 0;
	virtual void enable() = 0;
	virtual void disable() = 0;
	virtual Bool isEnabled() = 0;
	virtual Bool isAttachedTo( GameWindow *window ) = 0;
	virtual GameWindow *getWindow() = 0;
	virtual Bool isComposing() = 0;
	virtual void getCompositionString( void *string ) = 0;
	virtual Int getCompositionCursorPosition() = 0;
	virtual Int getIndexBase() = 0;
	virtual Int getCandidateCount() = 0;
	virtual void *getCandidate( Int index ) = 0;
	virtual Int getSelectedCandidateIndex() = 0;
	virtual Int getCandidatePageSize() = 0;
	virtual Int getCandidatePageStart() = 0;
	virtual Bool serviceIMEMessage( void *window, UnsignedInt message,
		Int wParam, Int lParam ) = 0;
	virtual Int result() = 0;
};

// The global is only passed through GameWindow::winSetUserData; its concrete
// object layout is outside this body, so keep the declaration opaque.
class BfmeImeManager;
extern BfmeImeManager *TheBfmeImeManager;
extern void *Rva0048CD50WindowHandle;

extern "C"
{
	void *__stdcall ImmCreateContext();
	void *__stdcall ImmGetContext( void *window );
}

class IMEManager : public IMEManagerInterface
{
public:
	virtual void init();

private:
	Int m_result;                                      // +0x08
	GameWindow *m_window;                              // +0x0c
	void *m_context;                                   // +0x10
	void *m_oldContext;                                // +0x14
	Int m_disabled;                                    // +0x18
	char m_padding1c[0x304c - 0x1c];
	GameWindow *m_candidateWindow;                     // +0x304c
	GameWindow *m_statusWindow;                        // +0x3050
	GameWindow *m_candidateTextArea;                   // +0x3054
	GameWindow *m_candidateUpArrow;                    // +0x3058
	GameWindow *m_candidateDownArrow;                  // +0x305c
};

// ?init@IMEManager@@UAEXXZ
void IMEManager::init()
{
	m_context = ImmCreateContext();
	m_oldContext = ImmGetContext( Rva0048CD50WindowHandle );
	m_disabled = 0;

	m_candidateWindow = TheWindowManager->winCreateFromScript(
		AsciiString( "IMECandidateWindow.wnd" ) );
	m_candidateWindow->winSetStatus( 0x20 );

	if ( m_candidateWindow )
	{
		m_candidateWindow->winHide( true );

		NameKeyType id = TheNameKeyGenerator->nameToKey(
			AsciiString( "IMECandidateWindow.wnd:TextArea" ) );
		m_candidateTextArea = TheWindowManager->winGetWindowFromId(
			m_candidateWindow, id );

		id = TheNameKeyGenerator->nameToKey(
			AsciiString( "IMECandidateWindow.wnd:UpArrow" ) );
		m_candidateUpArrow = TheWindowManager->winGetWindowFromId(
			m_candidateWindow, id );

		id = TheNameKeyGenerator->nameToKey(
			AsciiString( "IMECandidateWindow.wnd:DownArrow" ) );
		m_candidateDownArrow = TheWindowManager->winGetWindowFromId(
			m_candidateWindow, id );

		if ( m_candidateTextArea == 0 )
		{
			TheWindowManager->winDestroy( m_candidateWindow );
			m_candidateWindow = 0;
		}
	}

	m_statusWindow = TheWindowManager->winCreateFromScript(
		AsciiString( "IMEStatusWindow.wnd" ) );
	if ( m_statusWindow )
		m_statusWindow->winHide( true );

	if ( m_candidateWindow != 0 )
	{
		m_candidateWindow->winSetUserData( TheBfmeImeManager );
		m_candidateTextArea->winSetUserData( TheBfmeImeManager );
	}

	detatch();
	enable();
}
