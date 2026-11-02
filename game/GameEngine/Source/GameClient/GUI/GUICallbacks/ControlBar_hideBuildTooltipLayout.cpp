// cl: /DNDEBUG /MD /EHsc

// The popup's animation switch at VA 0x012F3690 (Zero Hour's useAnimation in
// GUICallbacks/ControlBarPopupDescription.cpp). The popup bodies that read it,
// including ControlBar::hideBuildTooltipLayout, live in
// ControlBarPopupDescription.cpp; this unit keeps the data row's definition.

typedef bool Bool;

Bool g_bfmeReadyPT;                                          // 0x012F3690
