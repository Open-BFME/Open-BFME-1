// ?init@W3DDisplay@@UAEXXZ
// BFME layout-aware C++ body reconstructed from retail at RVA 0x006ED5B0.
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /Ireference
#include "vector3.h"
#include "CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/rect.h"
#include "shims/stringinline/StringInline.h"
typedef unsigned size_t;
void * __cdecl operator new(size_t);
void __cdecl operator delete(void *);

// The existing W3DDisplay header is Zero Hour: it places initialized at +0x60.
// This scratch TU uses the witnessed BFME layout and carries no ledger claim.
class LightClass; class Render2DClass; class Rva006E6C10;
class W3DDisplay { public:
    virtual void init();
    char pad04[0x24]; Rva006E6C10 *p28; unsigned callback2c;
    char pad30[0x110]; unsigned char initialized140; char pad141[3];
    LightClass *lights144[4]; LightClass *lights154[4]; Render2DClass *render164;
    char pad168[0x10c]; Rva006E6C10 *debug274;
};
class Rva006F6330 { unsigned char data[4]; public: Rva006F6330(); };
class LightClass {
    unsigned char data[0x124];
public: enum LightType { POINT, DIRECTIONAL }; LightClass(LightType);
};
class Rva006ED5B0Scene {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void Set_Ambient_Light(const Vector3 &);
};
class Rva00711B00 { char data[0x108]; public: Rva00711B00(); };
class RTS2DScene { char data[0x118]; public: RTS2DScene(); };
class Open2Counted;
class Rva00710FF0 { public: void store(Open2Counted *,int); };
class Rva00712F60 { char data[0x8a0]; public: Rva00712F60(); };
extern Rva006F6330 *TheRva006F6330;
extern Rva00711B00 *Rva012F8060;
extern RTS2DScene *Rva012F805C;
extern Rva00712F60 *Rva012F8058;
extern void *Rva012ED5C8;
extern void *Rva012F1484;
extern void *ApplicationHWnd;

enum WW3DErrorType { RvaWW3DErrorZero, RvaWW3DErrorOne };
class Rva00956A70 { public: static void store(int); };
class Rva008FE150 { public: static void store(int); };
class WW3D {
public:
    enum PrelitModeEnum { PRELIT_MODE_LIGHTMAP_MULTI_PASS=1 };
    static bool Init(void *,char * = 0,bool = false);
    static bool Shutdown();
    static void Set_Texture_Reduction(int,int);
    static WW3DErrorType Set_Render_Device(int,int,int,int,int,bool,bool,bool);
    static void Set_Prelit_Mode(PrelitModeEnum v) { Rva012D6D80=v; }
    static void Set_Collision_Box_Display_Mask(int);
    static void Enable_Static_Sort_Lists(bool v) { Rva0133F42D=v; }
    static void Set_Thumbnail_Enabled(bool v) { Rva012D6D84=v; }
    static void Set_Screen_UV_Bias(bool v) { Rva0133F42B=v; }
    static void Set_Texture_Bitdepth(int);
private:
    static int Rva012D6D80;
    static bool Rva0133F42D,Rva012D6D84,Rva0133F42B;
};
void bfmeSetSize(unsigned);
class Render2DClass {
    char data[0x58];
public: Render2DClass(); void Set_Coordinate_Range(const RectClass &);
};
enum StaticGameLODLevel { RvaLODMinusOne=-1 };
class GameLODManager {
public: int rva0007E0F0(); bool setStaticLODLevel(StaticGameLODLevel); void rva0007C350(int);
};
extern GameLODManager *TheGameLODManager;
class W3DShaderManager { public: static void init(); };
class GameFont;
class Rva006E6C10 {
    char data[0x30];
public: Rva006E6C10(); void apply(); void setAndNotify(int);
};
extern void *Rva012F1B38;

#define TheGlobalData Rva012ED5C8
#define TheWritableGlobalData Rva012ED5C8
#define TheGlobalLanguageData Rva012F1484
#define TheFontLibrary Rva012F1B38
#define m_3DInterfaceScene Rva012F8060
#define m_2DScene Rva012F805C
#define m_3DScene Rva012F8058

// Retail 0x006ED5B0. BFME fields are accessed by witnessed offset because the
// included Zero Hour W3DDisplay declaration does not describe this layout.
template<class T> static __forceinline T &rvaF(void *p, unsigned off)
{ return *reinterpret_cast<T *>(static_cast<char *>(p) + off); }
template<class T> static __forceinline const T &rvaF(const void *p, unsigned off)
{ return *reinterpret_cast<const T *>(static_cast<const char *>(p) + off); }

void clipCursorToClient();

void W3DRadarResetLock();
char bfmeUnlock1179();
struct Rva006ED5B0Guard {
    Rva006ED5B0Guard() { W3DRadarResetLock(); }
    ~Rva006ED5B0Guard() { bfmeUnlock1179(); }
};
// Constructor targets 0x009EB960 and 0x006FC970, reached by 0x006EDA88
// and 0x006EDB15 respectively. Sizes are the preceding allocation immediates.
class Rva009EB960 { char bytes[12]; public: Rva009EB960(); };
class Rva006FC970 { char bytes[0x2868]; public: Rva006FC970(); };
extern Rva009EB960 *Rva0134FAA0;
class Rva00711050 { public: void store(Open2Counted *, int); };
class FontLibrary { public: GameFont *getFont(AsciiString *, float, bool); };
bool Rva00938620(AsciiString, AsciiString);
void Rva009EBC00(int);
void Rva008FD330(bool);

class Rva006ED5B0DisplaySlots {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24(unsigned); virtual void slot28(unsigned);
    virtual unsigned slot2c(); virtual unsigned slot30();
    virtual void slot34(unsigned); virtual unsigned slot38();
    virtual void slot3c(bool); virtual bool slot40();
    virtual void slot44(); virtual void slot48(); virtual void slot4c();
    virtual void slot50(float,float,float,bool);
    virtual void slot54(); virtual void slot58(); virtual void slot5c();
    virtual void slot60(); virtual void slot64(); virtual void slot68();
    virtual void slot6c(); virtual void slot70(); virtual void slot74();
    virtual void slot78(); virtual void slot7c(); virtual void slot80();
    virtual void slot84(); virtual void slot88(); virtual void slot8c();
    virtual void slot90(); virtual void slot94(int);
};

static __forceinline bool rvaStringNotEmpty(const AsciiString &s) { const unsigned short *p=*(const unsigned short **)&s; return p && p[2]; }

void W3DDisplay::init(void)
{
    if (rvaF<unsigned char>(this,0x140)) return;
    TheRva006F6330 = new Rva006F6330;
    WWMath::Init();
    m_3DInterfaceScene = new Rva00711B00;
    reinterpret_cast<Rva006ED5B0Scene *>(m_3DInterfaceScene)->Set_Ambient_Light(Vector3(1,1,1));
    m_2DScene = new RTS2DScene;
    reinterpret_cast<Rva006ED5B0Scene *>(m_2DScene)->Set_Ambient_Light(Vector3(1,1,1));
    m_3DScene = new Rva00712F60;
    int i;
    for (i=0; i<rvaF<int>(TheGlobalData,0xa58); ++i) {
        rvaF<LightClass *>(this,0x144 + 4*i) = new LightClass(LightClass::DIRECTIONAL);
        rvaF<LightClass *>(this,0x154 + 4*i) = new LightClass(LightClass::DIRECTIONAL);
    }
    Rva006ED5B0DisplaySlots *d = reinterpret_cast<Rva006ED5B0DisplaySlots *>(this);
    d->slot94(rvaF<int>(TheGlobalData,0x218));
    for (i=0; i<rvaF<int>(TheGlobalData,0xa58); ++i) {
        reinterpret_cast<Rva00710FF0 *>(m_3DScene)->store(rvaF<Open2Counted *>(this,0x144+4*i),i);
        reinterpret_cast<Rva00711050 *>(m_3DScene)->store(rvaF<Open2Counted *>(this,0x154+4*i),i);
    }
    if (rvaF<bool>(TheGlobalData,0xbc5)) bfmeSetSize(1);
    if ((unsigned char)WW3D::Init(ApplicationHWnd) != 1) throw (unsigned)0xdead0007;
    WW3D::Set_Prelit_Mode(WW3D::PRELIT_MODE_LIGHTMAP_MULTI_PASS);
    Rva00956A70::store(0);
    WW3D::Enable_Static_Sort_Lists(true);
    WW3D::Set_Thumbnail_Enabled(false);
    WW3D::Set_Screen_UV_Bias(true);
    Rva008FE150::store(32);
    d->slot3c(rvaF<bool>(TheGlobalData,0x29));
    render164 = new Render2DClass;
    if (TheGameLODManager) {
        if (rvaF<int>(TheGameLODManager,0x16c0)==-1)
            TheGameLODManager->setStaticLODLevel((StaticGameLODLevel)TheGameLODManager->rva0007E0F0());
        else {
            int reduction=rvaF<int>(TheGlobalData,0x68);
            if (reduction>0) {
                WW3D::Set_Texture_Reduction(reduction,6);
                TheGameLODManager->rva0007C350(reduction);
            }
        }
    }
    d->slot24(rvaF<unsigned>(TheGlobalData,0x2c));
    d->slot28(rvaF<unsigned>(TheGlobalData,0x30));
    d->slot34(32);
    {
        Rva006ED5B0Guard guard;
        if ((unsigned char)WW3D::Set_Render_Device(0,d->slot2c(),d->slot30(),d->slot38(),d->slot40(),true,false,true)!=1) {
            rvaF<unsigned>(TheWritableGlobalData,0x2c)=800;
            rvaF<unsigned>(TheWritableGlobalData,0x30)=600;
            d->slot24(rvaF<unsigned>(TheGlobalData,0x2c));
            d->slot28(rvaF<unsigned>(TheGlobalData,0x30));
            if ((unsigned char)WW3D::Set_Render_Device(0,d->slot2c(),d->slot30(),d->slot38(),d->slot40(),true,false,true)!=1) {
                WW3D::Shutdown(); WWMath::Shutdown(); throw (unsigned)0xdead0007;
            }
        }
        if (d->slot40()) Rva008FD330(false); else clipCursorToClient();
    }
    render164->Set_Coordinate_Range(RectClass(0,0,(float)d->slot2c(),(float)d->slot30()));
    Rva0134FAA0 = new Rva009EB960;
    Rva00938620(rvaF<AsciiString>(TheGlobalData,0xdc0),rvaF<AsciiString>(TheGlobalData,0xdc4));
    if (rvaF<bool>(TheGlobalData,0x1278)) Rva009EBC00(0);
    Rva006FC970 *p = new Rva006FC970;
    rvaF<Rva006FC970 *>(this,0x180)=p;
    if (p) reinterpret_cast<Rva006ED5B0DisplaySlots *>(p)->slot04();
    if (rvaF<float>(TheGlobalData,0xc68)!=1.0f) d->slot50(rvaF<float>(TheGlobalData,0xc68),0,1,false);
    { Rva006ED5B0Guard guard; W3DShaderManager::init(); }
    debug274=new Rva006E6C10;
    p28=debug274;
    if (debug274) {
        debug274->apply();
        GameFont *font;
        if (TheGlobalLanguageData && rvaStringNotEmpty(rvaF<AsciiString>(TheGlobalLanguageData,0xc4)))
            font=reinterpret_cast<FontLibrary *>(TheFontLibrary)->getFont(&rvaF<AsciiString>(TheGlobalLanguageData,0xc4),(float)rvaF<int>(TheGlobalLanguageData,0xc8),rvaF<bool>(TheGlobalLanguageData,0xcc));
        else font=reinterpret_cast<FontLibrary *>(TheFontLibrary)->getFont(&AsciiString("FixedSys"),8.0f,false);
        debug274->setAndNotify((int)font);
        rvaF<int>(debug274,0x28)=13;
        rvaF<int>(debug274,0x24)=9;
    }
    rvaF<unsigned char>(this,0x140)=1;
    if (rvaF<bool>(TheGlobalData,0xa92)) rvaF<unsigned>(this,0x2c)=0x0042f9f0;
    else if (rvaF<bool>(TheGlobalData,0xa93)) rvaF<unsigned>(this,0x2c)=0x00448658;
    else rvaF<unsigned>(this,0x2c)=rvaF<bool>(TheGlobalData,0xa97) ? 0x0043413f : 0;
}
