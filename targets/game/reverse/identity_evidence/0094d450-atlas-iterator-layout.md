# Atlas bank at RVA 0094D450: missing iterator storage

This is a partial, not a production conversion. The inherited BfmeHostEY
spelling is retained; no new semantic method or class identity is asserted.

The served bank placed a 12-byte map at +08 directly before its texture
holder, putting the holder at +14 and every later field four bytes early.
Retail 0094D476 computes receiver+18, 0094D480 writes byte+1C, and
0094D496/499 store at +24/+20. Independently, sibling 0094D8D0 loads the
word at +14 at 0094D8E0, compares it with the map header at +08, and reads
its node payload at +10/+14. This supports a separate four-byte iterator
member at +14, represented with an address-qualified field name.

The local sorted-tree constructor stores its count four bytes after its
header. Destructor 0094CC70 likewise reads count at receiver+04 and header
at receiver+00. The missing word does not belong inside that tree layout.

The retail body ends with a reachable release block at 0094D890 through
the jump at 0094D8A5; INT3 starts at 0094D8A7. Thus the extent is1111 bytes,
not just the first RET at 0094D88F. Ghidra function creation independently
produces the same1111-byte body. The handler at C5E0C2 points to FuncInfo
E4D280 and six unwind actions; the packing temporary is state3 and the
surface/texture lifetimes are states4/5.

The served bank measures1116B/768 non-relocation differences. Correcting
+14 storage measures1116B/764 differences (quality0.3033), including with
native STLport map and texture headers. The old0.94 score described
normalized instruction shape. Map-reference accessors, narrowing the rows
workspace scope, and visible native map subscript do not improve the caller.
Keep the index specialization declaration-only in the bank; no helper or
pin is promoted. Remaining frame/member-address scheduling and unresolved
strict callee bindings still block production.
