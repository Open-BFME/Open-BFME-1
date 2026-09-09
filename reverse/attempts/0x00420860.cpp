// ?drawIconUI@Drawable@@QAEXXZ
// partial score=0.98 date=2026-09-08
// ?drawIconUI@Drawable@@QAEXXZ
// This body matches the retail control flow and stack layout through the
// projection path. The remaining four bytes come from MSVC 7.1 x87 load and
// FPU-stack cleanup choices in the adjusted health-box calculation.

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

class Object;
class Player;

class BFMEDrawableAIChain
{
public:
	unsigned char m_padding[0xfc];
	Object *m_object;
};

class Drawable
{
public:
	void drawIconUI();
};

class DrawableIconGameLogic
{
public:
	unsigned char m_padding[ 0x92 ];
	unsigned char m_drawIconUI;
};

class DrawableIconScriptEngine
{
public:
	unsigned char m_padding[ 0x170b4 ];
	Int m_fade;
};

class DrawableIconTacticalView
{
public:
#define DRAWABLE_ICON_VIEW_SLOT( n ) virtual void slot##n();
	DRAWABLE_ICON_VIEW_SLOT( 0 ) DRAWABLE_ICON_VIEW_SLOT( 1 )
	DRAWABLE_ICON_VIEW_SLOT( 2 ) DRAWABLE_ICON_VIEW_SLOT( 3 )
	DRAWABLE_ICON_VIEW_SLOT( 4 ) DRAWABLE_ICON_VIEW_SLOT( 5 )
	DRAWABLE_ICON_VIEW_SLOT( 6 ) DRAWABLE_ICON_VIEW_SLOT( 7 )
	DRAWABLE_ICON_VIEW_SLOT( 8 ) DRAWABLE_ICON_VIEW_SLOT( 9 )
	DRAWABLE_ICON_VIEW_SLOT( 10 ) DRAWABLE_ICON_VIEW_SLOT( 11 )
	DRAWABLE_ICON_VIEW_SLOT( 12 ) DRAWABLE_ICON_VIEW_SLOT( 13 )
	DRAWABLE_ICON_VIEW_SLOT( 14 ) DRAWABLE_ICON_VIEW_SLOT( 15 )
	DRAWABLE_ICON_VIEW_SLOT( 16 ) DRAWABLE_ICON_VIEW_SLOT( 17 )
	DRAWABLE_ICON_VIEW_SLOT( 18 ) DRAWABLE_ICON_VIEW_SLOT( 19 )
	DRAWABLE_ICON_VIEW_SLOT( 20 ) DRAWABLE_ICON_VIEW_SLOT( 21 )
	DRAWABLE_ICON_VIEW_SLOT( 22 ) DRAWABLE_ICON_VIEW_SLOT( 23 )
	DRAWABLE_ICON_VIEW_SLOT( 24 ) DRAWABLE_ICON_VIEW_SLOT( 25 )
	DRAWABLE_ICON_VIEW_SLOT( 26 ) DRAWABLE_ICON_VIEW_SLOT( 27 )
	DRAWABLE_ICON_VIEW_SLOT( 28 ) DRAWABLE_ICON_VIEW_SLOT( 29 )
	DRAWABLE_ICON_VIEW_SLOT( 30 ) DRAWABLE_ICON_VIEW_SLOT( 31 )
	DRAWABLE_ICON_VIEW_SLOT( 32 ) DRAWABLE_ICON_VIEW_SLOT( 33 )
	DRAWABLE_ICON_VIEW_SLOT( 34 ) DRAWABLE_ICON_VIEW_SLOT( 35 )
	DRAWABLE_ICON_VIEW_SLOT( 36 ) DRAWABLE_ICON_VIEW_SLOT( 37 )
	DRAWABLE_ICON_VIEW_SLOT( 38 ) DRAWABLE_ICON_VIEW_SLOT( 39 )
	DRAWABLE_ICON_VIEW_SLOT( 40 ) DRAWABLE_ICON_VIEW_SLOT( 41 )
	DRAWABLE_ICON_VIEW_SLOT( 42 ) DRAWABLE_ICON_VIEW_SLOT( 43 )
	DRAWABLE_ICON_VIEW_SLOT( 44 ) DRAWABLE_ICON_VIEW_SLOT( 45 )
	DRAWABLE_ICON_VIEW_SLOT( 46 ) DRAWABLE_ICON_VIEW_SLOT( 47 )
	DRAWABLE_ICON_VIEW_SLOT( 48 ) DRAWABLE_ICON_VIEW_SLOT( 49 )
	DRAWABLE_ICON_VIEW_SLOT( 50 ) DRAWABLE_ICON_VIEW_SLOT( 51 )
	DRAWABLE_ICON_VIEW_SLOT( 52 ) DRAWABLE_ICON_VIEW_SLOT( 53 )
	DRAWABLE_ICON_VIEW_SLOT( 54 ) DRAWABLE_ICON_VIEW_SLOT( 55 )
	DRAWABLE_ICON_VIEW_SLOT( 56 ) DRAWABLE_ICON_VIEW_SLOT( 57 )
	DRAWABLE_ICON_VIEW_SLOT( 58 ) DRAWABLE_ICON_VIEW_SLOT( 59 )
	DRAWABLE_ICON_VIEW_SLOT( 60 ) DRAWABLE_ICON_VIEW_SLOT( 61 )
	DRAWABLE_ICON_VIEW_SLOT( 62 ) DRAWABLE_ICON_VIEW_SLOT( 63 )
	DRAWABLE_ICON_VIEW_SLOT( 64 ) DRAWABLE_ICON_VIEW_SLOT( 65 )
	DRAWABLE_ICON_VIEW_SLOT( 66 ) DRAWABLE_ICON_VIEW_SLOT( 67 )
	DRAWABLE_ICON_VIEW_SLOT( 68 ) DRAWABLE_ICON_VIEW_SLOT( 69 )
	DRAWABLE_ICON_VIEW_SLOT( 70 ) DRAWABLE_ICON_VIEW_SLOT( 71 )
	virtual Real getZoom() const;
	DRAWABLE_ICON_VIEW_SLOT( 73 ) DRAWABLE_ICON_VIEW_SLOT( 74 )
	DRAWABLE_ICON_VIEW_SLOT( 75 ) DRAWABLE_ICON_VIEW_SLOT( 76 )
	DRAWABLE_ICON_VIEW_SLOT( 77 ) DRAWABLE_ICON_VIEW_SLOT( 78 )
	virtual Real getMaxZoom() const;
	DRAWABLE_ICON_VIEW_SLOT( 80 ) DRAWABLE_ICON_VIEW_SLOT( 81 )
	DRAWABLE_ICON_VIEW_SLOT( 82 ) DRAWABLE_ICON_VIEW_SLOT( 83 )
	DRAWABLE_ICON_VIEW_SLOT( 84 ) DRAWABLE_ICON_VIEW_SLOT( 85 )
	DRAWABLE_ICON_VIEW_SLOT( 86 )
	virtual Int worldToScreen( const Coord3D *world, ICoord2D *screen );
#undef DRAWABLE_ICON_VIEW_SLOT
};

class DrawableIconObjectCall
{
public:
	Int getHealthBoxDimensions( Real &height, Real &width ) const;
	Bool testStatus( Int status ) const;
	Bool isKindOf( Int kind ) const;
	Bool isLocallyControlled() const;
	Player *getControllingPlayer() const;
};

class DrawableIconPlayerCall
{
public:
	Int getSquadNumberForObject( const Object *object ) const;
};

class DrawableIconSelfCall
{
public:
	void getHealthBoxPosition( Coord3D &position );
	const Coord3D *getPosition() const;
};

class DrawableIconClientCall
{
public:
	void addIcon( Int stage, Drawable *drawable );
};

class DrawableIconRegion
{
public:
	unsigned char m_padding[ 0x3c4 ];
	Int m_left;
	Int m_top;
	Int m_right;
	Int m_bottom;
};

struct DrawableIconLocals
{
	Real m_width;
	Real m_height;
	Int m_left;
	union
	{
		Int m_top;
		ICoord2D m_adjustedScreen;
	};
	ICoord2D m_screenCenter;
	Coord3D m_adjustedHealthBoxPosition;
	Coord3D m_healthBoxPosition;
};

union DrawableIconHealthPositionCall
{
	void (*freeFunction)();
	void (DrawableIconSelfCall::*memberFunction)( Coord3D & );
};

union DrawableIconPositionCall
{
	void (*freeFunction)();
	const Coord3D *(DrawableIconSelfCall::*memberFunction)() const;
};

union DrawableIconDimensionsCall
{
	void (*freeFunction)();
	Bool (DrawableIconObjectCall::*memberFunction)( Real &, Real & ) const;
};

union DrawableIconStatusCall
{
	void (*freeFunction)();
	Bool (DrawableIconObjectCall::*memberFunction)( Int ) const;
};

union DrawableIconObjectPredicateCall
{
	void (*freeFunction)();
	Bool (DrawableIconObjectCall::*memberFunction)() const;
};

union DrawableIconKindCall
{
	void (*freeFunction)();
	Bool (DrawableIconObjectCall::*memberFunction)( Int ) const;
};

union DrawableIconOwnerCall
{
	void (*freeFunction)();
	Player *(DrawableIconObjectCall::*memberFunction)() const;
};

union DrawableIconPlayerCallValue
{
	void (*freeFunction)();
	Int (DrawableIconPlayerCall::*memberFunction)( const Object * ) const;
};

union DrawableIconQueueCall
{
	void (*freeFunction)();
	void (DrawableIconClientCall::*memberFunction)( Int, Drawable * );
};

#define DRAWABLE_ICON_GAME_LOGIC (*(DrawableIconGameLogic **)0x012F0898)
#define DRAWABLE_ICON_SCRIPT_ENGINE (*(DrawableIconScriptEngine **)0x012F076C)
#define DRAWABLE_ICON_TACTICAL_VIEW (*(DrawableIconTacticalView **)0x012F1600)
#define DRAWABLE_ICON_CLIENT (*(DrawableIconClientCall **)0x012F1464)
#define DRAWABLE_ICON_DEFAULT (*(const Real *)0x01075334)
#define DRAWABLE_ICON_VERTICAL_SCALE (*(const Real *)0x010F15CC)
#define DRAWABLE_ICON_WIDTH_SCALE (*(const Real *)0x010F1628)
#define DRAWABLE_ICON_TWO (*(const Real *)0x01088830)
#define DRAWABLE_ICON_FOUR (*(const Real *)0x01075340)

extern void j_000016a4();
extern void j_0001ff91();
extern void j_00020824();
extern void j_000211fc();
extern void j_00021715();
extern void j_000239ed();
extern void j_0003251f();
extern void j_0003ee55();
extern void j_00042aff();

void Drawable::drawIconUI( void )
{
	if ( DRAWABLE_ICON_GAME_LOGIC->m_drawIconUI == 0 )
		return;
	if ( DRAWABLE_ICON_SCRIPT_ENGINE->m_fade != 0 )
		return;

	Object *object = (Object *)((BFMEDrawableAIChain *)this)->m_object;
	if ( object == 0 )
		return;

	DrawableIconLocals locals;
	DrawableIconHealthPositionCall healthPosition = { j_000239ed };
	(reinterpret_cast<DrawableIconSelfCall *>( this )->*healthPosition.memberFunction)(
		locals.m_healthBoxPosition );

	DrawableIconDimensionsCall dimensions = { j_00042aff };
	if ( !(reinterpret_cast<DrawableIconObjectCall *>( object )->*dimensions.memberFunction)(
		locals.m_height, locals.m_width ) )
		return;

	if ( DRAWABLE_ICON_TACTICAL_VIEW->worldToScreen(
		&locals.m_healthBoxPosition, &locals.m_screenCenter ) )
	{
		DrawableIconStatusCall status = { j_000016a4 };
		if ( !(reinterpret_cast<DrawableIconObjectCall *>( object )->*status.memberFunction)( 2 ) )
			return;

		(reinterpret_cast<DrawableIconSelfCall *>( this )->*healthPosition.memberFunction)(
			locals.m_adjustedHealthBoxPosition );
		DrawableIconPositionCall position = { j_0003ee55 };
		const Coord3D *drawablePosition =
			(reinterpret_cast<DrawableIconSelfCall *>( this )->*position.memberFunction)();
		DrawableIconTacticalView *tacticalView = DRAWABLE_ICON_TACTICAL_VIEW;
	Real &adjustedZ = locals.m_adjustedHealthBoxPosition.z;
	adjustedZ -= (drawablePosition->z - adjustedZ) * DRAWABLE_ICON_VERTICAL_SCALE;

		if ( tacticalView->worldToScreen(
			&locals.m_adjustedHealthBoxPosition, &locals.m_adjustedScreen ) )
			return;
	}

	locals.m_width *= DRAWABLE_ICON_DEFAULT / DRAWABLE_ICON_TACTICAL_VIEW->getZoom();
	locals.m_height = 4.0f;
	DrawableIconRegion *region = reinterpret_cast<DrawableIconRegion *>( this );
	locals.m_left = (Int)(locals.m_screenCenter.x - locals.m_width * DRAWABLE_ICON_WIDTH_SCALE);
	region->m_left = locals.m_left;
	locals.m_top = (Int)(locals.m_screenCenter.y - DRAWABLE_ICON_TWO);
	region->m_top = locals.m_top;
	region->m_right = (Int)(locals.m_left + locals.m_width);
	region->m_bottom = (Int)(locals.m_top + DRAWABLE_ICON_FOUR);

	DrawableIconQueueCall queue = { j_00021715 };
	(DRAWABLE_ICON_CLIENT->*queue.memberFunction)( 0, this );
	if ( ((unsigned char *)object)[ 0x344 ] & 1 )
		return;
	DrawableIconKindCall kind = { j_0003251f };
	if ( (reinterpret_cast<DrawableIconObjectCall *>( object )->*kind.memberFunction)( 0x2f ) )
		return;
	(DRAWABLE_ICON_CLIENT->*queue.memberFunction)( 1, this );
	(DRAWABLE_ICON_CLIENT->*queue.memberFunction)( 2, this );
	if ( ((unsigned char *)this)[ 0x3ac ] == 0 )
		return;
	DrawableIconObjectPredicateCall local = { j_0001ff91 };
	if ( !(reinterpret_cast<DrawableIconObjectCall *>( object )->*local.memberFunction)() )
		return;
	DrawableIconOwnerCall owner = { j_00020824 };
	Player *player = (reinterpret_cast<DrawableIconObjectCall *>( object )->*owner.memberFunction)();
	DrawableIconPlayerCallValue squadNumber = { j_000211fc };
	Int squad = (reinterpret_cast<DrawableIconPlayerCall *>( player )->*squadNumber.memberFunction)( object );
	if ( squad <= -1 || squad >= 10 )
		return;
	(DRAWABLE_ICON_CLIENT->*queue.memberFunction)( 3, this );
}
