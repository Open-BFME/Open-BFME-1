# Selection callback 00532280: native helper visibility

2026-10-03, n2, model=gpt-6-astra.

The existing matched wrappers 005329C0 and 005329E0 call ILT 00047807
with the same ECX receiver and two stack arguments: object, then action 2
or 3. Their native source names Rva005329Classify::classify; this recovery
retains that address-qualified identity, without assigning a screen name.

Retail ends the code with RET 8 at 00532439 (+1B9). Four little-endian
switch targets at 0053243C..0053244B are VA 00932310, 00932330,
009323AE and 009323BF. INT3 starts at 0053244C. The established claim
is therefore 460 bytes including the 16-byte switch table. Ghidra's initial
function creation follows only 276 bytes before the indirect switch; it is
not the boundary proof. Raw baseline decoding supplies the complete extent.

The preferred bank emitted 460 bytes with five differences at +49..+58:
it loaded the vector begin into ECX, branched directly past a destructor
reload on the empty path, and copied ECX to EBX before the loop. Retail
loads EBX directly, branches to the reload, and jumps across the loop pad.
Putting the actual selection helper definition in this translation unit,
with noinline, makes the callback exact modulo its 25 relocations. No
volatile access, barrier, invented helper behavior or compiler flag change
is needed. A free-function helper declaration produced 29 differences;
a visible free helper produced 452 bytes. A member-pointer adapter to that
free helper retained the original five differences. The visible member
view reproduces both bodies: caller 460 bytes, helper 171 bytes.

## Existing selection helper and calling convention

The call at caller +3C reaches ILT 0001BFEA, whose E9 reaches 00531DE0.
The caller explicitly restores its original receiver into ECX at +36 before
the call. The helper itself does not read incoming ECX: its first ECX write
is MOV ECX,[ESI] at helper +12, after the cdecl list-box count call. Its two
stack arguments are the list box and the vector pointer. It returns the
vector size in EAX and ends RET 8 at +A8, followed by INT3 at +AB.
Ghidra independently creates a 171-byte function and corroborates this
vector-clear/selected-index append behavior.

The complete helper source is the existing verified
Rva00531DE0Selection.cpp algorithm: erase(begin,end), request the selection
array only for nonzero entry count, stop on a negative selected index, and
append native int elements. Its retail calls are:

- 00010857 -> 004B77C0, GadgetListBoxGetNumEntries;
- 00008945 -> 004B77E0, GadgetListBoxGetSelected;
- 0003B075 -> 000BBE70, native vector<int> insertion overflow;
- IAT VA 0135945C, MSVCR71.dll memmove.

The body is now emitted through an address-qualified receiver view whose
receiver is unused. This retains the caller's witnessed ECX setup while
exposing the genuine body to MSVC. The existing address-derived ledger name
and extent are retained; object-symbol names the member emitter. This is an
ABI view of the same verified body, not another semantic identity. The strict
caller resolver does not use
object-symbol aliases as callee bindings, so one pin maps this independently
verified member emitter to physical body 00531DE0. No ILT alias is added.
Ordinary stdcall callers remain compatible because the body does
not consume ECX. Only the two existing stack arguments are popped.

The caller uses the canonical string headers and native STLport vector.
The opaque player record's field at +14 remains field14; the bank's
profile-ID spelling is not asserted as an independently proven field name.

## Strict verification

The scoped add_match gate passes both bodies (2/2) and all eight recorded
DIR32 references. Pin consistency passes after the single emitter binding.
The previous standalone selection source is removed after rehoming its sole
ledger row; no second body claim is introduced.

## Bank helper names

The bank declared `Gather00531DE0::gather` without a definition or binding.
The independently decoded target is the already verified, address-qualified
`Rva00531DE0RefreshSelectedIndices` body. It ignores incoming ECX, so the
bank's receiver-class spelling is not evidence of a native Gather class.
The replacement explicitly names an address-qualified receiver **view**, and
retains the existing verified helper's operation name rather than promoting
the bank-only alias. Exact snapshot corrections cover these two substitutions;
they do not authorize another receiver identity or a second body claim.
