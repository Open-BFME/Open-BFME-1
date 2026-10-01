# gpDisconnect at RVA 0x008E9800

This corrects the opaque `?bfmeGoUJC@@YAXPAUBfmeConnUJC@@@Z` claim while
preserving its exact 44-byte extent. The canonical provider is the existing
2004 GameSpy Presence SDK C TU at
`game/GameEngine/Source/GameNetwork/GameSpy/gp/gp.c`.

## Independent identity

The matched `BuddyThreadClass::Thread_Function` at RVA 0x0063EB00 has a
LOGOUT case which clears the connecting/connected flags and calls this body.
The shipped BuddyThread source at
`game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp:331`
names that call `gpDisconnect(con)`. The reconstructed matched caller at
`BuddyThreadClassThreadFunction.cpp:353` retains the same public API call.
The existing `_gpDisconnect` symbols pin independently records this caller
and the target RVA 0x008E9800.

## Boundary and typed calls

Retail bytes at RVA 0x008E9800 are:

```text
568b74240885f674218b0685c0741b8b880801000085c975116a0156e8ff41000056e89927000083c40c5ec3
```

The body null-checks `GPConnection *` and the pointed-to connection, checks
the 32-bit simulation flag at offset 0x108, calls `_gpiDisconnect` at RVA
0x008EDA20 with `(connection, GPITrue)`, then `_gpiReset` at RVA 0x008EBFC0
with `(connection)`. It cleans up three argument words with `add esp, 0xc`
and returns at offset 43. The next matched SDK API `_gpIsConnected` starts
at RVA 0x008E9830; the intervening four bytes are padding.

`gp.h` declares `GPConnection` as `void *`. `gpi.h` defines `GPIBool` with
`GPITrue == 1`, and its `GPIConnection` places the simulation flag after the
256-byte error string and two preceding four-byte boolean fields, at 0x108.
The shipped `gpiConnect.h` declares `gpiDisconnect(GPConnection *, GPIBool)`;
`gpi.h` declares `gpiReset(GPConnection *)`. Both are C calls. Their matched
424-byte and 354-byte providers establish the two callee identities.

## Release difference and ownership

The public 2004 SDK release carried in the vendored TU stops after
`gpiDisconnect`. BFME retail additionally calls `gpiReset`; the replacement
adds that single call and documents the retail modification in the source.

The old opaque UJC definition has no source callers outside its own TU. Its
two supporting structs and callee declarations are used only by that orphan
body and are removed. The unrelated 61-byte `BfmeThingUJA::bfmeClearUJA`
sibling remains in `BfmeConv1334.cpp` and must still pass its scoped gate.

This is one body at one address, rehomed into its proven SDK identity. Its
provenance changes from the old authored opaque row to vendored SDK C with a
retail modification; it adds no matched bytes or authored C++ credit.
