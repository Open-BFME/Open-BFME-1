# 0x003F9310 Pathfinder worker — call contract and identity evidence

Anonymous 3812 B body (`?d_003f9310@@YAXXZ`, `game/gen_asm/d_003f4190.asm`;
carved rel32-call/jmp start, ret+int3 end). No named caller reaches it
directly: the only referrers are the still-unnamed 0x003FA5B0
(`Pathfinder::updateAt003FA5B0` worker, itself blocked) and its own ILT
entry — so no owning method name can be proven yet.

## Prologue shape (from `dis_retail.py`, new this pass)

SEH registration frame (`eh_00c1ff03`), `sub esp, 0xDC`, saves
ebx/ebp/esi/edi, `mov ebx, ecx` (thiscall receiver → ebx). First action is a
virtual call through the first stack argument's vtable slot `+0x28`, result
kept in edi and spilled to `[esp+0x10]`. So arg1 is a polymorphic object whose
slot-5 method feeds the rest of the body.

## Call contract (from `callees.py`, all 31 now ledger-named)

- Self-recursion through ILT `0x0003B962` (thiscall, 2 stack slots).
- `0x003F8070` — landed `rva003F8070@Pathfinder@@QAE_NHHPAVPathfindCell@@PAVPolygonTrigger@@H_N@Z`
  (ECX=Pathfinder, six stack args, AL tested).
- `0x0087E370` — now matched
  `?method@Rva0087E370@@QBEXABUCoord3D@@MAAURegion2D@@@Z`
  (Coord3D + float + Region2D&); newly usable arg contract.
- Set/map traversal: `_M_increment` / `_Rebalance_for_erase` /
  `_M_deallocate` (bool-keyed `?$_Rb_global@_N@`), `new`/`delete`,
  `StringBase` copy+set, `_bfme_debugRecordCallsite` /
  `_bfme_debugReportingEnabled`, `ceil`/`floor` imports (4 sites each).
- Remaining dump-backed callees (the concrete frontier): `0x003E3F70`
  (424 B) and `0x0041BAC0` (695 B). Down from seven at the last review.

## Why still blocked

Identity needs a matched caller or vtable slot; the receiver class has no
witnessed layout (name_oracle: no member views); a 3812 B reconstruction from
Ghidra decomp alone would be a guessed body, which no gate can see. Next step
is the two dump callees above, then the 0x003FA5B0 caller — not this body
directly.
