# 0x0061A0F0 (?d_0061a0f0, 213 B) -- un-rotated found-loop bank, 2026-11-02

Model claude-opus-5-5, session a1/536. Banked (with the earlier bank's names kept for name_regression)
as targets/game/reverse/attempts/0x0061a0f0.cpp.

BFME 1 target facts (dis_retail): this kept in EDI; TheLivingWorldCampaignManager
(0x012F1024) -> ILT 0x00045917 -> 0x003B3950 (ledger
?Rva003B3950Room@Glo012F1024Type@@QAE?AVBfmeRoomYC@@XZ, hidden-pointer AsciiString
return into the frame local); empty -> format(AsciiString("NoActNameFound"));
walk the 0x24-byte entries at this+0x9C until the first one whose +0x18 byte
is 0: getName via ILT 0x0001DEE4 -> 0x006196F0 (object-symbol
?getName@Rva003A4390Owner@@QAE?AVAsciiString@@XZ), then 0x00619C40 via ILT
0x000451FB with `mov ecx,edi` (caller treats it as a thiscall member of the
owner; the callee never reads ECX, so its stdcall ledger name is
byte-equivalent but the caller needs a member spelling, i.e. one
address-derived pin ?rva00619C40@Rva0061A0F0Owner@@QAEXPAURva00619C40Entry@@HABVAsciiString@@@Z
at 0x00619C40 before landing).

Measured (probe, /DNDEBUG /MD /EHsc + WWLib ascii_string.h):
- plain `for (i = 0; !found; ++i)` / continue / while forms: 219 B, 90 diffs
  (MSVC rotates the loop; retail keeps `xor cl,cl; test cl,cl; jne` at the head).
- `bool searching = true; for (i = 0; searching && !found; ++i)` (s512 lever:
  foldable && first term) un-rotates it: 211 B, 81 diffs, shape 0.953.
  Same result for continue-form, while-form, (m_entries + i), pointer local,
  volatile flag read, inline flag accessor, inline entryAt(i).
- `this && !found`: 221 B; hoisting i/found above the name: 209 B 140 diffs;
  const-ref temp for getName: 214 B 118 diffs.

Remaining residue: this in ESI / index in EDI / found in AL (retail EDI / ESI / CL),
and retail does not CSE &m_entries[i] between the flag load
(`mov dl,[esi+eax+0x18]`) and getName's receiver (`lea ecx,[esi+eax]`
recomputed after the temp lea) -- ours keeps `lea ecx,[edi+edx]` live. The
two retail sizes differ by exactly that recomputation (+2 B).

LANDED later the same session: spelling each record use
`m_entries.begin()[i]` (inline begin() on a 3-pointer vector view at +0x9C)
made it EXACT (213/213). Landed as ?rva0061A0F0@Rva0061A0F0Owner@@QAEXXZ in
game/GameEngine/Source/GameLogic/LivingWorld/Rva0061A0F0Dispatch.cpp with two
caller-view pins: ?rva00619C40@Rva0061A0F0Owner@@... at 0x00619C40 and
?rva006196F0@Rva00619C40Entry@@QAE?AVAsciiString@@XZ at 0x006196F0 (the
getName@Rva003A4390Owner spelling resolves to the twin 0x003A4390's ILT
0x0004958A, not to 0x006196F0's ILT 0x0001DEE4).
