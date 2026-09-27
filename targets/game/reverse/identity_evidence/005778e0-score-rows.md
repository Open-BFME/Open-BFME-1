# Score-screen row population at 005778E0

Retail starts at 005778E0 and ends after RET at 00577F46: 1639 contiguous
bytes, followed by INT3. Ghidra's instruction-count extent is three bytes
shorter. The matched caller 005780E0 invokes ILT 000490A8 with its screen
receiver and tests AL. Constructor 00578160 and InitGadgets 00571EC0 establish
the same ScoreScreen owner and persistent-units list box at +310. There is no
evidence for an original method name; the bank uses rva005778E0.

This is the first complete native draft after seventeen blocked verdicts with
no bank. Fresh read-only Ghidra output was checked against retail instructions
and all 23 distinct direct callees. The existing analyzed project's executable
SHA256 is c1a907c44b84df129c1f18dc7365ea25ba438f9b8f39a374b86ed852936ff0a9.
The flow gathers mode-four player-army pointers, looks up each army's object
template, sorts eight-byte (army, template) rows and fills seven list columns.
The previous descriptions of GameSpyGroupRoom copies were misleading ICF names;
the actual stored records are LivingWorldArmy objects and string values.

## Independent layout and ABI witnesses

LivingWorldArmyAssign.cpp and LivingWorldPlayerArmyRva00365630.cpp independently
establish the B4-byte LivingWorldArmy, its getName() at ILT 000041D3, and the
player-army vector at +30. The assignment body corroborates fields +0C, +3C,
+40, +44, AsciiString +4C and UnicodeString +78. Unknown fields retain offsets.
The selected name is the army's +78 string when nonempty, otherwise the
template's +0C string. List-box and portrait APIs use the existing callee
contracts; the campaign manager's +28 pointer supplies the region lookup.

Three address-derived declarations require resolver pins before any future
landing. These are established targets, not missing or invented retail callees:

* GameLogic::rva00388BE0 returns a three-word vector of player-army pointers
  through a hidden stack result, RET4. The complete 33-byte body adds 170 to
  the GameLogic receiver and calls ILT 00031507, then returns the result pointer.
  That ILT reaches the independently authored 340-byte
  BfmeLivingWorldPlayerArmyCollection::collectModeFourArmyPointers at 00364E70.
  Its native source filters the 58-byte player-army records and returns their
  addresses. Main encodes ILT 0000D1E8, independently decoded to 00388BE0.
* Rva00573580Lookup::number(int) uses the complete 158-byte helper at 00573580,
  reached through ILT 0000FD3A. Its hidden AsciiString result plus integer are
  the two stack words consumed by RET8. BfmeNumberedLookupAI.cpp independently
  shows the numeric key formatting and lookup. The new view retains the RVA
  rather than asserting the old BfmeTableAI semantic owner. An inline PMF-return
  adapter was rejected: VC7.1 emitted a separate wrapper even with forceinline.
  A wrapper must not be pinned to this different retail body.
* vector<ScoreRowSortValue>::_M_insert_overflow is the 305-byte native eight-byte
  element implementation at 005740A0, reached through ILT 00037047. The body
  reads three vector pointers, copies exactly two words per element, consumes
  five stack slots and returns RET14. The bank's actual STLport instantiation
  independently matches all 305 bytes with _STLP_NO_EXCEPTIONS=1, consistent
  with the existing OCLUpgradesVectorInsert.cpp ICF owner. All four allocator
  calls resolve. This existing helper adds zero conversion credit.

The remaining address-only ILT adapters have ordinary pointer return values
and inline into their actual retail calls. The AsciiString and UnicodeString
types use existing headers. Native vector ownership and normal string cleanup
reproduce the complete exception structure; no raw vptr, assembly, volatile
shaping, memory barrier or dummy local is used.

## Measurements and exhausted levers

The cleaned preferred bank emits 1639 bytes with two relocation-masked byte
differences: the global campaign load at +3DF selects ECX instead of EDX, and
the following member load at +3E5 consequently uses ECX as its base. Concrete
masked score is 1637/1639 = 0.9987797437461877; normalized instruction structure
is 1.000. These are different metrics. Three unresolved callee declarations
listed above are not masked acceptance and are not yet published pins.

A reference to the army's native vector fixed the initial loop allocation.
Explicit number argument locals reproduced the four string-result call sites.
The final residue survived a bounded 64-toggle rotation sweep plus direct
region calls, manager/campaign locals, pointer/reference/accessor variants,
native row constructors and finite loop/EH variants. No nonmatching source was
installed under game/. Bank before repeating those shapes; another pass needs
a fresh code-generation explanation for the two remaining register bytes.

Scratch receipts: build/round4-score-rows/{retail.txt,callees.txt,helper-proof.txt,
overflow-proof29.txt,probe-bank.txt,rotation29.txt,ghidra/0x005778e0.c}.
Model GPT-6; t=30min. Native conversion credit: zero.
