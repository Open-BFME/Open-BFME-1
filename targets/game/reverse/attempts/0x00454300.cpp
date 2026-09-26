// ?resetMap@@YAXXZ
// partial score=0.70 date=2026-09-22
// NOT a standalone opaque candidate: the real body already lives at
// Code/GameEngine/Source/GameClient/MapUtil.cpp, static void resetMap(void),
// lines ~298-313 (compiles as-is in that file today, committed, no local
// diff pending). This note documents how close it is and exactly what is
// missing so the next attempt does not re-derive it from scratch.
//
// PROOF the file/function is right: the ZH twin at
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/MapUtil.cpp:281-296
// is byte-identical in shape for the m_data/m_waypoints half; BFME's added
// m_techPositions/m_supplyPositions (Coord3DList = std::list<Coord3D>, real
// project typedef, see MapUtil.h) drain via plain .clear() calls already
// written in Code/. Probing that exact file+symbol against 0x00454300 with
// `python3 tools/probe.py Code/GameEngine/Source/GameClient/MapUtil.cpp
// "?resetMap@@YAXXZ" 0x00454300 --size 164` gives ours=162 retail=164,
// 44 non-reloc diff bytes, FIRST DIVERGENCE AT +0x75 -- i.e. the entire
// m_data/m_waypoints half (bytes 0..0x74) is BYTE-EXACT already, including
// the two delete/delete[] call targets (0x42dbf0, 0x42dbb0).
//
// THE RESIDUE (all 44 bytes, both list-clear blocks identically):
// Retail's node-free call is the raw 2-argument static
//   ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z(ptr, 0x14)
// (`push 0x14; push eax; call; add esp,8`), matching the ALREADY-LANDED
// 0x0025EB90 sibling's ids.clear() shape exactly (see
// Code/GameEngine/Source/GameLogic/Object/Update/Rva0025EB90*.cpp history).
// Our compiled Coord3DList::clear() -> _List_base::clear() ->
// allocator<_List_node<Coord3D>>::deallocate(p,1) [vendor/stlport/stl/_alloc.h:358]
// -> __sgi_alloc::deallocate(p,20) [_alloc.h:253, branches on __n>128] ->
// _M_deallocate(p,20) [_alloc.h:241, PRIVATE] does NOT fully inline in this
// translation unit the way it apparently does for the isolated 0x0025EB90
// file: it stops one layer short and calls an OUTLINED 1-argument helper
// (`push eax; call; add esp,4`) that must have the byte size baked in
// internally instead of passed on the stack. Net effect: one call argument
// and one stack-cleanup byte short per list, x2 lists, = the 44 bytes.
//
// TRIED AND REJECTED (all reproduced the SAME 44-byte residue, or worse):
//  - #pragma inline_depth(255) around the two .clear() calls: no change.
//  - Manual node-walk calling __node_alloc<true,0>::deallocate() (the PUBLIC
//    wrapper with the size>128 branch) instead of .clear(): compiles, but
//    the extra branch/call shape needs an extra register (edi) that isn't
//    needed anywhere else in the function, and MSVC reallocates registers
//    for the WHOLE function as a result -- the previously-exact 0..0x74
//    bytes regress too (73 diff bytes, first divergence at +5).
//  - Manual node-walk calling _M_deallocate directly via an
//    extern+`#pragma comment(linker,"/alternatename:...")` alias (bypassing
//    the private-access error the direct call gives -- vendor/stlport/stl/
//    _alloc.h:241 is private): same whole-function register-allocation
//    ripple as above, same 73-byte regression, regardless of whether the
//    node-list head is cached in a local or re-read through a macro each use.
// NEXT LEVER TO TRY: something that makes MSVC 7.1 finish inlining
// allocator<>::deallocate -> __sgi_alloc::deallocate -> _M_deallocate as ONE
// call without adding a live register anywhere else in resetMap(); the
// eh_levers.py / shape_family_levers.py `frame`/`register` families found
// nothing automatically (no explicit adjacent local-decl pair to swap, no EH
// frame on this body). A `__forceinline`-shadowed private copy of the three
// allocator layers declared ahead of Coord3DList's use, or building with a
// slightly different _STLP_* define local to just this TU section, are both
// unexplored. t=28min model=claude-sonnet-5 score=0.70 (was 0.35)
