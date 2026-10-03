# Include both runtime-check initializer loop exits

Both61B claims cut the final short loop JMP at009F7F46/009F7F8A.
JAE009F7F24/009F7F68 reaches the omitted CALL009F7EC3 and RET at
009F7F4D/009F7F91. Original RunTmChk initsect.obj emits68B per body;
Ghidra/local PE tails agree. Next code begins009F7F4E/009F7F92.

Retain the current __RTC_Initialize identity and the second address-named
archive twin's explicit identity uncertainty. Each complete68B comparison
has48concrete matching bytes with archive relocations masked. No new
semantic identity, source code or pin follows from that masked equality.
