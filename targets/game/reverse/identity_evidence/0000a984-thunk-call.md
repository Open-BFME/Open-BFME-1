# 0x0000A984: the ILT thunk GetGameLogicRandomSeedCRC calls

Retail's `GetGameLogicRandomSeedCRC` at `0x00096A60` is 18 bytes:

    +0000  6a 00                 push 0
    +0002  6a 18                 push 0x18
    +0004  68 28 7c 2a 01        push 0x12A7C28        ; theGameLogicSeed
    +0009  e8 16 3f f7 ff        call 0x0000A984
    +000e  83 c4 0c              add esp, 0xc
    +0011  c3                    ret

The call relocation lands on the packed incremental-link thunk at
`0x0000A984` (`e9 c7 a8 05 00`, `jmp 0x00065250`), not directly on the packet
CRC body `BFMEComputeCRC` at `0x00065250`. `native_packet_crc.cpp` defines that
body, so naming it at the call site emits a relocation to `0x00065250` and the
copy no longer matches retail's relocation target.

`random_value.cpp` therefore names the thunk (`j_0000a984`, ledger
`0x0000A984`) at the call site, which emits `call ?j_0000a984@@YAXXZ` and lands
on retail's target. The thunk is defined by the byte-true generated scaffold
`game/gen_small/thunks_004.cpp` and jumps to the matched packet CRC.
`BFMEComputeCRC` keeps its own identity at `0x00065250` for its other callers.
