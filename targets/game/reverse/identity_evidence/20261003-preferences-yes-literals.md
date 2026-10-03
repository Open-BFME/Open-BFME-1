# Complete affirmative literals in the system-map getters

`docs/matching.md` requires the complete literal, including its terminator, to
match retail. `usesSystemMapDir` emitted `y\0`, while each of its three
95-byte claims pushes the complete `yes\0` at VA `0x0107C76C`.

| RVA | Existing identity | Key | Final RET / following INT3 |
|---|---|---|---|
| 00090780 | OptionPreferences::usesSystemMapDir | UseSystemMapDir | 000907DE / 000907DF |
| 000869A0 | ?dup_000869a0@@YAXXZ | UseSystemMapDir | 000869FE / 000869FF |
| 0009E7B0 | ?dup_0009e7b0@@YAXXZ | UseSystemMapDir | 0009E80E / 0009E80F |

Each literal operand is independently read at body +0x47; the key operand is
at +6. Each call uses the imported `_strcmpi` at IAT VA `0x0135933C`. The
PE contains `79 65 73 00` at the shared literal; Ghidra independently agrees.
The GeneralsMD OptionsMenu.cpp twin uses the same key, default true result and
case-insensitive `yes` comparison. The two address names stay opaque; equal
instructions are not evidence that they share the primary getter's identity.

Before the edit, the scoped gate passes all five TU instruction claims but
reports exactly three complete-string mismatches. Changing only the shared
`y` literal to `yes` repairs all three. The unrelated two existing getters are
reverified unchanged. No ABI, name, extent, pin or coverage change is claimed.

The stale `y` prose is corrected in both the system-map row and the previously
fixed save-camera row (original e7e7c3335c, rebased 80c8162b9c). The latter's
95-byte source fix is unchanged. Body 00090880 has the same literal lead but
is held by another worker and is outside this source edit.
