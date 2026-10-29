# 0x003A1080 bfmeSetupJG: tail sub-struct bank (2 bytes left)

Retail 119 B, `ret 0x18` at +0x74, int3 at +0x77. Bank
`targets/game/reverse/attempts/0x003a1080.cpp` (session 475, claude-opus-5-5).

## What changed
The previous bank (5 diffs) made fields 0x3C..0x50 `volatile` to pin the store
order. Modelling 0x3C..0x50 as a struct with an inline `reset(bool f)` that
stores a3c, a40, a45, a46 and then calls a nested float trio's inline `zero()`
(0x48/0x4C/0x50), called as `m_tail.reset(m_bfme0cJG != 0)`, reproduces every
store in retail order with no volatile. The structure is a hypothesis that fits
the codegen; no retail evidence names those fields.

## Remaining mismatch
+0x5F/+0x62: retail `setne dl; mov [esi+0x46],dl`, ours `setne al; mov [esi+0x46],al`.
Retail leaves EAX (p5 / m_0c) and ECX untouched.

## Ruled out (all stay at 2 unless noted)
`this->`, `0 !=`, `!!`, `? true : false`, `const bool &` parameter, self pointer
inside reset, reference to m_tail, inline `hasFive()` getter, bool local first,
int trio, chained `x = y = z = 0`, bool field types, trio as a separate member
after m_tail, `return m_0c` (122 B). `reset(p5 != 0)` gives `dl` but sinks the
cmp (11). Plain stores without the nested trio: the 0x46 store sinks below
0x48..0x50 (8). Flags /G5 /G6 /G7 /Ox /Og inert, /O1 worse.

The name_corrections entry for this bank records a positional token pairing
(`p5` -> `m_bfme0cJG` in the reset argument), not a rename.

## Register-choice observations (same session, later)
Returning `p5` as int (`return p5;`, no extra bytes, EAX already holds it)
moves the flag to `setne cl`: the byte register follows liveness, so retail has
EAX and ECX both unavailable at +0x5F. Inert with the int return: cast `this`,
trio pointer, `TailJG *` local, bool local; `return m_0c` reloads (122 B).
Inline `__fastcall` static/free reset helpers (flag second or third) stay `al`.
The function is only reached through slot 2 of the vtable at 0x010C7E28
(`??_7GiantBirdNested@@6B@` in dir32), so its return type is not proven void.
