# 0x001ABC90: bank class `GenKey` retired on landing

name_regression pairs the old bank `targets/game/reverse/attempts/0x001abc90.cpp`
with the landed `game/GameEngine/Source/GameLogic/Map/TerrainLogicAddWaypoint.cpp`
and reports `GenKey -> Rva0002FF6DStringPresenceThunk`.

`GenKey` is not an identity:

- It does not occur in `inputs/reference`. The Zero Hour addWaypoint uses
  `StaticNameKey` / `TheKey_*` globals for the same fetches.
- In `symbols.csv` its pins all describe the class as a placeholder:
  `?fetch@GenKey@@QAEHXZ` at 0x00009304 is "address-derived no-argument lazy
  key fetch call", `?fetch@GenKey@@QAEHPA_N@Z` is an "address-derived name",
  and the `GenKey0012A79xx` globals are "address-derived lazy key global".
- The old bank declared `GenKey` TU-locally with a single `fetch()` pinned to
  ILT 0x00009304.

The landed source calls the same ILT 0x00009304 through `Key001ABC90::key()` on
the six key globals at 0x012A77B8..0x012A77E0. `Rva0002FF6DStringPresenceThunk`
is the address-derived owner of the Dict AsciiString lookup reached through
0x0002FF6D. Both names keep an address. The pins that name `GenKey` elsewhere
are untouched.
