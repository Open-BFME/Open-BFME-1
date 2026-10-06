# BfmeConv985.cpp: the window-manager call is ?apply@Rva00465B80@@QAEXXZ

`BfmeA985::bfmeGo985A` (0x00569340) and `bfmeGo985B` (0x005693C0) called the
window manager at 0x012F19E8 through a TU-local view
`BfmeHub985::bfmeDo985()`, a name nothing defines (link census 56ab264495:
unresolved).

`tools/callees.py` on both bodies gives `0x290d2 -> 0x465b80`, the same ILT
and target as the four callers corrected in
`000290d2-window-manager-call-is-rva00465b80-apply.md`: retail 0x00465B80 is
`mov byte ptr [ecx+0x1AC], 1; ret`, matched as `?apply@Rva00465B80@@QAEXXZ`
(TinyByteFieldSetters.cpp): thiscall, no arguments, the same ABI as the old
view. The callers now declare and call `Rva00465B80::apply()`; both bodies
still match (3/3 rows in the TU).

`BfmeHub985`/`bfmeDo985` were per-file placeholder spellings of that call,
not an identity of the body.

The same file's `BfmeC985::bfmeGo985C` (0x001DCCC0) calls ILT 0x000077B6 ->
0x001C5A30 (`?affectedByUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z`,
ObjectUpgrades.cpp) and ILT 0x0000BA37 -> 0x001C9F50
(`?hasUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z`, Object.cpp); those calls
are respelled to the matched Object members in the same change.
