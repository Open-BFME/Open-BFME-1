# Corrected bank for RVA 0x001F7B10

This is evidence and a nonmatching bank, not a new ledger or source claim.
The owner chain is independently established in 001f7cc0-clickreaction-owner.md:
ClickReactionBehavior constructor 0x001F7860 installs secondary table VA
0x010A3190 at +0x20; slot 1 contains ILT VA 0x00412134 -> 0x001F7B10.
The primary name getter returns ClickReactionBehavior. No full method name
is witnessed; the former bank's onClick spelling was a behavioral guess.

Retail's 289-byte ledger window ends inside the live body. The code returns
at RVA 0x001F7C4C (+0x13C); three padding bytes align the five-entry jump table
at 0x001F7C50. Its absolute targets are 0x005F7BEE, 0x005F7BF5, 0x005F7BFC,
0x005F7C03 and 0x005F7C0A. The table ends at 0x001F7C64 (+0x154), followed by
12 INT3 bytes. The complete code-and-table extent is therefore 340 bytes.
Linear disassembly warnings at +0x153 decode this proven table as code.

The bank now uses the canonical Object layout and known owner with the
address-qualified method rva001F7B10. The prior apparent status byte at
Object+0x124 is actually inside model-condition word 5. Masks selected by
the switch are 0x04000000 through 0x40000000, not the former bank's 4..0x40.
The getter through ILT 0x000209FA is the matched Rva001BEF20FieldAddress::get,
which returns Object+0x29C; no getStatusPtr identity is asserted. Existing
GetGameLogicRandomValue, Object::notifyModelConditionChanged, and
Drawable::applyPendingModelConditionFlags declarations replace fake callee
names. The filename literal was read from retail VA 0x010A3400.

Module-data +8 and +0xC..+0x1C, and full-object +0x24/+0x28, have witnessed
integer accesses but no lexical field names. The old m_clickTimer,
m_reactionFrames and m_elapsed labels were guesses. New fields retain their
addresses; no semantic field identity is claimed. The unknown AI virtual
interface is an address-qualified slot view, not a guessed class identity.

The best new source emits 340 bytes with 41 differing non-relocation bytes
and normalized instruction shape 0.901. Retail uses ESI for Object and EDI
for module data; the candidate reverses them and schedules their loads
slightly differently. Definition-order, pointer qualification, and volatile
load-order variants preserve the residue; delaying module data until after
the null guard worsens it. The new source also corrects the actual extent,
mask values, owner/receiver, and callee declarations regardless of its score.
The banking tool scores against the still-289-byte ledger window, so its
stored quality is distinct from the full-340-byte probe measurement above.

## Snapshot-bound name-check corrections

The bank still declares ClickReactionBehavior, so pairing that retained class
with rva001F7B10 is false. The old v0 was an unnamed interface filler; the
replacement slot-1 method is named only by its independently witnessed RVA.
ClickReactionBehaviorIface and RvaUpdateModuleIface2 did not have witnessed
lexical interface identities: the new Rva001F7B10Interface explicitly models
only the observed secondary table. RvaUpdateModule becomes a 32-byte opaque
primary-prefix view, without claiming a complete UpdateModule declaration.
RvaObjectModuleBase was an invented name for the pointer loaded from Object
+0x204; the canonical Object header identifies that field as the AI interface,
and the new address-owned view supplies only the slot-96 call ABI.
RvaModuleData was a generic partial header view; Rva001F7B10Data makes its
address provenance explicit. The old RvaDrawable -> Rva001BEF20FieldAddress
pairing is also false: the former setState shim is replaced by the real
Drawable callee, while the latter is a distinct pre-existing matched getter.
Snapshot-bound corrections cover these pairings and the unproven field labels
discussed above. They do not authorize any production identity change.
