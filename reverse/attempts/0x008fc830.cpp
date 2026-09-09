// ?clear@W3DRadarResetSurface@@QAEXI@Z
// partial score=0.82 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME W3DRadarResetSurface::clear body at retail RVA 0x008FC830.
// The one-pointer surface ABI, SurfaceClass descriptor query, ECX-based
// SurfaceDescription pixel-size helper, and BFME DX8 error stream are all
// established by the matched neighboring SurfaceClass bodies.

#include <string.h>

typedef unsigned long BfmeResult;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned int WW3DFormat;
typedef int Int;

struct BfmeLockedRect
{
	long pitch;
	void *bits;
};

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04();
	virtual void Slot08();
	virtual void Slot0C();
	virtual void Slot10();
	virtual void Slot14();
	virtual void Slot18();
	virtual void Slot1C();
	virtual void Slot20();
	virtual void Slot24();
	virtual void Slot28();
	virtual void Slot2C();
	virtual void Slot30();
	virtual void Slot34();
	virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
	virtual void Slot3C();
	virtual void Slot40();
	virtual void Slot44();
	virtual void Slot48();
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00();
	virtual void Slot04();
	virtual void Slot08();
	virtual void Slot0C();
	virtual void Slot10();
	virtual void Slot14();
	virtual void Slot18();
	virtual void Slot1C();
	virtual void Slot20();
	virtual void Slot24();
	virtual void Slot28();
	virtual void Slot2C();
	virtual void Slot30();
	virtual void Slot34();
	virtual void Slot38();
	virtual void Slot3C();
	virtual void Slot40();
	virtual void Slot44();
	virtual void Slot48();
	virtual void Slot4C();
	virtual void Slot50();
	virtual void Slot54();
	virtual void Slot58();
	virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64();
	virtual void Slot68();
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context);
};

class BfmeSurfaceResource
{
public:
	virtual void Slot00();
	virtual void Slot04();
	virtual void Slot08();
	virtual void Slot0C();
	virtual void Slot10();
	virtual void Slot14();
	virtual void Slot18();
	virtual void Slot1C();
	virtual void Slot20();
	virtual void Slot24();
	virtual void Slot28();
	virtual void Slot2C();
	virtual void Slot30();
	virtual BfmeResult __stdcall LockRect(BfmeLockedRect *locked,
		const void *rectangle, unsigned flags);
	virtual BfmeResult __stdcall UnlockRect();
};

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);

static __forceinline void BFME_Surface_ErrorCode(unsigned result)
{
	if (result != 0) {
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->Begin_Report();
		BFMEIndexBufferDebugStream *stream =
			g_BFMEIndexBufferDebug->Get_Stream(0, 0);
		stream->Put_String("DX8 error ")->Put_Unsigned(result)->Finish(1);
	}
}

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		WW3DFormat Format;
		unsigned Width;
		unsigned Height;
		unsigned Rva008FC4F0_PixelSize() const;
	};

	void Get_Description(SurfaceDescription &description);
};

class W3DRadarResetSurface
{
public:
	void clear(UnsignedInt color);

private:
	void *m_surface;
};

void W3DRadarResetSurface::clear(UnsignedInt color)
{
	if (m_surface)
	{
		SurfaceClass::SurfaceDescription description;
		reinterpret_cast<SurfaceClass *>(this)->Get_Description(description);
		UnsignedInt size = description.Rva008FC4F0_PixelSize() * description.Width;

		BfmeLockedRect locked;
		::memset(&locked, 0, sizeof(locked));
		BFME_Surface_ErrorCode(reinterpret_cast<BfmeSurfaceResource *>(m_surface)->LockRect(&locked, NULL, 0));

		UnsignedInt fill = static_cast<UnsignedByte>(color) ? 0xff : 0;
		unsigned char *memory = static_cast<unsigned char *>(locked.bits);
		if (size == 0 && (description.Format == static_cast<WW3DFormat>(0x31545844) ||
			description.Format == static_cast<WW3DFormat>(0x32545844) ||
			description.Format == static_cast<WW3DFormat>(0x33545844) ||
			description.Format == static_cast<WW3DFormat>(0x34545844) ||
			description.Format == static_cast<WW3DFormat>(0x35545844)))
		{
			size = locked.pitch;
			UnsignedInt i = description.Height >> 2;
			if (static_cast<UnsignedByte>(color))
			{
				unsigned char pattern[8];
				Int copy_count = size >> 3;
				fill |= 0xff;
				pattern[0] = static_cast<unsigned char>(fill);
				pattern[1] = 0xfe;
				pattern[2] = static_cast<unsigned char>(fill);
				pattern[3] = static_cast<unsigned char>(fill);
				pattern[4] = 0x55;
				pattern[5] = 0x55;
				pattern[6] = 0x55;
				pattern[7] = 0x55;
				for (i = description.Height >> 2; i > 0; --i)
				{
					if (copy_count > 0)
					{
						*reinterpret_cast<UnsignedInt *>(memory) =
							*reinterpret_cast<UnsignedInt *>(pattern);
						*reinterpret_cast<UnsignedInt *>(memory + 4) =
							*reinterpret_cast<UnsignedInt *>(pattern + 4);
						::memcpy(memory + 8, memory, (copy_count * 8 - 5) & ~3U);
					}
					memory += locked.pitch;
				}
				goto unlock;
			}
		}
		UnsignedInt i;
		for (i = description.Height; i > 0; --i)
		{
			::memset(memory, fill, size);
			memory += locked.pitch;
		}

	unlock:
		BFME_Surface_ErrorCode(reinterpret_cast<BfmeSurfaceResource *>(m_surface)->UnlockRect());
	}
}
