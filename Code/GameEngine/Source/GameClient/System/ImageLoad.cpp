// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport

// Open-BFME5: BFME Image texture loader, retail 0x005D31D0.
//
// The BFME branch loads mapped-image textures lazily.  The vendored Zero Hour
// Image class supplies the field layout, while the texture/asset-list helpers
// below retain the already matched BFME ABI at their call sites.

#include <new>
#include <set>
#include "StringInline.h"

typedef unsigned char Bool;
typedef unsigned short UnsignedShort;

static char *bfmeStringData(const AsciiString &value)
{
    return *(char **)&value;
}

static char *bfmeString(const AsciiString &value)
{
    char *data = bfmeStringData(value);
    if (data)
        return data + 8;
    return (char *)0x0107388b;
}

static __forceinline Bool bfmeIsEmpty(const AsciiString &value)
{
    char *data = bfmeStringData(value);
    return data == 0 || *(UnsignedShort *)(data + 4) == 0;
}

class TextureClass
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTexture
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mipCount, int format);

class Gen_00920a60
{
public:
	char m_pad00[0x0c];
	int m_uAddress;
	int m_vAddress;
};

class ShroudFilter : public Gen_00920a60
{
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);
};

class Gen_0090E810
{
public:
	void bfmeSetFlag(unsigned char value);
};

class AssetList
{
public:
	AssetList &operator <<(const AsciiString &name);
};

struct Gen_t_00140950_k4
{
	int m_value;
};

typedef _STL::_Rb_tree<Gen_t_00140950_k4, Gen_t_00140950_k4,
	_STL::_Identity<Gen_t_00140950_k4>, _STL::less<Gen_t_00140950_k4>,
	_STL::allocator<Gen_t_00140950_k4> > ImageAssetTree;

// The BFME asset-list constructor has the same first 0x14 bytes as the
// recovered STL tree destructor below.  Keep the proven constructor identity
// while supplying the nontrivial cleanup that retail tracks for this object.
class BfmeList950B
{
public:
	BfmeList950B(void);

	~BfmeList950B(void)
	{
		((ImageAssetTree *)this)->~ImageAssetTree();
	}

	char m_storage[0x14];
};

class Image
{
public:
    AsciiString getFilename(void) const
    {
        return m_filename;
    }
	void load(void);

private:
	char m_bfmePrefix[8];
	AsciiString m_filename;
	char m_padding0c[0x20];
	TextureClass *m_rawTextureData;
	unsigned int m_status;
};

extern void Rva009EBAC0(int value);

#define FirstUpdateSubsystem (*(void **)0x0134faa0)

// The retail Image getter is the 32-byte StringBase<char> copy accessor at
// 0x00520640, reached by its existing incremental-link thunk 0x000336AE.
#pragma comment(linker, "/alternatename:?getFilename@Image@@QBE?AVAsciiString@@XZ=?j_000336ae@@YAXXZ")

// ?load@Image@@QAEXXZ
void Image::load(void)
{
    Bool reject = bfmeIsEmpty(getFilename()) ||
        m_rawTextureData != 0 || (m_status & 2) != 0;
    if (reject)
        return;

	BFMEWaterTrackTextureHandle texture =
		BFMEGetWaterTrackTexture(bfmeString(getFilename()), 1, 0);

	((ShroudTexture *)&texture)->getFilter()->m_vAddress = 1;
	((ShroudTexture *)&texture)->getFilter()->m_uAddress = 1;
	((Gen_0090E810 *)&texture)->bfmeSetFlag(1);

	if (FirstUpdateSubsystem)
	{
		BfmeList950B assets;
		(*(AssetList *)&assets) << getFilename();
		Rva009EBAC0((int)&assets);
	}
}
