# ShroudTextureShader::set at RVA 0x007C3FD0

## Result and scope

`?set@ShroudTextureShader@@EAEHH@Z` is recovered in `game/GameEngineDevice/Source/W3DDevice/GameClient/ShroudTextureShaderSet.cpp`. Its complete 1337-byte body matches retail with relocation operands resolved by the scoped gate. This investigation starts from revision `0c01876b63040c17ea243f85030119bf8a85481d` and the saved reconstruction. The source, function row and evidence are pending collection because this worker cannot write the Git index. No symbol pin or shared header was changed.

The old definition in `W3DShaderManager.cpp` was removed to avoid retaining a second, incomplete definition of the same method. The canonical `_PresetMultiplicativeSpriteShader` datum at VA `0x012D6E60` now has a verified data row owned by its existing definition in `game/Libraries/Source/WWVegas/WW3D2/shader.cpp`. Its four bytes and size were compiled and checked independently. The first landing attempt exposed this missing ownership record; no address or initializer was invented to satisfy the gate.

## Retry hypothesis and refutation

The saved body's stack-frame mismatch was caused partly by missing work and partly by different object lifetimes. Retail calls the counted shroud getter to test whether the texture exists, destroys that result, then calls the getter again to bind the underlying D3D texture. The saved body omitted the conditional binding. Retail also preserves seven distinct 64-byte matrix objects or copies. The canonical game DX8 header and the landed FlatShroudTextureShader body supplied declarations and a comparable explicit matrix-copy pattern that the old bank did not use.

The hypothesis would fail if the complete getter wrote additional fields, the apparent getter call was not on an instruction boundary, the condition destroyed a different object, or the explicit seven-matrix body did not improve the measured bank. The complete decoded getters write exactly one pointer, the target contains both calls and both release paths, and the corrected body reaches exact bytes. Merely enlarging the old frame or changing register spelling was not sufficient.

## Complete boundary and caller

`build/shroud-007c3fd0/retail.txt` retains the complete target decode. `boundary-check.txt` verifies continuous coverage, every conditional branch and jump destination, the sole final return at RVA `0x007C4506`, and the following 40 bytes of INT3 padding. No branch or tail jump leaves the target extent. `checked-target.txt` and `checked-helpers.txt` retain the unedited checked-callee inventories. The target contains no STL value or container reconstruction.

The complete matched `W3DShaderManager::setShader` body at RVA `0x00716980`, extent 61, loads a shader instance from VA `0x012F9C88 + 4 * index`, passes that instance in ECX, pushes one 32-bit pass argument and calls virtual slot zero. The call at RVA `0x007169B7` is a decoded instruction inside that body. The target keeps ECX as its receiver, writes the argument to receiver offset `+8`, returns EAX equal to one and removes four argument bytes. There is no receiver adjustment or hidden return storage for this method. See `helper-decode.txt` and `checked-helpers.txt`.

## Independent class identity

The instance at VA `0x012BBF84` has vptr VA `0x0112878C`. Its four vtable slots route to the target, the already matched `ShroudTextureShader::reset` at RVA `0x007C4660`, initializer RVA `0x007C3F80` and shutdown RVA `0x007C33F0`. The nine-byte constructor at RVA `0x007C3FC0` installs this exact vptr. The initializer writes the instance into shader-array index five and writes one into the corresponding pass-count entry. The Zero Hour `ShaderTypes` enumeration identifies index five as `ST_SHROUD_TEXTURE`, and its ShroudTextureShader registration and set implementation agree with this behavior. These observations establish the name independently of compilation.

The nearby initializer at RVA `0x007C3FA0` belongs to FlatShroudTextureShader and its different vtable. It is a useful source donor, not evidence that it owns this target. Raw evidence is in `retail-data.txt`, `vtable.txt`, `vtables-all.txt`, `registration-decode.txt` and `helper-decode.txt`. The enum is in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h`; the twin class and implementation are in its `Source/W3DDevice/GameClient/W3DShaderManager.cpp`.

## Counted texture returns and ownership

The complete `bfmeGet` body at RVA `0x007C34A0`, extent 35, is reached through ILT RVA `0x0001ADED`. It receives hidden result storage followed by a 32-bit index on the cdecl stack, reads one pointer from its table, writes only that pointer to the result and increments the pointee's 16-bit reference count at `+4` when nonnull. It returns the result address in EAX and leaves stack cleanup to the caller.

The complete `W3DShroud::getShroudTexture` body at RVA `0x006D2630`, extent 29, receives the shroud in ECX and hidden result storage on the stack. It reads the pointer at shroud offset `+0x1C`, writes only four bytes to the result and performs the same conditional 16-bit increment. EAX returns the result address and `ret 4` removes the hidden argument. This proves a single-pointer counted return object from all its reads and writes, rather than from allocation size or a donor name.

The complete 12-byte owning destructor at RVA `0x0005CC00` dereferences that pointer, tests it and tail-jumps to `Release_Ref` at RVA `0x009EB7A0`. The latter's complete 36-byte body decrements the low 16 bits at pointee offset `+4`; when the remaining count is zero and flag `0x01000000` is set, it tail-jumps to virtual slot `+0x20`. Its other path returns without arguments. Both BfmeHandleCX and TextureHandle cleanup wrappers reproduce this route.

`BoxSetTexture` at RVA `0x00905AC0`, extent 74, is cdecl with a 32-bit stage and the address of the single-pointer handle. It compares the pointed-to texture with the stage cache, retains the new texture, releases the old one and updates the cache and dirty mask. It does not swap the old texture into the input handle. `Peek_D3D_Base_Texture` at RVA `0x0090DC60`, extent 37, receives the address of a handle, dereferences its first pointer and returns either zero or the D3D pointer obtained through texture offset `+0x14` and underlying-handle offset `+8`. Its virtual calls at texture slots `+0x28` and `+0x2C` take ECX and no stack arguments; the first result is tested in AL. Passing the raw texture as this receiver would be wrong. See `retail.txt`, `texture-decode.txt` and `helper-decode.txt`.

Material ownership uses a different width. `VertexMaterialClass::Get_Preset` at RVA `0x009212C0`, extent 22, takes a 32-bit preset, returns a pointer and increments a DWORD count at `+4`. The target's inline material operations likewise use DWORD increments and decrements and virtual slot zero for deletion. The source includes the canonical game VertexMaterialClass and DX8Wrapper declarations rather than redeclaring their layouts.

## Layout and indirect ABI

The target reads W3DShroud float fields at `+0x10`, `+0x14`, `+0x2C` and `+0x30`, and signed integer dimensions at `+0x20` and `+0x24` through FILD. It reads the terrain object's map pointer at `+0x2FF4` and shroud pointer at `+0x30B8`. The TU views name the witnessed members and leave unobserved storage opaque. These declarations do not claim a complete layout for either class. The shader view has its vptr at zero, pass count at `+4` and stage at `+8`, consistent with its constructor, registration and reset evidence.

The complete target has device virtual calls at slots 67, 57, 65, 45 and 44 for texture-stage state, render state, texture binding, GetTransform and SetTransform respectively. Their stack words are the device followed by three, two, two, two and two 32-bit arguments. Each call uses callee stack cleanup; HRESULT results are unused. The transform pointers address full 64-byte matrices. These calls use the existing typed SDK declarations and the BFME device slots established in the landed shader donor. All indirect call addresses are listed in `boundary-check.txt`.

The public D3DX multiply, inverse, scaling and translation entries are indirect dispatch thunks at RVAs `0x009FACAD`, `0x009FB321`, `0x009FB6F4` and `0x009FB784`. Their complete thunks and initialization entries are decoded in `retail.txt`, `registration-decode.txt` and `helper-decode.txt`, with checked inventories in `checked-helpers.txt`. Scaling and translation initialization preserve three float arguments and an output pointer and return with 16-byte cleanup. The SDK declarations establish the matrix pointer types and stdcall signatures; the target's copies each transfer 16 DWORDs. The seven matrix slots are current view, first product, scale, inverse, second product copy, translation and third product, at stack offsets `+0x28`, `+0x68`, `+0xA8`, `+0xE8`, `+0x128`, `+0x168` and `+0x1A8` during matrix work.

## String lifetime and exception cleanup

The source uses canonical StringClass methods. Complete `Get_String` at RVA `0x009DB890`, extent 352, takes length and a bool carried in a stack word, writes the receiver's sole pointer and returns with eight-byte cleanup on every path. Complete `Free_String` at RVA `0x009DB7A0`, extent 117, acts on that pointer and its allocation header and returns without stack arguments on every path. BFMEValueName and BFMEValueNameLate preserve the donor's one-pointer views and the two observed load schedules for the runtime character at VA `0x0134ECC8`. The character is read from storage, not replaced by an assumed constant. The initial empty-string pointer at VA `0x012D9124` points to this storage. Complete render-state and texture-stage-state name helpers, including their tail route to the cdecl varargs StringClass::Format at RVA `0x009DBB90`, are retained in `state-helper-decode.txt`, `format-decode.txt` and their checked logs.

Retail's EH handler at RVA `0x00C52EC7` refers to five cleanup states. States zero and four release a counted handle at `ebp - 0x1E0`; states one, two and three free a string view at `ebp - 0x1E4`. Every predecessor is minus one. The compiled object's unwind map has the same state count, predecessor values and receiver offsets. Complete compiled cleanup destructors match the retail release or string-free routes, including the owning handle's null guard. `eh-retail.txt` records the retail map, and `eh-comparison.txt` records the object comparison and five passing checks. This verifies cleanup in addition to the main-body byte gate.

## Measured experiments

Each source snapshot and unedited probe output is retained under `build/shroud-007c3fd0/`. The table records non-relocation byte differences at the complete retail extent; an instruction-shape score is not substituted for byte equality.

| Trial and raw probe | Compiled bytes | Differing bytes | Observation |
| --- | ---: | ---: | --- |
| `baseline.cpp`, `probe-baseline.txt` | 1292 | 882 | Reproduced the saved bank with corrected include paths. Frame remained `0x194`. |
| `native-lifetimes.cpp`, `probe-native-lifetimes.txt` | 1337 | 273 | Native declarations, conditional texture binding and explicit matrix copies restored the missing work. Frame was four bytes too large. |
| `scope-math.cpp`, `probe-scope-math.txt` | 1337 | 241 | Ending the handle lifetime before the nested matrix block restored frame `0x1D8`. |
| `both-snapshots.cpp`, `probe-both-snapshots.txt` | 1337 | 28 | Existing snapshot wrappers restored the string load schedules. |
| `bind-handle-inline.cpp`, `probe-bind-handle-inline.txt` | 1337 | 18 | An inlined handle binding placed the device load after the counted getter and before Peek. |
| `tail-counter-after.cpp`, `probe-tail-counter-after.txt` | 1337 | 0 | Moving the matrix counter increment after the final full matrix copy restored the final instruction order. |
| Final source, `probe-ShroudTextureShaderSet.txt` | 1337 | 0 | Repeated at the intended game source path after cleanup. |

Mechanical EH search on the isolated, assembly-free candidate made no improvement across its seven choices (`search-eh.txt`). A finite register experiment swapping the two translation-local declarations changed 241 differences to 243 and was rejected (`search-register.txt`). SDK matrix operator expressions produced only six matrix slots and a 1309-byte body; explicit copies were required. Earlier frame-only and SDK-multiply attempts did not include the complete conditional texture operation. Every rejected snapshot and raw measurement remains available; no nonmatching body remains under game/.

## Verification and collection limitation

`scoped-gate-final.txt` passes the target's function, body guard, 55 DIR32 references and two float constants. `canonical-gate.txt` passes all 47 remaining function rows and ten data rows in W3DShaderManager.cpp after removing the obsolete definition. `shader-data-owner-gate.txt` passes the unchanged shader.cpp owner with its new verified data claim. `add-data.txt` independently verifies the canonical preset's size and bytes. `declared-final.txt`, `class-gate-final.txt` and `pin-consistency-final.txt` pass. No shared header changed, so the change does not require a full header gate.

The required direct `python tools/check_csv.py` invocation is preserved in `check-csv-direct.txt`. It fails because the read-only Git index still lists the deleted bank. The new source is also pending staging. `integrity-manifest.txt` passes the same checker against actual working-tree contents with the explicitly stated new-source and bank-removal collection manifest, without modifying the checker or Git index. It also reports no name regressions between the original bank and new source through the checker's existing `name_regression.regressions` implementation. The current name_regression command-line interface accepts Git revisions rather than the two file arguments requested by the dispatch; its raw rejection is retained in `name-regression-direct.txt`. The coordinator must stage the listed paths and run the normal CSV check and commit hooks. This is an uncompleted index-dependent collection check, not evidence of a remaining byte, ABI or identity mismatch.
