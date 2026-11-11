# Water draw: bind existing providers, retain BFME1 routes

Base: `99ae58b84f9f0c7116febe55e5bf8c443b49faec`.
Consumer: `game/GameEngineDevice/Source/W3DDevice/GameClient/Water/Rva007AA820WaterDraw.cpp`.
This repairs three caller declarations, not the identity or implementation of any provider.

## BFME1 evidence

`tools/callees.py 0x007A8FF0 4953` independently decodes these retail routes:

| Call displacement offset in 007A8FF0 | Encoded ILT | Existing body | Existing provider |
| --- | --- | --- | --- |
| +0xC6F | 0x00025EC3 | 0x007A6AA0 | `WaterShader007A6AA0::setup(char *)` |
| +0xC84 | 0x00024A14 | 0x007A7240 | `WaterShader007A7240::setup(char *)` |
| +0x121E | 0x00013BBF | 0x006D2630 | `W3DShroud::getShroudTexture()` |

The setup callees consume the existing water record on the stack and return with
RET4. The caller supplies its unchanged receiver in ECX. Their existing source
units define exactly these address-qualified classes and `char *` argument;
casting only the call views preserves the record pointer, receiver and ABI.
No semantic shader name, new pin, alias, or original EA class identity is inferred.

The getter's complete 29-byte provider in `W3DShroud_getShroudTexture.cpp`
copies the pointer at receiver+0x1C into the hidden result, increments its
16-bit reference count at +4 when nonnull, and returns the hidden result with
RET4. The caller copies that one-pointer owning result into the existing shader
texture slot and releases the temporary. The caller uses native texture.h's
Add_Ref/Release_Ref, as before. Its local handle view now spells the existing
getter's `TextureHandle` result, and the receiver declaration no longer adds
const to the existing provider's method. This changes no object access or
lifetime. The global remains declared under its existing `BfmeHandleCX[8]`
identity, accessed through the local handle view, as already established in
`Water/W3DWater.cpp` and `W3DRoadBuffer_drawRoads.cpp`. No global/provider or
shared-header change is made.

The consumer's other 422-byte row at 007AA820 must remain exact as well:
`007aa820-visible-quad.md` records why visible callee context affects its codegen.
This repair retains that context and both row identities/extents.

## Donor review, not donor transfer

Reviewed read-only BFME2 pinned revision
`76f0baefa6f285d54bc1ca922397674312a5913f`, specifically:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroudMaterialPass.cpp`,
`Water/W3DWaterBoundingSphere.cpp`, and `docs/recipes.md`.
The shroud material path uses a counted result and shader-slot assignment but
has different BFME2 terrain/shroud offsets and different provider identities.
Those layouts and symbols are inapplicable here. The water unit does not provide
these BFME1 address-qualified shader setup declarations. The repair is supported
by BFME1's existing providers and retail calls, not equal donor names or RVAs.

Official upstream HEAD `9d454154c81659910fc024730687144db7c2993d` was fetched.
Its reviewed water delta adds an include directory; the material-pass source is
unchanged from the pin. Broader upstream changes have not received a complete
freshness/compatibility verification. Per experiment supervisor direction the
read-only checkout is restored to the tracked pin and its gitlink is unchanged;
a shared pointer update is explicitly deferred, not reported successful.
No donor source is a BFME1 build dependency.

## Verification and closure limits

Runner: installed Wine 11.16, supervisor-approved lane-private WoW64 prefix
`build/wineprefix-sol12h-wow64` (`WINEARCH=win64`, `BUILD_POOL=2`, no display).
Original mandated win32 setup was unsupported on this host; no gate is relaxed.

Before: scoped caller build passes 2/2. After: normal `./build.sh` over the
consumer plus `WaterShader007A6AA0.cpp`, `W3DWaterDraw.cpp`, and
`W3DShroud_getShroudTexture.cpp` passes **5/5** rows, **2/2** data rows,
64 float constants, 360 DIR32 references, and zero body-guard findings.
No new matched bytes are claimed.

A diagnostic using `build.compile_function` asserts strict unmasked caller
bytes and zero unresolved relocations, checks each provider relocation by its
canonical name, then decodes each E9 ILT destination. All three encoded routes
in the table are unchanged. Logs and the reproducible diagnostic are retained
in this worktree's `build/sol12h-bindings/` (`water-routes.log`,
`check_water_routes.py`, `water-after-build.log`).

The fetched census at `9ac0d06c54` reported three unresolved names for this
consumer (5,373 non-CC bytes). Current cold-worktree link previews are separate
from byte verification; unavailable current definers can make them UNKNOWN.
The 201.6-second current preview reports no unit linked (0/4): the consumer and
bump-setup provider are UNKNOWN because 22,806 current ledger objects are not
readable here. The flat-setup unit still has ten unresolved names: public
DX8Wrapper D3DDevice, Pixel_Shader_Constants, TextureStageStates, matrix_changes,
render_state, render_state_changed and texture_stage_state_changes; public
ShaderClass::ShaderDirty and WW3D::SnapshotActivated; and `bfmeTwoRB`.
The shroud getter unit still has a duplicate getter definition. These existing
provider-family problems are outside this caller-only repair. No shared
selection evidence is manufactured to suppress them.
Removing these three call names is not a census-confirmed unique-byte gain,
whole-program link proof, or a claim that the provider units themselves link.
