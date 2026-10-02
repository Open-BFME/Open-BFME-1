# W3DPropBuffer constructor at RVA 0x00702FF0

The Zero Hour twin is the explicit W3DPropBuffer::W3DPropBuffer definition in
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBuffer.cpp`.
It initializes the buffer and creates a directional LightClass plus a
W3DShroudMaterialPassClass. The matched BFME BaseHeightMapRenderObjClass
constructor at RVA 0x006CFAE0 calls this constructor at VA 0x00ACFD4C through
ILT RVA 0x00032097 -> 0x00702FF0. The existing matched complete and deleting
W3DPropBuffer destructors and buffer methods corroborate ownership. This is
an upstream name plus a matched caller, not an identity inferred from codegen.

Retail begins at that ILT target with an EH registration frame. RET at RVA
0x00703137 is followed by INT3 at 0x00703138: the complete extent is 328 bytes.
It constructs 4000 0x30-byte TProp entries at +4 and 96 0x18-byte TPropType
entries at +0x2EE0C. The existing destructor TU already proves this BFME layout,
including the extra pointer at +0x2F714, so the constructor extends that class
home instead of changing the older Zero Hour layout used by W3DPropBuffer.cpp.

The canonical Snapshot, LightClass, W3DShroudMaterialPassClass and SphereClass
headers are included. Snapshot's trivial constructor/destructor are inlined in
this TU; its proper Xfer-pointer virtual declarations replace the prior local
void-pointer approximation. TPropType's 16-byte bounds storage uses its native
SphereClass type, as in the upstream record. Calling SphereClass::Init with a
zero Vector3 and radius one reproduces the retail induction pointer at
+0x2EE1C and five stores in its type-initialization loop. A flat float array
matched the size but selected a different pointer base and missed ten bytes.

The first array uses existing DIR32 callbacks at ILTs 0x00004660 and
0x00044CF6; the second uses 0x00040FB1 and 0x0001C8AA. LightClass is allocated
with 0x124 bytes and constructed with enum DIRECTIONAL=1 at RVA 0x0093BE90.
The 0x3C-byte shroud material pass calls MaterialPassClass's existing constructor
at RVA 0x009333A0, installs vtable VA 0x011209C4 and clears its +0x38 flag.
The buffer installs VA 0x011209D8. These references passed the strict gate's
ten DIR32 checks. All calls use existing bindings; no pin is added.

Addresses and the full boundary were decoded from the current unpacked retail
image with pefile/capstone. The scoped strict gate verifies both the new
328-byte constructor and the unchanged 268-byte destructor. No shared header,
generated source or baseline is modified.
