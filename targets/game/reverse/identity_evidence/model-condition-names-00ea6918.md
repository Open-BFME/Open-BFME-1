# Model-condition name-pointer sequence at RVA 0x00EA6918

This correction binds a caller to a new address-derived structural owner.
It does not recover the original BFME C++ declaration. The semantic descriptor
ModelConditionNames is retained in Rva00EA6918ModelConditionNames; the address
makes the narrower, observed storage identity explicit.

## Why the old declaration is not an established storage identity

At the base snapshot, parseModelConditionFlags.cpp declares only
`extern const char *const ModelConditionNames[]`. It has no definition in the
current game sources, no data-ledger owner, and no strong, COMMON, COMDAT or
alias definition in the frozen census. Three incompatible reconstructed views
are anchored at the same address: that const-pointer array, `g_bfmeTokA450`
as a character array, and `bfmeGlobalTable12A6918` as various mutable pointer
arrays. An anchored undefined spelling establishes a reference address, not
an original declaration or existing storage owner.

Independent upstream evidence contradicts treating that free const-pointer
array declaration as a recovered canonical owner: GeneralsMD Common/BitFlags.h
line 56 declares a private static `const char *s_bitNameList[]`, and lines
264-277 return/iterate `const char **`. GeneralsMD Common/BitFlags.cpp lines
40-175 defines ModelConditionFlags::s_bitNameList with a final NULL. The
reference therefore has a different declaring owner and mutable pointers.
INI.h lines 101-102 accepts a qualification-only const read view and cannot
establish storage constness. There is no relevant retail export to resolve
BFME's original spelling or top-level pointer constness. Its read-only callers
cannot prove them either.

The replacement is deliberately an address-derived mutable pointer array in
the observed writable retail section, with a normal qualification conversion
at the scanIndexList call. It claims the observed sequence, values and use,
not historical C++ constness, a class member, or a wider enclosing allocation.
It does not define or alias the old const-pointer symbol. Other unresolved
views remain unchanged rather than being silently rebound to an invented ABI.
No metric is used to justify this exact naming correction.

## Exact snapshot-bound correction

- Base: d6c408f268b0d00c996ca7b17394d888bec47313
- Path before and after: game/GameEngine/Source/Common/parseModelConditionFlags.cpp
- Pair: ModelConditionNames -> Rva00EA6918ModelConditionNames
- Before source SHA-256: f5318b0d95a9bafd81865f3ccb6a3a78718ba6026e36c7d062ce8fa2123d6f4c
- After source SHA-256: 04bc88e3b19dc8f8bca3e6586fc0a4f202abe359e2ad5769ad91563e8eb54ef2
- Baseline PE SHA-256: 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75
- Exact 1220-byte retail sequence SHA-256: 7ccc1f6c5d4f04e70e39ab79be9715367523c6265cbe1735ace436624f6722f0

## Independent address, layout, values and use

The PE image base is 0x00400000. VA 0x012A6918 is RVA and file offset
0x00EA6918, in fully file-backed writable .data (characteristics 0xC0000040),
not loader-zero storage. There are 304 nonzero 32-bit pointers followed by
NULL at index 304, VA 0x012A6DD8. The consumed sequence is exactly 1220 bytes,
ending exclusively at VA 0x012A6DDC. Each target is a fully file-backed .rdata
string; all bytes through its NUL are compared independently. Examples are
TOPPLED at VA 0x01075060, FRONTCRUSHED at 0x01075050 and final
EMOTION_UNCONTROLLABLY_AFRAID at 0x01073AAC. Every slot is represented by the
source initializer and a compiler-literal pin whose note identifies its slot
and exact target; equal text at another address is not accepted.

The matched 213-byte parser at RVA 0x0076A580 removes NOT_ and searches this
sequence to set two BitFlags<304> masks. BitFlags304BuildDescription.cpp
indexes the same address to describe enabled bits. The matched script
condition-duration reader searches with bound 0x130. Current
Common/INI/ini_parsers.cpp lines 499-516 searches until NULL. These independent
readers prove semantic use, 304 named positions and the consumed terminator.
Trailing zero bytes do not establish a broader original allocation, and this
change does not claim one. No existing data row overlaps the consumed range.

## Compiler, ownership and full-delta verification

MSVC 7.1 proves sizeof the new 305-element array and its allocation extent are
both 1220 bytes. It emits one external initialized .data symbol, aligned to
8 bytes as the retail address is, with 304 DIR32 relocations and a final zero
word. There is no dynamic initializer, added code, CRT startup section, alias,
cast, second owner, or source-level write to the table. Ordinary add_data_match
verifies the row, every relocation's exact target, and the complete extent.

All 565 original COFF section payloads, including code, STLport COMDAT data,
auxiliary records and debug content, are retained. The only existing relocation
change is the parser's one table DIR32 symbol; raw code stays all 213 bytes.
Exactly 305 sections are added: the pointer array and 304 string COMDATs.
All new strings, including NULs, independently equal their exact pointer
locations. The normal caller gate and nine direct-consumer rows pass.

The full data checker reports 306 verified sections, no contradictions, and
538 unplaced STLport constant sections. A paired check on the preserved before
object reports the exact same 538 unplaced sections and one verified literal;
all 305 additions are fully verified. This is not a claim that unchanged
unplaced constants became proved. The supported frozen scoped preview is
213 newly linkable caller bytes, with no native/full-link or transitive claim.
Local receipts are retained in build/model_condition_names_audit.
