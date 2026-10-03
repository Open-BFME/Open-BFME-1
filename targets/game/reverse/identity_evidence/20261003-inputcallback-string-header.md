# Input-callback parser canonical string

Severity: HYGIENE. AGENTS.md requires: "never redeclare a type a header already covers: #include it".

RVA00486900/130B retains its existing parseInputCallback identity, signature and address-qualified lookup binding. The Zero Hour GameWindowManagerScript.cpp twin scans a quoted callback name and stores the lookup result. No new lookup owner/function identity is inferred.

Replace the local AsciiString declaration with canonical ascii_string.h and call its actual StringBase<char>::set explicit-length overload887D20. Canonical str() uses the exported TheNullChr atVA0107388B, matching operand+0x5C. Ghidra/PE independently agree on all130B plus padding: finalRET486981,CC486982. Direct lookup routes remain3ADD7->8FFC0 and25CD4->105280 with flag1; strtok remains the PE import atIAT013594D8.

Strict build passes1/1 body, one full quote literal and seven DIR32 references. No shared-header, pin, ledger, identity, extent or coverage changes. Existing opaque lookup declaration is preserved, not promoted.
