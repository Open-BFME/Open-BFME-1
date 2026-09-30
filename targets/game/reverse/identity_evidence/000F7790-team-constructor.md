# Team constructor, RVA 0x000F7790

The complete 631-byte body is `Team::Team(TeamPrototype*, UnsignedInt)`.

## Matched callers name the symbol

Two byte-verified callers in `game/GameEngine/Source/Common/RTS/TeamFactoryCreate.cpp`
construct a `Team` through this body and declare exactly this signature:

- `createTeamOnPrototype` at 0x000F7E70 (`team = new Team(prototype, ++m_uniqueTeamID)`)
  declares `Team(TeamPrototype *prototype, UnsignedInt id);  // ILT 0x00031638 -> 0x000F7790`.
- `createEmptyTeam` at 0x000F7CD0 (`return new Team(proto, ++m_uniqueTeamID)`)
  shares the same TU declaration and call shape.

The declaration's `(TeamPrototype*, UnsignedInt)` parameter list is therefore
witnessed by the callers' own argument setup, not inferred from this body alone.

## Boundary

The 631-byte extent is the predecessor-banked attempt's proven range
(`targets/game/reverse/attempts/0x000f7790.cpp`, probe EXACT modulo 23
relocation slots): retail bytes `0x000F7790..0x000F7A01`. The following body is
`createTeam` at 0x000F7CA0; no bytes move. The prior ledger row at this address
is the `TeamCtorThunk.cpp` `__emit` lift (`object-symbol=_bfme_TeamCtor_0F7790`),
a byte dump carrying no identity, superseded by this clean C++ conversion.

## Callee bindings proven from retail

- `0x000F77F2` (`+0x62`) encodes `CALL 0x000276B5`; the ILT slot holds
  `E9 -> 0x000F6AC0` (read from the image with `tools/build.py exe_image`).
  The TU's file-scope `Rva000F4250Hash::initializeBuckets(unsigned)` runs the
  inline 100-bucket setup there; `symbols.csv` pins
  `?initializeBuckets@Rva000F4250Hash@@AAEXI@Z` at `0x000276B5`.
  (`pin_consistency.py --symbol` before: no pin on that name; `--check` and
  `--routes` after: green.)
- `0x000F7901` (`+0x171`) encodes `CALL 0x0001F1BD`; the ILT slot holds
  `E9 -> 0x000F1C80`. The same `Rva000F4250Hash::clear()` is the `+0x1C` member
  the matched Team destructor (`??1Team@@MAE@XZ` at 0x000F4250,
  `TeamDestructorThunk.cpp`) clears through the same ILT, reusing the proven
  `?clear@Rva000F4250Hash@@QAEXXZ` pin at `0x0001F1BD` (no new pin).
