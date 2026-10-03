# RVA 001C15F0: native color getter structure

Retail starts after INT3 at 001C15F0 and ends with RET at 001C1673,
followed by INT3 at 001C1674 (132 bytes). Ghidra creation confirms the same
extent. The receiver uses primary slot10 (getDrawable), team +23C, and
indicator-color override +244, matching canonical Object. The two direct
calls are independently matched Team::getControllingPlayer (000EC8F0 via
ILT0002369B) and Drawable::setIndicatorColor(unsigned int) (004186E0 via
ILT00028C09). No source witness gives this method its original name, so it
stays Object::rva001C15F0.

The preferred bank remeasures 132 bytes with ten non-relocation differences.
Its manually expanded branches use EDX for the night color and schedule
receiver moves after argument pushes. Native getter structure fixes both:
Object's matched unsigned getIndicatorColor body and an equivalent local
unsigned night-color helper feed the real Drawable setter. The complete
132-byte caller then matches, including all three receiver-before-push sites.
ObjectTeamAndPlayer.cpp and Object.cpp independently supply the two getter
operations and player field offsets +1C4/+1C8.

The existing public getNightIndicatorColor returns signed Color/int. Using
that signed declaration, including a forceinline trial, grows this caller to
152 bytes. The final source does not introduce a competing unsigned public
method: its local static address-qualified helper returns the same 32-bit
color representation to the unsigned Drawable setter. This is reconstruction
structure, not a claimed additional retail function or source qualifier.
The existing getIndicatorColor signature remains unchanged.

Object/Thing uses the canonical header. TheWritableGlobalData uses its
canonical GlobalData pointer type with a local address-qualified view of the
observed +218 mode test; no compiled default or INI behavior is inferred.
No pin, shared header, assembly, volatile access, or barrier is added.

The exact old bank is archived as 001c15f0-original-bank.cpp.txt. Any narrow
snapshot-bound correction concerns comparison with its synthetic names, not
a rename of an established production identity. Only d_001c15f0 is replaced.
