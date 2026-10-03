# PlayerInfo map insertion cleanup at RVA 00C40A09

Retail parent 00633C70 pushes handler 00C40A1A. Its FuncInfo at
00E30598 names the three-state unwind map at 00E30580. State 1 has
predecessor -1 and action 00C40A09. All 17 bytes decode through RET at
00C40A19; the next instruction begins the handler. The two placement
pointers are EBP+0C and EBP+10. ILT 0002AAA9 routes to canonical scalar
placement delete at 000607F0.

The unchanged native PeerDefs_PlayerInfoMap_M_insert.cpp emits two
byte-identical placement-delete actions in its parent EH section. Bytes
alone cannot choose between them. In this build the parent handler has a
DIR32 relocation at +1 to $T1249. That FuncInfo has magic 19930520,
count 3, and a +8 relocation to $T1252. This unwind map has predecessor
-1 in each row and action relocations +4->$L1100, +12->$L1145,
+20->$L1208. Therefore retail state 1 selects $L1145, not $L1208.

$L1145 lies in executable COFF section 43 and retains 13 concrete bytes;
its REL32 at +9 is ??3@YAXPAX0@Z. The full native parent and action pass
the strict scoped gate (2/2). The new row uses only an opaque action name.
No source, symbol pin, template identity, or generated dump was changed.
