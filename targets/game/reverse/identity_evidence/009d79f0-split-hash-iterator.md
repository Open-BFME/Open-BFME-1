# Retail ranges 0x009D79F0 and 0x009D7A20

The former 76-byte gen-dump row combines two independent functions. Decoding
inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe gives:

- 0x009D79F0: two stack arguments; reads key pointers at +0/+4, accumulates
  `hash = hash * 5 + signed_byte`, and divides by the second argument. RET 8
  starts at +0x2B and ends at +0x2E (46 bytes). Two INT3 bytes follow.
- 0x009D7A20: a fresh entry loads its second stack argument, saves ESI, saves
  incoming ECX in ESI, and calls 0x009D7680. It writes the returned node and
  receiver to the first stack argument, returns that address, and ends in
  RET 8 at +0x19 (28 bytes). INT3 begins at +0x1C.

Neither function flows into the other. The first body has no direct calls and
uses no receiver fields. Its exact public/template owner is unproven, so the
source uses Rva009D79F0Owner and a two-pointer Rva009D79F0Key view. The source
algorithm is also present in STLport stl/_string_hash.h; that resemblance does
not identify this particular template copy.

The second body has the member return-by-value ABI for the two-word STLport
iterator. Its only direct call is the independently matched basic_string/int
hashtable `_M_find` at 0x009D7680, in Rva009D8580StringMapOperator.cpp. That TU
establishes the callee's native template type from its same-object operator[]
caller and pair construction, and already reconstructs another 28-byte iterator
wrapper at 0x009D7840. The _hashtable.h find implementation constructs an
iterator from `_M_find(key)` and `this`. Rva009D7A20Owner keeps this distinct
copy address-derived; no new canonical template identity or callee pin is
proposed.
