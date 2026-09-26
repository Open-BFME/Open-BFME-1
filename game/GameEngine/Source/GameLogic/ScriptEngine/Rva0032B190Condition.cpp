// cl: /DNDEBUG /DWIN32 /MD
// RVA 0032B190: comparison dispatched by Rva0032D720 case 53 through ILT
// 00033EBF. The condition's semantic name is not established.
// Object+200 and the two direct calls use the canonical Object/Thing layout.
// The second view returned by 001BFE20 is opaque: only its unsigned-return
// virtual slots 83 and 86 are required here; it is not an Object pointer.
// Parameter+8 is the witnessed script integer/comparison operand.
// The six-target switch table starts at 0032B30C after three alignment bytes.
// A separate scaled intermediate preserves retail's multiply-before-divide
// order; a single expression permits VC7.1 to reassociate these operations.
enum KindOfType { Rva0032B190Kind = 108 };
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS void *unidentified_001BFE20() const;
#include "../Object/object.h"
class Parameter { public: char opaque00[8]; int m_int; };
class BodyModuleInterface { public:
virtual void slot00() = 0;
virtual void slot01() = 0;
virtual void slot02() = 0;
virtual void slot03() = 0;
virtual float slot04() = 0;
virtual void slot05() = 0;
virtual void slot06() = 0;
virtual float slot07() = 0;
};
class Rva0032B190ContainView { public:
virtual void slot00() = 0;
virtual void slot01() = 0;
virtual void slot02() = 0;
virtual void slot03() = 0;
virtual void slot04() = 0;
virtual void slot05() = 0;
virtual void slot06() = 0;
virtual void slot07() = 0;
virtual void slot08() = 0;
virtual void slot09() = 0;
virtual void slot10() = 0;
virtual void slot11() = 0;
virtual void slot12() = 0;
virtual void slot13() = 0;
virtual void slot14() = 0;
virtual void slot15() = 0;
virtual void slot16() = 0;
virtual void slot17() = 0;
virtual void slot18() = 0;
virtual void slot19() = 0;
virtual void slot20() = 0;
virtual void slot21() = 0;
virtual void slot22() = 0;
virtual void slot23() = 0;
virtual void slot24() = 0;
virtual void slot25() = 0;
virtual void slot26() = 0;
virtual void slot27() = 0;
virtual void slot28() = 0;
virtual void slot29() = 0;
virtual void slot30() = 0;
virtual void slot31() = 0;
virtual void slot32() = 0;
virtual void slot33() = 0;
virtual void slot34() = 0;
virtual void slot35() = 0;
virtual void slot36() = 0;
virtual void slot37() = 0;
virtual void slot38() = 0;
virtual void slot39() = 0;
virtual void slot40() = 0;
virtual void slot41() = 0;
virtual void slot42() = 0;
virtual void slot43() = 0;
virtual void slot44() = 0;
virtual void slot45() = 0;
virtual void slot46() = 0;
virtual void slot47() = 0;
virtual void slot48() = 0;
virtual void slot49() = 0;
virtual void slot50() = 0;
virtual void slot51() = 0;
virtual void slot52() = 0;
virtual void slot53() = 0;
virtual void slot54() = 0;
virtual void slot55() = 0;
virtual void slot56() = 0;
virtual void slot57() = 0;
virtual void slot58() = 0;
virtual void slot59() = 0;
virtual void slot60() = 0;
virtual void slot61() = 0;
virtual void slot62() = 0;
virtual void slot63() = 0;
virtual void slot64() = 0;
virtual void slot65() = 0;
virtual void slot66() = 0;
virtual void slot67() = 0;
virtual void slot68() = 0;
virtual void slot69() = 0;
virtual void slot70() = 0;
virtual void slot71() = 0;
virtual void slot72() = 0;
virtual void slot73() = 0;
virtual void slot74() = 0;
virtual void slot75() = 0;
virtual void slot76() = 0;
virtual void slot77() = 0;
virtual void slot78() = 0;
virtual void slot79() = 0;
virtual void slot80() = 0;
virtual void slot81() = 0;
virtual void slot82() = 0;
virtual unsigned int slot83() = 0;
virtual void slot84() = 0;
virtual void slot85() = 0;
virtual unsigned int slot86() = 0;
};
class ScriptEngine { public:
virtual void slot00() = 0;
virtual void slot01() = 0;
virtual void slot02() = 0;
virtual void slot03() = 0;
virtual void slot04() = 0;
virtual void slot05() = 0;
virtual void slot06() = 0;
virtual void slot07() = 0;
virtual void slot08() = 0;
virtual void slot09() = 0;
virtual void slot10() = 0;
virtual void slot11() = 0;
virtual void slot12() = 0;
virtual void slot13() = 0;
virtual void slot14() = 0;
virtual void slot15() = 0;
virtual void slot16() = 0;
virtual void slot17() = 0;
virtual void slot18() = 0;
virtual void slot19() = 0;
virtual void slot20() = 0;
virtual void slot21() = 0;
virtual void slot22() = 0;
virtual void slot23() = 0;
virtual void slot24() = 0;
virtual void slot25() = 0;
virtual Object *getUnitNamed(Parameter *)=0;
};
extern ScriptEngine *TheScriptEngine;
class Rva0032B190Condition { public: bool evaluate(Parameter*,Parameter*,Parameter*); };
bool Rva0032B190Condition::evaluate(Parameter *unit, Parameter *comparison, Parameter *value)
{
 Object *object=TheScriptEngine->getUnitNamed(unit);
 if (!object) return false;
 BodyModuleInterface *body=object->m_body;
 if (!body) return false;
 float current=0.0f;
 float total=1.0f;
 int percent=0;
 if (object->isKindOf(Rva0032B190Kind)) {
  Rva0032B190ContainView *view=(Rva0032B190ContainView*)object->unidentified_001BFE20();
  if (view) { current=(float)view->slot86(); total=(float)view->slot83(); }
 } else {
  current=body->slot04();
  total=object->m_body->slot07();
 }
 if (total>0.0f) { float scaled=current*100.0f; percent=(int)(scaled/total); }
 switch (comparison->m_int) {
 case 0:return percent<value->m_int;
 case 1:return percent<=value->m_int;
 case 2:return percent==value->m_int;
 case 3:return percent>=value->m_int;
 case 4:return percent>value->m_int;
 case 5:return percent!=value->m_int;
 }
 return false;
}
