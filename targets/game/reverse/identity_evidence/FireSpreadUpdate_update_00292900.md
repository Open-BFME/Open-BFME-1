# FireSpreadUpdate::update — RVA 0x00292900

## Identity and extent

The Zero Hour twin is `FireSpreadUpdate::update` in
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FireSpreadUpdate.cpp`.
It checks the owning object's aflame status, creates the configured embers OCL,
queries for a flammable object, finds `FlammableUpdate`, calls `tryToIgnite`, and
returns the next spread delay. BFME preserves this distinctive sequence and the
`FlammableUpdate` literal at VA 0x010905D0. Its constructor at RVA 0x002926C0,
filter `allow` at 0x002925C0, delay method at 0x00292840, and start method at
0x00292AF0 are already byte-matched from the same owning TU.

The unpacked retail image has the entry at 0x00292900, the final `ret` at
0x00292A81, and INT3 padding from 0x00292A82. The extent is 386 bytes. The
receiver is the update-interface subobject: object and module-data pointers
are loaded at incoming ECX-8 and ECX-12. The native TU's existing inheritance
layout reproduces these accesses without another class declaration.

## BFME changes recovered from the bytes

- Object+0x90 bit 0x400 gates the body. Module-data+8 supplies the OCL and
  module-data+0x14 supplies the radius; the native module-data declaration
  already has these offsets.
- The temporary filter has a vptr at +0 and a null link at +4. Its constructor
  writes VA 0x010BE9EC (`PartitionFilterFlammable`); destruction restores
  0x01083B5C (`PartitionFilter`). The destructor runs immediately after the
  closest-object query. This is a linked filter node, not the ZH pointer array.
  An address-derived view preserves this lifetime and both existing table
  symbols without changing the shared ZH filter header.
- The closest-object query receives Object+0x38, radius bits, 2, and the filter
  head. If it returns null, the body tests the byte at
  `(*((char **)TheAI + 5))+0xB8`. No behavioral name is assigned to that byte.
- The fallback queries terrain using position, radius, 1, and 0, then passes
  the returned position to the helper at 0x001AA5B0. Passing the already-null
  object result as the final zero preserves retail's `push esi`.
- The local static name key and its exception state remain native C++. The
  delay method inlines its original file/line-bearing random call at line 152.

## Callees and the one dependency repair

`tools/callees.py 0x00292900 386` was run before reconstruction. Every target
below was cross-checked against bytes from the unpacked retail executable.

| Retail target | Binding and evidence |
| --- | --- |
| ILT 0x000160D1 → 0x001D6810 | Existing `j_000160d1` symbol. The matched OCL body walks elements, calls their creation slot, returns void, and pops three arguments. ZH's header returns Object*, so a TU-local single-inheritance member-pointer binding uses the proven BFME ABI without redeclaring the header's class or adding an alias pin. |
| 0x009F26A0 | Existing `BfmeC1050::bfmeGo1050D`: 33-byte wrapper, ECX receiver, four stack slots, returned pointer in EAX, `ret 16`; inserts a null optional argument before forwarding through its inner manager at +0xC. |
| ILT 0x000226AB → 0x001A62D0 | Existing `BfmeA1275::bfmeGo1275`: 58-byte wrapper initializes a 24-byte result, forwards the four input slots and result address, returns the result pointer at +0x14, and executes `ret 16`. |
| ILT 0x00034CA2 → 0x001AA5B0 | New address-derived `Rva001AA5B0Receiver::invoke(const Coord3D*)` pin, anchored at the real body. Independent 367-byte decode: ECX is the terrain receiver; its single stack argument is forwarded as the position to ILT 0x00023448. One path returns the Object produced through ILT 0x0004494A in EAX; another returns the closest-object query result. Both exits use `ret 4`. The caller uses the result as the receiver of the proven Object module lookup. No semantic method name is claimed. |
| ILT 0x0003ADD7 → 0x0008FFC0 | Existing NameKeyGenerator::nameToKey binding and the narrow `FlammableUpdate` literal. |
| ILT 0x0002AE23 → 0x001BEE60 | Native inline findUpdateModule reaches the existing Object::findModule binding; the 63-byte body walks the module array at +0x1F0 and compares each module's name key. |
| ILT 0x000322D6 → 0x00293990 | Existing FlammableUpdate::tryToIgnite row; result unused. |
| ILT 0x00001BAE → 0x00096CF0 | Existing GetGameLogicRandomValue binding with retail file literal and line 0x98. |

The scoped gate verifies 7/7 functions in the owning TU, five string literals,
one float constant, and 13 DIR32 references. The single new real-body pin
passes `pin_consistency.py --check`. The existing cleanup rows at RVA
0x00C11A00 and 0x00C11A68 were repinned with `eh_state_pins.py --fix` using the
retail parent unwind states; their bodies were byte-verified. No baseline,
shared header, or generated source is changed.
