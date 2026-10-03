// cl: /O2
// Retail RVA 0x007E88A0, 11 bytes.  The receiver's identity is unproved.
// This leaf reads a word at +0x24 and returns whether it is nonzero.
// The old W3DVideoBuffer identity is refuted by that class's native vtable
// and BFME layout; see the tracked identity correction evidence.

class Rva007E88A0
{
public:
	bool method();
};

bool Rva007E88A0::method()
{
	return *reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(this) + 0x24) != 0;
}
