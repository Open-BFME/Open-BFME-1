# GameSpyPlayerInfoOverlaySystem at 0x004D99C0

`GameSpyPlayerInfoOverlaySystem` moved out of the shared, many-function
`PopupPlayerInfo.cpp` translation unit into its own TU,
`PopupPlayerInfoOverlaySystem.cpp`, replacing the Open-BFME5 `__emit` naked
lift. Deleting the naked function's ~820 lines changed `PopupPlayerInfo.cpp`,
so `name_regression.py`'s "unchanged donor" skip does not apply and its
whole-file comparison pairs the two files.

`PopupPlayerInfo.cpp` still declares, unchanged and at their original lines,
the `BfmeStringLiteralBase` / `BfmeAsciiStringArg` helper classes used by the
independently matched `PopulatePlayerInfoWindows` argument shim elsewhere in
that same file (see `((BfmeStringLiteralBase *)this)->BfmeStringLiteralBase::
BfmeStringLiteralBase(text)` and the `BfmeAsciiStringArg` call site). Neither
class has anything to do with the extern `Rva00627C40SetFlag` declaration in
the new file, which names the already-matched Zero Hour `ReOpenPlayerInfo`
twin body at `0x00627C40` (the `buttonSetLocaleID` case's flag-reset call) by
its address, per AGENTS.md's `RvaXXXXXXXX` convention for an address-derived
identity.

The token-level whole-file diff pairs `BfmeStringLiteralBase` with
`Rva00627C40SetFlag` purely because both files otherwise share large runs of
identical C++ boilerplate tokens (types, includes, `extern`/`void` decls) that
`difflib.SequenceMatcher` aligns as "equal", leaving this one unrelated
identifier pair aligned as if it were a "replace". This is the same
donor/landed file-pair false positive documented in
`targets/game/reverse/identity_evidence/004dfef0.md`: the old identifier stays
in the retained donor file and the new identifier is an unrelated,
independently-justified name in the new file, not a rename of the same
entity.
