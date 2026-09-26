// ?method@Rva0090D280@@QAEXXZ
// partial score=0.5610632183908046 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0090D280..0090D7AA, switch data 0090D7AC..0090D7EF.
// Owner is address-derived: ctor 0090E470 installs VA 0113A668; slot 3.
// BFME surface wrappers below have the retail one-pointer ABI, unlike ZH SurfaceClass.
#include "vector3.h"
void RGB_To_HSV(Vector3 &, const Vector3 &);
void HSV_To_RGB(Vector3 &, const Vector3 &);
struct BfmeItemDC {
    virtual void slot00(); virtual void slot04();
    virtual unsigned long __stdcall release();
};
class BfmeThingDC {
public: BfmeThingDC(BfmeItemDC *); BfmeItemDC *surface;
};
class W3DRadarResetSurface {
public: ~W3DRadarResetSurface(); BfmeItemDC *surface;
};
class SurfaceClass {
public:
    struct SurfaceDescription { int Format; unsigned Width, Height; };
    void *Lock(int *, bool); void Unlock(); void Get_Description(SurfaceDescription &);
};
struct Rva0090D280Surface : BfmeThingDC {
    Rva0090D280Surface(BfmeItemDC *p) : BfmeThingDC(p) {}
    ~Rva0090D280Surface() { reinterpret_cast<W3DRadarResetSurface *>(this)->~W3DRadarResetSurface(); }
};
class Rva0090D280Texture {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44();
    virtual int __stdcall surfaceLevel(unsigned, BfmeItemDC **);
};
class BfmeSub937B {
public: void bfmeCall937B(void *); char pad[8]; Rva0090D280Texture *texture;
};
class Rva0090D280Stream {
public:
    virtual Rva0090D280Stream *s00(int);
    virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10();
    virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20();
    virtual void s24(); virtual void s28(); virtual void s2c(); virtual void s30();
    virtual void s34(); virtual Rva0090D280Stream *s38(const char *);
    virtual void s3c(); virtual void s40(); virtual void s44(); virtual void s48();
    virtual Rva0090D280Stream *s4c(int);
};
class Rva0090D280Debug {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
    virtual void s60(); virtual void s64(); virtual void s68();
    virtual Rva0090D280Stream *s6c(int,int);
};
extern Rva0090D280Debug *g_BFMEIndexBufferDebug;
void _bfme_debugRecordCallsite(int);
extern unsigned short Rva00D3A54C[16];
class Rva0090D280 {
public:
    virtual void *slot00();
    char pad04[0x10]; BfmeSub937B *sub;
    char pad18[0x24]; const char *name; unsigned color;
    void method();
};
void Rva0090D280::method()
{
    sub->bfmeCall937B(slot00());
    if (!sub->texture) return;
    BfmeItemDC *p = 0;
    int hr = sub->texture->surfaceLevel(0, &p);
    if (hr) {
        _bfme_debugRecordCallsite(1);
        g_BFMEIndexBufferDebug->s60();
        g_BFMEIndexBufferDebug->s6c(0,0)->s38("DX8 error ")->s00(hr)->s4c(1);
    }
    Rva0090D280Surface surface(p);
    if (p) p->release();
    int pitch;
    void *bits = reinterpret_cast<SurfaceClass *>(&surface)->Lock(&pitch,false);
    SurfaceClass::SurfaceDescription desc;
    reinterpret_cast<SurfaceClass *>(&surface)->Get_Description(desc);
    float blue = float(color & 255u) * (1.0f/255.0f);
    float green = float((color >> 8) & 255) * (1.0f/255.0f);
    Vector3 rgb(float((color >> 16) & 255) * (1.0f/255.0f),green,blue), hsv;
    const float &red = rgb.X;
    bool palette = name[3]=='D' || name[3]=='d';
    unsigned values[16];
    if (palette) goto fillPalette;
    RGB_To_HSV(hsv,rgb);
convertPixels:
    switch(desc.Format) {
    case 21: case 22:
        if (palette) {
            for (int i=0;i<16;++i) static_cast<unsigned *>(bits)[i]=values[i];
        } else {
            unsigned rowBytes=desc.Width*4;
            unsigned *dest=static_cast<unsigned *>(bits);
            for (unsigned y=0;y<desc.Height;++y) {
                for(unsigned x=0;x<desc.Width;++x,++dest) {
                    if ((*dest & 0xffffff) != 0xffffff) {
                        double opacity=double(reinterpret_cast<unsigned char*>(dest)[3])*(1.0/255.0);
                        int packed=int(opacity*255.0);
                        packed<<=8; packed|=int(double(red)*255.0);
                        packed<<=8; packed|=int(double(green)*255.0);
                        packed<<=8; packed|=int(double(blue)*255.0);
                        *dest=packed;
                    }
                }
                dest += (pitch-rowBytes)/4;
            }
        }
        break;
    case 23: case 24: case 25: case 26: case 29: case 30: case 40: case 51:
        if (palette) {
            for(int i=0;i<16;++i) static_cast<unsigned short *>(bits)[i]=(unsigned short)values[i];
        } else {
            unsigned short *dest=static_cast<unsigned short *>(bits);
            for(unsigned y=0;y<desc.Height;++y) {
                for(unsigned x=0;x<desc.Width;++x,++dest) {
                    if (*dest < 0xffff) {
                        Vector3 c(float((*dest>>8)&15)*(1.0f/15.0f),float((*dest>>4)&15)*(1.0f/15.0f),float(*dest&15)*(1.0f/15.0f));
                        Vector3 output;
                        RGB_To_HSV(rgb,c);
                        rgb.X=hsv.X; rgb.Y*=hsv.Y;
                        HSV_To_RGB(output,rgb);
                        float alpha=float(*dest>>12);
                        unsigned packed = (unsigned short)(output.X*15.0f);
                        packed = (packed<<4)|int(output.Y*15.0f);
                        packed = (packed<<4)|int(output.Z*15.0f);
                        *dest = (unsigned short)(packed|int(alpha));
                    }
                }
                dest += (pitch-desc.Width)/2;
            }
        }
        break;
    }
    goto done;
fillPalette:
    { unsigned *dest=values;
        for (int i=0; i<16; ++i,++dest) {
            float intensity = float(Rva00D3A54C[i]);
            int r = int(red*intensity);
            int g = int(green*intensity);
            int b = int(blue*intensity);
            switch (desc.Format) {
            case 21: case 22: *dest = (((r|0xffffff00)<<8 | g)<<8)|b; break;
            case 26: *dest = (((((r & ~15)<<4)|g)&~15) | ((b|0xf0000)>>4)); break;
            case 25: *dest = (((((r & ~7)<<5)|g)&~7)<<2) | ((b|0x40000)>>3); break;
            case 23: *dest = (((((r & ~7)<<5)|g)&~3)<<3) | (b>>3); break;
            }
        }
    }
    goto convertPixels;
done:
    reinterpret_cast<SurfaceClass *>(&surface)->Unlock();
}
