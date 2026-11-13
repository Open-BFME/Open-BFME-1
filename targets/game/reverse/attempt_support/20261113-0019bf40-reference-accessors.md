# 0x0019BF40: exact primary parser bank, blocked by the Coord3D contract

Runtime model: `openai/gpt-6.1-sol:high`; BFME I input
`72cdedeab4bda93ec099f6454b92cc568a8e7b96`. No production source,
function ledger, header, type contract, pin or datum is changed.

## Measured improvement

The prior bank, after removing its obsolete duplicate AsciiString destructor
and using the already-existing explicit-vptr parser-registration view, compiles
to **1195/1197 bytes, 47 relocations, 209 masked byte differences, frame D8**.
The explicit-vptr view alone is byte-neutral; it comes from
`game/GameEngine/Source/Common/Rva00352810ParserRegistrationCtor.cpp` and
`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptListParseScriptListDataChunk.cpp`.
No novel vtable or virtual-destructor identity is inferred.

The stronger candidate is preserved at
`targets/game/reverse/attempt_support/20261113-0019bf40-exact-candidate.cpp.txt`.
`re_log.py --stash` refused to update the preferred bank because remeasurement
of the retained old source fails on its obsolete duplicate AsciiString destructor
(C2264). The old preferred bank is untouched; a normal `blocked` verdict cites
this tracked candidate. No tool or string-class repair was attempted.
The primary body is **1197/1197 bytes, 47 relocations, zero masked differences**.
This diagnostic is not strict relocation/identity/link admission. The existing
bank spelling `parseSidesDataChunk` is historical; native evidence establishes
the bound parser's role/receiver but not that original member spelling.
Any eventual production identity must remain address-qualified unless separately
established. **Accepted source gain: zero**, not 1197 bytes.

These genuine reference expressions, not filler temporaries, resolved the draft:

| Change from prior bank | Primary result |
|---|---|
| Existing explicit-vptr registration view | 1195B / 209 differences / D8 frame, neutral |
| `if (version < 5) { scripts array; registration; parse; handoff; }` instead of early return plus function-scope array | 1195B / 179 differences / **CC frame** |
| Reference Bool setter parameters instead of assigning normalized bytes directly | 1195B / 168 differences / D8 frame |
| Above scope + Bool setters | 1195B / 138 differences / CC frame |
| Above + `getNumSides()` in outer script-loop guard | **1197B** / 16 differences |
| Above + `getScriptList()` / `setScriptList()` reference accessors | 1197B / 2 differences at +2BC/+2C0 |
| Above + BuildListInfo `getNext()` / `setNextBuildList()` reference accessors | **1197B / zero masked differences** |

Negative controls: member bool types alone are neutral; getter if/nested-if,
script pointer local, index declaration and shared index are neutral. A throwing
getter diagnostic is not semantically compatible with the native nullable getter
and was rejected, not banked. See the preserved generating helpers and the
private `build/spike3/{parser-variants,parser-tail-variants}/results.json`.

The pre-v5 lexical scope and accessor expressions are witnessed by pinned BFME 2
`76f0baefa6f285d54bc1ca922397674312a5913f`,
`Code/GameEngine/Source/GameLogic/Map/SidesListDataChunks.cpp` (SHA256
`1e3d8acc41979ef173d68a85121e230383e8d27817fabffa464ebaeb2156eb61`), and
Zero Hour `GeneralsMD/Code/GameEngine/{Source/GameLogic/Map/SidesList.cpp,Include/GameLogic/SidesList.h}`.
BFME 2's new scratch SidesList/swap, 20-side limit and wider records do not apply
to BFME I. Only the evidenced expressions/lexical context were adapted.
The mirror lacks `.git`; its enclosing-repository revision is not donor identity.

## Native identity and extent

Retain `identity_evidence/0019bf40-sideslist-bound-parser.md`: map-loading
registration at VA 0x0074AE99 binds SidesList string VA 0x0109C1E4, receiver
from VA 0x012EF428, ILT RVA 0x00043C93 and adjustment zero. Table VA
0x0109BFD4 -> invoker RVA 0x00192120 and callback RVA 0x001028D0 forward
that receiver plus file/info. Native RET8 at RVA 0x0019C3EA and INT3 at
0x0019C3ED bound 1197 bytes. This is not identity inferred from a nearby table.
The side/BuildListInfo offsets are supported by the matched constructor and
adjacent matched side/team consumers, not by donor offsets alone.

The parser and native BuildListInfo constructor show location at +0x0C;
name_oracle currently reports `m_location+0x8` for a +0x0C query. Record that
contradiction, do not rename the class or edit the oracle to evade it.

## Admission blocker, investigated without exceptions

The old bank privately defines `struct Coord3D` with a nontrivial copy ctor and
no nontrivial destructor. `class_gate.py` correctly refuses that new private
view and requires `game/Libraries/Include/Lib/Coord3D.h` (canonical POD).
No allow comment, contract edit, typedef rename or header modification was made.

Actual header trials after the expression repairs:

* Canonical POD include: **1181B, 616 masked differences, C0 frame**, 47 relocs.
  The initial C1083 used a missing include-search prefix; the corrected trial
  adds the actual canonical include directory and compiles. C1083 is setup,
  not type evidence.
* Existing `WWMath/coord3d.h`, unchanged and without private inline overrides:
  **1250B, 783 masked differences, CC frame**, 52 relocs. It emits unresolved
  default ctor, copy ctor, assignment and dtor calls. Its class-return/argument
  mangling uses `VCoord3D` and `ABV0`, whereas the existing BuildListInfo
  setLocation row is `UCoord3D` and the exact bank emits `ABU0` for its copy ctor.
  Same 12-byte storage is not the same class/ABI/lifetime contract.
* Both exact bank and canonical POD emit a **26B, zero-relocation, exact**
  `?setLocation@BuildListInfo@@QAEXUCoord3D@@@Z` against matched RVA 0x000C8F10.
  This rules out the proposed trivial/nontrivial setter ABI mismatch; it does
  not establish that the private copy ctor is an admissible canonical contract.

A one-off `setNextBuildList` diagnostic accidentally used nearby RVA 0x00191480
without a ledger identity; it measures a jump stub and is **invalid evidence**,
not a provider mismatch or claim. Do not reuse that address.

The primary exactness therefore does not authorize source promotion. Parent
approved existing-header scratch investigation only, not a classwide repair or
exception. No native image was executed, and no provider-link closure is claimed.
Raw complete exact-object COFF sections/symbol auxiliaries/publics/relocations
are retained in `build/spike3/parser-exact-coff-graph.log` (37531 bytes);
this is inventory, not a passed coexistence/selection proof. The current census
is absent. Whole closure/scaffolding delta is NULL/unknown.

## Reproduction and resume

Every project import/compiler/helper entered external
`/home/pispike/qa/bfme-spike3-20261113/game.sh` before importing tools; private
objects were freshly compiled. No old object or receipt was copied. Scratch
include-directory stability caused cache refusal, not failed compilation.

Logs: `build/spike3/sides-parser-{repro,provider-view,scope-setters,accessors,canonical,wwmath,wwmath-symbols}.log`,
`build/spike3/parser-setlocation-{provider,canonical}.log`,
`build/spike3/parser-bank-tool-refusal.{log,exit}`, and the complete COFF
inventory above. Helpers are preserved with this handoff as `.py.txt`.

Resume on an independently established, normally admissible coordinate type/
lifetime contract or a source-level explanation using the current canonical
POD that preserves real semantics. Do not copy extra WWMath method bodies,
redeclare Coord3D or add noise just to regain the primary bytes. No repeat of
the older coordinate/frame/exception sweeps is justified by this bank.
