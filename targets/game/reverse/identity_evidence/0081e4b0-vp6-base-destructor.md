# 0x0081E4B0: complete base destructor, not a reset method

The prior `BfmeThingUC::bfmeResetUC` claim has no identity evidence in its
ledger notes. Its 22 bytes are the complete destructor of the same opaque
base whose constructor is already named `Gen_0081E480` at RVA 0x0081E480.
This correction preserves that existing address-derived identity; it does
not assert an unproven EA class name.

## Independent retail evidence

- Constructor 0x0081E480 is 33 bytes, takes two stack DWORDs, and initializes
  the base's offsets +0 through +0x10 before RET 8.
- Constructor and destructor install table VA 0x0112D210 (RVA 0x00D2D210).
- Destructor [0x0081E4B0,0x0081E4C6) accepts ECX=this, no stack arguments,
  and ends in plain RET. It conditionally calls the 72-byte list-removal
  body at 0x0081C3D0 with ECX=[this+0x0C] and this on the stack.
- The matched VP6 derived destructor at 0x007E3C20 calls this body at
  0x007E3CE2 after member destruction, with EH state set to -1.
- The matched derived constructor's sole unwind state uses funclet
  0x00C544D0, whose tail jump at 0x00C544D3 reaches this same body.
- Derived destructor unwind state 1->0 destroys the +0x1C member through
  0x00C544F8. State 0->-1 invokes 0x00C544F0, whose jump at 0x00C544F3
  reaches this body. These are automatic base-cleanup positions.
- Base table slot 0 instead points to the distinct 44-byte scalar deleting
  destructor at 0x0081E500. The 22-byte body does not accept deletion flags.
- An executable-section exact-target scan and independent Ghidra xrefs
  agree on the normal call and two unwind jumps. No ILT targets this body.

## Source and ownership correction

`BfmeThreeHundredFiftyFour.cpp` now defines the complete virtual destructor
under the existing opaque base class name. `__declspec(novtable)` retains
its polymorphic base width while suppressing a fabricated table. The body
keeps the established manual `_bfmeVftUC` store. The old `BfmeThingUC` prefix
view remains solely for the unchanged `bfmeDropUC(BfmeThingUC*)` ABI.

The only external-definition replacement is the reset method with the
complete destructor. Independent pre/post COFF inspection proves both
22/72-byte bodies and their relocations identical, all non-debug sections
unchanged, and no generated vtable or deleting-destructor body. The two VP6
caller objects and base-constructor object are byte-identical. The unchanged
source gate passes all nine owned rows and eight DIR32 checks.

The ledger row retains its position, address, size, source, status, and line
ending. Its false method key is durably tombstoned. No caller, shared header,
pin, alias, validation tool, or baseline changes are involved. The matched
constructor and EH cleanup evidence establish the destructor identity;
matching bytes alone are not the naming justification.

The two caller TUs gain 144+217 bytes in the per-file link preview. The owner
TU retains unrelated unresolved `_bfmeVftUC` and `g_bfmeThingUCHead` storage;
this correction does not claim a complete executable is linked.
