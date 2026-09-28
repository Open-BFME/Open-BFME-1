# 0x0053E390: OnlineStateUpdate00544E40::createGame0053E390

## Owner

The matched `?update@OnlineStateUpdate00544E40@@QAEXXZ` (0x00544E40) switches
on `this+0x188`. In state 4 it calls ILT 0x0000FB32 (`jmp 0x0053E390`) with
its own `this` in ECX. This body ends with `mov [ebp+0x188], 5`, so it advances
that same state field. The receiver is therefore the object update() runs on.
That class still carries an address name: no vtable, string or caller names it.
The method keeps the address token for the same reason.

## What the body does

The body is the BFME form of Zero Hour's `createGame()` in PopupHostGame.cpp:

- It constructs a PeerRequest through the matched ctor 0x004D51B0 (ILT
  0x000171FC) and destroys it through the matched dtor 0x004D52D0 (ILT
  0x00016BD5).
- It reads the name and password text entries (`this+0x1A0`, `this+0x1A4`)
  through `GadgetTextEntryGetText`.
- It sets request type 9 (Zero Hour's `PEERREQUEST_CREATESTAGINGROOM` with the
  BFME enum shift documented in `inputs/reference/shims/nat/.../PeerThread.h`).
- It assigns `text`, `password`, `ladderIP = "localhost"` and `hostPingStr`
  through the STLport `assign(first, last)` bodies 0x004D5600 and 0x000A5810.
- It sets the staging room's game name, allow-observers flag, ladder IP and
  port at +0x418, +0x429, +0x444 and +0x450.
- It posts the request with `TheGameSpyPeerMessageQueue->addRequest`.

The BFME additions are:

- `TheLanguageFilter->filterLine` on the name.
- Persisting the keys "PreferedGameName" and "PreferedGamePassword" through the
  embedded CustomMatchPreferences at +0x174. That receiver is proven by the
  matched `setAllowsObserver` (0x000ADD20) and `getPreferredMap` (0x000AC690)
  calls on it.
- An internal-IP word at request +0xF0.
- The preferred map's player count from TheMapCache.

## Callee name correction: AptLivingWorldWindowIndex -> Rva0009B4B0

The banked attempt called ILT 0x000019F6 through the pin
`?AptLivingWorldWindowIndex@@YAHHH@Z`. The ILT jumps to 0x0009B4B0. The ledger
matches that body as `?Rva0009B4B0@@YAHHH@Z`, one of the
`BFME_OBF_WRAPPER( Rva0009B4B0, g_Slot012C233C, ... )` obfuscation-hook
wrappers in `game/GameEngine/Source/Common/BigObfHookWrappers.cpp`. Here it is
called as `(exeCRC, exeCRC)` and its result becomes the request's exeCRC.
Nothing ties it to APT Living World windows. The conversion therefore calls
the ledger's own address name for the body, not the guessed pin name.
