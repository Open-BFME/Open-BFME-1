# 0x000DB020 is Player::initFromDict, not GameLogic::updateLoadProgress

## Caller proof (strongest)

The only matched C++ caller of 0x000DB020 is `PlayerList::newGame` at
0x000E0060 (`PlayerListNewGame.cpp`, itself a ZH twin). It calls through ILT
stub 0x0000E5E8, whose retail bytes are `E9 33CA0C00`, targeting
`0x0000E5E8 + 5 + 0x000CCA33 = 0x000DB020`. The caller's ledger notes already
record "initFromDict ILT 0xE5E8 pinned".

Zero Hour `PlayerList.cpp` (newGame) does exactly:

```
p->initFromDict(d);
```

A matched caller naming the symbol at retail's call site is the strongest
identity evidence (AGENTS.md).

## EA proof

`targets/game/reverse/ea_evidence.csv`:

```
0x000DB020,file,GameEngine/Source/Common/RTS/Player.cpp,wb1,
0x000DB020,name,Player::initFromDict,chain+direct,aligned
```

Route `chain+direct` with a WorldBuilder file anchor in `Player.cpp`, plus the
caller and ZH evidence above, jointly confirm this `aligned` item.

## ZH twin

`GeneralsMD/.../GameEngine/Include/Common/Player.h:220` declares
`void initFromDict(const Dict* d);`, defined at `Player.cpp:808`. Mangled:
`?initFromDict@Player@@QAEXPBVDict@@@Z`.

## Refuted claim

`?updateLoadProgress@GameLogic@@QAEXH@Z` at 0x000DB020 exists only as a
`__declspec(naked)` + `__emit` byte dump
(`GameLogicUpdateLoadProgressThunk.cpp`, object-symbol
`_bfme_GameLogic_updateLoadProgress_DB020`). A naked lift is not a conversion
and proves no name. No caller, export, ZH twin, or EA row supports
`GameLogic::updateLoadProgress` at this address; the row is retired with this
note as its tombstone reason, and the naked TU is deleted once the real
`Player::initFromDict` body verifies.
