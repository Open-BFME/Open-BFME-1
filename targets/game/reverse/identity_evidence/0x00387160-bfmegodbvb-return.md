# `bfmeGoDVBb` ABI evidence

The retail `bfmeUseDXI` body at RVA `0x00583190` calls ILT `0x00048653` with a result buffer and the banner entry's integer argument. The body passes the returned buffer to the ScriptEngine virtual slot at `+0x88`. It then releases the buffer through the string routine at RVA `0x00887940`.

The `bfmeGoDVBb` body at RVA `0x00387160` passes the result buffer and integer to ILT `0x0002AB0D`. It returns the result buffer in EAX. The matched `BfmeSubDVB::bfmeTwoDVB(int)` body at RVA `0x00361E80` returns `BfmeSharedString`. These instructions support `BfmeSharedString` by value with one integer argument as the caller's ABI for `bfmeGoDVBb`.

`BfmeConv787.cpp` keeps the two-pointer source declaration that reproduces the 38-byte body. The ledger records the caller's ABI name and sets `object-symbol=` to that existing declaration. The pin at ILT `0x00048653` routes to the matched body at RVA `0x00387160`.
