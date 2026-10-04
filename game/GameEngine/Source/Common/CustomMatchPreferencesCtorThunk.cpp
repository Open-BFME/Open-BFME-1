// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWLib
// stlport
//
// The retail ILT at 0x0000B0F5 jumps straight to the matched
// CustomMatchPreferences constructor at 0x000AB7F0, and its caller already
// holds the object in ECX, so the ILT is a bare five-byte tail jump that
// forwards `this`.  MSVC emits the same five bytes for a placement
// construction on a pointer it knows is non-null (`__assume`), which is why
// this body needs no linker alias:
//   __assume(this != 0);            -- drops the `test ecx,ecx / jz` guard
//   new (this) CustomMatchPreferences();  -- the discarded result makes the
//                                         ctor call a tail jump
// /EHs-c- is the one shape lever here: with synchronous EH enabled the
// compiler wraps the placement new in a SEH filter (`push -1 / push handler`)
// that would call ~CustomMatchPreferences if the constructor threw.  Retail's
// hand-emitted ILT has no such frame, and a five-byte jump cannot express one,
// so this translation unit compiles without C++ EH.  The rest of the base
// flags (including -EHsc-) are unchanged and apply to every other TU.

#include "PreRTS.h"

#include "Common/CustomMatchPreferences.h"

class CustomMatchPreferencesCtorThunk
{
public:
	void forward();
};

// ?forward@CustomMatchPreferencesCtorThunk@@QAEXXZ
void CustomMatchPreferencesCtorThunk::forward()
{
	__assume(this != 0);
	new (this) CustomMatchPreferences();
}
