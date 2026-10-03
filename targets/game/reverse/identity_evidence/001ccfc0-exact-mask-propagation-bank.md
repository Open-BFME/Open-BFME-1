# RVA 0x001CCFC0 exact propagation bank

Native extent is 332 bytes: RET4 at +0x149, INT3 at +0x14C. ILT 0x275B1
routes to this body. Earlier scans found no caller or table entry naming it;
retain an opaque address identity. The receiver uses the independently
established Object layout (+4 template, +0x1FC contain, +0x214 container),
but neither that nor a byte match proves an original wrapper method name.

The template override walker is native 0x87A80, and parent test is native
Thing::isKindOf at 0xA2CF0 with ordinal 0x6C. Template word +0xD4 bit0x1000
chooses the receiver directly; otherwise the tested parent is selected.
Interface calls use slot +0x68 then +0xEC. No semantic name for those two
interfaces is asserted by this bank: both use address-qualified ABI views.

The list copy at 0x1CB160 is 111 bytes, RET4, allocating a 12-byte sentinel,
self-linking next/prev then copying the source range. Its existing symbols
include a conflicting generated pair-copy pin; do not silently reuse that
identity. Native destructor 0xCEBD0 frees 12-byte nodes with no payload
cleanup. EH cleanup 0xC09230 addresses the list at EBP-0x38 and jumps via
0x418949 to 0xD0020, itself a jump through ILT0xE68D to 0xCEBD0.
Thus list<Object*> is a viable shape, but its generated provider bindings
still need coordinated identity/ABI reconciliation before production.

Each item receives caller clear mask and an all-zero 40-byte set mask through
0x1C7720. The selected receiver gets the same update after the list loop.
A bitset-backed mask with separate lexical scopes reuses the native stack
slot; explicitly load the item pointer BEFORE creating its zero mask.
This changes the first probe (332B /54 differing nonrelocation bytes) to
332B EXACT modulo10 relocations. The bitset is solely forty-byte zeroed
storage here; no total semantic model-condition count is inferred.

The final bank intentionally uses only opaque, address-qualified ABI views
for covered game types, not competing Object/Thing/Overridable/BitFlags
class declarations. It is not production source and its helper/vtable/list
bindings are unvalidated. A landing must adopt canonical headers and resolve
list-copy/deletion and the current BitFlags<320> versus historical304 update
signatures. No new helper pin or conversion row is added by this bank.
