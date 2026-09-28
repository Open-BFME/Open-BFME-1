// cl: /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include <string.h>
#include <new>
#include "targa.h"
// Surface helper named by matched Rva007BB060 caller; native D3D9 slots.
struct Rva007BB060Surface;
struct SurfaceDesc007B93E0 { unsigned Format, Type, Usage, Pool, MultiSampleType, MultiSampleQuality, Width, Height; };
struct LockedRect007B93E0 { int Pitch; char *pBits; };
struct SurfaceVtable007B93E0 {
 void *s00[2];
 unsigned long (__stdcall *Release)(Rva007BB060Surface*);
 void *s0c[9];
 long (__stdcall *GetDesc)(Rva007BB060Surface*,SurfaceDesc007B93E0*);
 long (__stdcall *LockRect)(Rva007BB060Surface*,LockedRect007B93E0*,void*,unsigned);
};
struct Rva007BB060Surface { SurfaceVtable007B93E0 *vtable; };
struct Device007B93E0;
struct DeviceVtable007B93E0 {
 void *s00[32];
 long (__stdcall *GetRenderTargetData)(Device007B93E0*,Rva007BB060Surface*,Rva007BB060Surface*);
 void *s84[3];
 long (__stdcall *CreateOffscreenPlainSurface)(Device007B93E0*,unsigned,unsigned,unsigned,unsigned,Rva007BB060Surface**,void*);
};
struct Device007B93E0 { DeviceVtable007B93E0 *vtable; };
extern Device007B93E0 *Rva01340534Device;
class Rva009E0360 { public: void m009E0360(); };
class BfmeAwakenLog
{
public:
	virtual BfmeAwakenLog *slot00(int value);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual BfmeAwakenLog *slot38(const char *value);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual BfmeAwakenLog *slot4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual BfmeAwakenLog *slot6c(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(int kind);

void Rva007B93E0(Rva007BB060Surface *surface)
{
 Rva007BB060Surface *copy=0;
 SurfaceDesc007B93E0 desc;
 surface->vtable->GetDesc(surface,&desc);
 Device007B93E0 *device=Rva01340534Device;
 device->vtable->CreateOffscreenPlainSurface(device,desc.Width,desc.Height,desc.Format,2,&copy,0);
 device->vtable->GetRenderTargetData(device,surface,copy);
 LockedRect007B93E0 locked;
 int result=copy->vtable->LockRect(copy,&locked,0,16);
 if (result) {
  _bfme_debugRecordCallsite(1);
  TheBfmeAwakenDebug->slot60();
  TheBfmeAwakenDebug->slot6c(0,0)->slot38("DX8 error ")->slot00(result)->slot4c(1);
 }
 unsigned width=desc.Width, height=desc.Height;
 char *image=new char[width*height*4];
 for (unsigned y=0;y<height;y++) {
  for (unsigned x=0;x<width;x++) {
   unsigned src=y*locked.Pitch+x*4;
   unsigned dst=(y*width+x)*4;
   image[dst]=locked.pBits[src+3];
   image[dst+1]=locked.pBits[src+2];
   image[dst+2]=locked.pBits[src+1];
   image[dst+3]=locked.pBits[src];
  }
 }
 Targa targa;
 memset(&targa.Header,0,sizeof(targa.Header));
 targa.Header.Width=(short)width;
 targa.Header.Height=(short)height;
 targa.Header.PixelDepth=32;
 targa.Header.ImageType=2;
 targa.SetImage(image);
 ((Rva009E0360*)&targa)->m009E0360();
 targa.Save("SurfaceTest.tga",1,false);
 copy->vtable->Release(copy);
}

