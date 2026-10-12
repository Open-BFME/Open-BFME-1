# The 0x00798F30 body is W3DGadgetTextEntryDraw

`tools/ilt_oracle.py check "?W3DGadgetTextEntryDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z" 0x00798F30`
returns `CONFIRMED p_false=3.91e-04 (exact)`. The address-derived spelling
`?Rva00798F30@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z` returns `CONTRADICTED`, so the
row keeps the descriptive name rather than an address token.

## The operation

The 495-byte body through RET +0x1EE is the text entry gadget's draw callback. It
clears the pending-unichar flag at `+0x15`, reads the window's screen position and
size, selects the composite/text/back colours for the disabled, hilited and enabled
states, draws the back border and the filled back, measures the entry text through
`DisplayString` vtable slot 15 (`[eax+0x3c]`, the BFME offset), then draws the edit
text through the file-static seven-word helper at 0x007986C0.

## The seven-word helper

Retail's call at +0x1E1 pushes exactly seven words (`esi`, then the two text colours,
the two composite colours, `start.x`, `start.y`) and cleans with `add esp,0x1c`. The
`?drawTextEntryText@@YAXPAVGameWindow@@PAVWinInstanceData@@HHHHHHHH@Z` pin that sits on
0x007986C0 carries the Zero Hour ten-argument signature and cannot express that ABI, so
the caller declares the callee under the address token
`?Rva007986C0@@YAXPAVGameWindow@@HHHHHH@Z` and `symbols.csv` pins it at 0x007986C0 as
`additive: retail call target of the red row ...`, the pin read from this row's own
retail bytes by `tools/unresolved_pins.py`. Both callers of the helper (0x00798F30 and
0x007991A0) push the same seven words.

## The shape lever

The four `ICoord2D` locals carry an empty default constructor through an
address-qualified local template derived from `ICoord2D`
(`DefaultConstructed00798f30<ICoord2D>`). Construction alone leaves one LEA SIB byte at
+0x14B (`end.x = start.x + size.x - 2`); constructing every coordinate removes it. This
is the same lever banked for 0x00793260 in
`targets/game/reverse/identity_evidence/00793260-empty-coordinate.md`. The template adds
no field, store, destructor or escaping object, and `ICoord2D` itself stays in use.
