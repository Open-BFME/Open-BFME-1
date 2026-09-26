// Retail 0x004BC8A0, 175 bytes.
// The body has no named caller or callback-table row, so its identity stays
// address-derived. Retail proves the GameWindow data field, selected drawable,
// production interface, command-button resolver, and six-word upgrade mask.

typedef bool Bool;

class GameWindow;
class Drawable;
class Object;
class CommandButton;
class BfmeThingLU;

struct BfmeUpgradeMask
{
	unsigned int m_word[ 6 ];
};

class InGameUI
{
public:
#define BFME_INGAME_SLOT( n ) virtual void slot##n( void ) = 0;
	BFME_INGAME_SLOT( 00 ) BFME_INGAME_SLOT( 01 ) BFME_INGAME_SLOT( 02 )
	BFME_INGAME_SLOT( 03 ) BFME_INGAME_SLOT( 04 ) BFME_INGAME_SLOT( 05 )
	BFME_INGAME_SLOT( 06 ) BFME_INGAME_SLOT( 07 ) BFME_INGAME_SLOT( 08 )
	BFME_INGAME_SLOT( 09 ) BFME_INGAME_SLOT( 10 ) BFME_INGAME_SLOT( 11 )
	BFME_INGAME_SLOT( 12 ) BFME_INGAME_SLOT( 13 ) BFME_INGAME_SLOT( 14 )
	BFME_INGAME_SLOT( 15 ) BFME_INGAME_SLOT( 16 ) BFME_INGAME_SLOT( 17 )
	BFME_INGAME_SLOT( 18 ) BFME_INGAME_SLOT( 19 ) BFME_INGAME_SLOT( 20 )
	BFME_INGAME_SLOT( 21 ) BFME_INGAME_SLOT( 22 ) BFME_INGAME_SLOT( 23 )
	BFME_INGAME_SLOT( 24 ) BFME_INGAME_SLOT( 25 ) BFME_INGAME_SLOT( 26 )
	BFME_INGAME_SLOT( 27 ) BFME_INGAME_SLOT( 28 ) BFME_INGAME_SLOT( 29 )
	BFME_INGAME_SLOT( 30 ) BFME_INGAME_SLOT( 31 ) BFME_INGAME_SLOT( 32 )
	BFME_INGAME_SLOT( 33 ) BFME_INGAME_SLOT( 34 ) BFME_INGAME_SLOT( 35 )
	BFME_INGAME_SLOT( 36 ) BFME_INGAME_SLOT( 37 ) BFME_INGAME_SLOT( 38 )
	BFME_INGAME_SLOT( 39 ) BFME_INGAME_SLOT( 40 ) BFME_INGAME_SLOT( 41 )
	BFME_INGAME_SLOT( 42 ) BFME_INGAME_SLOT( 43 ) BFME_INGAME_SLOT( 44 )
	BFME_INGAME_SLOT( 45 ) BFME_INGAME_SLOT( 46 ) BFME_INGAME_SLOT( 47 )
	BFME_INGAME_SLOT( 48 ) BFME_INGAME_SLOT( 49 ) BFME_INGAME_SLOT( 50 )
	BFME_INGAME_SLOT( 51 ) BFME_INGAME_SLOT( 52 ) BFME_INGAME_SLOT( 53 )
	BFME_INGAME_SLOT( 54 ) BFME_INGAME_SLOT( 55 ) BFME_INGAME_SLOT( 56 )
	BFME_INGAME_SLOT( 57 ) BFME_INGAME_SLOT( 58 ) BFME_INGAME_SLOT( 59 )
	BFME_INGAME_SLOT( 60 ) BFME_INGAME_SLOT( 61 ) BFME_INGAME_SLOT( 62 )
	BFME_INGAME_SLOT( 63 ) BFME_INGAME_SLOT( 64 )
	virtual Drawable *getFirstSelectedDrawable( void ) = 0;
#undef BFME_INGAME_SLOT
};

class Drawable
{
	char m_pad[ 0xfc ];

public:
	Object *m_object;
};

class ProductionUpdateInterface
{
public:
#define BFME_PUI_SLOT( n ) virtual void slot##n( void ) = 0;
	BFME_PUI_SLOT( 00 ) BFME_PUI_SLOT( 01 ) BFME_PUI_SLOT( 02 )
	BFME_PUI_SLOT( 03 ) BFME_PUI_SLOT( 04 ) BFME_PUI_SLOT( 05 )
	BFME_PUI_SLOT( 06 ) BFME_PUI_SLOT( 07 ) BFME_PUI_SLOT( 08 )
	BFME_PUI_SLOT( 09 ) BFME_PUI_SLOT( 10 ) BFME_PUI_SLOT( 11 )
	BFME_PUI_SLOT( 12 ) BFME_PUI_SLOT( 13 ) BFME_PUI_SLOT( 14 )
	virtual void *slot15( BfmeThingLU *thing ) = 0;
	BFME_PUI_SLOT( 16 )
	virtual void *slot17( BfmeUpgradeMask *mask ) = 0;
#undef BFME_PUI_SLOT
};

extern InGameUI *TheInGameUI;

extern void j_00003b52( void );
extern void j_00010e88( void );
extern void j_000205cc( void );
extern void j_00023240( void );
extern void j_00036692( void );
extern void j_00046538( void );

typedef void *(__cdecl *GetButtonData)( GameWindow * );

struct GameWindowCallTarget {};
struct ObjectCallTarget {};
struct CommandButtonCallTarget {};
struct UpgradeMaskCallTarget {};

typedef void *(GameWindowCallTarget::*GetUserDataCall)( void );
typedef ProductionUpdateInterface *(ObjectCallTarget::*GetProductionUpdateInterfaceCall)( void );
typedef BfmeThingLU *(CommandButtonCallTarget::*ResolveCommandButtonCall)( void );
typedef void (CommandButtonCallTarget::*FillUpgradeMaskCall)( BfmeUpgradeMask * );
typedef Bool (UpgradeMaskCallTarget::*AnyOccupiedCall)( void ) const;

void Rva004BC8A0( GameWindow *window )
{
	if( window == 0 )
		return;

	union
	{
		void (*raw)( void );
		GetUserDataCall member;
	} getUserData;
	getUserData.raw = j_00046538;
	void *data = (reinterpret_cast<GameWindowCallTarget *>( window )->*
		getUserData.member)();
	if( data == 0 )
		return;

	*(void **)((char *)data + 0x2c) = 0;

	Drawable *drawable = TheInGameUI->getFirstSelectedDrawable();
	if( drawable == 0 )
		return;

	Object *object = *(Object **)((char *)drawable + 0xfc);
	if( object == 0 )
		return;

	union
	{
		void (*raw)( void );
		GetProductionUpdateInterfaceCall member;
	} getProductionUpdateInterface;
	getProductionUpdateInterface.raw = j_00003b52;
	ProductionUpdateInterface *pui =
		(reinterpret_cast<ObjectCallTarget *>( object )->*
		getProductionUpdateInterface.member)();
	if( pui == 0 )
		return;

	CommandButton *command =
		(CommandButton *)((GetButtonData)j_00010e88)( window );
	if( command == 0 )
		return;

	union
	{
		void (*raw)( void );
		ResolveCommandButtonCall member;
	} resolveCommandButton;
	resolveCommandButton.raw = j_000205cc;
	BfmeThingLU *thing =
		(reinterpret_cast<CommandButtonCallTarget *>( command )->*
		resolveCommandButton.member)();
	if( thing == 0 )
		return;

	BfmeUpgradeMask mask;
	union
	{
		void (*raw)( void );
		FillUpgradeMaskCall member;
	} fillUpgradeMask;
	fillUpgradeMask.raw = j_00023240;
	(reinterpret_cast<CommandButtonCallTarget *>( command )->*
		fillUpgradeMask.member)( &mask );
	union
	{
		void (*raw)( void );
		AnyOccupiedCall member;
	} anyOccupied;
	anyOccupied.raw = j_00036692;
	if( (reinterpret_cast<UpgradeMaskCallTarget *>( &mask )->*
		anyOccupied.member)() )
		*(void **)((char *)data + 0x2c) = pui->slot17( &mask );
	else
		*(void **)((char *)data + 0x2c) = pui->slot15( thing );
}
