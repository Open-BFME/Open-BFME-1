# RVA0049BA80: extent and physical ABI evidence

No original owner identity or semantic member names are claimed. The entry
retains its address in Rva0049BA80Owner::rva0049ba80. The bank supplied the
source hypothesis; independent retail instruction decoding supplies the proof.

## Extent and entry contract

RVA0049BA80 is292 bytes, endingRET8 at0049BBA1..0049BBA4 followed byINT3
padding. It receives a receiver inECX, an opaque object pointer in stackslot1,
and a boolean lowbyte in stackslot2. It conditionally writes receiver+0x148.
All six direct call operands resolve exactly in the strict byte gate.

## The virtual call at0049BB0F

After the direct contain-query call at0049BAFE returns, TEST EAX,EAX branches
away onnull. MOV EDX,[EAX] at0049BB0B reads that returned object's vptr;
MOV ECX,EAX at0049BB0D establishes that same pointer as receiver; CALL
[EDX+0xD8] at0049BB0F pushes no argument words. XOR AL,[ESP+0x10] at0049BB15,
NEG AL and SBB EAX,EAX subsequently consume only the lowbyte boolean result.
Thus Rva0049BA80SlotD8View is solely a borrowed ABI view with one no-stack-arg
bool operation at vtableoffsetD8. Its unused declarations describe slotspacing,
not proven signatures. No owning concrete type, method meaning, constructor,
destructor or lifetime operation is asserted. No synthetic parent induces ABI.

The former bank redefined existing BfmeX1004 with55slots, although an authored
TU defines that legacy type with39slots. That incompatible definition is removed:
BfmeX1004 is only forward-declared as the existing callee's return name, then the
separate address-derived slotview supplies the one independently proven call.

## Five helper contracts independently decoded

| Retail call route | Existing declaration | Physical contract |
| --- | --- | --- |
| ILT000209FA ->001BEF20 (7B) | BFMEWeaponSetOwner::getWeaponSetFlags legacy view | ECXreceiver, no stackarguments; LEA EAX,[ECX+29C],RET. Caller reads one32-bit word at returnedaddress. No weapon semantic identity inferred from alias. |
| ILT00035995 ->001CB0C0 (119B) | RvaC4390Second::resolve(int) | ECXreceiver, one stackargument tested as lowbyte; fullEAX nullable pointer return,RET4. Existing canonical return is struct RvaC4390First (PAU), so bank's class forwarddecl (PAV) was corrected. |
| ILT0000D3B9 ->001BFE20 (18B) | BfmeHold1004::bfmeFind1004 legacy view | ECXreceiver, no stackarguments; receiver+1FC pointer is checked, null returns0, else taildispatches its vtable+68; fullEAX nullable borrowed pointer. Matches existing Object::unidentified_001BFE20 opaque result and its vtable witness. |
| ILT000016A4 ->000C4D40 (41B) | BFMEActionObject::testStatus(int) legacy view | ECXreceiver, one32-bit bitindex, bitarrayat90; fullEAX exactly0/1,RET4. Caller consumesAL, so existing bool declaration is physically compatible. |
| ILT0003AB20 ->000D3F10 (41B), two calls | BFMESelectionStatusBits::test(unsigned) legacy view | ECXreceiver, one32-bit bitindex, bitarrayat110; fullEAX exactly0/1,RET4. Caller consumesAL, so existing bool declaration is physically compatible. |

These pre-existing aliases are not newly proposed identities. No pin address,
body identity or shared declaration is changed. pin_consistency reports the
accessor, contain-query and resolver routes consistent with their matched owners.
The readonly accessor at1BEF20 remains address-derived; the contain query's
opaque result remains opaque. Existing ObjectTeamAndPlayer.cpp independently
records the contain module's+68 query and returned subobject vtable witnesses.

None of these placeholder types is declared in canonical game/reference headers;
no covered type is redeclared. No shared header or generated source is edited.

## Reproduction artifacts

Independent full retail and helper disassembly:
build/0049ba80_abi_extent.txt in the isolated conversion clone.
Strict scratch comparison: build/0049ba80_strict.log,1/1 exact292B,6REL32,
DIR32zero references, no-op patchpass. The official source-scoped add_match/build
must pass before publication; scratch instruction/shape scores alone are not proof.
