# PSThreadClass::tryLogin — RVA 006549C0

The former `_BFMENetworkBackendEventCallback@40` label is not a callback ABI.
The complete 375-byte retail body enters with its thread in ECX, returns a
boolean in AL, and ends with RET 40 after destroying three 12-byte STLport
strings. Its four arguments are profile ID followed by nickname, password,
and email, all three strings by value. The dispatcher at 0065CA50 calls it
three times through ILT 000276B0 with exactly that receiver and argument order.

Identity is supported independently of the new body's byte shape:

* `PersistentStorageThread.cpp`'s reference `PSThreadClass::tryLogin` has the
  same private bool member signature, validation buffer, persistent-auth
  wait loop, and login/done state pair. The retail pair is +50/+51.
* The dispatcher's call to independently authored 29-byte
  `PSThreadClass::tryConnect` at 006517B0 uses the same receiver. Both sources
  use the adjacent GameSpy persistent-storage API and operation counter.
* Retail callback 006517E0 is a complete 25-byte cdecl function taking five
  parameters: it checks argument 5, stores `argument3 != 0` at thread+50,
  then stores true at +51. Its pointer is supplied to the independently
  vendored `PreAuthenticatePlayerPartner` at 009D4D10. The source retains
  that callback's existing address-derived symbol with a typed adapter.
* The constructor at 006547F0 installs vtable 0111988C, clears +50/+51/+58
  and +54, and stores a mutex pointer at +68. That vtable's +8 dispatch
  route reaches 0065CA50. These witnesses agree with the storage thread
  source and its BFME additions; no broader legacy family rename is made.

BFME behavior differs from the Zero Hour reference: it duplicates strings
from global VA 012F71B4 virtual slots +2C and +30, generates the response from
slot +30, and authenticates with the slot +2C token. The global's queue
identity is also witnessed by the authored lobby callbacks, but the accessor
names remain address-derived because their semantic identity is not proven.
The obsolete nickname/password/email values still receive normal destruction.

`tools/callees.py 006549C0 375` identifies all eight direct callees. Their
contracts agree with the native calls: node deallocation and operator delete,
BFMEDuplicateString, GenerateAuthA, IsStatsConnected, GetChallenge,
PreAuthenticatePlayerPartner, and PersistThink. The independently authored
62-byte BFMEDuplicateString at 008543B0 only checks the pointer, calls CRT
malloc, and copies bytes; its explicit nonthrowing declaration is justified
by that complete implementation, not by the desired caller shape. GameSpy
API signatures are checked against the vendored 2004 gstats/gpersist headers.

Validation: native isolated TU produces all 375 bytes exactly modulo legitimate
relocations. The full scoped build checks all direct calls and repeated data
references. No symbols.csv pin is added. The old naked function is removed
from native_network.cpp; its other bodies retain their existing ownership.
Model GPT-6; session 2026-09-26; t=22 minutes including dispatcher research.
