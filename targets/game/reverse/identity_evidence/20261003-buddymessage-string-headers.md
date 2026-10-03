# BuddyMessage copy constructor canonical strings

Severity: HYGIENE. AGENTS.md requires: "never redeclare a type a header already covers: #include it".

RVA004EA520/120B retains its existing BuddyMessage copy-constructor identity and field layout. Zero Hour GameNetwork/GameSpy/PeerDefs.h declares the same timestamp, sender ID/nickname, recipient ID/nickname and wide-message sequence. No new owner, field or function name is proposed.

Replace duplicate local AsciiString and UnicodeString declarations with canonical headers, retaining the TU-visible wide copy-constructor delegation to StringBase<unsigned short>. Retail/Ghidra independently agree on all120B plus padding: narrow copy calls887B60 for offsets8 and16, wide copy888400 for offset20, full RET4 at4EA595..4EA597, CC begins4EA598. Existing exception states preserve member-construction lifetimes. Callees were inspected before editing.

Strict source gate passes1/1 body; no referenced strings/constants/data addresses occur in this function. No shared-header, ledger, pin, extent or coverage changes. This does not claim newly named cleanup actions.
