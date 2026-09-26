// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The command-mask caller at 0x004A3D50 reaches this body through ILT
// 0x0003F18E.  It intersects ten mask words and reports whether any remain.

typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Rva001ED9A0MaskWords
{
	UnsignedInt words[10];
};

class Rva001ED9A0Mask
{
public:
	Bool intersects(const UnsignedInt *mask);

private:
	Rva001ED9A0MaskWords m_words;
};

Bool Rva001ED9A0Mask::intersects(const UnsignedInt *mask)
{
	Rva001ED9A0MaskWords result = m_words;
	for (UnsignedInt index = 0; index < 10; ++index)
		result.words[index] &= mask[index];
	for (UnsignedInt index = 0; index < 10; ++index) {
		if (result.words[index] != 0)
			return true;
	}
	return false;
}
