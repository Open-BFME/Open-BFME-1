# FireWeaponWhenDamagedBehavior constructor, RVA 001FB5D0

This is an exact bank, not a production identity correction or landing.

## Identity and extent

The existing registry audit `upgrademux-slot9-upgradeimplementation.md`
identifies the complete FireWeaponWhenDamagedBehavior literal at RVA C909A4
and factory 116F30. Independent retail decoding confirms that factory allocates
0x4c bytes and calls ILT 2A379, which jumps to 1FB5D0. The full constructor
ends at RET 8 at +0x289, extent 652 bytes. Its eight allocateNewWeapon/reloadAmmo
paths reproduce the GeneralsMD FireWeaponWhenDamagedBehavior constructor,
with BFME additions. MobMemberSlavedUpdate is not this owner.

## Reconstruction and measured differences

A native reference-header port emitted 506 bytes. BFME_MODULE_NO_MPO and the
existing game UpdateModule header restored the base layout, yielding 543 bytes.
The complete source then matched 652 bytes after these evidence-backed changes:

* UpdateModule stores zero at +14 and -1 at both +18 and +1c. The game header
  already declares m_pad at +1c but does not initialize it. Add m_pad(-1).
* Module data comes from owner+4 and Object from owner+8. Native header getters
  with BFME_MODULE_NO_MPO express those accesses. A local address-qualified
  data view reads StartsActive at +70 and eight weapon pointers at +7c..98;
  the reference module-data layout differs. The name oracle independently
  reports m_reactionWeaponPristine at +7c from FieldParse evidence.
* Each reload is followed by copying the ObjectID at Object+74 into Weapon+8.
  No semantic Weapon member name is asserted; the typed offset helper retains
  the existing canonical Object and Weapon declarations.
* The already-proven UpgradeMux receiver is owner+20. Its BFME virtual calls
  are slots 11,13,9,8, with true passed to the last, then slot0 tests the state.
  A TU-local address-qualified ABI view reproduces those calls without
  redeclaring UpgradeMux or pretending the ZH slot list is BFME's.

The only added dependency pin is UpgradeMux::UpgradeMux at 2D9B80, through
ILT 3D24E. Its complete 13-byte body writes base vtable VA 010CE518, clears
byte +4, returns this, and has plain RET. The native ZH constructor initializes
m_upgradeExecuted(false); registered inheritance and the shared receiver
establish this identity independently of a masked caller match.

## Strict validation and queue

With the header patch and pin applied, ./build.sh on the constructor TU
reports Functions OK 1/1 and DIR32 addresses OK for 18 references. All 652
bytes and direct-call bindings pass. For this temporary validation only, the
existing 1FB5D0 ledger row was repointed to the new TU with object-symbol set
to the correct native constructor. Its inherited false MobMember name in
that temporary test is NOT an identity claim. The ledger was restored after
validation; no function-row change is included in the queue patch.

Patch: /home/deck/bfme_astra2/header_queue/b2-001fb5d0-fireweapon-constructor.patch
Base: b2eaf64d85f1f928946424265363047a69bba95b
Contains the source, one-line UpdateModule initialization, and one callee pin.
The lead must run the combined full gate and reconcile the incorrect
MobMemberSlavedUpdate constructor label and FireWeapon constructor ILT row
before promotion. The neighboring Mob-named destructor claims also deserve
an identity audit; this bank does not silently rename them.

The preferred bank probes 1.000 with the queued header patch applied. Without
it, the missing initialization remains a real byte mismatch. No shared header
change or nonmatching production source remains in this bank commit.
