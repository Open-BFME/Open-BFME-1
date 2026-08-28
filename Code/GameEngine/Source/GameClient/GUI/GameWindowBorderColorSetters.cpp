// cl: /DNDEBUG /MD /EHs-c-

// The nine winSet<state><field> setters sit in one run at 0x00478FE0, each 37
// or 40 bytes and identical apart from the store's displacement:
//
//   0x00478FE0 +0x48   0x00479010 +0x4C   0x00479040 +0x50    enabled
//   0x00479070 +0xB4   0x004790A0 +0xB8   0x004790E0 +0xBC    disabled
//   0x00479120 +0x120  0x00479150 +0x124  0x00479190 +0x128   hilite
//
// so the draw data is three arrays of nine 12-byte {image, color, borderColor}
// entries starting at +0x48 -- and the index test is against nine, not the
// eight Zero Hour's MAX_DRAW_DATA has.
//
// GameWindow.cpp compiles these from Zero Hour's own WinInstanceData, whose
// draw data lands four bytes lower, so its rows are all one slot off: what it
// calls winSetEnabledColor is really the image setter, and the third of each
// group has no row at all. Those three are the bodies claimed here, under
// dup_ names because GameWindow.cpp holds the real ones.

typedef int Int;
typedef int Color;			// HHH, so signed here

enum { MAX_DRAW_DATA = 9 };
enum { WIN_ERR_OK = 0, WIN_ERR_INVALID_PARAMETER = -3 };

class Image;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	WinDrawData m_enabledDrawData[ MAX_DRAW_DATA ];
	WinDrawData m_disabledDrawData[ MAX_DRAW_DATA ];
	WinDrawData m_hiliteDrawData[ MAX_DRAW_DATA ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winSetEnabledBorderColor( Int index, Color color );
	Int winSetDisabledBorderColor( Int index, Color color );
	Int winSetHiliteBorderColor( Int index, Color color );

private:
	char m_bfmeHead[ 0x48 ];
	WinInstanceData m_instData;			// +0x48
};

// GameWindow::winSetEnabledBorderColor =======================================
/** set border color for state at this index */
//=============================================================================
Int GameWindow::winSetEnabledBorderColor( Int index, Color color )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
		return WIN_ERR_INVALID_PARAMETER;

	m_instData.m_enabledDrawData[ index ].borderColor = color;
	return WIN_ERR_OK;

}  // end winSetEnabledBorderColor

// GameWindow::winSetDisabledBorderColor ======================================
/** set border color for state at this index */
//=============================================================================
Int GameWindow::winSetDisabledBorderColor( Int index, Color color )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
		return WIN_ERR_INVALID_PARAMETER;

	m_instData.m_disabledDrawData[ index ].borderColor = color;
	return WIN_ERR_OK;

}  // end winSetDisabledBorderColor

// GameWindow::winSetHiliteBorderColor ========================================
/** set border color for state at this index */
//=============================================================================
Int GameWindow::winSetHiliteBorderColor( Int index, Color color )
{

	// sanity
	if( index < 0 || index >= MAX_DRAW_DATA )
		return WIN_ERR_INVALID_PARAMETER;

	m_instData.m_hiliteDrawData[ index ].borderColor = color;
	return WIN_ERR_OK;

}  // end winSetHiliteBorderColor
