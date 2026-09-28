# 0x006D2130 grid dispatch: element callees `probe`/`apply` were placeholders

The bank `targets/game/reverse/attempts/0x006d2130.cpp` declared the two
per-element callees as `Rva006D2130Elem::probe` and
`Rva006D2130Elem::apply`. The landed source
`GridDispatch006D2130.cpp` names them `rva00729180` and `rva0072EAA0`.
name_regression reads that as a descriptive-to-opaque regression. It is
not one, for these reasons:

- The bank's own header said the names were read off the call sites
  ("return type/arg count read off the call sites, not guessed at
  semantically") and told later agents to "keep the class and the two
  probe/apply names address-derived per docs/naming_evidence.md".
- Neither target has a real name anywhere. The ledger has only
  generator placeholders: `?d_00729180@@YAXXZ` (287 B, gen_asm),
  `?d_0072eaa0@@YAXXZ` (35 B, gen_asm), their ILT thunks
  `?j_00013de5` / `?j_0002db41`, and symbols.csv `?b_00729180` /
  `?b_0072eaa0` (gen-thunk body). No vtable slot, string, Zero Hour twin
  or matched caller supplies an identity.
- Retail calls both through ILT thunks 0x00013DE5 -> 0x00729180 and
  0x0002DB41 -> 0x0072EAA0 with ECX = element (0xC4 stride), no stack
  arguments, and a plain `ret`. That fixes the ABI. It says nothing about
  what either function does.

The address-derived names state only what is proven: the target address.
