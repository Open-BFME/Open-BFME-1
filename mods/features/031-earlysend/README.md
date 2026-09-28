# 031-earlysend: guest send delay 92 ms → 0 ms

In retail, a guest's command waits up to 200 ms on the guest's own machine
before it is sent, because the outbound list is drained only on a logic tick.
With this mod it leaves on the engine tick that created it. The host never had
this delay: it stamps and executes its own commands inside the same tick.

It is in the repository bundle, `mods/dist`, and ships with `033-retrytime`,
never alone.

## What players get

Across the measured captures, a guest command's local hold was 87–96 ms in
every retail capture and 0.1 ms in every capture with the fix, including 11 real
build orders.

The gain is invisible on a bad link: at 150 ms round trip and 3% loss, retail's
~2000 ms freezes swamp 92 ms, which is why it ships paired with `033`. It shows
on a good link (−152 ms on a clean LAN) and against a baseline whose freezes are
already fixed (−100 ms median over two matches).

## How it works

Logic frames run at 5 Hz, and retail drains the outbound command list only from
`Network::update`, on a logic tick. A detour at `0x0006BA44`, in the client half
of the engine frame (about 30 Hz), calls the same pump,
`Network::getCommandsFromCommandList` (`0x00A828D0`), under retail's own guards.
It runs just before the engine's own `liteupdate(FALSE)` at `0x0006BA53`, which
then puts the command on the wire. The payload is about 106 bytes in a code
cave.

It does not raise the 5 Hz logic rate, which would speed up the game, and it
keeps the router's frame-assignment and ordering rules. Commands only arrive
earlier, which can change the frame that receives one.

## Build

`python3 tools/modbuild.py --dist` builds the bundle into `mods/dist/`.

## Safety and limits

* Every player in a lobby must run the same build; the launcher's MD5 check
  enforces this.
* The logic rate stayed at 5.000 frames per second across twelve test matches.
* Measured with two players only; eight-player behaviour is modelled, not
  measured.

Protocol and evidence:
[multiplayer-lockstep.md](../../../targets/game/reverse/network_delay/multiplayer-lockstep.md),
[FINDINGS.md](../../../targets/game/reverse/network_delay/FINDINGS.md).
