// ??0Rva0048F5C0Owner@@QAE@ABVUnicodeString@@PAVRva0048F5C0Descriptor@@@Z
// partial score=0.2014 date=2026-10-01
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /I.
// stlport
#include <vector>
#include "unicode_string.h"
#include "game/GameEngine/Source/GameClient/GUI/IngameNoticeDisplay.cpp"
class Rva0048F5C0Descriptor {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual int slot3();
 unsigned value;
};
class Rva0048F5C0Resource {
public:
 virtual void slot0(); virtual void setText(UnicodeString);
 virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5();
 virtual void setDescriptor(unsigned);
 virtual void slot7(); virtual void slot8(); virtual void slot9(); virtual void slot10();
 virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
 virtual void measure(unsigned *,unsigned *);
 virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
 virtual void slot20(); virtual void slot21(); virtual void append(unsigned short);
};
class Rva0048F5C0Manager {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8();
 virtual Rva0048F5C0Resource *create();
 virtual void release(Rva0048F5C0Resource *);
};
struct Rva0048F5C0FullOwner : Rva0048EC80ResourceOwner {
 char tail[8];
 Rva0048F5C0FullOwner(const UnicodeString &text,Rva0048F5C0Descriptor *desc,int value)
 : Rva0048EC80ResourceOwner((const Rva0048EC80UnicodeString &)text,(Rva0048EC80Descriptor *)desc,value) {}
};
class Rva0048F5C0Owner {
public:
 std::vector<Rva0048F5C0FullOwner *> values;
 Rva0048F5C0Owner(const UnicodeString &text,Rva0048F5C0Descriptor *desc);
};
Rva0048F5C0Owner::Rva0048F5C0Owner(const UnicodeString &text,Rva0048F5C0Descriptor *desc)
{
 if(text.isNotEmpty()) {
  Rva0048F5C0Manager *manager=(Rva0048F5C0Manager *)Rva0048EC80TheManager;
  Rva0048F5C0Resource *resource=manager->create();
  resource->setDescriptor(desc->value);
  UnicodeString partial;
  unsigned maximum=desc->slot3();
  unsigned limit=maximum;
  int remaining=text.getLength();
  int index=0;
  while(remaining>0) {
   unsigned short ch=(unsigned short)text.getCharAt(index++);
   resource->append(ch);
   unsigned width,height;
   resource->measure(&width,&height);
   if(width>maximum) {
    values.push_back(new Rva0048F5C0FullOwner(partial,desc,limit));
    limit=width-limit;
    partial=UnicodeString::TheEmptyString;
    partial+=(wchar_t)ch;
    resource->setText(partial);
   } else {
    limit=width;
    partial+=(wchar_t)ch;
   }
   --remaining;
  }
  if(partial.isNotEmpty()) values.push_back(new Rva0048F5C0FullOwner(partial,desc,limit));
  manager->release(resource);
 }
}
