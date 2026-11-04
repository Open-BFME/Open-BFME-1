# Terrain-update forwarding shim: remove a false provider

Queue46 claim FA1ED7FF. HeightMapRenderObjClassRva006D2000.cpp contains an
inline forwarding convenience named W3DTerrainBackground::rva0072D210.
Its body is not the1920-byte retail terrain update: it binds the existing
?d_0072d210@@YAXXZ provider through a member-function-pointer view. MSVC also
emits this convenience as a standalone COMDAT under the typed body's pinned
name, causing the queued wrong-provider verdict. Suppress only that emitted
copy using the already measured dllimport __forceinline technique. All
existing inline calls retain the complete242-byte consumer exactly.

Normal consumer gate passes1/1 with5 DIR32 references and1 float constant.
COFF no longer defines/references the typed rva0072D210 symbol and creates
no import of it; it still references the original dump provider. The only
import reference is existing Sleep. Existing retail1920-byte dump provider
was checked separately through the normal build; this is linking hygiene,
not recovery or conversion of that body.

callees.py006D2000/242 witnesses ILT000324D4->0072D210, thiscall with four
stack slots. Existing target pin evidence and matched sibling region callers
establish region/map/two bool ABI; no identity, layout or pin change.
Related-unit sweep: HeightMapRenderObjClass_doPartialUpdate.cpp uses a
file-static uniquely named forwarder; W3DTerrainBackgroundRva0072DC30.cpp
and W3DTerrainBackgroundRva0072E150.cpp only declare the typed member.
They do not emit this competing wrapper and need no identical edit.

Donor latest reviewed a9286edec5374324e40c1f5dd29c3a8ab5582283:
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainBackground.cpp
and W3DTerrainBackgroundDoPartialUpdate.cpp. The latter is a clean1869-byte
four-argument implementation, a future reconstruction lead for the BFME1
1920-byte body; its flags /O1 /G7 /arch:SSE and BFME2 offsets cannot simply
replace this BFME1 target. Existing local shape_levers.md documents the BFME2
inline-suppression technique; current BFME1 calls/bytes prove this use.
No donor includes or cached trials were used. Verified build donor remains
59e3f8f825; latest was read from the separate donor-latest tree.

Before link_check: wrong helper COMDAT under typed retail name. After:
selection unknown against stale Oct19 census; no linked bytes claimed.
