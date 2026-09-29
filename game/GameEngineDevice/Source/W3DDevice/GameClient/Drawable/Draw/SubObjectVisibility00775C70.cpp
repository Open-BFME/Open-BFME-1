// stlport
// cl: /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00775C70, 640 bytes. ZH W3DModelDraw::showSubObject supplies
// the name comparison and hide/show loop; BFME adds a second 24-byte record
// vector and per-collection dirty flags. Keep the address-qualified receiver:
// the secondary-interface adjustment and BFME method signature are unproven.
// The four trailing record slots are opaque 32-bit floating-point carriers;
// this body only copies incoming slots 08/10 and assigns 0/1/epsilon constants.
// Their semantic names are deliberately not inferred from the codegen.
// Reuse the landed 24-byte vector insert ABI at 0x00771B10 and the existing
// _Construct pin via ILT 0x000334EC to 0x00768D20; no new callee pin is needed.
// The named wasShown local preserves retail's bool normalization and scratch
// register allocation. The two record scopes preserve the two unwind states.
#include "string_base.h"
template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }
#include "ascii_string.h"
#include <string.h>
namespace _STL {
struct Rva00771B10Element {
 AsciiString name;
 bool hide;
 float at08;
 float at0c;
 float at10;
 float at14;
};
}
namespace _STL { template<class T> void __cdecl _Construct(T*,const T&); }
#include <vector>
class SubObjectVisibility00775C70 {
 char at00[0x40];
 _STL::vector<_STL::Rva00771B10Element,_STL::allocator<_STL::Rva00771B10Element> > at40,at4c;
 char at58[0x164-0x58];
 bool at164,at165;
public:
 void update(const AsciiString& name,bool show,bool fade,float value08,float value10);
};
void SubObjectVisibility00775C70::update(const AsciiString& name,bool show,bool fade,float value08,float value10) {
 if(!name.isEmpty()) {
  if(fade) {
   bool found=false;
   for(_STL::Rva00771B10Element* it=at4c.begin();it!=at4c.end();++it) {
    if(_stricmp(it->name.str(),name.str())==0) {
     at165=true; it->hide=!show; it->at08=value08; it->at10=value10; it->at14=1.0f; found=true;
    }
   }
   if(!found) {
    at165=true;
    _STL::Rva00771B10Element info;
    info.name=name; info.hide=!show; info.at08=value08; info.at10=value10; info.at14=1.0f; info.at0c=show?0.9999f:0.0001f;
    at4c.push_back(info);
   }
  } else {
   bool found=false;
   for(_STL::Rva00771B10Element* it=at40.begin();it!=at40.end();++it) {
    if(_stricmp(it->name.str(),name.str())==0) {
     bool wasShown = !it->hide;
     if(wasShown != show) { at164=true; it->hide=!show; }
     found=true;
    }
   }
   if(!found) {
    at164=true;
    _STL::Rva00771B10Element info;
    info.name=name; info.hide=!show; info.at08=0; info.at0c=1.0f; info.at10=0; info.at14=0;
    at40.push_back(info);
   }
  }
 }
}
