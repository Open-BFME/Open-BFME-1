# Incomplete MemoryPool initializer claim

The retail export names `?_Init@MemoryPool@@YAXXZ` at RVA008827D0
(ordinal1365). Its identity is retained; this correction withdraws a false
complete-body claim, not the export declaration.

The old source was a366-byte naked/__emit transcription ending after
`cmp esi,eax` at88293C. Retail next executes `jb 882920`, then
`pop edi; pop esi; pop ecx; ret` at882940..882943. INT3 begins882944.
The complete extent is372 bytes. The early return at8827E1 does not
terminate the second path. Local unpacked retail and Ghidra read_memory
at VA00C82920 independently agree:

```text
00882920: mov edx, dword ptr [0x130e9f0]
00882926: mov eax, dword ptr [edx + esi*4]
00882929: test eax, eax
0088292B: je 0x882936
0088292D: push esi
0088292E: call 0x882630
00882933: add esp, 4
00882936: mov eax, dword ptr [0x12d4d10]
0088293B: inc esi
0088293C: cmp esi, eax
0088293E: jb 0x882920
00882940: pop edi
00882941: pop esi
00882942: pop ecx
00882943: ret 
00882944: int3 
00882945: int3 
00882946: int3 
00882947: int3 
00882948: int3 
00882949: int3 
0088294A: int3 
0088294B: int3 
0088294C: int3 
0088294D: int3 
0088294E: int3 
0088294F: int3 
```

AGENTS.md requires matched rows backed by real source and byte verification,
and says a naked/__emit lift is not a conversion. Extending the dump would
preserve neither rule. Remove this incomplete definition and tombstone its
row. Keep the existing header declaration and runtime GetProcAddress string.
No directly named source caller was found: the startup resolver stores this
export in its callback table.

Native recovery remains open. The helper882630 consumes EAX plus one stack
argument, as its prologue/caller show; the speculative no-stack thiscall
inference from callees.py is not adequate ABI evidence. This retirement does
not invent a helper alias or change any pin. The surviving memory_pool.cpp
claims must pass the normal scoped gate.
