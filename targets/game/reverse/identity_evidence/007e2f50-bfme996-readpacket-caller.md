# 0x007E32A0 calls BfmeB996::readPacket at 0x007E2F50

`python3 tools/dis_retail.py 0x007E32A0 48` shows that
`?dispatchWhenReady@Rva007E32A0State@@QAE_NHHH@Z` calls ILT 0x0003F80F with
five stack arguments and returns the callee's AL value directly. The ILT body
at 0x0003F80F is an unconditional `jmp 0x007E2F50`. The matched identity at
that destination is `?readPacket@BfmeB996@@QAEDPAPAHPAH1PADD@Z`, landed in
`game/GameEngine/Source/Common/BfmeConv996ReadPacket.cpp`.

The old `ForwardView` type was not a recovered identity. It existed only so the
previously unidentified bank could express a five-argument member call and
preserve the `ret 0xc` shape. Once 0x007E2F50 was resolved, declaring the real
callee class at the call site removed that scaffold and kept the caller
byte-exact. A declaration-site type-name correction therefore does not discard
a proven name.
