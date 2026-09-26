// WindowLayout.h -- TU-scoped BFME shadow shim (see GameWindowFields.cpp).
//
// ZH's WindowLayout keeps addWindow()/removeWindow() as plain non-virtual
// members (reference/.../GameClient/WindowLayout.h). Retail winBringToTop
// (0x4794f0) dispatches both through m_layout's OWN vtable at this+0x18 (add)
// and this+0x1c (remove) -- proof: `mov eax,[edi]; ...; call [eax+0x1c]` then
// `mov edx,[edi]; ...; call [edx+0x18]` right after `mov edi,[esi+0x210]`
// (m_layout). Six dummy slots land the two real methods at those offsets,
// matching ZH's declared order (addWindow before removeWindow). The real BFME
// WindowLayout shape beyond that is unidentified -- this shim exists only to
// unblock winBringToTop, not to give WindowLayout a byte-correct BFME layout.
// Only this TU sees it (private /Ireference/shims/gamewindow wins the quoted
// "GameClient/WindowLayout.h" include pulled in by GameWindowManager.h).
#pragma once

#ifndef __WINDOWLAYOUT_H_
#define __WINDOWLAYOUT_H_

#include "GameClient/GameWindow.h"

class GameWindow;
class WindowLayout;

typedef void (*WindowLayoutInitFunc)( WindowLayout *layout, void *userData );
typedef void (*WindowLayoutUpdateFunc)( WindowLayout *layout, void *userData );
typedef void (*WindowLayoutShutdownFunc)( WindowLayout *layout, void *userData );

class WindowLayout
{
public:
	virtual ~WindowLayout( void ) { }
	virtual void bfme_wl_1( void ) { }
	virtual void bfme_wl_2( void ) { }
	virtual void bfme_wl_3( void ) { }
	virtual void bfme_wl_4( void ) { }
	virtual void bfme_wl_5( void ) { }
	virtual void addWindow( GameWindow *window ) { }		// @+0x18
	virtual void removeWindow( GameWindow *window ) { }	// @+0x1c
};

#endif // __WINDOWLAYOUT_H_
