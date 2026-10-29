# 0x0024ECA0 callee spelling: askDG -> Gen_0021AD10::bfmeAskRaw

- BFME 1 target evidence: retail 0x0024ECA0+0x16 calls ILT 0x00036C05 with
  `mov ecx,esi` (the this-0x20 container) and one pushed argument; the ILT jumps
  to the matched row ?bfmeAskDG@@YGHPAUBfmeThingDG@@@Z at 0x00248AE0 (31 B,
  `ret 4`, ECX unused).
- symbols.csv already pins ILT 0x00036C05 as the thiscall spelling
  ?bfmeAskRaw@Gen_0021AD10@@AAEPAXPAX@Z (used by Rva0021AD10Find.cpp).
- The old bank's `Rva0024ECA0AskDG::askDG` was a bank-local invention bound
  by `/alternatename` to ?j_00036c05@@YAXXZ; no matched caller, header or EA
  string names it. The converted source calls the pinned spelling instead.
- Bytes: scoped build exact, 126/126 B (add_match verified).
