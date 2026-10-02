# RVA 0x001F7CC0 has a ClickReactionBehavior receiver

Retail PE decoding and GhidraMCP agree on the unique pointer to ILT
VA 0x0043715F at table entry VA 0x010A3198. That ILT reaches body
RVA 0x001F7CC0, whose complete extent is 208 bytes: RET 4 at +0xCD,
followed by INT3 at +0xD0.

Matched ClickReactionBehavior constructor RVA 0x001F7860 first stores
abstract three-entry table 0x010A3180 at full object+0x20 (VA 0x005F78AA).
It **replaces** that with final table 0x010A3190 at VA 0x005F78D1. The
final table's entries are ILTs to 0x001F77D0, 0x001F7B10 and our body.
The primary final table is 0x010A33CC, stored at VA 0x005F78BD.

The owner is independently established by primary slot 2: ILT 0x004311B0
reaches six-byte getter RVA 0x001F7920 returning VA 0x01090CC0, whose
retail bytes spell `ClickReactionBehavior`. Primary slot 4 reaches the
matched module-name-key getter at 0x001F7930.

Thus ECX points +0x20 into ClickReactionBehavior. The body's [ECX-0x18]
is full object+8, matching the constructor's Object receiver load. Its
[ECX+8] zero store touches the full object's +0x28 field, which the
constructor also clears. These facts retire the unproved-owner claim.

The table is not established as Snapshot: its second entry is a click
reaction condition/animation operation, and our body consumes a Boolean
argument at entry ESP+4. After clearing the six bits 154..159 and its
+0x28 counter, that Boolean controls whether the retrieved Drawable gets
applyPendingModelConditionFlags(false). The earlier zero-argument bank
and its suggested hidden-this cleanup are incorrect; RET 4 cleans the
explicit argument.

The native method name and formal interface spelling remain unresolved.
The original bank did not reproduce the redundant inline bitset initialization.
The implementation evidence below resolves that code-generation blocker while
retaining an address-qualified method name.

## Clean implementation at 208 bytes

The final source uses ClickReactionBehavior::rva001F7CC0(bool), with a
32-byte primary-prefix view and the witnessed secondary interface at +0x20.
The member body therefore receives the same adjusted receiver as retail;
Object is at full+8 and the cleared state dword is full+0x28. This is a
partial emission view, not a claim to know the original interface name.
The constructor/table/getter chain above was independently redecoded from
retail before this conversion.

Canonical Common/BitFlags.h with native STLport bitset<320> reproduces the
mask stores without hand-written copies. Default construction, then clear(),
then setting bits 154 through 159 generates the repeated stores exactly.
The state reset must precede construction of the masks in source. MSVC then
schedules its immediate zero store late, exactly as retail does at +0xA7.
Placing the reset after mask construction instead uses EAX and is four bytes
short. The corrected Boolean argument controls the final Drawable call;
RET 4 does not clean an implicit this pointer.

The canonical Object header supplies virtual getDrawable at slot 10. The
existing typed clearAndSetModelConditionFlags(BitFlags<320> const&,
BitFlags<320> const&) pin routes via ILT 0x000095ED to 0x001C7720; its source
copies the current ten-word mask and applies both incoming pointer arguments.
The existing Drawable::applyPendingModelConditionFlags(bool) pin routes via
ILT 0x0002D439 to matched body 0x0041AA90. No callee is renamed or newly pinned.
Probe reports exact 208-byte instructions with two relocations; the scoped
build verifies their targets as well.

## Bank-to-source name-check pairings

The retired bank's clearAndSetModelConditionFlags declaration was a callee
stub, not the callback's identity. The final source retains that exact callee
name through OBJECT_TU_MEMBERS and its call, using the canonical Object type.
The bank's unused08 was an anonymous filler in its Object-vtable view; the
canonical Object header replaces that whole view. Neither name became the
new callback name. The checker's alignment pairs these unrelated declarations
with rva001F7CC0 when the bank disappears. Its third pairing, method to
rva001F7CC0, simply replaces an explicitly opaque placeholder with the required
address-preserving spelling. The old bank itself disclaims lexical identity.
Snapshot-bound name_corrections entries document these three pairings.
