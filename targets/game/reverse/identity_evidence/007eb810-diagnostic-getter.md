# Diagnostic pointer getter at 0x007EB810

The six retail bytes are `A1 A0 A5 30 01 C3`: load the dword at VA
0x0130A5A0 into EAX and return, with no arguments or direct callees.
The old integer return declaration describes its width but loses the
pointer ABI established by independent producers and consumers.

The matched creator at 0x007EBAA0 allocates 0x14 bytes, writes vtable VA
0x01129D30 at object+0, and stores the object into this same global slot.
Vtable slot 3 points to the matched assertion formatter at 0x007EB920.
Matched FESL callers use the getter result as a pointer and dispatch this
slot with a message, file and line. Direct-global logging and assertion
bodies also load the same pointer cell. These witnesses establish the
pointer return independently of the existing candidate pin.

The owner now returns the existing opaque `struct Rva007EB810Diag *`
decoration `?Rva007EB810Get@@YAPAURva007EB810Diag@@XZ`. Its six bytes and
DIR32 target remain exact. The raw global declaration stays unchanged;
this repair supplies no data definition and claims no complete reporter
class identity.

Six callers previously declaring an integer result adopt the pointer
signature. Three local reporter views use `struct` consistently with the
existing pointer decoration; all their members were already public.
The seventh caller at 0x008063B0 keeps its separate local
`Rva008063B0Diag` view and `report` member, casts the canonical getter
result at its existing call site, and drops its sole alternate return-type
pin. That obsolete pin represented the same retail getter with a second
return decoration. The canonical typed pin is retained; no new pin is
introduced.

Scratch verification covers 65 matched rows in the eight affected source
files, 28 string literals, three empty references and 63 DIR32 references.
The new getter's actual `RetailTruth` verdict is `retail`. Two callers
already linked in the census retain their bytes and clean status. AddSlot
still has unrelated message-data debt, and the owner has existing global
data debt; neither is included in the 1,819-byte native gain preview.
The fresh native census is required before claiming that gain.
