# Drawable::handleWeaponFireFX at RVA 0x00411730

The former name ended `MMMPBUCoord3D@@M@Z` (eight stack arguments).
The corrected name ends `MMMPBUCoord3D@@@Z` (seven stack arguments).
Only the final damageRadius argument is removed; owner and operation are retained.

Retail evidence from the current retail-1.03-unpacked baseline:

* Start 0x00411730 is the existing body start. The old 23-byte claim ended
  after `test ah,0x44` at 0x00411744, before its conditional branch.
* Two complete exits, at 0x004117F4 and 0x004117FD, both encode `C2 1C 00`.
  Seven 4-byte stack arguments are popped. The last RET ends at 0x00411800;
  64 int3 bytes separate it from the next proven start 0x00411840.
* Recoil reads the fifth and sixth stack arguments. The module loop loads
  arguments seven, four, three, two, one and calls interface vslot +0x54.
  There is no eighth argument read or passed.
* The existing reference function in Drawable.cpp gives the same distinctive
  operation: recoil direction relative to Object orientation, add PI, Cos/Sin
  acceleration updates, then first-success draw-module dispatch.
* name_oracle witnesses Drawable+0xFC as m_object and +0x138 as m_locoInfo.
  Retail loads module pointers from +0x150 and calls module vslot +0x9C.
  The new TU keeps unknown helper types and slots address-derived.
* The corrected seven-argument body compiles to all 208 retail bytes modulo
  relocation slots. add_match additionally verifies calls to Cos/Sin, the
  PI constant, absolute references, and exact bytes.

No new semantic function identity is inferred from matching bytes. This is
an arity correction to the supplied existing identity, supported by both
return instructions and the argument forwarding sequence. The reference
header has the Zero Hour eight-argument signature, so the BFME declaration
is kept TU-local without modifying that shared header.
