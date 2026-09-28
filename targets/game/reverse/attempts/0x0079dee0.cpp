// ?d_0079dee0@@YAXXZ
// partial score=0.978 date=2026-09-28
// ?renderRadarViewBox@AptPalantir@@UAEXXZ
// Identity: vtable 0x01127A48 slot +0x28 routes through 0x000392D4 to 0x0079DEE0.
// Matched aptPalantirRenderRadarViewBox at 0x00563C40 calls that slot; constructor installs this table.
// Remaining unlanded direct callees: QuadrilateralInset0079D530::update at 0x0079D530
// and RenderBuffer0079DEE0::render at 0x00934940. No pins added.
// cl: /DNDEBUG /MD /EHsc
struct BfmeV1207 { float m_bfme00,m_bfme04; BfmeV1207(float a,float b):m_bfme00(a),m_bfme04(b){} };
class BfmeA1207 {};
void bfmeGo1207(BfmeA1207 *,const BfmeV1207 *,const BfmeV1207 *,const BfmeV1207 *,const BfmeV1207 *,const BfmeV1207 *,const BfmeV1207 *);
class TextureClass { public: void Release_Ref(); void *m_vtable; unsigned short m_refCount; };
class RenderBuffer0079DEE0: public BfmeA1207 { public:
 unsigned m_state00; char m_pad04[0x48]; TextureClass *m_texture4c; unsigned m_flags50; bool m_dirty54;
 void render();
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
struct StateGuard0079DEE0 {
 RenderBuffer0079DEE0 *m_object; unsigned m_state;
 StateGuard0079DEE0(RenderBuffer0079DEE0 *p):m_object(p),m_state(p->m_state00){p->m_state00=1;}
 ~StateGuard0079DEE0(){m_object->m_state00=m_state;}
};
class AptPalantir {public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void slot20(); virtual void slot24(); virtual void renderRadarViewBox();
 char m_pad04[0x518];Image0079DEE0 *m_image51c;TextureClass *m_texture520;char m_pad524[0x20]; BfmeV1207 m_coords544[4],m_coords564[4];
};
void AptPalantir::renderRadarViewBox(){
 if(!m_image51c)return;
 RenderBuffer0079DEE0 *renderer=TheDisplay->slot85();
 if(!renderer)return;
 if(((const Rva0079D180 *)this)->compare())((QuadrilateralInset0079D530 *)this)->update();
 renderer->m_dirty54=true;
 if(m_texture520!=renderer->m_texture4c){
  if(m_texture520)++m_texture520->m_refCount;
  if(renderer->m_texture4c)renderer->m_texture4c->Release_Ref();
  TextureClass *texture=m_texture520;
  unsigned flags=texture ? -1 : 0;
  renderer->m_texture4c=texture;
  renderer->m_flags50=flags;
 }
 StateGuard0079DEE0 state(renderer);
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
