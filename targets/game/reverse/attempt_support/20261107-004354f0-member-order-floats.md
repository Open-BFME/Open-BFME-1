# 0x004354F0 `??0Rva00435A40Sink@@QAE@PAVGameFont@@MMHHHH@Z` (517 B): EXACT

Landed source: `game/GameEngine/Source/Common/Gen0000D33CCtor004354F0.cpp` (class renamed from the `Rva00435A40Sink` view to `Gen0000D33C`). `probe.py` reports `517/517`,
17 relocations, `EXACT (modulo relocation slots)`.
cl: `/DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS`
plus `// stlport`. These are the banked flags, unchanged.

## Starting point
The bank `targets/game/reverse/attempts/0x004354f0.cpp` reproduced as logged:
517 B, 17 relocations, 14 non-relocation differences from +0x142. The `/FAsc`
table showed the residue: the CSE temporary for `(float)m_20` (tv418) took the
dead `height` home (+16, esp+0x2C) and `halfTextWidth` took the `value58` home
(+28, esp+0x38). Retail has those two swapped. Earlier sessions had tried
about 40 spellings (operand order, locals, const/register, named float m_20,
half-block placement, EH levers), and every one gave the same 14-difference
result.

## What fixed it (statement order: control flow / evaluation family)
Assign the float fields in member order and read back the stored members:

```cpp
m_30 = textWidth;
m_48 = (float)textWidth * 0.06666667f;
m_4c = width;
Int rowWidth = (m_24 - 1) * textWidth;
m_50 = height - (float)rowWidth;          // a rowBottom local also works
m_54 = (float)m_20 + width;
m_58 = height;                            // must come AFTER m_54
Int halfTextWidth = textWidth >> 1;
float widthWithHalf = width + (float)halfTextWidth;
m_5c = widthWithHalf;
m_60 = m_50 + (float)halfTextWidth;
m_64 = (float)m_20 - (float)textWidth + widthWithHalf;
m_68 = (float)((m_24 - 2) * textWidth) + m_60;
```

The scheduled instruction stream is unchanged. Only the slot tie-break flips:
`_halfTextWidth$ = 16`, `tv418 = 28`. This matches retail.

Trials (all with `/FAsc` tables):

| variant | result |
|---|---|
| bank order (b0) | 14 diffs, the known fixed point |
| `width += half` in place | 14 diffs |
| `height -= rows*h` in place | 61 diffs |
| all-members form, `m_58` before `m_50` | 61 diffs |
| half from `m_30 >> 1` | 14 diffs |
| width and height both in place | 521 B |
| half computed first | 68 diffs |
| `m_54` late | 511 B |
| `m_64` early | 513 B |
| named `right = (float)m_20` first | 515 B |
| **member order** (`m_30,m_48,m_4c,m_50,m_54,m_58,...`) | **EXACT** |
| bank order plus only an `m_50` read-back | 61 diffs |
| member order with `m_58` moved before `rowWidth` | 61 diffs |
| member order with a `rowBottom` local | EXACT |

Measured lever: `m_58 = height;` must follow `m_54 = ...` in the member-order
sequence. Putting `m_58` earlier gives 61 diffs.

## Push-back callee (cleaner than the bank)
The bank used `#define _M_insert_overflow j_0001be87` over a fake POD payload,
so the call bound to a TU-local, misnamed member. The landed source drops the macro
and writes `((_STL::vector<BfmeItemKA *> *)&g_bfmeBegKA)->push_back(this);`.
The bytes stay EXACT, and the call now names
`?_M_insert_overflow@?$vector@PAVBfmeItemKA@@V?$allocator@PAVBfmeItemKA@@@_STL@@@_STL@@IAEXPAPAVBfmeItemKA@@ABQAV3@ABU__true_type@2@I_N@Z`.
Pointer elements get STLport's `__true_type` traits (`type_traits.h:184`
`_IsPtr`), which agrees with the `__true_type` object-symbol of the 0x00434FF0
row.

## Landing notes (read-only checks; not landed)
(a) `ilt_oracle.py check` reports CONTRADICTED (p_false=8.48e-04, window
30872:19327-19339) for `??0Rva00435A40Sink@@...`. It gives the same verdict for
`??0Gen0000D33C@@QAE@PAVGameFont@@MMHHHH@Z`, which is also pinned at
0x004354F0 (`symbols.csv:2913`, evidence `006ee3f0-descriptor-reset.md`) and is
used by matched caller `W3DDisplayRva006EE3F0.cpp`, and for `?d_004354f0`.
Pin `symbols.csv:3606` is the `Rva00435A40Sink` name used by matched caller
`MilesAudioManagerRva006AF840.cpp`. The ILT row is `?j_00026afd@@YAXXZ`
(0x00026AFD). Both class names sit on one address, and the dtor at 0x00435780
is `??1Gen0000D33C@@QAE@XZ` (`GenDtor006952C0.cpp`). The class names need to be
reconciled before landing, as a one-identity issue; use `one_identity.py`. The
oracle contradicts every candidate, so it does not pick between them. Land
under whichever name the lander reconciles, and update the other caller.

(b) Helper COMDATs this TU emits that have their own rows:
- `_STL::vector<Gen_t_004353c0_p8cd>::~vector` probed against 0x004353C0
  (149 B): EXACT. Its home row is `game/gen_small/tgrid_115.cpp`.
- `vector<BfmeItemKA*>::_M_insert_overflow` (`__true_type`) probed against
  0x00434FF0 (265 B): EXACT. Its row is
  `Gen_f265_b7a8aa_00434ff0` (gen-shim, `fam_001.cpp`), whose object-symbol
  names a `Gen_t_00434ff0_m4pod` payload. The call site goes through ILT
  `?j_0001be87@@YAXXZ` (0x0001BE87 -> 0x00434FF0). The lander must make the new
  mangled name resolve: pin it (with `route=`) or repoint the 0x00434FF0 row
  to the real `vector<BfmeItemKA*>` name. Run `pin_consistency.py` first.

(c) Globals referenced by address, all present in `dir32_addresses.csv`:
`?Rva0048EC80TheManager@@3PAVRva0048EC80Manager@@A` 0x012F12CC,
`?g_bfmeBegKA@@3PAPAVBfmeItemKA@@A` 0x012F146C,
`?g_bfmeEndKA@@3PAPAVBfmeItemKA@@A` 0x012F1470 (+4 end_of_storage at
0x012F1474 through the vector view), `?BFMEEmptyString@@3QBGB` 0x01084C34, and
`__real@3d888889` 0x010F3984. There is also the EH handler/funcinfo
`eh_00c2210b`. Check its `$L` state pins with `eh_state_pins.py`.

(d) Home TU: no existing TU defines this class. The same object's
`Rva00435270Layout::apply` (0x00435270) lives in
`game/GameEngine/Source/GameClient/GUI/Rva00435270ApplyLayout.cpp`, and the
dtor lives in `game/GameEngine/Source/Common/GenDtor006952C0.cpp`. A new
`game/GameEngine/Source/GameClient/Rva00435A40Sink.cpp`, which could later
also hold the 0x00435A40 `publish` bank, is the natural home. Reuse the
canonical `UnicodeString` header if it preserves the bytes. An earlier log
entry says it does.

## Landed (2026-11-07)

- `??0Gen0000D33C@@QAE@PAVGameFont@@MMHHHH@Z` landed over the gen dump with `--replace-rva`.
  `Gen0000D33C` is the class name already used by the matched dtor 0x00435780 and by the
  matched W3DDisplay caller. The second pin, `??0Rva00435A40Sink`, still names the same
  address for the MilesAudioManager view. Reconciling it is left to a class-contract pass
  (the `publish` bank at 0x00435A40 uses that name).
- 0x00434FF0 moved from the gen-shim `Gen_f265_b7a8aa_00434ff0` to the STLport instantiation
  this TU emits:
  `?_M_insert_overflow@?$vector@PAVBfmeItemKA@@...__true_type...`. Retail callers are this
  ctor and the shim 0x00435350, both through ILT 0x0001BE87, found by a raw E8 scan.
- `vector<Gen_t_004353c0_p8cd>::~vector` is emitted here too. It is retail-identical to its
  tgrid row at 0x004353C0, which stays as it is.
