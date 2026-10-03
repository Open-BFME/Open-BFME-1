# RVA009AB530 control-flow audit

The full raw PE body ends at RET009AB75B and INT3 starts009AB75C: 556 bytes.
Ghidra FUN_00dab530 reports550 addresses, excluding internal alignment, not
a550-byte contiguous extent. Its decompile agrees with these direct branch
witnesses, which refute the older bank's frame-only diagnosis:

- JNE009AB5C6 targets009AB5DA. The reuse flag skips only the28-byte copy
  fromVA01143124 to context+560, not the subsequent decoder/table loops.
- DecodeBool(state,128) at009AB5E0 is followed by JE009AB5EA to009AB62E.
  That guard encloses both the index loop and BuildTable at009AB626.
- CMP ESI,40h at009AB619 followed by JB009AB61C bounds the loop to1..63,
  not1..64. Its store is context+63C+index.
- The two14-column loops at009AB62E..009AB672 and all three final passes
  execute regardless of reuse. In the final loop, a decoded value updates
  previous[column] at009AB6DE before context+3B6 at009AB6E2. The failure arm
  checks reuse at009AB6EB..009AB6F1, then copies previous[column] through
 009AB6F3..009AB6FF when reuse is false. The older bank omitted both history
  operations here.

Direct callees are DecodeBool009B4800 (typed Rva009B4800State*), integer
decoder009AC550 (void*,int), BuildTable009AAFE0 (Rva009AAFE0Context*,const
unsigned char*), and BuildTone009B64A0 (unsigned char*). The corrected bank
uses their canonical declarations. The data view names the physical region
atVA011430B0; addends18h,58h,74h,90h and21Ch reproduce the independently
decoded probability/copy addresses and final endpoint. No data pin is added
and no original source-level array identity is asserted.

The served bank measured550B/457 differences (quality0.1565). Correcting
behavior first gives628B/483 differences; named data lowers that to596B/447.
Writing byte += (byte == 0) retains retail's SETcc/add calculation and gives
572B/445. Reusing the dead parameter as the table cursor with volatile cursor
and two stack counters gives547B/433, quality0.1888. This is an experimental
bank, not a conversion or proof that those qualifiers existed in the source.
The stack allocation and loop register schedule remain different. Parameter
top-level volatile changes the emitted spelling toYAXRAE_N but not the
witnessed two-word cdecl entry contract.

Negative controls include counter declaration reuse, signed endpoint/do-loop
forms, direct address arithmetic, row-index/matrix-loop expressions and
recomputing the state address. /Og- gives881B; /O1 gives489B. The best corrected
nonvolatile draft remains572B/445 and is in build/n1/session4/probability_setcc.cpp.
No nonmatching body or speculative callee alias was added to game/.
