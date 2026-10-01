// Retail 0x0040A260; address-derived snapshot owner.
// Version storage occupies four bytes; Xfer consumes its first two bytes.
// XferException identity is witnessed by ThrowInfo VA 0x011DFE5C.
// cl: /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
#include "ascii_string.h"
#include "xfer.h"
struct XferException {
 XferException(int,const char*,...);
 XferException(const XferException&);
 ~XferException();
 char *text; int tag;
};
struct BlockView0040A260 {
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
 virtual void begin(const char*); virtual void end(); virtual void skip(const char*);
};
struct Snapshot0040A260 {
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void transfer(Xfer*);
};
class ThingTemplate;
// TU-local view of the 0x012EF1D8 template singleton. findTemplate is a real
// ThingFactory member, so the view keeps the class name (callee mangling) and
// the global takes the canonical spelling.
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString&); };
extern ThingFactory *TheThingFactory;
struct EffectFactory0040A260 { Snapshot0040A260 *create001B0E90(const ThingTemplate*,void*); };
extern EffectFactory0040A260 *Effects0040A260;
extern void *Owner0040A260;
struct RGBColor { float red,green,blue; };
struct BuffTransfer0040A260 {
 int field00; bool field04; char bytes05[3]; int field08,field0c,field10,field14;
 Snapshot0040A260 *field18; const ThingTemplate *field1c; RGBColor field20; float field2c;
 Snapshot0040A260 field30;
 void transfer(Xfer*);
};
void BuffTransfer0040A260::transfer(Xfer *xfer) {
 { struct VersionStorage { Xfer::Version value; unsigned short padding; } storage; Xfer::Version &version=storage.value; version.data[0]=1; version.data[1]=5;
 *xfer == version;
 if(xfer->IsCRC()) return;
 if(version.data[1]<5) throw XferException(2,0); }
 *xfer == field04;
 xfer->XferRawBytes(&field08,4);
 xfer->XferRawBytes(&field0c,4);
 *xfer == field10; *xfer == field14;
 bool hasTemplate=field1c!=0;
 *xfer == hasTemplate;
 AsciiString name;
 if(xfer->IsLoading()) {
  if(hasTemplate) {
   *xfer == name;
   field1c=TheThingFactory->findTemplate(name);
   if(!field1c) throw XferException(4,0);
  } else field1c=0;
 } else if(hasTemplate) {
  name=*(const AsciiString*)((const char*)field1c+0x20);
  *xfer == name;
 }
 bool hasEffect=field18!=0;
 *xfer == hasEffect;
 if(xfer->IsLoading()) {
  if(hasEffect) {
   if(field1c && Owner0040A260) {
    field18=Effects0040A260->create001B0E90(field1c,Owner0040A260);
    ((BlockView0040A260*)xfer)->begin("TBUFF");
    field18->transfer(xfer);
    ((BlockView0040A260*)xfer)->end();
   } else ((BlockView0040A260*)xfer)->skip("TBUFF");
  } else field18=0;
 } else if(hasEffect) {
  ((BlockView0040A260*)xfer)->begin("TBUFF");
    field18->transfer(xfer);
    ((BlockView0040A260*)xfer)->end();
 }

 *xfer == field20;
 *xfer == field2c;
 field30.transfer(xfer);
}
