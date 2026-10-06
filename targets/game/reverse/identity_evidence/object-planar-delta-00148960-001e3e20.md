# Object planar delta: 0x00148960 and 0x001E3E20 take their callers' Object ABI

## Rows

| RVA | Size | Old row | New row |
| --- | ---: | --- | --- |
| 0x00148960 | 36 | `?bfmeDelta@Gen_00148960@@QBE?AVBfmeVec3DG@@PBVBfmeVec2DG@@@Z` | `?bfmeDelta@Object@@QBE?AUCoord3D@@PBU2@@Z` |
| 0x001E3E20 | 25 | `?bfmeGo941G@@YGPAXPAX0@Z` | `?bfmeGo941G@Object@@QBE?AUCoord3D@@PBV1@@Z` |

Both rows keep their established method names and take the receiver and
types their callers use; the old free-function/Gen_ views had no caller.
The matched callers of 0x001E3E20 called it as the pin
`?getPlanarDirectionTo@Object@@QBE?AUCoord3D@@PBV1@@Z`, which nothing
defined; retail's thunk table contradicts that name
(`tools/ilt_oracle.py check ... 0x001E3E20`: CONTRADICTED, outside every
window of slots 8212:7254-7261; it is already listed in
ilt_contradicted_baseline.txt), so the callers now call the row's
established stand-in `Object::bfmeGo941G` instead.
Retail has no identical-COMDAT folding, so each body takes the one name its
callers use.

## 0x001E3E20

Retail body (`tools/dis_retail.py 0x001E3E20 25`): loads `[esp+8]`, adds
`0x38`, pushes it, pushes the hidden result `[esp+4]`, calls ILT `0x0000B00F`
without touching ECX, returns the result pointer, `ret 8`. ECX is passed
through, so it is a `__thiscall` member returning a 12-byte struct by hidden
pointer, not a `__stdcall` free function.

Matched caller DieMuxData::isDieApplicable (0x002551F0) at +0x0088..+0x0090:
`push eax` (killer Object), `lea ecx,[esp+0x10]; push ecx` (result slot),
`mov ecx, edi` (victim Object), `call 0x40B069` (ILT 0x0000B069 -> 0x001E3E20),
then reads the result's x/y. Matched Object::rva001E3E40 (0x001E3E40) calls the
same entry on `this`. Both declared it as
`Coord3D Object::getPlanarDirectionTo(const Object *) const`. The stdcall row
`bfmeGo941G` could not be called with that ECX-loading shape, so the census
left the pin name unresolved (alias of `bfmeGo941G`). Both callers now declare
`Coord3D Object::bfmeGo941G(const Object *) const`, the row's own ABI.

## 0x00148960

Retail body: `fld [point]; fsub [ecx+0x38]; fld [point+4]; fsub [ecx+0x3C];
mov [result+8], 0; fstp x; fstp y; ret 8`: a `__thiscall` member on the same
Object (position at +0x38/+0x3C), point argument, Coord3D result by hidden
pointer. Its callers reach it through ILT 0x0000B00F with ECX = the Object:
matched Object::rva001E2560 (0x001E2560), which declared it as
`Coord3D Object::rva00148960(const Coord3D *) const` (pinned at the ILT,
defined nowhere), and Object::bfmeGo941G above, which must forward its own hidden
result slot, so the callee's return type must be the caller's `Coord3D`. The
old row's `Gen_00148960`/`BfmeVec3DG`/`BfmeVec2DG` view had no caller. The
method name is not recovered; the row keeps the ledger's established
`bfmeDelta` and both callers now call `Object::bfmeDelta`.
