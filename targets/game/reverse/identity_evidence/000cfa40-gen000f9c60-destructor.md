# RVA 0x000CFA40: opaque record destructor

Baseline: BFME 1 retail 1.03 unpacked, SHA256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.

The native body begins at RVA 0x000CFA40 and returns at 0x000CFA8C (`ret`); the byte after that instruction is 0x000CFA8D, proving the 77-byte extent. It destroys the narrow string at +0x18 through 0x00887940 and the wide string at +0x14 through 0x008881D0, in reverse field order. It has no vptr store or virtual dispatch. The thiscall receiver is ECX, with no stack arguments or return value.

The existing matched copy constructor `Gen_000F9C60::Gen_000F9C60` at RVA 0x000F9C60 (115 bytes, `Common/BfmeMixedCopyWK.cpp`) copies integer data at +0, +4, +8 and +0x0C, a byte at +0x10, and UnicodeString/AsciiString at +0x14/+0x18. The native zero constructor 0x001C2E50 (25 bytes, `Common/R3ScalarFieldConstructors2.cpp`) zeros the same fields. Its transfer at 0x001C2E70 uses xferInt for the first four dwords, xferBool +0x10, xferUnicodeString +0x14 and xferAsciiString +0x18. This independently proves a nonpolymorphic 28-byte record: +0 holds data, not a vptr.

The matched 0x000F9FF0 copy places that record at +0x44 within a 96-byte outer object. In matched `Common/Rva000FB2E0Insert.cpp`, the temporary starts at ESP+4 and its member at ESP+0x48 is destroyed through ILT 0x0002671F, whose native five-byte jump reaches 0x000CFA40. The existing `??1Gen_000F9C60@@QAE@XZ` pin already names this address. Together, the constructor, field layout and real matched caller establish the existing opaque identity without asserting a semantic class name.

Actual AudioEventRTS is separately witnessed by native 162-byte destruction at 0x000B31F0. It stores vptr VA 0x01081D40 and destroys strings at +0x6C, +0x1C, +0x18, +0x14 and +4 plus counted metadata +8. That vtable's first entry is VA 0x0043A0DF, an ILT jump to its 30-byte deleting wrapper 0x000B33C0, which calls ILT 0x00026F35 to 0x000B31F0. It cannot be the 28-byte record at 0x000CFA40.

This change retires only the false AudioEventRTS destructor identity at 0x000CFA40 and changes the existing address-derived 0x0002671F forwarder's direct callee. No new pins or aliases are introduced. The pre-existing AudioEventRTS UAE pin at 0x0002671F remains debt pending independent EH-consumer analysis; it is not evidence for this corrected identity.
