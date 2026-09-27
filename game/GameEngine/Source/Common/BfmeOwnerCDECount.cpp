// cl: /EHsc
// 0x008FA4B0: retain the established getCDECount identity from its matched
// caller BfmeOwnerCDE::rva008fa850 (0x008FA850). The geometry summary is the
// 0x24-byte record filled by GeometryInfo::rva0087E190; its +0x1c string owns
// the cleanup visible on both returns. The provider's geometry dispatch uses
// the virtual-base offset at provider+4, as in that matched caller.
// Debug stream slots are witnessed at +0x20 (float), +0x38 (text), +0x4c
// (finish), +0x60 (begin), +0x6c (stream). Short-circuit diagnostic expressions
// preserve retail's conditionally constructed string-temporary EH states.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class CountDebug008FA4B0 {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual CountDebug008FA4B0 &number(float);
 virtual void slot24(); virtual void slot28(); virtual void slot2c(); virtual void slot30(); virtual void slot34();
 virtual CountDebug008FA4B0 &text(const char *);
 virtual void slot3c(); virtual void slot40(); virtual void slot44(); virtual void slot48();
 virtual void finish(int);
 virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
 virtual void begin(); virtual void slot64(); virtual void slot68();
 virtual CountDebug008FA4B0 &stream(void *, void *);
};
extern CountDebug008FA4B0 *g_BFMEIndexBufferDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int);
#define NAMED_DEBUG reinterpret_cast<CountDebug008FA4B0 &>(reinterpret_cast<Debug &>(g_BFMEIndexBufferDebug->stream(0,0).text("Geometry for ")) << object->name())
#define REPORT(msg) (_bfme_debugReportingEnabled() && (_bfme_debugRecordCallsite(1), g_BFMEIndexBufferDebug->begin(), (NAMED_DEBUG msg).finish(2), true))
class Rva000FC640 {
public:
 int m_type;
 float m_height, m_majorRadius, m_minorRadius;
 float m_offsetX, m_offsetY, m_offsetZ;
 AsciiString m_name;
 bool m_enabled;
 Rva000FC640() : m_type(0), m_height(1), m_majorRadius(1), m_minorRadius(1), m_offsetX(0), m_offsetY(0), m_offsetZ(0), m_enabled(true) {}
};
class GeometryInfo {
public:
 void rva0087E190(Rva000FC640 &) const;
 void *m_00; bool m_04;
};
class CountVirtualBase008FA4B0 {
public:
 virtual const GeometryInfo &geometry();
};
class CountLeading008FA4B0 {
public:
 virtual AsciiString name();
};
class CountProvider008FA4B0 : public CountLeading008FA4B0, public virtual CountVirtualBase008FA4B0 {};
class BfmeShapeEU;
class BfmeHostEU { public: int bfmeStepsEU(const BfmeShapeEU *); };
class BfmeOwnerCDE {
public:
 int getCDECount(void *what);
 char m_00[0x20]; float m_20;
};
int BfmeOwnerCDE::getCDECount(void *what)
{
 CountProvider008FA4B0 *object = (CountProvider008FA4B0 *)what;
 const GeometryInfo &geometry = object->geometry();
 Rva000FC640 shape;
 geometry.rva0087E190(shape);
 if (geometry.m_04) {
   unsigned count = ((BfmeHostEU *)this)->bfmeStepsEU((const BfmeShapeEU *)&shape);
   if (count >= 10000) {
     REPORT(.text(" is too large - INI error?\n"));
   } else if (count > 4) {
     switch (shape.m_type) {
       case 0: case 1:
         REPORT(.text(" is too large for a small object.\nReduce major radius to a value less than ").number(1.0f/(m_20+m_20)).text(" or make the geometry non-small.\n"));
         break;
       case 2:
         REPORT(.text(" is too large for a small object.\nReduce the length of the diagonal of the box to a value less than ").number(1.0f/(m_20+m_20)).text(" or make the geometry non-small.\nThe diagonal is calculated as SquareRoot( MajorRad*MajorRad + MinorRad*MinorRad ).\n"));
         break;
     }
   }
   return 4;
 } else {
   unsigned count = ((BfmeHostEU *)this)->bfmeStepsEU((const BfmeShapeEU *)&shape);
   if (count >= 10000) {
     REPORT(.text(" is too large - INI error?\n"));
   }
   return count;
 }
}
