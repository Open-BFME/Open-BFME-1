# RVA 0x00744360: vector temporary evaluation

The retail image is `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`.
Its image base is 0x00400000; addresses below say explicitly whether they are
RVAs or VAs.

## Boundary and identity

Vtable VA 0x011217A0 belongs to the existing W3DView family. Its installing
constructor and destructor are the independently recovered bodies at RVAs
0x00745B10 and 0x007461B0; the existing W3DView deleting-destructor recovery
at RVA 0x007463F0 documents the owner. Slot 155, at VA 0x01121A0C, contains
VA 0x004217E7. That five-byte ILT jumps to VA 0x00B44360 (RVA 0x00744360).
This identifies the receiver family, not an original method spelling.
`rva00744360HasClearShot` retains the address and describes the observed operation.

The failure epilogue starts at RVA 0x007444B8: POP EDI, POP ESI, XOR AL,AL,
POP EBP, ADD ESP,0xB8, RET 0xC. The RET ends at RVA 0x007444C6; INT3 padding
starts there. Thus the complete body is 358 bytes. Ghidra independently creates
a 358-byte function at VA 0x00B44360 and recovers the object checks, coordinate
copies, ray dispatch, and null-success/different-owner-failure tail.

## ABI and bindings

The three explicit arguments are two ObjectIDs and the ray-pick integer. The
body ignores its incoming receiver. Each Object is found through ILT RVA
0x0001F253, reaching the existing matched GameLogic lookup at RVA 0x0009A510.
The enum ObjectID spelling already has a pin to that same ILT. No new lookup
pin or storage model is introduced. Object vtable slot 10 is the existing
header's `getDrawable`, not the bank's opaque integer-returning `Able` label.
The canonical Object header supplies position +0x38 and ID +0x74; the layout
oracle confirms `m_id` at +0x74 and Drawable's `m_object` at +0xFC.

Other calls use existing matched names and definitions:

- ILT RVA 0x0004935A -> LineSegClass::Set at RVA 0x003FEB40, 49 bytes.
- ILT RVA 0x0001B757 -> RayCollisionTestClass constructor at RVA 0x00609A20,
  120 bytes; line reference, CastResultStruct pointer, collision integer and
  two boolean arguments.
- ILT RVA 0x00019CC2 -> RTS3DScene::castRay at RVA 0x007129F0, 856 bytes.

The collision/math types come from existing headers. Their Set/constructor
are parsed with automatic inlining disabled, keeping the real calls. Vector3
and CastResultStruct are parsed first with inlining enabled, preserving the
inlined vector copies and result initialization. The existing RenderObjClass header also reproduces BFME's observed
Get_User_Data dispatch at slot 86, preserving the bank's established type name.
No semantic alias or new callee pin is needed.

## Measured source change

The served bank builds 358 bytes with twelve non-relocation differences at
+0x5C through +0x93: the two Vector3 temporaries exchange their source objects
and stack homes. Whole-object local copies instead build 363 bytes; binding
the first constructed temporary to a const reference retains 358 bytes but
has 65 differences. Earlier scalar-local variants are recorded in re_attempts.

The reconstruction-only inline `rva00744360SetEndStart` takes the end temporary
before the start temporary, then calls the real Set with (start, end). VC7.1's
right-to-left construction now copies the first object's position first, as
retail does, without changing Set's ABI or argument order. This is a source
shaping adapter, not a claim that EA named or wrote that helper. It introduces
no extra call, assembly, volatile storage, or dummy value. The complete caller
is exact modulo relocations, including after canonical-header adoption; the
normal add_match/build gate supplies strict relocation validation.
