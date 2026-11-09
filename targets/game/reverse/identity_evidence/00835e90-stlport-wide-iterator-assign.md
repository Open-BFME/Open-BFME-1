# STLport wide output-iterator assignment at 0x00835E90

The BFME1 53-byte body is bounded by INT3 and ends with RET 4. It
tests the iterator success byte at +4, reads the streambuf pointer at
+0 and calls the 31-byte wide `basic_streambuf::sputc` at 0x00835ED0.
The caller passes a single four-byte stack slot and the return value
from `sputc` is compared as a word against 0xFFFF. Both branches store
the result and return the original iterator pointer. The pre-existing
canonical pin for the wide iterator assignment identifies this address.

Donor: Open-BFME-2 `2bac16a657`,
`Code/Libraries/Source/WWVegas/WWLib/stlport_ostreambuf_iterator_assign.cpp`.
Its wide instantiation supplies the correct `wchar_t` traits and
unsigned 16-bit return type. Compiling the wide instantiation in the
existing BFME1 narrow provider preserves the narrow bytes and relocation.
The wide object has one REL32 to the rowed 0x00835ED0 callee. All other
bytes equal BFME1 retail. The old placeholder method has no source
caller and its unrelated sibling remains in BfmeConv1016.cpp.
