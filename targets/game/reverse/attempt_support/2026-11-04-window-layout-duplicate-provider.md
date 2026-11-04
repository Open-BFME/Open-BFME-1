# Remove the obsolete layout factory while preserving placement delete

Queue #46: winCreateLayout, claim F6127D2F. Census 77a8439ee4 reports
GameWindowManager_winCreateLayout_Thunk.cpp duplicate/selected, 0 -> 0
linked bytes. The real 257-byte factory is already recovered there at
0x004889A0: load WindowLayoutInfo, optionally call its stdcall creation
callback with a catch-all handler, otherwise allocate and attach a layout.
The old GameWindowManagerScript.cpp Zero Hour body instead allocates first
and calls WindowLayout::load. It has no matched row and is the wrong strong
provider. Remove it, keeping the verified native factory.

Initial removal exposed the independently matched placement-delete row
0x007EFFF0/12B: the old allocation was its only emission context. The existing
TU-local pool macro now declares placement delete out of line, and an explicit
WindowLayout::operator delete definition keeps the same BfmePoolGlue::free call.
This follows the already-used NetCommandWrapperList.cpp ownership pattern.
callees.py confirms its only callee, the CRT free import thunk at 0x009F6C3A.
No synthetic caller, retention anchor, alias, pin or header change was added.

Normal scoped verification of both units passes 32/32, 116 string references,
43 DIR32 references and body guards. find_declared_unmatched passes. A private
compile of the previous GameWindowManagerScript source, compared with the
final normal object using object_facts, proves zero new undefined names,
no old factory definition, and the preserved placement-delete definition.
The native factory has zero masked byte differences over its full 257B;
RetailTruth is UNKNOWN, rather than retail, for unresolved identity evidence.
A bounded current link preview is UNKNOWN because the pre-existing BFME 2
checkout differs from staged inputs; the full current dependency census is also
unavailable. No newly linked bytes are claimed without a fresh census.

BFME 2 donor c8b988aae8f06e96b73717239e0bb8f1e7ec23d4:
Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp already removes
the old factory and points to Rva0031763ACtorDtorAssign.cpp. This corroborates
the ownership repair; donor addresses, flags and layout are not imported.
BFME 1's ledger, existing source and scoped verification establish the retained
provider and placement-delete bytes independently. Code maps to local game.
