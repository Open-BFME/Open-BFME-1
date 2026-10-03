# Opacity-envelope parser numeric operands

The existing642-byte body at000B9EA0 returns at000BA121, followed by INT3.
Its five x87 numeric operands at entry offsets237,322,407,492,572 all
reference VA01082C38. Retail bytes0AD7A33B encode0.005f. The previous
source calls the Zero Hour inline conversion helper, whose local readonly
LOGICFRAMES_PER_MSEC_REAL bytes8FC2F53C encode0.03f.

Use a TU-local inline arithmetic helper in an address-qualified namespace with the proven
0.005f value for exactly these five expressions. Its inherited helper name
is retained; the shared original helper remains unchanged. Retain the existing opaque
owner, field offsets, parser flow, call ABIs and /Ob1 inline budget. No
shared header, timing constant, ledger identity or extent is changed.
The first three ceil calls remain IAT01359394, and the final two remain
ILT00032B00 ->000B8E60. The reviewed7bfaf884e4 reference verifier checks
the exact numeric operands alongside full function bytes and literals.

Ghidra entry/end004B9EA0..004BA121 corroborates the642-byte span, although
its address-set body_size is636; the local PE return/padding proves the
contiguous extent. The20-byte wrapper000B8E60 loads a float, widens it to
the imported ceil argument and returns at000B8E73. No callee pin is added.
