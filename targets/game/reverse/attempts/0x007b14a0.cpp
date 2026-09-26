// ?flushDecals@W3DProjectedShadowManager@@QAEXPAVW3DShadowTexture@@W4ShadowType@@HH@Z
// partial score=0.1 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/projectedshadow /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Partial reconstruction seed for retail 0x007B14A0.
//
// The sole named retail caller is W3DProjectedShadowManager::renderShadows.
// Its call sites pass four stack arguments, while the Zero Hour source twin
// below exposes the earlier two-argument flushDecals implementation.  Keeping
// the class-home twin compilable here preserves the verified control-flow and
// rendering skeleton without claiming the missing BFME-specific extension.
#include "W3DProjectedShadow.cpp"
