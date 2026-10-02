// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// FILE: AptPalantir.cpp -- data only.
//
// The AptPalantir window index the class's own TU owns, per EA's convention
// (`GameClient *TheGameClient = NULL;` in GameClient.cpp:210). Retail links
// the definition into whichever object holds it, so the image has no symbol
// for it; only the spelling, the type and the address are proven.
//
// Identity (build/report_0x012F7048.md, section "0x012B7D80 -- AptPalantir
// window index"): no EA name exists, so the descriptive spelling the
// referencing files already use is kept -- `extern int g_aptPalantirWindow;`
// in AptPalantirRegisterCallbacks.cpp:126 (and in BfmeConv2003/2005/2006.cpp,
// BfmeConv2004.cpp, AptPalantirOnButtonAlert.cpp,
// AptPalantirOnInitialized.cpp). Nothing is respelled here.
//
// Type `int`, not a pointer: the baseline's initial value at RVA 0x0EB7D80 is
// 0xFFFFFFFF, which refutes every pointer spelling. Semantics: 0x012B7D80 is
// `TheWindowManager->vslot15()` compared against -1 (the one store, RVA
// 0x00565FA3, in the Apt window loader that AptPalantirRegisterCallbacks.cpp
// :160-162 reproduces as `loadAptWindow("Apt\\", ..., 0, 0, -1)`), and 78
// loads all push it as the first stack argument of
// `?bfmeBuildAN@BfmeLevelAN@@QAEPADIHHHHHHH@Z` with an Apt script function
// name as the second. The -1 initial value puts it in .data, not .bss.

typedef int Int;

Int g_aptPalantirWindow = -1;