// ?rva00349730@ScriptEngine@@QAEXPAVObject@@ABVAsciiString@@@Z
// partial score=0.8548 date=2026-10-01
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"
class Overridable { public: const Overridable *getFinalOverride() const; };
class ThingTemplate { public: unsigned char head[0x20]; AsciiString name; };
class Object { public: unsigned char head[4]; ThingTemplate *type; unsigned char pad08[0x74-8]; int id; unsigned char pad78[12]; AsciiString name; };
typedef _STL::pair<AsciiString,Object *> NamedRequest;
class ScriptEngine { public: void rva00349730(Object *,const AsciiString &); void AppendDebugMessage(const AsciiString &,bool); unsigned char head[0x1709c]; _STL::vector<NamedRequest> records; };
extern ScriptEngine *TheScriptEngine;
extern const AsciiString Rva01336E50EmptyString;
void ScriptEngine::rva00349730(Object *object,const AsciiString &fallback)
{
 if (!object) return;
 AsciiString name(object->name);
 bool replaced=false;
 if (((const StringBase<char> &)name).compare((const StringBase<char> &)Rva01336E50EmptyString)==0) {
  if (fallback.getLength()==0) return;
  name=fallback;
  replaced=true;
 }
 for (_STL::vector<NamedRequest>::iterator it=records.begin();it!=records.end();++it) {
  if (it->first.compare(name)==0) {
   if (!it->second) {
    AsciiString message;
    ThingTemplate *type=object->type;
    if (type && *(Overridable **)((char *)type+4))
     type=(ThingTemplate *)(*(Overridable **)((char *)type+4))->getFinalOverride();
    const char *typeName=type->name.str();
    message.format(AsciiString("Reassigning dead object's name '%s' to object (%d) of type '%s'\n"),name.str(),object->id,typeName);
    TheScriptEngine->AppendDebugMessage(message,false);
    it->second=object;
   } else if (it->second!=object && replaced) it->second=object;
   return;
  }
  if (object==it->second) { it->first=name; return; }
 }
 NamedRequest request;
 request.first=name; request.second=object;
 records.push_back(request);
}
