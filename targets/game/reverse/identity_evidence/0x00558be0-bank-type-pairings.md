# 0x00558BE0 bank type pairings

The 341-byte body starts at retail RVA 0x00558BE0 and ends with RET at
0x00558D34 followed by INT3 padding. Its existing matched gadget-selector
callback calls ILT RVA 0x00005F3D, whose jump targets this entry.

## GameWindow is retained, not renamed

Both the old bank and the reconstructed translation unit declare GameWindow
and call GameWindow::winGetSize with width and height output pointers. The
new translation unit retains that name. The name regression matcher pairs
this retained GameWindow declaration with the newly introduced
Rva004B5AA0 declaration; this pairing is false.

The latter declaration belongs to a different retail callee: at caller
0x00558CEC the image, width, height, and color arguments are pushed and the
ECX gadget receiver calls ILT 0x00026BE8, which jumps to 0x004B5AA0. The
existing ledger independently names that matched body
?m@Rva004B5AA0@@QAEHPBVImage@@HHH@Z. Its callee entry returns -1 when the
receiver's window pointer is null and uses RET 16. This cannot be the
GameWindow::winGetSize call at 0x00558C2F through ILT 0x00036EBC, which
instead takes two output pointers. No GameWindow identity is retired.

## The bank's combined gadget class lacks an identity witness

OnlineQuickMatchGadgetState in the bank is a synthetic combined declaration
with five methods and linker alternatename directives. Those directives
map its invented method names to existing unrelated ledger identities:

| Retail ILT | Destination | Existing ledger identity | Cleanup |
| --- | --- | --- | --- |
| 0x00026BE8 | 0x004B5AA0 | Rva004B5AA0::m | RET 16 |
| 0x00036F34 | 0x004B5B30 | Rva004B5B30::set | RET 4 |
| 0x00046A01 | 0x004B5B70 | BfmeThing925C::bfmeGo925C | RET |
| 0x00046DBC | 0x004B5B90 | BfmeThing925D::bfmeGo925D | RET 4 |
| 0x00035B02 | 0x004B5C00 | BfmeThing926A::bfmeGo926A | RET 8 |

The reconstruction calls these existing ledger declarations directly and
introduces no callee pins or alternatename directives. The empty
Rva00558BE0Gadget object only locates the receiver storage at this+0x5c;
it claims no semantic class identity or behavior. Retail shows the storage's
first word supplies the window pointer. The bank's OnlineQuickMatchGadgetState
name is not established by a named retail caller, vtable, export, or donor.
Its five alternate-name declarations are contrary evidence to treating it
as one independently proven real class. Retaining an address-derived storage
view is therefore an explicit correction of the bank's unproved combined
identity, not a rename to manufacture a byte match.

The two correction records are restricted to the exact old bank and exact
verified source hashes. The final source passed the strict existing-TU gate:
3/3 functions, six string literals, and eight DIR32 references. The function
ledger itself retains ?dup_00558be0@@YAXXZ with an object-symbol annotation,
because its semantic owner is still provisional.
