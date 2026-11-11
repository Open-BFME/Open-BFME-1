# DataChunk parser callers: native byte and parser-registration bindings

## Scope and unchanged owners

Four existing consumer units reconcile two obsolete external declarations with
existing native providers; no provider, shared header, ledger, pin, alias or
baseline changes. No function identity or new matched bytes are claimed.

| Consumer | Existing rows checked | Repaired sites |
| --- | --- | --- |
| ScriptRva0035C0C0Parse.cpp | 1 | 6 readByte + 3 registerParser |
| OrCondition_ParseOrConditionDataChunk_Thunk.cpp | 2 | 1 registerParser |
| WaterRenderObjReadSkyBoxSettings.cpp | 6 | 1 registerParser |
| Rva0019A470ChunkParser.cpp | 1 | 4 readByte |

Consumers remain at their current game/GameEngine/Source/GameLogic/ScriptEngine,
game/GameEngineDevice/Source/W3DDevice/GameClient/Water, and
 game/GameEngine/Source/GameLogic/Map paths. The full source list is recorded in
build/sol12h-bindings/datachunk-consumers.txt. Only existing per-unit method
declarations and byte reads change. There is no native BFME1 DataChunk.h under
game/GameEngine/Include; the Zero Hour header's void registration declaration
contradicts the established BFME1 provider return, so it is not imported.

## Primary BFME1 evidence

* `?readByte@DataChunkInput@@QAEDXZ`: existing48B row at RVA00102830 in
  game/GameEngine/Source/Common/System/DataChunk.cpp. The source's Byte alias
  emits plain-char return mangling D, not the obsolete unsigned-byte E spelling
  `?bfmeReadByte@DataChunkInput@@QAEEXZ`. Its complete native body reads one byte,
  adjusts chunk accounting, returns AL, and ends RET with no explicit arguments.
* `?registerParser@DataChunkInput@@QAEPAVUserParser@@ABVAsciiString@@0P6A_NAAV1@PAUDataChunkInfo@@PAX@Z3@Z`:
  existing113B row at RVA00103840 in
  game/GameEngine/Source/Common/System/DataChunkInput.cpp. It returns the newly
  allocated UserParser pointer in EAX, unlike the old QAEX void declaration.
  BFME1 source and target establish allocation size1C, intrusive node previous
  link at+8, parser-list head at this+18, and RET10 for four stack arguments.
  Prior re_log evidence43804 already records removal of the obsolete void
  provider and preservation of this native provider; no provider is recreated.

The six Script byte results are only tested against zero, so byte signedness
cannot affect their truth values. The four map-record results explicitly cast
the native char back to the consumer's existing unsigned Byte type, preserving
its raw-byte contract. All registration return pointers remain unused; this
changes only the external spelling, not receiver, arguments or caller code.

Existing Script class/address-keyed method evidence remains
0035c0c0-parse-script-instance-method.md; its instance layout, child callbacks
and method name are unchanged. The other consumers' private payload classes,
callbacks, data roots and existing independent identity/selection debt are not
reinterpreted or repaired here. No disputed gadget getter/provider is involved.

## Exact native bindings, not a spelling-only inference

The saved verified before/after objects have IDENTICAL external definition sets
in every consumer. Their undefined sets differ only by the two intended native
spelling substitutions: two in Script, one in each other unit. No new helper,
COMDAT provider, facade or out-of-line definition is emitted.

All10consumer rows are strict/unmasked byte-identical, with no unresolved patch
references. Every repaired REL32 operand keeps its original ILT and native body:

| Root RVA | REL32 operand offsets | Native route |
| --- | --- | --- |
| 0035C0C0 | A7,B9,C8,D7,E6,F5 | 0000C234 -> 00102830 |
| 0035C0C0 | 150,1AC,208 | 00015BD1 -> 00103840 |
| 0035B700 | 7D | 00015BD1 -> 00103840 |
| 007A6120 | 48 | 00015BD1 -> 00103840 |
| 0019A470 | 12F,187,197,1A7 | 0000C234 -> 00102830 |

The check asserts each physical E9 thunk destination, all15sites, both complete
native provider byte streams and their RET/RET10 cleanup. Existing DIR32 roots,
including callback addresses and the OrCondition vtable, remain verified.
This does not depend on selecting a same-byte tiny getter or an ICF assumption.

Reproduce with the unchanged normal build command for the four consumers plus
both provider files, then
`python3 build/sol12h-bindings/check_datachunk_routes.py`.
The script and archived verified before/after objects are lane-private evidence,
not replacements for normal build receipts. Exact outcomes:58/58functions,
9literals,7empty-string refs and41DIR32 references, zero baselined body-guard
findings. Existing unwind labels resolve through the normal gate despite
renumbering; no EH-state or data pins change. The final normal gate was rerun
after a separate before-state link preview and reapplication of this same patch.

## Reference sweep and build context

Read-only BFME2 pin76f0baefa6f285d54bc1ca922397674312a5913f was reviewed at
Code/GameEngine/Include/Common/DataChunk.h and the matching Common/System
DataChunkInput.cpp/ScriptEngine sources. The BFME2 native header likewise
returns UserParser*, but readByte is UNSIGNED there, unlike BFME1's native
plain-char mangling. This ABI difference is reconciled from BFME1 evidence,
not copied from donor declarations. BFME2's current Scripts.cpp is a different
source shape; no donor body, layout, flag, include or build dependency is
imported. Available shallow history exposes the pinned census snapshot, not
an independent donor repair history; no such historical proof is asserted.
The donor gitlink remains unchanged.

Compiler context is the existing source //cl directives, unchanged, and MSVC7.1
under supervisor-approved lane-private Wine11.16 WoW64, WINEARCH=win64 and
BUILD_POOL=2. Private original objects were copied BEFORE rebuilding the edits.
Artifacts under build/sol12h-bindings/datachunk-* include source/object snapshots,
callee output, claims, normal before/after/final gates, native-route assertions
and actual before/current link previews. Before preview used restored original
sources, not a substituted diagnostic object; its cold-cache result was0of6
clean in232.7seconds with22782unavailable/currentness-changed ledger objects.
That preview is not a census refresh or confirmed linked-byte measurement.

Actual after-preview:0of6clean in235.3seconds, same22782unavailable/currentness-
changed objects. Script and the map parser are UNKNOWN; OrCondition, Water and
both providers retain their independent debt. The explicit diagnostic-set
comparison adds ZERO new blockers and removes exactly the five obsolete
undefined-spelling diagnostics (two Script, one each other unit). This is
caller-edge repair only: no current unit or unique linked-byte gain is claimed.
