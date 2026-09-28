# 0x0029A150 Bezier helper: bank's `FlightCurve0029A150::build` retired

The bank `targets/game/reverse/attempts/0x0029a150.cpp` called this body
`FlightCurve0029A150::build(bool, float)`. The landed source
`PhysicsBehaviorRva0029A150.cpp` names it
`?rva0029A150@PhysicsBehavior@@QAEEHM@Z`. name_regression reads
`build -> rva0029A150` as a lost descriptive name. There was nothing
descriptive to lose:

- `build` and `FlightCurve0029A150` appear only in that bank. They are
  not in `inputs/reference`, the ledger, symbols.csv or any vtable.
- symbols.csv already pinned 0x0029A150 as
  `?rva0029A150@PhysicsBehavior@@QAEEHM@Z` before this seat ran. The
  matched caller `PhysicsBehavior::rva0029AB10` (0x0029AB10,
  `PhysicsBehaviorRva0029AB10.cpp`) calls it under that name with
  ECX = the PhysicsBehavior `this`, pushes an int option and a float, and
  the callee returns with `ret 8`. A matched caller naming the symbol
  outranks the bank's guess. The bank's class (`FlightCurve0029A150`) and
  `bool` parameter/return also contradict that witnessed ABI.
- The body resembles Zero Hour's `DumbProjectileBehavior::calcFlightPath`
  (Bezier control points, terrain height, segment points). But the owner
  here is PhysicsBehavior and the arity differs (int + float vs one
  `Bool`), so that name is unproven and was not adopted either.

The seat kept the existing pinned, address-derived identity.
