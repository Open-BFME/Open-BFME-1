// cl: /DNDEBUG /MD /EHsc
// Retail RVA006D2000, 242B. HeightMapRenderObjClass vtable slot133 (+0x214) via ILT393CE.
// Address-derived memory view: pristine ZH HeightMap.h has different BFME fields.
class WorldHeightMap;
struct Rva0072E150Region { int loX, loY, hiX, hiY; };
class W3DTerrainBackground {
public:
    void rva0072D210(const Rva0072E150Region &, WorldHeightMap *, bool, bool);
    char rva00000000[0xC4];
};
class Rva00490350Base;
extern Rva00490350Base *Rva00490350Head;
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
class Rva006D2000ProgressView {
public:
    virtual void rva00000000();
    virtual void rva00000004(int);
};
class Rva006D2000SubsystemView {
public:
    virtual void rva00000000(); virtual void rva00000004();
    virtual void rva00000008(); virtual void rva0000000C();
    virtual void rva00000010(); virtual void rva00000014();
    virtual void rva00000018(); virtual void rva0000001C();
    virtual void rva00000020(); virtual void rva00000024();
};
struct Rva006D2000MapView { char rva00000000[8]; int rva00000008, rva0000000C; };
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);
class Rva006D2000Owner {
public:
    void method();
private:
    char rva00000000[0x2ff4];
    WorldHeightMap *rva00002FF4;
    char rva00002FF8[0x3014-0x2ff8];
    bool rva00003014;
    char rva00003015[0x30d8-0x3015];
    W3DTerrainBackground *rva000030D8;
    int rva000030DC, rva000030E0, rva000030E4;
};
void Rva006D2000Owner::method() {
    Rva0072E150Region region;
    region.loX=0;
    region.loY=0;
    region.hiX=((Rva006D2000MapView *)rva00002FF4)->rva00000008;
    region.hiY=((Rva006D2000MapView *)rva00002FF4)->rva0000000C;
    int x=0;
    int width=rva000030E0;
    for(; x<width; ++x,width=rva000030E0) {
        if(Rva00490350Head)
            ((Rva006D2000ProgressView *)Rva00490350Head)->rva00000004(50-(int)((float)x * -45.0f / width));
        for(int y=0;y<rva000030E4;++y) {
            rva000030D8[y*rva000030E0+x].rva0072D210(region,rva00002FF4,false,rva00003014);
            Sleep(0);
            if(Rva0134FAA0)
                ((Rva006D2000SubsystemView *)Rva0134FAA0)->rva00000024();
        }
    }
}
