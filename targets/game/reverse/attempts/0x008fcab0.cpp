// ?d_008fcab0@@YAXXZ
// partial score=0.962085 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>
#include <windows.h>

typedef unsigned long BfmeResult;

struct BfmeLockedRect008FCF40
{
	long Pitch;
	void *pBits;
};

class BFMEDebugStream008FCF40
{
public:
	virtual BFMEDebugStream008FCF40 *Put_Unsigned(unsigned value);
	virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34();
	virtual BFMEDebugStream008FCF40 *Put_String(const char *text);
	virtual void Slot3C(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
	virtual BFMEDebugStream008FCF40 *Finish(int report);
};

class BFMEDebugClass008FCF40
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
	virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
	virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual BFMEDebugStream008FCF40 *Get_Stream(void *owner, void *context);
};

class BfmeSurfaceResource008FCF40
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30();
	virtual BfmeResult __stdcall LockRect(BfmeLockedRect008FCF40 *, RECT *, unsigned);
	virtual BfmeResult __stdcall UnlockRect();
};

extern BFMEDebugClass008FCF40 *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);

static __forceinline void BFME_Surface_ErrorCode008FCF40(unsigned result)
{
	if (result != 0) {
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->Begin_Report();
		BFMEDebugStream008FCF40 *stream =
			g_BFMEIndexBufferDebug->Get_Stream(0, 0);
		stream->Put_String("DX8 error ")->Put_Unsigned(result)->Finish(1);
	}
}

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		unsigned Format;
		unsigned Width;
		unsigned Height;
	};

	void Get_Description(SurfaceDescription &surface_desc);
	void ScaleChannels008FCAB0(float red, float green, float blue);

private:
	BfmeSurfaceResource008FCF40 *D3DSurface;
};


extern void d_008fc4f0(void);
// Retail +0 holds the COM surface; Get_Description and both adjacent methods
// witness this layout, unlike the surviving ZH ref-counted wrapper.
void SurfaceClass::ScaleChannels008FCAB0(float red, float green, float blue)
{
    if (!D3DSurface) return;
    SurfaceDescription sd;
    Get_Description(sd);
    typedef unsigned (SurfaceDescription::*PixelSizeOperation)();
    union { void *pointer; PixelSizeOperation member; } cast;
    cast.pointer = reinterpret_cast<void *>(d_008fc4f0);
    unsigned size = (sd.*cast.member)();
    BfmeLockedRect008FCF40 lock;
    memset(&lock, 0, sizeof(lock));
    BFME_Surface_ErrorCode008FCF40(D3DSurface->LockRect(&lock, 0, 0));
    unsigned char *row = (unsigned char *)lock.pBits;
    if (sd.Format == 0x31545844 || sd.Format == 0x32545844 ||
        sd.Format == 0x33545844 || sd.Format == 0x34545844 || sd.Format == 0x35545844) {
        int width = (unsigned)lock.Pitch >> 3;
        unsigned height = sd.Height >> 2;
        for (unsigned y=height; y>0; --y) {
            for (int x=0; x<width; ++x) {
                if (sd.Format == 0x31545844 || (x & 1)) {
                    unsigned short *pixel = (unsigned short *)(row + x*8);
                    short c = pixel[0];
                    pixel[0] = (((unsigned short)(((unsigned short)c >> 11)*red)*64 + (unsigned short)((((int)c >> 5)&63)*green))*32 + (unsigned short)((c&31)*blue));
                    c = pixel[1];
                    pixel[1] = (((unsigned short)(((unsigned short)c >> 11)*red)*64 + (unsigned short)((((int)c >> 5)&63)*green))*32 + (unsigned short)((c&31)*blue));
                }
            }
            row += lock.Pitch;
        }
    } else if (size == 4 && (sd.Format == 21 || sd.Format == 22)) {
        for (unsigned y=sd.Height; y>0; --y) {
            for (unsigned x=0; x<sd.Width; ++x) {
                unsigned c = ((unsigned *)row)[x];
                int r = (c >> 16)&255, g=(c >> 8)&255, b=c&255;
                if(r<127) r=127;
                if(g<127) g=127;
                if(b<127) b=127;
                ((unsigned *)row)[x] = (((int)(r*red)*256 + (int)(g*green))*256 + (int)(b*blue)) + (c&0xff000000);
            }
            row += lock.Pitch;
        }
    }
    BFME_Surface_ErrorCode008FCF40(D3DSurface->UnlockRect());
}
