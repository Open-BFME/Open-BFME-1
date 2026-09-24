// ?draw@W3DDisplay@@UAEXXZ
// partial score=0.94 date=2026-09-24
// cl: /DNDEBUG /MD /EHs-c- /Ireference/shims/sweep
#include <windows.h>
void * __cdecl operator new[](unsigned);
void __cdecl operator delete[](void *);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class W3DView { public: bool updateCameraMovements(); };
class BfmeQ1087 { public: void bfmeGo1087A(); };
class W3DDisplay {
public:
 virtual void draw();
 char pad04[0x28]; unsigned callback2c; char pad30[0xe1]; unsigned char field111;
 void rva006F0300(); void rva006F2CC0(); void rva006EE800(); bool rva006EB500(unsigned);
protected:
 void updateAverageFPS(); void captureScreen(char *,unsigned); void saveScreenShot(char *,unsigned,unsigned);
};
class RvaDrawSlots { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3c();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4c();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5c();
 virtual void slot60();
 virtual void slot64();
 virtual void slot68();
 virtual void slot6c();
 virtual void slot70();
 virtual W3DView *slot74();
 virtual void slot78();
 virtual void slot7c();
 virtual void slot80();
 virtual void slot84();
 virtual void slot88();
 virtual void slot8c();
 virtual void slot90();
 virtual void slot94();
 virtual void slot98();
 virtual void slot9c();
 virtual void slota0();
 virtual void slota4();
 virtual void slota8();
 virtual void slotac();
 virtual void slotb0();
 virtual void slotb4();
 virtual void slotb8();
 virtual void slotbc();
 virtual void slotc0();
 virtual void slotc4();
 virtual void slotc8();
 virtual void slotcc();
 virtual void slotd0();
 virtual void slotd4();
 virtual void slotd8();
 virtual void slotdc();
 virtual void slote0();
 virtual void slote4();
 virtual void slote8();
 virtual void slotec();
 virtual void slotf0();
 virtual void slotf4();
 virtual void slotf8();
 virtual void slotfc();
 virtual void slot100();
 virtual void slot104();
 virtual void slot108();
 virtual void slot10c();
 virtual void slot110();
 virtual void slot114();
 virtual void slot118();
 virtual void slot11c();
 virtual void slot120();
 virtual void slot124();
};
class Rva006F3FC0ClientSlots { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3c();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4c();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5c();
 virtual void slot60();
 virtual void slot64();
 virtual unsigned slot68();
};
class Rva006F3FC0Client : public Rva006F3FC0ClientSlots { public: char pad04[0xc0]; unsigned char fieldc4; };
class Rva006F3FC0Tactical { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3c();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4c();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5c();
 virtual void slot60();
 virtual void slot64();
 virtual void slot68();
 virtual void slot6c();
 virtual void slot70();
 virtual bool slot74();
 virtual void slot78();
 virtual void slot7c();
 virtual void slot80();
 virtual void slot84();
 virtual void slot88();
 virtual void slot8c();
 virtual void slot90();
 virtual void slot94();
 virtual void slot98();
 virtual void slot9c();
 virtual void slota0();
 virtual void slota4();
 virtual void slota8();
 virtual void slotac();
 virtual void slotb0();
 virtual void slotb4();
 virtual void slotb8();
 virtual void slotbc();
 virtual void slotc0();
 virtual void slotc4();
 virtual void slotc8();
 virtual void slotcc();
 virtual void slotd0();
 virtual void slotd4();
 virtual int slotd8();
};
class BfmeGameLogicPause { public: char pad00[0x10c]; int field10c; char pad110[0xd]; unsigned char field11d; bool isGamePaused(); };
class ScriptEngine { public: bool isTimeFast(); };
class TerrainTracksRenderObjClassSystem { public: void update(); };
class WW3D { public: static void Sync(unsigned); };
namespace Debug_Statistics { void Begin_Statistics(); }
void Rva00754A10();
struct Rva006F3FC0Global {
 char pad00[0x1e]; unsigned char field1e; char pad1f[0xb9a];
 unsigned char fieldbb9; char padbba[0x9f]; unsigned char fieldc59; char padc5a[0x272];
 int fieldecc; unsigned char fielded0,fielded1; char paded2[2]; float fielded4,fielded8;
};
extern Rva006F3FC0Global *Rva012ED5C8;
extern BfmeGameLogicPause *Rva012F0898;
extern ScriptEngine *Rva012F076C;
extern Rva006F3FC0Client *Rva012F1464;
extern Rva006F3FC0Tactical *Rva012F1600;
extern TerrainTracksRenderObjClassSystem *Rva012F9D98;
extern unsigned Rva012BAA2C,Rva012F8064,Rva012BB1CC;
extern int Rva012BAA5C,Rva012F804C;
extern HWND ApplicationHWnd;
extern const float Rva0111E36C,Rva010A13C4;

void W3DDisplay::draw()
{
    if (ApplicationHWnd && IsIconic(ApplicationHWnd)) return;
    updateAverageFPS();
    reinterpret_cast<BfmeQ1087 *>(this)->bfmeGo1087A();
    if (callback2c==0x0042f9f0) rva006F0300();
    else if (callback2c==0x0043413f) rva006F2CC0();
    else if (callback2c==0x0040d779) rva006EE800();
    bool frozen = !Rva012F1464->fieldc4;
    W3DView *view = reinterpret_cast<RvaDrawSlots *>(this)->slot74();
    unsigned delta = Rva012F1464->slot68() - Rva012BAA2C;
    if (frozen) delta=0;
    else Rva012BAA2C = Rva012F1464->slot68();
    bool fast=false;
    if (!Rva012F0898->isGamePaused() && Rva012ED5C8->fieldc59) fast=true;
    if (Rva012F076C->isTimeFast()) fast=true;
    if (!frozen && fast && !Rva012F0898->field11d && (Rva012F1464->slot68()%30)!=0) {
        view->updateCameraMovements();
        Rva012F8064 += Rva012BB1CC;
        WW3D::Sync(Rva012F8064);
        return;
    }
    Debug_Statistics::Begin_Statistics();
    if (Rva012ED5C8->fieldbb9!=1 && Rva012F9D98) Rva012F9D98->update();
    Rva012F8064 += Rva012BB1CC*delta;
    WW3D::Sync(Rva012F8064);
    static int prevTime=timeGetTime();
    int now=timeGetTime();
    if (Rva012F1600->slotd8()>1) {
        --Rva012BAA5C;
        if (Rva012BAA5C>1) return;
        Rva012BAA5C=Rva012F1600->slotd8();
    } else prevTime=now-30;
    if (field111) return;
    do {
        if (Rva012ED5C8->fieldbb9!=1) {
            while (Rva012ED5C8->field1e && now-prevTime <29) now=timeGetTime();
            prevTime=now;
        }
        if (Rva012F804C>0 && Rva012ED5C8->fieldecc) {
            Rva012ED5C8->fielded0=true;
            Rva012ED5C8->fielded4=Rva0111E36C/(float)Rva012ED5C8->fieldecc;
            RECT rect;
            POINT point;
            GetClientRect(ApplicationHWnd,&rect);
            point.x=rect.left; point.y=rect.top;
            ClientToScreen(ApplicationHWnd,&point);
            rect.left=point.x; rect.top=point.y;
            point.x=rect.right; point.y=rect.bottom;
            ClientToScreen(ApplicationHWnd,&point);
            rect.right=point.x; rect.bottom=point.y;
            int width=rect.right-rect.left;
            int height=rect.bottom-rect.top;
            char *image=new char[Rva012ED5C8->fieldecc*height*width*3];
            for(int i=0; i<Rva012ED5C8->fieldecc; ++i) {
                Rva012ED5C8->fielded8=((float)i*Rva010A13C4)/(float)Rva012ED5C8->fieldecc;
                Rva012ED5C8->fielded1=(i==Rva012ED5C8->fieldecc-1);
                if (!rva006EB500(now)) frozen=false;
                int count=Rva012ED5C8->fieldecc;
                captureScreen(image+((count/2+i)%count)*width*3,count*width*3);
            }
            --(*reinterpret_cast<volatile int *>(&Rva012F804C));
            saveScreenShot(image,Rva012ED5C8->fieldecc*width,height);
            delete []image;
            Rva012ED5C8->fielded0=false;
        } else if (!rva006EB500(now)) break;
    } while (frozen && !Rva012F1600->slot74() &&
             (Rva012F0898->field10c==1 || Rva012F0898->field10c==5 || Rva012F0898->isGamePaused()));
    if (Rva012F804C>0 && !Rva012ED5C8->fieldecc) {
        --Rva012F804C;
        reinterpret_cast<RvaDrawSlots *>(this)->slot124();
    }
    Rva00754A10();
}

// Evidence: primary W3DDisplay vtable 0x0111EDD0 slot 7 -> ILT 0x000093EF -> RVA 0x006F3FC0.
// Boundary ends with ret at 0x006F445F, size 1184 (Ghidra fragmented size 1178 is stale).
// Complete screenshot branch naturally produces the aligned frame; do not add explicit align.
