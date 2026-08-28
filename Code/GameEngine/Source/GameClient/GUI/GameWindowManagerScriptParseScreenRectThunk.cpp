// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: parseScreenRect, retail 0x004854F0, converted out of a machine
// byte dump. The reference body ports unchanged.
//
// Four things in the 453 bytes are worth writing down.
//
// BFME's signature is not the reference's. Retail reads its four Int* through
// [esp+0x38..0x44], the first four argument slots, and its one caller at
// 0x00488127 pushes exactly four addresses -- 0x012F2544, 0x012F2548,
// 0x012F254C, 0x012F2550, four consecutive globals -- before the call. The
// reference's leading `char *token, char *buffer` are unused in the body and
// are gone here, which is why the symbol is ?parseScreenRect@@YA_NPAH000@Z and
// not the reference's ...@@YA_NPAD0PAH111@Z. Keeping them compiles to a body of
// exactly the right length whose every argument reference is eight bytes off.
//
// The prologue is peekWindow() inlined: `mov eax,[stackPtr]` /
// `cmp eax, offset windowStack` / `xor ebp,ebp` or `mov ebp,[eax-4]`. That the
// compare is against an immediate rather than a load is what says windowStack
// is an array and stackPtr a separate pointer into it, and retail's addresses
// put stackPtr at 0x012F24F4 immediately BEFORE windowStack at 0x012F24F8 --
// the reverse of their declaration order, which is ordinary BSS layout and not
// something the source has to say.
//
// getWidth and getHeight are called through slots +0x2C and +0x30, and each
// result gets the `test eax,eax / jge / fadd 4294967296.0` fixup, so both
// return UnsignedInt rather than Int. The dummy slots below exist only to put
// the two real ones at those offsets; BFME's Display has more virtuals ahead of
// them than the reference does.
//
// scanInt is inlined at every one of its six call sites -- there is no call to
// it anywhere in the body, just six sscanf calls through the IAT -- which is
// why it is spelled out here as a static rather than reached for as a helper.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

#define NULL 0
#define TRUE true

// _CRTIMP, spelled out. Retail hoists the two IAT slots into esi and edi and
// calls `ff d6` / `ff d7` fifteen times; a plain declaration compiles to
// fifteen direct `e8` calls instead, which is the whole of the 33-byte
// difference between a correct body and this one.
extern "C" __declspec(dllimport) int __cdecl sscanf( const char *, const char *, ... );
extern "C" __declspec(dllimport) char * __cdecl strtok( char *, const char * );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winGetScreenPosition( Int *x, Int *y );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void bfmeRetailSlot00( void ) = 0;
	virtual void bfmeRetailSlot01( void ) = 0;
	virtual void bfmeRetailSlot02( void ) = 0;
	virtual void bfmeRetailSlot03( void ) = 0;
	virtual void bfmeRetailSlot04( void ) = 0;
	virtual void bfmeRetailSlot05( void ) = 0;
	virtual void bfmeRetailSlot06( void ) = 0;
	virtual void bfmeRetailSlot07( void ) = 0;
	virtual void bfmeRetailSlot08( void ) = 0;
	virtual void bfmeRetailSlot09( void ) = 0;
	virtual void bfmeRetailSlot10( void ) = 0;
	virtual UnsignedInt getWidth( void ) = 0;				///< +0x2C
	virtual UnsignedInt getHeight( void ) = 0;				///< +0x30
};

extern Display *TheDisplay;

enum { WIN_STACK_DEPTH = 10 };

// Implement a stack to keep track of parent/child nested window descriptions.
static GameWindow *windowStack[ WIN_STACK_DEPTH ];
static GameWindow **stackPtr;

// scanInt ====================================================================
//=============================================================================
static Int scanInt( const char *source, Int& val )
{
	Int ret = sscanf( source, "%d", &val ); // not strictly necessary to wrap this, but it's more consistent

	return ret;
}  // end scanInt

// peekWindow =================================================================
//=============================================================================
static GameWindow *peekWindow( void )
{
  if (stackPtr == windowStack)
    return NULL;

  return *(stackPtr - 1);

}  // end peekWindow

// parseScreenRect ============================================================
/** Parse the screen rect entry which tells us the position and size
	* of window.  Note we scale for the current resolution if needed
	* and adjust to make the screen rect coords relative to any parent
	* if present */
//=============================================================================
// ?parseScreenRect@@YA_NPAH000@Z
Bool parseScreenRect( Int *x, Int *y, Int *width, Int *height )
{
	GameWindow *parent = peekWindow();
	IRegion2D screenRegion;
	ICoord2D createRes;  // creation resolution
	char *seps = " ,:=\n\r\t";
	char *c;

	c = strtok( NULL, seps );  // UPPERLEFT token
	c = strtok( NULL, seps );  // x position
	scanInt( c, screenRegion.lo.x );
	c = strtok( NULL, seps );  // y posotion
	scanInt( c, screenRegion.lo.y );

	c = strtok( NULL, seps );  // BOTTOMRIGHT token
	c = strtok( NULL, seps );  // x position
	scanInt( c, screenRegion.hi.x );
	c = strtok( NULL, seps );  // y posotion
	scanInt( c, screenRegion.hi.y );

	c = strtok( NULL, seps );  // CREATIONRESOLUTION token
	c = strtok( NULL, seps );  // x creation resolution
	scanInt( c, createRes.x );
	c = strtok( NULL, seps );  // y creation resolution
	scanInt( c, createRes.y );

	//
	// shrink or expand the screen region by the ratio of the current
	// resolution divided by the creation resolution
	//
	Real xScale = (Real)TheDisplay->getWidth() / (Real)createRes.x;
	Real yScale = (Real)TheDisplay->getHeight() / (Real)createRes.y;
	screenRegion.lo.x = (Int)((Real)screenRegion.lo.x * xScale);
	screenRegion.lo.y = (Int)((Real)screenRegion.lo.y * yScale);
	screenRegion.hi.x = (Int)((Real)screenRegion.hi.x * xScale);
	screenRegion.hi.y = (Int)((Real)screenRegion.hi.y * yScale);

	//
	// given the screen region upper left compute the upper left that we
	// will give this window, if we have a parent note that the position
	// is relative to the parent client area, if no parent is present
	// we're talking about the screen
	//
	if( parent )
	{
		ICoord2D parentScreenPos;

		// get parent position on screen
		parent->winGetScreenPosition( &parentScreenPos.x, &parentScreenPos.y );

		// save x and y with parent position as relative (0,0) location
		*x = screenRegion.lo.x - parentScreenPos.x;
		*y = screenRegion.lo.y - parentScreenPos.y;

	}  // end if
	else
	{

		*x = screenRegion.lo.x;
		*y = screenRegion.lo.y;

	}  // end else

	// save the width and height
	*width = screenRegion.hi.x - screenRegion.lo.x;
	*height = screenRegion.hi.y - screenRegion.lo.y;

	return TRUE;

}  // end parseScreenRect
