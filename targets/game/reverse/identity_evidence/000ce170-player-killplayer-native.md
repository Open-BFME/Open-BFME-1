# Player::killPlayer at RVA 0x000CE170

## Identity and extent

GeneralsMD `GameEngine/Source/Common/RTS/Player.cpp`, `Player::killPlayer`
at line 2055, supplies the named twin: evacuate every instance of every owned
team prototype; mark the player dead; kill those teams; preserve an AI player
in a single-player mission; withdraw its remaining money. BFME replaces the
later Zero Hour local-player/UI arm with a PlayerList virtual call at +0x2C.
The existing named lift at this address used the same signature.

Independent pefile/Capstone decoding of the retail-1.03-unpacked image gives
plain RETs at RVA 0x000CE20A and 0x000CE227, with INT3 at 0x000CE228. The
complete body is 184 bytes, with ECX=this and no stack arguments.

## Layout and callees

The loop reads the native STLport list sentinel at Player+0x288, then the
TeamPrototype instance-list head at +0x274. Both views already exist in
`Player.cpp`. The dead flag is Player+0x680, also named by the layout witness.
The mode-dependent player-type test remains an explicit BFME offset +0x2C;
the reference Player data layout differs and is not used for that read.

Retail call routes are:

- ILT 0x0000B582 -> Team::evacuateTeam at 0x000F3250.
- ILT 0x00022A70 -> 0x000C8A30, `mov eax,[ecx+0x14]; ret`. Reuse the
  existing `BfmeTeamInstanceLink::_bfme_nextInInstanceList` declaration/pin.
- ILT 0x000341D0 -> Team::killTeam at 0x000F6490.
- ILT 0x0001BE28 -> GameLogic::isInSinglePlayerGame at 0x00382B00. Its
  existing named native provider resolves the call without a new pin.
- ILT 0x00041894 -> Money::withdraw at 0x000C8610, returning with `ret 8`.
  The caller loads the amount at Player+0x4C and passes Money at Player+0x48,
  agreeing with the native Money header's four-byte Snapshot prefix.

The PlayerList dispatch is left as the address-derived `rvaSlot2C`; its
semantic method name is not established by this conversion. Both globals
reuse the native `ThePlayerList` and `TheGameLogic` declarations.

## Source-shape resolution

The served bank emitted 187 bytes, adding two two-byte inner-loop pads where
retail instead has one byte before the second outer loop. Restoring the twin's
`if (!team) continue;` inside **both** loops yields the exact 184-byte shape.
These conditions disappear from the executable instructions but affect
VC7.1's earlier loop-alignment decision. A bounded nine-choice search found
the combination in trial 4; the same result holds with native STLport lists.

The production body lives in the lift's documented `Player.cpp` and adopts
its existing Player, Team, Money, GameLogic, list and retail-view declarations.
It introduces no duplicate native type or header change. For the last call,
a direct Money receiver expression retains retail's argument-before-receiver
schedule; a separate pointer local had moved LEA before the pushes.

## Name-regression pairing

The bank's `PLAYER_LIST_SLOT` macro only generates anonymous dispatch slots;
the native TU's `RVA000CE170_SLOT` is the same padding with a scoped address
label. No slot identity is being retired. The checker also pairs the bank's
`Team::evacuateTeam` declaration with the unrelated pre-existing `j_0004494a`
declaration in the large destination TU. This is a false pairing: the native
body still calls `team->evacuateTeam()` and uses its existing Team header.
Exact-snapshot correction entries document both cases without renaming any
matched native callee.
