# PointGroup submit, 0x00913AF0

The complete body is 3438 bytes: its final `ret 8` is at +0xD6B,
followed by two INT3 bytes before 0x00914860. Ghidra reports 3431 because
its terminal block omits the final epilogue bytes. Independently matched
PointGroupClass::Render at 0x00917B70 calls this target at +0x287 with
ECX=this, vertex count, and a byte flag. The separate 0x00917E10 body
calls it at +0x373. Keep the existing address-derived member identity
`?rva00913AF0@PointGroupClass@@QAEXH_N@Z`.

The native bank saves world/view matrices, sets identity matrices and point
material/shader/texture, selects index buffers, packs a default RGBA color,
uploads batches of at most 2048 vertices through BoxDynamicVBAccessClass,
and draws or queues the batch before restoring both matrices. It retains
separate position, UV, and color cursors and two color branches. The mode
and alpha fields have independent matched setters/getters at 0x00912080 /
0x00912090 and 0x00912020 / 0x00912030. The default RGB and remaining view
follow the matched prepare_shader and Render implementations.

## Bounded assembly donor

Only the clamp CMOV branch and canonical x87 color-packing helper use
assembly. The CMOV donor is the independently matched complete 328-byte
DX8Wrapper::Clamp_Color at 0x0090F310, implemented in
DX8WrapperClampColor.cpp; its internal 94-byte CMOV arm starts at 0x0090F3FA.
Its CPU feature flag is independently written by Init_Processor_Features.
VC7.1 emits branches for equivalent native integer clamp expressions.
The bank copies that existing CMOV helper and writes its fallback as four
native component expressions. A loop fallback remained rolled inside this
larger caller, whereas retail unrolls all four components. The native submit
algorithm is not an assembly transcription. The canonical dx8wrapper.h
Convert_Color helper retains the independently used x87 rounding behavior.

## Callee and data contracts still relevant to landing

The twelve direct target identities are independently resolved by callees.py:
array construction iterator 0x0000AE5C -> 0x0005C600; StringClass Get_String
0x009DB890 and Free_String 0x009DB7A0; BoxSetTexture 0x00905AC0;
BoxDynamicVBAccess ctor 0x0091F730 and dtor 0x0091D9E0; its WriteLock ctor
0x0091F160 and dtor 0x0091F240; Set_Index_Buffer 0x00904470;
Set_Vertex_Buffer 0x00904510; Draw_Triangles 0x00906DF0; and sorting target
0x0093B340. No new pin is claimed by this bank.

The independently matched BoxDynamicVBAccessCtor.cpp establishes the 24-byte
record: FVFInfo reference +0; unsigned type/FVF/start +4/+8/+C; ushort
count/offset +10/+12; buffer pointer +14. The matched Set_Vertex_Buffer in
dx8wrapper.cpp explicitly reads this BFME layout through its existing
DynamicVBAccessClass ABI. Canonical FVFInfoClass supplies stride +4,
position +8, UV +14, and diffuse +34.

The sorting call uses an address-derived 12-byte center view; it does not
claim that the object is the legacy 16-byte SphereClass. The 0x009037D0
wrapper, the 0x0093B340 implementation, and this aligned five-argument call
independently support the three-float input plus four ushort arguments.
The current scratch declaration reuses the ledger's object symbol
_bfme_SortingRenderer_InsertTriangles_93B340; strict relocation closure
remains to be run after the caller matches. The second sorting-enable byte
at VA 0x012D6D75 remains an unpinned address-derived data name. The first
byte is 0x012D6D74. Do not infer a semantic name from adjacency.

The landed UV/diffuse evidence proves VertexLoc / VertexUV / VertexDiffuse
buffer records through the matched sizing helper. All other DIR32 targets
and any necessary bounded pin require the ordinary strict gate before a
future landing; this bank does not claim relocations have passed that gate.

## Measurement and exhausted experiments

The first complete native draft emitted 3100 bytes with .795 normalized
instruction shape. The saved final source emits 3442 bytes against 3438,
with 1666 probe-masked positional byte differences and a 4-byte extent
penalty. Its bank score is `(3442 - 1666 - 4) / 3442`, or
0.5148169668797211. This is not a .998 byte match: .998 is only the separate
normalized instruction-shape diagnostic, which now differs in two alignment
padding regions. The frame is 0x14C rather than 0x148. Default-color X spills
to EBP-0xE0 rather than EBP-0x14, displacing later stack locals.

The complete donor helper plus four native fallback statements recovered
.986 shape; direct Vector4 temporary and MIN batch expression reached .998.
A by-value converter enlarged the frame, an integrated clamp/pack helper
changed floating stores, a double-valued ternary generated wrong qword
constants, and a non-forced converter stayed out of line. Named/scoped
default-color temporary, declarations moved to outer scope, shared loop
index, equivalent component indexing, if/else spelling, and a center record
containing canonical Vector3 all retained the same 3442-byte residue.
No nonmatching game source, speculative pin, or coverage claim was added.
Resume with new evidence for the native temporary lifetime/stack coloring.
