# ILT 0x000290D2 is the matched ?apply@Rva00465B80@@QAEXXZ

Four matched callers invoked the window manager at 0x012F19E8 through a
TU-local view `BfmeGlobal_012f19e8::bfmeCall_000290d2()`, a name that only
spelled the ILT address; nothing defines it (link census: unresolved,
pinned-elsewhere at 0x000290D2).

`tools/callees.py` on each caller, `Rva00516A50::wrap` (0x00516A50),
`Rva56A8StateOwner::applyGlobalCall` (0x0056A870),
`Rva56A8StateOwner::dispatchState` (0x0056A940) and
`ControlBar::hidePurchaseScience` (0x00598F30), gives
`0x290d2 -> 0x465b80`. Retail 0x00465B80 (`tools/dis_retail.py 0x00465B80 8`)
is `mov byte ptr [ecx+0x1AC], 1; ret`, matched as `?apply@Rva00465B80@@QAEXXZ`
(TinyByteFieldSetters.cpp, `BFME_BYTE_FIELD_SETTER(Rva00465B80, 0x1AC, 1)`):
thiscall, no arguments, the same ABI as the old view. The callers now declare
and call `Rva00465B80::apply()`, the matched name at the call's retail target.
Their bytes are unchanged (1/1, 4/4, 1/1, 67/67).

`BfmeGlobal_012f19e8`/`bfmeCall_000290d2` were address spellings of the
global and the ILT slot, not an identity of the body.
