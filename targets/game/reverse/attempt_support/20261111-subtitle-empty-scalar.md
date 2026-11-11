# Subtitle empty-wide scalar ownership

At input ed2b03186a, SubtitleEntryConstructor.cpp declares the existing empty
UTF16 datum as an array. MSVC therefore references `?BFMEEmptyUnicodeString@@3QBGB`
while the existing recorded/matched provider's actual name is
`?BFMEEmptyUnicodeString@@3GB`. Its definition in LANAPIRequestHasMap.cpp is
`extern const unsigned short BFMEEmptyUnicodeString = 0`,2 bytes at VA0107388C.

Use that scalar declaration and its address in the existing str() expression.
No value load or new branch is added. The native constructor318B's DIR32 operand
at+94 already takes precisely that address. No alias/pin/header/provider/data
row change; every layout and function identity remains unchanged.

Normal2-source baseline:2/2 functions and1data row, but wrong-name DIR32 FAIL1.
Repaired provider/consumer gate:2/2 functions,1matched data row,5literals+2empty
references,17DIR32 refs, no unverified refs. Paired proof preserves all13
nondebug sections (flags/bytes/definitions/relocations), normalizing ONLY the
array-name-to-existing-scalar-name external correction. Evidence:
build/subtitle-empty-{baseline,repaired}.log, build/subtitle-empty-proof.json,
and original objects build/subtitle-empty-before/.

The identity/width/address come from BFME 1's existing matched data provider
and native operand, not a donor name or layout. Other canonical scalar clients
are unchanged. Compiler MSVC7.1 13.10.3077, original /O2 /MD /EHsc,
approved private WoW64 prefix, WINEARCH=win64, BUILD_POOL=2.
No actual census/linked-byte gain is claimed. Parent review before publication.
