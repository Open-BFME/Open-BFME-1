# RVA 008D9EC0: AABCollisionStruct constructor

Zero Hour's `GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/colmathaabox.cpp:439`
defines AABCollisionStruct and its constructor taking four references:
`const AABoxClass&, const Vector3&, const AABoxClass&, const Vector3&`.
The existing native BFME `CollisionMathMovingAABox.cpp` already contains
that type, with the independently matched moving-box CollisionMath::Collide
at 008DA000 and its private aab_separation_test helper at 008D9F20.
Its BFME-specific `Side(0)` initialization is already present.

The retail standalone constructor exactly agrees with that type: bool at
+0, MaxFrac zero at +4, AxisId -1 at +8, Side zero at +C, two Vector3
differences at +10/+1C, and the two box references at +28/+2C. The first
difference uses box1.Center minus box0.Center; the second uses move1 minus
move0. It returns this in EAX and pops all four reference arguments (RET16).
The canonical existing constructor emits exactly these 95 bytes, with no
relocations. The old opaque pointer-based bank emits 95 bytes with 21 byte
differences and is superseded by the actual typed source, not by an alias.

Boundary is independently complete: prior CollisionMath::Overlap_Test ends
RET at 008D9EBC followed by three INT3 bytes. Entry 008D9EC0 establishes its
own receiver and arguments, ends RET16 at 008D9F1C, and has an INT3 at
008D9F1F before the separately matched helper entry 008D9F20. Baseline
Capstone decode and Ghidra agree; Ghidra creates the full 95-byte function.
No incoming standalone call was found. The ZH constructor twin, existing
typed helper/caller layout and exact complete body supply the identity.

No production source, header, callee pin, or helper calling convention
changes are required. Verification covers the whole existing three-body TU.
