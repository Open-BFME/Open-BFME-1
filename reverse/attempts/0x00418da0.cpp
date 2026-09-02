// ??0Drawable@@QAE@PBVThingTemplate@@W4DrawableStatus@@@Z
// partial score=0.3 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/shims/locomotor /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// Focused conversion witness for retail RVA 0x00418DA0. The complete clean
// constructor is already authored in Drawable.cpp; including it preserves the
// compilable MSVC 7.1 body while the BFME-only layout and control-flow deltas
// are reconstructed. Retail evidence identifies this as Drawable::Drawable:
// it installs the Drawable and Thing vtables, initializes Drawable's module
// arrays and envelopes, filters draw modules through TheGameLODManager, calls
// onObjectCreated, initializes static images, and is followed by its destructor.
#include "../../Code/GameEngine/Source/GameClient/Drawable.cpp"
