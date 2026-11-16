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
table where the old incomplete view emitted4B; the actual table has four entries; the initial probe identified three roles.
The fourth entry is ILT0002D27C; a zero separator follows atVA0110FE88. An old placeholder slot also becomes ParticleInfo::slot. The
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

## Table extent clarification after publication

Direct retail reads show the ParticleInfo table's four entries:
VA004446F2,0040614F,00421DAA,0042D27C, followed by zero atVA0110FE88.
The initial probe established three slot roles, not a three-entry extent.
The earlier attempt-log wording "three-slot interface" is superseded by
this direct-byte extent check. Its rejected candidate remains rejected;
no game source or verification verdict is changed by this clarification.

## Additional weather-array identity probe, not landed

GlobalWeatherSystemConstructor.cpp constructs5 x8B elements at+0x28 using ILT3C0BA ->39B050 (13B) and ILT48D42 ->39B060 (35B). The existing167B WeatherData parser supports a4B sound reference at+0 and a lightning byte at+4. BFME2 GlobalWeatherSystemCtorDeferred.cpp has a related array at+0x30, not BFME1's+0x28.

The13B entry at39B050 is already owned by IPEnumeration, with identical13B retail twins624B90 and6915D0. The35B entry at39B060 is already ThingRef's destructor and has other35B twins. An8B array plus a prefix-member destructor callback does not refute either protected descriptive identity. Matching new WeatherData ctor/dtor bodies is insufficient original-name evidence. No identity or ledger change was applied.

A first local-pointer destructor candidate optimized out a null check. A member-access candidate emitted13B+35B with matching code outside the recorded DIR32 issue, but the complete graph check still refused an unmapped section13. The parent candidates were preserved but not applied after that refusal. All leases were released. Useful isolated candidates/controls remain in diagnostics/continue-20261116-fivehundred/weather-lifetime-identity and its member-probe log. No typed array, constructor, runtime or memory/crash improvement is claimed.
