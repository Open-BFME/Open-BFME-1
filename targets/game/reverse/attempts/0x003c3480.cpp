// ?d_003c3480@@YAXXZ
// partial score=0.1405 date=2026-10-04
// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB /Igame
// stlport
#include <vector>
#include <new>
#include "GameEngine/Source/Common/System/xfer.h"
#include "GameEngine/Source/Common/System/snapshot.h"
// Use the existing owners rather than inventing duplicate class declarations.
#include "GameEngine/Source/Common/MidTwoStoreCtors.cpp"
#include "GameEngine/Source/Common/TinyVfptrCtors.cpp"
#include "GameEngine/Source/Common/Rva003C2F40TreeCtor.cpp"
class Rva003C3480View {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void transfer(Xfer *);
 virtual void slot4(); virtual void slot5(); virtual int kind();
};
class Rva003C3480 {
public: void run(Xfer *, std::vector<Rva003C3480View *> *);
};
void Rva003C3480::run(Xfer *xfer, std::vector<Rva003C3480View *> *items) {
 int count = items->size();
 *xfer == count;
 if (xfer->IsLoading()) {
  for (int i=0; i<count; ++i) {
   int kind;
   xfer->XferEnum("DelayedEventType", &kind, sizeof(kind));
   Rva003C3480View *item;
   switch (kind) {
    case 1: item = reinterpret_cast<Rva003C3480View *>(new Rva003BD6D0); break;
    case 2: item = reinterpret_cast<Rva003C3480View *>(new Rva003BEA00); item->transfer(xfer); break;
    case 4: item = reinterpret_cast<Rva003C3480View *>(new (::operator new(32)) Rva003BD6F0); break;
    case 8: item = reinterpret_cast<Rva003C3480View *>(new (::operator new(28)) Rva003C2F40Owner); break;
   }
   item->transfer(xfer);
   items->push_back(item);
  }
 } else {
  for (int i=0; i<count; ++i) {
   int kind=(*items)[i]->kind();
   xfer->XferEnum("DelayedEventType", &kind, sizeof(kind));
   (*items)[i]->transfer(xfer);
  }
 }
}
