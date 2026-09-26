// ?d_0073e050@@YAXXZ
// partial score=0.3 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Partial reconstruction seed for retail RVA 0x0073E050.
//
// Identity evidence: the body reads W3DDisplay::m_3DScene, calls
// W3DShaderManager::filterPreRender/filterPostRender, switches the scene pass,
// clears the render target, and uses W3DView fields +0x08/+0x10/+0x14/+0x18.
// This uniquely matches W3DView::draw in the Zero Hour twin.
//
// Probe of the readable twin: ours=1831B retail=5126B, 1527 non-relocation
// byte differences, first at +0x06.  Retail has a 0x120-byte frame with no SEH
// setup; the current twin has a 0x1bc-byte frame plus EH for local render-info
// objects.  Extract draw only and remove/reshape non-trivial locals first.

#include "W3DView.cpp"
