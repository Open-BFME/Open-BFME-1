# Opaque broadcaster at 0x0081D520

Retail 0x0081D520 is an 82-byte physical body, not an ILT thunk. It saves EBX,
ESI, and EDI, reads an array of listener pointers from `this+0x14` and
`this+0x18`, and iterates it by four-byte elements. At +0x2A..+0x3A, it loads
listener vtable slot +4 and passes six words: its first incoming argument, the
broadcaster `this`, and its remaining four incoming arguments. Its epilogue at
+0x4F is `ret 0x14`, so the direct callee accepts five stack words and cleans
20 bytes. The previous pin `?handle@Handler@@QAEXH@Z` and matched caller's
comment/declaration claimed only one `Int` argument, which requires `ret 4`
under that thiscall ABI. The previous source explicitly said the owner had no
named identity; `Handler` was a local descriptive guess, not a caller, export,
or vtable witness.

There are three direct retail callers. The already matched
`Rva004942C0Owner::run` at 0x004942C0 prepares four float words at +0x65..+0x81,
calls virtual slot +0x20 at +0x84, pushes its result at +0x87, and calls
0x0081D520 at +0x8A. It has no stack adjustment between these calls and resumes
by popping EDI and ESI. The anonymous bodies at 0x006EB500 (+0x39C call) and
0x006EE0C0 (+0x245 call) each have two float payloads and two zero payloads
under a pushed result of a virtual +0x20 call at the direct call site. These
call sites agree with the five-word cleanup; the identities of their virtual
callees and the broadcaster's semantic owner remain unproved.

Clean C++ for `Rva0081D520Owner::broadcast(Int,Real,Real,Real,Real)` probes at
82/82 exact bytes with no relocations. Correcting the matched caller's local
view to call virtual slot +0x20 with no explicit arguments and to pass its four
float payloads to `broadcast` probes at 146/146 exact bytes, with two aligned
relocations. `tools/add_match.py --replace-rva 0x0081D520` and scoped
`./build.sh` verify both claims. The old `Handler::handle(Int)` pin appeared
in no other source or bank; it is replaced with the address-derived five-word
symbol at the physical body. `pin_consistency.py` marked both spellings
location-consistent, which does not validate ABI or semantic identity. No
semantic owner is asserted by the replacement.
