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
Existing mask callees have competing synthetic/template declarations, and
the bank does not reproduce retail's redundant inline bitset initialization.
This is owner/ABI evidence only; no source, pin or identity rename lands.
