# C1B799 cleanup and 37EAC0 pair-destructor binding

Retail parent RVA 003820A0 pushes handler C1B7B2. That handler loads
FuncInfo E0BBD0, whose map E0BBC0 state 1 (predecessor 0) points to C1B799.
Ghidra raw-memory search independently finds that action pointer at VA0120BBCC.
The action tests/clears bit 4 of EBP-18, destroys the temporary at EBP-14,
and conditionally returns at C1B7B1: exactly 25 bytes before the handler.
Its E9 at C1B7AC reaches ILT 00048CFC, which reaches real body 0037EAC0.

The type is supported independently of this cleanup's byte match. The already
matched ExperienceLevelSystem::rva00382210 (474 bytes) indexes its map at +8
through ILT 0003BB33 -> 003820A0 and assigns its list through 000175BC ->
00381E80. ExperienceLevelSystemMapOperator.cpp defines that native map as
hash_map<int, list<ExperienceLevel>>, and its full 293-byte operator[] is
already strictly verified. ExperienceLevelListCopyConstructor.cpp (00381DF0)
and ExperienceLevelListAssignment.cpp (00381E80) separately establish the
mapped list element, also witnessed by the matched node/element operations.
The map's value_type is pair<const int, list<ExperienceLevel>>. Its temporary
pair lives at EBP-14; the list is the second member at +4.

Independent retail decode of 0037EAC0:
- save ESI; form ECX+4 in ESI; call list clear via ILT 0004278A -> 0037DCA0;
- reload the list sentinel, test it, call operator delete at 00881EB0 if set;
- restore ESI; RET at 0037EADB, followed by INT3 at 0037EADC.
Thus this is a complete 28-byte body, not a jump stub. Its existing ledger
provider is the opaque BfmeThing927A::bfmeGo927A in BfmeConv927.cpp.

The native pair destructor emitted from ExperienceLevelSystemMapOperator.cpp
independently matches all 28 bytes modulo its two relocations. Those two
relocations name _List_base<ExperienceLevel>::clear (already pinned to
0037DCA0) at +7, and operator delete at +19 (00881EB0), exactly the retail
calls. No additional dependency pin or source change is necessary. The new
pair-destructor pin is at body 0037EAC0, not at ILT 00048CFC, and needs no
route exemption. It does not add a second ledger body or rename the existing
opaque provider. The dependent cleanup must pass the strict source gate.

Validation: pin_consistency.py --check passed. The ordinary build verifier
was called with an in-memory selected row for the 28-byte native destructor
(no ledger mutation); it reported Functions: OK 1/1 with both REL32s resolved.
The normal add_match source gate then verified the 293-byte parent and its
25-byte cleanup, Functions: OK 2/2. No body or shared header was changed.
