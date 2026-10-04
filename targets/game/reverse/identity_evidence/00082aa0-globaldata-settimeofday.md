# 0x00082AA0 is GlobalData::setTimeOfDay(TimeOfDay)

Image: `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`,
SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses are RVAs (add image base `0x00400000` for VAs). Read with pefile and
Capstone, independently of ledger names.

Replaces `?bfmeLoadJF@BfmeXfJF@@QAE_NH@Z` ("range-guarded 3x3 vector transpose
out of an indexed set"), an invented class and method with no evidence behind
either name, and the second invented ILT pin `?apply82AA0@ZoomSettings@@QAEXH@Z`.

## The body (0x00082AA0..0x00082BC9, 298 bytes, `ret 4` thiscall)

    mov  eax,[esp+4]
    cmp  eax,6      / jge fail        ; tod >= TIME_OF_DAY_COUNT
    cmp  eax,1      / jl  fail        ; tod <  TIME_OF_DAY_FIRST
    mov  [ecx+0x218],eax              ; m_timeOfDay = tod
    imul eax,eax,0x6C                 ; sizeof(TerrainLighting[3]) = 3 * 36
    ... nine 12-byte copies, light-major:
        +0x224+i*0x24 -> +0x9BC+i*12  ; ambient
        +0x230+i*0x24 -> +0x9E0+i*12  ; diffuse
        +0x23C+i*0x24 -> +0xA04+i*12  ; lightPos
    mov  al,1 / ret 4
    fail: xor al,al / ret 4

## Zero Hour twin

`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/GlobalData.cpp:1107`:

    Bool GlobalData::setTimeOfDay( TimeOfDay tod )
    {
        if( tod >= TIME_OF_DAY_COUNT || tod < TIME_OF_DAY_FIRST )
            return FALSE;
        m_timeOfDay = tod;
        for (Int i=0; i<MAX_GLOBAL_LIGHTS; i++)
        {   m_terrainAmbient[i] = m_terrainLighting[ tod ][i].ambient;
            m_terrainDiffuse[i] = m_terrainLighting[ tod ][i].diffuse;
            m_terrainLightPos[i] = m_terrainLighting[ tod ][i].lightPos;
        }
        return TRUE;
    }

Every feature matches: the two-sided range guard, the store before the copy,
the 3-light loop (MAX_GLOBAL_LIGHTS = 3, unrolled by VC7.1), the per-light
order ambient/diffuse/lightPos, the `Bool` return. The ZH source compiles to
retail's 298 bytes exactly (`game/GameEngine/Source/Common/GlobalDataSetTimeOfDay.cpp`).

BFME differences are data only: BFME's TimeOfDay name table (VA 0x012A9FE0)
holds six names, NONE MORNING AFTERNOON EVENING NIGHT INTERPOLATE, so
TIME_OF_DAY_COUNT is 6 (the `cmp eax,6`) and m_terrainLighting is [6][3]
(the matched GlobalData constructor's 6 x 3 lighting loop at +0x224).

## Member offsets

- `GlobalData+0x218 m_timeOfDay`: `tools/name_oracle.py --class GlobalData
  --offset 0x218` (field_names, confidence 1.00, from the GameData INI
  field-parse table).
- `+0x224 m_terrainLighting[6][3]` (36-byte elements): the matched
  constructor (`??0GlobalData@@QAE@XZ`, 0x00084510) view.
- `+0x9BC/+0x9E0/+0xA04` are m_terrainAmbient/m_terrainDiffuse/
  m_terrainLightPos by this twin; the constructor view still keeps them
  address-named (m_rgb09bc/m_rgb09e0/m_pos0a04).

## Callers (all `call` to ILT 0x0000BA64, `jmp 0x00082AA0`)

| Site | Function | ZH twin call |
|---|---|---|
| 0x000852CA | `GlobalData::GlobalData` (0x00084510), `this`, m_timeOfDay | ZH GlobalData ctor `setTimeOfDay(m_timeOfDay)` |
| 0x006BED80 | `W3DTerrainLogic::loadMapAbi` (0x006BEB90) | ZH W3DTerrainLogic.cpp:190 `if( TheWritableGlobalData->setTimeOfDay( TheGlobalData->m_timeOfDay ) ) TheGameClient->setTimeOfDay(...)` |
| 0x007D1F71, 0x007D201C | `ScreenZoomFilter::set` (0x007D1F00), on TheWritableGlobalData, with a saved mode and 4 (NIGHT) | (BFME-only filter) |

The loadMap site has exactly ZH's shape: the bool result gates
`TheGameClient->setTimeOfDay(m_timeOfDay)`.

## Independent corroboration

withmorten's bfme12x-dll (https://github.com/withmorten/bfme12x-dll,
`src/bfme1.cpp`) calls ILT 0x0040BA64 (RVA 0x0000BA64) as
`GlobalData::setTimeOfDay` and reads GlobalData+0x218 as the TimeOfDay field,
hooking the W3DTerrainLogic::loadMap call site.
