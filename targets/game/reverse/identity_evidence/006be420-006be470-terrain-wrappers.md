# Two opaque terrain-table forwarding entries

Retail PE and Ghidra memory agree on both complete entries and their padding.
Table VA0111D090 slot23 at0111D0EC holds00434658, whose five-byte ILT
route targets006BE420. Slot1 at0111D094 holds00423DD5, routing006BE470.
Constructor006BE070 installs this table at006BE083; destructor006BE0C0
restores it at its entry. These are entry/receiver witnesses, not proof of
original owner or method spelling. Both entries retain address-qualified names.

006BE420 is11 bytes: MOV ECX,[012F7FE0]; E9 to ILT0001A587 ->006C6F60,
then five INT3 bytes. The canonical BaseHeightMap header declares the existing
TheTerrainRenderObject global at this VA. Existing native provider
Gen_006C6F60Terrain::query(float,float) has117 bytes and RET8 at006C6FD2;
its map and coordinate computation establish the two floating arguments and
bool result. The wrapper retains that existing callee identity and forwards
both incoming arguments unchanged. No new pin is needed.

006BE470 is five bytes: E9 to ILT00032AC9 ->001AB150, then eleven INT3
bytes. The existing135-byte TerrainLogic::deleteBridges provider uses ECX
and ends in plain RET at001AB1D6. The canonical TerrainLogic header supplies
its protected declaration. A TU-local address-qualified derived view permits
this call without redeclaring the covered class or changing its header; it
introduces no field or original owner-name claim. Receiver and no-argument
ABI are unchanged. This is not claimed as TerrainLogic::init or
W3DTerrainLogic::init: those have distinct existing entries.

callees.py was run for both complete extents; its E8-only output omits these
E9 tail calls, which were independently decoded. Both scratch probes matched
and production verification resolves the existing global/callee references.
