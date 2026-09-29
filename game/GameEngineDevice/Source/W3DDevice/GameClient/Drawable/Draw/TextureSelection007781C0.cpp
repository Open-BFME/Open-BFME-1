inline int clamp779(int v,int lo,int hi) { if(v<lo)return lo; if(v>hi)return hi; return v; }
// stlport
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x007781C0, 779 bytes. Address-qualified receiver view.
// Clears three caller-owned vectors then chooses one texture in each 20-byte
// record using the two witnessed object seed routes. Only unequal names are
// emitted. The record ABI is independently established by the landed
// W3DModelDrawModuleData::parseRandomTexture and Rva007701C0Vector.cpp.
// The +04/+08 receiver pointers and +78/+B0 data offsets are retail accesses;
// no complete owner layout or original method spelling is asserted here.
// STLport string construction/copy and range erase reuse existing typed pins;
// the incorrectly AnimSet-labelled 12-byte insert is reached by the existing
// vector<string> pin at its proven 0x00755CA0 body (ILT 0x0000DB2F).
// Named string scopes preserve retail unwind states. The value-taking clamp
// preserves one pre-loop decrement and its first-iteration register lifetime.
#include "string_base.h"
#include "ascii_string.h"
#include <string>
#include <vector>
#include <string.h>
struct Rva007701C0Element {
 AsciiString m_name;
 _STL::vector<AsciiString> m_vector04;
 int m_word10;
};
struct TextureSelection007781C0Data {
 char at00[0x78];
 _STL::vector<Rva007701C0Element> at78;
 char at84[0xb0-0x84];
 bool atb0;
};
struct TextureSelection007781C0Object {
 char at00[0xfc];
 char* atfc;
 char at100[0x2f0-0x100];
 int at2f0;
};
class TextureSelection007781C0 {
 int at00;
 TextureSelection007781C0Data* at04;
 TextureSelection007781C0Object* at08;
public:
 void collect(int count,_STL::vector<_STL::string>* originals,_STL::vector<_STL::string>* replacements,_STL::vector<int>* values);
};
void TextureSelection007781C0::collect(int count,_STL::vector<_STL::string>* originals,_STL::vector<_STL::string>* replacements,_STL::vector<int>* values) {
 replacements->clear();
 originals->clear();
 values->clear();
 TextureSelection007781C0Data* data=at04;
 TextureSelection007781C0Object* object=at08;
 int seed;
 if(data->atb0) { char* related=object->atfc; seed=*(int*)(related+0x78); } else seed=object->at2f0;
 int ordinal=0;
 for(_STL::vector<Rva007701C0Element>::const_iterator it=data->at78.begin();it!=data->at78.end();++it,++ordinal) {
  int upper=clamp779(count-1,0,(int)it->m_vector04.size()-1);
  if(!it->m_vector04.empty()) {
   int pick=(seed+(seed/3)+(seed/5)+ordinal+(seed&15)*(ordinal+1)) % it->m_vector04.size();
   if(pick<0) pick=0;
   else if(pick>upper) pick=upper;
   if(_stricmp(it->m_vector04[pick].str(),it->m_name.str())!=0) {
    { _STL::string replacement(it->m_vector04[pick].str()); replacements->push_back(replacement); }
    { _STL::string original(it->m_name.str()); originals->push_back(original); }
    values->push_back(it->m_word10);
   }
  }
 }
}
