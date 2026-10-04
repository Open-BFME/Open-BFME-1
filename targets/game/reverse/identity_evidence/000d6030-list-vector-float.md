# Address-qualified list/vector float body at RVA 000D6030

The complete retail extent is 162 bytes. It is a native thiscall with one
stack pointer argument and an x87 float result; both exits use RET 4.
The final RET occupies 000D60CF..000D60D1, followed by INT3 at 000D60D2.
No named caller establishes the receiver class, so the owner and method
retain the address-qualified Rva000D6030 identity.

The receiver has a sentinel-headed doubly linked list at +640. Each node
contains next/previous pointers and an item pointer. The item has a filter
pointer at +0, a three-pointer float vector at +4/+8/+C, and object ID at
+10. Native STLport vector<float>::size/operator[] reproduces the exact
end-then-start load ordering and four-byte element arithmetic.

The direct call through ILT 0001F253 reaches the established
GameLogic::findObjectByID body at 0009A510. Its existing
Common/Thing/GameLogicObjectLookup.h declaration is included instead of
redeclaring the class. The global pointer load is at VA012F0898.
The returned object is rejected if null, byte+118 bit8 is set, or
dword+90 bit80000 is set.

The second direct call is ILT 0001B437 -> 0039F0A0. Its receiver is ECX,
return is boolean AL, and RET12 consumes three stack pointers. Existing
BannerThingCounterAdd and Rva003A04A0FilterAccepts declarations agree on
accepts(const void*, Player*, Player*); this body supplies two null players.
The first argument is independently consumed as a ThingTemplate: the
callee loads it into EBP at 0039F0BC, then copies EBP to ECX at
0039F2A9/0039F2D7 for calls at 0039F2AB/0039F2D9 through ILT0003E80B.
That route reaches the established ThingTemplate::isEquivalentTo body
at 0013FE10, whose identity is witnessed by named Team/Script callers.

An accepted item overwrites the float result only when the shared index
is below that item's vector size. The index increments even when the
item's array is short; retail does not terminate the walk on a short array.
The result starts at zero and finishes with +1.0f; null input returns 1.0f.
Both retail constant operands read VA01075334, bytes 0000803F, in immutable
.rdata. Using literals removes the old bank's pin-only constant dependency.

The complete clean-C++ body verifies with strict REL32 resolution, no
unresolved call or masked fallback, both float constants, and the global
DIR32 address. No shared header, pin, assembly body, or verifier is changed.
