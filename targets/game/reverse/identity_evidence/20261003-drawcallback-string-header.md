# Draw-callback parser canonical string

Severity: HYGIENE. AGENTS.md requires: "never redeclare a type a header already covers: #include it".

RVA00486A60/130B retains the existing parseDrawCallback identity and signature. The Zero Hour GameWindowManagerScript.cpp twin scans the opening quote, tokenizes with strtok, saves the draw-name string and resolves its name key through FunctionLexicon. Existing owner/callee names remain unchanged.

Include canonical ascii_string.h instead of the local class. The explicit-length assignment now names its actual canonical StringBase<char>::set overload, matching retail887D20. The canonical str() fallback is the exported TheNullChr atVA0107388B (operand+0x5C), replacing the local empty literal while preserving the retail address. PE/Ghidra independently agree over all130B and padding: finalRET486AE1,CC486AE2. Name-key/draw lookup routes remain3ADD7->8FFC0 and1907E->105420; strtok remains the PE import atIAT013594D8.

Strict source build passes1/1, one complete literal and seven DIR32 references. No shared-header, pin, ledger, identity, extent or coverage change.
