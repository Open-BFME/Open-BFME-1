// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Include /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include
// DX8Wrapper's inline native state setter and its RenderStateStruct assignment
// carry the reference counts and only copy enabled lights.
#include "dx8wrapper.h"

void (*BfmeSetRenderStateAnchor)(const RenderStateStruct &) =
	&DX8Wrapper::Set_Render_State;
