// ?method@Rva0090D280@@QAEXXZ
// partial score=0.8628 date=2026-10-03
// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Opaque identity: table VA 0x0113A668 slot 3 at VA 0x0113A674; ret at RVA 0x0090D7AA; switch tables end at 0x0090D7F0.
class BFMEDebugStream008FC660
{
public:
	virtual BFMEDebugStream008FC660 *Put_Unsigned(unsigned value);
	virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34();
	virtual BFMEDebugStream008FC660 *Put_String(const char *text);
	virtual void Slot3C(); virtual void Slot40(); virtual void Slot44(); virtual void Slot48();
	virtual BFMEDebugStream008FC660 *Finish(int report);
};

class BFMEDebugClass008FC660
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
	virtual BFMEDebugStream008FC660 *Get_Stream(void *owner, void *context);
};

extern void *g_Rva00F36E5C;
#define g_BFMEIndexBufferDebug reinterpret_cast<BFMEDebugClass008FC660 *>(g_Rva00F36E5C)
extern void _bfme_debugRecordCallsite(int kind);

static __forceinline void BFME_Surface_ErrorCode008FC660(unsigned result)
{
	if (result != 0) {
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->Begin_Report();
		BFMEDebugStream008FC660 *stream =
			g_BFMEIndexBufferDebug->Get_Stream(0, 0);
		stream->Put_String("DX8 error ")->Put_Unsigned(result)->Finish(1);
	}
}


#include "surfaceclass.h"
#include "vector3.h"
#include <string.h>
void RGB_To_HSV(Vector3 &, const Vector3 &);
void HSV_To_RGB(Vector3 &, const Vector3 &);
struct BfmeItemDC {
public:
 virtual void s0(); virtual unsigned __stdcall AddRef(); virtual unsigned __stdcall Release();
};
class BfmeThingDC {
public: BfmeThingDC(BfmeItemDC *); BfmeItemDC *p;
};
class W3DRadarResetSurface {
public: ~W3DRadarResetSurface();
};
struct Rva0090D280Surface : BfmeThingDC {
 Rva0090D280Surface(BfmeItemDC *p) : BfmeThingDC(p) {}
 ~Rva0090D280Surface() {
  reinterpret_cast<W3DRadarResetSurface *>(this)->~W3DRadarResetSurface();
 }
};
// SurfaceClass::Lock(int*,bool) is proven at 008FC660, but the canonical
// header lacks that BFME overload. This scratch ABI view is UNPINNED;
// repair its native declaration before any production promotion.
class Rva008FC660 { public: void *method(int *, bool); };
class Rva0090D280Resource {
public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
 virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
 virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
 virtual void s40(); virtual void s44();
 virtual unsigned __stdcall get(unsigned,BfmeItemDC **);
};
class Rva0090C2F0Inner { public: void rva0090CD00LoadFromMemory(const char *); char f00[8]; Rva0090D280Resource *f08; };
extern unsigned short g_Rva00D3A54C[16];
class Rva0090D280 {
public:
 virtual const char *slot00();
 char f04[0x10]; Rva0090C2F0Inner *f14; char f18[0x24]; char *f3c; unsigned f40;
 void method();
};
void Rva0090D280::method()
{
 f14->rva0090CD00LoadFromMemory(slot00());
 if (!f14->f08) return;
 BfmeItemDC *resource=0;
 BFME_Surface_ErrorCode008FC660(f14->f08->get(0,&resource));
 Rva0090D280Surface surface(resource);
 if (resource) resource->Release();
 int pitch;
 void *pixels=((Rva008FC660 *)&surface)->method(&pitch,false);
 SurfaceClass::SurfaceDescription desc;
 ((SurfaceClass *)&surface)->Get_Description(desc);
 float blue=(f40&255)*(1.0f/255.0f);
 float green=((f40>>8)&255)*(1.0f/255.0f);
 Vector3 color((float)((f40>>16)&255)*(1.0f/255.0f),green,blue);
 bool palette=f3c[3]=='D'||f3c[3]=='d';
 int entries[16];
 Vector3 shift;
 if(palette) goto fillPalette;
 RGB_To_HSV(shift,color);
convertPixels:
 switch((int)desc.Format) {
 case 21:case 22:
  if(palette) { unsigned *out=(unsigned *)pixels;
   out[0]=entries[0];
   out[1]=entries[1];
   out[2]=entries[2];
   out[3]=entries[3];
   out[4]=entries[4];
   out[5]=entries[5];
   out[6]=entries[6];
   out[7]=entries[7];
   out[8]=entries[8];
   out[9]=entries[9];
   out[10]=entries[10];
   out[11]=entries[11];
   out[12]=entries[12];
   out[13]=entries[13];
   out[14]=entries[14];
   out[15]=entries[15];
  }
  else {
   unsigned *p=(unsigned *)pixels;
   unsigned rowbytes=desc.Width*4;
   for(unsigned y=0;y<desc.Height;++y) {
    for(unsigned x=0;x<desc.Width;++x,++p) {
     if((*p&0xffffff)!=0xffffff) {
      double alpha=((unsigned char *)p)[3]*(1.0/255.0);
      *p=((((((int)(alpha*255.0)<<8)|(int)(color.X*255.0))<<8)|(int)(green*255.0))<<8)|(int)(blue*255.0);
     }
    }
    p+=((unsigned)pitch-rowbytes)/4;
   }
  }
  break;
 case 23:case 24:case 25:case 26:case 29:case 30:case 40:case 51:
  if(palette) { for(int i=0;i<16;++i) ((unsigned short *)pixels)[i]=(unsigned short)entries[i]; }
  else {
   unsigned short *p=(unsigned short *)pixels;
   for(unsigned y=0;y<desc.Height;++y) {
    for(unsigned x=0;x<desc.Width;++x,++p) {
     if(*p<0xffff) {
      Vector3 rgb(((*p>>8)&15)*(1.0f/15.0f),((*p>>4)&15)*(1.0f/15.0f),(*p&15)*(1.0f/15.0f));
      RGB_To_HSV(color,rgb);
      color.X=shift.X;
      color.Y*=shift.Y;
      Vector3 result;
      HSV_To_RGB(result,color);
      float alpha=*p>>12;
      *p=(((((unsigned short)(int)(result.X*15.0f)<<4)|(int)(result.Y*15.0f))<<4)|(int)(result.Z*15.0f))|(int)alpha;
     }
    }
    p+=((unsigned)pitch-desc.Width)/2;
   }
  }
  break;
 }
 goto done;
fillPalette:
 {
  int *out=entries;
  for(unsigned short *p=g_Rva00D3A54C;(int)p<(int)(g_Rva00D3A54C+16);++p,++out) {
   float scale=*p;
   int r=(int)(color.X*scale),g=(int)(green*scale),b=(int)(blue*scale);
   switch((int)desc.Format) {
    case 21:case 22:r|=0xffffff00; r<<=8; r|=g; r<<=8; break;
    case 26:r&=~15; r<<=4; r|=g; r&=~15; b|=0xf0000; b>>=4; break;
    case 25:r&=~7; r<<=5; r|=g; r&=~7; r<<=2; b|=0x40000; b>>=3; break;
    case 23:r&=~7; r<<=5; r|=g; r&=~3; r<<=3; b>>=3; break;
    default:continue;
   }
   *out=r|b;
  }
 }
 goto convertPixels;
done:
 ((SurfaceClass *)&surface)->Unlock();
}
