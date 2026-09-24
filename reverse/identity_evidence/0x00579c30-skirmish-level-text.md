# Apt screen level text at 0x00579C30

The byte-matched `BfmeAptScreenSkirmish::levelBar` at 0x0057C340 calls
ILT 0x0001E812 four times, once for each faction. That thunk jumps to the
433-byte body at 0x00579C30. Each call passes the same `this` and constructs
three by-value `AsciiString` arguments in stack slots. The callee ends in
`ret 12`, copies the first argument for both rank queries, and uses its second
and third arguments as APT text keys. This establishes the owner and ABI.
The method name remains address-qualified because the caller does not supply
an original semantic method name.

The body adds 0x3C4 to `this` before calling the matched
`SkirmishBattleHonors::getRank` and `getPointsToNextRank` bodies through their
retail ILTs. It formats the rank with `APT:CurrentLevelNumFormat`; the second
value uses `APT:NoNextLevel`, `APT:NextLevelNumFormatForOnePoint`, or
`APT:NextLevelNumFormat`. Both values go to the established
`WindowManager::bfme_setAptText` UnicodeString overload through ILT
0x0000BDCA. The observed offset supports a source-local honors field at
0x3C4; `name_oracle.py` has no independent class layout witness, so the
field is labelled by that offset rather than asserted as a globally known
member name.

## Design and adversarial checkpoint before the live claim

Replace only the 0x00579C30 generated dump claim with a clean C++ method in
the GUI source directory. Use the existing `StringInline.h` by-value string
model and add the missing declaration for the already matched
`UnicodeString::format(UnicodeString, ...)` method to that shim header. This
adds a declaration, no layout or implementation. The alternatives are
redeclaring covered string classes in the new source (the header-adoption
gate forbids this) or changing the canonical `unicode_string.h` constructor
and destructor definitions (a broad code-generation risk). Neither is needed.

The source-shaped probe reaches 433/433 bytes with 29 relocation slots
masked. That is diagnostic only. Before claiming a conversion, the strict
`add_match.py --replace-rva` gate must verify every relocation and literal,
and the affected-source/full-header gates must remain green. No new pin is
proposed. The first `getRank` and second `getPointsToNextRank` call routes
are existing ILT symbols, not invented aliases.

The design could still fail if a thunk symbol resolves to the right bytes at
the wrong physical call address; strict relocation verification must reject
that. The four matched caller sites establish an owner but do not justify
dropping the address token from the method name. The shared shim declaration
might change dependent translation units indirectly; the normal full gate
must reject such a regression. If any of these checks fails, keep a banked
attempt and do not claim these bytes.
