# Native D3DXMatrixScaling dispatch provider at 0x009FB6F4

## Public identity and ABI

The installed SDK headers `inputs/toolchains/dx81/include/d3dx8math.h`
(line 756) and `d3dxmath.h` (line 666) both declare `D3DXMATRIX * WINAPI
D3DXMatrixScaling(D3DXMATRIX *, float, float, float)`. The external native
archive identity is `_D3DXMatrixScaling@16`: four stack words and stdcall
cleanup. Its initializer physically ends `C2 10 00`; this ABI is independently
consistent with both matched callers. Neither caller source nor any header,
type, pin, or global is changed.

## Exact archive route and independent retail ownership

DirectX9 Summer2003 archive `inputs/vendor/d3dx9/d3dx9.lib`, SHA256
`9496d4ce606998c2ad7588f2db9aada3c59786515244482230fde0cd6099ed56`,
contains member `obj\i386\d3dxmath.obj`, SHA256
`4ed40107bcefeb5f7b2c54d581c109f3a208fa68f85271f7f6b4cf94288df065`.
Its real external function in section 277 is exactly six bytes
`FF 25 84 00 00 00`, with one DIR32 relocation at +2 to
`?g_D3DXFastTable@@3UD3DXFASTTABLE@@A` plus 0x84. The existing table home
VA 0x012DBDF8 gives retail cell VA 0x012DBE7C. Retail's public six bytes are
`FF 25 7C BE 2D 01`. This is native static SDK dispatch data, not a DLL IAT.

The archive table field at +0x84 has one DIR32 initializer to
`?init_D3DXMatrixScaling@@YGPAUD3DXMATRIX@@PAU1@MMM@Z`; retail holds
VA 0x00DFB6C6 there. That distinct 46-byte initializer already has an
independently matched archive row at RVA 0x009FB6C6. Its two actual relocation
operands are REL32 at +3 to `_D3DXCpuOptimizations@4` and DIR32 at +0x27 to
the same table field +0x84. The official archive_import verifier independently
binds both operands and compares the initializer's concrete bytes, native
member ownership, and actual initial dispatch value. The public six-byte
extent has two concrete opcode bytes and four independently bound address
bytes; it does not qualify by relaxed thin-library byte masking.

The old generated six-byte provider exports `?ji_009fb6f4@@YAXXZ`, and its
actual frozen census object contains `FF 25 00 00 00 00` with relocation at
+2 to invented `__imp_?i_009fb6f4@@YAXXZ`. It does not define the canonical
public identity required by the native callers. Replacing its one ledger row
through official `--replace-archive-import` preserves a tombstone, the same
address and extent, and the untouched generated file. No alias is invented.

## Caller and selected-link proof

Existing matched `W3DShaderManager::setShroudTex`, RVA 0x00717E90/2072,
contains its Scaling call at opcode RVA 0x007185E3. Existing matched
address-derived TerrainTextureMatrix builder, RVA 0x007DCF00/281, has Scaling
calls at opcode RVAs 0x007DCF8D and 0x007DCFE0. All three actual retail
REL32 operands reach RVA 0x009FB6F4. Mandatory callees were inspected before
work. Existing Scaling pin consistency is green; no pin is added or changed.

Baseline official scoped gate on both caller TUs: 2/2 matched, seven float
constants, 107 DIR32 references verified. Actual source objects are preserved
and hashed in `build/d3dx_scaling/controls.json`. A physical fixture links their
actual sliced definitions, the actual native archive/member, retail import
libraries, and native SDK Uuid.Lib. It explicitly labels unrelated owner
stubs; those stubs are not closure or native API proofs. The three Scaling
calls, native public six bytes, initializer 46 bytes, and table initial target
are independently verified after this link. Direct-child exit and complete
binary streams are captured through regular files.

Positive exit 0 selects native Scaling VA 0x100034F0, initializer VA
0x100034C2, and table VA 0x100E2000; public cell is table+0x84 and initially
addresses that native initializer. Both unchanged caller bodies match retail
outside their original relocation fields. Actual old-generated provider
negative and missing-provider negative both exit 96 with unresolved canonical
`_D3DXMatrixScaling@16`. Both retain labelled unrelated stubs; neither invents
a Scaling substitute.

## Scope and accounting

Only the public provider row is replaced, plus its official tombstone and
this evidence. Translation at 0x009FB784 and Transform provider work remain
outside this change. No new C++ body or matched-byte gain is claimed: six
existing generator-written bytes move to the prebuilt archive lane. The qualified
historical ae75 link_check reports both callers still blocked by other globals,
duplicates, COMDATs or selected owners (0/2; 0 linked bytes). That index already
contained the physical SDK member; this identity repair is not fresh census
closure attribution.

Final official combined gate: 2942/2942 across the SDK archive, both caller
TUs, and remaining generated import siblings; two structural archive routes,
1176 literals plus ten empty literals, 1569 float constants, 3200 recorded
DIR32 references verified. The standalone gate process exits zero. Read-only
pin consistency after replacement assigns the existing Scaling pin to its
canonical native archive owner. An independent wrong-native-name control
tries the genuine Translation public symbol at the Scaling address and is
rejected: its table field misses the actual retail cell. No declaration or
baseline exception is involved.

`tools/progress.py HEAD` reports zero authored, matched, and linked byte gain;
generator-written decreases six bytes and prebuilt library increases six.
Both historical caller previews remain blocked (0/2, 0 -> 0 bytes).
