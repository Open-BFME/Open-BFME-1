# Rva00249250 callee declaration repair

The 142-byte caller at RVA 0x00249250 uses these direct ILT routes, checked
by `tools/callees.py 0x00249250 142` and retail disassembly:

| ILT | Body | Existing matched provider |
| --- | --- | --- |
| 0x0003F0FD | 0x00248AA0 | BfmeThingCQE::bfmeGoCQE(BfmeArgCQE*) |
| 0x00012E3B | 0x00410BA0 | Gen_00410BA0::bfmeBusy() const |
| 0x00008337 | 0x00411DD0 | Gen_00411DD0::bfmeSet(bool) |

The declarations previously named unavailable fallback, kind, and run
methods. The replacement uses existing ledger provider names and makes no
new semantic identity claim. The old BfmeRva49250AI remains a forward-declared
view returned by the virtual slot; casts at the direct call sites only
express the independently matched callee signatures. The name checker pairs
the removed declaration block with Gen_00410BA0, but this does not rename an
AI implementation or establish an AI identity for either provider.

The 29-byte bfmeBusy body reads bytes +0x3AD and +0x3AE, returns zero if both
are zero, otherwise one. Retail caller 0x002492B4 compares AL with one, so an
explicit char conversion preserves that consumption of the int result.
The 26-byte bfmeSet body reads the low byte of its stack argument, stores it
at +0x3AD if changed, calls its existing notification helper, and returns
with ret 4. Passing false matches the caller's push 0. The fallback body
accepts one object pointer with the unchanged primary this pointer.

The corrected caller passes its exact scoped byte comparison, including
its 142-byte extent through ret 8. No providers, ledger rows, or pins change.
