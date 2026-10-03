# RVA 0x002E996A: Lua parser typed catch

The retail parent at RVA 0x002E9680 is already byte-matched in
`LuaScriptEngineParseModelConditionEvent.cpp`. Its EH handler at RVA
0x00C15980 points to FuncInfo RVA 0x00E0542C. The one try-map record at
RVA 0x00E05418 covers states 1..2, catch-high 3, and has two handlers
in the array at RVA 0x00E053F8. The first handler record contains
adjectives 8, type descriptor VA 0x012A6FD4, catch-object offset -0x74,
and handler VA 0x006E996A. The second is catch-all at VA 0x006E99BF.
This metadata, rather than adjacency, proves the parent.

Retail bytes at 0x002E996A end in `mov eax,0x006E991D; ret` at +0x4F,
for 85 bytes total. The next six bytes are the separate catch-all, then
INT3 padding. Ghidra function creation at VA 0x006E996A independently
reported an 85-byte body; decompilation confirms the debug-reporting guard,
logging slots +0x60/+0x6C/+0x38/+0x4C, exception load through EBP-0x74,
and continuation VA 0x006E991D. No class identity is inferred from logging.

The existing native try/catch emits compiler-local label $L5359, whose
first 85 bytes reproduce this handler. The following six bytes are a
separate label. The ordinary scoped gate checks calls, literals, globals
and the continuation relocation. The row uses an opaque address identity
and records its parent and object label; no assembly body is authored.
