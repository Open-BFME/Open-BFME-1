# STLport callback registration, BFME 1 retail 1.03

## Independent BFME 1 identity, extent and ABI

The existing iword/pword siblings at 0x0083F0C0 and 0x0083F140 establish
this STLport ios_base cluster. The canonical BFME 1 vendored declaration,
inputs/vendor/stlport/stl/_ios_base.h, declares register_callback(event_callback,
int), with event_callback = void (*)(event, ios_base &, int). Its callback
storage is pair<event_callback, int>*, followed by capacity and next index.
Retail 0x0083F1C0 loads these three fields at +0x24/+0x28/+0x2C, grows that
array, writes the supplied function and integer as one eight-byte element,
and increments the next index. This combination establishes register_callback,
not merely a same-size donor placement. Failure sets iostate +0x08 and tests
exception mask +0x14, just as the two independently recovered word wrappers.
The native vendor layout and every access in all three wrappers agree.

The complete 132-byte body starts at 0x0083F1C0, ends with RET 8 at +0x81,
and is followed by INT3 at +0x84. The grow helper starts at 0x0083EF20 and
has a complete 147-byte extent ending before its alignment padding. These
are the existing scaffold/helper extents, independently inspected with
callees.py and dis_retail.py. The callback's only direct relative call is
0x0083EF20; it also calls MSVCR71.dll!fputs through IAT VA 0x013593C8.
The helper calls MSVCR71.dll!realloc through IAT VA 0x01359474.

The callback pushes index, capacity, array, and a stack result address,
then cleans 16 bytes. The helper returns that result address in EAX and
writes pointer/count into the result. Returning the actual non-POD STLport
pair from a three-argument C++ helper expresses this hidden-result ABI.
The former explicit-output signature was machine-compatible, but its
invented Callback type used void (*)(int, void *, int) rather than the
vendor callback signature, and its GrowPair was a private POD surrogate.
Neither surrogate nor the original grow_array spelling is independently
established as a retail C++ identity. Retire that claim rather than adding
a second identity at the same address. The replacement retains the address
in its spelling and uses the real vendor types:

Old: `??$grow_array@UCallback@_STL@@@_STL@@YAPAU?$GrowPair@UCallback@_STL@@@0@PAU10@PAUCallback@0@II@Z`

New: `??$rva0083EF20@U?$pair@P6AXW4event@ios_base@_STL@@AAV23@H@ZH@_STL@@@_STL@@YA?AU?$pair@PAU?$pair@P6AXW4event@ios_base@_STL@@AAV23@H@ZH@_STL@@I@0@PAU?$pair@P6AXW4event@ios_base@_STL@@AAV23@H@ZH@0@II@Z`

No other game source calls the old callback helper; the long/void* grow
specializations remain unchanged in game/stlport/IosBaseWordArrayGrow.cpp.
The old callback-helper source is retired after its row moves to the
existing official ios_base home. No alias, new pin, or second body owner
is introduced. Existing fallback globals g_0130BD24/g_0130BD28 are preserved.

## BFME 2 evidence and explicit translation

Read-only donor checkout: /work8/Open-BFME-2, revision
e2fdc5620c5834c1c98de24aa3510d72e2cbcc69. Reviewed donor commits
1e726cf7cf299ff126c390e7dbed212200903c24 and
24cfd001e1d3b8b67e5f892dd9ebc9627bd35fe5, source
Code/Libraries/Source/WWVegas/WWLib/stlport_ios_base_iword.cpp, and
reverse/attempt_support/ios-callback-local-count-20261021/readme.md.
The donor source materially supplies the native pair return and caller
shape; it is credited in the commit. Its register_callback RVA 0x0001C090
is a unique relocation-aware 132-byte twin, a discovery lead rather than
identity proof. Donor addresses are not imported.

Code/ maps to BFME 1 game/ at the same official path. Donor reverse/
records map only conceptually to targets/game/reverse/. The private
compile receipt confirms actual headers from BFME 1 inputs/vendor/stlport
and its own VS2003 toolchain. Source flags /MD /G6 /Ob1 augment normal
/O2 /GR- /EHsc-; _STLP_USE_STATIC_LIB and _STLP_NO_EXCEPTIONS match the
donor context. No donor compiler, nested reference, or shared header edit
is used. BFME 1 fallback symbols replace the donor's local statics.

Ruled out: donor's ICF helper alias, since BFME 1 has one identity per
body; its explicit-output surrogate, since prior BFME 1 attempts differed
at callback offsets +0x66/+0x6C/+0x6E (ECX instead of retail EDX in the
stderr tail). Isolated BFME 1 compilation with the real pair return gives
zero byte differences and no unresolved relative calls for 132/147/117/117
bytes, before normal admission. This observation supports the compiler
representation; it does not recover the original helper spelling.

Normal add_match/build and commit-hook results are authoritative. The
new recovery contributes 132 unique C++ bytes; rehoming the already clean
147-byte helper contributes zero additional bytes. Linking remains unknown
without a complete current census index and is not claimed as progress.
