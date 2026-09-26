// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: three more out-of-line GDI+ header members from
// gdiplusheaders.h, the Graphics half of the cluster
// game/GameEngine/Source/Common/T3GdiplusImageMembers.cpp opened.
//
// The callees name them. Each body is a direct REL32 into a six-byte
// `jmp [.idata]` stub and the stubs resolve to
//   0x009F6C1C GdipGetImageGraphicsContext
//   0x009F6C22 GdipDrawImageI
//   0x009F6C2E GdipCloneImage
//   0x009F6C28 GdipAlloc
// which is exactly the callee set of Graphics::Graphics(Image*),
// Graphics::DrawImage(Image*,INT,INT) and Image::Clone().
//
// The layouts fall straight out of the operands and agree with the sibling TU:
// Image is vptr at +0 (it is the one GDI+ wrapper with a virtual destructor),
// the GpImage* at +4 and the mutable lastResult at +8, while Graphics has NO
// vptr -- 0x0005E070 stores no vftable -- so it is GpGraphics* at +0 and
// lastResult at +4. `mov ecx,[ecx+4]` in both Graphics bodies is
// image->nativeImage, which is why Graphics is a friend of Image.
//
// GdipAlloc is GdiplusBase::operator new, and the `test eax,eax / je` after it
// is the compiler's null guard on a class-specific operator new, not an if in
// the header: the null arm skips the vptr store as well, which no source-level
// test could do.
//
// The calls are direct REL32 to the stubs, so the declarations are plain
// __stdcall externs pinned in targets/game/reverse/symbols.csv; declaring them dllimport
// would emit the indirect six-byte `ff 15` form instead.

typedef int INT;
typedef unsigned int UINT;
typedef int Status;

namespace Gdiplus
{

class GpImage {};
class GpGraphics {};

}

extern "C"
{
	Status __stdcall GdipGetImageGraphicsContext(Gdiplus::GpImage *image, Gdiplus::GpGraphics **graphics);
	Status __stdcall GdipDrawImageI(Gdiplus::GpGraphics *graphics, Gdiplus::GpImage *image, INT x, INT y);
	Status __stdcall GdipCloneImage(Gdiplus::GpImage *image, Gdiplus::GpImage **cloneImage);
	void *__stdcall GdipAlloc(unsigned int size);
}

namespace Gdiplus
{

class GdiplusBase
{
public:
	void *operator new(unsigned int size)
	{
		return GdipAlloc(size);
	}
};

class Image : public GdiplusBase
{
	friend class Graphics;

public:
	virtual ~Image();

	Image *Clone(void);

protected:
	Image(GpImage *image, Status status)
	{
		SetNativeImage(image);
		lastResult = status;
	}

	void SetNativeImage(GpImage *nativeImage)
	{
		this->nativeImage = nativeImage;
	}

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

class Graphics : public GdiplusBase
{
public:
	Graphics(Image *image);

	Status DrawImage(Image *image, INT x, INT y);

protected:
	void SetNativeGraphics(GpGraphics *graphics)
	{
		this->nativeGraphics = graphics;
	}

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

	GpGraphics *nativeGraphics;							///< retail this+0x00
	mutable Status lastResult;							///< retail this+0x04
};

// ??0Graphics@Gdiplus@@QAE@PAVImage@1@@Z
Graphics::Graphics(Image *image)
{
	GpGraphics *graphics = 0;

	if (image != 0)
	{
		lastResult = GdipGetImageGraphicsContext(image->nativeImage, &graphics);
	}

	SetNativeGraphics(graphics);
}

// ?DrawImage@Graphics@Gdiplus@@QAEHPAVImage@2@HH@Z
Status Graphics::DrawImage(Image *image, INT x, INT y)
{
	return SetStatus(GdipDrawImageI(nativeGraphics,
		image != 0 ? image->nativeImage : 0, x, y));
}

// ?Clone@Image@Gdiplus@@QAEPAV12@XZ
Image *Image::Clone(void)
{
	GpImage *cloneImage = 0;

	SetStatus(GdipCloneImage(nativeImage, &cloneImage));

	return new Image(cloneImage, lastResult);
}

}
