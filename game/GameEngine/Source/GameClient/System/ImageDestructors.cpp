// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/shims/sweep
// Image complete and scalar-deleting destructors, retail 0x5D2840/117B and
// 0x5D2BD0/30B. Matched Image constructor0x5D2260 installs vtable0x0110FFEC;
// slot0 -> ILT0x294CE -> scalar wrapper -> ILT0x3B719 -> complete destructor.
// The named preview image factory constructs this same object and its owners
// invoke virtual deletion. This recovers the real class, not a byte-shape alias.
//
// The holder at +0x2C releases its first pointer via0x9EB7A0: the independently
// matched TextureBaseClass::Release_Ref WORD-refcount/flags contract. Keep the
// holder's type address-qualified because its original class name is unknown.
// Strings at +4/+8 use canonical AsciiString layout and genuine releaseBuffer.
// Including canonical Code texture.h is necessary: the old reference header
// inlines an incompatible RefCountClass decrement instead of the retail call.

void __cdecl operator delete(void *block);

#include "ascii_string.h"

inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

#include "../../../../Libraries/Source/WWVegas/WW3D2/texture.h"

class Rva005D2840HolderView
{
public:
	~Rva005D2840HolderView()
	{
		if (m_texture != 0)
			m_texture->Release_Ref();
	}

	TextureBaseClass *m_texture;
};

class Image
{
public:
	__declspec(noinline) virtual ~Image();
	AsciiString m_name;
	AsciiString m_filename;
	char m_unmodelled0C[0x20];
	Rva005D2840HolderView *m_rawTextureData;
};

Image::~Image()
{
	delete m_rawTextureData;
}
