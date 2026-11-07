// cl: /DNDEBUG /MD /EHsc
//
// AptPalantir vtable slot +0x28, retail 0x0079DEE0 (423 B). ilt_oracle contradicts
// ?renderRadarViewBox@AptPalantir@@UAEXXZ (and the sibling rva-style spellings), so the
// name carries the address. Handoff:
// targets/game/reverse/attempt_support/20261107-0079dee0-set-texture-donor.md
// Identity: vtable 0x01127A48 slot +0x28 routes through 0x000392D4 to 0x0079DEE0.
// Matched aptPalantirRenderRadarViewBox at 0x00563C40 calls that slot; constructor installs this table.
// Direct callees QuadrilateralInset0079D530::update (0x0079D530, through ILT 0x0000CA45)
// and RenderBuffer0079DEE0::render (0x00934940) are pinned by address: both are
// thiscall with no stack arguments (plain ret) and the caller ignores EAX.
// The renderer layout (+0x00 shader state, +0x4C texture handle, +0x50 flag,
// +0x54 dirty byte) is the matched Render2DClass constructor's; Set_Texture
// follows the BFME 2 donor Render2DSentenceBuildTexturesBFME2.cpp shape
// (guarded handle operator= then the flag derived from the stored handle),
// already used by Render2DSentenceClass_Build_TexturesMethodThunk.cpp.
struct BfmeV1207 { float m_bfme00,m_bfme04; BfmeV1207(float a,float b):m_bfme00(a),m_bfme04(b){} };
class BfmeA1207 {};
void bfmeGo1207(BfmeA1207 *,const BfmeV1207 *,const BfmeV1207 *,const BfmeV1207 *,const BfmeV1207 *,const BfmeV1207 *,const BfmeV1207 *);
class TextureClass { public: void Release_Ref(); void Add_Ref(){++m_refCount;} void *m_vtable; unsigned short m_refCount; };
class TexRef { public: TextureClass *m_texture;
 TexRef &operator=(const TexRef &o){ if(o.m_texture)o.m_texture->Add_Ref(); if(m_texture)m_texture->Release_Ref(); m_texture=o.m_texture; return *this; } };
class RenderBuffer0079DEE0: public BfmeA1207 { public:
 int m_state00; char m_pad04[0x48]; TexRef m_texture4c; int m_flags50; bool m_dirty54;
 void render();
 void Set_Texture(const TexRef &t){ if(t.m_texture==m_texture4c.m_texture)return; m_texture4c=t; m_flags50=m_texture4c.m_texture?-1:0; }
};
class Rva0079D180 {public: bool compare()const;};
class QuadrilateralInset0079D530 {public: void update();};
class Display {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual RenderBuffer0079DEE0 *slot85();
};
extern Display *TheDisplay;
struct Region0079DEE0 { BfmeV1207 lo,hi; };
struct Image0079DEE0 {char m_pad00[0x14]; Region0079DEE0 m_uv14;};
// Retail 0x0079D070 (ctor shape: store ptr, save *ptr, store value, return this)
// and 0x0079D090 (unwind funclet target: *m_target = m_saved) are this guard's
// out-of-line copies.
struct StateGuard0079DEE0 {
 int *m_target; int m_saved;
 StateGuard0079DEE0(int *p,int value):m_target(p),m_saved(*p){*p=value;}
 ~StateGuard0079DEE0(){*m_target=m_saved;}
};
class AptPalantir {public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void slot20(); virtual void slot24(); virtual void renderRadarViewBoxRva0079DEE0();
 char m_pad04[0x518];Image0079DEE0 *m_image51c;TexRef m_texture520;char m_pad524[0x20]; BfmeV1207 m_coords544[4],m_coords564[4];
};
void AptPalantir::renderRadarViewBoxRva0079DEE0(){
 if(!m_image51c)return;
 RenderBuffer0079DEE0 *renderer=TheDisplay->slot85();
 if(!renderer)return;
 if(((const Rva0079D180 *)this)->compare())((QuadrilateralInset0079D530 *)this)->update();
 renderer->m_dirty54=true;
 renderer->Set_Texture(m_texture520);
 StateGuard0079DEE0 state(&renderer->m_state00,1);
 const Region0079DEE0 *uv=&m_image51c->m_uv14;
 for(int i=0;i<4;++i){
  int next=i+1;if(next>=4)next-=4;
  const BfmeV1207 *inner=&m_coords544[i];
  const BfmeV1207 *nextOuter=&m_coords564[next];
  BfmeV1207 a(uv->lo.m_bfme00,uv->lo.m_bfme04),b(uv->hi.m_bfme00,uv->lo.m_bfme04),c(uv->hi.m_bfme00,uv->hi.m_bfme04),d(uv->lo.m_bfme00,uv->hi.m_bfme04);
  bfmeGo1207(renderer,inner,&m_coords564[i],nextOuter,&a,&b,&c);
  bfmeGo1207(renderer,inner,nextOuter,&m_coords544[next],&a,&c,&d);
 }
 renderer->render();
}
