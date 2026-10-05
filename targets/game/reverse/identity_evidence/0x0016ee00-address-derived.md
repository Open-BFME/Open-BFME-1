# Identity evidence for 0x0016EE00

The matched caller `AIAttackApproachTargetState::computePath` at retail RVA
0x00182360 calls ILT 0x0001041A with a `Coord3D*` destination and an `Object*`
attacker. The caller branches on the returned boolean, but it does not give the
callee a method name.

`targets/game/reverse/functions.csv` maps ILT 0x0001041A to generated thunk
`?j_0001041a@@YAXXZ`, with target token `FUN_0056ee00`. The thunk and target row
do not name a class or operation. The earlier partial source
`targets/game/reverse/attempts/0x0016ee00.cpp` labels its compiler emitter
`DestinationSearch0016EE00::find`, then states that identity is deliberately
address-derived. That emitter name records a source spelling for a probe, not
an identity proved by retail evidence.

Retail returns with `ret 8` at +0x29A and starts INT3 padding at +0x29D, which
proves the 669-byte extent. The caller proves the arguments and boolean use, but
does not prove the descriptive owner `DestinationSearch0016EE00`. The source
keeps the retail address in `Rva0016EE00::method` until independent identity
evidence names the operation.
