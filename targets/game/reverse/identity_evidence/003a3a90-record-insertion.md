# RVA 0x003A3A90: 184-byte record lifetime and insertion

The 146-byte body is a one-argument thiscall (`ret 4`), ending at 0x003A3B22. It constructs one 184-byte temporary, copies the input's three words to its +0xA4/+0xA8/+0xAC, inserts the temporary at the beginning of the vector at receiver+0x2C, and destroys it on both normal and exceptional exit. The owner and input remain address-qualified because their semantic identities are not proved.

The entire 270-byte constructor at 0x003A18D0, reached through ILT0x22F0C, constructs ten 12-byte subobjects at +0x2C, initializes the trailing string at +0xB0 and the words through +0xB4, then returns its receiver without stack arguments. The full 90-byte destructor at 0x002BC7A0, reached through ILT0x36241, releases the string at +0xB0 and destroys the same ten-element array. These prove the lifetime and width without relying on the destructor's competing semantic ledger labels.

The third callee, 0x003A35F0 through ILT0x2B9F9, is the already-landed 300-byte canonical STLport `vector<Rva003A35A0Element>::insert`. Its two stack arguments are position and element reference; its allocation and pointer increments use the same 184-byte stride. The new TU reuses that address-qualified element specialization and its existing constructor/destructor symbols. No pins or shared headers changed.

Validation: the simplified member access `m_records.insert(m_records.begin(), temporary)` retains the worker's exact 146-byte result. The scoped add_match gate verifies 1/1, including call and EH relocations. The old ASM is untouched; boundaries and total exact coverage are unchanged. The conversion adds 146 C++ bytes, not a generated-source reclassification.
