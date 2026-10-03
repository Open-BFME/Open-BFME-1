# isValidMap canonical string header

Severity: HYGIENE. AGENTS.md requires: "never redeclare a type a header already covers: #include it".

RVA00457ED0/170B retains its existing `?isValidMap@@YA_NVAsciiString@@_N@Z` identity and MapCache view. The Zero Hour twin in GameClient/MapUtil.cpp also takes an AsciiString by value and checks emptiness before updating the cache, lowercasing and finding the name. No new owner or field identity is proposed.

Replace the local AsciiString/AsciiStringData declarations with canonical ascii_string.h. A TU-visible specialization of StringBase<char>::isEmpty preserves this caller's actual inline null/length test. The canonical forwarding toLower calls RVA00887DA0; both normal exits release the by-value string through RVA00887940. Retail's complete170B, independently checked with Ghidra memory and PE decode, has success RET00457F56 and final RET00457F79 followed byCC00457F7A.

Callees were inspected first; existing updateCache/find ILT routes00018F0C->00457E70 and000263D7->000773E0 remain unchanged. Strict build passes the existing1/1 body and two DIR32 references. No shared header, pin, ledger, extent or coverage changes.
