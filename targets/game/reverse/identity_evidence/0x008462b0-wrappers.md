# RVA 0x008462B0 / 0x008462D0 / 0x008462F0 wrappers

The old 109-byte generated dump merged three independent functions and two
INT3 alignment bytes. Retail decoding proves these complete extents:

- 0x008462B0: plain RET at +0x1E, INT3 at +0x1F; 31 bytes.
- 0x008462D0: plain RET at +0x1E, INT3 at +0x1F; 31 bytes.
- 0x008462F0: plain RET at +0x2C, followed by INT3; 45 bytes.

The preceding function has RET 0x20 at 0x008462A5, ending at 0x008462A8;
eight INT3 bytes separate it from 0x008462B0.
The first two wrappers each forward four cdecl slots and a null fifth slot,
clean 20 bytes and return the callee result. Their calls at +0x16 resolve to
0x00836BC0 and 0x00836980 respectively. Those existing matched providers
are the long- and int-distance STLport narrow time_get `__match`
specializations. The native `_time_facets.c` declaration proves two
istreambuf_iterator references followed by two string pointers and the
distance-type pointer. Explicit specialization declarations here preserve
those out-of-line providers instead of creating extra definitions.

The third wrapper forwards seven cdecl slots and cleans 28 bytes: its hidden
return buffer, first and last character pointers, a two-word
ostreambuf_iterator, an empty iterator-tag reference, and a null int pointer.
The direct call at 0x00846311 resolves to 0x008460D0. The already verified
`Rva008460D0` ABI pin used by 0x00846B40 supplies this exact route, rather
than the canonical `__copy` provider at 0x00835590. No pin is added or changed.
Independent decoding of the complete 114-byte callee confirms its difference
loop, streambuf put-area/overflow writes, success-byte tracking and two-word
hidden-result store. See also [the original callee proof](0x00846b40.md).

Ghidra 12.1.2 read-only inspection of the restored retail project on
2026-10-03 independently reports three entries of 31, 31 and 45 bytes,
with the same direct-call destinations, plus the 114-byte copy callee.
Its inferred void return types are not used as ABI proof: the matched native
providers and retail register/stack operations establish the signatures.

The wrapper shapes alone cannot distinguish the exact original template
names. Each wrapper therefore retains its own address-derived identity.
Native STLport includes supply real iterator and string layouts; no invented
class or hand-redeclared vendor layout is introduced.

All three probe results are exact modulo relocations. `add_match.py` and the
scoped build validate the actual direct-call destinations. This recovers all
107 executable bytes of the old bundle, excluding only the two INT3 bytes.
