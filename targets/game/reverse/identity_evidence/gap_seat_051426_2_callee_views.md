# Gap seat 20260928T051426_2: three flagged renames are callee/type views, not identity changes

## Object.cpp `setTransformMatrix -> rva00132200` (Object::reactToTransformChange, 0x001CDC30)

The retail drawable call in 0x001CDC30 goes through ILT 0x000361CE to 0x00132200
(`tools/callees.py 0x001CDC30 399`).
The ledger names that body `?rva00132200@Thing@@QAEXPBVMatrix3D@@@Z` and puts
`?setTransformMatrix@Thing@@QAEXPBVMatrix3D@@@Z` on the different body at
0x00132350 (ILT 0x00023D49). Spelling the call `setTransformMatrix` would bind it
to 0x00132350, which retail does not call, so the seat used the ledger's name for
the real target. No definition was renamed.

Open identity debt (not fixed here): the evidence favours 0x00132200 being the
real Thing::setTransformMatrix. `tools/callers_of.py` lists 17 named callers of
0x00132200 (Thing::setPosition, Thing::setPositionZ, Drawable::xfer,
Drawable::updateDrawable, Drawable::loadPostProcess, ToppleUpdate::update,
StructureToppleUpdate::update, Locomotor bodies, ...), which are the ZH
setTransformMatrix call sites. Its body is the ZH GeneralsMD Thing.cpp:250 body
(save old angle/pos/matrix, copy, refresh cache, clear flags, call
reactToTransformChange(&oldMtx,&oldPos,oldAngle)). 0x00132350 has no named
caller, compares old against new, and calls a no-argument virtual. Swapping the
two names is a ledger + pin + Thing.cpp change outside this seat.

## Rva007F2350StatsCursor.cpp `next -> rva007F2230`

Additive. `next` (0x007F2350) is unchanged; the seat added a new sibling method
at 0x007F2230 (int3 at 0x007F222F, ret 4 at 0x007F2348, stats.%d.key/value/rank/text
literals) under an address-derived name because its identity is not proven.

## meshmdlio.cpp -> MeshLoadContextDestructor.cpp `Vector2 -> Rva0096E1B0Elem`

The 544-byte BFME destructor at 0x0096FD30 destroys TempUVArray through the
SimpleVecClass specialization whose vtable 0x0113E684 and Resize at 0x0096E1B0
are already matched as `SimpleVecClass<Rva0096E1B0Elem>` (functions.csv rows at
0x0096EA10 and 0x0096E1B0). `SimpleVecClass<Vector2>` is a different retail
specialization (decalmsh.cpp, 0x0096CBB0 dtor). Retail was linked without ICF,
so the element type must be the one whose vtable the destructor installs.
