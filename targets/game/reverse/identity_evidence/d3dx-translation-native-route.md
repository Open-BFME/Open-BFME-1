# Native D3DXMatrixTranslation public dispatch

Only the six-byte provider at RVA009FB784 is repaired. Caller sources,
headers, global families and existing pins remain unchanged.

Retail W3DShaderManager::setShroudTex at RVA00717E90/2072 has E8 at
RVA007185AD; TerrainTextureMatrix's existing address-derived build at
RVA007DCF00/281 has E8 at RVA007DCF54. Both operand destinations are
RVA009FB784. Its six-byte body is FF2560BE2D01, through private cell
VA012DBE60, whose initial value is VA00DFB756. This names the independently
matched 46-byte init_D3DXMatrixTranslation, which ends RET16.

The existing native DX81 d3dx8math.h at line760 declares
D3DXMATRIX* WINAPI D3DXMatrixTranslation(D3DXMATRIX*,FLOAT,FLOAT,FLOAT).
The Summer2003 SDK archive's public symbol _D3DXMatrixTranslation@16 and
its independently matched typed initializer/scalar bodies agree with this
four-argument stdcall contract. No inferred prototype or new caller cast is
needed for this provider-only repair.

Actual inputs/vendor/d3dx9/d3dx9.lib member obj\i386\d3dxmath.obj defines
_D3DXMatrixTranslation@16 as FF2568000000, sole DIR32 at+2 to its own
?g_D3DXFastTable@@3UD3DXFASTTABLE@@A plus0x68. The independently recorded
native table home VA012DBDF8 plus0x68 equals the retail cell VA012DBE60.
archive_import verifies native table initialization, the matched initializer
body and each DIR32/REL32 identity, unique archive destinations and ownership.
This is static SDK private dispatch, not a PE DLL import.

Archive SHA256 9496d4ce606998c2ad7588f2db9aada3c59786515244482230fde0cd6099ed56;
member SHA256 4ed40107bcefeb5f7b2c54d581c109f3a208fa68f85271f7f6b4cf94288df065.
Both hashes are frozen row proofs and freshly validated by the official gate.

Strict controls in build/d3dx_translation use read-only copies of the owning
Scaling lane's exact caller objects. Donor/current source bytes must agree;
caller object hashes are recorded. No caller claim or compile is duplicated.
The actual selected native archive member/library, genuine retail imports and
explicitly labelled unrelated scaffolding are linked without /FORCE:

- Positive LINK0: both caller bodies match retail outside their actual original
  relocations, with native public6B and initializer46B likewise exact.
- Both E8 operands reach selected public VA10003580; FF25 selects native table
  VA100E2000+0x68, initially containing native initializer VA10003552.
- Old generated wrapper (actual archived census COFF) without native provider
  fails LINK96; it cannot resolve the canonical public SDK symbol.
- Missing native provider fails LINK96 on _D3DXMatrixTranslation@16.
- Actual Scaling@16 and RotationX@8 archive alternatives are independently
  rejected because their table fields miss the retail cell.

Receipts/scripts/MAPs are under build/d3dx_translation. These are physical
provider/edge proofs, not whole-program runtime closure. Six existing generated
bytes are replaced by an existing native archive provider; zero C++ or data
bytes are authored and no projected or measured closure gain is claimed.

Official add_match archive gate exits0: 2733/2733 functions, three native
archive-dispatch routes, 1176 literals plus ten empty refs, 1562 constants,
2886 DIR32. Pin consistency passes. The generated source is untouched;
the official row replacement preserves its prior row in deleted_rows.csv.
