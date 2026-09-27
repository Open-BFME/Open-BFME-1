// Retail 0x00377AF0..0x00377CA9 (441 bytes).
// An INI callback: read a name key, append index-list tokens to its existing
// map entry, or insert a freshly parsed vector. No owning class name is proved.
// Data-flow evidence: ILT 0x0002F662 -> parseIndexListVector; tree find through
// 0x00021611; pair/vector construction through 0x00025252 and 0x0003F382;
// insert_unique through 0x00008C1F. Every node stores a key at +0x10 and a
// three-pointer int vector at +0x14. The name table is retail VA 0x012B4180.
// /EHsc- preserves retail's inline converting-pair copy and seven EH states.
// cl: /DNDEBUG /DWIN32 /MD /EHsc- /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>
#include "StringInline.h"
class INI { public: const char *getNextToken(const char *seps=0); };
enum NameKeyType { InvalidKey=-1 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva000BD260 { public: static void parseIndexListVector(INI *,void *,void *,const void *); };
extern const char *const Names00377AF0[];
// Enumeration identity is unproved; the callback writes 32-bit table indices.
enum Index00377AF0 { Index00377AF0_Unknown = -1 };
typedef _STL::vector<Index00377AF0> IndexList00377AF0;
typedef _STL::map<int,IndexList00377AF0> IndexMap00377AF0;
void __cdecl parseNamedIndexLists00377AF0(INI *ini, void *, void *store, const void *)
{
    AsciiString name(ini->getNextToken());
    int key=TheNameKeyGenerator->nameToKey(name.str());
    IndexMap00377AF0 *map=(IndexMap00377AF0 *)store;
    IndexMap00377AF0::iterator it=map->find(key);
    if (it != map->end()) {
        Rva000BD260::parseIndexListVector(ini,0,&it->second,Names00377AF0);
    } else {
        IndexList00377AF0 values;
        Rva000BD260::parseIndexListVector(ini,0,&values,Names00377AF0);
        map->insert(_STL::make_pair(key,values));
    }
}
