# Native FX constant-table data at VA 0x01110180

Five external constant pointer arrays reproduce the native contiguous 196-byte region at VA 0x01110180. They retain address-derived identities; no semantic name is claimed for either gap table. There is no padding, section directive, initializer function, header dependency, or embedded retail byte array.

## Layout and identity

| Symbol | VA | Extent | Section offset |
|---|---|---|---|
| `?g_rva01110180Names@@3QBQBDB` | `0x1110180` | 48 | 0 |
| `?g_rva011101B0Names@@3QBQBDB` | `0x11101b0` | 32 | 48 |
| `?g_rva011101D0Names@@3QBQBDB` | `0x11101d0` | 28 | 80 |
| `?g_rva011101ECNames@@3QBQBDB` | `0x11101ec` | 28 | 108 |
| `?g_rva01110208Names@@3QBQBDB` | `0x1110208` | 60 | 136 |

All five arrays have a final null pointer, natural four-byte alignment, and occupy one .rdata section with base VA 0x01110180. The five extents are 48/32/28/28/60 bytes. The 44 pointer relocations refer to 40 literal identities. Every occurrence of a repeated literal symbol has the same native target; in particular all five NONE entries target VA 0x010736D8. Each literal including its NUL terminator is independently compared to the native PE bytes.

Pristine GeneralsMD GameEngine/Include/GameClient/ParticleSys.h lines 250–277 establishes the analogous five-table declaration order. Actual BFME data determines all values here, including BFME-specific first/second-table contents. The middle tables lack a proven BFME semantic name or PE consumer witness, so their names remain opaque. Raw contiguous data and exact symbol-target identities establish this data reconstruction.

## Exact pointer-target bindings

| Actual emitted COFF literal symbol | Native VA |
|---|---|
| `??_C@_04OKGDLNCL@NONE?$AA@` | `0x10736d8` |
| `??_C@_08CLGLKNDC@ADDITIVE?$AA@` | `0x10f277c` |
| `??_C@_0BE@MNNPGDMF@ADDITIVE_ALPHA_TEST?$AA@` | `0x11104e8` |
| `??_C@_05ELNMJPED@ALPHA?$AA@` | `0x10f2788` |
| `??_C@_0L@EBMCPKGO@ALPHA_TEST?$AA@` | `0x11104d8` |
| `??_C@_08LDEOAAGM@MULTIPLY?$AA@` | `0x11104cc` |
| `??_C@_0BH@IAKIBIGP@ADDITIVE_NO_DEPTH_TEST?$AA@` | `0x11104b0` |
| `??_C@_0BE@MAEPDEGL@ALPHA_NO_DEPTH_TEST?$AA@` | `0x1110498` |
| `??_C@_0M@CKCKOCGP@W3D_DIFFUSE?$AA@` | `0x1110488` |
| `??_C@_09CNKKGCPJ@W3D_ALPHA?$AA@` | `0x111047c` |
| `??_C@_0N@MIMPELGB@W3D_EMISSIVE?$AA@` | `0x111046c` |
| `??_C@_08IFAKNICE@PARTICLE?$AA@` | `0x1110460` |
| `??_C@_08NOHMCFMI@DRAWABLE?$AA@` | `0x1110454` |
| `??_C@_06GLHNNMNH@STREAK?$AA@` | `0x111044c` |
| `??_C@_0BA@LECGKCHH@VOLUME_PARTICLE?$AA@` | `0x1110438` |
| `??_C@_06NPDGGFMN@SMUDGE?$AA@` | `0x1110430` |
| `??_C@_0BB@CGFOLNGN@TERRAIN_PARTICLE?$AA@` | `0x111041c` |
| `??_C@_05LPOHGNAJ@ORTHO?$AA@` | `0x1110414` |
| `??_C@_09GANPOLNL@SPHERICAL?$AA@` | `0x1110408` |
| `??_C@_0O@IDGFKAGB@HEMISPHERICAL?$AA@` | `0x11103f8` |
| `??_C@_0M@KFAOPBP@CYLINDRICAL?$AA@` | `0x11103e8` |
| `??_C@_07NOCECAHK@OUTWARD?$AA@` | `0x11103dc` |
| `??_C@_05NKNPLGBO@POINT?$AA@` | `0x10739b8` |
| `??_C@_04LFMILBJH@LINE?$AA@` | `0x11103d4` |
| `??_C@_03OGACKNPE@BOX?$AA@` | `0x11103d0` |
| `??_C@_06FKFPCBEF@SPHERE?$AA@` | `0x11103c8` |
| `??_C@_08BCBFCBGI@CYLINDER?$AA@` | `0x11103bc` |
| `??_C@_0BB@OBFJLGNE@WEAPON_EXPLOSION?$AA@` | `0x11103a8` |
| `??_C@_0L@HPBHFJKN@SCORCHMARK?$AA@` | `0x1110398` |
| `??_C@_0L@DHBJCPPH@DUST_TRAIL?$AA@` | `0x1110388` |
| `??_C@_07PBGGLDJP@BUILDUP?$AA@` | `0x111037c` |
| `??_C@_0N@LPFMPDII@DEBRIS_TRAIL?$AA@` | `0x111036c` |
| `??_C@_0P@OIDKBKFK@UNIT_DAMAGE_FX?$AA@` | `0x1110358` |
| `??_C@_0BA@MNNCBJIP@DEATH_EXPLOSION?$AA@` | `0x1110344` |
| `??_C@_0O@FNDOPDEA@SEMI_CONSTANT?$AA@` | `0x1110334` |
| `??_C@_08NKJCBOGG@CONSTANT?$AA@` | `0x107fcf4` |
| `??_C@_0N@LPCCNCNA@WEAPON_TRAIL?$AA@` | `0x1110324` |
| `??_C@_0M@CKACIBKA@AREA_EFFECT?$AA@` | `0x1110314` |
| `??_C@_08FOLAHAHG@CRITICAL?$AA@` | `0x1081784` |
| `??_C@_0O@OOIOMGOG@ALWAYS_RENDER?$AA@` | `0x1110304` |

## Verification

Source SHA-256: `a76892eab671163b5d5fc75986e815786aefa3ea3dac082a52a3f21210e21186`.
Post-scoped-gate object SHA-256: `06a174141ec1bb8cb7ec1b05afbffad4fdf0864bf9bef19399febd4e541f5852`.

Supported add_data_match.py gates passed for each actual extent, including sizeof/allocation extent and all DIR32 targets. ./build.sh on the intended source passed all five data rows. check_csv.py and pin_consistency.py --check passed.

The data_check.py CLI returns 2 because its rows_for_source reads only functions.csv, so it cannot discover a pure data TU. This limitation is not reported as a pass. An ignored evidence adapter invokes the unchanged Placement/audit core on the exact current object, with no fabricated function rows. Its only added anchors are the five actual matched data_rows identities; the 40 literal identities come from the normal dir32_addresses catalog. It verifies all 41 initialized noncode sections, with zero contradictions, unknowns, or placement conflicts. Exact adapter/result hashes and placement reasons are retained in build/fx-tables/.

The literal address bindings are shared verification inputs and require the campaign full integration gate before final acceptance. This component establishes 196 bytes of static data only; it claims zero game-code bytes, no additional literal-data credit, and no measured link gain. It does not make the banked 1568-byte FX writer or its held STLport dependencies accepted.
