# Assigned 008B3AA0 extent and native property dispatcher

The supplied 1940-byte dump spans three independently entered functions:

- 008B3AA0..008B3B6D inclusive: 206 bytes. One string cleanup EH state, RET at 008B3B6D; two INT3 bytes follow.
- 008B3B70..008B3C3D inclusive: 206 bytes. Fresh FS registration, distinct EH handler, RET at 008B3C3D; two INT3 bytes follow.
- 008B3C40..008B4233 inclusive: 1524 bytes including a 52-byte switch table at 008B4200. Fresh FS registration, six unwind states, RET 8 ending at 008B41FF. The table spans 13 DWORD entries and is followed by INT3 padding before 008B4260.

The first two bodies are also independently taken as native callback addresses at VA 00CB3FA5 and 00CB40AE in the third function. They call virtual slots 80h and 88h respectively after converting a type 1/42 stack value to a string. The third function handles property IDs 100..112 with default gaps. All source names retain the entry address; no original proprietary class identity is asserted.

## Typed dependency at RVA 008B2F50

The real REL32 call at VA 00CB3C70 targets VA 00CB2F50. The caller passes key at ESP+8 and owner at ESP+4 with the original receiver in ECX, and uses EAX as a value pointer (flags at +4).

Independent callee evidence: VA 00CB2F72 saves incoming ECX in EBX. VA 00CB2F5E reads first stack argument and tests it; VA 00CB2F7A reads the second argument, dereferences its first DWORD, reads the length WORD at +2, and passes bytes at +8 to the same property hash helper at 00CD5DC0. Sixteen decoded real returns through VA 00CB3868 use RET 8. The body selects property callbacks and returns value pointers. Thus a two-argument __thiscall with a value-pointer result is established independently of matching the new caller. PropertyLookup008B2F50::lookup is an address-derived ABI view only.

Pin: ?lookup@PropertyLookup008B2F50@@QAEPAURva00899560Value@@PAVNativeProperties008B3C40@@PAUString008B3C40@@@Z at RVA 008B2F50. Existing generated dump remains its owner; this adds no converted bytes.

## Source shape

The 1824-byte array dispatcher matched on its first complete draft. The 206-byte wrappers required an unsigned kind accessor and the native null guard in an inline method taking the string by reference. The 1524-byte dispatcher required force-inlining the small boolean constructor, matching all pooled allocations and all six retail EH states. Compiler flags remained O2 /EHsc throughout final sources. Mechanical EH searches did not improve the candidates.

GhidraSQL exact-address pseudocode queries for the assigned carved dump returned zero rows. Subsequent database inspection requests timed out; the running server was not restarted or stopped. Retail Capstone disassembly, existing exact neighbors, hash switch tables, and EH unwind maps supplied the control-flow evidence.
