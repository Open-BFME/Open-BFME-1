# Per-unit sound lookup at 0x00416FE0

Three byte-matched callers previously named this body
`ThingTemplate::getPerUnitSound`, because their TU-local `Object` views named
vtable slot `+0x28` `getTemplate`. Retail gives that slot a different meaning:
`Object` vtable `0x0109EE58` slot 10 contains ILT `0x0002074D`, which jumps to
the matched seven-byte `Object::getDrawable` body at `0x001BE440`. The getter
returns `[Object+0x80]`. In `AIChargeTargetState::onEnter` (`0x0017ECB0`),
`TurretAI::startRotOrPitchSound` (`0x0018D390`) and
`Rva00174A20State::update` (`0x00174A20`), the result of that same virtual
call becomes `this` for the call through ILT `0x0000FD44`. The ILT jumps to
`0x00416FE0`. The separately matched DozerAction caller also passes a
Drawable to the per-unit sound lookup.

The three matched TUs now use `Drawable` names and their object relocations
name `Drawable::getPerUnitSound`; each still byte-verifies against retail,
including the call through `0x0000FD44`. The misleading ThingTemplate pin and
its derived `reloc_names.csv` candidate were removed. This is an identity
correction, not a new body: `0x00416FE0` remains a generated dump because the
banked clean C++ implementation still differs in 19 non-relocation bytes.
The existing Drawable pin at the body is identity evidence from the callers,
not acceptance of that C++ bank. A `route=` pin on the thunk would require a
matched body under this identity, so the matched callers retain their
TU-local thunk aliases until the body can be converted.
