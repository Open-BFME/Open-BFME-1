// ?m00267B10@Rva00267B10@@QAEXE@Z
// partial score=0.1974 date=2026-10-03
void j_000022bb();void j_0000b95b();void j_0001742c();void j_0001a9dd();void j_0002191d();void j_00026df0();void j_00028560();void j_0002bb0c();void j_0002c336();void j_000348ec();void j_000399A5();void j_0003dcf8();
struct Rva0020AA00Registry;extern Rva0020AA00Registry *Rva0020AA00TheRegistry;
class ClientRoot4120;extern ClientRoot4120 *TheGameClient;
struct Rva00367E30Logic;extern Rva00367E30Logic *TheBfmeGameLogic;
class InGameUI;extern InGameUI *TheInGameUI;
struct Rva00267B10Receiver {};
template<class R> R invoke0(void(*p)(),void*self) {union {void(*p)();R(Rva00267B10Receiver::*m)();}u;u.p=p;return (((Rva00267B10Receiver*)self)->*u.m)();}
template<class R,class A> R invoke1(void(*p)(),void*self,A a) {union {void(*p)();R(Rva00267B10Receiver::*m)(A);}u;u.p=p;return (((Rva00267B10Receiver*)self)->*u.m)(a);}
template<class R,class A,class B> R invoke2(void(*p)(),void*self,A a,B b) {union {void(*p)();R(Rva00267B10Receiver::*m)(A,B);}u;u.p=p;return (((Rva00267B10Receiver*)self)->*u.m)(a,b);}
template<class R,class A,class B,class C> R invoke3(void(*p)(),void*self,A a,B b,C c) {union {void(*p)();R(Rva00267B10Receiver::*m)(A,B,C);}u;u.p=p;return (((Rva00267B10Receiver*)self)->*u.m)(a,b,c);}
typedef char CheckMemberSize[sizeof(void(Rva00267B10Receiver::*)())==4?1:-1];
struct Rva00267B10Draw {char m00[0xb0];unsigned mB0;char mB4[0x3ac-0xb4];unsigned char m3AC;char m3AD[11];void*m3B8;};
struct Rva00267B10Flags {unsigned words[10];};
struct __single_inheritance Rva00267B10Object;
struct Rva00267B10ObjTable {void*slot[10];Rva00267B10Draw*(Rva00267B10Object::*m28)();};
struct __single_inheritance Rva00267B10Status;
struct Rva00267B10StatusTable {void*slot[127];void(Rva00267B10Status::*m1FC)(int);};
struct Rva00267B10Status {Rva00267B10StatusTable *table;};
struct Rva00267B10Object {Rva00267B10ObjTable*table;void*m04;char m08[0x38-8];float m38[3];float m44;char m48[0x110-0x48];Rva00267B10Flags m110;char m138[0x204-0x138];Rva00267B10Status *m204;};
struct __single_inheritance Rva00267B10Client;
struct Rva00267B10ClientTable {void*slot[24];void(Rva00267B10Client::*m60)(Rva00267B10Draw*);};
struct Rva00267B10Client {Rva00267B10ClientTable *table;};
struct __single_inheritance Rva00267B10UI;
struct Rva00267B10UITable {void*slot[56];void(Rva00267B10UI::*mE0)(Rva00267B10Draw*);};
struct Rva00267B10UI {Rva00267B10UITable*table;};
struct Rva00267B10View {void*m00;char*m04;Rva00267B10Object*m08;char m0C[0xec-12];unsigned mEC;};
class Rva00267B10 {public:void m00267B10(unsigned char);};
void Rva00267B10::m00267B10(unsigned char value) {
 Rva00267B10View *self=(Rva00267B10View*)this;
 Rva00267B10Object *object=self->m08;
 Rva00267B10Draw *draw=(object->*object->table->m28)();
 bool selected=draw->m3AC!=0;
 if(self->m04[0x268] && (object->m110.words[8]&0x800)) {
  if(!(object->m110.words[6]&0x800)) {object->m110.words[6]|=0x800;invoke0<void>(j_0002191d,object);}
  Rva00267B10Status *status=object->m204;(status->*status->table->m1FC)(7);
  invoke1<void,int>(j_000348ec,object,0x15);
  invoke1<void,int>(j_0002bb0c,object,6);
 }
 if(invoke1<void*,char*>(j_00028560,Rva0020AA00TheRegistry,self->m04+0x25c)) {
  Rva00267B10Flags saved=object->m110;
  void *data=draw->m3B8;
  Rva00267B10Client *client=(Rva00267B10Client*)TheGameClient;
  (client->*client->table->m60)(draw);
  void *thing;
  if(value) {thing=object->m04;if(thing){void *next=((void**)thing)[1];if(next)thing=invoke0<void*>(j_000022bb,next);}}
  else thing=invoke1<void*,char*>(j_00028560,Rva0020AA00TheRegistry,self->m04+0x25c);
  draw=invoke3<Rva00267B10Draw*,void*,int,int>(j_0002c336,Rva0020AA00TheRegistry,thing,0,-1);
  if(draw) {
   invoke2<void,Rva00267B10Object*,Rva00267B10Draw*>(j_0003dcf8,TheBfmeGameLogic,object,draw);
   invoke1<void,float*>(j_0001742c,draw,object->m38);
   invoke1<void,float>(j_000399A5,draw,object->m44);
   draw->mB0=self->mEC;
   invoke1<void,Rva00267B10Flags*>(j_0000b95b,object,&saved);
   invoke1<void,Rva00267B10Flags*>(j_0001a9dd,object,&saved);
   invoke1<void,void*>(j_00026df0,draw,data);
   if(selected){Rva00267B10UI *ui=(Rva00267B10UI*)TheInGameUI;(ui->*ui->table->mE0)(draw);}
  }
 }
}
