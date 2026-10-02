# STLport string global initializers

All five retail bodies return at +0x22 and INT3 starts at +0x23 (35 bytes).
Each initializes the existing singleton with a native from-pointer string
constructor and registers its already matched cleanup wrapper.

| Initializer RVA | Stored pointer RVA | Global VA | Literal VA / payload | Cleanup RVA |
|---|---|---|---|---|
| 0x00C6D8B0 | 0x00EA5D04 | 0x0130BCB4 | 0x010892DC / * | 0x00C70CC0 |
| 0x00C6D9E0 | 0x00EA5D08 | 0x0130C098 | 0x01080FB4 / true | 0x00C70DD0 |
| 0x00C6DA10 | 0x00EA5D0C | 0x0130C08C | 0x0111C2A0 / false | 0x00C70DE0 |
| 0x00C6DA40 | 0x00EA5D10 | 0x0130C0A4 | 0x0107301C / empty | 0x00C70DF0 |
| 0x00C6DA70 | 0x00EA5D14 | 0x0130C080 | 0x0112F398 / wide true | 0x00C70E00 |

Narrow constructors route through the independently decoded E9 ILT at
RVA0x0003B318 to the existing matched native STLport `basic_string<char>`
from-pointer constructor at0x002D89D0 (113 bytes, PingThread.cpp).
The wide constructor routes through ILT0x000203CE to the existing matched
`basic_string<wchar_t>` from-pointer constructor0x00661750 (98 bytes).
Both constructor identities/prototypes already belong to native header
instantiations in the ledger. The existing S3SingletonForwarders cleanup
wrappers all load the corresponding global and tail-call its string release.
Application-level identities remain opaque; address-preserving initializer
names and existing receiver/cleanup symbols are retained.

The source includes the canonical `<string>` header. Explicit specialization
DECLARATIONS retain the existing out-of-line constructor bindings; they add
no body, shim type or new pin. The native allocator default argument creates
the retail one-byte stack temporary at `[esp+3]`. A qualified constructor
call is the compiler-supported spelling used by other exact STLport global
initializers. Placement new was independently tested but adds an EH frame;
no placement-new helper, member-pointer pun, assembly or linker alias is used.

Each body passes the strict gate independently, including full REL32 routes,
its existing singleton/cleanup DIR32 identities and baseline-read literals.
Final scoped verification is5/5, four literals plus one empty-string reference,
and ten global/cleanup DIR32 references. This batch converts175 bytes.
