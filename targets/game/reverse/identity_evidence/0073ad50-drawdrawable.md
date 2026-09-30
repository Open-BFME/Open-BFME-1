# 0x0073AD50 is `drawDrawable`

The recovered `W3DView::update` body at RVA `0x007446A0` passes VA `0x00B3AD50` to `GameClient` slot `0x54`, then passes `this` as the fourth argument.

At RVA `0x0073AD50`, retail loads the first two stack arguments, pushes the second, calls ILT `0x00003873`, and returns. The `symbols.csv` pin for `?draw@Drawable@@QAEXPAVView@@@Z` at that ILT resolves to matched body `0x00421830`. The caller therefore invokes `Drawable::draw(View *)` with the first argument as `this` and the second as the view.

`W3DViewDrawDrawable.cpp` defines `drawDrawable(Drawable *, void *)` and calls `Drawable::draw` with the user data as a `View *`. `tools/probe.py` reports that this 15-byte function matches RVA `0x0073AD50` exactly, including its one relocation slot. The old ledger row names a `SparseMatchFinder` helper, but the retail call path identifies this body as the drawable callback.
