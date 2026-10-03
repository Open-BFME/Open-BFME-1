# RVA 008B6F90: typed field store

The entry remains address-qualified. No EA method or owner identity is claimed.
The bank's Rva008B6D70Obj is the existing neighboring setter ABI view.

Retail PE disassembly and Ghidra agree: the 73-byte body starts with the
argument-count guard, returns at RVA008B6FD8 and is followed by INT3 at6FD9.
It loads the count at VA01338748 and argument-vector pointer at01338750;
the early return reads013379BC. These use the existing count/array/fallback
bindings, with no new data pin.

The call at008B6FB5 reaches the matched const AptValue::toInteger body00898300.
The call at008B6FC7 passes this in ECX and three stack arguments: this+20,
this+40 and the scalar at+60. Independent decoding of the complete207-byte
008B65E0 helper shows eight integer fields copied/adjusted through those two
pointers, and signed subtraction/comparison/division of its third argument.
It ends in RET12 at008B66AC; it does not consume incoming ECX. This supports
the existing refreshNeg integer-argument binding used by sibling callbacks;
the method spelling is inherited and does not prove a semantic operation.
The bank's void-pointer third argument was wrong. No new alias or pin is added.
The final call at008B6FCE reaches the existing AptInteger::Create at008A11E0,
passes integer zero, and receives the returned object pointer in EAX.

The original bank compiled73 bytes with five differences: it stored through a
separate int pointer before loading the scalar at+60. Merely correcting the
scalar type, using integer arrays, or exposing the full non-inlined adjustment
helper did not change that residue. Storing directly to m_rect[0], then passing
m_rect to the call, reproduces the retail load-before-store sequence. Removing
the now-unused pointer local preserves the match. The final source uses the
matched const integer conversion and native integer factory signatures.

The scoped add_match gate validates the73 bytes and all six relocations.
There is no assembly, volatile access, barrier, or helper-visibility dependency
in the final source.
