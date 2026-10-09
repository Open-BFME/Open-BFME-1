# State array at VA 013387E0

The matched 47-byte bfmeSeed at RVA 008D3AB0 stores the seed-or-one
value at VA 013387E0 and fills 623 following DWORDs with a walking
pointer and countdown. This establishes 624 written slots.

The independently decoded reload body at RVA 008D3AE0 uses the same
base in EDI and starts ESI at base+8. Its first loop performs 227
iterations (EDX=E3), and its second performs 396 (EBP=18C). Each loop
reads [ESI] and advances ESI by four. The last second-loop load reads
index 624, establishing a 625th lookahead DWORD. The final output
store targets index 623. The array therefore includes 625 words.

The separately witnessed next-pointer datum is VA 013391A4: the reload
stores base+4 there at RVA 008D3B19, and matched bfmeNext1221 reads and
increments that pointer. Base+625*4 equals 013391A4, bounding the array
without claiming its neighbor. Retail loader-mapped .data contains
2500 zero bytes throughout this full extent. A raw file offset read
would incorrectly continue into file data past the section raw extent;
the data-row verifier uses the loader-mapped image.

Define the already recorded symbol g_bfmeStateFA as int[625], preserving
its mangled name and the caller view. Its meanings remain opaque; this
adds no address global, data pin, alias, or DIR32 record.
