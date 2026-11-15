# Narrow-string header adoption: tasks 1-8 of 200

Baseline `7c314a3e6cbd63b2ee6d6a7f0aa68c8bc6e68432`. Eight existing source units adopt
`game/Libraries/Source/WWVegas/WWLib/ascii_string.h`, replacing private AsciiString
facades. No canonical header, compiler option, symbol pin or source-authored
linker alias changes. This is source reconciliation, not new reconstructed bytes.

| Task | Source | Retail function RVAs |
|---|---|---|
| 1 | `game/GameEngine/Source/Common/RTS/ScienceStoreInternalName.cpp` | `0x000E71F0` |
| 2 | `game/GameEngine/Source/Common/System/SaveGame/GameStateSetPristineMapName.cpp` | `0x00387960` |
| 3 | `game/GameEngine/Source/Common/Rva000CD770StringSetter.cpp` | `0x000CD770` |
| 4 | `game/GameEngine/Source/Common/S4SwapElem12.cpp` | `0x0052E370` |
| 5 | `game/GameEngine/Source/Common/System/SubsystemInterfaceName.cpp` | `0x0006E250` |
| 6 | `game/GameEngine/Source/GameLogic/System/assignRandomStillImage.cpp` | `0x00385430` |
| 7 | `game/GameEngine/Source/Common/Rva003BB590.cpp` | `0x003BB590` |
| 8 | `game/GameEngine/Source/GameClient/GUI/WindowLayoutGetFilename.cpp` | `0x004EA450` |

## Independent layout and behavior evidence

Canonical AsciiString is the existing BFME 1 class over StringBase<char>, with
its four-byte base at offset zero, no added fields or vptr. Native CodeView
controls establish the old and new layouts in each unit; seven old types already
have size four. assignRandomStillImage had an empty size-one facade used solely
through a pointer. Its canonical size four adds no object, copy, allocation or
frame bytes: the entire compiled runtime graph remains identical. The previously
recorded overload-hiding refusal there is resolved by explicitly qualifying the
same StringBase<char>::set(buffer,length) it called before; no new overload is added.

All 8 consumer rows retain all 759 bytes.
Ordered runtime sections retain bytes, flags, sizes, relocation graphs, defined
external identities and placements. Local targets compare by section and offset;
SafeSEH symbol indices compare by their resolved handler targets. Private edited
and unedited controls share the original source-file context. Normal native
objects are independently compared with the saved native originals. Private
experiments never write the shared native object cache.

The only linker-directive difference is three VC7-generated template fallbacks
from the existing canonical header. They already occur in the unchanged, native
byte-verified provider objects. Every newly duplicated alias is unreferenced by
the consumer relocation graph, and all remaining directive tokens are unchanged.
alias_guard independently returns ok for less-than and equality; inequality
remains unknown to that checker because the implementation name is only a
ledger object-symbol. This unknown is not turned into a pin, source alias or
proof of a new call route. No guard or baseline is weakened.

The four existing providers are independently gated: AsciiStringNative.cpp,
ascii_string.cpp, AsciiStringDeletingDestructor.cpp and Libraries/Source/string/StringBase.cpp.
Their 174/174 rows and 340 DIR32 fields pass before the change. The first combined
normal gate passes 182/182 rows across all twelve sources, and the final consumer
gate passes 8/8 after the controlled before/after link measurement.

## Reference and prior-work review

BFME 2 reference: f6c3838e7b58025531e09913bc42b810f1a01216, checked within 72 hours.
Reviewed Code/Libraries/Source/WWVegas/WWLib/string_base.h and docs/recipes.md.
The shared template-owner pattern is a lead; BFME 1's own settled header, original
copy/release call relationships and compiler layouts establish its ABI.
No donor RVA, heap layout or compiler directive is imported. The cached older
AsciiString.json contract predates the evidenced BFME inheritance and is not used
to assert the class has no base. Existing native headers and their retail constructor
and destructor evidence take precedence. Selected function attempts and header_queue
entries were reviewed; the old pointer-facade set overload blocker is addressed above.

## Link checks and limits

Original objects against census 1a248a7b47: 6/8 LINKS, 504 LINKED bytes.
Repaired objects against that same index: 6/8 LINKS, 504 LINKED bytes.
No previously linkable unit is lost. Two existing selected-definition/duplicate
blockers remain; this is not a whole-image link or runtime claim.
Staged current-provider preview: 8/8 UNKNOWN, 0/8 LINKS, 0/8 blocked. Unknown results do not authorize LINKED claims.

The new complete census run 43711614660 was in progress at selection time on
7c314a3e6c and completed during this batch. Its full per-file status confirms
the previous expected +450B independently (184B factory plus266B string maker).
See 20261115-450-byte-census-confirmation.md. This current header adoption itself
has no predicted additional linked bytes. Original/final sources, objects, CodeView layouts, alias and
section comparisons are preserved in build/codex-20261115-twohundred/batch-1/.
