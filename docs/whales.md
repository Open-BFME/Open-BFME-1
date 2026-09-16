# WHALE-2 recipes

## 0x00960A30 — SegLineRendererClass::Render

- Status: banked partial, not landed. Preferred source is `reverse/attempts/0x00960a30.cpp` with support declarations in `reverse/attempt_support/0x00960a30.inc`.
- Evidence: 14,081 bytes, frame `0x6d84`, 190 relocation tuples, all callees resolved, and 17 canonical sibling emissions exact. The preferred body has 51 non-relocation differences (`0.9963780981464385`); the remaining groups are merge base/index SIB encodings (40), merge X-product order (2), initial-output SIB encodings (5), and expansion TOP-X addition order (4).
- Recipe: include canonical `matrix3d.h` before the TU-local ABI prefix, retain the hidden-result VB ABI, the proven `BoxDynamicVBAccessClass`/lock declarations, `BoxSetTexture` at `0x00905AC0`, the `TILED_TEXTURE_MAP` dead fall-through, the asymmetric `DotSegLineBottomOutput` helper with volatile `point.Y`, and `ScaleSegLineExpansion` for the three component stores. No new pins are required.
- Search: 12 explicit pointer/index alternatives were compiled with `tools/shape_search.py`; all legal alternatives stayed at the same 51-byte shape. Integer-address and reversed-index forms are therefore recorded as exhausted for this bank. Keep the bank; do not edit `Code/gen_asm` until an exact source is found.

