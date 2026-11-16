# Remaining DIR32 repair probes: unchanged game sources

The full baseline at4e7859a7d792's ancestry verified173475/173475 function rows
but had four DIR32 names red. Six parser callers and the existing WaterSettings
cleanup ownership were subsequently repaired. The following two names remain
unfixed. These isolated experiments are not successful tasks, source changes,
new matches, memory/crash fixes, or runtime verification.

The game files below remain identical to their versions at4723fed793ffc3dc.
Private controls/candidates use the same physical wrapper, original source
line context/parent include path and native compiler flags. Only CodeView
layout compilations add debug information; private objects never enter
build/match. All owned rows were reserved for each experiment and the leases
released afterwards. No verifier, pin or baseline was relaxed.

## Q3GuardedMemberDestructors.cpp /005CE890 /73B

Flags: the source's ordinary /EHsc context. Eight matched rows in this source
remain intact. Native primary-vtable ownership identifies ParticleInfo's
table atVA0110FE78. Its already matched30B scalar deleting destructor005CF020
calls ILT00029BF9 ->005CE890 without adjusting this; the native caller route
is stronger identity evidence than the table store alone. Slot1 reaches the
existing loadPostProcess005BD3F0; slot2 returns FXParticleInfo through the
address-named getter005BDC50. Existing source class names are not assumed to
prove the complete original interface or fields.

Four explicit vptr-store/novtable/volatile variants all alter the73B body.
They are ruled out. A separate diagnostic changes the local destructor view
to ParticleInfo with a virtual destructor. All eight retained rows then match
byte-for-byte, and its extra30B scalar-deleting copy independently passes
native RetailTruth for the existing owner. However it emits an8B two-slot
table where the old incomplete view emitted4B; the actual table has three
known slots. An old placeholder slot also becomes ParticleInfo::slot. The
entire object inventory therefore fails. Do not land this patch or merely
record its wrong virtual surface. Resolve the original interface/base and
all emitted data/providers before trying the identity reconciliation.

Best incomplete diagnostic:20261116-q3-native-identity.patch.txt.
Local evidence:diagnostics/continue-20261116-fivehundred/q3-native-destructor-identity,
q3-vtable-prototype and q3-vtable-variants, with compiler outputs and row diffs.
No full class-size or original field-name claim.

## Rva0039B560Destructor.cpp /0039B560 /134B

Flags:/DNDEBUG /MD /EHsc /O2. The old8B ThingRef element's callback reaches
ILT00048D42 ->0039B060. Existing native callback owners use address-derived
Rva0039B450Element/Rva0039B560Element spellings. Direct type respelling and
a typedef were refused by the descriptive-name regression guard; there is
no independent evidence refuting ThingRef, so no correction exemption was
added. Those source edits were restored.

A later private wrapper preserves the ThingRef declaration and delegates
the40B array cleanup to the known four-slot MSVC eh-vector-destructor helper.
Without throw(...) the /EHsc extern-C assumption removes an EH transition
and changes the parent body. With the throwing declaration, both existing
rows are byte-equal. Whole-object proof still fails: an extra16B wrapper
destructor has no retained retail identity; the explicit stdcall identifier
also acquires an unwanted @16 suffix. A raw callback address is passed only
to the runtime helper, whose original contract invokes thiscall; the pointer
declaration is never itself called. No source alias was published. Do not
call this fixed on the strength of the two matching bodies.

Best incomplete diagnostic:20261116-thingref-explicit-cleanup.patch.txt.
Local evidence:diagnostics/continue-20261116-fivehundred/thingref-explicit-cleanup,
thingref-explicit-process*.log and inspect-thingref-objects.py.
Remaining prerequisites:preserve the complete unwind/runtime graph, correct
the actual helper binding, avoid an unowned emitted helper, and preserve
established names. Re-run native byte, naming, DIR32 and linking checks.

The BFME2 reference remains read-only ataa505f34c898e6fb7c9a1f1632e75ce232f4829a.
The previously reviewed U1Zero/ParticleInfo table evidence is not a license
to copy another engine's layout or guess missing slots.
