# 0x009A2FE0 identity: BfmeThingCGD::bfmeOneCGD

## Claim

The 193-byte body at retail RVA `0x009A2FE0` is
`?bfmeOneCGD@BfmeThingCGD@@QAEXXZ` (`void BfmeThingCGD::bfmeOneCGD()`).

The ledger row now reads `?bfmeOneCGD@BfmeThingCGD@@QAEXXZ` with source
`game/Libraries/Source/collisionmanager/BfmeConv597.cpp`; it was a
`?d_009a2fe0@@YAXXZ` / `game/gen_asm/d_0099d0c0.asm` `gen-dump` placeholder
until this conversion. `targets/game/reverse/symbols.csv:78120` carries a
`pin` row for the real mangled name at this address.

## Evidence

1. **Matched caller.** `?bfmeGoCGD@BfmeThingCGD@@QAEXXZ` at `0x009A4A30`
   (41 B) is a `matched` row backed by clean C++ in
   `game/Libraries/Source/collisionmanager/BfmeConv597.cpp`. Its bytes
   (`tools/dis_retail.py 0x009A4A30 41`) are:

   ```
   +000f e8 9c e5 ff ff   call 0xda2fe0   ; ?d_009a2fe0@@YAXXZ
   ```

   A matched body calling the address is the strongest identity evidence
   available in this repo (`docs/naming_evidence.md`). The surrounding
   source names three same-class methods, `bfmeOneCGD`, `bfmeTwoCGD`,
   `bfmeGoCGD`; the call order inside `bfmeGoCGD` is One, Global, Two, so
   `0x009A2FE0` is the "one" step and `0x009A30B0` the "two" step.
   The sibling `0x009A30B0` is independently pinned to
   `?bfmeTwoCGD@BfmeThingCGD@@QAEXXZ` (`symbols.csv:79347`), which
   corroborates the pairing.

2. **Prologue arity.** The body has no stack frame, no arguments and no
   return value (`ret` with `pop edi; pop esi` only), consistent with
   `QAEXXZ` and inconsistent with any static or one-argument form.

3. **Owner layout.** The body is `this`-relative throughout (`ecx` is
   read at `+0xae10`, `+0xc060`, `+0xc064`, `+0xc05c` only). Its owner
   guard at `+0xc06d` is the same dword the matched `bfmeGoCGD` sets
   before the call and clears after it, which places both bodies in one
   object.

## What the body proves about the class

Address-derived only; no BFME helper, string literal or vtable slot ties
these offsets to a named field, so they keep their address tokens:

| offset | role |
|---|---|
| `+0xAE10` | bucket table, `0x493` slots (matches the landed `BfmeThingVDB::m_bfmeTable` and the landed `Rva009A2BE0Iter::m_buckets`) |
| `+0xC05C` | head of a second intrusive list the body relinks nodes onto |
| `+0xC060` | bucket cursor (index) |
| `+0xC064` | node cursor |
| node `+0x00`, `+0x04` | two sub-object pointers, both opaque |
| sub `+0x04`, `+0x10` | two flag words, both compared against zero |
| node `+0x10` | cleared to zero when both sub flags at `+0x04` are set |
| node `+0x2C` | back-slot (`Rva009A2FE0Node **`), the landed `Rva009A3770HashChainInsert` idiom |
| node `+0x30` | next |

## Verdict

Landed. The byte-exact clean C++ is
`BfmeThingCGD::bfmeOneCGD()` in
`game/Libraries/Source/collisionmanager/BfmeConv597.cpp` (all 193 bytes,
verified by `add_match.py`); the `gen-dump` scaffold row is retired.

Two source spellings carry the last 9 bytes of the earlier 184 B attempt,
and both are load-bearing:

- `m_cur = m_cur->m_next;` (the cursor, not the local `n`) keeps retail's
  `cmp eax,esi / je` at +0x51/+0x5C. With `m_cur = n->m_next;` MSVC 7.1's
  null-check elimination deletes the test, because the load through `n`
  already implies `n != 0`; dereferencing the member leaves the test on the
  local live.
- `Rva009A2FE0Node **curp = &m_cur;` with `*curp` at the use site stops
  MSVC 7.1 forwarding the value stored at +0x56 into the compare at +0x7F.
  Retail reloads `mov edx,[ecx+0xc064]`; the forwarded value instead pins
  `EDX` across the sub-flag tests, which pushes the first sub-object
  pointer out of `EDX` into a third callee-saved register. Reloading frees
  `EDX`, and the prologue becomes retail's two pushes.

See the `re_attempts.log` rows for the seven earlier blocked verdicts and
the trials that did not move them.
