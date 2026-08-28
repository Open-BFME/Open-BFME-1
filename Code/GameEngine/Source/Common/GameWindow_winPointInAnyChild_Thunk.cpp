// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?winPointInAnyChild@GameWindow@@QAEPAV1@HH_N0@Z: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// Open-BFME5: GameWindow::winPointInAnyChild, retail 0x00479970, converted out
// of a machine byte dump. The reference body ports unchanged.
//
// The 145 bytes fix the window layout, and every offset agrees with the naked
// sibling in GameWindow_winPointInChild_Thunk.cpp, which is the reason to
// believe them:
//
//   +0x008  m_status          (`f6 41 08 10` -- WIN_STATUS_HIDDEN is 0x10)
//   +0x00C  m_size.x
//   +0x010  m_size.y
//   +0x014  m_region.lo.x
//   +0x018  m_region.lo.y
//   +0x1F8  m_next
//   +0x200  m_parent
//   +0x204  m_child
//
// The tail is the one thing worth reading twice. Retail pushes four arguments
// to winPointInChild -- `6a 00 / 50 / 53 / 55` -- while the reference source
// writes three. That is not a signature difference: the fourth parameter,
// playDisabledSound, defaults to FALSE, and a default argument is materialised
// at the call site. Declaring the callee with the default and calling it with
// three arguments emits the `push 0` on its own.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

#define TRUE  true
#define FALSE false

#define BitTest( x, i ) (((x) & (i)) != 0)

enum { WIN_STATUS_HIDDEN = 0x00000010 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;													///< +0x00
	Int y;													///< +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct IRegion2D
{
	ICoord2D lo;											///< +0x00
	ICoord2D hi;											///< +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	GameWindow *winPointInChild( Int x, Int y, Bool ignoreEnableCheck = FALSE,
															 Bool playDisabledSound = FALSE );
	GameWindow *winPointInAnyChild( Int x, Int y, Bool ignoreHidden,
																	Bool ignoreEnableCheck = FALSE );

private:
	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_status;									///< +0x008
	ICoord2D m_size;										///< +0x00C
	IRegion2D m_region;										///< +0x014
	unsigned char m_unreconstructed_24[0x1F8 - 0x24];
	GameWindow *m_next;										///< +0x1F8
	unsigned char m_unreconstructed_1fc[0x200 - 0x1FC];
	GameWindow *m_parent;									///< +0x200
	GameWindow *m_child;									///< +0x204
};

// GameWindow::winPointInAnyChild =============================================
/** Find the child in which the cursor resides; regardless of
	* whether or not the window is actually enabled */
//=============================================================================
// ?winPointInAnyChild@GameWindow@@QAEPAV1@HH_N0@Z
GameWindow *GameWindow::winPointInAnyChild( Int x, Int y, Bool ignoreHidden, Bool ignoreEnableCheck )
{
	GameWindow *parent;
	GameWindow *child;
	ICoord2D origin;

	for( child = m_child; child; child = child->m_next )
	{

		origin = child->m_region.lo;
		parent = child->m_parent;

		while( parent )
		{

			origin.x += parent->m_region.lo.x;
			origin.y += parent->m_region.lo.y;
			parent = parent->m_parent;

		}  // end while

		if( x >= origin.x && x <= origin.x + child->m_size.x &&
				y >= origin.y && y <= origin.y + child->m_size.y )
		{

			if( !(ignoreHidden == TRUE &&	BitTest( child->m_status, WIN_STATUS_HIDDEN )) )
				return child->winPointInChild( x, y, ignoreEnableCheck );

		}  // end if

	}  // end for child

	// not in any children, must be in parent
	return this;

}  // end WinPointInAnyChild
