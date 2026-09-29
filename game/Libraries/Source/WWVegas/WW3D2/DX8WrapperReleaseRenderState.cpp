// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// DX8Wrapper::Release_Render_State at 0x00903520 (192 B): the header inline
// from dx8wrapper.h, emitted out of line in the DX8Wrapper block. Retail
// releases the index buffer's and both vertex buffers' engine refs, then each
// held ref, and nulls a pointer only when it held one: BFME's REF_PTR_RELEASE
// clears inside the test, where the Zero Hour macro stores NULL
// unconditionally. With that macro the reference header reproduces all 192
// bytes. SortingRendererClass::Flush inlines the same body
// (sortingrenderer.cpp).
//
// The inline is __forceinline, so only an address reference makes VC7.1 emit
// a standalone copy; g_bfmeReleaseRenderStateKeep is that reference and has
// no retail counterpart.
#define Matrix4x4 Matrix4  // BFME renamed it
#include "refcount.h"
#undef REF_PTR_RELEASE
#define REF_PTR_RELEASE(x)		{ if (x) { x->Release_Ref(); x = NULL; } }
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "dx8wrapper.h"
#include "vertmaterial.h"
#include "texture.h"

// ?Release_Render_State@DX8Wrapper@@SAXXZ
void (*g_bfmeReleaseRenderStateKeep)() = &DX8Wrapper::Release_Render_State;
