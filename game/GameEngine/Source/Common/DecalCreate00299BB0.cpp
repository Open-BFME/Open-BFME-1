// Retail 0x00299BB0: creates a projected decal from the configured curve.
// Owner identity is unproved; every layout below retains its address token.
extern "C" __declspec(dllimport) char* __cdecl strncpy(char*,const char*,unsigned int);
class U4Curve006095D0 { public: float evaluate(int) const; };
class BfmeColourABK { public: void bfmeSetABK(int); };
struct Position00299BB0 { float x,y,z; };
struct Result00299BB0 : BfmeColourABK { char pad00[8]; Position00299BB0 at08; };
struct Config00299BB0 { char pad00[8]; char* at08; int at0c; U4Curve006095D0 at10; };
struct Input00299BB0 { char pad00[0x38]; Position00299BB0 at38; };
struct DecalInfo00299BB0 {
 char name[128]; int at80; bool at84,at85; float at88,at8c,at90,at94; char pad98[4]; float at9c; bool ata0;
 DecalInfo00299BB0() : at9c(20.0f),ata0(false) {}
};
class Manager00299BB0 { public: virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c(); virtual Result00299BB0* create(int,DecalInfo00299BB0*,DecalInfo00299BB0*); };
extern Manager00299BB0* g_manager00299BB0;
class DecalCreate00299BB0 {
public: void create();
 char pad00[4]; Config00299BB0* at04; Input00299BB0* at08; char pad0c[0x18]; Result00299BB0* at24;
};
void DecalCreate00299BB0::create() {
 if(at24) return;
 Config00299BB0* config=at04;
 if(!config->at08 || !*(short*)(config->at08+4)) return;
 DecalInfo00299BB0 info;
 float radius=config->at10.evaluate(0);
 strncpy(info.name,config->at08 ? config->at08+8 : "",64);
 info.name[63]=0;
 info.at80=64;
 info.at84=false; info.at85=true;
 info.at8c=info.at88=radius+radius;
 info.at94=info.at90=0.0f;
 at24=g_manager00299BB0->create(64,&info,&info);
 if(at24) {
  at24->at08=at08->at38;
  at24->bfmeSetABK(config->at0c);
 }
}

