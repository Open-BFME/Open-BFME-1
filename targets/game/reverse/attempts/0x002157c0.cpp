// ?refresh@Rva002157C0Owner@@QAEXXZ
// partial score=0.942373 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
struct Matrix3D;
struct Thing { void rva00132200(const Matrix3D*); };
struct Rva002157C0Data { char pad[0x5c]; AsciiString field5c; };
struct Rva002157C0Node { char pad[0x74]; int field74; char gap[0xc]; AsciiString field84; Rva002157C0Node *next; };
struct Gen_00383090 { int m(); };
extern Gen_00383090 *TheBfmeGameLogic;
struct BfmeOwnFCB { void bfmeAfterFCB(); void refreshRva00215650(); };
struct Rva002157C0Owner {
 void *vtable; Rva002157C0Data *data; Thing *object; char pad[0xd8]; int fieldE4;
 void refresh();
};
void Rva002157C0Owner::refresh() {
 Thing *obj=object;
 if(obj) {
  Rva002157C0Data *md=data;
  Rva002157C0Node *node=(Rva002157C0Node*)TheBfmeGameLogic->m();
  AsciiString name;
  for(;node;node=node->next) {
   name=node->field84;
   if(name.compare(md->field5c)==0) {
    obj->rva00132200((const Matrix3D*)((char*)node+8));
    fieldE4=node->field74;
    ((BfmeOwnFCB*)this)->bfmeAfterFCB();
    break;
   }
  }
  ((BfmeOwnFCB*)this)->refreshRva00215650();
  ((BfmeOwnFCB*)this)->bfmeAfterFCB();
 }
}
