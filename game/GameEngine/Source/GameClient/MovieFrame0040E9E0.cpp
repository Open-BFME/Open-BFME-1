// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0040E9E0, 559 bytes through RET 4.
// Address-derived movie-frame dispatcher. The receiver and stream layout agree
// with the matched MovieOpen0040E3B0::open/play0040F780 bodies: stream +0x34,
// flags +0x38, completion byte +0x59 and render virtual slot +0x164.
// Callee update0040E680 takes a bool (RET 4); ready/advance/frame are witnessed
// at stream vtable offsets +0x14/+0x18/+0x20. Return flags start at 2.
// The +0x138 counter is a volatile ABI view preserving retail's separate load,
// increment and store around the Sleep(1) path; no original qualifier is claimed.
// Clock values are signed 64-bit (SUB/SBB, signed high-word comparison, FILD).
// The two format strings and all imported call slots were read from retail.
extern "C" __declspec(dllimport) int __cdecl sprintf(char*,const char*,...);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char*);
class DX8Wrapper { public: static unsigned char Try_Acquire_Device_Lock(unsigned long); };
class BfmeObjDC { public: void bfmeGoDC(); };
char bfmeUnlock1179();
void setFPMode();
struct MovieStream0040E3B0 {
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
 virtual bool ready(int); virtual unsigned advance(int); virtual void v1c(); virtual int frame();
};
struct Engine0040E9E0 {
 virtual void v00();
 virtual void v04();
 virtual void v08();
 virtual void v0c();
 virtual void v10();
 virtual void v14();
 virtual void v18();
 virtual void v1c();
 virtual void v20();
 virtual void v24();
 virtual void v28();
 virtual void v2c();
 virtual void v30();
 virtual void v34();
 virtual void v38();
 virtual void v3c();
 virtual void v40();
 virtual bool active();
};
struct MovieControl0040F780 { virtual void v00(); virtual void v04();virtual void v08();virtual void v0c();virtual void v10();virtual void update();};
// The global this body reads at 0x012F1B40 is EA's window-manager singleton,
// spelled in exactly one name everywhere in the link:
// `GameWindowManager *TheWindowManager' (?TheWindowManager@@3PAVGameWindowManager@@A),
// defined in game/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp. The
// slot this call site uses keeps its TU-local ABI view; only the spelling of the
// global changes.
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
extern Engine0040E9E0 *EngineGlobal0040E9E0;
extern __int64 Previous0040E9E0, Current0040E9E0, Threshold0040E9E0, Elapsed0040E9E0;
extern bool Trace0040E9E0;
extern double Sum0040E9E0;
extern double Interval0040F780;
extern int Count0040E9E0;
extern "C" int __identifier("?Count0040E9E0@@3HA") = 0;
struct MovieOpen0040E3B0 {
 virtual void v00();
 virtual void v04();
 virtual void v08();
 virtual void v0c();
 virtual void v10();
 virtual void v14();
 virtual void v18();
 virtual void v1c();
 virtual void v20();
 virtual void v24();
 virtual void v28();
 virtual void v2c();
 virtual void v30();
 virtual void v34();
 virtual void v38();
 virtual void v3c();
 virtual void v40();
 virtual void v44();
 virtual void v48();
 virtual void v4c();
 virtual void v50();
 virtual void v54();
 virtual void v58();
 virtual void v5c();
 virtual void v60();
 virtual void v64();
 virtual void v68();
 virtual void v6c();
 virtual void v70();
 virtual void v74();
 virtual void v78();
 virtual void v7c();
 virtual void v80();
 virtual void v84();
 virtual void v88();
 virtual void v8c();
 virtual void v90();
 virtual void v94();
 virtual void v98();
 virtual void v9c();
 virtual void va0();
 virtual void va4();
 virtual void va8();
 virtual void vac();
 virtual void vb0();
 virtual void vb4();
 virtual void vb8();
 virtual void vbc();
 virtual void vc0();
 virtual void vc4();
 virtual void vc8();
 virtual void vcc();
 virtual void vd0();
 virtual void vd4();
 virtual void vd8();
 virtual void vdc();
 virtual void ve0();
 virtual void ve4();
 virtual void ve8();
 virtual void vec();
 virtual void vf0();
 virtual void vf4();
 virtual void vf8();
 virtual void vfc();
 virtual void v100();
 virtual void v104();
 virtual void v108();
 virtual void v10c();
 virtual void v110();
 virtual void v114();
 virtual void v118();
 virtual void v11c();
 virtual void v120();
 virtual void v124();
 virtual void v128();
 virtual void v12c();
 virtual void v130();
 virtual void v134();
 virtual void v138();
 virtual void v13c();
 virtual void v140();
 virtual void v144();
 virtual void v148();
 virtual void v14c();
 virtual void v150();
 virtual void v154();
 virtual void v158();
 virtual void v15c();
 virtual void v160();
 virtual void render(bool);
 char bytes04[0x30]; MovieStream0040E3B0 *stream34; int flags38;
 int field3c,field40; char bytes44[0x15]; bool field59;
 char bytes5a[0xde]; volatile int field138;
 bool update0040E680(bool);
 unsigned frame0040E9E0(int);
};
unsigned MovieOpen0040E3B0::frame0040E9E0(int force)
{
    unsigned result = 2;
    char text[40];
    if (!force && (field3c || field40))
        return 0;
    if (stream34)
    {
        if (!EngineGlobal0040E9E0->active())
        {
            Sleep(10);
            return 0;
        }
        Elapsed0040E9E0 = Current0040E9E0 - Previous0040E9E0;
        if (Elapsed0040E9E0 > Threshold0040E9E0)
            sprintf(text, "%d", stream34->frame());
        Previous0040E9E0 = Current0040E9E0;
        if (stream34->ready(flags38))
        {
            if (!update0040E680(false))
            {
                ((BfmeObjDC*)this)->bfmeGoDC();
                if (DX8Wrapper::Try_Acquire_Device_Lock(1))
                {
                    field138 = 0;
                    if (!EngineGlobal0040E9E0->active())
                    {
                        bfmeUnlock1179();
                        Sleep(10);
                        return 0;
                    }
                    result = stream34->advance(flags38);
                    if (result & 2)
                        field59 = true;
                    ((MovieControl0040F780 *)TheWindowManager)->update();
                    render(false);
                    bfmeUnlock1179();
                    setFPMode();
                    if (Trace0040E9E0)
                    {
                        Sum0040E9E0 += (double)(Current0040E9E0 - Previous0040E9E0);
                        if (Count0040E9E0++ > 30)
                        {
                            sprintf(text, "Avg frame time %4.4f\n", Interval0040F780 * Sum0040E9E0);
                            OutputDebugStringA(text);
                            Sum0040E9E0 = 0.0;
                            Count0040E9E0 = 0;
                        }
                    }
                }
                else
                {
                    Sleep(1);
                    ++field138;
                }
            }
            else
                field59 = true;
        }
    }
    return result;
}
