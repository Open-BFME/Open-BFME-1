# W3DDisplay::init relocation dependencies at 0x006ED5B0

Retail vtable `0x0111EDD0` slot 1 routes through ILT `0x000323D0` to this
body. The final `ret` is at `+0x71F` and padding begins at `+0x720`, giving
1,824 bytes. The bank at `reverse/attempts/0x006ed5b0.cpp` currently compiles
to 1,824 bytes with 101 relocation sites and zero differences outside those
sites. This is a masked probe result, **not** a verified byte-match landing.

The strict production resolver still reports nine unresolved COFF call names.
Each retail target below was decoded from the matching relocation offset; a
known address or matched body does not by itself prove the bank's declaration.

| Offset | Bank declaration's target | Current retail evidence / issue |
| --- | --- | --- |
| `+0x047` | `Rva006F6330` constructor | ILT `0x00034F86` reaches the now-matched `W3DFileSystem` constructor at `0x006F6330`; the bank has the stale opaque declaration. |
| `+0x12A` | `Rva00712F60` constructor | ILT `0x000337DA` reaches dump body `0x00712F60`; constructor identity and ABI remain unverified. |
| `+0x2FB` | `GameLODManager::rva0007E0F0` | ILT `0x0002DE02` reaches matched `OptionPreferences::getIdealStaticGameDetail` at `0x0007E0F0`; the bank's owner name is wrong. |
| `+0x32D` | `GameLODManager::rva0007C350` | ILT `0x0003852D` reaches `0x0007C350`, currently claimed under an address-derived name; the bank's owner and method semantics remain unproved. |
| `+0x443` | `Rva00908E50` | ILT `0x008FD330` reaches matched `DX8Wrapper::Set_Swap_Interval` at `0x00908E50`; the bank has the stale opaque declaration. |
| `+0x525` | `Rva00938620(AsciiString, AsciiString)` | Retail calls body `0x00938620`, but its matched ledger row says `Load_Asset_Dat(void)`. The callee reads two caller-supplied strings at `[esp+0x1AC]` and `[esp+0x1B0]` after its prologue and releases both before a plain `ret`. Its current `void`-argument declaration is contradicted by the retail ABI; its semantic name is not proved here. |
| `+0x566` | `Rva006FC970` constructor | ILT `0x00007FC2` reaches dump body `0x006FC970`; constructor identity and ABI remain unverified. |
| `+0x601` | `Rva006E6C10::init` | ILT `0x00028B1E` reaches matched `Rva006E6CC0::apply`; the bank's owner/method declaration needs reconciliation with that body. |
| `+0x68D` | `Rva006E6C10::setFont` | ILT `0x00013C8C` reaches matched `Rva006E6CE0Source::setAndNotify`; the bank's `setFont` claim is not established by the matching call bytes. |

The `W3DFileSystem` and swap-interval rows may now be repaired using existing
verified identities. The remaining entries need independent callee ABI and
owner evidence, including correction of the `0x00938620` row's signature,
before this bank can replace the generated dump. Do not add aliases merely to
make the relocations green: pins are additive and cannot prove identity.
