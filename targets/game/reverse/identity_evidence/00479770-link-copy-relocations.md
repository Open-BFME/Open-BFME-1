# GameWindow::winPointInChild selected-copy repair

Retail RVA 0x00479770, extent 399 bytes. The freshly compiled owner was
instruction-byte identical outside relocation fields, but its REL32 at +0xF9
named `??0AudioEventRTS@@QAE@ABVAsciiString@@W4ObjectID@@@Z`. That ledger
identity lives at 0x000B4350. Native +0xF9 instead calls ILT 0x00025306,
which jumps to 0x000B2CC0, the separately matched `int` overload
`??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z`. Its definition in
AudioEventRTSCopyAndLifetime.cpp stores the argument at +0x28 (time of day).
The two constructors have different 188-byte and 159-byte retail bodies.

The additive ObjectID pin at ILT 0x00025306 explained the old 100% byte-gate
result; it did not prove the relocation identity. RetailTruth correctly gives
the ledger identity priority. No verifier rule or pin was changed.

The owner now declares and calls the int overload with the same value 2.
GameWindow.cpp's competing present-unmatched definition was removed; the
matched implementation remains in GameWindowTextAndHitTest.cpp. Both emitter
TUs must be supplied to link_check so the census's discarded definition is
replaced by current object facts.

Validation: build.sh preserves the owner's 2/2 and emitter's 55/55 matched
rows. Fresh RetailTruth no longer returns wrong: the five REL32 targets are
StringBase<char>'s C-string constructor, the int AudioEventRTS constructor,
releaseBuffer, AudioEventRTS destruction, and the recursive winPointInChild
call. It returns unknown solely for TU-local EH data. The existing selected
copy rules remain responsible for that result. Relevant link verifier suites:
121 tests passed, including rejection of pins that conceal a wrong callee.
