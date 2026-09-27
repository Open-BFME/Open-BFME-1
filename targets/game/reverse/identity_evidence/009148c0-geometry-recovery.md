# PointGroup position fill, 0x009148C0

## Identity and extent

The exact native `PointGroupClass::Render(RenderInfoClass &, int)` at
0x00917B70 calls 0x009148C0 at +0x25A with ECX holding its PointGroup receiver
and four stack arguments: Vector3 positions, float sizes, byte orientations,
and active point count. Its existing pin is
`?rva009148C0@PointGroupClass@@QAEXPAVVector3@@PAMPAEH@Z`. The address token
is retained: BFME split the original Update_Arrays implementation into several
helpers, so this is not a claim that the complete original method lives here.
The other caller is 0x00917E10+0x35F.

The complete extent is 9232 bytes: executable code finishes with the common
`ret 16` at +0x23DD, the twelve-entry aligned switch table occupies
+0x23E0 through +0x240F. The dispatch at +0x42 addresses that table. Ghidra's
9159-byte extent omits disjoint tail/table coverage, and linear decoding's
warning inside +0x2404 is table data. The next body starts at 0x00916CD0.

## Independent layout and data evidence

The matched PointGroup renderer and accessors establish the receiver layout.
`PointGroupClass::Get_Flag` at 0x009120D0 and the name oracle witness Flags at
+0x30. Matched Get_Point_Size at 0x00912010 reads +0x34 and matched
Get_Point_Orientation at 0x00912050 reads +0x48; those names therefore do not
rely only on the Zero Hour header. PointMode is +0x2C and viewport min/max are
+0x4C, +0x50, +0x54, +0x58, as used by the matched Set_Arrays implementation.
The unused +0x24/+0x28 slots remain address-derived in this bank.

The canonical Vector2, Vector3, Vector4, Matrix4, VectorClass, and DX8Wrapper
headers are used. A local PointGroup view is necessary because the canonical
header does not declare BFME's split helpers, as already documented in the
landed PointGroupClassRender.cpp.

The matched 0x00917280 initializer independently builds the triangle and quad
orientation tables at VA 0x01341288 and 0x013436B8. The matched renderer's
VertexLoc object is at VA 0x01341264 (buffer at +4). The original pointgr.cpp
provides the two GroundMultiplier vectors; this body reads their three
components at VA 0x012D6F30 and 0x012D6F3C and the screen-size table at
0x012D6EE8. These are recorded identities for the reconstruction, not newly
added data pins. No DIR32 byte masking is being presented as a landed proof.

Direct calls are the Vector3 array constructor iterator via 0x0000AE5C,
WW3D::Get_Render_Target_Resolution via 0x008FD1F0 to matched 0x00906990, and
D3DXMatrixRotationZ through 0x009FB93B. The last is a six-byte lazy import
thunk, with independently named vendored initializer at 0x009FB91F; a future
landing must close its typed import route rather than invent a normal-body
pin. No pin was added during this bank attempt.

## Native recovery and measured residue

Started with the original pointgr.cpp position section, not an instruction
lift. The first complete source emitted 7612/9232 bytes, normalized instruction
shape 0.292. Scalar vertex assignments, pointer loops, the invariant billboard
branch, and fixed screen-table initialization recovered 9232/9232 with 3625
raw non-relocation differences and shape 0.932. That equal length alone was
not acceptance.

Retail computes sum/difference corner offsets before any vertex stores.
Recovering those four float temporaries raised shape to 0.948. Separate quad
output cursors raised it to approximately 0.958; the bank keeps that complete
algorithm with unused source variables removed. Current measurements are in
the verdict. The bank score is the positional masked-byte score with an extent penalty:
`(9264 - 3797 - 32) / 9264 = 0.5866796200345423`. The 276 relocation sites
are masked by probe; they are not independently accepted bindings. Normalized
instruction shape is a separate diagnostic: 0.957 over the full probe stream,
or 0.966278603 over executable instructions excluding the 48-byte inline
table. Neither structural number is used as the finish-queue bank score.
The two simple variable quad cases normalize to identical
instruction streams when compared at their own switch entries; the whole
function still has cursor/register allocation, stack coloring, screen-table
initialization order, and x87 evaluation differences.

Rejected bounded alternatives: Matrix3D view replaced the correct 0xF0 frame
with 0xC4 and changed optimization broadly; Matrix4::Transform_Vector forms
regressed length/shape; explicit scalar transforms regressed; indexed quad
loops regressed; parameter copies regressed; moving the Vector4 result lifetime
made no improvement; the full existing matched 195-byte render-target helper,
made visible and noinline, did not improve the main body's shape. No asm,
volatile spills, dummy locals, or compiler-output transcription was introduced.

No functions.csv row changed and no nonmatching game source was installed.
The native draft is preserved by re_log as evidence only. This round adds
zero native bytes for this address.
