# RVA 0x003A3B50: record append

This 206-byte one-argument thiscall ends at 0x003A3C1E with ret4. It constructs a 184-byte element, copies the three input words to +0xA4/+0xA8/+0xAC and appends it to the vector at receiver+0x2C. Its full lifetime follows the contracts documented for the already-landed 0x003A3A90 and 0x003A39C0 siblings.

The old bank hand-declared a partial STLport vector with a pointer-taking push_back and forced that implementation inline. Replacing that shell with the actual STLport vector header and its reference-taking push_back recovers all 206 bytes, including the placement-copy lifetime and overflow path. The source retains the existing address-qualified element family rather than guessing the game class.

The four independently established callees are default constructor 0x003A18D0 through ILT22F0C, copy constructor 0x003A2360 through ILT1F573, vector overflow insertion 0x003A3410 through ILT2798F, and destructor 0x002BC7A0 through ILT36241. The full 130-byte copy constructor confirms the 184-byte layout: prefix words, ten 12-byte points, three words at A4..AC, AsciiString at B0 and trailing word B4. Existing symbols resolve every call; no pins or headers changed.

The scoped gate verifies 1/1 including all relocations. The retired bank remains in immutable attempt history and the original ASM is untouched. This adds 206 rebuilt C++ bytes without changing total exact coverage or function boundaries.
