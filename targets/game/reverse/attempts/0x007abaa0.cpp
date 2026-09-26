// ?render@WaterTracksObj@@QAEHPAVDX8VertexBufferClass@@H@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// WaterTracksObj::render at retail 0x007ABAA0.
// Identity review: the matched WaterTracksRenderSystem::flush ILT caller supplies the exact render signature; the matched constructor, scalar deleting destructor, layout witness, and Zero Hour twin confirm WaterTracksObj ownership.
// The canonical in-tree body is semantically complete and emits 2192 bytes,
// but retail uses a 0x88-byte local frame while MSVC 7.1 coalesces it to 0x30.
// Keep the whole BFME source unit available to the next probe iteration.
#include "../../Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp"
