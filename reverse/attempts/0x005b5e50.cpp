// ?translate@Rva005B5E50@@UAEHPBVRva005B5E50Message@@@Z
// partial score=0.9987868985038415 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseunicode /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath
// Candidate for 005B5E50. Address-qualified owner because the existing
// LookAtTranslator semantic pin refers to an incompatible event-buffer body.
// This body's 0110DE48 slot zero, ctor005B5470, bookmark literal and complete
// camera dispatch are recorded in IDENTITY.md. Retail governs every enum value.
#include <stddef.h>
#include <string.h>
#pragma intrinsic(memcpy)
#include "Common/UnicodeString.h"
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t>*)this)->releaseBuffer(); }

#include "icoord.h"
#include "coord2d.h"
#include "region.h"
inline Coord2D::Coord2D() { }
inline Coord2D::~Coord2D() { }
inline ICoord2D::ICoord2D() { }
inline ICoord2D::ICoord2D(const ICoord2DBase &p) { x=p.x; y=p.y; }
inline ICoord2D &ICoord2D::operator=(const ICoord2D &p) { x=p.x; y=p.y; return *this; }
inline ICoord2D &ICoord2D::operator=(const ICoord2DBase &p) { x=p.x; y=p.y; return *this; }
typedef ICoord2D Rva005B5E50Pixel;
inline Region2D::Region2D() {}
inline Region2D::~Region2D() {}
typedef Region2D Rva005B5E50Region;
struct Rva005B5E50Location { char data[32]; };
union Rva005B5E50Argument {
    int coordinate[2]; int value;
    int integer() const {return value;}
    const ICoord2DBase &pixel() const { return *(const ICoord2DBase*)coordinate; }
};
extern void j_00045ae3();
extern void j_0000ccde();
extern void j_0000e11f();
extern void j_0002523e();
extern void j_0002d281();
extern void j_00034d15();
class Rva005B5E50Message {
public:
    char pad000[16]; int at010;
    const Rva005B5E50Argument *argument(int n) const {
        typedef const Rva005B5E50Argument *(Rva005B5E50Message::*P)(int) const;
        union {void(*raw)();P method;} route={j_00045ae3};
        return (this->*route.method)(n);
    }
};

// Generated declarations below contain only witnessed virtual-slot signatures.
class Rva005B5E50View { public:
    virtual void slot000()=0;
    virtual void slot004()=0;
    virtual void slot008()=0;
    virtual void slot00c()=0;
    virtual void slot010()=0;
    virtual void slot014()=0;
    virtual void slot018()=0;
    virtual void slot01c()=0;
    virtual void slot020()=0;
    virtual void slot024()=0;
    virtual void slot028()=0;
    virtual void slot02c()=0;
    virtual void slot030()=0;
    virtual void slot034()=0;
    virtual void slot038()=0;
    virtual void slot03c()=0;
    virtual void slot040()=0;
    virtual void slot044()=0;
    virtual void slot048()=0;
    virtual void slot04c()=0;
    virtual void slot050()=0;
    virtual void slot054()=0;
    virtual void slot058()=0;
    virtual void slot05c()=0;
    virtual void slot060()=0;
    virtual void slot064()=0;
    virtual void slot068()=0;
    virtual void slot06c()=0;
    virtual void slot070(int)=0;
    virtual void slot074()=0;
    virtual void slot078()=0;
    virtual void slot07c()=0;
    virtual void slot080()=0;
    virtual void slot084()=0;
    virtual void slot088()=0;
    virtual void slot08c()=0;
    virtual void slot090()=0;
    virtual void slot094()=0;
    virtual void slot098()=0;
    virtual void slot09c()=0;
    virtual void slot0a0()=0;
    virtual void slot0a4()=0;
    virtual void slot0a8()=0;
    virtual void slot0ac()=0;
    virtual void slot0b0()=0;
    virtual void slot0b4()=0;
    virtual void slot0b8()=0;
    virtual void slot0bc()=0;
    virtual void slot0c0()=0;
    virtual void slot0c4(int,int,int,int)=0;
    virtual void slot0c8()=0;
    virtual void slot0cc()=0;
    virtual void slot0d0()=0;
    virtual void slot0d4()=0;
    virtual void slot0d8()=0;
    virtual void slot0dc()=0;
    virtual void slot0e0()=0;
    virtual void slot0e4()=0;
    virtual void slot0e8()=0;
    virtual void slot0ec()=0;
    virtual void slot0f0()=0;
    virtual void slot0f4()=0;
    virtual void slot0f8(float)=0;
    virtual float slot0fc()=0;
    virtual void slot100(float)=0;
    virtual float slot104()=0;
    virtual void slot108()=0;
    virtual void slot10c()=0;
    virtual void slot110()=0;
    virtual void slot114()=0;
    virtual void slot118()=0;
    virtual void slot11c()=0;
    virtual void slot120()=0;
    virtual void slot124()=0;
    virtual void slot128()=0;
    virtual void slot12c()=0;
    virtual void slot130()=0;
    virtual void slot134()=0;
    virtual void slot138()=0;
    virtual void slot13c()=0;
    virtual void slot140()=0;
    virtual void slot144()=0;
    virtual void slot148()=0;
    virtual void slot14c()=0;
    virtual void slot150()=0;
    virtual void slot154()=0;
    virtual void slot158()=0;
    virtual void slot15c()=0;
    virtual void slot160()=0;
    virtual void slot164()=0;
    virtual void slot168()=0;
    virtual void slot16c(Rva005B5E50Location*)=0;
    virtual void slot170(const Rva005B5E50Location*)=0;
    virtual void slot174()=0;
    virtual void slot178()=0;
    virtual void slot17c()=0;
    virtual void slot180()=0;
    virtual void slot184()=0;
    virtual void slot188()=0;
    virtual void slot18c()=0;
    virtual void slot190()=0;
    virtual void slot194()=0;
    virtual void slot198()=0;
    virtual void slot19c()=0;
    virtual void slot1a0(bool)=0;
    virtual void slot1a4()=0;
    virtual void slot1a8()=0;
    virtual void slot1ac()=0;
    virtual void slot1b0()=0;
    virtual void slot1b4()=0;
    virtual void slot1b8()=0;
    virtual void slot1bc()=0;
    virtual void slot1c0()=0;
    virtual void slot1c4()=0;
    virtual bool slot1c8()=0;
    virtual void slot1cc()=0;
    virtual void slot1d0()=0;
    virtual void slot1d4()=0;
    virtual void slot1d8()=0;
    virtual void slot1dc()=0;
    virtual void slot1e0()=0;
    virtual void slot1e4()=0;
    virtual void slot1e8()=0;
    virtual void slot1ec(float)=0;
    virtual void slot1f0()=0;
    virtual float slot1f4()=0;
};
class Rva005B5E50UI { public:
    virtual void slot000()=0;
    virtual void slot004()=0;
    virtual void slot008()=0;
    virtual void slot00c()=0;
    virtual void slot010()=0;
    virtual void slot014()=0;
    virtual void slot018()=0;
    virtual void slot01c()=0;
    virtual void slot020()=0;
    virtual void slot024()=0;
    virtual void slot028()=0;
    virtual void slot02c()=0;
    virtual void slot030()=0;
    virtual void __cdecl slot034(UnicodeString,...)=0;
    virtual void slot038()=0;
    virtual void slot03c()=0;
    virtual void slot040()=0;
    virtual void slot044()=0;
    virtual void slot048()=0;
    virtual void slot04c()=0;
    virtual void slot050()=0;
    virtual void slot054()=0;
    virtual void slot058()=0;
    virtual void slot05c()=0;
    virtual void slot060()=0;
    virtual void slot064()=0;
    virtual void slot068()=0;
    virtual void slot06c()=0;
    virtual void slot070()=0;
    virtual void slot074()=0;
    virtual void slot078()=0;
    virtual void slot07c()=0;
    virtual void slot080()=0;
    virtual void slot084()=0;
    virtual void slot088()=0;
    virtual void slot08c()=0;
    virtual void slot090()=0;
    virtual void slot094()=0;
    virtual void slot098()=0;
    virtual void slot09c()=0;
    virtual void slot0a0()=0;
    virtual void slot0a4()=0;
    virtual void slot0a8()=0;
    virtual bool slot0ac()=0;
    char pad004[9]; bool at00d,at00e;
    bool enabled() { typedef bool(Rva005B5E50UI::*P)(); union {void(*raw)();P method;} route={j_0000e11f}; return (this->*route.method)(); }
};
class Rva005B5E50Client { public:
    virtual void slot000()=0;
    virtual void slot004()=0;
    virtual void slot008()=0;
    virtual void slot00c()=0;
    virtual void slot010()=0;
    virtual void slot014()=0;
    virtual void slot018()=0;
    virtual void slot01c()=0;
    virtual void slot020()=0;
    virtual void slot024()=0;
    virtual void slot028()=0;
    virtual void slot02c()=0;
    virtual void slot030()=0;
    virtual void slot034()=0;
    virtual void slot038()=0;
    virtual void slot03c()=0;
    virtual void slot040()=0;
    virtual void slot044()=0;
    virtual void slot048()=0;
    virtual void slot04c()=0;
    virtual void slot050()=0;
    virtual void slot054()=0;
    virtual void slot058()=0;
    virtual void slot05c()=0;
    virtual void slot060()=0;
    virtual void slot064()=0;
    virtual unsigned slot068()=0;
};
class Rva005B5E50Text { public:
    virtual void slot000()=0;
    virtual void slot004()=0;
    virtual void slot008()=0;
    virtual void slot00c()=0;
    virtual void slot010()=0;
    virtual void slot014()=0;
    virtual void slot018()=0;
    virtual void slot01c()=0;
    virtual void slot020()=0;
    virtual void slot024()=0;
    virtual UnicodeString slot028(const char*,bool*)=0;
};
class Rva005B5E50Display { public:
    virtual void slot000()=0;
    virtual void slot004()=0;
    virtual void slot008()=0;
    virtual void slot00c()=0;
    virtual void slot010()=0;
    virtual void slot014()=0;
    virtual void slot018()=0;
    virtual void slot01c()=0;
    virtual void slot020()=0;
    virtual void slot024()=0;
    virtual void slot028()=0;
    virtual unsigned slot02c()=0;
    virtual unsigned slot030()=0;
};


struct Rva005B5E50Logic { char pad000[0x3c]; unsigned at03c; };
struct Rva005B5E50Global { char pad000[0x29]; bool at029; };
struct Rva005B5E50Shell { char pad000[0x58]; bool at058; };
struct Rva005B5E50MouseState { Rva005B5E50Pixel pos; char pad008[0x10]; int at018; };
struct Rva005B5E50Mouse {
    char pad000[0x4d10]; Rva005B5E50MouseState at4d10;
    bool compare(const Rva005B5E50Pixel *a,const Rva005B5E50Pixel *b) {
        typedef bool(Rva005B5E50Mouse::*P)(const Rva005B5E50Pixel*,const Rva005B5E50Pixel*);
        union {void(*raw)();P method;} route={j_0000ccde};
        return (this->*route.method)(a,b);
    }
    void region(Rva005B5E50Region *out) {
        typedef void(Rva005B5E50Mouse::*P)(Rva005B5E50Region*);
        union {void(*raw)();P method;} route={j_0002d281};
        (this->*route.method)(out);
    }
};
extern Rva005B5E50View *g_Rva005B5E50View;
extern Rva005B5E50UI *g_Rva005B5E50UI;
extern Rva005B5E50Client *g_Rva005B5E50Client;
extern Rva005B5E50Text *g_Rva005B5E50Text;
extern Rva005B5E50Display *g_Rva005B5E50Display;
extern Rva005B5E50Logic *g_Rva005B5E50Logic;
extern Rva005B5E50Global *g_Rva005B5E50Global;
extern Rva005B5E50Shell *g_Rva005B5E50Shell;
extern Rva005B5E50Mouse *g_Rva005B5E50Mouse;
extern bool g_Rva005B5E50Scroll[4];

class Rva005B5E50 {
public:
    virtual int translate(const Rva005B5E50Message *msg);
    Rva005B5E50Pixel at004,at00c,at014;
    bool at01c; char pad01d[3];
    Rva005B5E50Pixel at020,at028,at030;
    bool at038,at039,at03a,at03b,at03c; char pad03d[3];
    unsigned at040,at044;
    Rva005B5E50Location at048[8];
    int at148; unsigned at14c,at150;
    bool at154,at155,at156,at157;
    void start(int mode) {
        typedef void(Rva005B5E50::*P)(int);
        union {void(*raw)();P method;} route={j_0002523e};
        (this->*route.method)(mode);
    }
    void stop() {
        typedef void(Rva005B5E50::*P)();
        union {void(*raw)();P method;} route={j_00034d15};
        (this->*route.method)();
    }
};

int Rva005B5E50::translate(const Rva005B5E50Message *msg) {
    int disposition=0;
    int type=msg->at010;
    switch(type) {
    case 0x15: case 0x16: {
        unsigned char key=(unsigned char)msg->argument(0)->integer();
        unsigned char state=(unsigned char)msg->argument(1)->integer();
        bool down=!(state&1);
        if(g_Rva005B5E50Shell && g_Rva005B5E50Shell->at058) break;
        switch(key) {
        case 0xc8:g_Rva005B5E50Scroll[0]=down;break;
        case 0xd0:g_Rva005B5E50Scroll[1]=down;break;
        case 0xcb:g_Rva005B5E50Scroll[2]=down;break;
        case 0xcd:g_Rva005B5E50Scroll[3]=down;break;
        case 0x4b:at154=down;break;
        case 0x4d:at155=down;break;
        case 0x48:at156=down;break;
        case 0x50:at157=down;break;
        }
        if(g_Rva005B5E50UI->slot0ac() || (at038 && at148!=2)) break;
        int count=0;
        for(int i=0;i<4;++i) if(g_Rva005B5E50Scroll[i]) ++count;
        if(count && !at038) start(2);
        else if(!count && at038) stop();
        break;
    }
    case 0xe:
        at150=g_Rva005B5E50Logic->at03c;
        at014=msg->argument(0)->pixel();
        { const int copyX=at014.x,copyY=at014.y; at004.x=copyX; at004.y=copyY; }
        if(!g_Rva005B5E50UI->slot0ac() && !at038) at01c=true;
        break;
    case 0x10:
        at150=g_Rva005B5E50Logic->at03c;
        at01c=false;
        if(at148==1) stop();
        break;
    case 0xa:
        at150=g_Rva005B5E50Logic->at03c;
        at039=true;
        at020=msg->argument(0)->pixel();
        at028=msg->argument(0)->pixel();
        at030=msg->argument(0)->pixel();
        at040=g_Rva005B5E50Client->slot068();
        if(!at038) g_Rva005B5E50View->slot1a0(true);
        break;
    case 0xc: {
        if(at039 && !at038) g_Rva005B5E50View->slot1a0(false);
        at150=g_Rva005B5E50Logic->at03c;
        at039=false;
        int dx=at030.x-at028.x; if(dx<0) dx=-dx;
        int dy=at030.y-at028.y;
        bool moved=(unsigned)dx>5 || (unsigned)dy>5;
        if(!moved && g_Rva005B5E50Client->slot068()-at040<5)
            g_Rva005B5E50View->slot0c4(0,0,0,0);
        break;
    }
    case 3: {
        unsigned width;
        if(at01c && !at038) {
            Rva005B5E50Pixel pos=msg->argument(0)->pixel();
            if(g_Rva005B5E50Mouse->compare(&at004,&pos)) start(1);
        }
        if(!g_Rva005B5E50View->slot1c8()) {
            if(at014.x!=msg->argument(0)->pixel().x || at014.y!=msg->argument(0)->pixel().y)
                at150=g_Rva005B5E50Logic->at03c;
            if(at039) {
                at03a=true; at030=msg->argument(0)->pixel();
            } else if(at03a && at148==1) {
                int dx=at004.x-at014.x,dy=at004.y-at014.y;
                at014=msg->argument(0)->pixel();
                at004.x=at014.x+dx; at004.y=at014.y+dy;
                at03a=false;
            } else at014=msg->argument(0)->pixel();
            unsigned height=g_Rva005B5E50Display->slot030();
            width=g_Rva005B5E50Display->slot02c();
            Rva005B5E50UI *ui=g_Rva005B5E50UI;
            if(!ui->enabled()) {
                if(at038) stop();
                break;
            }
            bool selecting=ui->slot0ac();
            if(selecting) {
                const Rva005B5E50MouseState *mouseState=&g_Rva005B5E50Mouse->at4d10;
                if(mouseState && mouseState->at018!=1) selecting=false;
            }
            if(!g_Rva005B5E50Global->at029 && !selecting) {
                if(at038) {
                    if(at148==3 && at014.x>=3 && at014.y>=3 && (unsigned)at014.y<height-3 && (unsigned)at014.x<width-3) stop();
                } else if(at014.x<3 || at014.y<3 || (unsigned)at014.y>=height-3 || (unsigned)at014.x>=width-3) start(3);
            }
            if(at039) {
                float angle=(at030.x-at020.x)*0.005f;
                g_Rva005B5E50View->slot0f8(g_Rva005B5E50View->slot0fc()+angle);
                at020=msg->argument(0)->pixel();
            }
        } else {
            Rva005B5E50Region region;
            g_Rva005B5E50Mouse->region(&region);
            Coord2D mousePos;
            mousePos.x=(float)g_Rva005B5E50Mouse->at4d10.pos.x;
            mousePos.y=(float)g_Rva005B5E50Mouse->at4d10.pos.y;
            region.x_min+=15.0f; region.x_max-=15.0f;
            region.y_min+=15.0f; region.y_max-=15.0f;
            if(mousePos.x<=region.x_min) {
                g_Rva005B5E50View->slot0f8(g_Rva005B5E50View->slot0fc()+0.046f);
                goto cameraRotated;
            } else if(mousePos.x>=region.x_max) {
                g_Rva005B5E50View->slot0f8(g_Rva005B5E50View->slot0fc()-0.046f);
cameraRotated:
                float span=region.y_max-region.y_min;
                g_Rva005B5E50View->slot1ec(g_Rva005B5E50View->slot1f4()+(((mousePos.y-span*0.5f)/span)+((mousePos.y-span*0.5f)/span))*0.03f);
            } else if(mousePos.y<=region.y_min) {
                g_Rva005B5E50View->slot1ec(g_Rva005B5E50View->slot1f4()-0.02f);
            } else if(mousePos.y>=region.y_max) {
                g_Rva005B5E50View->slot1ec(g_Rva005B5E50View->slot1f4()+0.02f);
            }
            if(at039) {
                float angle=(at030.x-at020.x)*0.001f;
                g_Rva005B5E50View->slot0f8(g_Rva005B5E50View->slot0fc()+angle);
                at020=msg->argument(0)->pixel();
            }
            if(at03b) {
                float angle=(at014.y-at004.y)*0.01f;
                g_Rva005B5E50View->slot100(g_Rva005B5E50View->slot104()+angle);
                at004=msg->argument(0)->pixel();
            }
        }
        break;
    }
    case 0x13: {
        at150=g_Rva005B5E50Logic->at03c;
        int spin=msg->argument(1)->integer();
        if(spin>0) { for(;spin>0;--spin) g_Rva005B5E50View->slot130(); }
        else { for(;spin<0;++spin) g_Rva005B5E50View->slot134(); }
    }
    case 0x6d: stop(); break;
    case 0x21: case 0x22: case 0x23: case 0x24:
    case 0x25: case 0x26: case 0x27: case 0x28: {
        int slot=type-0x20;
        if(slot>0 && slot<=8) {
            g_Rva005B5E50View->slot16c(&at048[slot-1]);
            UnicodeString text;
            text.format(g_Rva005B5E50Text->slot028("GUI:BookmarkXSet",0),slot);
            g_Rva005B5E50UI->slot034(text);
        }
        disposition=1; break;
    }
    case 0x29: case 0x2a: case 0x2b: case 0x2c:
    case 0x2d: case 0x2e: case 0x2f: case 0x30: {
        if(!g_Rva005B5E50UI->at00d || !g_Rva005B5E50UI->at00e) break;
        int slot=type-0x28;
        if(slot>0 && slot<=8) g_Rva005B5E50View->slot170(&at048[slot-1]);
        disposition=1; break;
    }
    case 0x451: { int value; memcpy(&value,msg->argument(0),sizeof(value)); g_Rva005B5E50View->slot070(value); break; }
    }
    return disposition;
}
