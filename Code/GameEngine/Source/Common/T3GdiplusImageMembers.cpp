// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the out-of-line GDI+ header members that retail emitted from
// gdiplusheaders.h / gdiplusbitmap.h.
//
// The cluster identifies itself through its callees: every body in it does
// `mov ecx,[esi+4]` and then calls a 6-byte `jmp [.idata]` stub, and the stubs
// resolve to gdiplus.dll GdipGetImageWidth / GdipGetImageHeight /
// GdipGetImagePixelFormat / GdipGetImagePaletteSize / GdipGetImagePalette /
// GdipBitmapLockBits / GdipBitmapUnlockBits. That fixes the object layout
// without guessing: the GDI+ Image wrapper is vptr at +0, the GpImage* handle
// at +4, and the mutable `lastResult` Status at +8, which is exactly what the
// `test eax,eax / je / mov [esi+8],eax` tail writes.
//
// That tail is SetStatus, not an if in the caller: the header spells it
//   if (status != Ok) return (lastResult = status); else return status;
// so both arms return the status, which is why the two-argument bodies fall out
// of the je into `xor eax,eax` rather than sharing one return.
//
// The calls are direct REL32 to the import stub, not `call dword ptr [__imp_]`,
// so the declarations here are plain __stdcall externs and the stub addresses
// are pinned in reverse/symbols.csv -- declaring them dllimport would emit the
// indirect six-byte form instead.
//
// GetPixelFormat is 32 bytes rather than 40 because its out parameter is not
// zero-initialised in the header; GetWidth/GetHeight/GetPaletteSize all carry
// the extra `mov [esp+0xc],0`.

typedef int INT;
typedef unsigned int UINT;
typedef int PixelFormat;
typedef int Status;

namespace Gdiplus
{

class GpImage {};
class GpBitmap : public GpImage {};
struct ColorPalette;
struct Rect;
struct BitmapData;

}

extern "C"
{
	Status __stdcall GdipGetImageWidth(Gdiplus::GpImage *image, UINT *width);
	Status __stdcall GdipGetImageHeight(Gdiplus::GpImage *image, UINT *height);
	Status __stdcall GdipGetImagePixelFormat(Gdiplus::GpImage *image, PixelFormat *format);
	Status __stdcall GdipGetImagePaletteSize(Gdiplus::GpImage *image, INT *size);
	Status __stdcall GdipGetImagePalette(Gdiplus::GpImage *image, Gdiplus::ColorPalette *palette, INT size);
	Status __stdcall GdipBitmapLockBits(Gdiplus::GpBitmap *bitmap, const Gdiplus::Rect *rect, UINT flags,
		PixelFormat format, Gdiplus::BitmapData *lockedBitmapData);
	Status __stdcall GdipBitmapUnlockBits(Gdiplus::GpBitmap *bitmap, Gdiplus::BitmapData *lockedBitmapData);
}

namespace Gdiplus
{

class GdiplusBase
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Image.h
class Image : public GdiplusBase
{
public:
	virtual ~Image();

	UINT GetWidth(void);
	UINT GetHeight(void);
	PixelFormat GetPixelFormat(void);
	INT GetPaletteSize(void);
	Status GetPalette(ColorPalette *palette, INT size);

protected:
	Status SetStatus(Status status) const
	{
		if (status != 0)
		{
			return (lastResult = status);
		}
		else
		{
			return status;
		}
	}

	GpImage *nativeImage;								///< retail this+0x04
	mutable Status lastResult;							///< retail this+0x08
	mutable Status loadStatus;							///< retail this+0x0C
};

class Bitmap : public Image
{
public:
	Status LockBits(const Rect *rect, UINT flags, PixelFormat format, BitmapData *lockedBitmapData);
	Status UnlockBits(BitmapData *lockedBitmapData);
};

// ?GetWidth@Image@Gdiplus@@QAEIXZ
UINT Image::GetWidth(void)
{
	UINT width = 0;
	SetStatus(GdipGetImageWidth(nativeImage, &width));
	return width;
}

// ?GetHeight@Image@Gdiplus@@QAEIXZ
UINT Image::GetHeight(void)
{
	UINT height = 0;
	SetStatus(GdipGetImageHeight(nativeImage, &height));
	return height;
}

// ?GetPixelFormat@Image@Gdiplus@@QAEHXZ
PixelFormat Image::GetPixelFormat(void)
{
	PixelFormat format;
	SetStatus(GdipGetImagePixelFormat(nativeImage, &format));
	return format;
}

// ?GetPaletteSize@Image@Gdiplus@@QAEHXZ
INT Image::GetPaletteSize(void)
{
	INT size = 0;
	SetStatus(GdipGetImagePaletteSize(nativeImage, &size));
	return size;
}

// ?GetPalette@Image@Gdiplus@@QAEHPAUColorPalette@2@H@Z
Status Image::GetPalette(ColorPalette *palette, INT size)
{
	return SetStatus(GdipGetImagePalette(nativeImage, palette, size));
}

// ?LockBits@Bitmap@Gdiplus@@QAEHPBURect@2@IHPAUBitmapData@2@@Z
Status Bitmap::LockBits(const Rect *rect, UINT flags, PixelFormat format, BitmapData *lockedBitmapData)
{
	return SetStatus(GdipBitmapLockBits(static_cast<GpBitmap *>(nativeImage), rect, flags, format,
		lockedBitmapData));
}

// ?UnlockBits@Bitmap@Gdiplus@@QAEHPAUBitmapData@2@@Z
Status Bitmap::UnlockBits(BitmapData *lockedBitmapData)
{
	return SetStatus(GdipBitmapUnlockBits(static_cast<GpBitmap *>(nativeImage), lockedBitmapData));
}

}
