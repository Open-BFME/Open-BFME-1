# ScoreScreen single-player population: complete bank, not a conversion

Retail RVA `00575B70` spans 3,413 bytes, ending immediately after the `RET` at
`005768C4`. The matched `_bfme_showScoreScreen` caller at `005775FC` reaches this
body through ILT `0003D08C`. Ghidra reports 3,400 decoded bytes; that count omits
alignment and is not the contiguous extent. The executable SHA256 is
`c1a907c44b84df129c1f18dc7365ea25ba438f9b8f39a374b86ed852936ff0a9`.

The old bank emitted 2,329 bytes and called six helpers absent from retail. The
new bank supplies the entire observed flow using canonical strings and native
STLport containers. Fresh read-only Ghidra, decoded calls, and the now-landed
ScoreScreen constructor provide the evidence below. Field labels retain their
offsets where no stronger name was witnessed.

* Seven count/multiplier/product triples begin at screen `+294`. The original
  draft multiplied the wrong two words. The multiplier pointer is at `+298`;
  each product uses its preceding count and its own multiplier.
* The objective count is called again on each loop test. Eligibility, indexing,
  completion and name calls are the existing CampaignManager methods. The name
  return is passed directly by value to GameText virtual slot `+24`.
* GameLogic `00388BE0` returns an owned 12-byte vector of player-army pointers
  through a hidden result pointer. Each player-army has a vector at `+30`; its
  elements have `B4` stride, name getter `00361900`, and a flag byte at `+39`.
  Template lookup is `00137E80`, portrait lookup is `0013EEC0`. Templates with
  bit `02000000` at `+D0` produce 12-byte hero records: key from `+4D0`, flag,
  then image. The record writes only its flag byte, leaving ordinary padding.
* Sorting uses the already-owned signed first-word comparator and the decoded
  introsort, insertion-sort and unguarded-insertion helpers. No invented sorter
  replaces those calls. Screen `+2E8` is the native vector<bool> witnessed by
  constructor `00578160`; retail erases its full range via bit-iterator `__copy`
  (`002CAF40`, encoded through `0000F682`), then pushes each sorted hero flag.
* Two Unicode strings remain alive through the tail. Text is translated from
  number helper `00573580`, prefixed with `L"x "`, and concatenated using the
  existing StringBase header and static null character. Screen `+300` is an
  AsciiString copied from player `+28`, not the old draft's UnicodeString.
* Region lookup is `003C8A50`. Score setter `000E8900` stores the region's
  `+78/+7C/+80` values into score `+12C/+130/+134`. The nine `00573C20` calls
  have three integer stack arguments. Each label's observed construction and
  destruction precedes or follows the corresponding fetch/image call.

## Independently recovered score-record contract

Getter `000E95A0` returns a 12-byte value whose first word is an owned
UnicodeString and whose remaining words come from owner `+2EC/+2F0`.
The first member is copied from `+2E8` through actual Unicode base constructor
`00888400`. It returns the hidden buffer in EAX and uses `RET 4`.
The bank's ordinary `return field2e8;` produces all 49 bytes (relocations masked),
including the local construction-state store; no dummy or volatile local is
needed. The old native helper's explicit output pointer is an ABI-compatible
view, but its extra volatile local is not needed by the actual return shape.

Receiver `003C0E60` consumes the complete 12-byte record by value (`RET 0C`).
It owns a list at `+C0`, allocates a 20-byte node through `0082E540`, copies the
record using `_Construct` at `003BE7C0` via ILT `000365CA`, appends before the
sentinel, and destroys the string in the by-value argument. Native
`fieldc0.push_back(value)` produces all 112 bytes (relocations masked).
`push_front` instead adds an extra sentinel dereference and is refuted.
The record getter and list receiver are already-owned bodies: zero new credit.

## Residue and next lever

Preferred main body: **3,397 / 3,413 bytes**, frame `54` versus `50`, 147
relocations, 2,109 differing masked positions, and 16 missing tail positions.
The positional byte score is **1,288 / 3,413 = 0.377380603575**. Normalized
instruction shape is **0.975** and must not be reported as byte match accuracy.
The old draft's author score was 0.35. This replaces its missing behavior; it
is not an accepted game source.

Strict resolution still lists five declarations requiring ownership work:

| Declaration | Independently decoded real target |
|---|---|
| vector<S4SortElem12> insert overflow | `00573DB0` / 314B; native sibling body and argument sequence |
| Rva00573580Lookup::number | `00573580` / 158B; score-row bank's independent hidden-return proof |
| GameLogic::rva00388BE0 | `00388BE0` / 33B; score-row bank's vector-return proof |
| Rva000E95A0Owner::value | `000E95A0` / 49B; independently reproduced above |
| Rva003C0E60Owner::insert | `003C0E60` / 112B; independently reproduced above |

No pins were added. These are actual decoded targets, not substitutes for
missing behavior. Remaining instruction differences concern bit-iterator
materialization, frame/local allocation, live registers and EH scheduling.
Explicit UI-key scopes recover retail's ordering. Counted loops, native STL
exception mode, empty/stateful comparator forms and twelve finite EH/loop
combinations were tested. The selected body retains canonical member types;
no assembly, fabricated stack padding, volatile scheduling or artificial
throw declarations were added. A later attempt needs new iterator/lifetime
or source evidence, not a repeat of those variants.

Session: GPT-6, approximately 30 minutes. All experiments remain under build/;
only the preferred bank and evidence are published. This investigation adds
**zero** rebuildable native bytes.

## Name-checker correction records

The existing bank did not establish `BfmeTableAI` as a real class. Its
`bfmeNumberedAI` declaration was a guessed view of the decoded `00573580`
number-string helper; `Rva00573580Lookup` retains that independently witnessed
address. The separate new `Rva000E95A0Value` is the 12-byte record proven above,
not a renaming of that old table view. The checker aligned both declarations
with `BfmeTableAI` because this substantially rewritten TU changed ordering.

`LivingWorldArmy` still exists under exactly that name with the witnessed B4
layout; its pairing with the unrelated `Rva00573580Lookup` is another token
alignment artifact. Old `Registry::findTemplate` was also not a real registered
identity: its by-value AsciiString argument contradicted lookup `00137E80`'s
const-reference contract. The new factory call uses the same existing typed
factory view as the score-row bank. It has no relationship to the objective
span-count owner `Rva003BDF70Owner` with which the checker paired it.

Finally, old `objectiveName` is replaced by the actual existing ledger/native
method `CampaignManager::rva003BF580`, reached by decoded ILT `000459DA`.
The old spelling was never a proved symbol for the target. No established
function or class identity is discarded by these five correction records;
each record is limited to the exact old/new source hashes.
