// ?rva004A9010@ControlBar@@QAEXPAX_N@Z
// partial score=0.9 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// BFME ControlBar command-window population at retail RVA 0x004A9010.
// Owner proved by the ControlBar findCommandSet and setControlCommand calls.

typedef int Int;
typedef bool Bool;

enum KindOfType { KINDOF_FIRST = 0 };

class AsciiString;
class CommandButton;

class Thing
{
public:
	Bool isKindOf( KindOfType kind ) const;
};

class Object : public Thing
{
public:
	const AsciiString &getCommandSetString( void ) const;
	Bool testStatus( Int status ) const;
	Object *bfmeResolveMeleeTarget( Int mode );
	void *unidentified_001BFE20( void ) const;
};

class GameWindow
{
public:
	void bfmeClose( Bool hide );
};

class BfmeUnit1013
{
public:
	void bfmeStop1013( char value );
};

class CommandSet
{
public:
	const CommandButton *getCommandButton( Int index ) const;
};

class CommandButton
{
public:
	unsigned char m_pad00[ 0x10 ];
	Int m_commandType;
	unsigned char m_pad14[ 4 ];
	Int m_options;
};

// The drawable carries its object at +0xFC; only that field is referenced here.
struct Rva004A9010Drawable
{
	unsigned char m_pad00[ 0xFC ];
	Object *m_object;
};

struct Rva004A9010SelNode
{
	Rva004A9010SelNode *m_next;
	Rva004A9010SelNode *m_prev;
	void *m_drawable;
};

struct Rva004A9010SelList
{
	Rva004A9010SelNode *m_node;
};

// Address-derived relation interface view: only virtual slot +0xD8 is used.
class Rva004A9010Relation
{
public:
	#define REL_SLOT(n) virtual void slot##n( void ) = 0;
	REL_SLOT(00) REL_SLOT(04) REL_SLOT(08) REL_SLOT(0C) REL_SLOT(10) REL_SLOT(14)
	REL_SLOT(18) REL_SLOT(1C) REL_SLOT(20) REL_SLOT(24) REL_SLOT(28) REL_SLOT(2C)
	REL_SLOT(30) REL_SLOT(34) REL_SLOT(38) REL_SLOT(3C) REL_SLOT(40) REL_SLOT(44)
	REL_SLOT(48) REL_SLOT(4C) REL_SLOT(50) REL_SLOT(54) REL_SLOT(58) REL_SLOT(5C)
	REL_SLOT(60) REL_SLOT(64) REL_SLOT(68) REL_SLOT(6C) REL_SLOT(70) REL_SLOT(74)
	REL_SLOT(78) REL_SLOT(7C) REL_SLOT(80) REL_SLOT(84) REL_SLOT(88) REL_SLOT(8C)
	REL_SLOT(90) REL_SLOT(94) REL_SLOT(98) REL_SLOT(9C) REL_SLOT(A0) REL_SLOT(A4)
	REL_SLOT(A8) REL_SLOT(AC) REL_SLOT(B0) REL_SLOT(B4) REL_SLOT(B8) REL_SLOT(BC)
	REL_SLOT(C0) REL_SLOT(C4) REL_SLOT(C8) REL_SLOT(CC) REL_SLOT(D0) REL_SLOT(D4)
	#undef REL_SLOT
	virtual Bool slotD8( void ) = 0;
};

// Address-derived UI singleton view: only virtual slot +0xFC is used.
class InGameUI
{
public:
	#define UI_SLOT(n) virtual void slot##n( void ) = 0;
	UI_SLOT(00) UI_SLOT(04) UI_SLOT(08) UI_SLOT(0C) UI_SLOT(10) UI_SLOT(14)
	UI_SLOT(18) UI_SLOT(1C) UI_SLOT(20) UI_SLOT(24) UI_SLOT(28) UI_SLOT(2C)
	UI_SLOT(30) UI_SLOT(34) UI_SLOT(38) UI_SLOT(3C) UI_SLOT(40) UI_SLOT(44)
	UI_SLOT(48) UI_SLOT(4C) UI_SLOT(50) UI_SLOT(54) UI_SLOT(58) UI_SLOT(5C)
	UI_SLOT(60) UI_SLOT(64) UI_SLOT(68) UI_SLOT(6C) UI_SLOT(70) UI_SLOT(74)
	UI_SLOT(78) UI_SLOT(7C) UI_SLOT(80) UI_SLOT(84) UI_SLOT(88) UI_SLOT(8C)
	UI_SLOT(90) UI_SLOT(94) UI_SLOT(98) UI_SLOT(9C) UI_SLOT(A0) UI_SLOT(A4)
	UI_SLOT(A8) UI_SLOT(AC) UI_SLOT(B0) UI_SLOT(B4) UI_SLOT(B8) UI_SLOT(BC)
	UI_SLOT(C0) UI_SLOT(C4) UI_SLOT(C8) UI_SLOT(CC) UI_SLOT(D0) UI_SLOT(D4)
	UI_SLOT(D8) UI_SLOT(DC) UI_SLOT(E0) UI_SLOT(E4) UI_SLOT(E8) UI_SLOT(EC)
	UI_SLOT(F0) UI_SLOT(F4) UI_SLOT(F8)
	#undef UI_SLOT
	virtual Rva004A9010SelList *slotFC( void ) = 0;
};

extern InGameUI *TheInGameUI;

// The two command-button callees carry no ledger identity; reach them through
// their incremental-link thunks.
extern void j_00011cd4( void );
extern void j_00006938( void );

struct Rva004A9010ButtonCalls
{
	void applyState( Int value );
	void applyObject( Object *object, Int mode );
};

typedef void (Rva004A9010ButtonCalls::*Rva004A9010StateCall)( Int );
typedef void (Rva004A9010ButtonCalls::*Rva004A9010ObjectCall)( Object *, Int );

static void callRva00011CD4( const CommandButton *button, Int value )
{
	union
	{
		void (*asFunction)();
		Rva004A9010StateCall asMember;
	} functionCast;
	functionCast.asFunction = j_00011cd4;
	(((Rva004A9010ButtonCalls *)button)->*functionCast.asMember)( value );
}

static void callRva00006938( const CommandButton *button, Object *object, Int mode )
{
	union
	{
		void (*asFunction)();
		Rva004A9010ObjectCall asMember;
	} functionCast;
	functionCast.asFunction = j_00006938;
	(((Rva004A9010ButtonCalls *)button)->*functionCast.asMember)( object, mode );
}

class ControlBar
{
public:
	void rva004A9010( void *draw, Bool populate );
	const CommandSet *findCommandSet( const AsciiString &name );

private:
	void setControlCommand( GameWindow *window, const CommandButton *button );

	unsigned char m_pad00[ 0x100 ];
	GameWindow *m_commandWindows[ 20 ];
	unsigned char m_pad150[ 0x1F0 - 0x150 ];
	const CommandButton *m_commonCommands[ 20 ];
};

void ControlBar::rva004A9010( void *draw, Bool populate )
{
	if ( draw == 0 )
		return;

	Object *obj = ((Rva004A9010Drawable *)draw)->m_object;
	if ( obj == 0 )
		return;

	if ( obj->isKindOf( (KindOfType)0x2F ) )
		return;

	GameWindow **win = m_commandWindows;
	const CommandSet *commandSet = findCommandSet( obj->getCommandSetString() );

	if ( commandSet == 0 )
	{
		Int hide;

		for ( hide = 20; hide != 0; --hide )
		{
			GameWindow *window = win[ 0 ];
			((const CommandButton **)win)[ 0x3C ] = 0;
			if ( window != 0 )
				window->bfmeClose( true );
			++win;
		}

		return;
	}

	Int i;

	if ( populate == true )
	{
		for ( i = 0; i < 20; ++i, ++win )
		{
			const CommandButton *button = commandSet->getCommandButton( i );
			if ( button == 0 )
				continue;

			if ( ( button->m_options & 0x100 ) == 0 )
				continue;

			GameWindow *window = win[ 0 ];
			((const CommandButton **)win)[ 0x3C ] = button;
			if ( window == 0 )
				continue;

			window->bfmeClose( false );
			((BfmeUnit1013 *)win[ 0 ])->bfmeStop1013( 1 );

			if ( button->m_commandType == 0x23 )
			{
				Rva004A9010SelList *list = TheInGameUI->slotFC();
				Int score = 0;
				Rva004A9010SelNode *head = list->m_node;
				Rva004A9010SelNode *entry = head->m_next;

				if ( entry != head )
				{
					do
					{
						void *selected = entry->m_drawable;
						if ( selected != 0 )
						{
							Object *other = ((Rva004A9010Drawable *)selected)->m_object;
							if ( other != 0
								&& other->isKindOf( (KindOfType)0x2F ) == false
								&& other->testStatus( 0x13 ) == false )
							{
								Object *target = other->bfmeResolveMeleeTarget( 0 );
								if ( target != 0 )
								{
									void *relation = target->unidentified_001BFE20();
									if ( relation != 0 )
									{
										if ( ((Rva004A9010Relation *)relation)->slotD8() )
											--score;
										else
											++score;
									}
								}
							}
						}
						entry = entry->m_next;
					}
					while ( entry != list->m_node );
				}

				callRva00011CD4( button, score >= 0 );
			}
			else
			{
				callRva00006938( button, obj, 0 );
			}

			setControlCommand( win[ 0 ], button );
		}

		return;
	}

	for ( i = 0; i < 20; ++i, ++win )
	{
		const CommandButton *button = commandSet->getCommandButton( i );
		const CommandButton **slot = (const CommandButton **)win + 0x3C;
		Bool handled = false;

		if ( ( button != 0 && button->m_commandType == 9 )
			|| ( slot[ 0 ] != 0 && slot[ 0 ]->m_commandType == 9 ) )
		{
			handled = true;

			if ( slot[ 0 ] == 0 )
			{
				GameWindow *window = win[ 0 ];
				slot[ 0 ] = button;
				if ( window != 0 )
				{
					window->bfmeClose( false );
					((BfmeUnit1013 *)win[ 0 ])->bfmeStop1013( 1 );
					setControlCommand( win[ 0 ], button );
				}
				continue;
			}
		}

		if ( button != slot[ 0 ] && handled == false )
		{
			GameWindow *window = win[ 0 ];
			slot[ 0 ] = 0;
			if ( window != 0 )
				window->bfmeClose( true );
		}
	}
}
