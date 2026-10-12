# The class spelling at 0x007D3D40 is refuted, not the operation

`tools/ilt_guard.py` keeps retail's incremental-link thunk table as an independent
witness for one decorated name: a thunk's slot fixes the hash bucket of its symbol to
a narrow window (`targets/game/reverse/ilt_windows.tsv`, `tools/ilt_oracle.py`). The
operation at 0x007D3D40 is proven. The class spelling `ScreenCrossFadeFilter` that the
Zero Hour donor supplies is what the witness refutes.

## The operation is proven

Constructor RVA 0x007D3740 installs vtable VA 0x01128A50. Slot 5 points to ILT RVA
0x0000FECF, whose whole five-byte body jumps to 0x007D3D40. Slot 3 goes through ILT
RVA 0x0004435A to the independently matched `ScreenCrossFadeFilter::postRender` at
0x007D38B0, whose decoded call at +0x5A loads slot 0x14, pushes the mode, passes the
unadjusted receiver in ECX and tests the full EAX return. Zero Hour's `GeneralsMD`
`W3DShaderManager.cpp:860` declares `protected: virtual Int set(enum FilterModes mode)`
with the same circle-mask state ladder. The conversion at
`game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenCrossFadeFilterSet.cpp`
reproduces the recorded 1,817-byte extent, 167 relocations and eleven unwind states.

## The class spelling is refuted

Every `ScreenCrossFadeFilter` row already in the ledger is CONTRADICTED by the thunk
table, each at a different slot:

| RVA | name | target slot: window |
|---|---|---|
| 0x00006D0C | `?updateFadeLevel@ScreenCrossFadeFilter@@IAE_NXZ` | 4763: 5150-5157 |
| 0x0073A8D0 | `?setFadeParameters@ScreenCrossFadeFilter@@SAXHH@Z` | 55645: 32629-32647 |
| 0x007D36B0 | `?preRender@ScreenCrossFadeFilter@@UAE_NAA_NAAW4CustomScenePassModes@@@Z` | 7640: 6912-6928 |
| 0x007D3700 | `?reset@ScreenCrossFadeFilter@@MAEXXZ` | 14533: 10641-10652 |
| 0x007D3760 | `?init@ScreenCrossFadeFilter@@UAEHXZ` | 55490: 32554-32560 |
| 0x007D38B0 | `?postRender@ScreenCrossFadeFilter@@UAE_NW4FilterModes@@AAUCoord2D@@AA_NPAU3@@Z` | 55057: 32343-32345 |
| 0x007D3D40 | `?set@ScreenCrossFadeFilter@@MAEHW4FilterModes@@@Z` | 12226: 9367-9368 |

The class name is a substring of every one of those decorated names, so a wrong class
spelling moves the bucket of every member at once. Seven members missing seven
different windows is that signature; no single access, const or calling-convention
change on one member explains it. The seven keys sit in the shrink-only
`targets/game/reverse/ilt_contradicted_baseline.txt`, whose contract refuses an eighth:
`ilt_guard.py` will not accept a new contradicted real name.

## Why the landed row keeps the address

The true retail class name is unknown. A search over the documented candidate
spellings (`W3DShaderManager`, `W3DFilterInterface`, `ScreenBWFilter`, `FadeFilter`,
`ScreenFilter`, ...) fits none of the four 0x007D3xxx member windows. `docs/naming_evidence.md`
routes a conflict with a shared witness this seat cannot settle to an address-named
partial layout view (`Rva0015C570GuardMachine`), which `ilt_guard.py` exempts as an
honest stand-in. So the row is `?set@Rva007D3D40CrossFadeFilter@@MAEHW4FilterModes@@@Z`
and the source class is `Rva007D3D40CrossFadeFilter`, keeping the proven address, the
proven vtable slot and the proven ZH operation name while stating that the class
spelling is unproven.

This evidence would be refuted by a class name that fits the four 0x007D3xxx windows,
or by an anchor correction that moves slot 12226's window onto the ZH spelling.
