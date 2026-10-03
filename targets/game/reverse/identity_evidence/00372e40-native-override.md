# RVA00372E40: native override plus visible lookup

The body retains an opaque address-qualified entry. The literal
CastleMemberBehavior identifies a lookup key, not the enclosing function.
Retail PE and Ghidra agree on the 280-byte extent, ending RET00372F57 with
INT3 at00372F58. Caller00372FA0 reaches it through ILT000386FE at00372FF0
and00373040, cleans sixteen argument bytes, and tests EAX (not AL).
Caller00373090 also forwards its full result. The third argument is a pointer:
00372FA0 reads the passed record at+CC before forwarding it. Its pointee is
left opaque; the bank's integer-shaped argument has been corrected.

## Calls and storage

- ILT0001F253 reaches the existing82-byte GameLogic::findObjectByID0009A510.
  The shared GameLogicObjectLookup.h supplies the authentic hash lookup.
- Object+4 is its template pointer. Native Overridable stores the next pointer
  at+4; its recursive getFinalOverride call through ILT000022BB reaches00087A80.
  The native OVERRIDE conversion preserves the nullable outer access and the
  single inline override step. The test reads template+D8 with mask00200000;
  no new semantic flag identity is asserted.
- NameKeyGenerator::nameToKey through0003ADD7 targets0008FFC0. The literal at
  VA01090D8C is CastleMemberBehavior. Retail key/guard are VA012F0838/012F083C.
- Object::findModule through0002AE23 targets001BEE60, whose63-byte body scans
  the object's behavior list. The conditional module+14 check precedes
  CastleBehavior::isPendingObjectUnavailable00372090 through0004B015.
- Object's existing getProjectileUpdateInterface through0000DE9F targets001BF630:
  its45-byte body scans modules and dispatches at secondary-interface slot+94.
  The local view preserves the bank's two observed virtual slots: +0C takes
  no stack arguments and returns a byte; +10 takes six stack arguments and
  forwards a full-word result. These are ABI observations, not evidence for
  the bank view's semantic slot names or the ZH ProjectileUpdateInterface ABI.
- Object::getControllingPlayer through00020824 targets001BE3F0. Its18-byte body
  reads team+23C and tails to Team's getter or returns zero. The caller passes
  that pointer, zero, Object's witnessed cached position at+38, its opaque
  third argument, the Object pointer, and its incoming flag to the final slot.

The final source uses the canonical BFME Object/Thing header, native
Overridable/OVERRIDE, and existing named direct callees; no pin is added.

## Measured lever

The served bank is280 bytes with14 ESI/EDI operand differences. Visible lookup
alone and canonical Object/direct-call declarations alone leave all14.
Native OVERRIDE combined with visible lookup removes them. Disabling lookup
visibility restores all14 even with native OVERRIDE, so both are necessary.
The final pointer-argument signature retains the exact result. A bool-result
trial was worse and is contradicted by the callers' full-EAX tests.

The visible helper is the authentic shared implementation, not a synthesized
side-effect stub. The final scoped gate verifies all280 bytes and references. A separate strict
in-memory selection of existing rows verifies the same TU's82-byte lookup and
26-byte const override resolver, including their references, without changing
either helper's ledger owner or credit.
