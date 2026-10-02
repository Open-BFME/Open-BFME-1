// cl: /DNDEBUG /MD /O2 /Ob1 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Retail 0x002E9590, 186 bytes. Matched Events dispatcher selects this body
// for the native ScriptedEvent tag. Its authentic method spelling is unknown.
// Evidence: targets/game/reverse/identity_evidence/002e9590-lua-scripted-event-parser.md
// The four-byte record keeps the existing opaque vector payload identity.
// A normal local record lets VC7.1 reuse the dead incoming parser home.
#include <vector>
#include <string.h>
#pragma intrinsic(memcmp)
class BfmeLexEAN;
class XmlNameSlotList { public: int count(); int finish(); };
class Rva0035EF60 { public: void *get(int); };
class Rva0035EF90 { public: void *get(int); };
class Gen_002df780 { public: void *m(); };
class BfmeThingBLC { public: void bfmeGoBLC(void *); };
struct Gen_t_002e8eb0_m4pod { int a[1]; };
// Partial BFME view: vptr, then fields through the vector at +0x7C.
class __declspec(novtable) LuaScriptEngine {
public:
 virtual ~LuaScriptEngine();
 void rva002E9590ParseScriptedEvent(BfmeLexEAN *parser);
private:
 char pad[0x78];
 _STL::vector<Gen_t_002e8eb0_m4pod> m_eventCapacity;
};
// ?rva002E9590ParseScriptedEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
void LuaScriptEngine::rva002E9590ParseScriptedEvent(BfmeLexEAN *parser)
{
 LuaScriptEngine *owner = this;
 BfmeLexEAN *xml = parser;
 int i = 0;
 if (((XmlNameSlotList *)xml)->count() > 0) {
  do {
   int diff = memcmp(((Rva0035EF60 *)xml)->get(i), "Name", 5);
   if (diff == 0) {
    void *value = ((Rva0035EF90 *)xml)->get(i);
    Gen_t_002e8eb0_m4pod record;
    ((Gen_002df780 *)&record)->m();
    ((BfmeThingBLC *)&record)->bfmeGoBLC(value);
    owner->m_eventCapacity.push_back(record);
   }
   ++i;
  } while (i < ((XmlNameSlotList *)xml)->count());
 }
 ((XmlNameSlotList *)xml)->finish();
}
