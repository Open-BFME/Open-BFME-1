# Data identity at VA 0x012D6DAD

Corrected: DX8Wrapper::_EnableTriangleDraw, protected bool scalar.

## Retail facts and extent

The accepted row is `?_EnableTriangleDraw@DX8Wrapper@@1_NA` at VA 0x012D6DAD, RVA 0x00ED6DAD, with 1 byte in `.data`, owned by `game/Libraries/Source/WWVegas/WW3D2/dxwrapper.cpp`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012D6DAD-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan. The original range probe found no overlapping data row and no interior DIR32 name. The accepted gate checks every initial byte and every emitted relocation target.

Retail initially holds 1. DX8Wrapper::Draw at RVA 0x00906B40 reads the byte and skips triangle submission when false, agreeing with reference dx8wrapper.cpp and its protected member declaration. SortingRendererClass::Flush at RVA 0x0093A810 saves, changes and restores it; RVA 0x00938D50 writes the byte argument. Box and shadow renderers also consult the same byte. The separate SortingRendererClass::_EnableTriangleDraw is at VA 0x012D71A4 and is not this object.

Initial bytes: `01`.

The verified COFF initializer has 0 relocation(s). The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x00710E60` (`?get_00710e60@@YAEXZ`, read), `0x00711600` (`?Rva00711600FilterDraw@@YAXII_NI@Z`, read), `0x007B14A0` (`?flush007B14A0@W3DProjectedShadowManager@@QAEXIPAUShadowTexture007B6D30@@0H@Z`, read), `0x007B9280` (`?renderStencilShadows@W3DVolumetricShadowManager@@IAEXXZ`, read), `0x007BBF80` (`?RenderMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@@Z`, read), `0x007BC270` (`?RenderDynamicMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@@Z`, read), `0x00906B40` (`?Draw@DX8Wrapper@@CAXHGGGGH@Z`, read), `0x0093A810` (`?Flush@SortingRendererClass@@SAXXZ`, read, write).

## Receiver and argument contract

The scalar is accessed as one byte. The cdecl enable setter takes one stack bool, and the no-argument getter returns AL. Draw and shadow methods retain their existing member and stack contracts.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012D6DAD-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?TheBoxFilterUVEnabled@@3_NA`: 1 game file(s).
- `?_EnableTriangleDraw@DX8Wrapper@@0_NA`: 1 game file(s).
- `?_EnableTriangleDraw@DX8Wrapper@@1_NA`: 2 game file(s).
- `?g_get_00710e60@@3EA`: 1 game file(s).
- `DX8Wrapper::_EnableTriangleDraw (additional public view)`: 1 game file(s); additional unpinned spelling.

## Change and verification

Registered the existing protected definition in dxwrapper.cpp. The byte getter and box filter now use the existing reference inline getter. The Draw TU-local declaration uses protected visibility. The shadow TU-local declaration also uses protected visibility and the existing getter; its formerly public spelling was an additional unpinned view. No shared header changed.

The raw datum gate output is `build/rlink/identity-data-20261005/add-draw-enable.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

A different byte used for the reference triangle gate, a wider access, a changed initial value, confusion with the separate sorting-renderer byte, or a byte mismatch in any dependent row would refute this correction.
