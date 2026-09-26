// cl: /DNDEBUG /MD /O2 /EHsc

// These carved retail bodies contain only `ret`. Their callers reach them
// through anonymous ILT thunks, so the address-derived names intentionally
// make no semantic owner claim.
void dup_001b08a0() {}
void dup_001b4cf0() {}
void dup_0020dbe0() {}
void dup_00213cf0() {}
