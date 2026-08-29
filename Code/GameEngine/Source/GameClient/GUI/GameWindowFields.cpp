// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/gamewindow /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?winClearStatus@GameWindow@@QAEII@Z: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetChild@GameWindow@@QAEPAV1@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetEnabledTextBorderColor@GameWindow@@QAEHXZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetInstanceData@GameWindow@@QAEPAVWinInstanceData@@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetLayout@GameWindow@@QAEPAVWindowLayout@@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetNext@GameWindow@@QAEPAV1@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetNextInLayout@GameWindow@@QAEPAV1@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetOwner@GameWindow@@QAEPAV1@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetParent@GameWindow@@QAEPAV1@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetPrev@GameWindow@@QAEPAV1@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetPrevInLayout@GameWindow@@QAEPAV1@XZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetScreenPosition@GameWindow@@QAEHPAH0@Z: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetStatus@GameWindow@@QAEIXZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetStyle@GameWindow@@QAEIXZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetUserData@GameWindow@@QAEPAXXZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winGetWindowId@GameWindow@@QAEHXZ: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winSetDisabledImage@GameWindow@@QAEHHPBVImage@@@Z: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winSetEnabledImage@GameWindow@@QAEHHPBVImage@@@Z: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winSetHiliteImage@GameWindow@@QAEHHPBVImage@@@Z: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winSetPrev@GameWindow@@QAEXPAV1@@Z: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winSetSize@GameWindow@@QAEHHH@Z: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// readable body of ?winSetTooltipFunc@GameWindow@@QAEHP6AXPAV1@PAVWinInstanceData@@I@Z@Z: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
//
// GameWindow field accessors, byte-matched against the reconstructed BFME
// GameWindow layout (reference/shims/gamewindow/GameClient/GameWindow.h). These
// are the retail bodies the incremental-link thunks jump to; each is a single
// field load off the real BFME offset (m_status@0x08, m_instData@0x30, ...).
//
// They live here rather than in GUI/GameWindow.cpp because that TU resolves
// GameClient/GameWindow.h to the ZH-layout reference header (m_instData@0x2c);
// the private /Ireference/shims/gamewindow above makes only this TU see the
// true BFME offsets, so converting these leaves does not disturb GameWindow.cpp.
#include "PreRTS.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"  // TheWindowManager
#include "GameClient/Gadget.h"          // GWS_COMBO_BOX
#include "GameClient/GadgetComboBox.h"  // GadgetComboBoxSet*TextColors

// ?winGetInstanceData@GameWindow@@QAEPAVWinInstanceData@@XZ
WinInstanceData *GameWindow::winGetInstanceData( void )
{
	return &m_instData;
}

// ?winGetUserData@GameWindow@@QAEPAXXZ
void *GameWindow::winGetUserData( void )
{
	return m_userData;
}

// ?winGetStatus@GameWindow@@QAEIXZ
UnsignedInt GameWindow::winGetStatus( void )
{
	return m_status;
}

// ?winGetStyle@GameWindow@@QAEIXZ
UnsignedInt GameWindow::winGetStyle( void )
{
	return m_instData.m_style;
}

// ?winGetWindowId@GameWindow@@QAEHXZ
Int GameWindow::winGetWindowId( void )
{
	return m_instData.m_id;
}

// ?winIsHidden@GameWindow@@QAE_NXZ
Bool GameWindow::winIsHidden( void )
{
	return BitTest( m_status, WIN_STATUS_HIDDEN );
}

// Read m_instData.m_owner (@0x44) directly rather than via getOwner(): the inline
// WinInstanceData::getOwner() otherwise emits an out-of-line COMDAT with no ledger
// row. Same bytes.
// ?winGetOwner@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetOwner( void )
{
	return m_instData.m_owner;
}

// The window-list / layout pointer leaves below prove the reconstructed tail
// (m_next@0x1f8, m_prev@0x1fc, m_parent@0x200, m_child@0x204,
//  m_nextLayout@0x208, m_prevLayout@0x20c, m_layout@0x210).

// ?winGetNext@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetNext( void )
{
	return m_next;
}

// ?winGetPrev@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetPrev( void )
{
	return m_prev;
}

// ?winGetParent@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetParent( void )
{
	return m_parent;
}

// ?winGetChild@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetChild( void )
{
	return m_child;
}

// ?winGetNextInLayout@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetNextInLayout( void )
{
	return m_nextLayout;
}

// ?winGetPrevInLayout@GameWindow@@QAEPAV1@XZ
GameWindow *GameWindow::winGetPrevInLayout( void )
{
	return m_prevLayout;
}

// ?winGetLayout@GameWindow@@QAEPAVWindowLayout@@XZ
WindowLayout *GameWindow::winGetLayout( void )
{
	return m_layout;
}

// ?winGetSize@GameWindow@@QAEHPAH0@Z
Int GameWindow::winGetSize( Int *width, Int *height )
{
	if( width == NULL || height == NULL )
		return WIN_ERR_INVALID_PARAMETER;

	*width  = m_size.x;
	*height = m_size.y;

	return WIN_ERR_OK;
}

// ?winGetScreenPosition@GameWindow@@QAEHPAH0@Z
Int GameWindow::winGetScreenPosition( Int *x, Int *y )
{
	GameWindow *parent = m_parent;

	*x = m_region.lo.x;
	*y = m_region.lo.y;

	while( parent )
	{
		*x += parent->m_region.lo.x;
		*y += parent->m_region.lo.y;
		parent = parent->m_parent;
	}

	return WIN_ERR_OK;
}

// ?winSetUserData@GameWindow@@QAEXPAX@Z
void GameWindow::winSetUserData( void *userData )
{
	m_userData = userData;
}

// ?winClearStatus@GameWindow@@QAEII@Z
UnsignedInt GameWindow::winClearStatus( UnsignedInt status )
{
	UnsignedInt oldStatus;

	oldStatus = m_status;
	BitClear( m_status, status );

	return oldStatus;
}

// ?winNextTab@GameWindow@@QAEHXZ
Int GameWindow::winNextTab( void )
{
	return WIN_ERR_OK;
}

// ?winPrevTab@GameWindow@@QAEHXZ
Int GameWindow::winPrevTab( void )
{
	return WIN_ERR_OK;
}

// ?winGetEnabledTextBorderColor@GameWindow@@QAEHXZ
Color GameWindow::winGetEnabledTextBorderColor( void )
{
	return m_instData.m_enabledText.borderColor;
}

// ?winSetEnabledTextColors@GameWindow@@QAEXHH@Z
void GameWindow::winSetEnabledTextColors( Color color, Color borderColor )
{
	m_instData.m_enabledText.color = color;
	m_instData.m_enabledText.borderColor = borderColor;

	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetEnabledTextColors( this, color, borderColor );
}

// ?winSetDisabledTextColors@GameWindow@@QAEXHH@Z
void GameWindow::winSetDisabledTextColors( Color color, Color borderColor )
{
	m_instData.m_disabledText.color = color;
	m_instData.m_disabledText.borderColor = borderColor;

	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetDisabledTextColors( this, color, borderColor );
}

// ?winSetHiliteTextColors@GameWindow@@QAEXHH@Z
void GameWindow::winSetHiliteTextColors( Color color, Color borderColor )
{
	m_instData.m_hiliteText.color = color;
	m_instData.m_hiliteText.borderColor = borderColor;

	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetHiliteTextColors( this, color, borderColor );
}

// ?winSetIMECompositeTextColors@GameWindow@@QAEXHH@Z
void GameWindow::winSetIMECompositeTextColors( Color color, Color borderColor )
{
	m_instData.m_imeCompositeText.color = color;
	m_instData.m_imeCompositeText.borderColor = borderColor;

	if( BitTest( m_instData.getStyle(), GWS_COMBO_BOX ) )
		GadgetComboBoxSetIMECompositeTextColors( this, color, borderColor );
}

// ?winSetTooltipFunc@GameWindow@@QAEHP6AXPAV1@PAVWinInstanceData@@I@Z@Z
Int GameWindow::winSetTooltipFunc( GameWinTooltipFunc tooltip )
{
	m_tooltip = tooltip;

	return WIN_ERR_OK;
}

// ?winSetEnabledImage@GameWindow@@QAEHHPBVImage@@@Z
Int GameWindow::winSetEnabledImage( Int index, const Image *image )
{
	if( index < 0 || index >= MAX_DRAW_DATA )
		return WIN_ERR_INVALID_PARAMETER;

	m_instData.m_enabledDrawData[ index ].image = image;

	return WIN_ERR_OK;
}

// ?winSetHiliteImage@GameWindow@@QAEHHPBVImage@@@Z
Int GameWindow::winSetHiliteImage( Int index, const Image *image )
{
	if( index < 0 || index >= MAX_DRAW_DATA )
		return WIN_ERR_INVALID_PARAMETER;

	m_instData.m_hiliteDrawData[ index ].image = image;

	return WIN_ERR_OK;
}

// Retail's winSetDisabledImage body ICF-folds byte-for-byte with winSetHiliteImage
// above (both thunks resolve to the identical body at 0x479120, verified via
// objdump: index math -> m_instData offset 0x130 = &m_hiliteDrawData[index].image).
// BFME never wrote a distinct disabled-image path here; write the same field so
// our object code folds the same way and matches the retail bytes.
// ?winSetDisabledImage@GameWindow@@QAEHHPBVImage@@@Z
Int GameWindow::winSetDisabledImage( Int index, const Image *image )
{
	if( index < 0 || index >= MAX_DRAW_DATA )
		return WIN_ERR_INVALID_PARAMETER;

	m_instData.m_hiliteDrawData[ index ].image = image;

	return WIN_ERR_OK;
}

// GameWindow::winSetPosition ==================================================
// Retail (0x4780d0) does not call the ZH normalizeWindowRegion() helper out of
// line -- the swap logic is inlined directly into this body, so it is written
// out here rather than as a call.
// ?winSetPosition@GameWindow@@QAEHHH@Z
Int GameWindow::winSetPosition( Int x, Int y )
{
	// BFME: notify the anchor of the old->new position before overwriting it
	if( m_bfmeAnchor )
		m_bfmeAnchor->bfme_anchor_reposition( m_region.lo.x, m_region.lo.y, x, y );

	m_region.lo.x = x;
	m_region.lo.y = y;

	m_region.hi.x = x + m_size.x;
	m_region.hi.y = y + m_size.y;

	if( m_region.lo.x > m_region.hi.x )
	{
		Int t = m_region.lo.x;
		m_region.lo.x = m_region.hi.x;
		m_region.hi.x = t;
	}

	if( m_region.lo.y > m_region.hi.y )
	{
		Int t = m_region.lo.y;
		m_region.lo.y = m_region.hi.y;
		m_region.hi.y = t;
	}

	return WIN_ERR_OK;
}

// GameWindow::winBringToTop ====================================================
// BFME uses addWindowToParentAtEnd here where ZH's commented-out line shows it
// once used addWindowToParent (retail call is [vtable+0xcc], the manager's
// addWindowToParentAtEnd slot -- see GameWindowManager.h).
// ?winBringToTop@GameWindow@@QAEHXZ
Int GameWindow::winBringToTop( void )
{
	GameWindow *current;
	GameWindow *parent = winGetParent();

	if( parent )
	{
		TheWindowManager->unlinkChildWindow( this );
		TheWindowManager->addWindowToParentAtEnd( this, parent );
	}
	else
	{
		// sanity, make sure this window is in the window list
		for( current = TheWindowManager->winGetWindowList();
				 current != this;
				 current = current->m_next)
			if (current == NULL)
				return WIN_ERR_INVALID_PARAMETER;

		// move to head of windowList
		TheWindowManager->unlinkWindow( this );
		TheWindowManager->linkWindow( this );
	}

	// if the window is part of a screen layout, move it to the top of the
	// screen layout to reflect the new position of the window in the real
	// window list
	if( m_layout )
	{
		WindowLayout *saveLayout = m_layout;

		saveLayout->removeWindow( this );
		saveLayout->addWindow( this );
	}

	return WIN_ERR_OK;
}

// GameWindow::winEnable ========================================================
// BFME adds a winGetFocus() check when disabling (clears focus if this window
// had it) and only messages the manager when m_status actually changed.
// ?winEnable@GameWindow@@QAEH_N@Z
Int GameWindow::winEnable( Bool enable )
{
	GameWindow *child;
	UnsignedInt oldStatus = m_status;

	if( enable )
		BitSet( m_status, WIN_STATUS_ENABLED );
	else
	{
		BitClear( m_status, WIN_STATUS_ENABLED );

		// BFME: if this window currently has focus and is being disabled, drop focus
		if( TheWindowManager->winGetFocus() == this )
			TheWindowManager->winSetFocus( NULL );
	}

	if( m_child )
	{
		for( child = m_child; child; child = child->m_next)
			child->winEnable( enable );
	}

	// BFME: only notify the manager if the status word actually changed
	if( m_status != oldStatus )
		TheWindowManager->winSendSystemMsg( this, 0x1c, enable, 0 );

	return WIN_ERR_OK;
}

// GameWindow::winSetSize =======================================================
// BFME body is byte-identical to ZH (same GGM_RESIZED=0x4004 enum ordering).
// ?winSetSize@GameWindow@@QAEHHH@Z
Int GameWindow::winSetSize( Int width, Int height )
{
	m_size.x = width;
	m_size.y = height;
	m_region.hi.x = m_region.lo.x + width;
	m_region.hi.y = m_region.lo.y + height;

	TheWindowManager->winSendSystemMsg( this,
																			GGM_RESIZED,
																			(WindowMsgData)width,
																			(WindowMsgData)height );

	return WIN_ERR_OK;
}

// GameWindow::winSetNextInLayout / winSetPrevInLayout / winSetLayout =========
// BFME changed these three from ZH's void return to Int: the retail body is
// 'mov eax,[esp+4]; mov [ecx+off],eax; ret 4' -- it returns the same pointer
// it was just given, reinterpreted as Int. See the shim declaration for why
// these can't just stay void.
// ?winSetNextInLayout@GameWindow@@QAEHPAV1@@Z
Int GameWindow::winSetNextInLayout( GameWindow *next )
{
	m_nextLayout = next;
	return (Int)next;
}

// ?winSetPrevInLayout@GameWindow@@QAEHPAV1@@Z
Int GameWindow::winSetPrevInLayout( GameWindow *prev )
{
	m_prevLayout = prev;
	return (Int)prev;
}

// ?winSetLayout@GameWindow@@QAEHPAVWindowLayout@@@Z
Int GameWindow::winSetLayout( WindowLayout *layout )
{
	m_layout = layout;
	return (Int)layout;
}

// GameWindow::winHide ==========================================================
// BFME-modified: messages the manager with winSendSystemMsg(this, 0x1b, !hide, 0)
// when the status actually changed, and unconditionally clears status bit
// 0x10000000 on every call (both absent from ZH).
// ?winHide@GameWindow@@QAEH_N@Z
Int GameWindow::winHide( Bool hide )
{
	UnsignedInt oldStatus = m_status;

	if( hide )
	{
		BitSet( m_status, WIN_STATUS_HIDDEN );

		// notify the window manger we are hiding
		TheWindowManager->windowHiding( this );
	}
	else
	{
		BitClear( m_status, WIN_STATUS_HIDDEN );
	}

	if( m_status != oldStatus )
		TheWindowManager->winSendSystemMsg( this, 0x1b, !hide, 0 );

	// BFME-only: unconditionally clear this status bit on every call
	m_status &= ~0x10000000;

	return WIN_ERR_OK;
}
