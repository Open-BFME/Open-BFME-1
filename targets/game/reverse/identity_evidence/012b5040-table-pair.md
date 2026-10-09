# Table pair at VA 012B5040 and 012B50A0

The complete matched 22-byte copy at RVA 00421E20 loads ECX=24,
ESI=012B5040, and EDI=012B50A0, then executes REP MOVSD. Thus both
arrays contain 24 DWORDs (96 bytes). The two bases are exactly 96
bytes apart, bounding the source; the distinct next source table
begins at VA 012B5100, exactly after the destination. This following
table is independently used by matched bfmeCopySecond in
Bfme5TinyFifteen.cpp, with its separate 22-word copy extent.

Retail .data contains identical 96-byte initializers in both arrays.
The existing int[24] views are retained, including the raw bit patterns
of their floating-point entries and the final integer values 3 and 1.
No semantic identities are asserted for individual entries. Both
compiler sizeof probes must report 96, and neither array has a pointer
relocation. Define the existing symbols; no pins, aliases, address
globals, header changes, or DIR32 record edits are needed.
