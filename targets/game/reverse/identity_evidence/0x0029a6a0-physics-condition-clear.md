# 0x0029A6A0 / 196-byte PhysicsBehavior condition clear

The matched `Object::rva001C7CF0` at retail `0x001C7CF0` loads
`PhysicsBehavior*` from `Object+0x208`, pushes Boolean true, and calls ILT
`0x0000D81E`, whose target is this body at `0x0029A6A0`. Existing source
`game/GameEngine/Source/GameLogic/Object/Object_rva001C7CF0.cpp` records the
same exact 295-byte caller and field. The matched `PhysicsBehavior` constructor
at `0x0029A880` and destructor at `0x0029AA30` independently prove the
compact module layout, including Object at `this+0x08`. Retail 0x0029A6A0
loads that pointer, uses ECX as `this`, reads its Boolean argument at
`[esp+0x10]` after three saved registers, and terminates with `ret 4` at
`+0xC1`. The method's descriptive identity is still unproved; the existing
pin and new source therefore keep `rva0029A6A0(bool)`.

The retail calls are ILT `0x000022BB` twice to matched
`Overridable::getFinalOverride` (`0x00087A80`) and ILT `0x0002191D` three
times to matched `Object::notifyModelConditionChanged` (`0x001BE1C0`).
Both callee identities and physical routes predate this conversion; no
new pin is required. The body checks an unnamed byte at final ThingTemplate
`+0x4B0` for the Object and its contained-by Object at Object `+0x214`.
Either true byte forces the Boolean false. The two tests short-circuit to
one shared false path in retail; one C++ `||` expression reproduces it.

On false it writes `this+0x5C`, clears three Object model-condition bits only
if set, calls the notifier after each changed bit, then zeroes `this+0x58`.
The 40-byte condition field starts at Object `+0x110`; retail masks are
`0x02000000` in word `+0x120` (index 153), `0x01000000` in word `+0x11C`
(index 120), and `0x02000000` in word `+0x11C` (index 121). The shipped
name table at VA `0x012A6918` calls those indices `STUNNED_STANDING_UP`,
`STUNNED_FLAILING`, and `STUNNED`. The identities of the template byte
and PhysicsBehavior fields `+0x58/+0x5C` are not established.

The first scratch probe used two separate `if` statements and compiled to
200 bytes, placing `xor al,al` before the contained-by check. Combining the
same checks into one short-circuit `||` moved the false branch to the retail
location and produced a 196/196 exact masked probe with five relocations.
The strict byte/relocation gate is required before claiming coverage.
