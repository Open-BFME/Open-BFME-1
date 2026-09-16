// ?rva000D9680@Rva000D9680Player@@QAEXXZ
// partial score=0.987 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
struct Rva000D9680Strings {
 Rva000D9680Strings(const Rva000D9680Strings &);
 ~Rva000D9680Strings();
 AsciiString *first, *last, *end;
};
struct Rva000D9680Template { char pad[0xf4]; Rva000D9680Strings strings; };
class ThingTemplate;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
extern ThingFactory *TheThingFactory;
class Rva000D9680Player;
struct Rva000FB3F0 {
 void rva000FB3F0(const ThingTemplate *, Rva000D9680Player *);
};
class Rva000D9680Player {
public:
 void rva000D9680();
 void *vtable;
 Rva000D9680Template *definition;
 char pad008[0x684-8];
 Rva000FB3F0 field684;
};
#pragma comment(linker, "/alternatename:??0Rva000D9680Strings@@QAE@ABU0@@Z=?j_00015474@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva000D9680Strings@@QAE@XZ=?j_00026ab2@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000FB3F0@Rva000FB3F0@@QAEXPBVThingTemplate@@PAVRva000D9680Player@@@Z=?j_00049b1b@@YAXXZ")
void Rva000D9680Player::rva000D9680() {
 if (definition) {
  Rva000D9680Strings names(definition->strings);
  int count=names.last-names.first;
  int index=0;
  if(count>0) do {
   AsciiString *first = names.first;
   ThingFactory *factory = (ThingFactory *volatile &)TheThingFactory;
   const ThingTemplate *resolved=factory->findTemplate(first[index]);
   if(resolved) field684.rva000FB3F0(resolved,this);
   ++index;
  } while(index<count);
 }
}
