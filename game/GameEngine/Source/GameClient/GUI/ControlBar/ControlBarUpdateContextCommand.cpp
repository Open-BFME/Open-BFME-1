// cl: /DNDEBUG /MD /EHsc
// ?updateContextCommand@ControlBar@@IAEXXZ

// Retail 0x004A5950, 959 bytes (RET at +0x3BE, then an eight-entry jump
// table for the availability switch).
//
// Identity: ControlBar::update's context-command branch reaches this body
// through ILT 0x0003672D, where tools/ilt_oracle.py CONFIRMS
// ?updateContextCommand@ControlBar@@IAEXXZ (protected, as in Zero Hour's
// ControlBar.h; the private AAE spelling earlier attempts used is
// CONTRADICTED). Zero Hour's body (ControlBarCommand.cpp) is the shape
// reference; BFME adds the percent output of getCommandAvailability, the
// observer/inactive-player handling and the extra availability states.
//
// Callees without a proven name are called through their retail ILT rows.

#include "../../../../Include/Common/ScalarTypes.h"




#ifndef NULL
#define NULL 0
#endif

#include "../../../../Include/Common/NameKeyType.h"

enum CommandAvailability
{
	COMMAND_RESTRICTED = 0,
	COMMAND_AVAILABLE = 1,
	COMMAND_ACTIVE = 2,
	COMMAND_HIDDEN = 3,
	COMMAND_NOT_READY = 4,
	COMMAND_CANT_AFFORD = 5,
	COMMAND_DISABLED = 6,
	COMMAND_UNAVAILABLE = 7
};

enum
{
	WIN_STATUS_RVA4A5950_8 = 0x00000008,
	WIN_STATUS_NOT_READY = 0x00400000,
	WIN_STATUS_ALWAYS_COLOR = 0x01000000,
	WIN_STATUS_RVA4A5950_40000000 = 0x40000000,
	WIN_STATUS_RVA4A5950_80000000 = 0x80000000
};


extern void j_0004a1fb();
extern void j_00027b24();
extern void j_00027f2a();


extern void j_0000238d();

extern void j_00010e88();
extern void j_0000bc49();
extern void j_0003e545();
extern void j_00005669();

class GameWindow;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	UnsignedInt _bfme_winSetStatus( UnsignedInt status );

	Bool winIsHidden();
	void winEnable( Bool enable )
	{
		union { void (*raw)(); void (GameWindow::*fn)( Bool ); } call = { j_0004a1fb };
		(this->*call.fn)( enable );
	}
	void winClearStatus( UnsignedInt status )
	{
		union { void (*raw)(); void (GameWindow::*fn)( UnsignedInt ); } call = { j_00027b24 };
		(this->*call.fn)( status );
	}
	void winHide( Bool hide )
	{
		union { void (*raw)(); void (GameWindow::*fn)( Bool ); } call = { j_00027f2a };
		(this->*call.fn)( hide );
	}
	UnsignedInt winGetStatus();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

#define WINDOW_SLOT(n) virtual void slot##n();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	WINDOW_SLOT(00) WINDOW_SLOT(01) WINDOW_SLOT(02) WINDOW_SLOT(03)
	WINDOW_SLOT(04) WINDOW_SLOT(05) WINDOW_SLOT(06) WINDOW_SLOT(07)
	WINDOW_SLOT(08) WINDOW_SLOT(09) WINDOW_SLOT(10) WINDOW_SLOT(11)
	WINDOW_SLOT(12) WINDOW_SLOT(13) WINDOW_SLOT(14) WINDOW_SLOT(15)
	WINDOW_SLOT(16) WINDOW_SLOT(17) WINDOW_SLOT(18) WINDOW_SLOT(19)
	WINDOW_SLOT(20) WINDOW_SLOT(21) WINDOW_SLOT(22) WINDOW_SLOT(23)
	WINDOW_SLOT(24) WINDOW_SLOT(25) WINDOW_SLOT(26) WINDOW_SLOT(27)
	WINDOW_SLOT(28) WINDOW_SLOT(29) WINDOW_SLOT(30) WINDOW_SLOT(31)
	WINDOW_SLOT(32) WINDOW_SLOT(33) WINDOW_SLOT(34) WINDOW_SLOT(35)
	WINDOW_SLOT(36) WINDOW_SLOT(37) WINDOW_SLOT(38) WINDOW_SLOT(39)
	WINDOW_SLOT(40) WINDOW_SLOT(41) WINDOW_SLOT(42) WINDOW_SLOT(43)
	WINDOW_SLOT(44) WINDOW_SLOT(45) WINDOW_SLOT(46) WINDOW_SLOT(47)
	WINDOW_SLOT(48) WINDOW_SLOT(49) WINDOW_SLOT(50) WINDOW_SLOT(51)
	WINDOW_SLOT(52) WINDOW_SLOT(53) WINDOW_SLOT(54)
	virtual GameWindow *winGetWindowFromId( GameWindow *parent, NameKeyType id );	// slot 55
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	WINDOW_SLOT(00) WINDOW_SLOT(01) WINDOW_SLOT(02) WINDOW_SLOT(03)
	WINDOW_SLOT(04) WINDOW_SLOT(05) WINDOW_SLOT(06) WINDOW_SLOT(07)
	WINDOW_SLOT(08) WINDOW_SLOT(09) WINDOW_SLOT(10) WINDOW_SLOT(11)
	WINDOW_SLOT(12) WINDOW_SLOT(13) WINDOW_SLOT(14) WINDOW_SLOT(15)
	WINDOW_SLOT(16) WINDOW_SLOT(17) WINDOW_SLOT(18) WINDOW_SLOT(19)
	WINDOW_SLOT(20) WINDOW_SLOT(21) WINDOW_SLOT(22)
	virtual Int getContainMax() const;							// slot 23
	WINDOW_SLOT(24) WINDOW_SLOT(25) WINDOW_SLOT(26) WINDOW_SLOT(27)
	WINDOW_SLOT(28) WINDOW_SLOT(29) WINDOW_SLOT(30) WINDOW_SLOT(31)
	WINDOW_SLOT(32) WINDOW_SLOT(33) WINDOW_SLOT(34) WINDOW_SLOT(35)
	WINDOW_SLOT(36) WINDOW_SLOT(37) WINDOW_SLOT(38) WINDOW_SLOT(39)
	WINDOW_SLOT(40) WINDOW_SLOT(41) WINDOW_SLOT(42) WINDOW_SLOT(43)
	WINDOW_SLOT(44) WINDOW_SLOT(45) WINDOW_SLOT(46) WINDOW_SLOT(47)
	WINDOW_SLOT(48) WINDOW_SLOT(49) WINDOW_SLOT(50) WINDOW_SLOT(51)
	WINDOW_SLOT(52) WINDOW_SLOT(53) WINDOW_SLOT(54) WINDOW_SLOT(55)
	WINDOW_SLOT(56) WINDOW_SLOT(57) WINDOW_SLOT(58) WINDOW_SLOT(59)
	WINDOW_SLOT(60) WINDOW_SLOT(61) WINDOW_SLOT(62) WINDOW_SLOT(63)
	virtual Int getContainCount( Bool countRiders ) const;			// slot 64
};

class ProductionEntry
{
public:
	unsigned char m_pad000[ 0x14 ];
	Real m_percentComplete;							// +0x14

	Real getPercentComplete() const { return m_percentComplete; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionUpdate.h
class ProductionUpdateInterface
{
public:
	WINDOW_SLOT(00) WINDOW_SLOT(01) WINDOW_SLOT(02) WINDOW_SLOT(03)
	WINDOW_SLOT(04) WINDOW_SLOT(05) WINDOW_SLOT(06) WINDOW_SLOT(07)
	WINDOW_SLOT(08) WINDOW_SLOT(09) WINDOW_SLOT(10) WINDOW_SLOT(11)
	WINDOW_SLOT(12) WINDOW_SLOT(13) WINDOW_SLOT(14) WINDOW_SLOT(15)
	WINDOW_SLOT(16) WINDOW_SLOT(17)
	virtual const ProductionEntry *firstProduction() const;			// slot 18
};

#undef WINDOW_SLOT

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ProductionUpdateInterface *getProductionUpdateInterface();
	ContainModuleInterface *getContain() const { return m_contain; }
	Bool isLocallyControlled() const;

	unsigned char m_pad000[ 0x1FC ];
	ContainModuleInterface *m_contain;				// +0x1fc
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	Object *getObject() const { return m_object; }

	unsigned char m_pad000[ 0xFC ];
	Object *m_object;							// +0xfc
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	Int getCommandType() const { return m_command; }
	UnsignedInt getOptions() const { return m_options; }

	unsigned char m_pad000[ 0x10 ];
	Int m_command;								// +0x10
	unsigned char m_pad014[ 4 ];
	UnsignedInt m_options;							// +0x18
	unsigned char m_pad01c[ 0x151 - 0x1C ];
	Bool m_field151;							// +0x151
};

class BfmeCommandButtonDispatchILT;
class BfmeCommandButtonResolveILT
{
public:
	BfmeCommandButtonDispatchILT *resolve();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool isPlayerActive() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }

	unsigned char m_pad000[ 0xC ];
	Player *m_local;							// +0x0c
};

extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;

static inline void *GadgetButtonGetData( GameWindow *window )
{
	return ((void *(*)( GameWindow * ))j_00010e88)( window );
}
static inline void GadgetButtonDrawOverlayImage( GameWindow *window, const void *image )
{
	((void (*)( GameWindow *, const void * ))j_0000bc49)( window, image );
}
static inline void GadgetButtonDrawInverseClock( GameWindow *window, Int percent, Int color )
{
	((void (*)( GameWindow *, Int, Int ))j_0003e545)( window, percent, color );
}
static inline void GadgetCheckLikeButtonSetVisualCheck( GameWindow *window, Bool checked )
{
	((void (*)( GameWindow *, Bool ))j_00005669)( window, checked );
}

class BfmeRva004A4240CommandAvailabilityView
{
public:
	Int call( const CommandButton *command, GameWindow *win, Object *obj,
		Real *percent, Bool forceDisabledEvaluation ) const;
};

enum { MAX_COMMANDS_PER_SET = 20 };
enum { CP_BUILD_QUEUE = 3 };

class ControlBar
{
protected:
	void updateContextCommand();

private:
	void setPortraitByObject( Object *obj );
	void evaluateContextUI()
	{
		union { void (*raw)(); void (ControlBar::*fn)(); } call = { j_0000238d };
		(this->*call.fn)();
	}
	CommandAvailability getCommandAvailability( const CommandButton *command, GameWindow *win,
		Object *obj, Real *percent, Bool forceDisabledEvaluation ) const
	{
		return (CommandAvailability)((const BfmeRva004A4240CommandAvailabilityView *)this)->call(
			command, win, obj, percent, forceDisabledEvaluation );
	}

	unsigned char m_pad000[ 0x34 ];
	GameWindow *m_contextParent[ 10 ];					// +0x34
	Drawable *m_currentSelectedDrawable;				// +0x5c
	unsigned char m_pad060[ 0x10 ];
	UnsignedInt m_lastRecordedInventoryCount;			// +0x70
	unsigned char m_pad074[ 0x100 - 0x74 ];
	GameWindow *m_commandWindows[ MAX_COMMANDS_PER_SET ];	// +0x100
	unsigned char m_pad150[ 0x26C - 0x150 ];
	Int m_buildUpClockColor;							// +0x26c
};

void ControlBar::updateContextCommand()
{
	Object *obj = NULL;
	Int i;

	if ( m_currentSelectedDrawable )
		obj = m_currentSelectedDrawable->getObject();

	ContainModuleInterface *contain = obj ? obj->getContain() : NULL;
	if ( contain && contain->getContainMax() > 0 &&
			m_lastRecordedInventoryCount != contain->getContainCount( false ) )
	{
		m_lastRecordedInventoryCount = contain->getContainCount( false );
		evaluateContextUI();
	}

	ProductionUpdateInterface *pu = obj ? obj->getProductionUpdateInterface() : NULL;

	if ( m_contextParent[ CP_BUILD_QUEUE ]->winIsHidden() == false )
	{
		setPortraitByObject( NULL );
		if ( pu )
		{
			const ProductionEntry *produce = pu->firstProduction();
			if ( produce )
			{
				static NameKeyType winID = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonQueue01" );
				GameWindow *win = TheWindowManager->winGetWindowFromId( m_contextParent[ CP_BUILD_QUEUE ], winID );
				GadgetButtonDrawInverseClock( win, produce->getPercentComplete(), m_buildUpClockColor );
			}
		}
	}

	Bool locallyControlled = obj ? obj->isLocallyControlled() : false;

	for ( i = 0; i < MAX_COMMANDS_PER_SET; i++ )
	{
		GameWindow *win;
		const CommandButton *command;

		if ( !m_commandWindows[ i ] )
			continue;
		win = m_commandWindows[ i ];

		command = (const CommandButton *)GadgetButtonGetData( win );
		if ( command == NULL )
			continue;

		Real percent = 0.0f;
		CommandAvailability availability = getCommandAvailability( command, win, obj, &percent, false );

		Bool inactive = false;
		Bool restricted = false;
		Bool observer = restricted;
		if ( !locallyControlled )
		{
			if ( ThePlayerList->getLocalPlayer()->isPlayerActive() )
			{
				observer = true;
				if ( availability != COMMAND_RESTRICTED && availability != COMMAND_HIDDEN )
				{
					restricted = true;
					availability = COMMAND_RESTRICTED;
				}
			}
			else
				inactive = true;
		}

		if ( availability == COMMAND_HIDDEN && win->winIsHidden() )
			continue;

		if ( ( availability == COMMAND_RESTRICTED || availability == COMMAND_DISABLED ) &&
				( command->getOptions() & 0x00400000 ) && !restricted )
			availability = COMMAND_HIDDEN;

		if ( command->getCommandType() == 0x0F )
		{
			win->_bfme_winSetStatus( WIN_STATUS_ALWAYS_COLOR );
			if ( availability == COMMAND_HIDDEN )
				win->winHide( true );
			continue;
		}

		win->winClearStatus( WIN_STATUS_NOT_READY );
		win->winClearStatus( WIN_STATUS_ALWAYS_COLOR );
		win->winClearStatus( WIN_STATUS_RVA4A5950_40000000 );
		win->winClearStatus( WIN_STATUS_RVA4A5950_80000000 );

		Bool hide = false;
		Int clockColor = 0;
		switch ( availability )
		{
			case COMMAND_HIDDEN:
				hide = true;
				break;
			case COMMAND_RESTRICTED:
			case COMMAND_UNAVAILABLE:
				win->winEnable( false );
				win->_bfme_winSetStatus( WIN_STATUS_RVA4A5950_80000000 );
				if ( availability == COMMAND_UNAVAILABLE )
					win->_bfme_winSetStatus( WIN_STATUS_ALWAYS_COLOR );
				break;
			case COMMAND_NOT_READY:
				clockColor = m_buildUpClockColor;
				win->winEnable( false );
				win->_bfme_winSetStatus( WIN_STATUS_NOT_READY );
				break;
			case COMMAND_CANT_AFFORD:
			case COMMAND_DISABLED:
				win->winEnable( false );
				win->_bfme_winSetStatus( WIN_STATUS_ALWAYS_COLOR );
				break;
			default:
				win->winEnable( true );
				break;
		}

		if ( clockColor < 1.0f && !observer )
			GadgetButtonDrawInverseClock( win, percent * 100.0f, clockColor );

		if ( inactive && ( win->winGetStatus() & WIN_STATUS_RVA4A5950_8 ) )
		{
			win->winEnable( false );
			win->_bfme_winSetStatus( WIN_STATUS_RVA4A5950_40000000 );
		}

		win->winHide( hide );

		if ( !command->m_field151 )
			win->winEnable( false );
		((BfmeCommandButtonResolveILT *)command)->resolve();
		GadgetButtonDrawOverlayImage( win, NULL );

		if ( command->getOptions() & 0x00000400 )
			if ( availability == COMMAND_ACTIVE )
				GadgetCheckLikeButtonSetVisualCheck( win, true );
			else
				GadgetCheckLikeButtonSetVisualCheck( win, false );
	}
}
