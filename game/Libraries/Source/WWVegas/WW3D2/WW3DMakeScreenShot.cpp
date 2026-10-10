// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#define TGA_USES_WWLIB_FILE_CLASSES
#include "ww3d.h"
#include "dx8wrapper.h"
#include "ffactory.h"
#include "targa.h"
#include "wwdebug.h"
#include "debug.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#pragma pack(push, 2)
struct Rva008FD930BitmapFileHeader
{
    unsigned short bfType;
    unsigned long bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned long bfOffBits;
};
#pragma pack(pop)
struct Rva008FD930BitmapInfoHeader
{
    unsigned long biSize;
    long biWidth;
    long biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned long biCompression;
    unsigned long biSizeImage;
    long biXPelsPerMeter;
    long biYPelsPerMeter;
    unsigned long biClrUsed;
    unsigned long biClrImportant;
};
extern "C" __declspec(dllimport) int __stdcall GetWindowRect(HWND, RECT *);

// D3D9 writes eight dwords; the inherited sweep descriptor omits one.
struct Rva008FD930SurfaceDesc { unsigned words[8]; };
struct Rva008FD930SurfaceView
{
    virtual HRESULT __stdcall slot00();
    virtual ULONG __stdcall slot04();
    virtual ULONG __stdcall Release();
    virtual void __stdcall slot0C();
    virtual void __stdcall slot10();
    virtual void __stdcall slot14();
    virtual void __stdcall slot18();
    virtual void __stdcall slot1C();
    virtual void __stdcall slot20();
    virtual void __stdcall slot24();
    virtual void __stdcall slot28();
    virtual void __stdcall slot2C();
    virtual HRESULT __stdcall GetDesc(Rva008FD930SurfaceDesc *);
    virtual HRESULT __stdcall LockRect(D3DLOCKED_RECT *, const RECT *, DWORD);
};
extern void *g_WW3D_Hwnd;

class Rva008FD930DebugStream
{
public:
	virtual Rva008FD930DebugStream *Put_HResult(Debug::HResult value);
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
	virtual Rva008FD930DebugStream *Put_String(const char *text);
	virtual void Slot3C();
	virtual void Slot40();
	virtual void Slot44();
	virtual void Slot48();
	virtual bool Finish(int report);
};

struct Rva00889690Obj
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
	virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
	virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual bool Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual Rva008FD930DebugStream *Get_Stream(const char *owner, int context);
};

extern Rva00889690Obj *g_rva00889690;
extern void _bfme_debugRecordCallsite(int kind);

// ?BFME_DX8_ErrorCode@@YAXI@Z absent-from-retail
static __forceinline void BFME_DX8_ErrorCode(unsigned result)
{
	if (result != D3D_OK) {
		_bfme_debugRecordCallsite(1);
		g_rva00889690->Begin_Report();
		Rva008FD930DebugStream *stream = g_rva00889690->Get_Stream(NULL, NULL);
		stream->Put_String("DX8 error ")->Put_HResult(Debug::HResult(result))->Finish(1);
	}
}

// ?Make_Screen_Shot@WW3D@@SAXPBDMW4ScreenShotFormatEnum@1@@Z
// Identity and ABI: targets/game/reverse/identity_evidence/008fd930-screenshot-recovery.md.
void WW3D::Make_Screen_Shot( const char * filename_base , const float gamma, const ScreenShotFormatEnum format)
{

	WWASSERT(!IsRendering);

	char filename[80];

	char ext[4];
	switch (format) {
		case TGA:
			sprintf(ext,"tga");
			break;
		case BMP:
			sprintf(ext,"bmp");
			break;
		default:
			WWASSERT(0);
			return;
			break;
	}

	static int frame_number = 1;

	bool done = false;
	while (!done) {
		sprintf( filename, "%s%.2d.%s", filename_base, frame_number++, ext);
		FileClass*file=_TheFileFactory->Get_File( filename );
		if ( file ) {
			file->Open();
			done = !file->Is_Available();
			_TheFileFactory->Return_File( file );
		} else {
			done = true;
		}
	}

	WWDEBUG_SAY(( "Creating Screen Shot %s\n", filename ));

	// make the gamma look up table
	int i;
	unsigned char gamma_lut[256];
	float recip = 1.0f;
	if (gamma > WWMATH_EPSILON) {
		recip = 1.0f / gamma;
	}
	for (i = 0; i < 256; i++) {
		gamma_lut[i] = (unsigned char) (256.0f * powf(i / 256.0f, recip));
	}

	// Lock front buffer and copy

	Rva008FD930SurfaceView *fb;
	fb=(Rva008FD930SurfaceView *)DX8Wrapper::_Get_DX8_Front_Buffer();
	Rva008FD930SurfaceDesc desc;
	fb->GetDesc(&desc);

	RECT bounds;
	GetWindowRect((HWND)g_WW3D_Hwnd,&bounds);

	D3DLOCKED_RECT lrect;

	BFME_DX8_ErrorCode(fb->LockRect(&lrect,&bounds,D3DLOCK_READONLY));

	unsigned int x,y,index,index2,width,height;

	width=bounds.right-bounds.left;
	height=bounds.bottom-bounds.top;

	unsigned char *image=W3DNEWARRAY unsigned char[3*width*height];

	for (y=0; y<height; y++)
	{
		for (x=0; x<width; x++)
		{
			// index for image
			index=3*(x+y*width);
			// index for fb
			index2=y*lrect.Pitch+4*x;

			image[index]   = gamma_lut[*((unsigned char *) lrect.pBits + index2+2)];
			image[index+1] = gamma_lut[*((unsigned char *) lrect.pBits + index2+1)];
			image[index+2] = gamma_lut[*((unsigned char *) lrect.pBits + index2+0)];
		}
	}

	fb->Release();

	switch (format) {
		case TGA:
			{
				Targa targ;
				memset(&targ.Header,0,sizeof(targ.Header));
				targ.Header.Width=width;
				targ.Header.Height=height;
				targ.Header.PixelDepth=24;
				targ.Header.ImageType=TGA_TRUECOLOR;
				targ.SetImage((char *) image);
				targ.YFlip();

				FileClass*file=_TheWritingFileFactory->Get_File( filename );
				if ( file ) {
					file->Create();
					file->Close();
					_TheWritingFileFactory->Return_File( file );
				}

				targ.Save(filename,TGAF_IMAGE,false);
			}
		break;
		case BMP:
			{
				Rva008FD930BitmapFileHeader fileheader;
				Rva008FD930BitmapInfoHeader header;
				memset(&header, 0, sizeof(Rva008FD930BitmapInfoHeader));
				header.biSize = sizeof(Rva008FD930BitmapInfoHeader);
				header.biWidth = width;
				header.biHeight = height;
				header.biPlanes = 1;
				header.biBitCount = 24;
				header.biCompression = 0;
				header.biXPelsPerMeter = 0xB12;
				header.biYPelsPerMeter = 0xB12;
				int len = ((width * 24 +31) & ~31) /8;
    
				memset(&fileheader, 0, sizeof(Rva008FD930BitmapFileHeader));
				fileheader.bfType = 19778; // BM
				fileheader.bfOffBits = sizeof(Rva008FD930BitmapFileHeader) + sizeof(Rva008FD930BitmapInfoHeader);
				fileheader.bfSize = sizeof(Rva008FD930BitmapFileHeader) + sizeof(Rva008FD930BitmapInfoHeader) + 3 * len * height * sizeof(char);

				FileClass *file = _TheWritingFileFactory->Get_File( filename );
				if ( file ) {
					file->Create();
					file->Open(FileClass::WRITE);
					int num;
					num = file->Write(&fileheader, sizeof(Rva008FD930BitmapFileHeader));
					WWASSERT(num == sizeof(Rva008FD930BitmapFileHeader));
					num = file->Write(&header, sizeof(Rva008FD930BitmapInfoHeader));
					WWASSERT(num == sizeof(Rva008FD930BitmapInfoHeader));
					char *temp = new char [3 * len];
					memset(temp, 0, 3 * len * sizeof(char));
					// invert image, pad and swap R and B
					for (y = 0; y < (int) height; y++) {
						memcpy(&temp[0], &image[ 3 * width * (height - y - 1)], 3 * width * sizeof(char));
						for (x = 0; x < width; x++) {
							char t2 = temp[3 * x];
							temp[3 * x] = temp[3 * x + 2];
							temp[3 * x + 2] = t2;
						}
						num = file->Write(&temp[0], len * sizeof(char));
						WWASSERT(num == len * (int)sizeof(char));
					}
					delete [] temp;
					file->Close();
					_TheWritingFileFactory->Return_File( file );
				}
			}
			break;
	}

	delete [] image;
}
