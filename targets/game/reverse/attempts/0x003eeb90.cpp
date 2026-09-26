// ?d_003eeb90@@YAXXZ
// partial score=0.55 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/terrainlogic /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Partial reconstruction seed for retail RVA 0x003EEB90.
//
// Identity evidence:
// - matched callers findGroundPath (0x003F2160), findPath (0x003F2F60), and
//   findClosestPath (0x003F3460) all call the thunk at 0x001FA14;
// - each caller pushes seven arguments;
// - retail returns with `ret 0x1c`;
// - argument order is Bool isHuman, LocomotorSurfaceTypeMask, Object *obj,
//   const Coord3D *from, const Coord3D *rawTo, Bool crusher, Bool closestOK.
//
// The Zero Hour twin below has the same control-flow skeleton but lacks BFME's
// Object argument and BFME-specific hierarchical-path logic.  Compiling its
// internal_findHierarchicalPath body and probing it at 0x003EEB90 gives 3427B
// versus retail's 4836B, with the common prologue through +0x08 and the first
// semantic divergence caused by rawTo moving from [ebp+0x14] to [ebp+0x18].
// This include is a handoff seed, not a landable translation unit: the next
// worker should extract only internal_findHierarchicalPath, add the Object
// parameter to a TU-scoped Pathfinder declaration, then iterate from +0x08.

#include "AIPathfind.cpp"
