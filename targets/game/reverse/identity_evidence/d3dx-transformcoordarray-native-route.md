# Native D3DXVec3TransformCoordArray public dispatch

Retail's existing 289B BfmeShadowBufferEntry::update at RVA007C1DC0 has a direct
E8 at +0x113 to RVA009FA44E. That exact six-byte body is FF25F4BE2D01, through
VA012DBEF4. The cell initially names VA00DFA43D, the independently matched
17B init_D3DXVec3TransformCoordArray in the Summer2003 D3DX9 SDK archive.

The actual inputs/vendor/d3dx9/d3dx9.lib member obj\i386\d3dxmath.obj defines
_D3DXVec3TransformCoordArray@24 as FF25FC000000, with sole DIR32+2 to its own
?g_D3DXFastTable@@3UD3DXFASTTABLE@@A plus0xFC. The independently recorded table
home VA012DBDF8 plus0xFC equals the retail cell. archive_import.verify proves
the initialized field and initializer body, all its actual DIR32/REL32
identities, and its unique archive destinations. Archive SHA256
9496d4ce606998c2ad7588f2db9aada3c59786515244482230fde0cd6099ed56;
member SHA256 4ed40107bcefeb5f7b2c54d581c109f3a208fa68f85271f7f6b4cf94288df065.
This is private static SDK dispatch, not a DLL import or a guessed thunk.

Microsoft's native API contract is independently documented at
https://learn.microsoft.com/en-us/windows/win32/direct3d9/d3dxvec3transformcoordarray:
D3DXVECTOR3* return, arguments D3DXVECTOR3*, UINT, const D3DXVECTOR3*, UINT,
const D3DXMATRIX*, UINT. Native @24 and the existing scalar/initializer archive
names independently agree on stdcall six 32-bit arguments. DX81 lacks this
D3DX9 array declaration. This TU therefore uses the existing validated
sweep/d3dx8math.h types and a local declaration of the documented API. Its
local duplicate _D3DXMATRIX is removed; no shared header or pin changes.

The existing Vector3 declares consecutive float X,Y,Z and uses (&X)[i];
retail passes 12B source/output strides. Matrix4 holds four Vector4 rows;
its Transpose returns the 16-float transposed temporary whose address retail
passes. Existing validated D3DXVECTOR3 float3 and D3DXMATRIX float4x4 describe
those native physical buffers. The casts express pointer ABI views; no
object conversion or buffer lifetime change is introduced.

Before/after caller gates both pass 2/2 existing matched bodies (289B update,
67B Get_Deformed_Vertices), zero constants/literals/DIR32. Strict controls
are recorded separately in build/d3dx_array/controls.json: actual caller
COMDAT plus the unmodified SDK member and archive; labelled unrelated stubs
are scaffolding only. The selected E8 must reach the actual public symbol,
its FF25 must reach selected native table+0xFC, and the initial cell must
reach selected native initializer. All three bodies are compared to retail
outside their original relocation fields. Removing the native archive/member
must leave the public symbol unresolved. No whole-program runtime closure or
historical queue projection is claimed.
