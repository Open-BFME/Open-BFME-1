// ?method@Rva000AF660Owner@@QAEXXZ
// partial score=0.6909 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /I.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string.h>
#include "ascii_string.h"
#pragma intrinsic(strlen)
template<> inline void StringBase<char>::set(const char *s) { set(s,s ? (int)strlen(s):0); }
#include "game/GameEngine/Source/Common/CarvedBFMERetailAsciiStringDestructor.cpp"
struct Rva000AF660Record { AsciiString name; int index; _STL::vector<BFMERetailAsciiString> values; };
class Rva000AF660Owner { public: void method(); private: char head[8]; Rva000AF660Record records[6]; };
void Rva000AF660Owner::method() {
 struct Entry { int index; const char *name; } entries[6] = {
  {0,"RiverTextures"},{1,"WaterBumpMapTextures"},{2,"RiverAlphaEdgeTextures"},{3,"WaterSkyTextures"},{5,"RiverSparkleTextures"},{4,"RiverNoiseTextures"}
 };
 for(int i=0;i<6;++i) {
  Rva000AF660Record &record=records[entries[i].index];
  record.values.erase(record.values.begin(),record.values.end());
  ((StringBase<char> *)&record.name)->set(entries[i].name);
  record.index=entries[i].index;
 }
}
