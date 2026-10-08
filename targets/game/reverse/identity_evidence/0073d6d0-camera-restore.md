# Camera restore routine at RVA 0x0073D6D0

The complete 306-byte body remains a partial C++ reconstruction. The tested revision is `bdd2694177b87e45f8ea91ba53616264ee3cda73`. No function row or symbol pin changes are required for this bank. The retained symbol is `?apply@Rva0073D6D0@@UAEXI@Z`; its class and method identity remain address-derived.

## Result and reopening condition

The candidate emits 306 bytes. Independently resolving its external references leaves 20 differing bytes at every offset from `+0x3A` through `+0x4D`. Retail loads the snapshot scalar at VA `0x012F9DD4` before storing position Z, then loads VA `0x012F9DD0` before storing the first scalar. The candidate completes each store before loading the next scalar. All instructions outside that interval agree after independent address resolution. The repository probe reports 12 masked differing bytes and a score of 0.9608 because two relocation slots are displaced across this interval. That diagnostic score is not an exact recovery; the independently resolved byte fraction is 286/306.

Reopen only with an independently supported change to the snapshot restore access structure or compiler scheduling context, or with a complete caller that clarifies slot 150's unused argument and return contract. Repeating scalar temporary order, a coordinate reference, a standalone versus grouped snapshot declaration, or the native `View::setPosition` inline does not supply a new hypothesis.

## New evidence and refutation tests

The earlier unproven semantic name is addressed by retaining an opaque receiver name. The earlier unpinned-global blocker is addressed by the verifier's existing address-derived DIR32 rule, rather than new pins. `tools/build.py::unrecorded_dir32_problem` permits a datum whose encoded address is the observed retail VA or RVA. The snapshot writer at RVA `0x00743CE0` independently writes each address read by the target. Its complete decoded 530-byte extent is retained in `build/0073d6d0/caller_helpers_disasm.log`. A decoded write using a different layout, or a conflicting existing datum covering these addresses, would refute the proposed snapshot mapping.

The first full candidate matched the target's frame, branch layout, virtual calls and x87 tail. The tested hypothesis was that the proved field layout plus address-derived globals is enough to reconstruct the whole routine. The strict byte gate refutes exactness because the restore block remains reordered. The successful constant checks separately refute the need for another tangent spelling experiment.

## Boundary and virtual ABI evidence

`build/0073d6d0/target_disasm.log` contains the complete body and following padding. The only return is `ret 4` at RVA `0x0073D7FF`, ending at `0x0073D802`. All conditional branches and the local unconditional jump stay inside the extent. There are no direct calls, external tail jumps, EH registration or unwind states. `checked_target.log` records the checked inventory. The ILT at RVA `0x00003102` is a complete five-byte jump to this entry. Its pointer occurs at VA `0x011219F8`, slot 150 of the constructor-installed primary table at VA `0x011217A0`. The landed owner constructor at RVA `0x00745B10` establishes the View prefix, a secondary base at `+0xB4`, SubsystemInterface at `+0xFC`, and the embedded scalar object at `+0x24B8`.

The target uses ECX as its receiver and consumes one four-byte stack slot without reading it. The source declares that unused slot as `unsigned`. No complete caller of this target has been established, so the original argument's semantic type and whether callers observe an integer return remain unresolved. There is no hidden return storage read or write and the x87 stack is empty at the return. A table slot and an unused EAX residue alone do not prove the original void return declaration. This limits ABI acceptance even if a future shape becomes exact.

The first owner virtual call is table offset `0x19C`, slot 103. Its table entry routes through ILT RVA `0x00034234` to the complete 72-byte reset at RVA `0x0073F960`, independently decoded in `caller_helpers_disasm.log`. It takes no stack arguments. The second owner virtual call is offset `0x1D4`, slot 117. Its entry routes through ILT RVA `0x0004692A` to the complete 13-byte setter at RVA `0x0045BF90`. That body reads the full dword argument, writes receiver offset `+0x88`, and returns with `ret 4`. The bank therefore uses a dword argument, not the initial trial's bool. The ledger's Bridge name is not adopted as this view's identity.

The embedded receiver's constructor at RVA `0x006DF550` installs table VA `0x0111E188`. Slots 1, 2 and 3 route through ILTs `0x0003249D`, `0x0000CC61` and `0x0001695A` to RVAs `0x006DF5A0`, `0x006DF5B0` and `0x006DF5C0`. Each complete four-byte body loads one float at receiver offset `+0x08`, `+0x0C` or `+0x10` into ST0 and returns without stack cleanup. `aux_getters.log`, `aux_vtable.log`, and `checked_aux01.log` through `checked_aux03.log` retain the decoding and inventory. The target passes exactly `this+0x24B8`; there is no nullable pointer or secondary-base adjustment at those calls.

The terrain singleton call is slot 6 at offset `0x18`, passing X, Y and a null normal pointer in right-to-left order. The W3DTerrainLogic table at VA `0x0111D090` routes it through ILT RVA `0x000445CB` to the complete 59-byte body at RVA `0x006BE250`. That body initializes a nonnull normal as three floats, then either returns a float with `ret 12` or tail-jumps through the terrain render object's slot at `0x248`. The constructor-installed BaseHeightMap table at VA `0x0111D8B8` routes that slot through ILT RVA `0x0003065C` to the complete 957-byte body at RVA `0x006CBB50`. This final body reads the first two incoming arguments with `fld dword ptr`, writes all three normal components, and returns a float with `ret 12` on every path. `terrain_forwarder.log`, `height_slot.log`, `height_query_disasm.log`, `checked_terrain.log` and `checked_height_query.log` retain that evidence. The bank forward-declares the canonical TerrainLogic singleton and casts at the call into a local ABI view; it does not privately redefine TerrainLogic.

## Fields, data and constants

The snapshot writer copies view position `+0x0C`, `+0x10` and `+0x14` into VAs `0x012F9DE4`, `0x012F9DE8` and `0x012F9DEC`. It copies view fields `+0x6C`, `+0x3C` and `+0x50` into VAs `0x012F9DD8`, `0x012F9DD4` and `0x012F9DD0`. The target restores those values into the same position, `+0x6C`, `+0x3C`, and `+0x40`/`+0x50`, respectively. The named neighbouring camera bodies independently witness the float fields and position layout. The bank includes the canonical `Lib/Coord3D.h`. No container key, payload or element ownership inference is involved. The arbitrary file bytes printed for snapshot addresses by the initial inventory are not initialized-value evidence; these addresses lie in zero-initialized virtual storage.

The main body writes the terrain height at `+0x23F8`, clears the bool at `+0x240C`, and stores float 1 at `+0x2434`. The owner constructor independently initializes the two bool bytes at `+0x2438` and `+0x2439` and the float at `+0x2434`. The three-float result at `+0x23D8` is constructed from the embedded object's height, pitch and yaw getters. Retail multiplies pitch and yaw by the same eight-byte constant at VA `0x0111E168`, whose bits are `3f91df46aaaaaaab`. The source reproduces it with a float PI promoted for division by double 180.0. The strict constant checker verifies this factor at both references and the 700.0f terrain clamp at VA `0x011216A4`.

## Rejected measured shapes

| Trial | Change | Emitted bytes | Probe differences | First difference |
|---|---|---:|---:|---:|
| 01 | Full plain C++ reconstruction | 306 | 12 | 0x3A |
| 02 | Explicit position fields and scalar locals | 305 | 216 | 0x18 |
| 03 | Defined snapshot storage and corrected float PI | 306 | 12 | 0x3A |
| 04 | Explicit coordinate assignment operator | 300 | 218 | 0x18 |
| 05 | Canonical coordinate and decoded scalar getter declarations | 306 | 12 | 0x3A |
| 06 | Zoom local before position copy | 306 | 50 | 0x22 |
| 07 | Scalar locals after position copy | 304 | 209 | 0x18 |
| 08 | Position and zoom references | 306 | 12 | 0x3A |
| 09 | Value snapshot temporary | 307 | 218 | 0x18 |
| 10 | Contiguous snapshot aggregate | 306 | 12 | 0x3A |
| 11 | Native View position setter inline | 306 | 12 | 0x3A |
| 12 | Constructor-proved three-base owner and virtual slot 150 | 306 | 12 | 0x3A |
| 13 | Coordinate and scalar memcpy intrinsics | 306 | 12 | 0x3A |

All trial sources and unedited probe output are under `build/0073d6d0/`. The reviewed store-family generator tried reversing the two scalar stores: the original scored 0.9607843137254902, the alternative 0.9575163398692811, and neither was exact. Its original sources and manifest are under `build/shape_search/def2e2b14e104c8f9f1757e09fe58de9/`; raw probes are `store_probe01.log` and `store_probe02.log` in the target folder. Trial 12 is retained because it gives the best measured code with the most independently established ABI structure. The plain first trial's double PI constant is not retained.

The direct scoped function gate on trial 12 fails 1/1. The independent address resolution and all 20 differing offsets are retained in `build/0073d6d0/scoped_trial12.log`. The constant check passes with three verified references. The routine is not landed and contributes zero recovered bytes. No shared header, policy, tool, STL ledger row, baseline or symbol pin has been changed.

The portable retained bank uses `/Igame/Libraries/Include/Lib` and includes `Coord3D.h` without a trial-folder-relative path. Its terrain normal declaration is `Coord3D *`, as established by the complete terrain bodies. Re-probing this retained source preserves the same 306-byte emission and 12 masked differences (`build/0073d6d0/probe_bank_raw.log`). Its strict scoped byte gate fails 1/1; its three constant references pass (`scoped_bank_raw.log`). Final CSV and pin consistency checks pass (`check_csv_final.log` and `pins_final.log`); the class gate exits zero (`class_bank_final.log`). No full gate is required for banking this partial. The historical lack of snapshot pins is no longer the blocking condition; the measured restore ordering and unobserved target return contract are.

The final bank declares the primary base's slot zero as a virtual destructor, as witnessed by the retail table, rather than a dummy void member. This prevents the secondary SubsystemInterface destructor from adding a new primary slot. A compiler-only dispatch check emits `call [eax+0x258]` for the bank's virtual `apply` declaration (`build/0073d6d0/virtual_layout_raw.log`). This check validates the proposed C++ declaration's slot placement; it is not an independently recovered retail caller. The final bank probes to the same 306 bytes and 12 masked differences (`probe_banked_raw.log`), and its class gate exits zero (`class_banked.log`). All immutable source snapshots remain in the attempt archive; exactly one verdict row was recorded. The final bank's scoped gate result is retained in `scoped_banked_raw.log`, and CSV verification after banking passes in `check_csv_banked.log`.
