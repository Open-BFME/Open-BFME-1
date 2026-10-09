// ?method@Rva006C3500W3DRadar@@UAEXXZ
// partial score=0.9898 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

#include <string.h>
#include "ascii_string.h"
#include "surfaceclass.h"

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

extern const char g_bfmeEmptyAscii[];

static __forceinline char *bfmeString(const AsciiString &value)
{
	char *data = *(char **)&value;
	return data ? data + 8 : (char *)g_bfmeEmptyAscii;
}

class SurfaceResource
{
public:
	virtual void slot00();
	virtual unsigned long __stdcall addRef();
	virtual unsigned long __stdcall release();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual int __stdcall LockRect(void *lockedRect, const void *rect, UnsignedInt flags);
	virtual int __stdcall UnlockRect();
};

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface() : m_surface(0) {}
	W3DRadarResetSurface(const W3DRadarResetSurface &other) : m_surface(other.m_surface)
	{
		if (m_surface)
			m_surface->addRef();
	}
	~W3DRadarResetSurface();
	void clear(UnsignedInt color);

	SurfaceResource *m_surface;
};

typedef SurfaceClass::SurfaceDescription SurfaceDescription;

class W3DRadarTextureObject
{
public:
	virtual void slot00();
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel();

	W3DRadarTextureObject *m_texture;
};

class TextureClass;

class BFMEWaterTrackTexture
{
public:
	void Release_Ref();
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *name, int mipCount, int format);

class Gen_0090E810
{
public:
	void bfmeSetFlag(unsigned char value);
};

class Image
{
public:
	AsciiString getFilename(void) const
	{
		return m_filename;
	}

	W3DRadarResetTexture *getRawTextureData() const
	{
		return reinterpret_cast<W3DRadarResetTexture *>(m_rawTextureData);
	}

	char m_bfmePrefix[8];
	AsciiString m_filename;
	char m_padding0c[0x20];
	TextureClass *m_rawTextureData;
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;
extern void W3DRadarResetLock(void);
extern char bfmeUnlock1179(void);
extern void _bfme_debugRecordCallsite(int kind);

class Rva006C3500Lock
{
public:
	Rva006C3500Lock() { W3DRadarResetLock(); }
	~Rva006C3500Lock() { bfmeUnlock1179(); }
};

class BfmeAwakenDebugStream
{
public:
	virtual BfmeAwakenDebugStream *slot00(int value);
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenDebugStream *slot38(const void *value);
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual BfmeAwakenDebugStream *slot4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenDebugStream *slot6c(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;

static __forceinline void recordSurfaceError(int result)
{
	if (result != 0)
	{
		_bfme_debugRecordCallsite(1);
		TheBfmeAwakenDebug->slot60();
		TheBfmeAwakenDebug->slot6c(0, 0)->slot38("DX8 error ")
			->slot00(result)->slot4c(1);
	}
}

struct LockedRect
{
	int pitch;
	void *bits;
};

class Rva006C3500W3DRadar
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void method();

private:
	char m_pad04[0x1490];
	W3DRadarResetTexture m_shroudTexture;
	char m_pad1498[0x46];
	Bool m_imageReady;
};

void Rva006C3500W3DRadar::method()
{
	Rva006C3500W3DRadar *radar = this;
	radar->m_imageReady = 0;
	radar->m_shroudTexture.getSurfaceLevel().clear(0);

	const Image *image;
	{
		AsciiString imageName("ScrollShroud");
		image = TheMappedImageCollection->findImageByName(imageName);
	}
	if (image)
	{

	BFMEWaterTrackTextureHandle texture =
		BFMEGetWaterTrackTexture(bfmeString(image->getFilename()), 1, 0);
	((Gen_0090E810 *)&texture)->bfmeSetFlag(1);

	W3DRadarResetTexture *sourceTexture = !image->getRawTextureData() ? reinterpret_cast<W3DRadarResetTexture *>(&texture) : image->getRawTextureData();
	if (sourceTexture)
	{

	W3DRadarResetSurface source = sourceTexture->getSurfaceLevel();
	W3DRadarResetSurface destination = radar->m_shroudTexture.getSurfaceLevel();
	SurfaceDescription destinationDescription;
	SurfaceDescription sourceDescription;
	((SurfaceClass *)&source)->Get_Description(sourceDescription);
	((SurfaceClass *)&destination)->Get_Description(destinationDescription);
	if (sourceDescription.Format == destinationDescription.Format)
	{

	Rva006C3500Lock lock;
	SurfaceResource *sourceSurface = source.m_surface;
	SurfaceResource *destinationSurface = destination.m_surface;
	if (sourceSurface && destinationSurface)
	{
		LockedRect sourceLocked;
		LockedRect destinationLocked;
		memset(&sourceLocked,0,sizeof(sourceLocked));
		memset(&destinationLocked,0,sizeof(destinationLocked));
		int lockResult = sourceSurface->LockRect(&sourceLocked, 0, 0x10);
		recordSurfaceError(lockResult);
		lockResult = destinationSurface->LockRect(&destinationLocked, 0, 0);
		recordSurfaceError(lockResult);

		if (sourceDescription.Width == destinationDescription.Width &&
			sourceDescription.Height == destinationDescription.Height)
		{
			UnsignedInt bytesPerPixel;
			if (sourceDescription.Format == 0x15)
				bytesPerPixel = 4;
			else if (sourceDescription.Format == 0x1a)
				bytesPerPixel = 2;

			if (sourceDescription.Format == 0x15 || sourceDescription.Format == 0x1a)
			{
				char *sourceBits = (char *)sourceLocked.bits;
				char *destinationBits = (char *)destinationLocked.bits;
				for (int row = destinationDescription.Height - 1; row >= 0; --row)
				{
					memcpy(destinationBits, sourceBits,
						bytesPerPixel * sourceDescription.Width);
					sourceBits += sourceLocked.pitch;
					destinationBits += destinationLocked.pitch;
				}
			}
		}
		else if (destinationDescription.Format == 0x15 ||
			destinationDescription.Format == 0x1a)
		{
			memset(destinationLocked.bits, 0,
				destinationLocked.pitch * destinationDescription.Height);
		}

		recordSurfaceError(destinationSurface->UnlockRect());
		recordSurfaceError(sourceSurface->UnlockRect());
		radar->m_imageReady = 1;
	}
}
}
}
}
