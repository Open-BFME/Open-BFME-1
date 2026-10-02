# RVA 0x000FE640 is the allow slot of the 0x010860C4 partition filter

Retail facts settle the filter family and refute the old DecalMeshClass
rationale. Its authentic concrete filter class spelling is still unknown.
Keep the existing address-derived identity; no production rename is made.
All native addresses below use retail-1.03-unpacked lotrbfme.exe,
base 0x00400000, decoded with pefile and capstone.

## Actual table routes

Table VA 0x010860C4 has three entries:
- slot 0: ILT 0x0001762A -> scalar deleting destructor 0x000FCA80;
- slot 1: ILT 0x00017F49 -> target 0x000FE640;
- slot 2: ILT 0x0003B9E4 -> 0x000C3BA0, the four-byte +4 accessor.

The 32-byte constructor 0x000FC2E0 installs this table at 0x000FC2F1,
zeroes receiver+4 and stores the two supplied words at +8/+C. Older
DecalMeshClass_ctor.cpp assigns pointer types to both words, but a byte
match cannot establish those types. The DecalMeshClassDeletingDestructor
ledger note incorrectly says slot zero reaches 0x000FC6F0; actual decoding
reaches 0x000FCA80. Thus those descriptive names cannot veto filter evidence.

## Matched BFME construction caller supplies position and float radius

The matched BuildAssistant::moveObjectsForConstruction at 0x001012B0
(1109 bytes, Common/System/BuildAssistant_moveObjectsForConstruction.cpp)
constructs the filter inline at RVA 0x00101334: vptr 0x010860C4 at stack+18h,
zero next pointer at stack+1Ch, incoming Coord3D* at stack+20h, and FLD/FMUL
then FSTP of a radius at stack+24h. At 0x00101348 it takes the address of
this filter and invokes ThePartitionManager through 0x009F2A40. The clean
matched source calls the same object Rva000FC2E0Filter deriving from
PartitionFilter, with virtual allow(Object*) in slot 1 and position/radius
at +8/+C. This is BFME caller evidence, not a plausible type guessed from
the constructor's two-word shape.

Independent PartitionFilter sibling tables use slot 1 for their already
matched allow(Object*) implementations and slot 2 for getPlayerMask. The
Zero Hour declaration corroborates that family layout; its unrelated decal
source does not explain this BFME caller, float radius or AI path invalidation.

The target's current matched PathProximity000FE640::apply(Object*) reads
its receiver+8 as position and +C as float radius, examines Object/AI path
geometry, destroys an intersecting path and always returns false. RET 4
at 0x000FE8F4 ends at 0x000FE8F7, followed by INT3, proving 695 bytes.
This establishes the native filter allow slot and its Object* ABI. It does
not supply an authentic concrete class spelling. No source/ledger/pin change
or second identity claim is introduced here; the conflicting constructor
and destructor descriptions require their own scoped correction later.
