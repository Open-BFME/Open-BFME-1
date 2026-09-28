// ?d_006e2540@@YAXXZ
// partial score=0.9849 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
template<> inline StringBase<char>::~StringBase() { releaseBuffer(); }
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

struct Triple006E2540 {
    float x,y,z;
    void set(float a,float b,float c) { x=a; y=b; z=c; }
};
struct Copy006E2540 { float x,y,z; };
struct Box006E2540 { Triple006E2540 lo,hi; };
class Gen00049FDA { public: bool handle(); };
extern Gen00049FDA *R2Ptr012F0FE0;
class BfmeSubXW { public: float bfmeScaleXW(); char data[12]; };
class WWMath { public: static float Random_Float(); };
class Sink006E2540 {
public:
    void read(Triple006E2540 *);
    void write(const Triple006E2540 *);
    void adjust(Triple006E2540 *,bool);
};
extern Sink006E2540 *g_012F8058;
struct State006E2540 { int pad; unsigned color; };
extern State006E2540 *g_01306EEC;
class Terrain006E2540 {
public:
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void bounds(Box006E2540 *);
};
extern Terrain006E2540 *g_012EF4CC;
class Client006E2540 {
public:
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20(); virtual void p24(); virtual void p28(); virtual void p2c();
    virtual void p30(); virtual void p34(); virtual void p38(); virtual void p3c();
    virtual void p40(); virtual void p44(); virtual void p48(); virtual void p4c();
    virtual void p50(); virtual void p54(); virtual void p58(); virtual void p5c();
    virtual void p60(); virtual void p64(); virtual unsigned frame();
};
extern Client006E2540 *g_012F1464;
class Display006E2540 {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual void pad23();
    virtual void pad24();
    virtual void pad25();
    virtual void pad26();
    virtual void pad27();
    virtual void pad28();
    virtual void pad29();
    virtual void pad30();
    virtual void pad31();
    virtual void pad32();
    virtual void pad33();
    virtual void pad34();
    virtual void pad35();
    virtual void pad36();
    virtual void pad37();
    virtual void pad38();
    virtual void pad39();
    virtual void pad40();
    virtual void pad41();
    virtual void pad42();
    virtual void pad43();
    virtual void pad44();
    virtual void pad45();
    virtual void pad46();
    virtual void pad47();
    virtual void pad48();
    virtual void pad49();
    virtual void pad50();
    virtual void pad51();
    virtual void pad52();
    virtual void pad53();
    virtual void pad54();
    virtual void pad55();
    virtual void pad56();
    virtual void pad57();
    virtual void pad58();
    virtual void pad59();
    virtual void pad60();
    virtual void pad61();
    virtual void pad62();
    virtual void pad63();
    virtual void pad64();
    virtual void pad65();
    virtual void pad66();
    virtual void pad67();
    virtual void pad68();
    virtual void pad69();
    virtual void pad70();
    virtual void pad71();
    virtual void pad72();
    virtual void pad73();
    virtual void pad74();
    virtual void pad75();
    virtual void pad76();
    virtual void pad77();
    virtual void pad78();
    virtual void pad79();
    virtual void pad80();
    virtual void pad81();
    virtual void pad82();
    virtual void pad83();
    virtual void pad84();
    virtual void pad85();
    virtual void pad86();
    virtual void pad87();
    virtual void pad88();
    virtual void pad89();
    virtual void pad90();
    virtual void pad91();
    virtual void pad92();
    virtual void pad93();
    virtual void pad94();
    virtual void pad95();
    virtual void pad96();
    virtual void pad97();
    virtual void pad98();
    virtual void pad99();
    virtual void pad100();
    virtual void pad101();
    virtual void pad102();
    virtual void pad103();
    virtual void pad104();
    virtual void pad105();
    virtual void pad106();
    virtual void pad107();
    virtual void pad108();
    virtual void pad109();
    virtual void pad110();
    virtual void pad111();
    virtual void pad112();
    virtual void pad113();
    virtual void pad114();
    virtual void pad115();
    virtual void pad116();
    virtual void pad117();
    virtual void pad118();
    virtual void pad119();
    virtual void pad120();
    virtual void pad121();
    virtual void pad122();
    virtual void pad123();
    virtual void pad124();
    virtual void pad125();
    virtual void pad126();
    virtual void pad127();
    virtual void pad128();
    virtual void pad129();
    virtual void pad130();
    virtual void pad131();
    virtual void pad132();
    virtual void pad133();
    virtual void pad134();
    virtual void pad135();
    virtual void pad136();
    virtual void pad137();
    virtual void refresh(int);
};
extern Display006E2540 *g_012F7FE0;
class FXList;
class Matrix3D;
struct Coord3D {float x,y,z;};
class FXList { public: static void doFXPos(const FXList *,const Coord3D *,const Matrix3D *,float,const Coord3D *); };
class FXListStore { public: const FXList *findFXList(const char *) const; };
extern FXListStore *TheFXListStore;

class Rva006E2540 {
public:
    void update();
    float probability() const { return f50; }
    Triple006E2540 triple() const { return f2c; }
    Triple006E2540 *pick(Triple006E2540 *);
    unsigned color();
    AsciiString stringAt9C();
    char pad00[0x2c];
    Triple006E2540 f2c;
    char pad38[0x14];
    bool f4c;
    char pad4d[3];
    float f50;
    char pad54[0x10];
    BfmeSubXW f64;
    float f70;
    BfmeSubXW f74;
    bool f80, f81;
    char pad82[0x2e];
    int fb0, fb4;
    bool fb8;
    char padb9[3];
    int fbc;
    float fc0;
    Triple006E2540 fc4,fd0,fdc;
    unsigned fe8;
    const FXList *fec;
    unsigned ff0;
    int ff4;
};
// Retail keeps both colour copies at one stack slot; the fade factor stays on the x87 stack.
void Rva006E2540::update() {
    if(fb0==0) return;
    Triple006E2540 value;
    if(fb0==2) {
        value=f2c;
        unsigned char on = R2Ptr012F0FE0 ? R2Ptr012F0FE0->handle() : 0;
        if(on) {
            if(fb8) {
                fc4.set(value.x,value.y,value.z);
                if(--fbc<=0) {
                    fb8=false; fbc=0; fc0=0; ff4=0; fc4.set(0,0,0);
                    if(f4c) {g_012F8058->write(&fd0); if(g_01306EEC) g_01306EEC->color=fe8;}
                    g_012F8058->adjust(&fdc,true);
                    fd0.set(0,0,0); fdc.set(0,0,0);
                    return;
                }
                if(f81) {
                    fc0=f74.bfmeScaleXW();
                    if(fc0>0.9) fc0=0.9f;
                    g_012F8058->adjust(&fdc,true);
                    fdc.set(fc0,fc0,fc0);
                    g_012F8058->adjust(&fdc,false);
                }
                if(f80) {
                    float chance=f70;
                    if(WWMath::Random_Float()<chance && f4c) {
                        pick(&value);
                        g_012F8058->write(&value);
                    }
                }
                return;
            }
            float random=WWMath::Random_Float();
            if(random < probability() && ++ff4>3) {
                Triple006E2540 other;
                fb8=true;
                fbc=(int)f64.bfmeScaleXW();
                fc0=f74.bfmeScaleXW();
                if(fc0>0.9) fc0=0.9f;
                fdc.set(fc0,fc0,fc0);
                if(f4c) {
                    g_012F8058->read(&fd0);
                    pick(&other);
                    g_012F8058->write(&other);
                    if(g_01306EEC) {
                        unsigned saved=g_01306EEC->color;
                        fe8=saved;
                        g_01306EEC->color=color();
                    }
                }
                g_012F8058->adjust(&fdc,false);
                if(!fec) {
                    AsciiString name=stringAt9C();
                    if(name.isNotEmpty()) fec=TheFXListStore->findFXList(name.str());
                }
                if(fec) {
                    Box006E2540 box;
                    g_012EF4CC->bounds(&box);
                    Coord3D pos;
                    pos.x=(box.lo.x+box.hi.x)*0.5f;
                    pos.y=(box.lo.y+box.hi.y)*0.5f;
                    pos.z=0;
                    FXList::doFXPos(fec,&pos,0,0,0);
                }
            }
        }
        fc4.set(value.x,value.y,value.z);
    }
    else {
        double factor=1.0-(float)fb4*0.00392156862745098;
        value=f2c;
        fc4.x=value.x*factor;
        fc4.y=value.y*factor;
        fc4.z=value.z*factor;
        if(g_012F1464->frame()%10==0) g_012F7FE0->refresh(0);
    }
}
