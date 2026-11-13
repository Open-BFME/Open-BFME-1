# PolygonTriggers base parser: bounded canonical-contract feasibility

Status: **not production-ready**. No production source, header, type contract, ledger,
pin or datum changed. No new parser draft was compiled. The proposed header is
`build/spike3/PolygonTrigger.h.txt`, deliberately uncompiled and outside build inputs.
Original lease `0x00190700=ccea8f4fe3314743be4f08867bac4344` was released through normal claims.release with the exact lease-resolved token78ebe122fcc2744e01457d853861bc6fb6885274 at2026-11-13T11:19Z. Parent authorized banking, not wider production reconciliation.
Donor: pinned `76f0baefa6f285d54bc1ca922397674312a5913f`.

## Independent target facts

`polygon-native-contract.log` proves `[00190700,00190C9E)` is **1438 bytes, all
non-CC**, SHA256 `cf418a3e6b4db037faa5c28e011c13e59b9015128537910661d285c4ae283c6d`.
RET 8 is at 00190C9B; INT3 starts 00190C9E. The queue's 1432 is not used.
Base parser table VA0109BFB0 slot1 -> ILT00013B10 ->00190700. Derived table
VA0109BFBC slot1 ->ILT00022F02 ->00190F10. Its matched wrapper pushes two
arguments at 00190F32/33, retains ECX, calls that guard, tests AL.

The parser allocates 0x88 at 00190A14 and calls constructor001903F0 through
ILT00024B4A with the read integer ID and `pointCount+1`. EAX is retained as ESI;
all the following stores use that same, **unadjusted** object:

| Offset | Native evidence | Defensible representation |
|---|---|---|
| 04 | ctor zero; wrapper list threading | next pointer |
| 08 / 34 | ctor zero/EH + parser StringBase<char>::set | two AsciiStrings |
| 0C | ID read/ctor write/wrapper maximum scan | int ID |
| 10/14/18 | parser point loop + existing grow/append | int3 pointer/count/capacity |
| 1C..2C / 30 | matched updateBounds + name_oracle witnesses | four int bounds, float radius, dirty byte |
| 32 | normalized version>=2 byte;00190B82 store | bool |
| 40 / 44 | normalized version>=3 byte and readInt;00190B8F/98 | bool / int |
| 48..5C | six-element ctor/dtor callbacks, indexed setter, parser loop | six AsciiStrings |
| 60 | normalized version>=5 byte;00190B0D store | bool; not the version>=3 river flag |
| 64/68/6C | packed RGB unpack, FILD/FMUL/FSTP;00190AE3..AF0 | three floats |
| 70/74/7C | three readReal calls0019096F/7A/85, FSTP locals,00190B26/33/3C copies | three floats |

The full existing initializer at
`game/GameEngineDevice/Source/W3DDevice/GameClient/Water/Rva001901F0WaterTextureInit.cpp`
already models these tail fields as floats. So this is **not** a new guessed
layout discovered only from donor source. Existing BfmeOwnVVB constructor/wrapper
views obscure the tail with padding instead.

## The integer-setter conflict is explained, not cast away

Native readReal001027B0 returns through `FLD [esp+4]` at001027DA (ST0), followed
by RET at001027E0. The parser immediately FSTPs each result, then copies those
representations into 70/74/7C. There is no receiver adjustment between the
constructor return and these stores.

This explicitly corrects the earlier supervisory getter hypothesis. 0018F2E0 is a **void setter**, not an integer getter: dirty OR, MOV stack word,
MOV [ECX+74], RET4. The existing Gen_0018F210::setRiverStart(int) declaration is
therefore not evidence for an int field. Likewise S3SplitTails.cpp's comment
that a MOV setter implies int rather than float is disproved by an existing
matched counterexample: ExperienceTracker::bfmeSetCurrentExperience(float),
001B2060, is MOV EAX,[ESP+4]; MOV [ECX+C],EAX; RET4. Its own existing evidence
cites x87-stored float callers. **This does not justify changing a getter to a
float return.** No +74 getter was identified in the inspected native member
range; no EAX-return getter is relabeled as ST0. Native callers_of reports no
named callers for0018F2C0/2E0/290; that is not global reachability proof.

The filtered native writer00191110 independently serializes the flags, RGB,
and real data from this record. Its existing source writes field70 **twice**,
not70 then74; retain the target behavior rather than 'fixing' it from a schema.

## Construction, ancestry and callback blockers

Both constructors and complete destructor install VA0109BFAC, whose only slot
routes through ILT000116DA to scalar-deleting destructor00191380; the next table
starts0109BFB0. No RTTI descriptor is present immediately before this table;
searches for the PolygonTrigger/BfmeOwnVVB class-key RTTI literals found none.
Constructor and destructor EH each have three states: string+8, string+34,
six-element string-array+48, stride4. Callback ILTs are00017BD9->00062030
(default ctor) and0000D828->0005EE90 (destructor).

Consequences still needing proof before a canonical header can land:
- Current constructor declarations take `void*` for what the native caller and
  initializer use as a count. A coherent header requires int count, changing
  decorated ctor/init symbols and existing caller declarations/pins.
- Six BfmeElemBX/retail-string aliases must become the existing canonical
  AsciiString representation **without losing native callback ILT bindings**.
  Real canonical providers do exist: ??0AsciiString,62030/export17BD9 in
  GameEngine/Source/Common/System/AsciiString.cpp; ??1AsciiString,5EE90/exportD828
  in Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp. No library edit is
  proposed. Their current ledger/provider existence is not a fresh constructor
  consumer/relocation/physical-selection check; normal proof remains necessary.
- The original base ancestry is **not settled**. The current ctor uses a
  nonvirtual node-list base; its zero-before-vptr order does not independently
  prove that C++ ancestry. The ZH MemoryPoolObject+Snapshot bases cannot simply
  be imported: their extra virtual slots disagree with this one-slot table.
- `class` and natural alignment4 are carried from current source/toolchain
  contracts, not independently recovered original RTTI. Heap allocation88
  does not by itself prove alignment or rule out an empty/base alternative.
- No cached current object exists for these provider TUs in this worktree;
  no new compilation was performed under the read-only feasibility amendment.

## One proposal and its real scope

Propose one BFME1 canonical `game/GameEngine/Include/GameLogic/PolygonTrigger.h`,
retaining the already-used PolygonTrigger class spelling and canonical
AsciiString, with native88-byte layout. `PolygonTrigger.h.txt` is the one
layout draft, **not an assertion that the no-base form is proven**. Its primitive
bounds/color arrays assert scalar storage only, not original EA aggregate types.
Naming oracle corroborates points/bounds/radius/dirty offsets; new tail roles
remain offset-named. Do not import BFME2 virtual inheritance or its modern parser.

Inventory: `polygon-view-inventory.json` records source hashes and exact matched
row cohorts for **50 named-private-view TUs plus20 direct ZH-header consumers,
69 unique TUs /1145 matched rows /92901 raw row bytes**. These are review/gate
exposure counts, not unique bytes or progress. Five of those private-view TUs
also redeclare string classes; canonical adoption would require additional
string-consumer reconciliation. Transitive header consumers and unnamed alias
views are not exhaustively proven by this direct inventory.

Mandatory affected sources include BfmeOwnVVBConstructors/Destructor/DeletingDestructor,
PolygonTriggerRva00190F10, Rva001901F0WaterTextureInit, Rva00190590AsciiArraySetter,
BfmeConv740, Bfme5SmallAccessors, S3SplitTails, Bfme5TinyTwentyTwo,
Bfme5IndexedVector3{Grow,Setter,Insert}, Gen00375590PlayerObjectCreate,
PolygonTrigger_pointInTrigger, and the filtered writer. The inventory also
includes AICommandParmsStorageXfer/AIStates, requiring parent-owned cross-lane
coordination. Unifying currently distinct owner names requires normal naming,
ledger and pin tools, not typedefs, aliases or another private projection.
A registered/shared header costs the full normal hook gate, plus all affected
providers/consumers and actual bounded linking. No timing measurement or closure
claim is made; the project's usual40-60min full-gate estimate is not a run here.

## Donor distinctions and failed setup

Reviewed donor OldPolygonTrigger.cpp and Common/Rva00328E96WaterRecord.cpp supply
version>=5 six-texture/real structure, but are **not exact BFME1 semantics**:
BFME1 takes initial RGB and color-enabled defaults from the final water override
before the record loop; the donor helper's old-version branch hardcodes white
and false. BFME1's two scalar defaults are `0x3D75C290`, not an assumed `0.06f`.
The array lives outside the loop (eight parser EH states); the modern BFME2
parser is unrelated in shape. Do not reuse donor read barriers/dead-EH code.

The normal private donor trial88e581c5bf3d44caa810abe23c552c0b was **refused**
with `header dependency set changed during trial`. Its emitted object has not
been reused, admitted or treated as a valid cached trial. This refusal is not a
body-mismatch verdict. No override/tool patch was made.

## Banked disposition

The native field/type prerequisite is now much better constrained, including a
concrete refutation of the integer-store inference. Production reconciliation
is nevertheless materially wider than adding the parser: original ancestry,
canonical callback routing, ctor-count symbols, canonical string adoption and
full transitive consumers remain unresolved. Recommend bank this prerequisite
rather than authorize a speculative header or raw-offset workaround. Only a
specifically approved shared canonical/naming/provider reconciliation should
resume it. Current source gain and global/native closure remain0 / unknown.

## Durable artifacts and replay

The adjacent `20261113-00190700-PolygonTrigger.h.txt` is NONADMISSIBLE; do not install it.
Adjacent native-contract, contract-inventory and view-inventory `.py.txt` files
are inspection helpers, not game bodies. Run copied helpers only through the
experiment guard (or the subsequently approved project environment). The view
inventory consumes native `rg -l` results for class/struct bodies named
PolygonTrigger, BfmeOwnVVB, Gen_0018F210, Gen_0018f2c0, Gen_0018F290,
Rva001901F0, Rva00190560, Rva00190590, plus direct PolygonTrigger.h includes,
under game/GameEngine and game/GameEngineDevice. `.sources.tsv` preserves
all69 source hashes/cohort counts; the full row lists remain in the private JSON.
No production edits, new header admission, naming/pin changes, native image
execution, linked-image proof or source gain are authorized by this bank.
